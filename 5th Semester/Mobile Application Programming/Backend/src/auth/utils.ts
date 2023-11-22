import { Request, Response, NextFunction } from "express";
import jwt from "jsonwebtoken";
import { User } from "../models/user";

const jwtSecret = process.env.JWT_SECRET;

export const createToken = (user: User) => {
  return jwt.sign(
    { id: user.id, username: user.username, profileImage: user.profileImage },
    jwtSecret ?? "",
    { expiresIn: "3h" }
  );
};

export const userFromJWT = (token: string): User => {
  const { iat, exp, ...userResponse } = jwt.verify(
    token,
    process.env.JWT_SECRET as string
  ) as any;
  return userResponse;
};

export const authenticateToken = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  const authHeader = req.headers["authorization"];
  const token = authHeader && authHeader.split(" ")[1];

  if (token == null) return res.sendStatus(401);

  jwt.verify(token, process.env.JWT_SECRET as string, (err: any, user: any) => {
    if (err) {
      return res.sendStatus(403);
    }
    (req as any).user = user;
    next();
  });
};

export const userFromAuthenticatedRequest = (req: Request): User => {
  const { iat, exp, ...userResponse } = (req as any).user;
  return userResponse;
};
