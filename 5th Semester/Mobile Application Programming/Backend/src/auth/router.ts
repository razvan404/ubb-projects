import express from "express";
import {
  createToken,
  authenticateToken,
  userFromAuthenticatedRequest,
} from "./utils";
import userService from "../models/user/service";

export const authRouter = express.Router();

// POST auth/login
authRouter.post("/login", async (req, res) => {
  try {
    const { usernameOrEmail, password } = req.body;
    console.log(usernameOrEmail, password);
    const user = await userService.findByUsernameOrMail(usernameOrEmail);
    console.log(user);
    if (!user) {
      return res.sendStatus(404);
    }
    if (!userService.checkPassword(user, password)) {
      return res.sendStatus(401);
    }
    const token = createToken(user);
    const { password: _, ...userResponse } = user;
    console.log(userResponse);
    res.status(200).send({ token, user: userResponse });
  } catch (err: any) {
    res.status(500).send(err.message);
  }
});

// POST auth/register
authRouter.post("/register", async (req, res) => {
  try {
    const { username, email, password } = req.body;
    const user = await userService.createUser(username, email, password);
    const token = createToken(user);
    res.status(200).send({ token, user });
  } catch (err: any) {
    res.status(500).send(err.message);
  }
});

// GET auth/me
authRouter.get("/me", authenticateToken, async (req, res) => {
  return res.status(200).send(userFromAuthenticatedRequest(req));
});
