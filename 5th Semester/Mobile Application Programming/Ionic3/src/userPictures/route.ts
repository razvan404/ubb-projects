import { RouteProps } from "../routing/types";
import UserPicturesPage from "./userPicturesPage";

export default {
  path: "/pictures",
  exact: true,
  component: UserPicturesPage,
} as RouteProps;
