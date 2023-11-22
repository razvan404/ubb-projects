import * as React from "react";
import { IonButton, IonIcon, IonImg, IonLabel, IonToast } from "@ionic/react";
import { cloudDownloadOutline, shareSocialOutline } from "ionicons/icons";
import { Picture, PictureType, usePictureTypes } from "../models";
import { downloadImageUrl, imageUrl } from "../api";
import MiniThumbnail from "../user/miniThumbnail";

import styles from "./styles/pictureComponent.module.css";
import { GlobalError } from "../extra/globalMessage";

type Props = {
  picture: Picture;
};

const PictureComponent = ({ picture }: Props) => {
  const [showToast, setShowToast] = React.useState(false);
  const {
    pictureTypes,
    loaded: pictureTypesLoaded,
    error: pictureTypesError,
    setError: setPictureTypesError,
  } = usePictureTypes();
  const [pictureType, setPictureType] = React.useState<PictureType>();

  React.useEffect(() => {
    if (!pictureTypesLoaded || pictureTypesError) {
      return;
    }
    if (pictureTypes && picture.typeId !== undefined) {
      setPictureType(pictureTypes[picture.typeId]);
    }
  }, [pictureTypes, pictureTypesLoaded, pictureTypesLoaded]);

  const pictureUrl = imageUrl(picture.image);
  const downloadPictureUrl = downloadImageUrl(picture.image);

  return (
    <div className={styles.container}>
      <IonImg src={pictureUrl} alt={picture.title} className={styles.image} />
      <div className={styles.uploaderRow}>
        <div className={styles.uploaderContainer}>
          <IonLabel className={styles.uploaderText}>Uploaded by</IonLabel>
          {<MiniThumbnail user={picture.author} />}
          {picture.createdAt && (
            <IonLabel className={styles.uploadDate}>
              on {picture.createdAt.toLocaleDateString("en-GB")}
            </IonLabel>
          )}
        </div>
        <div className={styles.topButtons}>
          <IonButton color="secondary" href={downloadPictureUrl}>
            <IonIcon slot="start" icon={cloudDownloadOutline} />
            <IonLabel>Download</IonLabel>
          </IonButton>
          <IonButton
            color="tertiary"
            onClick={() => {
              const currentUrl = window.location.href;
              navigator.clipboard.writeText(currentUrl).then(() => {
                setShowToast(true);
              });
            }}
          >
            <IonIcon slot="start" icon={shareSocialOutline} />
            <IonLabel>Share</IonLabel>
          </IonButton>
        </div>
      </div>
      <div className={styles.detailsRow}>
        <IonLabel className={styles.title}>{picture.title}</IonLabel>
        <IonLabel className={styles.type}>
          Type: {pictureType?.name ?? "unknown"}
        </IonLabel>
        <IonLabel className={styles.description}>
          "{picture.description}"
        </IonLabel>
      </div>
      <IonToast
        isOpen={showToast}
        message="Link copied to the clipboard"
        duration={3000}
        onDidDismiss={() => setShowToast(false)}
      />
      <GlobalError
        message={pictureTypesError}
        setMessage={setPictureTypesError}
      />
    </div>
  );
};

export default PictureComponent;
