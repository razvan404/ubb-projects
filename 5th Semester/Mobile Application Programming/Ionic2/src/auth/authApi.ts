import * as API from "../api";
import { AuthenticationResponse, User } from "../models/user/types";
import { logger } from "../core/logger";

const log = logger("AuthAPI");
const resourceURL = API.resourceURL("auth");

export default {
  login: async (usernameOrEmail: string, password: string) => {
    try {
      log("login - started");
      const response = await API.post<AuthenticationResponse>(
        `${resourceURL}/login`,
        {
          usernameOrEmail,
          password,
        }
      );
      log("login - succeeded");
      return response;
    } catch (err: any) {
      log("login - failed -", err.message);
      throw err;
    }
  },
  register: async (username: string, email: string, password: string) => {
    try {
      log("register - started");
      const response = await API.post<AuthenticationResponse>(
        `${resourceURL}/register`,
        {
          username,
          email,
          password,
        }
      );
      log("register - succeeded");
      return response;
    } catch (err: any) {
      log("register - failed -", err.message);
      throw err;
    }
  },
  me: async (token: string) => {
    try {
      log("me - started");
      const response = await API.get<User>(`${resourceURL}/me`, token);
      log("me - succeeded");
      return response;
    } catch (err: any) {
      log("me - failed -", err.message);
      throw err;
    }
  },
};
