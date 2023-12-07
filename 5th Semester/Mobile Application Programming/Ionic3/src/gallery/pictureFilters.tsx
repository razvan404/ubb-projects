import { IonChip, IonSearchbar } from "@ionic/react";
import { usePictureTypes } from "../models";

import styles from "./styles/pictureFilters.module.css";

type Props = {
  selectByTitle?: (titleFilter?: string) => void;
  selectByPictureType?: (pictureTypeId?: number) => void;
  selectedPictureType?: number;
};

const PictureFilters = ({
  selectByTitle,
  selectByPictureType,
  selectedPictureType,
}: Props) => {
  const { pictureTypes } = usePictureTypes();
  return (
    <>
      {selectByTitle && (
        <IonSearchbar
          className={styles.searchBar}
          placeholder="Search by title"
          onIonInput={(ev) => selectByTitle(ev.detail.value ?? undefined)}
        />
      )}
      {selectByPictureType && pictureTypes && (
        <>
          {Object.entries(pictureTypes).map(([id, pictureType]) => (
            <IonChip
              key={id}
              onClick={() => {
                selectByPictureType(pictureType.id);
              }}
              color={
                pictureType.id === selectedPictureType ? "primary" : undefined
              }
            >
              {pictureType.name}
            </IonChip>
          ))}
          <IonChip
            color={selectedPictureType === undefined ? "primary" : undefined}
            onClick={() => selectByPictureType()}
          >
            Clear filters
          </IonChip>
        </>
      )}
    </>
  );
};

export default PictureFilters;
