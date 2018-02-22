# NeonTube
Eine einfache Arduino-Bibliothek (Toolkit) zur Simulation von Neonröhren mittels Leuchtdioden im Modellbau.

## Version 1.0

Mittels der NeonTube-Bibliothek lässt sich das typische Verhalten von Neonröhren im Modellbau simulieren:
- Unterschiedliche Einschaltverzögerungen
- Flackern alter Neonröhren während des Starts
- unwirkürliche kurze Aussetzer während des Betriebs

Die Bibliothek wurde auf einem Digispark Mini mit ATtiny85 Mikrocontroller (z.B.: https://tinyurl.com/y6u2h2o6) 
entwickelt und getestet.

## Anleitung

### Variablen

Im Variablen-Bereich des Sketch können Instanzen der NeonTube-Klasse erzeugt werden:

```C++
NeonTube tube1;
```

### Initialisieren / Setup

Vor der Verwendung müssen die Instanzen der NeoTubes initialisiert und parametrisiert werden. Dies sollte in der der `setup()`-Funktion des Sketch geschehen. 

#### Funktion init

Bei der Initialisierung muss zumindest der Anschluss-Pin (pin) zugeordnet werden. Optional kann noch die 
Startverzögerung (startDelay) in Millisekunden angegeben werden.

```C++
void function init (
  uint8_t pin, // Pin-Id
  uint32_t startDelay = 0 // Startverzögerung in Milli-Sekunden (default = 0)
)
```

**Beispiele:**

Neonröhre an Pin 1:

```C++
tube1.init(1);
```

Neonröhre an Pin 0, Einschaltverzögerung 1 Sekunde:

```C++
tube1.init(0, 1000);
```

Neonröhre an Pin 0, Einschaltverzögerung zufällig zwischen 0,5 und 2 Sekunden:

```C++
tube1.init(0, random(500,2000));
```

#### Funktion setDigitalPattern

Mit der Funktion ```setDigitalPattern``` wird der Neonröhre ein Flacker-Muster zugeordnet. Das Muster wird beim Starten
der Neonröhre abgespielt. Zusätzlich kann die Zeit angegeben werden, in deren Rythmus die einzelnen Zustandsänderungen im Muster erfolgen sollen. Ein digitales Flacker-Muster besteht nur aus 0- und 1-Elementen für den entsprechenden Status LED an und LED aus. Digitale Muster können an allen I/O-Ausgängen des Boards verwendet werden.

```C++
void function setDigitalPattern (
  uint8_t patternRythm = 40, // Millisekunden zwischen den Statusänderungen in ms. (40 ms entsprechen 25 Hz).
  const uint8_t *patternCustom = NULL, // Zeiger auf das Custom-Array mit dem Flacker-Muster
  uint8_t patternSize = 0 //Größe des Arrays
```
**Beispiele**

Standard-Flacker-Muster der NeonTube-Klasse mit dem Standard-Rythmus von 40ms pro Status: 

```C++
tube1.setDigitalPattern();

Standard-Flacker-Muster der NeonTube-Klasse aber mit einem beschleunigten Rythmus von 20ms pro Status (entspricht 50Hz.). 

```C++
tube1.setDigitalPattern(20);
```

Verwende eigenes Flacker-Muster mit 30 Elementen, verwende dazu einen Rythmus von 25ms pro Element.

```C++
const uint8_t myDigital[] = {
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
    1, 0, 0, 0, 0, 1, 1, 1, 0, 0,
};

tube1.setDigitalPattern(25, myDigital, 30);
```

### Funktionen zur Laufzeit


## License
Please check the file LICENSE.md for the details.

I appreciate if you give credits when appropriate, and if you want to donate, please donate to the linked Children Hospice Charity: http://www.akhd-luenen.de

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

## Warranty
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Regards, Frank
