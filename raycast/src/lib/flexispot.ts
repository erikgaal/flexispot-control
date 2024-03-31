import { getPreferenceValues } from "@raycast/api";
import { ESPhome } from "./esphome";

function createFlexispotClient(): FlexispotClient {
  const preferences = getPreferenceValues();
  const instance = preferences.instance as string;

  return new FlexispotClient(instance);
}

class FlexispotClient {
  private esphome: ESPhome;
  constructor(instance: string) {
    this.esphome = new ESPhome({
      instance,
      timeoutMs: 1000,
    });
  }

  preset1 = async () => this.esphome.button.press("preset1");
  preset2 = async () => this.esphome.button.press("preset2");
  stand = async () => this.esphome.button.press("stand");
  sit = async () => this.esphome.button.press("stand");
}


export const Flexispot = createFlexispotClient();
