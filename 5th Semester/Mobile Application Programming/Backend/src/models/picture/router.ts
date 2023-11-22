import express from "express";
import pictureService from "./service";
import { authenticateToken, userFromAuthenticatedRequest } from "../../auth";
import { queryParamsToDict } from "../../utils/linkOps";
import { PictureMini } from "./types";

export const pictureRouter = express.Router();

// GET pictures/
pictureRouter.get("/", async (req, res) => {
  try {
    const { skip, take, ...filterAttributes } = req.query;
    let pictures: PictureMini[];
    if (skip && take) {
      pictures = await pictureService.findAll(
        queryParamsToDict(filterAttributes as any),
        parseInt(skip as string),
        parseInt(take as string)
      );
    } else {
      pictures = await pictureService.findAll(
        queryParamsToDict(filterAttributes as any)
      );
    }
    res.status(200).send(pictures);
  } catch (err: any) {
    res.status(500).send(err.message);
  }
});

// GET pictures/:id
pictureRouter.get("/:id", async (req, res) => {
  try {
    const picture = await pictureService.findById(req.params.id);
    res.status(200).send(picture);
  } catch (err: any) {
    res.status(500).send(err.message);
  }
});

// POST pictures/
pictureRouter.post("/", authenticateToken, async (req, res) => {
  try {
    const picture = await pictureService.create({
      ...req.body,
      userId: userFromAuthenticatedRequest(req).id,
    });
    res.status(200).send(picture);
  } catch (err: any) {
    res.status(500).send(err.message);
  }
});

// PUT pictures/
pictureRouter.put("/:id", authenticateToken, async (req, res) => {
  try {
    const picture = await pictureService.update({
      ...req.body,
      id: req.params.id,
      userId: userFromAuthenticatedRequest(req).id,
    });
    res.status(200).send(picture);
  } catch (err: any) {
    res.status(500).send(err.message);
  }
});

pictureRouter.delete("/:id", authenticateToken, async (req, res) => {
  try {
    await pictureService.delete(
      req.params.id,
      userFromAuthenticatedRequest(req).id as string
    );
    res.sendStatus(200);
  } catch (err: any) {
    res.status(500).send(err.message);
  }
});
