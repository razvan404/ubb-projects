import { Redirect, Route } from "react-router-dom";

export default () => (
  <Route exact path="/">
    <Redirect to="/gallery" />
  </Route>
);
