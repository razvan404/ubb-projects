import usePictures from "../models/picture/usePictures";
import { IonList, IonFabButton, IonIcon, IonFab } from "@ionic/react";
import { add } from "ionicons/icons";
import PicturePreview from "./picturePreview";

import styles from "./styles/pictureList.module.css";

const PictureList = () => {
  const { pictures } = usePictures();

  return (
    <>
      <IonList className={styles.pictureListContainer}>
        {pictures.map((picture) => (
          <PicturePreview picture={picture} key={picture.id} />
        ))}
      </IonList>
    </>
  );
};

export default PictureList;
