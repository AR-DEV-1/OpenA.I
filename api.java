import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;
import org.json.JSONObject;

public class ChatGPT {

    private final String OPENAI_API_KEY = "YOUR_OPENAI_API_KEY";
    private final String OPENAI_API_URL = "https://api.openai.com/v1/";

    public String generateResponse(String prompt) {
        String responseText = "";
        try {
            OkHttpClient client = new OkHttpClient();
            MediaType mediaType = MediaType.parse("application/json");
            JSONObject jsonBody = new JSONObject()
                    .put("prompt", prompt)
                    .put("temperature", 0.5)
                    .put("max_tokens", 50)
                    .put("top_p", 1)
                    .put("frequency_penalty", 0)
                    .put("presence_penalty", 0);
            RequestBody body = RequestBody.create(mediaType, jsonBody.toString());
            Request request = new Request.Builder()
                    .url(OPENAI_API_URL + "engines/davinci-codex/completions")
                    .post(body)
                    .addHeader("Content-Type", "application/json")
                    .addHeader("Authorization", "Bearer " + OPENAI_API_KEY)
                    .build();
            Response response = client.newCall(request).execute();
            String responseBody = response.body().string();
            JSONObject jsonResponse = new JSONObject(responseBody);
            responseText = jsonResponse.getJSONArray("choices").getJSONObject(0).getString("text");
        } catch (Exception e) {
            System.out.println("Error generating response from OpenAI: " + e.getMessage());
        }
        return responseText;
    }

}
