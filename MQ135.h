#ifndef MQ135_H
#define MQ135_H

#include "Arduino.h"

/// Resistor on Sensor in kΩ
#define RL 10

/// Voltage on Sensor in V
#define VIn 5

/// Board analog Input Resolution
/// Default: 2^10
#define Resolution 1024

/// CO2 Level in Atmosphere
#define ATMOCO2 397.13

/// Helper to calculate Voltage from Input
/// Voltage = input * Vin / (Resolution - 1)
const double VStep = (double)VIn / (Resolution - 1);

class MQ135 {
 private:
  /// input pin
  uint8_t pin;
  /// calibration Resistance
  float R0;

 public:
  /// Constructor with analog input Pin
  MQ135(uint8_t pin);
  /// Get R0 in default conditions for calibration purposes.
  /// Assume CO2 Level is the default Atmospheric Level (~400ppm)
  float getR0();
  /// Get R0 in custom conditions for calibration purposes.
  /// Can be used, if you know the current CO2 Level.
  double getR0ByCO2Level(float ppm);
  /// Set R0 Value for calibration.
  void setR0(float r0);
  
  /// Gets the resolved sensor voltage
  double getVoltage();
  /// Calculates the Resistance of the Sensor
  double getResistance();
  /// Calculates ppm on a exponential curve
  /// (Different Gases have different curves)
  double getPPM(float a, float b);
  /// Calculates ppm on a linear curve
  /// (Different Gases have different curves)
  double getPPMLinear(float a, float b);

  /// Gets ppm of Acetona in Air (C3H6O)
  double getAcetona();
  /// Gets ppm of Alcohol in Air
  double getAlcohol();
  /// Gets ppm of CO in Air
  double getCO();
  /// Gets ppm of CO2 in Air
  double getCO2();
  /// Gets ppm of NH4 in Air
  double getNH4();
  /// Gets ppm of Tolueno in Air (CH3)
  double getTolueno();
};
#endif
