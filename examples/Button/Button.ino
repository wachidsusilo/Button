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
