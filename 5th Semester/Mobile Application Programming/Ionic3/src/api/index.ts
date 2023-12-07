import { authConfig } from "../auth";
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

export const get = <T>(path: string, authToken?: string): Promise<T> =>
  withLogs<T>(axios.get(path, authConfig(authToken)), `GET - ${path}`);

export const post = <T>(
  path: string,
  body: any,
  authToken?: string
): Promise<T> =>
  withLogs<T>(
    axios.post(path, body, authConfig(authToken)),
    `POST - ${path} -`,
    body
  );

export const put = <T>(
  path: string,
  body: any,
  authToken?: string
): Promise<T> =>
  withLogs<T>(
    axios.put(path, body, authConfig(authToken)),
    `PUT - ${path} -`,
    body
  );

export const del = <T>(path: string, authToken?: string): Promise<T> =>
  withLogs<T>(axios.delete(path, authConfig(authToken)), `DELETE - ${path}`);

export type APIRequest = {
  type: "GET" | "POST" | "PUT" | "DELETE";
  resource: string;
  payload?: any;
};

export const sendRequest = <T>(
  request: APIRequest,
  authToken?: string
): Promise<T> => {
  switch (request.type) {
    case "GET":
      return get(resourceURL(request.resource), authToken);
    case "POST":
      return post(resourceURL(request.resource), request.payload, authToken);
    case "PUT":
      return put(resourceURL(request.resource), request.payload, authToken);
    case "DELETE":
      return del(resourceURL(request.resource), authToken);
  }
};

type Message<T extends any> = {
  event: string;
  payload: T;
};

export const newWebSocket = <T>(
  onMessage: (data: Message<T>) => void,
  token?: string
) => {
  const ws = new WebSocket(`${webSocketURL}`);
  ws.onopen = () => {
    log("web socket - on open");
    if (token) {
      ws.send(JSON.stringify({ type: "authorization", payload: { token } }));
    }
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
