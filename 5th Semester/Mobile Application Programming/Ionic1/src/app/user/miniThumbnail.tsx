import { User } from "../models";
import { IonCard, IonImg } from "@ionic/react";
import { imageUrl } from "../api";
import classNames from "classnames";

import styles from "./styles/miniThumbnail.module.css";

type Props = {
  user?: User;
  className?: string;
};

const MiniThumbnail = ({ user, className }: Props) => {
  const authorImageLink = imageUrl(user?.profileImage ?? "default.png");
  const authorUsername = user?.username ?? "unknown";

  return (
    <div className={classNames(className, styles.container)}>
      <IonCard className={styles.imageContainer}>
        <IonImg
          className={styles.image}
          src={authorImageLink}
          alt={authorUsername}
        />
      </IonCard>
      {authorUsername}
    </div>
  );
};

export default MiniThumbnail;
