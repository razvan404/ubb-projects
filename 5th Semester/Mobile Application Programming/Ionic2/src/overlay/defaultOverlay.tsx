import React from "react";
import {
  IonButtons,
  IonHeader,
  IonMenuButton,
  IonPage,
  IonTitle,
  IonToolbar,
  IonContent,
  IonBackButton,
  IonButton,
  IonIcon,
  IonInfiniteScroll,
  IonInfiniteScrollContent,
} from "@ionic/react";
import OverlayMenu from "./overlayMenu";
import { constructOutline } from "ionicons/icons";

import { Link } from "react-router-dom";

type OverlayProps = {
  title?: string;
  children?: React.ReactNode;
  disableButtons?: boolean;
  backHref?: string;
  color?: string;
  editHref?: string;
  fixedComponent?: React.ReactNode;
  withScrolling?: boolean;
  onScroll?: (ev: CustomEvent<void>) => void;
};

const DefaultOverlay = ({
  title,
  children,
  disableButtons,
  backHref,
  color = "success",
  editHref,
  fixedComponent,
  withScrolling = true,
  onScroll,
}: OverlayProps) => {
  return (
    <>
      <OverlayMenu />
      <IonPage id="main-content">
        <IonHeader>
          <IonToolbar color={color}>
            {!disableButtons && (
              <>
                <IonButtons slot="start">
                  <IonMenuButton />
                  {backHref && <IonBackButton defaultHref={backHref} />}
                </IonButtons>
                {editHref && (
                  <IonButtons slot="end">
                    <Link to={editHref}>
                      <IonButton color={"light"}>
                        <IonIcon size={"large"} icon={constructOutline} />
                      </IonButton>
                    </Link>
                  </IonButtons>
                )}
              </>
            )}
            {title && <IonTitle>{title}</IonTitle>}
          </IonToolbar>
        </IonHeader>
        <IonContent className="ion-padding">
          {children}
          {withScrolling && (
            <IonInfiniteScroll
              threshold="100px"
              disabled={!onScroll}
              onIonInfinite={onScroll}
            >
              <IonInfiniteScrollContent loadingText={"Loading more..."} />
            </IonInfiniteScroll>
          )}
          {fixedComponent}
        </IonContent>
      </IonPage>
    </>
  );
};

export default DefaultOverlay;
