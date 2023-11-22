import galleryRoute from "../gallery/route";
import pictureRoute, {
  createPictureRoute,
  editPictureRoute,
} from "../picture/route";
import loginRoute from "../login/route";
import userPicturesRoute from "../userPictures/route";
import DefaultRoute from "./defaultRoute";
import PrivateRoute from "./privateRoute";
import { RouteProps } from "./types";

export const routes: readonly RouteProps[] = [
  galleryRoute,
  userPicturesRoute,
  editPictureRoute,
  pictureRoute,
  createPictureRoute,
  loginRoute,
] as const;
export { DefaultRoute, PrivateRoute };
