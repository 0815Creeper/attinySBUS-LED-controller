#define DELAY_HALF_BIT()    __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t");\
  __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t");\
  __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t");\
  __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t");\
  __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t");\
  __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t");\
  __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t");\
  __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t");

#define PIN_LED 0
#define LED_OFF LOW
#define PIN_SIGNAL_IN 1

int chn14_val = 0;

void setup() {
  pinMode(PIN_SIGNAL_IN, INPUT);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LED_OFF);
  delay(3000);
  chn14_val = read_sbus_chan14();
}

void loop() {
  int i;
  if (chn14_val < 1550) {
    i = 200;
  } else if (chn14_val < 1650) {
    i = 135;
  } else {
    i = 70;
  }
  if (chn14_val > 1450 && chn14_val < 2150) {
    digitalWrite(PIN_LED, !LED_OFF);
    delay(i);
    digitalWrite(PIN_LED, LED_OFF);
    delay(i + 30);
    digitalWrite(PIN_LED, !LED_OFF);
    delay(i);
    digitalWrite(PIN_LED, LED_OFF);
  }
  unsigned long t = millis();
  while ((millis() - t) < 1200) {
    chn14_val = read_sbus_chan14();
    if (chn14_val <= 1450)
      break;
  }
}

int read_sbus_chan14() {
  while (true) {
    uint8_t parity_bit = 0;
    uint8_t sbus_data[25];
    unsigned long tt = micros();
    while ((micros() - tt) < 4000) {
      if ((PINB & (1 << PIN_SIGNAL_IN)))
        tt = micros();
    }
    //frame timeout
    cli();
    for (int i = 0; i < 25; i++) {
      uint8_t lcl_read = 0;
      while (!(PINB & (1 << PIN_SIGNAL_IN))); //wait for startbit
      DELAY_HALF_BIT()
      DELAY_HALF_BIT()
      DELAY_HALF_BIT()
      lcl_read = lcl_read | ((PINB & (1 << PIN_SIGNAL_IN)) >> 1);
      DELAY_HALF_BIT()
      DELAY_HALF_BIT()
      lcl_read = lcl_read | ((PINB & (1 << PIN_SIGNAL_IN)) << 0);
      DELAY_HALF_BIT()
      DELAY_HALF_BIT()
      lcl_read = lcl_read | ((PINB & (1 << PIN_SIGNAL_IN)) << 1);
      DELAY_HALF_BIT()
      DELAY_HALF_BIT()
      lcl_read = lcl_read | ((PINB & (1 << PIN_SIGNAL_IN)) << 2);
      DELAY_HALF_BIT()
      DELAY_HALF_BIT()
      lcl_read = lcl_read | ((PINB & (1 << PIN_SIGNAL_IN)) << 3);
      DELAY_HALF_BIT()
      DELAY_HALF_BIT()
      lcl_read = lcl_read | ((PINB & (1 << PIN_SIGNAL_IN)) << 4);
      DELAY_HALF_BIT()
      DELAY_HALF_BIT()
      lcl_read = lcl_read | ((PINB & (1 << PIN_SIGNAL_IN)) << 5);
      DELAY_HALF_BIT()
      DELAY_HALF_BIT()
      lcl_read = lcl_read | ((PINB & (1 << PIN_SIGNAL_IN)) << 6);
      DELAY_HALF_BIT()
      DELAY_HALF_BIT()
      //make odd parity
      parity_bit = (PINB & (1 << PIN_SIGNAL_IN)) >> 1;
      while ((PINB & (1 << PIN_SIGNAL_IN))); //wait for end of bit
      sbus_data[i] = ~lcl_read;
      //parity check does not work...
      /*if (((parity_bit) & 1) ^ ((lcl_read & 1) ^ ((lcl_read & 2) >> 1) ^ ((lcl_read & 4) >> 2) ^ ((lcl_read & 8) >> 3) ^ ((lcl_read & 16) >> 4) ^ ((lcl_read & 32) >> 5) ^ ((lcl_read & 64) >> 6) ^ ((lcl_read & 128) >> 7))) {
        sbus_data[0] = 0;
        } else {
        sbus_data[i] = ~lcl_read;
        }*/
    }
    sei();
    if (sbus_data[0] == 0x0f && sbus_data[23] == 0 && sbus_data[24] == 0) { //check if framestart and end are valid and no failsave and frame not lost
      int chn = 0;
      //11 bit per channel, channel 14 uses 1 bit from byte at idx 18, 8 bit from byte at idx 19, 2 bit from byte at idx 20
      chn = (int)(sbus_data[20] & 0b11) << 9;
      chn |= (int)sbus_data[19] << 1;
      chn |= (int)(sbus_data[18] & 0b10000000) >> 7;
      //scale to standart 988us to 2012us
      chn -= 992;
      chn *= 5;
      chn /= 8;
      chn += 1500;
      return chn;
    }
  }
}
