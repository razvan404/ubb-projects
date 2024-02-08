import { User } from "./types";

export default {
  login: (
    username: string,
    password: string
  ): Promise<{ user: User; token: string }> => {
    return Promise.reject({ message: "Not implemented" });
  },
  register: (
    username: string,
    password: string
  ): Promise<{ user: User; token: string }> => {
    return Promise.reject({ message: "Not implemented" });
  },
};
