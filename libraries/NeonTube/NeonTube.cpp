/*
 * NeonTube.cpp 
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
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it
 * under certain conditions; type `show c' for details.
 */

#include "NeonTube.h"

NeonTube::NeonTube() {
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

    lightTimer.set(0);
}

void NeonTube::init(
    uint8_t    pin, 
    uint32_t   startDelay, 
    uint32_t   failsInterval, 
    uint8_t    failsVariation,
    NT_Pattern pattern, 
    uint8_t    patternRythm,
    uint8_t    *patternCustom,
    uint8_t    patternSize
) {
	
	if (pin >= 0 && pin <= 5)
		this->pin = pin;

	if (startDelay >= 0) 		
		this->startDelay = startDelay;

	initFails(failsInterval, failsVariation);

	initPattern(pattern, patternRythm, patternCustom, patternSize);

	ledState = 0;
	pinMode(this->pin, OUTPUT);

}

void NeonTube::initFails(
    uint32_t    failsInterval, 
    uint8_t     failsVariation
) {
	this->failsInterval = failsInterval;
	this->failsVariation = failsVariation;
}

void NeonTube::initPattern(
    NT_Pattern  pattern, 
    uint8_t     patternRythm,
    uint8_t     *patternCustom,
    uint8_t     patternSize
) {
	if (pattern >= NT_NOPATTERN && pattern <= NT_ANALOGPATTERN)
		this->pattern = pattern;

	if (patternCustom) {
		patternPointer = patternCustom;
		if (patternSize) {
		    this->patternSize = patternSize;
		}
	} else {

		if (this->pattern == NT_DIGITALPATTERN) {
			patternPointer = patternDigital;
		    this->patternSize = sizeof(patternDigital)/sizeof(patternDigital[0]);
		}

		else if (this->pattern == NT_ANALOGPATTERN) {
			patternPointer = patternAnalog;
		    this->patternSize = sizeof(patternAnalog)/sizeof(patternAnalog[0]);
		}
	}

	if (patternRythm) {
		this->patternRythm = patternRythm;
	} 

    patternIndex = 0;
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
	switch(runState) {
		case NT_PATTERN : runPattern(); break;
		case NT_GLOW    : runGlow();    break;
		case NT_START   : runStart();   break;
		case NT_STOP    : runStop();    break;
	}
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
		} else {
			if ( *(patternPointer + patternIndex) != ledState) {
				ledState = *(patternPointer + patternIndex);
				if (pattern == NT_DIGITALPATTERN)
					digitalWrite(pin, ledState);
				else
					analogWrite(pin, ledState);
			}
		}
		patternIndex++;

	}
}

void NeonTube::runGlow() {
	// evtl. Fehler einstreuen
}

void NeonTube::runStop() {
	ledState = 0;
	digitalWrite(pin, 0);
}


