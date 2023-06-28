package api.services.notification;

import lombok.AllArgsConstructor;
import lombok.Data;

import java.io.Serializable;

@AllArgsConstructor
@Data
public class Notification implements Serializable {
    NotificationType type;
    Object data;
}
