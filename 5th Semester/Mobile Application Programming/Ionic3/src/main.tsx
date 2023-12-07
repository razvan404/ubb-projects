import * as dotenv from "dotenv";
import { createRoot } from "react-dom/client";
import { defineCustomElements } from "@ionic/pwa-elements/loader";
import App from "./app";

defineCustomElements(window);
const container = document.getElementById("root");
const root = createRoot(container!);
root.render(<App />);
