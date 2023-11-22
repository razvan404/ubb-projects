import {
  IonHeader,
  IonToolbar,
  IonTitle,
  IonContent,
  IonMenu,
  IonList,
  IonItem,
} from "@ionic/react";

import styles from "./styles/overlayMenu.module.css";
import { useAuth } from "../models";

const OverlayMenu = () => {
  const { currentUser, logout } = useAuth();

  return (
    <IonMenu contentId="main-content">
      <IonHeader>
        <IonToolbar color="primary">
          <IonTitle>Art Menu</IonTitle>
        </IonToolbar>
      </IonHeader>
      <IonContent className={styles.menuContent}>
        <IonList className={styles.menuList}>
          <IonItem button href="/gallery">
            Gallery
          </IonItem>
          <IonItem button href="/about">
            About
          </IonItem>
          <IonItem button href="/contact">
            Contact
          </IonItem>
        </IonList>
        <IonList className={styles.menuList}>
          {currentUser ? (
            <>
              <IonItem button href="/profile">
                Your Profile
              </IonItem>
              <IonItem button onClick={logout}>
                Logout
              </IonItem>
            </>
          ) : (
            <IonItem button href="/login">
              Login
            </IonItem>
          )}
        </IonList>
      </IonContent>
    </IonMenu>
  );
};

export default OverlayMenu;
