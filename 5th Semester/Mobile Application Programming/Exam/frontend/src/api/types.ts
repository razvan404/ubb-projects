export type Response<T> = {
  data: T;
  status: number;
};

export type APIRequest = {
  type: "GET" | "POST" | "PUT" | "DELETE";
  resource: string;
  payload?: any;
};
