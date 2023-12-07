import * as React from "react";
import * as Recoil from "recoil";
import UserAPI from "../models/user/userApi";
import AuthAPI from "./authApi";
import { User } from "../models/user/types";
import { logger } from "../core/logger";
import usePreferences from "../core/usePreferences";

const log = logger("UseAuth");

type AuthState = {
  currentUser?: User;
  token?: string;
  loading: boolean;
  error?: string;
};

const initialState: AuthState = {
  token: undefined,
  loading: false,
};

const authStateAtom = Recoil.atom<AuthState>({
  key: "authState",
  default: initialState,
});

const useAuth = () => {
  const [state, setState] = Recoil.useRecoilState(authStateAtom);
  const { currentUser, token, loading, error } = state;
  const { get, set, remove } = usePreferences();

  const deleteUser = React.useCallback(async () => {
    log("deleteUser - started");
    if (!currentUser?.id) {
      log("deleteUser - failed - No user to delete");
      return;
    }
    try {
      setState((prev) => ({ ...prev, loading: true }));
      await UserAPI.delete(currentUser.id);
      setState({ currentUser: undefined, token: undefined, loading: false });
      log("deleteUser - succeeded");
    } catch (err: any) {
      setState((prev) => ({ ...prev, loading: false, error: err.message }));
      log("deleteUser - failed -", err.message);
    }
  }, []);

  const login = React.useCallback(
    async (usernameOrEmail: string, password: string) => {
      try {
        setState((prev) => ({ ...prev, loading: true }));
        const resp = await AuthAPI.login(usernameOrEmail, password);
        await set("authToken", resp.token);
        setState({ currentUser: resp.user, token: resp.token, loading: false });
        log("login - succeeded");
      } catch (err: any) {
        setState((prev) => ({ ...prev, loading: false, error: err.message }));
        log("login - failed -", err.message);
      }
    },
    [set]
  );

  const register = React.useCallback(
    async (username: string, email: string, password: string) => {
      try {
        setState((prev) => ({ ...prev, loading: true }));
        const resp = await AuthAPI.register(username, email, password);
        await set("authToken", resp.token);
        setState({ currentUser: resp.user, token: resp.token, loading: false });
        log("register - succeeded");
      } catch (err: any) {
        setState((prev) => ({ ...prev, loading: false, error: err.message }));
        log("register - failed -", err.message);
      }
    },
    [set]
  );

  const logout = React.useCallback(async () => {
    setState({ currentUser: undefined, token: undefined, loading: false });
    remove("authToken");
  }, [remove]);

  const me = React.useCallback(async () => {
    if (token && !currentUser && !loading) {
      log("useEffect - token found");

      setState((prev) => ({ ...prev, loading: true }));
      AuthAPI.me(token)
        .then((user) => {
          setState((prev) => ({ ...prev, currentUser: user, loading: false }));
          log("useEffect - token found - succeeded");
        })
        .catch((err) => {
          setState({
            token: undefined,
            loading: false,
          });
          log("useEffect - token found - failed -", err.message);
        });
    }
  }, [token, currentUser, loading]);

  React.useEffect(() => {
    get("authToken").then((foundToken) => {
      if (foundToken) {
        setState((prev) => ({ ...prev, token: foundToken }));
      }
    });
  }, [get]);

  React.useEffect(() => {
    me();
  }, [me]);

  const setError = React.useCallback((error?: string) => {
    setState((prev) => ({ ...prev, error }));
  }, []);

  return {
    currentUser,
    token,
    loading,
    error,
    setError,
    deleteUser,
    login,
    register,
    logout,
  };
};

export default useAuth;
