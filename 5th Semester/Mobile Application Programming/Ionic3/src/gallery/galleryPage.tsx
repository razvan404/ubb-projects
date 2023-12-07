import * as React from "react";
import DefaultOverlay from "../overlay";
import PictureList from "./pictureList";
import { Picture, PictureAPI } from "../models";

const loadingAtOneTime = 3;

const GalleryPage = () => {
  const [pictures, setPictures] = React.useState<Picture[]>([]);
  const [selectedPictureType, setSelectedPictureType] = React.useState<
    number | undefined
  >();
  const [scrolledEnough, setScrolledEnough] = React.useState(false);
  const [titleFilter, setTitleFilter] = React.useState<string | undefined>();
  const [pictureTypeFilter, setPictureTypeFilter] = React.useState<
    number | undefined
  >();

  React.useEffect(() => {
    setScrolledEnough(false);
    PictureAPI.findAll({
      skip: 0,
      take: loadingAtOneTime,
      titleContains: titleFilter,
      typeId: pictureTypeFilter,
    }).then((pictures) => {
      if (pictures.length < loadingAtOneTime) {
        setScrolledEnough(true);
      }
      setPictures(pictures);
    });
  }, [titleFilter, pictureTypeFilter]);

  const onScroll = React.useCallback(
    (ev: CustomEvent<void>) => {
      if (scrolledEnough) {
        (ev.target as HTMLIonInfiniteScrollElement).complete();
        return;
      }
      PictureAPI.findAll({
        skip: pictures.length,
        take: loadingAtOneTime,
        titleContains: titleFilter,
        typeId: pictureTypeFilter,
      }).then((newPictures) => {
        if (newPictures.length < loadingAtOneTime) {
          setScrolledEnough(true);
        }
        setPictures([...pictures, ...newPictures]);
        (ev.target as HTMLIonInfiniteScrollElement).complete();
      });
    },
    [scrolledEnough, pictureTypeFilter, pictures]
  );

  return (
    <DefaultOverlay title={"Art Gallery"} onScroll={onScroll}>
      <PictureList
        pictures={pictures}
        selectByTitle={setTitleFilter}
        selectByPictureType={(numb?: number) => {
          setSelectedPictureType(numb);
          setPictureTypeFilter(numb);
        }}
        selectedPictureType={selectedPictureType}
      />
    </DefaultOverlay>
  );
};

export default GalleryPage;
