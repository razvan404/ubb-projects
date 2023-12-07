import * as React from "react";
import * as Recoil from "recoil";
import * as API from "../../api";
import { PictureType } from "./types";
import { logger } from "../../core/logger";

const log = logger("UsePictureTypes");

type PictureTypeState = {
  pictureTypes: { [id: number]: PictureType };
  loaded: boolean;
  error?: string;
};

const initialState: PictureTypeState = {
  pictureTypes: {},
  loaded: false,
};

const pictureTypeStateAtom = Recoil.atom<PictureTypeState>({
  key: "pictureTypeState",
  default: initialState,
});

const usePictureTypes = () => {
  const [state, setState] = Recoil.useRecoilState(pictureTypeStateAtom);
  const { pictureTypes, loaded, error } = state;
  const resourceURL = API.resourceURL("pictureTypes");

  const getPictureTypes = React.useCallback(async () => {
    try {
      log("getPictureTypes started");
      setState((prev) => ({ ...prev, loaded: false }));
      const pictureTypes = await API.get<PictureType[]>(resourceURL);
      setState((prev) => ({
        ...prev,
        pictureTypes: Object.fromEntries(
          pictureTypes.map((type: PictureType) => [type.id, type])
        ),
        loaded: true,
        error: undefined,
      }));
      log("getPictureTypes succeeded");
    } catch (err: any) {
      setState((prev) => ({ ...prev, error: err.message, loaded: true }));
      log("getPictureTypes failed -", err.message);
    }
  }, []);

  React.useEffect(() => {
    if (Object.keys(pictureTypes).length === 0) {
      getPictureTypes();
    }
  }, [pictureTypes]);

  const setError = React.useCallback((error?: string) => {
    setState((prev) => ({ ...prev, error }));
  }, []);

  return { pictureTypes, loaded, error, setError };
};

export default usePictureTypes;
