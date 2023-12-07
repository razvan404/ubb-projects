import * as React from "react";
import { Directory, Filesystem } from "@capacitor/filesystem";

const useFileSystem = () => {
  const readFile = React.useCallback(
    async (path: string) =>
      Filesystem.readFile({
        path,
        directory: Directory.Data,
      }).then((result) => result.data),
    []
  );

  const writeFile = React.useCallback(
    async (path: string, data: string) =>
      Filesystem.writeFile({
        path,
        data,
        directory: Directory.Data,
      }),
    []
  );

  const deleteFile = React.useCallback(
    async (path: string) =>
      Filesystem.deleteFile({
        path,
        directory: Directory.Data,
      }),
    []
  );

  return {
    readFile,
    writeFile,
    deleteFile,
  };
};

export default useFileSystem;
