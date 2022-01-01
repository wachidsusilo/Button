#include "Button.h"

ArrayList<Button*> Button::buttons = ArrayList<Button*>();
boolean Button::registered = false;
uint32_t Button::uid = 0;

Button::Button()
    : id(0), counter(0), pullup(true), flag(false), pressCallback(NULL), longCallback(NULL), releaseCallback(NULL) {}

Button::Button(uint8_t pin) : Button() {
    this->pin = pin;
}

Button::~Button() {
    uid = id;
    buttons.removeIf([](Button* b) -> bool { return b->id == uid; });
    Serial.println("Destroyed");
}

void Button::begin(bool pullup) {
    this->pullup = pullup;
    pinMode(pin, pullup ? INPUT_PULLUP : INPUT);
    uid = millis();
    while (buttons.contains([](Button* b) -> bool { return b->id == uid; })) uid++;
    id = uid;
    if (!buttons.contains([](Button* b) -> bool { return b->id == uid; })) {
        buttons.add(this);
    }
    if (!registered) {
        registered = true;
        Timer.setInterval(run, 100);
    }
}

bool Button::read() {
    return pullup ? !digitalRead(pin) : digitalRead(pin);
}

void Button::onPress(Callback callback) {
    this->pressCallback = callback;
}

void Button::onLongPress(Callback callback) {
    this->longCallback = callback;
}

void Button::onRelease(Callback callback) {
    this->releaseCallback = callback;
}

void Button::pollEvent() {
    if (read()) {
        if (!flag) {
            flag = true;
            counter = millis();
            if (pressCallback) pressCallback();
        } else {
            if (!longFlag) {
                if (millis() - counter < 700) return;
                if (longCallback) longCallback();
            }
        }
    } else {
        if (flag) {
            flag = false;
            longFlag = false;
            if (releaseCallback) releaseCallback();
        }
    }
}

void Button::run() {
    buttons.forEach([](Button* b, size_t) -> bool {
        if (b) b->pollEvent();
        return true;
    });
}
