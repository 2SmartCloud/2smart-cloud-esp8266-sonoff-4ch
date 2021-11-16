#pragma once

#define EB_HOLD 10000  // таймаут удержания кнопки

#include <Arduino.h>
#include <Button.h>

#include <map>
#include <string>

#include "property/property.h"

class RelayState : public Property {
 public:
    RelayState(const char* name, const char* id, Node* node, PROPERTY_TYPE type, bool settable, bool retained,
               const char* data_type, uint8_t relay_pin, uint8_t button_pin);

    bool Init(Homie* homie) override;

    void HandleCurrentState() override;

    void HandleSettingNewValue() override;

 private:
    //  EncButton<EB_TICK, 0> button_;  // esp32 13 //sonoff 0

    Button* button_ = nullptr;

    uint8_t relay_pin_ = 255;  // esp32 4 // sonoff 12
    uint8_t kDebounce = 30;

    uint32_t period_loop_ = millis();
};
