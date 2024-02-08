import {
  IonChip,
  IonContent,
  IonIcon,
  IonItem,
  IonLabel,
  IonList,
  IonListHeader,
  IonMenu,
  IonMenuToggle,
  IonNote,
} from "@ionic/react";

import { useLocation } from "react-router-dom";
import {
  archiveOutline,
  archiveSharp,
  bookmarkOutline,
  heartOutline,
  heartSharp,
  mailOutline,
  mailSharp,
  paperPlaneOutline,
  paperPlaneSharp,
  trashOutline,
  trashSharp,
  warningOutline,
  warningSharp,
  planetOutline,
  planetSharp,
  enterOutline,
  enterSharp,
  exitOutline,
  exitSharp,
  cloudOutline,
} from "ionicons/icons";
import "./styles/menu.css";
import useAuth from "../authentication/useAuth";
import { useNetwork } from "../core/useNetwork";

interface AppPage {
  url: string;
  iosIcon: string;
  mdIcon: string;
  title: string;
}

const appPages: AppPage[] = [
  {
    title: "Main thing 🥶",
    url: "/items",
    iosIcon: planetOutline,
    mdIcon: planetSharp,
  },
  {
    title: "Inbox 🙄",
    url: "/folder/Inbox",
    iosIcon: mailOutline,
    mdIcon: mailSharp,
  },
  {
    title: "Outbox 😭",
    url: "/folder/Outbox",
    iosIcon: paperPlaneOutline,
    mdIcon: paperPlaneSharp,
  },
  {
    title: "Favorites 🫠",
    url: "/folder/Favorites",
    iosIcon: heartOutline,
    mdIcon: heartSharp,
  },
  {
    title: "Archived 👀",
    url: "/folder/Archived",
    iosIcon: archiveOutline,
    mdIcon: archiveSharp,
  },
  {
    title: "Trash 🤮",
    url: "/folder/Trash",
    iosIcon: trashOutline,
    mdIcon: trashSharp,
  },
  {
    title: "Spam 😡",
    url: "/folder/Spam",
    iosIcon: warningOutline,
    mdIcon: warningSharp,
  },
  {
    title: "Login 🤔",
    url: "/login",
    iosIcon: enterOutline,
    mdIcon: enterSharp,
  },
];

const labels = ["Hello 👋", "World! 🗺️"];

const Menu: React.FC = () => {
  const location = useLocation();
  const { logout } = useAuth();
  const { networkStatus } = useNetwork();

  if (location.pathname == "/login") {
    return;
  }

  return (
    <IonMenu contentId="main" type="overlay">
      <IonContent>
        <IonList id="inbox-list">
          <IonListHeader>Mobile Exam 🤩</IonListHeader>
          <IonNote>hello user 😉</IonNote>
          {appPages.map((appPage, index) => {
            return (
              <IonMenuToggle key={index} autoHide={false}>
                <IonItem
                  className={
                    location.pathname === appPage.url ? "selected" : ""
                  }
                  routerLink={appPage.url}
                  routerDirection="none"
                  lines="none"
                  detail={false}
                >
                  <IonIcon
                    aria-hidden="true"
                    slot="start"
                    ios={appPage.iosIcon}
                    md={appPage.mdIcon}
                  />
                  <IonLabel>{appPage.title}</IonLabel>
                </IonItem>
              </IonMenuToggle>
            );
          })}
          <IonMenuToggle autoHide={false}>
            <IonItem
              routerLink="/login"
              routerDirection="none"
              onClick={logout}
              lines="none"
              detail={false}
            >
              <IonIcon
                aria-hidden="true"
                slot="start"
                ios={exitOutline}
                md={exitSharp}
              />
              <IonLabel>Logout 🏃‍♂️</IonLabel>
            </IonItem>
          </IonMenuToggle>
        </IonList>

        <IonList id="labels-list">
          <IonListHeader>Labels</IonListHeader>
          {labels.map((label, index) => (
            <IonItem lines="none" key={index}>
              <IonIcon aria-hidden="true" slot="start" icon={bookmarkOutline} />
              <IonLabel>{label}</IonLabel>
            </IonItem>
          ))}
          <IonItem lines="none">
            <IonIcon
              aria-hidden="true"
              slot="start"
              icon={cloudOutline}
              color={networkStatus.connected ? "success" : "danger"}
            />
            <IonLabel>
              {networkStatus.connected ? "Online" : "Offline"}
            </IonLabel>
          </IonItem>
        </IonList>
      </IonContent>
    </IonMenu>
  );
};

export default Menu;
