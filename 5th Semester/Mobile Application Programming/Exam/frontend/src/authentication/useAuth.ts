import * as React from "react";
import * as Recoil from "recoil";
import logger from "../core/logger";
import usePreferences from "../core/usePreferences";

const log = logger("UseAuth");

type AuthState = {
  currentUser?: string;
  loading: boolean;
  error?: string;
};

const initialState: AuthState = {
  loading: false,
};

const authStateAtom = Recoil.atom<AuthState>({
  key: "authState",
  default: initialState,
});

const useAuth = () => {
  const [state, setState] = Recoil.useRecoilState(authStateAtom);
  const { currentUser, loading, error } = state;
  const { get, set, remove } = usePreferences();

  const login = React.useCallback(
    async (username: string) => {
      try {
        await set("user", username);
        setState((prev) => ({ ...prev, currentUser: username }));
        log("login - succeeded");
      } catch (err: any) {
        setState((prev) => ({ ...prev, loading: false, error: err.message }));
        log("login - failed -", err.message);
      }
    },
    [set]
  );

  const logout = React.useCallback(async () => {
    setState({ currentUser: undefined, loading: false });
    remove("user");
  }, [remove]);

  React.useEffect(() => {
    get("user").then((user) => {
      if (user) {
        setState((prev) => ({ ...prev, currentUser: user }));
      }
    });
  }, [get]);

  const setError = React.useCallback((error?: string) => {
    setState((prev) => ({ ...prev, error }));
  }, []);

  return {
    currentUser,
    loading,
    error,
    setError,
    login,
    logout,
  };
};

export default useAuth;
