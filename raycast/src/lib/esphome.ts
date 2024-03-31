import fetch, { RequestInfo } from "node-fetch";

export class ESPhome {
    constructor(
      private config: {
        instance: string;
        timeoutMs?: number;
      },
    ) {}

    private async post(path: URL | RequestInfo) {
      const url = `http://${this.config.instance}${path}`;

      console.debug(`POST ${url}`);

      const response = await fetch(url, {
        method: "post",
        signal: this.config.timeoutMs ? AbortSignal.timeout(1000) : undefined,
      });

      return response;
    }

    get button() {
      return {
        press: async (id: string) => {
          return this.post(`/button/${id}/press`);
        },
      };
    }
  }
