import * as API from "../../api";
import { Picture, PictureToSave } from "./types";
import { logger } from "../../core/logger";

const log = logger("PicturesAPI");
const resourceUrl = API.resourceURL("pictures");

const fixPicture = (picture: any): Picture => {
  return {
    ...picture,
    createdAt: new Date(picture.createdAt),
  };
};

const filtersToQueryString = (filters?: { [key: string]: any }) => {
  if (!filters) {
    return "";
  }
  return Object.entries(filters)
    .filter(([_, value]) => value !== undefined && value !== "")
    .map(([key, value]) => `${key}=${value}`)
    .join("&");
};

export default {
  findAll: async (filters?: { [key: string]: any }) => {
    try {
      log("findAll - started");
      const queryString = filtersToQueryString(filters);
      const pictures = await API.get<Picture[]>(
        `${resourceUrl}${queryString && "?" + queryString}`
      );

      log("findAll - succeeded");
      return pictures.map(fixPicture);
    } catch (err: any) {
      log("findAll - failed -", err.message);
      throw err;
    }
  },
  findFromAuthorId: async (authorId: string) => {
    try {
      log("findFromAuthorId - started");
      const pictures = await API.get<Picture[]>(
        `${resourceUrl}?authorId=${authorId}`
      );
      log("findFromAuthorId - succeeded");
      return pictures.map(fixPicture);
    } catch (err: any) {
      log("findFromAuthorId - failed -", err.message);
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
  save: async (picture: PictureToSave, token?: string) => {
    try {
      log("savePicture - started");
      if (!token) {
        throw new Error("No token");
      }
      if (!picture.id) {
        const addedPicture = await API.post<Picture>(
          resourceUrl,
          picture,
          token
        );
        log("savePicture - succeeded");
        return fixPicture(addedPicture);
      } else {
        const updatedPicture = await API.put<Picture>(
          `${resourceUrl}/${picture.id}`,
          picture,
          token
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
