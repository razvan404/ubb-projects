import { RouteProps } from "../routing/types";
import PicturePage, { EditPicturePage, SavePicturePage } from "./picturePage";

const pictureRoute = {
  path: "/pictures/:id",
  exact: true,
  component: PicturePage,
} as RouteProps;

export default pictureRoute;

const createPictureRoute = {
  path: "/pictures/create",
  exact: true,
  component: SavePicturePage,
  isPrivate: true,
} as RouteProps;

const editPictureRoute = {
  path: "/pictures/:id/edit",
  exact: true,
  component: EditPicturePage,
  isPrivate: true,
} as RouteProps;

export { createPictureRoute, editPictureRoute };
