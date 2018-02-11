/*
 * neontube.ino
 *
 * Neon Tube - V 0.1 (Proof of concept)
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
 * CAlso add information on how to contact you by electronic and paper mail.
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

uint8_t myPattern[13] = {
  10, 40, 255, 0, 10, 20, 30, 40, 50, 200
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
  tube0.init(0, 1500, 0, 0, NT_ANALOGPATTERN, 25, myPattern, 25);
  tube1.init(1, 0, random(5000,10000), 50, NT_NOPATTERN);
  tube2.init(2, random(500,2500), 0, 0, NT_DIGITALPATTERN, 25);
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
