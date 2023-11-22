import * as API from "../../api";
import { User } from "./types";
import { logger } from "../../core/logger";

const log = logger("UsersAPI");
const resourceURL = API.resourceURL("users");

export default {
  findById: async (id: string) => {
    try {
      log("findById - started");
      const user = await API.get<User>(`${resourceURL}/${id}`);
      log("findById - succeeded");
      return user;
    } catch (err: any) {
      log("findById - failed -", err.message);
      throw err;
    }
  },
  save: async (user: User) => {
    try {
      log("save - started");
      if (user.id) {
        user = await API.put<User>(`${resourceURL}/${user.id}`, user);
      } else {
        user = await API.post<User>(resourceURL, user);
      }
      log("saveUser - succeeded");
      return user;
    } catch (err: any) {
      log("saveUser - failed -", err.message);
      throw err;
    }
  },
  delete: async (id: string) => {
    try {
      log("delete - started");
      await API.del<User>(`${resourceURL}/${id}`);
      log("delete - succeeded");
    } catch (err: any) {
      log("delete - failed -", err.message);
      throw err;
    }
  },
};
