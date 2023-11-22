import { IonLoading } from "@ionic/react";

type Props = {
  isOpen: boolean;
  message?: string;
};

const GlobalLoading = ({ isOpen, message = "Please wait..." }: Props) => {
  return <IonLoading isOpen={isOpen} message={message} spinner="circles" />;
};

export default GlobalLoading;
