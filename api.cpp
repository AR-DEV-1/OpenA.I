#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string generateResponse(const std::string& prompt, const std::string& apiKey) {
    std::string responseText;
    try {
        CURL* curl = curl_easy_init();
        if (curl) {
            std::string url = "https://api.openai.com/v1/engines/davinci-codex/completions";
            std::string authorization = "Authorization: Bearer " + apiKey;

            json body = {
                {"prompt", prompt},
                {"temperature", 0.5},
                {"max_tokens", 50},
                {"top_p", 1},
                {"frequency_penalty", 0},
                {"presence_penalty", 0}
            };

            std::string bodyStr = body.dump();
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, bodyStr.c_str());
            curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            headers = curl_slist_append(headers, authorization.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            std::string responseStr;
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](char* ptr, size_t size, size_t nmemb, void* userdata) -> size_t {
                std::string* response = reinterpret_cast<std::string*>(userdata);
                response->append(ptr, size * nmemb);
                return size * nmemb;
            });
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseStr);

            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "Error generating response from OpenAI: " << curl_easy_strerror(res) << std::endl;
            } else {
                json jsonResponse = json::parse(responseStr);
                responseText = jsonResponse["choices"][0]["text"];
            }
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error generating response from OpenAI: " << e.what() << std::endl;
    }
    return responseText;
}
