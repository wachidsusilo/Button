#ifndef BUTTON_H
#define BUTTON_H

#if defined(ESP32) || defined(ESP8266)
#include <functional>
#endif

#include "Arduino.h"
#include "Timer.h"

class Button {
   public:
#if defined(ESP32) || defined(ESP8266)
    using Callback = std::function<void()>;
#else
    using Callback = void (*)();
#endif
    Button();
    Button(uint8_t pin);
    ~Button();
    void begin(bool pullup = true);
    bool read();
    void onPress(Callback callback);
    void onLongPress(Callback callback);
    void onRelease(Callback callback);
    void pollEvent();

   private:
    uint32_t id;
    uint32_t counter;
    uint8_t pin;
    bool pullup;
    bool flag;
    bool longFlag;

    Callback pressCallback;
    Callback longCallback;
    Callback releaseCallback;

    static ArrayList<Button*> buttons;
    static boolean registered;
    static uint32_t uid;
    static void run();
};

#endif
