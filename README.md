# Flexispot

Library of programs and designs to control a Flexispot desk.

## Controller

### Development

Using the [Wokwi Simulator VS Code extension](https://marketplace.visualstudio.com/items?itemName=wokwi.wokwi-vscode) we can simulate the system without a need for the components.

First we need to compile the ESPhome firmware. Be sure to provide the `secrets.yaml`, for simulated development a copy of `secrets.yaml.example` is sufficient.

```sh
esphome compile flexispot.yml
```

After compilation of the firmware we can open `diagram.json` in VS Code and run the simulation from there. By default, a webserver will start on `localhost:8180` with controls.
