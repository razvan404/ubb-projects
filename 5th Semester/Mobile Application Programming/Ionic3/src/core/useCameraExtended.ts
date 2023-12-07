import * as React from "react";
import useCamera from "./useCamera";
import useFileSystem from "./useFileSystem";

const useCameraExtended = () => {
  const [lastPhoto, setLastPhoto] = React.useState<string | null>(null);
  const { takePhoto: _takePhoto } = useCamera();
  const { writeFile, deleteFile } = useFileSystem();

  const deleteLastPhoto = React.useCallback(() => {
    if (lastPhoto) {
      deleteFile(lastPhoto);
      setLastPhoto(null);
    }
  }, [lastPhoto, deleteFile, setLastPhoto]);

  const takePhoto = React.useCallback(async () => {
    const photo = await _takePhoto();
    deleteLastPhoto();
    if (photo) {
      const fileName = new Date().getTime() + ".jpeg";
      console.log("saving photo to", fileName, photo);
      writeFile(fileName, photo.dataUrl!);
      setLastPhoto(fileName);
    }
    return photo;
  }, [_takePhoto]);

  return {
    takePhoto,
    deleteLastPhoto,
    setLastPhoto,
  };
};

export default useCameraExtended;
