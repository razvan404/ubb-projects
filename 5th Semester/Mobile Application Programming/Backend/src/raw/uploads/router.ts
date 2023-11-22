import express from "express";
import fs from "fs";
import uploadsService from "./service";

export const uploadsRouter = express.Router();

// GET /uploads/:file
uploadsRouter.get("/:file", async (req, res) => {
  const file = req.params.file;
  const filePath = uploadsService.getPath(file);
  if (fs.existsSync(filePath)) {
    res.setHeader("Content-Type", "image/jpeg");
    fs.createReadStream(filePath).pipe(res);
  } else {
    res.sendStatus(404);
  }
});

uploadsRouter.get("/:file/download", async (req, res) => {
  const file = req.params.file;
  const filePath = uploadsService.getPath(file);
  if (fs.existsSync(filePath)) {
    res.download(filePath);
  } else {
    res.sendStatus(404);
  }
});
