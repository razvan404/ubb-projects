import * as React from "react";
import UserAPI from "./userApi";
import { User } from "./types";
import { logger } from "../../core/logger";

const log = logger("UseAuth");

type UserState = {
  currentUser?: User;
  loading: boolean;
  error: string;
};

const initialState: UserState = {
  currentUser: undefined,
  loading: false,
  error: "",
};

type ActionUser = {
  type: string;
  payload?: any;
};

const USERS_LOADING = "USERS_LOADING";
const USERS_FAILED = "USERS_FAILED";
const USERS_SUCCEEDED = "USERS_SUCCEEDED";
const USERS_LOGIN = "USER_LOGIN";
const USERS_LOGOUT = "USER_LOGOUT";

const userReducer = (
  state: UserState = initialState,
  action: ActionUser
): UserState => {
  switch (action.type) {
    case USERS_LOADING:
      return { ...state, loading: true, error: "" };
    case USERS_FAILED:
      return { ...state, loading: false, error: action.payload };
    case USERS_SUCCEEDED:
      return {
        ...state,
        loading: false,
        currentUser: action.payload,
      };
    case USERS_LOGIN:
      return {
        ...state,
        loading: false,
        currentUser: action.payload,
      };
    case USERS_LOGOUT:
      return {
        ...state,
        loading: false,
        currentUser: undefined,
      };
    default:
      return state;
  }
};

const useAuth = () => {
  const [state, dispatch] = React.useReducer(userReducer, initialState);
  const { currentUser, loading, error } = state;

  React.useEffect(() => {
    const fetchUser = async () => {
      try {
        dispatch({ type: USERS_LOADING });
        log("fetchUser - started");
        const user = await UserAPI.findById(
          "2ccc49e7-7fcf-43af-8dd9-80601103edf8"
        );
        dispatch({ type: USERS_SUCCEEDED, payload: user });
        log("fetchUser - succeeded");
      } catch (err: any) {
        dispatch({ type: USERS_FAILED, payload: err.message });
        log("fetchUser - failed -", err.message);
      }
    };
    fetchUser();
  }, []);

  const saveUser = React.useCallback(async (user: User) => {
    try {
      dispatch({ type: USERS_LOADING });
      log("saveUser - started");
      user = await UserAPI.save(user);
      dispatch({ type: USERS_SUCCEEDED, payload: user });
      log("saveUser - succeeded");
    } catch (err: any) {
      dispatch({ type: USERS_FAILED, payload: err.message });
      log("saveUser - failed -", err.message);
    }
  }, []);

  const deleteUser = React.useCallback(async () => {
    dispatch({ type: USERS_LOADING });
    log("deleteUser - started");
    if (!currentUser?.id) {
      dispatch({ type: USERS_FAILED, payload: "No user to delete" });
      log("deleteUser - failed - No user to delete");
      return;
    }
    try {
      await UserAPI.delete(currentUser.id);
      dispatch({ type: USERS_SUCCEEDED });
      log("deleteUser - succeeded");
    } catch (err: any) {
      dispatch({ type: USERS_FAILED, payload: err.message });
      log("deleteUser - failed -", err.message);
    }
  }, []);

  const login = React.useCallback(async (email: string, password: string) => {},
  []);

  const logout = React.useCallback(async () => {}, []);

  return {
    currentUser,
    loading,
    error,
    saveUser,
    deleteUser,
    login,
    logout,
  };
};

export default useAuth;
