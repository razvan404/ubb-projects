package api.networking.observer;

import api.networking.response.Response;
import api.networking.response.ResponseType;
import api.services.notification.Notification;
import api.services.observer.Observer;
import api.utils.JsonParser;
import lombok.AllArgsConstructor;
import lombok.EqualsAndHashCode;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;

import java.io.IOException;

@AllArgsConstructor
@EqualsAndHashCode
public class WebSocketObserver implements Observer {
    private final WebSocketSession session;

    public void notify(Notification notification) {
        try {
            String msg = JsonParser.toJson(new Response(ResponseType.UPDATE, notification));
            System.out.println("Sending notification... " + msg);
            if (msg != null) {
                session.sendMessage(new TextMessage(msg));
            }
        } catch (IOException ex) {
            System.err.println(ex.getMessage());
        }
    }
}
