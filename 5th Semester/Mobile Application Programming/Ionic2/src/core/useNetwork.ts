import * as React from "react";
import * as Recoil from "recoil";
import { Network, ConnectionStatus } from "@capacitor/network";
import { PluginListenerHandle } from "@capacitor/core";
import { logger } from "./logger";

const log = logger("UseNetwork");

const initialState = {
  connected: false,
  connectionType: "unknown",
};

export const useNetwork = () => {
  const [networkStatus, setNetworkStatus] = React.useState(initialState);
  React.useEffect(() => {
    let canceled = false;
    let handler: PluginListenerHandle;

    const handleNetworkStatusChange = (status: ConnectionStatus) => {
      log("status change", status);
      if (!canceled) {
        setNetworkStatus(status);
      }
    };
    const registerNetworkStatusChange = async () => {
      handler = await Network.addListener(
        "networkStatusChange",
        handleNetworkStatusChange
      );
    };

    registerNetworkStatusChange();
    Network.getStatus().then(handleNetworkStatusChange);

    return () => {
      canceled = true;
      handler?.remove();
    };
  }, []);

  return { networkStatus };
};
