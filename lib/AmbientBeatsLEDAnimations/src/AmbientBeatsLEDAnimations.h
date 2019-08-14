#ifndef AMBIENTBEATSLEDANIMATIONS_H
#define AMBIENTBEATSLEDANIMATIONS_H

#include "application.h"
#include "SpectrumEqualizerClient.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE;

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


class AmbientBeatsLEDAnimations
{
  public:
    SpectrumEqualizerClient *equalizer;
    bool poweredOn = true;
    bool audioReactiveOn = false;

    int animationCount;
    int animation = 1;
    int hue = 120;
    int brightness = 255;
    int saturation = 255;
    int speed = 0;
    int sensitivity = 720;

    uint8_t frequencyMode[7] = {0, 1, 2, 3, 4, 5, 6};

    AmbientBeatsLEDAnimations(SpectrumEqualizerClient* eq);

    void show();

    void setHue(int newHue);
    void setBrightness(int newBrightness);
    void setSaturation(int newSaturation);
    void setSensitivity(int newSensitivity);
    void setSpeed(int newSpeed);

    int getAnimation();
    int nextAnimation();
    int previousAnimation();
    int setAnimation(int animationNumber);
    int nextFrequencyMode();

    int previousFrequencyMode();

    virtual int runAnimation() = 0;
    virtual int toggleAudioReactive() = 0;
    virtual void clearAllLeds() = 0;
    virtual void fillColor() = 0;


    int clampToRange(int numberToClamp, int lowerBound, int upperBound);
    int clampSensitivity(int sensitivity);
    int wrapToRange(int numberToWrap, int lowerBound, int upperBound);
};

#endif
