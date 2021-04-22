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

//Correction Values
#define CorrA -0.000002469136
#define CorrB 0.00048148148
#define CorrC 0.0274074074
#define CorrD 1.37530864197
#define CorrE 0.0019230769

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
  float getCorrectedR0(float temparature, float humidity);
  /// Get R0 in custom conditions for calibration purposes.
  /// Can be used, if you know the current CO2 Level.
  double getR0ByCO2Level(float ppm);
  double getCorrectedR0ByCO2Level(float ppm, float temparature, float humidity);
  /// Set R0 Value for calibration.
  void setR0(float r0);

  /// Gets the resolved sensor voltage
  double getVoltage();

  /// Calculate Correction Factor depending on temparature and humidity
  double getCorrectionFactor(float temparature, float humidity);
  
  /// Calculates the Resistance of the Sensor
  double getResistance();
  double getCorrectedResistance(float temparature, float humidity);
  /// Calculates ppm on a exponential curve
  /// (Different Gases have different curves)
  double getPPM(float a, float b);
  double getCorrectedPPM(float a, float b, float temparature, float humidity);
  /// Calculates ppm on a linear curve
  /// (Different Gases have different curves)
  double getPPMLinear(float a, float b);

  /// Gets ppm of Acetona in Air (C3H6O)
  double getAcetona();
  double getCorrectedAcetona(float temparature, float humidity);
  /// Gets ppm of Alcohol in Air
  double getAlcohol();
  double getCorrectedAlcohol(float temparature, float humidity);
  /// Gets ppm of CO in Air
  double getCO();
  double getCorrectedCO(float temparature, float humidit);
  /// Gets ppm of CO2 in Air
  double getCO2();
  double getCorrectedCO2(float temparature, float humidit);
  /// Gets ppm of NH4 in Air
  double getNH4();
  double getCorrectedNH4(float temparature, float humidit);
  /// Gets ppm of Tolueno in Air (CH3)
  double getTolueno();
  double getCorrectedTolueno(float temparature, float humidit);
};
#endif
