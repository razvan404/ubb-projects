import * as React from "react";
import PictureAPI from "./pictureApi";
import { Picture } from "./types";
import { logger } from "../../core/logger";
import { newWebSocket } from "../../api";

const log = logger("UsePictures");

type PictureState = {
  pictures: Picture[];
  loading: boolean;
  error: string;
};

const initialState: PictureState = {
  pictures: [],
  loading: false,
  error: "",
};

type ActionPicture = {
  type: string;
  payload?: any;
};

const PICTURES_LOADING = "PICTURES_LOADING";
const PICTURES_FAILED = "PICTURES_FAILED";
const PICTURES_SUCCEEDED = "PICTURES_SUCCEEDED";

const pictureReducer = (
  state: PictureState = initialState,
  action: ActionPicture
): PictureState => {
  switch (action.type) {
    case PICTURES_LOADING:
      return { ...state, loading: true, error: "" };
    case PICTURES_FAILED:
      return { ...state, loading: false, error: action.payload };
    case PICTURES_SUCCEEDED:
      return { ...state, loading: false, pictures: action.payload };
    default:
      return state;
  }
};

const usePictures = () => {
  const [state, dispatch] = React.useReducer(pictureReducer, initialState);
  const { pictures, loading, error } = state;

  React.useEffect(() => {
    wsEffect();
  }, []);

  React.useEffect(() => {
    findPictures();
  }, []);

  const findPictures = React.useCallback(async () => {
    try {
      dispatch({ type: PICTURES_LOADING });
      log("getPictures - started");
      const fetchedPictures = await PictureAPI.findAll();
      dispatch({ type: PICTURES_SUCCEEDED, payload: fetchedPictures });
      log("getPictures - succeeded");
    } catch (err: any) {
      dispatch({ type: PICTURES_FAILED, payload: err.message });
      log("getPictures - failed -", err.message);
    }
  }, [pictures]);

  const savePicture = React.useCallback(
    async (picture: Picture) => {
      try {
        dispatch({ type: PICTURES_LOADING });
        log("savePicture - started");
        const isNewPicture = !picture.id;
        const fetchedPicture = await PictureAPI.save(picture);
        if (isNewPicture) {
          dispatch({
            type: PICTURES_SUCCEEDED,
            payload: [...pictures, fetchedPicture],
          });
        } else {
          dispatch({
            type: PICTURES_SUCCEEDED,
            payload: pictures.map((p) =>
              p.id === fetchedPicture.id ? fetchedPicture : p
            ),
          });
        }
      } catch (err: any) {
        dispatch({ type: PICTURES_FAILED, payload: err.message });
        log("savePicture - failed -", err.message);
      }
    },
    [pictures]
  );

  const wsEffect = () => {
    let canceled = false;
    log("wsEffect - connecting");
    const closeWebSocket = newWebSocket<Picture>((message) => {
      const { event, payload } = message;
      log("wsEffect - pictures -", event);
      if (event == "PICTURE_SAVED") {
        dispatch({ type: PICTURES_SUCCEEDED, payload: [...pictures, payload] });
      }
    });
  };

  return {
    pictures,
    loading,
    error,
    savePicture,
  };
};

export default usePictures;
