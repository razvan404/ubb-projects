import { IonFab, IonFabButton, IonIcon } from "@ionic/react";
import { add } from "ionicons/icons";
import DefaultOverlay from "../overlay";
import PictureList from "./pictureList";

const GalleryPage = () => {
  return (
    <DefaultOverlay
      title={"Gallery"}
      fixedComponent={
        <IonFab vertical="bottom" horizontal="end" slot="fixed">
          <IonFabButton href="/pictures/create">
            <IonIcon icon={add} />
          </IonFabButton>
        </IonFab>
      }
    >
      <PictureList />
    </DefaultOverlay>
  );
};

export default GalleryPage;
