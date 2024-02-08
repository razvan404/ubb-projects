import * as API from "../api";
import logger from "../core/logger";
import { Item } from "./types";

const log = logger("Items API");

export default {
  save: async (item: Item): Promise<Item> => {
    return Promise.reject({ message: "Not implemented" });
  },
  update: async (item: Item): Promise<Item> => {
    return Promise.reject({ message: "Not implemented" });
  },
  patch: async (item: Item) => {
    return API.patch(API.resourceURL(`asset/${item.id}`), {
      takenBy: item.takenBy,
      desiredBy: item.desiredBy,
    });
  },
};
