import { IonList } from "@ionic/react";
import PicturePreview from "./picturePreview";

import styles from "./styles/pictureList.module.css";
import { Picture } from "../models";
import { OptimisticPicture } from "../models/picture/types";
import PictureFilters from "./pictureFilters";

type Props = {
  pictures: (OptimisticPicture | Picture)[];
  selectByTitle?: (titleFilter?: string) => void;
  selectByPictureType?: (pictureTypeId?: number) => void;
  selectedPictureType?: number;
};

const PictureList = ({
  pictures,
  selectByTitle,
  selectByPictureType,
  selectedPictureType,
}: Props) => {
  return (
    <>
      <PictureFilters
        selectByTitle={selectByTitle}
        selectByPictureType={selectByPictureType}
        selectedPictureType={selectedPictureType}
      />
      <IonList className={styles.pictureListContainer}>
        {pictures.map((picture: OptimisticPicture) => (
          <PicturePreview picture={picture} key={picture.id} />
        ))}
      </IonList>
    </>
  );
};

export default PictureList;
