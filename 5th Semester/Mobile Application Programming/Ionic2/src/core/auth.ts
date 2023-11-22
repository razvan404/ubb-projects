export const authConfig = (token?: string) => {
  if (!token) {
    return undefined;
  }
  return {
    headers: {
      Authorization: `Bearer ${token}`,
    },
  };
};
