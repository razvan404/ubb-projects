export type User = {
  id?: string;
  username?: string;
  email?: string;
  password?: string;
  profileImage?: string;
};

export type AuthenticationResponse = {
  token: string;
  user: User;
};
