import * as React from "react";
import Map, { Geoloc } from "../map";
import {
  createAnimation,
  IonButton,
  IonHeader,
  IonModal,
  IonTitle,
} from "@ionic/react";

import styles from "./styles/mapModal.module.css";

type Props = {
  location: Geoloc | undefined;
  setLocation: (location: Geoloc | undefined) => void;
};

const MapModal = ({ location, setLocation }: Props) => {
  const [showModal, setShowModal] = React.useState(false);

  const enterAnimation = (baseEl: any) => {
    const root = baseEl.shadowRoot;
    const backdropAnimation = createAnimation()
      .addElement(root.querySelector("ion-backdrop")!)
      .fromTo("opacity", "0.01", "var(--backdrop-opacity)");

    const wrapperAnimation = createAnimation()
      .addElement(root.querySelector(".modal-wrapper")!)
      .keyframes([
        { offset: 0, opacity: "0", transform: "scale(0)" },
        { offset: 1, opacity: "1", transform: "scale(1)" },
      ]);

    return createAnimation()
      .addElement(baseEl)
      .easing("ease-out")
      .duration(1000)
      .addAnimation([backdropAnimation, wrapperAnimation]);
  };

  const leaveAnimation = (baseEl: any) => {
    return enterAnimation(baseEl).direction("reverse");
  };

  return (
    <>
      <IonModal
        isOpen={showModal}
        onDidDismiss={() => setShowModal(false)}
        enterAnimation={enterAnimation}
        leaveAnimation={leaveAnimation}
      >
        <IonHeader className={styles.header}>
          <IonTitle>Edit Location</IonTitle>
        </IonHeader>
        <Map
          id="map"
          location={location}
          onMapClick={(ev) => setLocation(ev)}
          onMarkerClick={() => setLocation(undefined)}
          height="100%"
        />
        <IonButton onClick={() => setShowModal(false)}>Close</IonButton>
      </IonModal>
      <Map
        id="map"
        location={location}
        onMapClick={() => setShowModal(true)}
        onMarkerClick={() => setShowModal(true)}
      />
    </>
  );
};

export default MapModal;
