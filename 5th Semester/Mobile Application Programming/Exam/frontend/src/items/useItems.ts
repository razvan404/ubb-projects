import React from "react";
import Recoil from "recoil";
import itemsApi from "./itemsApi";
import usePreferences from "../core/usePreferences";
import handleError from "../core/handleError";
import { Item } from "./types";
import logger from "../core/logger";
import { newWebSocket } from "../api";

const log = logger("useItems");

type ItemsState = {
  items: Item[];
  loading?: boolean;
  error?: string;
};

const initialState: ItemsState = {
  items: [],
};

const itemsState = Recoil.atom({
  key: "itemsState",
  default: initialState,
});

const upsertItem = (items: Item[], newItem: Item, update: any) => {
  let newItems = [];
  if (items.filter((item) => item.id === newItem.id).length === 0) {
    newItems = [...items, newItem];
  } else {
    newItems = items.map((item) => (item.id === newItem.id ? newItem : item));
  }
  update(newItems);
  return newItems;
};

const useItems = () => {
  const { set, get } = usePreferences();
  const [state, setState] = Recoil.useRecoilState(itemsState);

  React.useEffect(() => {
    const onClose = newWebSocket((data: any) => {
      log("webSocket - received -", data);
      if (Array.isArray(data)) {
        // array
        setState((prev) => ({
          ...prev,
          items: data,
          loading: false,
          error: undefined,
        }));
        set("items", JSON.stringify(data));
      } else {
        setState((prev) => ({
          ...prev,
          items: upsertItem(prev.items, data, (newItems: Item[]) =>
            set("items", JSON.stringify(newItems))
          ),
          loading: false,
          error: undefined,
        }));
      }
    });
    return () => {
      onClose();
    };
  }, [set]);

  React.useEffect(() => {
    setState((prev) => ({ ...prev, loading: true, error: undefined }));
    log("useItems - started");
    get("items")
      .then((items: string | null) => {
        if (items) {
          log("useItems - found in preferences");
          setState((prev) => ({
            ...prev,
            items: JSON.parse(items),
            loading: false,
            error: undefined,
          }));
        }
      })
      .catch((err) => {
        log("useItems - error", err);
        setState((prev) => ({ ...prev, loading: false, error: err.message }));
        handleError(err.message);
      });
  }, []);

  const findItem = React.useCallback(
    (id: number) => {
      return state.items.find((item) => item.id === id) ?? null;
    },
    [state]
  );

  const saveItem = React.useCallback(
    (item: Item | null) => {
      if (item === null) {
        setState((prev) => ({
          ...prev,
          loading: false,
          error: "Item cannot be null",
        }));
        return;
      }
      const newItem = { ...item, pending: true };
      if (newItem.id) {
        log("saveItem - update - started", newItem);
        const items = state.items.map((i) =>
          i.id === newItem.id ? newItem : i
        );
        setState({ ...state, items, loading: true, error: undefined });
        set("items", JSON.stringify(items));
        return itemsApi
          .update(item)
          .then((item) => {
            log("saveItem - update - success", item);
            const items = state.items.map((i) => (i.id === item.id ? item : i));
            set("items", JSON.stringify(items));
            setState({ ...state, items, loading: false, error: undefined });
          })
          .catch((err: any) => {
            log("saveItem - update - error", err);
            setState({ ...state, loading: false, error: err.message });
            handleError(err.message);
          });
      } else {
        log("saveItem - create - started", newItem);
        const insertedItem = {
          ...newItem,
          id: Math.floor(Math.random() * 10000 + 10000),
        };
        const items = [...state.items, insertedItem];
        setState({ ...state, items, loading: true, error: undefined });
        set("items", JSON.stringify(items));
        itemsApi
          .save(item)
          .then((item) => {
            log("saveItem - create - success", item);
            const items = [...state.items, item];
            set("items", JSON.stringify(items));
            setState({ ...state, items, loading: false, error: undefined });
          })
          .catch((err: any) => {
            log("saveItem - create - error", err);
            setState({ ...state, loading: false, error: err.message });
            handleError(err.message);
          });
      }
    },
    [state]
  );

  const update = React.useCallback((item: Item) => {
    setState((prev) => ({ ...prev, loading: true, error: undefined }));
    itemsApi
      .patch(item)
      .then(() => {
        setState((prev) => ({ ...prev, loading: false, error: undefined }));
      })
      .catch((err: any) => {
        handleError(err.message);
        setState((prev) => ({ ...prev, loading: false, error: err.message }));
      });
  }, []);

  const setError = React.useCallback((error?: string) => {
    setState((prev) => ({ ...prev, error }));
  }, []);

  return { ...state, findItem, saveItem, setError, update };
};

export default useItems;
