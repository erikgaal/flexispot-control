import { showHUD } from "@raycast/api";
import { Flexispot } from "./lib/flexispot";

export default async () => {
  try {
    await Flexispot.sit();
    await showHUD("Desk set to sitting");
  } catch (e) {
    await showHUD("Failed to control desk");
  }
};
