#ifndef LEDANIMATIONS_H
#define LEDANIMATIONS_H

#include "application.h"
#include "SpectrumEqualizerClient.h"
#include "AmbientBeatsLEDAnimations.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE;

#define NUM_LEDS 326 //381 w/ the peice that broke off :|

class LEDAnimations : public AmbientBeatsLEDAnimations
{
public:
    LEDAnimations(SpectrumEqualizerClient* eq);

    CRGB leds[NUM_LEDS];

    int runAnimation();
    int toggleAudioReactive();

    void clearAllLeds();
    void fillColor();

    void randomSilon();
    void rainbow();
    void rainbowSlide();
    void confetti();
    void sinelon();
    void bpm();
    void juggle();

    void waterfall();
    void waterfallRainbowBorder();

    void equalizerAnimation();
    void equalizerLeft(int frequencyValue);
    void equalizerRight(int frequencyValue);
};

#endif
