import React from "react";
import { useParams } from "react-router";
import { Item } from "../types";
import DefaultOverlay from "../../overlay/overlay";
import useItems from "../useItems";
import GlobalLoading from "../../core/globalLoading";
import SaveItem from "../saveItem/saveItem";
import { IonButton } from "@ionic/react";
import { GlobalError } from "../../core/globalMessage";

const ItemPage = () => {
  const { id } = useParams<{ id: string }>();
  const [item, setItem] = React.useState<Item | null>(null);
  const { findItem, loading, error, setError, saveItem } = useItems();

  React.useEffect(() => {
    setItem(findItem(parseInt(id)));
  }, [id, findItem]);

  return (
    <DefaultOverlay
      title={item ? `Edit ${item.title}` : "Item not found"}
      button={
        item && <IonButton onClick={() => saveItem(item)}>Update</IonButton>
      }
    >
      {item && <SaveItem itemToSave={item} setItemToSave={setItem} />}
      <GlobalLoading isOpen={loading} />
      <GlobalError message={error} setMessage={setError} />
    </DefaultOverlay>
  );
};

export default ItemPage;
