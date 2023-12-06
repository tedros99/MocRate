# MocRate: A Portable Pulse Oximeter
Detecting a patient’s heart rate and oxygen is a very common practice in the medical world. Due to this, a solution for a portable and user friendly monitor for efficient use is crucial.  In this project, we have designed and deployed a battery-powered and portable sensor that can quickly get an individuals heart rate by them simply placing their finger into a clip that measure their heart rate and oxygen levels and provide them that information quickly and clearly.

## Components
1. SparkFun Pulse Oximeter and Heart Rate Sensor -MAX30101 & MAX32664 (~42.50 USD)
2. Arduino Uno Rev3 (~25.29 USD)
3. AA Batteries (~3.00 USD)
4. AA Battery Holder (~6.48 USD for 6)
5. Waveshare 4.2inch E-Ink Display (~34.99 USD)
6. Power Button (~2.00 USD)
7. 3D Printed Chassis (Price Varies)

## Methods and Overviews
Creating the contraption was fairly straightforward, especially with the choice of parts. Using the Arduino UNO and its companion application, Arduino IDE, we were able to program the calculation of the sensor efficiently. The SparkFun Sensor family has pre-built libraries that translate the pulse oximeter’s signals to readable numbers. In addition to this, the libraries allowed us to print whether or not the user is correctly using the tool. Whilst the patient is interacting with the machine, the following statuses may be displayed:

NO OBJ - The tool does not detect anything.
OBJ DETECTED - The sensor detects the touch of an object.
NOT FINGER - The object detected is not a human finger.
MEASURING - The finger is successfully detected and is being measured.
UNKNOWN - Internal error, should almost never occur.

## Results and Conclusions
After thorough testing, we can comfortably say that the final product is sufficiently accurate and suitable for commercial and personal use. In comparison to our reference device, the margin of error for heart rate and blood oxygen was only ±1 BPM and ±1%, respectively.

Additionally, we noticed that in order for the patient to successfully get their results, they need to place the bottom of their fingers flat on the sensor; the fingertip does not suffice.

With this, we consider our final project a success in not only its use case, but as an application of the Arduino systems family. Although it is typically seen as a hobbyist tool, we have proven with this project that it can be just as beneficial in the professional world; all while learning important programming and circuitry skills.

## Acknowledgements
We thank Dr. Hoan Ngo for his guidance and support on this project.
