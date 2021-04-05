#include "MQ135.h"

MQ135::MQ135(uint8_t pin) {
  this->pin = pin;
  pinMode(pin, INPUT);
}

double MQ135::getVoltage() {
    return (double)analogRead(pin) * VStep;
}

double MQ135::getResistance() {
    double voltage = getVoltage();
    double rs = ((VIn * RL) / voltage) - RL;
    if (rs < 0) {
        rs = 0;
    }
    return rs;
}

double MQ135::getPPM(float a, float b) {
    double ratio = getResistance() / R0;
    double ppm = a * pow(ratio, b);
    if (ppm < 0) {
        ppm = 0;
    }
    return ppm;
}

double MQ135::getPPMLinear(float a, float b) {
    double ratio = getResistance() / R0;
    double ppm_log = (log10(ratio) - b) / a;
    double ppm = pow(10, ppm_log);
    if (ppm < 0) {
        ppm = 0;
    }
    return ppm;
}

double MQ135::getAcetona() {
    return getPPM(34.668, -3.369);
}

double MQ135::getAlcohol() {
    return getPPM(77.255, -3.18);
}

double MQ135::getCO2() {
    // return getPPMLinear(-0.3525, 0.7142) + ATMOCO2;
    return getPPM(110.47, -2.862) + ATMOCO2;
}

double MQ135::getCO() {
    return getPPM(605.18, -3.937);
}

double MQ135::getNH4() {
    return getPPM(102.2, -2.473);
}

double MQ135::getTolueno() {
    return getPPM(44.947, -3.445);
}

float MQ135::getR0() {
    double r0 = getResistance() / 3.6;
    return r0;
}

double MQ135::getR0ByCO2Level(float ppm) {
    if (ppm > ATMOCO2) {
        ppm -= ATMOCO2;
    }
    else {
        return NAN;
    }
    double tmp = -(log10(ppm / 110.47) / -2.862) + log10(getResistance());
    return pow(10, tmp);
}

void MQ135::setR0(float r0) {
    R0 = r0;
}
