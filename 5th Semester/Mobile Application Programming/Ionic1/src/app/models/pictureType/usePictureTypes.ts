import * as React from "react";
import * as API from "../../api";
import { PictureType } from "./types";
import { logger } from "../../core/logger";

const log = logger("usePictureTypes");

type PictureTypeState = {
  pictureTypes: { [id: number]: PictureType };
  loaded: boolean;
  error: string;
};

const initialState: PictureTypeState = {
  pictureTypes: {},
  loaded: false,
  error: "",
};

type ActionPictureType = {
  type: string;
  payload?: any;
};

const PICTURE_TYPES_LOADING = "PICTURE_TYPES_LOADING";
const PICTURE_TYPES_FAILED = "PICTURE_TYPES_FAILED";
const PICTURE_TYPES_SUCCEEDED = "PICTURE_TYPES_SUCCEEDED";

const pictureTypeReducer = (
  state: PictureTypeState = initialState,
  action: ActionPictureType
): PictureTypeState => {
  switch (action.type) {
    case PICTURE_TYPES_LOADING:
      return { ...state, loaded: false, error: "" };
    case PICTURE_TYPES_FAILED:
      return { ...state, loaded: true, error: action.payload };
    case PICTURE_TYPES_SUCCEEDED:
      return {
        ...state,
        loaded: true,
        pictureTypes: Object.fromEntries(
          action.payload?.map((type: PictureType) => [type.id, type])
        ),
      };
    default:
      return state;
  }
};

const usePictureTypes = () => {
  const [state, dispatch] = React.useReducer(pictureTypeReducer, initialState);
  const { pictureTypes, loaded, error } = state;
  const resourceURL = API.resourceURL("pictureTypes");

  React.useEffect(() => {
    getPictureTypes();
  }, []);

  const getPictureTypes = React.useCallback(async () => {
    try {
      log("getPictureTypes started");
      dispatch({ type: PICTURE_TYPES_LOADING });
      const pictureTypes = await API.get<PictureType[]>(resourceURL);
      dispatch({ type: PICTURE_TYPES_SUCCEEDED, payload: pictureTypes });
      log("getPictureTypes succeeded");
    } catch (err: any) {
      dispatch({ type: PICTURE_TYPES_FAILED, payload: err.message });
      log("getPictureTypes failed -", err.message);
    }
  }, []);

  return { pictureTypes, loaded, error };
};

export default usePictureTypes;
