# attinySBUS-LED-controller
Arduino sketch for attiny85 at 16Mhz reading SBUS signals without inverter and controlling a flashing anticollision light (ACL/Strobes)

Tested with ATTiny85 at 16MHz internal Clock with David A. Mellis' Attiny implementation v1.0.2 for Arduino 1.8.13

Modes: 
off: < 1450 us on sbus channel 14
long ontime: 1450us .. 1550us
medium ontime: 1550us .. 1650us
short ontime: 1650us .. 2150us
