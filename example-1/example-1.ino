/*
 * neontube.ino
 *
 * Neon Tube - V 0.3 (Proof of concept)
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
  0, 30, 60, 90, 120, 150, 180, 220, 0, 0, 
  0, 0, 0, 0, 0, 50, 100, 150, 200, 0, 
  0, 0, 0, 0, 0, 120, 255
};

const uint8_t myDigital[] = {
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
    1, 0, 0, 0, 0, 1, 1, 1, 0, 0,
};

/*
 * Functions
 */
void dcc_status_toggle (NTTimer &timer) {
  dccStatus = !dccStatus;

  if (dccStatus) {
    tube0.on(); 
    tube1.on(); 
    tube2.on();
    tube3.on();
  } else {
    tube0.off();
    tube1.off();
    tube2.off();
    tube3.off();
  }
}

/*
 * SETUP
 */
void setup() {
  // Timer instead of a dcc signal
  dccTimer.set(10000,dcc_status_toggle);

  //Tube 0: random start delay zero to 1 second; analog custom start pattern; some failures during runtime
  tube0.init(0, random(0,1000));
  tube0.setAnalogPattern(40, myAnalog, sizeof(myAnalog)/sizeof(myAnalog[0]));
  tube0.setFails(10, 200, 50);
  
  //Tube 1: no start delay; no pattern; no failures during runtime
  tube1.init(1, 0);
  
  //Tube 2: 500ms start delay; default digital start pattern; no failures during runtime
  tube2.init(2, 500);
  tube2.setDigitalPattern();

  //Tube 3: random start delay zero to 2 second; custom digital start pattern; few failures during runtime
  tube3.init(3, random(0,2000));
  tube3.setDigitalPattern(25, myDigital, sizeof(myDigital)/sizeof(myDigital[0]));
  tube0.setFails(30, 50, 50);

}
 
/*
 * LOOP
 */
void loop() {
  dccTimer.run();
  tube0.run();
  tube1.run();
  tube2.run();
  tube3.run();
}
