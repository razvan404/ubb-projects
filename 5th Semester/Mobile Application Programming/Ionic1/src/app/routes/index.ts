import galleryRoute from "../gallery/route";
import pictureRoute, {
  createPictureRoute,
  editPictureRoute,
} from "../picture/route";
import DefaultRoute from "./defaultRoute";
import NotFoundRoute from "./notFoundRoute";
import { RouteProps } from "./types";

export const routes: readonly RouteProps[] = [
  galleryRoute,
  pictureRoute,
  createPictureRoute,
  editPictureRoute,
] as const;
export { DefaultRoute, NotFoundRoute };
