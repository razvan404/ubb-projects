import { db } from "../../utils/database";
import { encrypt } from "../../utils/encryption";
import { type User } from "./types";

export default {
  findAll: async (): Promise<User[]> => {
    return await db.user.findMany({
      select: {
        id: true,
        username: true,
        profileImage: true,
      },
    });
  },
  findById: async (id: string): Promise<User | null> => {
    return await db.user.findUnique({
      where: {
        id,
      },
      select: {
        id: true,
        username: true,
        profileImage: true,
      },
    });
  },
  findByUsernameOrMail: async (
    usernameOrMail: string
  ): Promise<User | null> => {
    const isEmail = usernameOrMail.includes("@");
    const select = {
      id: true,
      username: true,
      profileImage: true,
      password: true,
    };
    return isEmail
      ? await db.user.findUnique({
          where: {
            email: encrypt(usernameOrMail),
          },
          select,
        })
      : await db.user.findUnique({
          where: {
            username: usernameOrMail,
          },
          select,
        });
  },
  checkPassword: (user: User, password: string) => {
    return user.password === encrypt(password);
  },
  createUser: async (
    username: string,
    email: string,
    password: string
  ): Promise<User> => {
    return await db.user.create({
      data: {
        username,
        email: encrypt(email),
        password: encrypt(password),
      },
      select: {
        id: true,
        username: true,
        profileImage: true,
      },
    });
  },
};
