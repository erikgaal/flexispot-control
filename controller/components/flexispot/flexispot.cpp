#include <vector>
#include "flexispot.h"
#include "esphome/core/log.h"

namespace esphome {
namespace flexispot {

static const char *const TAG = "flexispot";

const uint8_t FLEXISPOT_START_BYTE = 0x9b;

void FlexispotComponent::setup() {
    this->framestate = FrameState::START;
};

void FlexispotComponent::loop() {
    int count = 32;

    while (available() && count--) {
        uint8_t byte;

        read_byte(&byte);

        switch (framestate) {
            case FrameState::START:
                if (byte == FLEXISPOT_START_BYTE) {
                    framestate = FrameState::LENTGH;
                    buffer.clear();
                }

                break;

            case FrameState::LENTGH:
                length = byte;
                framestate = FrameState::TYPE;

                break;

            case FrameState::TYPE:
                type = byte;
                framestate = FrameState::DATA;

                break;

            case FrameState::DATA:
                buffer.push_back(byte);

                if (buffer.size() >= length - 1) {
                    framestate = FrameState::START;

                    Frame frame;
                    frame.type = type;
                    frame.length = length;
                    frame.data = buffer;

                    handle_frame(&frame);

                    framestate = FrameState::START;
                }

                break;
        }
    }
};

void FlexispotComponent::dump_config() {
    LOG_SENSOR("", "Flexispot", this);
};

void FlexispotComponent::handle_frame(Frame *frame) {
    // ESP_LOGD(TAG, "Incoming frame:");
    // ESP_LOGD(TAG, "type:   %02x", frame->type);
    // ESP_LOGD(TAG, "length: %d", frame->length);
    // ESP_LOGD(TAG, "data:   %s", uart::UARTDebug::log_hex(frame->data, ' ').c_str());

    switch (frame->type) {
        case 0x12:
            handle_height_frame(frame);
            break;
        default:
            break;
    }
};

void FlexispotComponent::handle_height_frame(Frame *frame) {
    if (frame->data[0] == 0x00) {
        return;
    }

    uint8_t digit1 = parse_seven_segment_digit(frame->data[0]);
    uint8_t digit2 = parse_seven_segment_digit(frame->data[1]);
    bool dot = (frame->data[1] & 0x80) > 0;
    uint8_t digit3 = parse_seven_segment_digit(frame->data[2]);

    float height = (digit1 * 100 + digit2 * 10 + digit3);

    if (digit1 == 0) {
        return;
    }

    if (dot) {
        height = height / 10;
    }

    if (this->height != height) {
        this->height = height;
        publish_state(height);
    }

    // ESP_LOGD(TAG, "Received height frame: %.1f", height);
};

char FlexispotComponent::parse_seven_segment_digit(uint8_t byte)
{
    switch (byte & 0x7f) {
        case 0x3f:
            return 0;
        case 0x06:
            return 1;
        case 0x5b:
            return 2;
        case 0x4f:
            return 3;
        case 0x66:
            return 4;
        case 0x6d:
            return 5;
        case 0x7d:
            return 6;
        case 0x07:
            return 7;
        case 0x7f:
            return 8;
        case 0x6f:
            return 9;
        default:
            return 0;
    }
}

} // namespace flexispot
} // namespace esphome
