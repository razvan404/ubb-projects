import WebSocket from "ws";
import { wsServer } from "..";

export const userFromWebSocket = (ws: WebSocket) => {
  const user = (ws as any).user;
  return user;
};

export const sendToAll = (event: any, payload: any) => {
  wsServer.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(JSON.stringify({ event, payload }));
    }
  });
};

export const sendToUser = (userId: string | null, event: any, payload: any) => {
  if (!userId) {
    return;
  }
  wsServer.clients.forEach((client) => {
    if (
      client.readyState === WebSocket.OPEN &&
      userFromWebSocket(client)?.id === userId
    ) {
      console.log(
        "User found... sending message: ",
        JSON.stringify({ event, payload })
      );
      client.send(JSON.stringify({ event, payload }));
    }
  });
};
