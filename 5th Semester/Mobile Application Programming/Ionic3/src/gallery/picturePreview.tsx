import * as React from "react";
import { imageUrl } from "../api";
import { IonCard, IonImg, IonSpinner, createAnimation } from "@ionic/react";

import styles from "./styles/picturePreview.module.css";
import MiniThumbnail from "../user/miniThumbnail";
import { Link } from "react-router-dom";
import classNames from "classnames";
import {
  OptimisticPicture,
  Picture,
  PictureToSave,
} from "../models/picture/types";
import { useAuth } from "../auth";

type Props = {
  picture: OptimisticPicture;
};

const PicturePreview = ({ picture }: Props) => {
  React.useEffect(() => {
    const wrapperAnimation = createAnimation()
      .addElement(document.getElementById(`${picture.id}`)!)
      .duration(10000)
      .iterations(Infinity)
      .keyframes([
        { offset: 0, color: "hsl(0, 100%, 50%)" },
        { offset: 0.25, color: "hsl(90, 100%, 50%)" },
        { offset: 0.5, color: "hsl(180, 100%, 50%)" },
        { offset: 0.75, color: "hsl(270, 100%, 50%)" },
        { offset: 1, color: "hsl(360, 100%, 50%)" },
      ]);
    wrapperAnimation.play();
  }, []);
  const { currentUser } = useAuth();
  const pictureLink = picture.image
    ? imageUrl(picture.image)
    : (picture as PictureToSave).rawImage?.dataUrl ?? imageUrl("default.png");

  const withLink = React.useCallback(
    (component: any) =>
      !picture.isPending ? (
        <Link to={`/pictures/${picture.id}`}>{component}</Link>
      ) : (
        component
      ),
    [picture]
  );

  const author = (picture as Picture).author ?? currentUser;

  return withLink(
    <IonCard
      className={classNames(styles.container, {
        [styles.pending]: picture.isPending,
      })}
    >
      {picture.isPending && (
        <div className={styles.pendingOverlay}>
          <IonSpinner className={styles.pendingIcon} name="circular" />
        </div>
      )}
      <IonImg className={styles.image} src={pictureLink} alt={picture.title} />
      <div className={styles.shadowOverlay} />
      <MiniThumbnail className={styles.authorContainer} user={author} />
      <div id={picture.id} className={styles.titleContainer}>
        {picture.title}
      </div>
    </IonCard>
  );
};

export default PicturePreview;
