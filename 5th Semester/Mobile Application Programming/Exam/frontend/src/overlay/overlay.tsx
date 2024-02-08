import {
  IonButton,
  IonButtons,
  IonContent,
  IonHeader,
  IonMenuButton,
  IonPage,
  IonTitle,
  IonToolbar,
} from "@ionic/react";

import styles from "./styles/overlay.module.css";

type Props = {
  title: string;
  children: React.ReactNode;
  button?: React.ReactNode;
};

const DefaultOverlay = ({ title, children, button }: Props) => {
  return (
    <IonPage>
      <IonHeader>
        <IonToolbar>
          <IonButtons slot="start">
            <IonMenuButton />
          </IonButtons>
          <IonTitle>{title}</IonTitle>
          <IonButtons slot="end">{button}</IonButtons>
        </IonToolbar>
      </IonHeader>

      <IonContent fullscreen>
        <IonHeader collapse="condense">
          <IonToolbar>
            <IonTitle size="large">{title}</IonTitle>
          </IonToolbar>
        </IonHeader>

        <div className={styles.container}>{children}</div>
      </IonContent>
    </IonPage>
  );
};

export default DefaultOverlay;
