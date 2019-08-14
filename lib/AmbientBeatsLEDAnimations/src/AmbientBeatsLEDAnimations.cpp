#ifndef AMBIENTBEATSLEDANIMATIONS_CPP
#define AMBIENTBEATSLEDANIMATIONS_CPP

#include "application.h"
#include "AmbientBeatsLEDAnimations.h"

SpectrumEqualizerClient *equalizer;

AmbientBeatsLEDAnimations::AmbientBeatsLEDAnimations(SpectrumEqualizerClient *eq) : equalizer(eq) { }

void AmbientBeatsLEDAnimations::show() {
    FastLED.show();
}

int AmbientBeatsLEDAnimations::nextAnimation() {
    animation++;
    animation = wrapToRange(animation, 0, animationCount-1);
    clearAllLeds();
    return animation;
}

int AmbientBeatsLEDAnimations::previousAnimation() {
    animation--;
    animation = wrapToRange(animation, 0, animationCount-1);
    clearAllLeds();
    return animation;
}

int AmbientBeatsLEDAnimations::setAnimation(int animationNumber) {
    animation = wrapToRange(animationNumber, 0, animationCount-1);
    clearAllLeds();
    return animation;
}

int AmbientBeatsLEDAnimations::getAnimation() {
    return animation;
}

void AmbientBeatsLEDAnimations::setHue(int newHue) {
    hue = newHue;
}

void AmbientBeatsLEDAnimations::setBrightness(int newBrightness) {
    brightness = newBrightness;
}

void AmbientBeatsLEDAnimations::setSaturation(int newSaturation) {
    saturation = newSaturation;
}

void AmbientBeatsLEDAnimations::setSensitivity(int newSensitivity) {
    sensitivity = newSensitivity;
}

void AmbientBeatsLEDAnimations::setSpeed(int newSpeed) {
    speed = newSpeed;
}

int AmbientBeatsLEDAnimations::nextFrequencyMode() {
    int wrapEnd = frequencyMode[6];
    for (int i = 6; i > 0; i--) {
        frequencyMode[i] = frequencyMode[i - 1];
    }
    frequencyMode[0] = wrapEnd;

    return wrapEnd;
}

int AmbientBeatsLEDAnimations::previousFrequencyMode() {
    int wrapBegining = frequencyMode[0];
    for (int i = 0; i < 6; i++) {
        frequencyMode[i] = frequencyMode[i + 1];
    }
    frequencyMode[6] = wrapBegining;

    return wrapBegining;
}

int AmbientBeatsLEDAnimations::clampToRange(int numberToClamp, int lowerBound, int upperBound) {
    if (numberToClamp > upperBound) {
        return upperBound;
    } else if (numberToClamp < lowerBound) {
        return lowerBound;
    }
    return numberToClamp;
}

int AmbientBeatsLEDAnimations::clampSensitivity(int sensitivity) {
    return clampToRange(sensitivity, 0, 4096);
}

int AmbientBeatsLEDAnimations::wrapToRange(int numberToWrap, int lowerBound, int upperBound) {
    if (numberToWrap > upperBound) {
        return lowerBound;
    } else if (numberToWrap < lowerBound) {
        return upperBound;
    }
    return numberToWrap;
}

#endif
