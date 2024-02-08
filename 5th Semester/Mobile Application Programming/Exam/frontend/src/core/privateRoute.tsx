import * as React from "react";
import { Redirect, Route } from "react-router-dom";
import useAuth from "../authentication/useAuth";

type Props = {
  children: React.ReactNode;
  exact: boolean;
  path: string;
};

const PrivateRoute = ({ children, ...rest }: Props) => {
  const { currentUser } = useAuth();
  const [shouldRedirect, setShouldRedirect] = React.useState<boolean>(false);
  setTimeout(() => {
    setShouldRedirect(true);
  }, 200);
  return (
    <Route {...rest}>
      {!currentUser && shouldRedirect ? <Redirect to="/login" /> : children}
    </Route>
  );
};

export default PrivateRoute;
