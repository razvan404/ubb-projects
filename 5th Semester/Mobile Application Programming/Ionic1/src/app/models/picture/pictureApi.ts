import * as API from "../../api";
import { Picture, PictureToSave } from "./types";
import { logger } from "../../core/logger";

const log = logger("PicturesAPI");
const resourceUrl = API.resourceURL("pictures");

const fixPicture = (picture: Picture) => {
  return {
    ...picture,
    // @ts-ignore - No overload matches this call.
    createdAt: new Date(picture.createdAt),
  };
};

export default {
  findAll: async () => {
    try {
      log("findAll - started");
      const pictures = await API.get<Picture[]>(resourceUrl);
      pictures;
      log("findAll - succeeded");
      return pictures.map(fixPicture);
    } catch (err: any) {
      log("findAll - failed -", err.message);
      throw err;
    }
  },
  findById: async (id: string) => {
    try {
      log("findPictureById - started");
      const picture = await API.get<Picture>(`${resourceUrl}/${id}`);
      log("findPictureById - succeeded");
      return fixPicture(picture);
    } catch (err: any) {
      log("findPictureById - failed -", err.message);
      throw err;
    }
  },
  save: async (picture: PictureToSave) => {
    try {
      log("savePicture - started");
      if (!picture.id) {
        const addedPicture = await API.post<Picture>(resourceUrl, picture);
        log("savePicture - succeeded");
        return fixPicture(addedPicture);
      } else {
        const updatedPicture = await API.put<Picture>(
          `${resourceUrl}/${picture.id}`,
          picture
        );
        log("savePicture - succeeded");
        return fixPicture(updatedPicture);
      }
    } catch (err: any) {
      log("savePicture - failed -", err.message);
      throw err;
    }
  },
  delete: async (id: string) => {
    try {
      log("deletePicture - started");
      await API.del<Picture>(`${resourceUrl}/${id}`);
      log("deletePicture - succeeded");
    } catch (err: any) {
      log("deletePicture - failed -", err.message);
      throw err;
    }
  },
} as const;
