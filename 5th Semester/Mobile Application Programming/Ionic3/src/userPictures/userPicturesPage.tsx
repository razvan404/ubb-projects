import { IonFab, IonFabButton, IonIcon } from "@ionic/react";
import { add } from "ionicons/icons";
import { Link } from "react-router-dom";
import PictureList from "../gallery/pictureList";
import DefaultOverlay from "../overlay";
import useOptimisticPictures from "../models/picture/useOptimisticPictures";
import GlobalError from "../extra/globalMessage";

const UserPicturesPage = () => {
  const { optimisticPictures } = useOptimisticPictures();

  return (
    <DefaultOverlay
      title={"My pictures"}
      color={"secondary"}
      fixedComponent={
        <IonFab vertical="bottom" horizontal="center" slot="fixed">
          <Link to="/pictures/create">
            <IonFabButton>
              <IonIcon size="large" icon={add} />
            </IonFabButton>
          </Link>
        </IonFab>
      }
    >
      <PictureList pictures={optimisticPictures} />
    </DefaultOverlay>
  );
};

export default UserPicturesPage;
