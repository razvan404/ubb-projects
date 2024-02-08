import { Item } from "../types";
import { IonHeader, IonInput, IonTitle } from "@ionic/react";

import styles from "./styles/saveItem.module.css";

type Props = {
  itemToSave: Item | null;
  setItemToSave: (item: Item | null) => void;
};

const SaveItem = ({ itemToSave, setItemToSave }: Props) => {
  return (
    <div className={styles.container}>
      <br />
      <IonInput
        label={"Title"}
        placeholder="Enter the desired title"
        fill="outline"
        labelPlacement="floating"
        clearInput
        value={itemToSave?.title}
        onIonInput={(ev) => {
          setItemToSave({
            ...itemToSave,
            title: ev.detail.value ?? "",
          });
        }}
      />
    </div>
  );
};

export default SaveItem;
