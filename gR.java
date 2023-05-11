public static void main(String[] args) {
    ChatGPT chatbot = new ChatGPT();
    String prompt = "What is the meaning of life?";
    String response = chatbot.generateResponse(prompt);
    System.out.println("Response: " + response);
}
