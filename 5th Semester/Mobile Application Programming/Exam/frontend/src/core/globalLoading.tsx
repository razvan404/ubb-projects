import { IonLoading } from "@ionic/react";
import logger from "./logger";

const log = logger("GlobalLoading");

type Props = {
  isOpen: boolean | undefined;
  message?: string;
};

const GlobalLoading = ({ isOpen, message = "Please wait..." }: Props) => {
  log("isOpen -", isOpen);
  return <IonLoading isOpen={isOpen} message={message} spinner="circles" />;
};

export default GlobalLoading;
