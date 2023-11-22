import { db } from "../src/utils/database";
import { configDotenv } from "dotenv";
import { encrypt } from "../src/utils/encryption";

configDotenv();

type User = {
  username: string;
  email: string;
  password: string;
};

const createUser = (
  username: string,
  email: string,
  password: string
): User => ({
  username: username,
  email: encrypt(email),
  password: encrypt(password),
});

type PictureType = {
  name: string;
};

const createPictureType = (type: string): PictureType => ({
  name: type,
});

type Picture = {
  title: string;
  description: string;
  url: string;
};

const createPicture = (
  title: string,
  description: string,
  url: string
): Picture => ({
  title: title,
  description: description,
  url: url,
});

const getUsers = (): User[] => [
  createUser("razvan", "razvan@gmail.com", "razvan"),
  createUser("alex", "alex@gmail.com", "alex"),
  createUser("andrei", "andrei@gmail.com", "andrei"),
  createUser("bogdan", "bogdan@gmail.com", "bogdan"),
  createUser("gabi", "gabi@gmail.com", "gabi"),
  createUser("mihai", "mihai@gmail.com", "mihai"),
  createUser("nicu", "nicu@gmail.com", "nicu"),
  createUser("cosmin", "cosmin@gmail.com", "cosmin"),
  createUser("rares", "rares@gmail.com", "rares"),
  createUser("sergiu", "sergiu@gmail.com", "sergiu"),
  createUser("denis", "denis@gmail.com", "denis"),
];

const getPictureTypes = (): PictureType[] => [
  createPictureType("Photography"),
  createPictureType("Painting"),
  createPictureType("Digital Art"),
  createPictureType("AI Generated"),
];

const getPictures = (): Picture[] => [
  createPicture(
    "Wonderful Lake in the Mountains",
    "Immerse yourself in the tranquil beauty of a mountain lake, a captivating photograph that showcases breathtaking alpine landscapes.h",
    "fe864dfc8570dbbb.png"
  ),
  createPicture(
    "Seasons Tree",
    "'Seasons Tree' art showcases the eternal cycle of nature, displaying the ever-changing beauty of each season in a single captivating image.",
    "aa48fc2a9ee5943f.png"
  ),
];

const seed = async () => {
  try {
    await Promise.all(
      getUsers().map((user) => {
        return db.user.create({
          data: {
            username: user.username,
            password: user.password,
            email: user.email,
          },
        });
      })
    );
  } catch (error) {
    console.log("Couldn't seed all the users");
  }
  try {
    await Promise.all(
      getPictureTypes().map((type) => {
        return db.pictureType.create({
          data: {
            name: type.name,
          },
        });
      })
    );
  } catch (error) {
    console.log("Couldn't seed all the picture types");
  }
  const author = await db.user.findFirst({
    where: {
      username: "razvan",
    },
  });
  const type1 = await db.pictureType.findFirst({
    where: {
      name: "Photography",
    },
  });
  const type2 = await db.pictureType.findFirst({
    where: {
      name: "Digital Art",
    },
  });

  const types = [type1, type2];

  try {
    await Promise.all(
      getPictures().map((picture, idx) => {
        const { title, description, url } = picture;
        return db.picture.create({
          data: {
            title: title,
            description: description,
            image: url,
            // @ts-expect-error
            typeId: types[idx].id,
            // @ts-expect-error
            authorId: author.id,
          },
        });
      })
    );
  } catch (error) {
    console.log("Couldn't seed all the pictures");
  }
};

seed();
