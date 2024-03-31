import { showHUD } from "@raycast/api";
import { Flexispot } from "./lib/flexispot";

export default async () => {
  try {
    await Flexispot.stand();
    await showHUD("Desk set to standing");
  } catch (e) {
    await showHUD("Failed to control desk");
  }
};
