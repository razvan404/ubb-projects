import { IonAlert } from "@ionic/react";

type Props = {
  title?: string;
  subTitle?: string;
  message?: string | null;
  setMessage: (arg0?: string) => void;
};

const GlobalMessage = ({ title, subTitle, message, setMessage }: Props) => {
  return (
    <IonAlert
      isOpen={!!message}
      header={title}
      subHeader={subTitle ?? "Something went wrong"}
      message={message ?? ""}
      buttons={[
        {
          text: "Ok",
          handler: () => {
            setMessage();
          },
        },
      ]}
    />
  );
};

const GlobalError = ({ message, setMessage }: Props) => {
  return (
    <GlobalMessage
      message={message}
      setMessage={setMessage}
      title={"Error"}
      subTitle={"Something went wrong"}
    />
  );
};

export default GlobalMessage;
export { GlobalError };
