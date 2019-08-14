#ifndef SPECTRUMEQUALIZERCLIENT_H
#define SPECTRUMEQUALIZERCLIENT_H

#include "application.h"

class SpectrumEqualizerClient {
public:
    SpectrumEqualizerClient();
    UDP multicastUDP;
    int port;
    IPAddress remoteIP;

    int frequenciesLeftChannel[7];
    int frequenciesRightChannel[7];

    void readAudioFrequencies();
};

#endif
