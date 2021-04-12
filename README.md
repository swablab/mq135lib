# MQ135 Library

Arduino Library for MQ135 Sensor

## Learn more
* [https://jayconsystems.com/blog/understanding-a-gas-sensor](https://jayconsystems.com/blog/understanding-a-gas-sensor)

    Basic understanding of an Air-Quality Sensor
* [https://github.com/miguel5612/MQSensorsLib](https://github.com/miguel5612/MQSensorsLib)

    Another MQ135 Library
* [https://github.com/GeorgK/MQ135](https://github.com/GeorgK/MQ135)
  
    Another MQ135 Library

## How does this work?
First we need to calculate the actual voltage from our sensor. The value we read by ``analogRead`` is just a value mapped to 2^10 bits.

Since we are running our sensor at 5V, a measured value of 1023 equals 5V and the measured value 0 equals 0V. We convert this with the following formula:

```
// x is our measured value
voltage = x * 5 / 1023
// or
voltage = 5x / 1023
```

Next we can calculate the resistance of the sensor.
For more details should be looked up in this article: [https://jayconsystems.com/blog/understanding-a-gas-sensor]()

```
V = I x R 
VRL = [VC / (RS + RL)] x RL 
VRL = (VC x RL) / (RS + RL) 

So now we solve for RS: 

VRL x (RS + RL) = VC x RL
(VRL x RS) + (VRL x RL) = VC x RL 
(VRL x RS) = (VC x RL) - (VRL x RL)
RS = [(VC x RL) - (VRL x RL)] / VRL
RS = [(VC x RL) / VRL] - RL
```

To calculate the gas content in the air from the resistance we use the values from [https://github.com/miguel5612/MQSensorsLib](https://github.com/miguel5612/MQSensorsLib)
