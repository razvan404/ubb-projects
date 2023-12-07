import * as React from "react";
import { Preferences } from "@capacitor/preferences";

const usePreferences = () => {
  const get = React.useCallback(
    async (key: string) =>
      Preferences.get({ key }).then((result) => result.value),
    []
  );

  const set = React.useCallback(
    async (key: string, value: string) => Preferences.set({ key, value }),
    []
  );

  const remove = React.useCallback(
    async (key: string) => Preferences.remove({ key }),
    []
  );

  return {
    get,
    set,
    remove,
  };
};

export default usePreferences;
