import DefaultOverlay from "../overlay/defaultOverlay";
import PictureComponent from "./pictureComponent";
import useParamsPicture from "./useParamsPicture";
import SavePicture from "./savePicture";
import { GlobalError } from "../extra/globalMessage";
import { useAuth } from "../auth";

const PicturePage = () => {
  const { picture, error, setError } = useParamsPicture();
  const { currentUser } = useAuth();

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
      {picture && <PictureComponent picture={picture} />}
      <GlobalError message={error} setMessage={setError} />
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
  const { picture, loading, error, setError } = useParamsPicture();

  return (
    <DefaultOverlay
      color={"medium"}
      title={`Edit ${picture?.title}`}
      backHref={`/pictures/${picture?.id}`}
    >
      {picture && <SavePicture picture={picture} />}
      <GlobalError message={error} setMessage={setError} />
    </DefaultOverlay>
  );
};

export { SavePicturePage, EditPicturePage };
