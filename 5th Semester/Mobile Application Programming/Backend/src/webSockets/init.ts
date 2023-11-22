import WebSocket from "ws";
import { userFromJWT } from "../auth/utils";

export default (wss: WebSocket.Server) => {
  wss.on("connection", (ws: WebSocket) => {
    ws.on("message", (message: string) => {
      const {
        type,
        payload: { token },
      } = JSON.parse(message);
      if (type !== "authorization") {
        ws.close();
        return;
      }
      try {
        (ws as any).user = userFromJWT(token);
      } catch (err) {
        ws.close();
      }
    });
  });
};
