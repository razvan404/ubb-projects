import { User } from "../user/types";
import { PictureType } from "../pictureType/types";
import { Photo } from "@capacitor/camera";

export type PictureToSave = {
  id?: string;
  title?: string;
  image?: string;
  rawImage?: Photo;
  description?: string;
  authorId?: string;
  typeId?: number;
};

export type Picture = {
  id?: string;
  createdAt?: Date;
  title: string;
  description?: string;
  image: string;
  author?: User;
  authorId?: string;
  type?: PictureType;
  typeId?: number;
};
