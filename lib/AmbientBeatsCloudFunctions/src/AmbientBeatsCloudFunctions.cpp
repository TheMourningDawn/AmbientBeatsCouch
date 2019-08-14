#ifndef AMBIENTBEATSCLOUDFUNCTIONS_CPP
#define AMBIENTBEATSCLOUDFUNCTIONS_CPP

#include "AmbientBeatsCloudFunctions.h"

LEDAnimations *ledAnimations;

AmbientBeatsCloudFunctions::AmbientBeatsCloudFunctions(LEDAnimations *animations) : ledAnimations(animations) {
    // Up to 15 cloud functions may be registered and each function name is limited to a maximum of 12 characters.
    Particle.function("toggle-audio-reactive", std::bind(&AmbientBeatsCloudFunctions::toggleAudioReactive, this, std::placeholders::_1));
    Particle.function("change-animation", std::bind(&AmbientBeatsCloudFunctions::changeAnimation, this, std::placeholders::_1));
    Particle.function("cycle-frequency", std::bind(&AmbientBeatsCloudFunctions::nextFrequency, this, std::placeholders::_1));

    Particle.function("set-hue", std::bind(&AmbientBeatsCloudFunctions::setHue, this, std::placeholders::_1));
    Particle.function("set-color", std::bind(&AmbientBeatsCloudFunctions::setColor, this, std::placeholders::_1));
    Particle.function("set-saturation", std::bind(&AmbientBeatsCloudFunctions::setSaturation, this, std::placeholders::_1));
    Particle.function("set-brightness", std::bind(&AmbientBeatsCloudFunctions::setBrightness, this, std::placeholders::_1));
    Particle.function("set-sensitivity", std::bind(&AmbientBeatsCloudFunctions::setSensitivity, this, std::placeholders::_1));
    Particle.function("set-animation", std::bind(&AmbientBeatsCloudFunctions::setAnimation, this, std::placeholders::_1));
    Particle.function("set-speed", std::bind(&AmbientBeatsCloudFunctions::setSpeed, this, std::placeholders::_1));

    Particle.function("reset-device", std::bind(&AmbientBeatsCloudFunctions::resetDevice, this, std::placeholders::_1));
    Particle.function("enter-safe-mode", std::bind(&AmbientBeatsCloudFunctions::enterSafeMode, this, std::placeholders::_1));
    Particle.function("power", std::bind(&AmbientBeatsCloudFunctions::power, this, std::placeholders::_1));
    Particle.function("pause", std::bind(&AmbientBeatsCloudFunctions::pause, this, std::placeholders::_1));

    Particle.variable("hue", &ledAnimations->hue, INT);
    Particle.variable("brightness", &ledAnimations->brightness, INT);
    Particle.variable("saturation", &ledAnimations->saturation, INT);
    Particle.variable("sensitivity", &ledAnimations->sensitivity, INT);
    Particle.variable("speed", &ledAnimations->speed, INT);
    Particle.variable("powered-on", ledAnimations->poweredOn);
    Particle.variable("animation", &ledAnimations->animation, INT);
    Particle.variable("audio-on", ledAnimations->audioReactiveOn);

    Particle.subscribe("ANIMATION",
                       std::bind(&AmbientBeatsCloudFunctions::handleAnimationEvent, this, std::placeholders::_1, std::placeholders::_2),
                       MY_DEVICES);
    Particle.subscribe("RESET",
                       std::bind(&AmbientBeatsCloudFunctions::handleResetEvent, this, std::placeholders::_1, std::placeholders::_2),
                       MY_DEVICES);
    Particle.subscribe("POWER",
                       std::bind(&AmbientBeatsCloudFunctions::handlePowerEvent, this, std::placeholders::_1, std::placeholders::_2),
                       MY_DEVICES);
    Particle.subscribe("AUDIO",
                       std::bind(&AmbientBeatsCloudFunctions::handleToggleAudioEvent, this, std::placeholders::_1, std::placeholders::_2),
                       MY_DEVICES);
}

/************************************
 Particle cloud function handlers
************************************/
int AmbientBeatsCloudFunctions::resetDevice(String arg) {
    System.reset();

    return 1;
}

int AmbientBeatsCloudFunctions::enterSafeMode(String arg) {
    System.enterSafeMode();

    return 1;
}

int AmbientBeatsCloudFunctions::power(String arg) {
    if(arg == "ON") {
        ledAnimations->poweredOn = true;
    } else if(arg == "OFF") {
        ledAnimations->poweredOn = false;
        ledAnimations->clearAllLeds();
        ledAnimations->show();
    } else {
        return -1;
    }

    return 1;
}


int AmbientBeatsCloudFunctions::pause(String arg) {
    ledAnimations->poweredOn = !ledAnimations->poweredOn;

    if (ledAnimations) {
        return 1;
    }

    return 0;
}

int AmbientBeatsCloudFunctions::toggleAudioReactive(String arg) {
    return ledAnimations->toggleAudioReactive();
}

int AmbientBeatsCloudFunctions::changeAnimation(String nextOrPrevious) {
    int animation;
    if(nextOrPrevious == "NEXT") {
        animation = ledAnimations->nextAnimation();
    } else if(nextOrPrevious == "PREVIOUS") {
        animation = ledAnimations->previousAnimation();
    } else {
        return -1;
    }
    Particle.publish("Animation #", String(animation));
    return animation;
}

int AmbientBeatsCloudFunctions::setAnimation(String animationNumber) {
    int animation = ledAnimations->setAnimation(animationNumber.toInt());
    Particle.publish("Animation #", String(animation));
    return animation;
}

int AmbientBeatsCloudFunctions::nextFrequency(String frequency) {
    int frequencyMode = ledAnimations->nextFrequencyMode();

    return frequencyMode;
}

int AmbientBeatsCloudFunctions::previousFrequency(String frequency) {
    int frequencyMode = ledAnimations->previousFrequencyMode();

    return frequencyMode;
}

//Expects rgb values to be in r,g,b format e.g. 140,200,90
int AmbientBeatsCloudFunctions::setColor(String rgbString) {
    char buffer[12];
    rgbString.toCharArray(buffer, 12);
    String r = "";
    String g = "";
    String b = "";

    int rgbItem = 0;
    for (int i = 0; i < 12; i++) {
        if (buffer[i] != ',') {
            if (rgbItem == 0) {
                r.concat(buffer[i]);
            } else if (rgbItem == 1) {
                g.concat(buffer[i]);
            } else if (rgbItem == 2) {
                b.concat(buffer[i]);
            }
        } else {
            rgbItem++;
        }
    }

    CRGB rgb = CRGB(r.toInt(), g.toInt(), b.toInt());
    CHSV hsv = rgb2hsv_approximate(rgb);

    ledAnimations->hue = hsv.hue;
    ledAnimations->saturation = hsv.sat;
    ledAnimations->brightness = hsv.val;

    return hsv.hue;
}

int AmbientBeatsCloudFunctions::setHue(String newHue) {
    ledAnimations->setHue(newHue.toInt());

    return ledAnimations->hue;
}

int AmbientBeatsCloudFunctions::setSaturation(String newSaturation) {
    ledAnimations->setSaturation(newSaturation.toInt());

    return ledAnimations->saturation;
}

int AmbientBeatsCloudFunctions::setBrightness(String newBrightness) {
    ledAnimations->setBrightness(newBrightness.toInt());

    return ledAnimations->brightness;
}

int AmbientBeatsCloudFunctions::setSensitivity(String newSensitivity) {
    ledAnimations->setSensitivity(newSensitivity.toInt());

    return ledAnimations->sensitivity;
}

int AmbientBeatsCloudFunctions::setSpeed(String newSpeed) {
    ledAnimations->setSpeed(newSpeed.toInt());

    return ledAnimations->speed;
}

/************************************
 Particle cloud event handlers
************************************/
void AmbientBeatsCloudFunctions::handleResetEvent(const char *eventName, const char *data) {
    resetDevice("");
}

void AmbientBeatsCloudFunctions::handleAnimationEvent(const char *eventName, const char *data) {
    if (strcmp(eventName, "ANIMATION_NEXT") == 0) {
        changeAnimation("NEXT");
    } else if (strcmp(eventName, "ANIMATION_PREVIOUS") == 0) {
        changeAnimation("PREVIOUS");
    }
}

void AmbientBeatsCloudFunctions::handlePowerEvent(const char *eventName, const char *data) {
    if (strcmp(eventName, "POWER_ON") == 0) {
        power("ON");
    } else if (strcmp(eventName, "POWER_OFF") == 0) {
        power("OFF");
    }
}

void AmbientBeatsCloudFunctions::handleToggleAudioEvent(const char *eventName, const char *data) {
    toggleAudioReactive("");
}

#endif
