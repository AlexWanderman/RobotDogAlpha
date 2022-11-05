#pragma once

#include <vector>
#include <Arduino.h>
#include "../model/command.hpp"
#include "../model/model.hpp"
#include <PS4Controller.h>
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include"esp_gap_bt_api.h"
#include "esp_err.h"

#define MAC_PS4_JOYSTICK "c0:e4:34:4f:b0:4d"

class ClickableButton {
private:
    bool __state = false;
    bool __buttonPressed = false;
public:
    bool state() {
        return __state;
    }

    bool press() {
        if (!__buttonPressed) {
            __state = true;
            __buttonPressed = true;
        }
        else {
            __state = false;
        }

        return __state;
    }

    bool release() {
        __state = false;
        __buttonPressed = false;

        return false;
    }

    bool turn(bool direction) {
        return direction ? this->press() : this->release();
    }
};

class ButtonWithState {
private:
	bool __state;
	bool __buttonPressed = false;
public:
    ButtonWithState(bool state = false) {
        this->__state = state;
    }

	bool state() {
		return __state;
	}

	bool turn(bool direction) {
        if (direction) {
            if (!__buttonPressed)
            {
                __state = !__state;
            }
            __buttonPressed = true;
        }
        else {
            __buttonPressed = false;
        }

        return __state;
	}
};

class JoystickController
{
public:
    JoystickController() {};
    void loop();
private:
    void cleanPairedDevices();
    char *bda2str(const uint8_t* bda, char *str, size_t size);
    bool initBluetooth();
};
