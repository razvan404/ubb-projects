package api.utils;

import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;

public class JsonParser {
    private final static ObjectMapper objectMapper = new ObjectMapper();
    public static String toJson(Object object) throws IOException {
        try {
            return objectMapper.writeValueAsString(object);
        } catch (Exception ex) {
            throw new IOException(ex);
        }
    }

    public static <T> T fromJson(String json, Class<T> type) throws IOException {
        try {
            return objectMapper.readValue(json, type);
        } catch (Exception ex) {
            throw new IOException(ex);
        }
    }

    public static <T> T changeType(Object obj, Class<T> type) throws IOException {
        try {
            return JsonParser.fromJson(JsonParser.toJson(obj), type);
        } catch (Exception ex) {
            throw new IOException(ex);
        }
    }
}
