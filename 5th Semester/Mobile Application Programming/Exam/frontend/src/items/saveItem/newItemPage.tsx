import React from "react";
import { IonButton } from "@ionic/react";
import DefaultOverlay from "../../overlay/overlay";
import SaveItem from "./saveItem";
import { Item } from "../types";
import useItems from "../useItems";
import { GlobalError } from "../../core/globalMessage";
import GlobalLoading from "../../core/globalLoading";

const NewItemPage = () => {
  const [item, setItem] = React.useState<Item | null>(null);
  const { error, setError, loading, saveItem } = useItems();

  return (
    <DefaultOverlay
      title="New Item"
      button={
        <IonButton
          onClick={() => {
            saveItem(item);
          }}
        >
          Save
        </IonButton>
      }
    >
      <SaveItem itemToSave={item} setItemToSave={setItem} />
      <GlobalError message={error} setMessage={setError} />
      <GlobalLoading isOpen={loading} />
    </DefaultOverlay>
  );
};

export default NewItemPage;
