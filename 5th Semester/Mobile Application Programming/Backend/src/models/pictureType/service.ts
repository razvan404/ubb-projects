import { db } from "../../utils/database";
import { type PictureType } from "./types";

export default {
  findAll: async (): Promise<PictureType[]> => {
    return await db.pictureType.findMany({
      select: {
        id: true,
        name: true,
      },
    });
  },
};
