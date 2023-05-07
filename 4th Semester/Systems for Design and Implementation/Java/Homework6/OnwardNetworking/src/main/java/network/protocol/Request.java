package network.protocol;

import java.io.Serializable;

public class Request implements Serializable {
    private RequestType type;
    private Object data;

    private Request() {}

    public RequestType getType() {
        return type;
    }

    public Object getData() {
        return data;
    }

    @Override
    public String toString() {
        return "Request{" +
                "type=" + type +
                ", data=" + data +
                '}';
    }

    public static class Builder {
        private final Request request = new Request();
        public Builder setType(RequestType type) {
            request.type = type;
            return this;
        }

        public Builder setData(Object data) {
            request.data = data;
            return this;
        }

        public Request build() {
            return request;
        }
    }
}
