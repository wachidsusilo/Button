## Button for Arduino
A simple button library for arduino. This library rely on [Timer](https://github.com/wachidsusilo/Timer) and [ArrayList](https://github.com/wachidsusilo/ArrayList) libraries. You can download or clone it from my repository

## Example
This library provide easy implementation of `onPress`, `onLongPress`, and `onReleased` event. 
```c++
#include "Button.h"

Button button(2);

void onPressed() {
    Serial.println("Button pressed");
}

void onLongPressed() {
    Serial.println("Button long pressed");
}

void onReleased() {
    Serial.println("Button released");
}

void setup() {
    Serial.begin(115200);

    //true means INPUT_PULLUP
    button.begin(true);

    //Assign onPressCallback with onPressed() function
    button.onPress(onPressed);

    //Assign onLongPressCallback with onLongPressed() function
    button.onLongPress(onLongPressed);

    //Assign onReleaseCallback with onreleased() function
    button.onRelease(onReleased);
}

void loop() {
    Timer.run();
}
```