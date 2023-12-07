import * as React from "react";
import * as Recoil from "recoil";
import PictureAPI from "./pictureApi";
import { useNetwork } from "../../core/useNetwork";
import { APIRequest, newWebSocket, sendRequest } from "../../api";
import { useAuth } from "../../auth";
import { Picture, PictureToSave } from "./types";
import { logger } from "../../core/logger";
import usePreferences from "../../core/usePreferences";

const log = logger("UseOptimisticPictures");

type OptimisticPicture = (Picture | PictureToSave) & {
  isPending?: boolean;
};

type OptimisticPictureState = {
  optimisticPictures: OptimisticPicture[];
  pendingRequests: APIRequest[];
};

const initialState: OptimisticPictureState = {
  optimisticPictures: [],
  pendingRequests: [],
};

const optimisticPicturesStateAtom = Recoil.atom<OptimisticPictureState>({
  key: "optimisticPicturesState",
  default: initialState,
});

const saveApiRequest = (picture: PictureToSave): APIRequest => ({
  type: picture.id ? "PUT" : "POST",
  resource: `pictures${picture.id ? "/" + picture.id : ""}`,
  payload: picture,
});

const useOptimisticPictures = () => {
  const { currentUser, token } = useAuth();
  const { networkStatus } = useNetwork();
  const [state, setState] = Recoil.useRecoilState(optimisticPicturesStateAtom);
  const { optimisticPictures, pendingRequests } = state;
  const { set, get, remove } = usePreferences();

  React.useEffect(() => {
    if (pendingRequests.length === 0) {
      remove("pendingRequests");
    } else {
      set("pendingRequests", JSON.stringify(pendingRequests));
    }
  }, [pendingRequests]);

  React.useEffect(() => {
    log("networkStatus - updating connected -", networkStatus.connected);
    if (!networkStatus.connected || pendingRequests.length === 0) {
      return;
    }

    log("networkStatus - sending requests", pendingRequests);
    pendingRequests.forEach((req) => {
      sendRequest(req, token);
    });
    setState((prev) => ({ ...prev, pendingRequests: [] }));
  }, [networkStatus, token, pendingRequests]);

  const saveOptimisticPicture = React.useCallback(
    async (picture: PictureToSave) => {
      log("saving pictures - network connected -", networkStatus.connected);
      if (!networkStatus.connected) {
        log("saveOptimisticPicture - saving locally");
        setState((prev) => ({
          ...prev,
          optimisticPictures: picture.id
            ? prev.optimisticPictures.map((p) =>
                p.id === picture.id ? { ...picture, isPending: true } : p
              )
            : [...prev.optimisticPictures, { ...picture, isPending: true }],
          pendingRequests: [
            ...prev.pendingRequests,
            saveApiRequest({ ...picture, authorId: currentUser?.id }),
          ],
        }));
        return true;
      } else {
        log("saveOptimisticPicture - sending to the server");
        try {
          await PictureAPI.save(picture, token);
        } catch (err: any) {
          log("saveOptimisticPicture - failed -", err.message);
          throw err;
        }
        return false;
      }
    },
    [networkStatus, currentUser, token]
  );

  // Web Socket effect
  React.useEffect(() => {
    let canceled = false;
    log("wsEffect - connecting");
    const closeWebSocket = newWebSocket<Picture>((message) => {
      if (canceled) {
        return;
      }
      const { event, payload } = message;
      log("wsEffect - pictures -", event);
      if (event === "PICTURE_SAVED") {
        setState((prev) => ({
          ...prev,
          optimisticPictures: [
            ...prev.optimisticPictures.filter((p) => p.title !== payload.title),
            payload,
          ],
        }));
      } else if (event === "PICTURE_UPDATED") {
        setState((prev) => ({
          ...prev,
          optimisticPictures: prev.optimisticPictures.map((p) =>
            p.id === payload.id ? payload : p
          ),
        }));
      } else if (event === "PICTURE_DELETED") {
        setState((prev) => ({
          ...prev,
          optimisticPictures: prev.optimisticPictures.filter(
            (p) => p.id !== payload.id
          ),
        }));
      }
    }, token);
    return () => {
      log("wsEffect - disconnecting");
      canceled = true;
      closeWebSocket?.();
    };
  }, [token]);

  React.useEffect(() => {
    if (currentUser?.id === undefined) return;
    log("getPictures - started");
    PictureAPI.findFromAuthorId(currentUser.id)
      .then((pictures) => {
        setState((prev) => ({
          ...prev,
          optimisticPictures: pictures,
        }));
        log("getPictures - succeeded");
      })
      .catch((err) => {
        log("getPictures - failed -", err.message);
      });
  }, [currentUser]);

  return {
    optimisticPictures,
    saveOptimisticPicture,
  };
};

export default useOptimisticPictures;
