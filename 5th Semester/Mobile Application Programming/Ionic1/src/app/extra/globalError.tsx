import { IonAlert } from "@ionic/react";
import { useHistory } from "react-router";

type Props = {
  error?: string | null;
};

const GlobalError = ({ error }: Props) => {
  const history = useHistory();
  console.log(error);

  return (
    <IonAlert
      isOpen={!!error}
      header={"Error"}
      subHeader={"An error occurred while loading the page"}
      message={error ?? ""}
      buttons={[
        {
          text: "Go back",
          handler: () => {
            history.goBack();
          },
        },
      ]}
    />
  );
};

export default GlobalError;
