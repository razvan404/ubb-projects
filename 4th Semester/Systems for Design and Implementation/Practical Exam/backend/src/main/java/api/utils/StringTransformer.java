package api.utils;

public class StringTransformer {
    public static String enumToPascalCase(String str) {
        String[] words = str.split("_");
        StringBuilder sb = new StringBuilder();
        for (String word : words) {
            sb.append(word.substring(0, 1).toUpperCase());
            sb.append(word.substring(1).toLowerCase());
        }
        return sb.toString();
    }
}
