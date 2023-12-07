import * as React from "react";
import { Geoloc } from "./types";
import { GoogleMap } from "@capacitor/google-maps";
import { logger } from "../core/logger";
import { GOOGLE_MAPS_API_KEY } from "../secrets";

const log = logger("Map");

type Props = {
  id: string;
  location: Geoloc | undefined;
  height?: string | number;
  onMapClick: (ev: Geoloc) => void;
  onMarkerClick: (ev: Geoloc) => void;
};

const mockLocation = {
  lat: 46.770439,
  lng: 23.591423,
};

const Map = ({ id, location, height, onMapClick, onMarkerClick }: Props) => {
  const mapRef = React.useRef<HTMLElement>(null);

  React.useEffect(() => {
    let googleMap: GoogleMap | null = null;
    const validLocation = location && location.lat && location.lng;
    const mapLocation: Geoloc = validLocation ? location : mockLocation;
    const loadMap = async () => {
      if (!mapRef.current) {
        return;
      }
      googleMap = await GoogleMap.create({
        id,
        element: mapRef.current,
        apiKey: GOOGLE_MAPS_API_KEY,
        config: {
          center: mapLocation,
          zoom: 12,
        },
      });
      log("Google Map - created");
      await googleMap.setOnMapClickListener(({ latitude, longitude }) => {
        onMapClick({ lat: latitude, lng: longitude });
      });
      if (validLocation) {
        await googleMap.addMarker({
          coordinate: mapLocation,
          title: "Selected location",
        });
        await googleMap.setOnMarkerClickListener(({ latitude, longitude }) => {
          onMarkerClick({ lat: latitude, lng: longitude });
        });
      }
    };
    loadMap();
    return () => {
      googleMap?.removeAllMapListeners();
    };
  }, [mapRef.current, location, onMapClick, onMarkerClick]);

  return (
    <capacitor-google-map
      ref={mapRef}
      style={{
        width: "100%",
        height: height ?? 400,
      }}
    />
  );
};

export default Map;
