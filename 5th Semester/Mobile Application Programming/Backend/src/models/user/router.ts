import express from "express";
import userService from "./service";

export const userRouter = express.Router();

// GET users/
userRouter.get("/", async (_, res) => {
  try {
    const users = await userService.findAll();
    res.status(200).send(users);
  } catch (err: any) {
    res.status(500).send(err.message);
  }
});

// GET users/:id
userRouter.get("/:id", async (req, res) => {
  try {
    const user = await userService.findById(req.params.id);
    if (!user) {
      return res.sendStatus(404);
    }
    res.status(200).send(user);
  } catch (err: any) {
    res.status(500).send(err.message);
  }
});
