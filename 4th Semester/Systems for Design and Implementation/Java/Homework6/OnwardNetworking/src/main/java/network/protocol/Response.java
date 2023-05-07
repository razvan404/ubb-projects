package network.protocol;

import java.io.Serializable;

public class Response implements Serializable {
    private ResponseType type;
    private Object data;

    private Response() {}

    public ResponseType getType() {
        return type;
    }

    public Object getData() {
        return data;
    }

    @Override
    public String toString() {
        return "Response{" +
                "type=" + type +
                ", data=" + data +
                '}';
    }

    public static class Builder {
        private final Response response = new Response();

        public Builder setType(ResponseType type) {
            response.type = type;
            return this;
        }

        public Builder setData(Object data) {
            response.data = data;
            return this;
        }

        public Response build() {
            return response;
        }
    }
}
