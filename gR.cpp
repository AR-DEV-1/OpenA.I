int main() {
    std::string apiKey = "YOUR_OPENAI_API_KEY";
    std::string prompt = "What is the meaning of life?";
    std::string response = generateResponse(prompt, apiKey);
    std::cout << "Response: " << response << std::endl;
    return 0;
}
