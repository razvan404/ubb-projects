export type RouteProps = {
  path: string;
  exact?: boolean;
  isPrivate?: boolean;
  component: React.ComponentType<any>;
};
