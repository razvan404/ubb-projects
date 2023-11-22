import { RouteProps } from "../routes/types";
import PicturePage, { EditPicturePage, SavePicturePage } from "./page";

const pictureRoute = {
  path: "/pictures/:id",
  component: PicturePage,
} as RouteProps;

export default pictureRoute;

const createPictureRoute = {
  path: "/pictures/create",
  component: SavePicturePage,
} as RouteProps;

const editPictureRoute = {
  path: "/pictures/:id/edit",
  component: EditPicturePage,
} as RouteProps;

export { createPictureRoute, editPictureRoute };
