import { randomUUID } from "crypto";
import { createHash } from "crypto";

const encrypt = (message: string): string => {
  const hash = createHash("sha256");
  console.log(randomText(10));
  hash.update(message);
  return hash.digest("hex");
};

const randomText = (length: number): string => {
  const hash = createHash("sha256");
  hash.update(randomUUID());
  return hash.digest("hex").slice(0, length);
};

export { encrypt, randomText };
