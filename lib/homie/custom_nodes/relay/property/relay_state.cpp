#include "relay_state.h"

#include "file_system.h"

RelayState::RelayState(const char* name, const char* id, Node* node, PROPERTY_TYPE type, bool settable, bool retained,
                       const char* data_type, uint8_t relay_pin, uint8_t button_pin = 255)
    : Property(name, id, node, type, settable, retained, data_type) {
    relay_pin_ = relay_pin;
    if (button_pin != 255) {
        button_ = new Button(button_pin, kDebounce);
        button_->begin();
    }

    pinMode(relay_pin_, OUTPUT);
}

bool RelayState::Init(Homie* homie) {  // initialize toggles for notification
    bool status = true;
    if (!Property::Init(homie)) status = false;
    SetValue(value_ == "true" ? "true" : "false");
    return status;
}

void RelayState::HandleCurrentState() {
    if (button_ != nullptr)
        if (button_->pressed()) SetValue(value_ == "true" ? "false" : "true");
}

void RelayState::HandleSettingNewValue() {
    Serial.println(value_ == "true" ? "Relay on" : "Relay off");
    digitalWrite(relay_pin_, value_ == "true");

    Device* device = node_->GetDevice();
    bool is_sys_notif_enabled = device->IsSysNotifyEnabled();
    if (is_sys_notif_enabled) device->SendNotification(value_ == "true" ? "Relay on" : "Relay off");
}
