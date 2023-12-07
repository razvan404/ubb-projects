export type Picture = {
  id: string;
  createdAt: Date;
  title: string;
  description: string;
  image: string;
  authorId: string | null;
  typeId: number;
  geoloc: {
    lat: number;
    lng: number;
  } | null;
};

export type PictureMini = {
  id: string;
  title: string;
  image: string;
  author: {
    username: string;
    profileImage: string | null;
  } | null;
};

export type PictureToSave = {
  title: string;
  description: string;
  authorId: string | null;
  typeId: number;
  rawImage: {
    dataUrl: string;
    format: string;
  };
  geoloc: {
    lat: number;
    lng: number;
  } | null;
};
