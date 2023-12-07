import * as React from "react";
import { Redirect, Route } from "react-router-dom";
import { useAuth } from "../auth";
import { RouteProps } from "./types";

const PrivateRoute = ({ component, ...rest }: RouteProps) => {
  const { currentUser } = useAuth();
  const [shouldRedirect, setShouldRedirect] = React.useState<boolean>(false);
  setTimeout(() => {
    setShouldRedirect(true);
  }, 200);
  return (
    <Route {...rest} component={currentUser && component}>
      {!currentUser && shouldRedirect && <Redirect to="/login" />}
    </Route>
  );
};

export default PrivateRoute;
