import {
  IonButton,
  IonChip,
  IonFab,
  IonFabButton,
  IonIcon,
  IonLabel,
  IonList,
  IonListHeader,
  IonTitle,
} from "@ionic/react";
import { add } from "ionicons/icons";
import DefaultOverlay from "../overlay/overlay";
import ItemPreview from "./itemPreview";
import useItems from "./useItems";

import styles from "./styles/itemsPage.module.css";
import { GlobalError } from "../core/globalMessage";
import GlobalLoading from "../core/globalLoading";
import useAuth from "../authentication/useAuth";
import React from "react";
import { Item } from "./types";

const ItemsPage = () => {
  const { currentUser } = useAuth();
  const { items, loading, error, setError, update } = useItems();
  const [displayItems, setDisplayItems] = React.useState<Item[]>([]);
  const [selectedColor, setSelectedColor] = React.useState<string | null>(null);

  const getColor = React.useCallback(
    (item: Item) =>
      item.takenBy === currentUser
        ? "red"
        : item.desiredBy[0] === currentUser
        ? "green"
        : item.desiredBy.includes(currentUser ?? "")
        ? "yellow"
        : "white",
    [currentUser]
  );

  React.useEffect(() => {
    console.log(selectedColor);
    if (!selectedColor) {
      setDisplayItems(items);
    } else {
      setDisplayItems(items.filter((item) => getColor(item) === selectedColor));
    }
  }, [items, selectedColor]);

  return (
    <DefaultOverlay title={"Some cute exam 😍"}>
      <div className={styles.content}>
        <div>
          <IonLabel>Filter by color:</IonLabel>
          <IonChip color="danger" onClick={() => setSelectedColor("red")}>
            Red
          </IonChip>
          <IonChip color="success" onClick={() => setSelectedColor("green")}>
            Green
          </IonChip>
          <IonChip color="warning" onClick={() => setSelectedColor("yellow")}>
            Yellow
          </IonChip>
          <IonChip color="dark" onClick={() => setSelectedColor("white")}>
            White
          </IonChip>
          <IonChip onClick={() => setSelectedColor(null)}>Clear</IonChip>
        </div>
        <IonListHeader>
          <IonTitle>Items List</IonTitle>
        </IonListHeader>
        <IonList>
          {displayItems.map((item) => (
            <ItemPreview
              key={item.id}
              item={item}
              color={getColor(item)}
              update={update}
            />
          ))}
        </IonList>
        {/* <IonFab
          vertical="bottom"
          horizontal="center"
          slot="fixed"
          className={styles.fab}
        >
          <IonFabButton routerLink="/newItem" className={styles.fabButton}>
            <IonIcon size="large" icon={add} />
          </IonFabButton>
        </IonFab> */}
      </div>
      <GlobalError message={error} setMessage={setError} />
      <GlobalLoading isOpen={loading} />
    </DefaultOverlay>
  );
};

export default ItemsPage;
