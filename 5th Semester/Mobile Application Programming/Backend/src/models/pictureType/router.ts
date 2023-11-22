import express from "express";
import pictureTypeService from "./service";

export const pictureTypeRouter = express.Router();

// GET pictureTypes/
pictureTypeRouter.get("/", async (req, res) => {
  try {
    const pictureTypes = await pictureTypeService.findAll();
    res.status(200).send(pictureTypes);
  } catch (err: any) {
    res.status(500).send(err.message);
  }
});
