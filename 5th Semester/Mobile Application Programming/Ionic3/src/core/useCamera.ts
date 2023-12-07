import * as React from "react";
import { Camera, CameraResultType, CameraSource } from "@capacitor/camera";

const useCamera = () => {
  const takePhoto = React.useCallback(
    async () =>
      Camera.getPhoto({
        quality: 100,
        allowEditing: true,
        source: CameraSource.Camera,
        resultType: CameraResultType.DataUrl,
      }).catch(() => {
        return null;
      }),
    []
  );

  return {
    takePhoto,
  };
};

export default useCamera;
