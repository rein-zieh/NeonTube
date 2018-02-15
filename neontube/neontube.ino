/*
 * neontube.ino
 *
 * Neon Tube - V 0.2 (Proof of concept)
 * Toolkit for simulating a neon tube
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Neon Tube Copyright (C) 2018 Frank Reins (github@rein-zieh.de)
 *
 * This program comes with ABSOLUTELY NO WARRANTY
 */

/*
 * Sketch for Digispark Mini
 * https://www.reichelt.de/index.html?ARTICLE=192128
 * 
 * Alle Pins können als Digitale Eingänge und Ausgänge genutzt werden
 * Pin 0 = I2C SDA, PWM (LED am Model B)
 * Pin 1 = PWM (LED am Model A)
 * Pin 2 = I2C SCK, Analog In
 * Pin 3 = Analog In (also used for USB+ if USB is used)
 * Pin 4 = PWM, Analog (also used for USB- if USB is used)
 * Pin 5 = Analog In
 * 
 * PWM Pin 0 max. 504Hz
 * PWM Pin 1 max. 504Hz    
 * PWM Pin 4 max. 1007Hz
 */


/*
 * CONFIGURATION
 */
#define DigisparkMini
#define __AVR_ATtiny85__

#include <NTTimer.h>
#include <NeonTube.h>

/*
 * STATUS/TIMER VARS
 */
uint32_t dccStatus = 0;
NTTimer dccTimer;

NeonTube tube0;
NeonTube tube1;
NeonTube tube2;
NeonTube tube3;

const uint8_t myAnalog[] = {
  10, 40, 255, 0, 10, 20, 30, 40, 50, 200, 
  10, 40, 255, 0, 10, 20, 30, 40, 50, 200
};

const uint8_t myDigital[] = {
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
    1, 0, 0, 0, 0, 1, 1, 1, 0, 0,
};

// 
/*uint8_t patternAnalog[] = {
      0,   0,  10,  20,  30,  30,  40,  50,  60,  70,
     80,  70,  70,  60,  60,  50,  50,  50,  60,  70, 
     80,  90, 100, 120, 140, 160, 240, 250, 100, 150,
    250, 250, 140, 240, 230, 220, 100,  80,  70,  70,
     70,  80,  80, 140, 130, 120, 110, 200, 210, 220,
    220, 100,  90,  40,  30,  30,  30,  20,  10,  10 
}; */


/*
 * Functions
 */
void dcc_status_toggle (NTTimer &timer) {
  dccStatus = !dccStatus;

  if (dccStatus) {
    tube0.on(); 
    tube1.on(); 
    tube2.on();
  } else {
    tube0.off();
    tube1.off();
    tube2.off();
  }
}

/*
 * SETUP
 */
void setup() {
  dccTimer.set(7000,dcc_status_toggle);

  tube0.init(0, 1000);
  tube0.setAnalogPattern(myAnalog, sizeof(myAnalog)/sizeof(myAnalog[0]), 25);
  
  tube1.init(1, 0);
  
  tube2.init(2, 1200);
  tube2.setDigitalPattern(myDigital, sizeof(myDigital)/sizeof(myDigital[0]), 25);

}
 
/*
 * LOOP
 */
void loop() {
  dccTimer.run();
  tube0.run();
  tube1.run();
  tube2.run();
}
