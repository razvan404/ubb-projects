import { db } from "../../utils/database";
import { PictureToSave, type Picture, type PictureMini } from "./types";
import uploadsService from "../../raw/uploads/service";
import * as webSockets from "../../webSockets";

export default {
  findAll: async (
    queryFilters: any,
    skip?: number,
    take?: number
  ): Promise<PictureMini[]> => {
    return await db.picture.findMany({
      where: { ...queryFilters },
      select: {
        id: true,
        title: true,
        image: true,
        author: { select: { username: true, profileImage: true } },
      },
      orderBy: { createdAt: "asc" },
      skip: skip,
      take: take,
    });
  },
  findById: async (id: string): Promise<Picture | null> => {
    return await db.picture.findUnique({
      where: { id },
      select: {
        id: true,
        createdAt: true,
        title: true,
        description: true,
        image: true,
        authorId: true,
        typeId: true,
      },
    });
  },
  create: async (picture: PictureToSave): Promise<PictureMini> => {
    const image = await uploadsService.save(
      picture.rawImage.dataUrl,
      uploadsService.generatePath(picture.rawImage.format)
    );
    const savedPicture = await db.picture.create({
      data: {
        title: picture.title,
        description: picture.description,
        image: image,
        authorId: picture.authorId,
        typeId: picture.typeId,
      },
      select: {
        id: true,
        title: true,
        image: true,
        author: { select: { username: true, profileImage: true } },
      },
    });
    if (savedPicture) {
      webSockets.sendToUser(picture.authorId, "PICTURE_SAVED", savedPicture);
    }
    return savedPicture;
  },
  update: async (picture: Picture): Promise<PictureMini> => {
    const updatedPicture = await db.picture.update({
      where: { id: picture.id },
      data: {
        title: picture.title,
        description: picture.description,
        image: picture.image,
        typeId: picture.typeId,
      },
      select: {
        id: true,
        title: true,
        image: true,
        author: { select: { username: true, profileImage: true } },
      },
    });
    if (updatedPicture) {
      webSockets.sendToUser(
        picture.authorId,
        "PICTURE_UPDATED",
        updatedPicture
      );
    }
    return updatedPicture;
  },
  delete: async (id: string, userId: string): Promise<void> => {
    const picture = await db.picture.findUnique({
      where: { id },
      select: { authorId: true },
    });
    if (picture?.authorId !== userId) {
      throw new Error("You can only delete your own pictures");
    }
    await db.picture.delete({ where: { id } });
    webSockets.sendToUser(userId, "PICTURE_DELETED", { id: id });
  },
};
