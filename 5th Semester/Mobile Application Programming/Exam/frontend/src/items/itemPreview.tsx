import { IonButton, IonItem, IonLabel, IonTitle } from "@ionic/react";
import { Item } from "./types";

import styles from "./styles/itemPreview.module.css";
import React from "react";
import useAuth from "../authentication/useAuth";

type Props = {
  item: Item;
  color: string;
  update: (item: Item) => void;
};

const ItemPreview = ({ item, color, update }: Props) => {
  const [isExpandend, setIsExpandend] = React.useState<boolean>(false);
  const { currentUser } = useAuth();

  const onClick = React.useCallback(() => {
    const newItem = { ...item };
    if (color === "red") {
      newItem.takenBy = null;
    } else if (color === "green") {
      newItem.takenBy = currentUser ?? "";
      newItem.desiredBy = newItem.desiredBy.filter(
        (user) => user !== currentUser
      );
    } else if (color === "yellow") {
      newItem.desiredBy = newItem.desiredBy.filter(
        (user) => user !== currentUser
      );
    } else {
      newItem.desiredBy = [...newItem.desiredBy, currentUser ?? ""];
    }
    console.log(newItem);
    update(newItem);
  }, [item, color]);

  const ionColor =
    color === "red"
      ? "danger"
      : color === "green"
      ? "success"
      : color === "yellow"
      ? "warning"
      : "dark";

  return (
    <>
      <div className={styles.container}>
        <IonItem
          className={styles.item}
          onClick={() => setIsExpandend((prev) => !prev)}
          color={ionColor}
        >
          <IonTitle>{item.name}</IonTitle>
        </IonItem>
      </div>
      {isExpandend && (
        <IonItem>
          <IonLabel>
            {item.desiredBy.length > 0
              ? `Desired by: ${item.desiredBy.join(", ")}`
              : "It's not desired"}
          </IonLabel>
          <IonButton onClick={onClick} color={ionColor}>
            <IonLabel>
              {color === "red"
                ? "Return"
                : color === "green"
                ? "Take"
                : color === "yellow"
                ? "Remove request"
                : "Add request"}
            </IonLabel>
          </IonButton>
        </IonItem>
      )}
    </>
  );
};

export default ItemPreview;
