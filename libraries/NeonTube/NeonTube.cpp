/*
 * NeonTube.cpp 
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
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it
 * under certain conditions; type `show c' for details.
 */

#include "NeonTube.h"

/*
 * Constructur
 */
NeonTube::NeonTube() {
    reset();
}

const uint8_t NeonTube::defaultAnalog[] = {
    0, 220, 40, 10, 0, 0, 0, 0, 0, 0, 
    220, 80, 20, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 180, 210, 230, 255
};

const uint8_t NeonTube::defaultDigital[] = {
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
    1, 0, 0, 0, 0, 1, 1, 1, 0, 0
};

void NeonTube::reset() {
    pin = 0;

    runState = NT_STOP;
    ledState = 0;
    
    startDelay = 0;
    pattern = NT_NOPATTERN;
    patternIndex = 0;
    patternPointer = NULL;
    patternSize = 0;
    patternRythm = 25;

    failsInterval = 0;
    failsVariation = 0;
    failsDuration = 10;

    lightTimer.set(0);
}

void NeonTube::init(uint8_t pin, uint32_t startDelay) {
    reset();
    
    this->pin = pin;
    this->startDelay = startDelay;

    pinMode(this->pin, OUTPUT);

}

void NeonTube::setFails(uint16_t failsInterval, uint8_t failsVariation, uint8_t failsDuration) {
    this->failsInterval = failsInterval;
    this->failsVariation = failsVariation;
    this->failsDuration = failsDuration;
}

void NeonTube::setDigitalPattern(uint8_t patternRythm, const uint8_t *patternCustom, uint8_t patternSize) {
    pattern = NT_DIGITALPATTERN;
    patternIndex = 0;
    this->patternRythm = patternRythm;

    if (patternCustom) {
        this->patternSize = patternSize;
        this->patternPointer = patternCustom;
        return;
    } 

    this->patternPointer = defaultDigital;
    this->patternSize = sizeof(defaultDigital)/sizeof(defaultDigital[0]);
}

void NeonTube::setAnalogPattern(uint8_t patternRythm, const uint8_t *patternCustom, uint8_t patternSize) {
    pattern = NT_ANALOGPATTERN;
    patternIndex = 0;
    this->patternRythm = patternRythm;

    if (patternCustom) {
        this->patternSize = patternSize;
        this->patternPointer = patternCustom;
        return;
    } 

    this->patternPointer = defaultAnalog;
    this->patternSize = sizeof(defaultAnalog)/sizeof(defaultAnalog[0]);
}

void NeonTube::on() {
    lightTimer.set(startDelay);
    runState = NT_START;
    patternIndex = 0;
    ledState = 0;
    run();
}

void NeonTube::off() {
    runState = NT_STOP;
    run();
}

void NeonTube::run() {
/*   
 *   switch(runState) {
 *       case NT_PATTERN : runPattern(); break;
 *       case NT_GLOW    : runGlow();    break;
 *       case NT_START   : runStart();   break;
 *       case NT_STOP    : runStop();    break;
 *   }
 * To avoid a lookup table in RAM memory
 */
    if (runState == NT_PATTERN) { runPattern(); return; }
    if (runState == NT_GLOW)    { runGlow();    return; }
    if (runState == NT_START)   { runStart();   return; }
    if (runState == NT_STOP)    { runStop();    return; }
}

void NeonTube::runStart() {
    if (lightTimer.check()) {
        switch (pattern) {
            case NT_DIGITALPATTERN : {
                runState = NT_PATTERN;
                lightTimer.set(patternRythm);
                return;
            }
            case NT_ANALOGPATTERN : {
                runState = NT_PATTERN;
                lightTimer.set(patternRythm);
                return;
            }
            case NT_NOPATTERN : {
                if (failsInterval) lightTimer.set(100 * failsInterval + random(0, failsInterval * failsVariation));
                ledState = 1;
                digitalWrite(pin, 1);
                runState = NT_GLOW;
                return;
            }
        }
    }
}

void NeonTube::runPattern() {
    if (lightTimer.checkAndRepeat()) {

        if (patternIndex >= patternSize) {
            ledState = 1;
            digitalWrite(pin, 1);
            runState = NT_GLOW;
            return;
        } 
        if ( *(patternPointer + patternIndex) != ledState) {
            ledState = *(patternPointer + patternIndex);
            if (pattern == NT_DIGITALPATTERN)
                digitalWrite(pin, ledState);
            else
                analogWrite(pin, ledState);
        }
        patternIndex++;

    }
}

void NeonTube::runGlow() {
    if (failsInterval && lightTimer.check()) {
        if (ledState) {
            ledState = 0;
            digitalWrite(pin, 0);
            lightTimer.set(failsDuration);
        } else {
            ledState = 1;
            digitalWrite(pin, 1);
            lightTimer.set(100 * failsInterval + random(0, failsInterval * failsVariation));
        }
    }
}

void NeonTube::runStop() {
    ledState = 0;
    digitalWrite(pin, 0);
}



