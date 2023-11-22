import { Picture } from "../models";
import { imageUrl } from "../api";
import { IonCard, IonImg, IonLabel } from "@ionic/react";
import { Link } from "react-router-dom";

import styles from "./styles/picturePreview.module.css";
import MiniThumbnail from "../user/miniThumbnail";

type Props = {
  picture: Picture;
};

const PicturePreview = ({ picture }: Props) => {
  const pictureLink = imageUrl(picture.image ?? "default.png");

  return (
    <IonCard href={`/pictures/${picture.id}`} className={styles.container}>
      <IonImg className={styles.image} src={pictureLink} alt={picture.title} />
      <div className={styles.shadowOverlay} />
      <MiniThumbnail className={styles.authorContainer} user={picture.author} />
    </IonCard>
  );
};

export default PicturePreview;
