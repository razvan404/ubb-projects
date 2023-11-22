import React from "react";
import {
  IonAlert,
  IonButton,
  IonIcon,
  IonImg,
  IonInput,
  IonLabel,
  IonSelect,
  IonSelectOption,
  IonTextarea,
} from "@ionic/react";
import { camera, trashBin } from "ionicons/icons";
import { Camera, CameraResultType, CameraSource } from "@capacitor/camera";
import { useHistory } from "react-router";
import { Picture, usePictureTypes, PictureToSave } from "../models";
import { useAuth } from "../auth";
import { imageUrl } from "../api";
import { GlobalError } from "../extra/globalMessage";

import styles from "./styles/savePicture.module.css";
import useOptimisticPictures from "../models/picture/useOptimisticPictures";

type Props = {
  picture?: Picture;
};

const SavePicture = ({ picture }: Props) => {
  const history = useHistory();
  const { saveOptimisticPicture } = useOptimisticPictures();
  const [pictureToSave, setPictureToSave] = React.useState<PictureToSave>({
    ...picture,
  });
  const {
    currentUser,
    error: currentUserError,
    setError: setCurrentUserError,
  } = useAuth();
  const {
    pictureTypes,
    error: pictureTypesError,
    setError: setPictureTypesError,
  } = usePictureTypes();
  const [error, setError] = React.useState<string>();
  const [success, setSuccess] = React.useState<string>();
  React.useEffect(() => {
    setPictureToSave({
      ...picture,
      authorId: currentUser?.id,
    });
  }, [currentUser]);

  const selectPicture = React.useCallback(async () => {
    const image = await Camera.getPhoto({
      quality: 90,
      allowEditing: true,
      resultType: CameraResultType.DataUrl,
      source: CameraSource.Photos,
    });
    setPictureToSave({
      ...pictureToSave,
      rawImage: image,
    });
  }, [pictureToSave]);

  const isNewPicture = !picture;
  const validatePicture = React.useCallback(() => {
    const errors = [];
    if (!pictureToSave?.title) {
      errors.push("Title is required");
    }
    if (!pictureToSave?.description) {
      errors.push("Description is required");
    }
    if (isNewPicture && !pictureToSave?.rawImage) {
      errors.push("Image is required");
    }
    if (!pictureToSave?.typeId) {
      errors.push("Type is required");
    }

    if (
      !isNewPicture &&
      pictureToSave.title === picture?.title &&
      pictureToSave.description === picture?.description &&
      pictureToSave.typeId === picture?.typeId
    ) {
      errors.push("No changes were made");
    }
    setError(errors.join("; "));
    return errors.length === 0;
  }, [pictureToSave, isNewPicture]);

  const saveGivenPicture = React.useCallback(async () => {
    if (!validatePicture()) {
      return;
    }
    saveOptimisticPicture(pictureToSave)
      .then((isPending) => {
        if (isPending) {
          setSuccess(
            "You don't have an internet connection, but the picture will be updated when you do"
          );
        } else {
          setSuccess(
            `The picture has been ${
              isNewPicture ? "uploaded" : "updated"
            } successfully`
          );
        }
      })
      .catch((err) => {
        setError(err.message);
      });
  }, [pictureToSave, validatePicture]);

  const pictureUrl = picture?.image && imageUrl(picture?.image);

  return (
    <>
      <div className={styles.container}>
        {!isNewPicture ? (
          <IonImg
            className={styles.image}
            src={pictureUrl}
            alt={picture.title}
          />
        ) : !pictureToSave?.rawImage ? (
          <IonButton
            className={styles.button}
            color="light"
            onClick={selectPicture}
          >
            <IonIcon slot="start" icon={camera} />
            <IonLabel>Select Image</IonLabel>
          </IonButton>
        ) : (
          <div className={styles.uploadedImageContainer}>
            <IonImg
              className={styles.uploadedImage}
              src={pictureToSave.rawImage.dataUrl}
            />
            <IonButton
              className={styles.retakeUploadedImage}
              color="light"
              shape="round"
              onClick={selectPicture}
            >
              <IonIcon slot="start" icon={camera} />
              <IonLabel>Retake</IonLabel>
            </IonButton>
            <IonButton
              className={styles.removeUploadedImage}
              color="danger"
              shape="round"
              onClick={() => {
                setPictureToSave({
                  ...pictureToSave,
                  rawImage: undefined,
                });
              }}
            >
              <IonIcon slot="start" icon={trashBin} />
              <IonLabel>Remove</IonLabel>
            </IonButton>
          </div>
        )}
        <IonInput
          label={isNewPicture ? "Title" : "Updated Title"}
          placeholder="Enter the desired title"
          fill="outline"
          labelPlacement="floating"
          clearInput
          value={pictureToSave?.title}
          onIonInput={(ev) => {
            setPictureToSave({
              ...pictureToSave,
              title: ev.detail.value ?? undefined,
            });
          }}
        />
        <IonTextarea
          className={styles.description}
          label={isNewPicture ? "Description" : "Updated Descrption"}
          placeholder="Enter the desired description"
          fill="outline"
          labelPlacement="floating"
          value={pictureToSave?.description}
          counter
          maxlength={400}
          counterFormatter={(inputLength, maxLength) =>
            `${maxLength - inputLength} characters remaining`
          }
          onIonInput={(ev) => {
            setPictureToSave({
              ...pictureToSave,
              description: ev.detail.value ?? undefined,
            });
          }}
        />
        <IonSelect
          label={isNewPicture ? "Type" : "Updated Type"}
          placeholder="Select the desired type"
          fill="outline"
          labelPlacement="floating"
          value={pictureToSave?.typeId}
          onIonChange={(ev) => {
            setPictureToSave({
              ...pictureToSave,
              typeId: ev.detail.value,
            });
          }}
        >
          {Object.values(pictureTypes).map((pictureType) => (
            <IonSelectOption key={pictureType.id} value={pictureType.id}>
              {pictureType.name}
            </IonSelectOption>
          ))}
        </IonSelect>
        <IonButton
          className={styles.button}
          color="warning"
          onClick={saveGivenPicture}
        >
          <IonLabel>
            {isNewPicture ? "Upload picture" : "Save changes"}
          </IonLabel>
        </IonButton>
        <IonAlert
          isOpen={!!error}
          header="Error"
          subHeader={`An error occurred while ${
            isNewPicture ? "uploading" : "updating"
          } the picture`}
          message={error}
          buttons={[{ text: "OK", handler: () => setError(undefined) }]}
        />
        <IonAlert
          isOpen={!!success}
          header="Success"
          message={success}
          buttons={[
            {
              text: "OK",
              handler: () => {
                setSuccess(undefined);
                history.push("/pictures");
              },
            },
          ]}
        />
        <GlobalError
          message={pictureTypesError}
          setMessage={setPictureTypesError}
        />
        <GlobalError
          message={currentUserError}
          setMessage={setCurrentUserError}
        />
      </div>
    </>
  );
};

export default SavePicture;
