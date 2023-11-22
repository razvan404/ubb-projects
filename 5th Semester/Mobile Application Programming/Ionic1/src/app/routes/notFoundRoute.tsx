import { Redirect, Route } from "react-router-dom";
import NotFound from "../extra/notFound";

const NotFoundRoute = () => (
  <>
    <Route path="*">
      <NotFound />
    </Route>
  </>
);

export default NotFoundRoute;
