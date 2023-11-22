import { logger } from "../core/logger";
import { baseURL, webSocketURL } from "./consts";
import { Response } from "./types";
import axios from "axios";

const log = logger("API");

export const resourceURL = (resource: string) =>
  `http://${baseURL}/api/${resource}`;

export const imageUrl = (image: string) => `http://${baseURL}/uploads/${image}`;

export const downloadImageUrl = (image: string) =>
  `${imageUrl(image)}/download`;

const withLogs = <T>(
  promise: Promise<Response<T>>,
  ...args: string[]
): Promise<T> => {
  log(...args, `- started`);
  return promise
    .then((res) => {
      log(...args, `- succeeded`);
      return Promise.resolve(res.data);
    })
    .catch((err) => {
      log(...args, `- failed - ${err}`);
      return Promise.reject(err);
    });
};

export const get = <T>(path: string): Promise<T> =>
  withLogs<T>(axios.get(path, { method: "GET" }), `GET - ${path}`);

export const post = <T>(path: string, body: any): Promise<T> =>
  withLogs<T>(axios.post(path, body), `POST - ${path} -`, body);

export const put = <T>(path: string, body: any): Promise<T> =>
  withLogs<T>(axios.put(path, body), `PUT - ${path} -`, body);

export const del = <T>(path: string): Promise<T> =>
  withLogs<T>(axios.delete(path), `DELETE - ${path}`);

type Message<T extends any> = {
  event: string;
  payload: T;
};

export const newWebSocket = <T>(onMessage: (data: Message<T>) => void) => {
  const ws = new WebSocket(`${webSocketURL}`);
  ws.onopen = () => {
    log("web socket - on open");
  };
  ws.onclose = () => {
    log("web socket - on close");
  };
  ws.onerror = (error) => {
    log("web socket - on error -", error);
  };
  ws.onmessage = (message) => {
    const data = JSON.parse(message.data);
    log("web socket - on message -", data);
    onMessage(data);
  };
  return () => {
    ws.close();
  };
};
