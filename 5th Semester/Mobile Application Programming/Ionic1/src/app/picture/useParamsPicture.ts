import * as React from "react";
import { useParams } from "react-router-dom";
import { Picture, PictureAPI, UserAPI } from "../models";

const useParamsPicture = () => {
  const { id } = useParams<{ id: string }>();
  const [picture, setPicture] = React.useState<Picture | undefined>();
  const [loading, setLoading] = React.useState<boolean>(false);
  const [error, setError] = React.useState<string | undefined>();

  React.useEffect(() => {
    setLoading(true);
    PictureAPI.findById(id)
      .then((fetchedPicture) => {
        setPicture(fetchedPicture);
        return fetchedPicture;
      })
      .then((fetchedPicture) => {
        if (!fetchedPicture || !fetchedPicture.authorId) return null;
        return UserAPI.findById(fetchedPicture.authorId);
      })
      .then((fetchedUser) => {
        if (!fetchedUser) return null;
        setPicture(
          (prevPicture) =>
            prevPicture && {
              ...prevPicture,
              author: fetchedUser,
            }
        );
        setLoading(false);
      })
      .catch((error) => {
        setError(error.message);
        setLoading(false);
      });
  }, [id]);

  return { picture, loading, error };
};

export default useParamsPicture;
