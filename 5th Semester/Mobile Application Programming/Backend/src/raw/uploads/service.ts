import fs from "fs";
import { randomText } from "../../utils/encryption";

const baseDir = `${__dirname}/../../../uploads`;

export default {
  getPath: (file: string) => {
    return `${baseDir}/${file}`;
  },
  generatePath: (format: string) => {
    while (true) {
      const filename = randomText(16);
      const filePath = `${baseDir}/${filename}.${format}`;
      if (!fs.existsSync(filePath)) return filePath;
    }
  },
  save: async (rawFile: string, filePath: string) => {
    const file = rawFile.replace(/^data:image\/\w+;base64,/, "");
    fs.writeFileSync(filePath, file, { encoding: "base64" });
    return filePath.slice(baseDir.length + 1);
  },
  delete: async (file: string) => {
    const filePath = `${__dirname}/../../uploads/${file}`;
    fs.unlinkSync(filePath);
  },
};
