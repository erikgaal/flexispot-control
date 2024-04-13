#include <vector>
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace flexispot {

enum FrameState {
  START = 0,
  LENTGH,
  TYPE,
  DATA,
  CHECKSUM,
  END,
};

struct Frame {
  uint8_t type;
  uint8_t length;
  std::vector<uint8_t> data;
};

class FlexispotComponent : public Component, public sensor::Sensor, public uart::UARTDevice {
  public:
    void setup() override;
    void loop() override;
    void dump_config() override;

  protected:
    uint8_t length;
    uint8_t type;
    std::vector<uint8_t> buffer{};
    FrameState framestate;
    float height;
    void handle_frame(Frame *frame);
    void handle_height_frame(Frame *frame);
    char parse_seven_segment_digit(uint8_t byte);
};


} // namespace flexispot
} // namespace esphome
