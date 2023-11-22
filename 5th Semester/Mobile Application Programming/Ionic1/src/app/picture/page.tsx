import DefaultOverlay from "../overlay/defaultOverlay";
import PictureComponent from "./pictureComponent";
import { IonLoading } from "@ionic/react";
import useParamsPicture from "./useParamsPicture";
import SavePicture from "./savePicture";
import GlobalError from "../extra/globalError";
import { useAuth } from "../models";
import GlobalLoading from "../extra/globalLoading";

const PicturePage = () => {
  const { picture, loading, error } = useParamsPicture();
  const { currentUser, loading: currentUserLoading } = useAuth();

  const isCurrentUserAuthor = currentUser?.id === picture?.authorId;

  return (
    <DefaultOverlay
      title={picture?.title}
      color={"medium"}
      backHref={"/gallery"}
      editHref={
        (isCurrentUserAuthor && `/pictures/${picture?.id}/edit`) || undefined
      }
    >
      <IonLoading isOpen={!picture} />
      {picture && <PictureComponent picture={picture} />}
      <GlobalLoading isOpen={loading || currentUserLoading} />
      <GlobalError error={error} />
    </DefaultOverlay>
  );
};

export default PicturePage;

const SavePicturePage = () => {
  return (
    <DefaultOverlay
      color={"medium"}
      title={"Upload Picture"}
      backHref={"/gallery"}
    >
      <SavePicture />
    </DefaultOverlay>
  );
};

const EditPicturePage = () => {
  const { picture, error } = useParamsPicture();

  return (
    <DefaultOverlay
      color={"medium"}
      title={`Edit ${picture?.title}`}
      backHref={`/pictures/${picture?.id}`}
    >
      <IonLoading isOpen={!picture} />
      {picture && <SavePicture picture={picture} />}
      <GlobalError error={error} />
    </DefaultOverlay>
  );
};

export { SavePicturePage, EditPicturePage };
