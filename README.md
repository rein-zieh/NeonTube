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
void init (
  uint8_t pin,            // Pin-Id
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

Mit der Funktion ```setDigitalPattern``` wird der Neonröhre ein digitales Flacker-Muster zugeordnet.
Das Muster wird beim Starten der Neonröhre abgespielt. Zusätzlich kann die Zeit angegeben werden, 
in deren Rhythmus die einzelnen Zustandsänderungen im Muster erfolgen sollen. Ein digitales Flacker-Muster 
besteht nur aus einem Feld (Array) aus 0- und 1-Werten für den entsprechenden Status LED an und LED aus. Digitale Muster 
können an allen I/O-Ausgängen des Boards verwendet werden.

```C++
void setDigitalPattern (
  uint8_t patternRythm = 40,           // Millisekunden zwischen den Statusänderungen in ms.
  const uint8_t *patternCustom = NULL, // Zeiger auf das Custom-Array mit dem Flacker-Muster
  uint8_t patternSize = 0              // Größe des Arrays
)
```
**Beispiele**

Ein digitales Standard-Flacker-Muster der NeonTube-Klasse mit dem Standard-Rhythmus von 40ms pro Status: 

```C++
tube1.setDigitalPattern();
```

Digitales Standard-Flacker-Muster der NeonTube-Klasse, aber mit einem beschleunigten Rhythmus von 20ms pro Status, dies entspricht ca. 50Hz.:

```C++
tube1.setDigitalPattern(20);
```

Verwende ein eigenes Flacker-Muster mit 30 Elementen, verwende dazu einen Rhythmus von 25ms pro Element:

```C++
const uint8_t myDigital[] = {
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
    1, 0, 0, 0, 0, 1, 1, 1, 0, 0,
};

tube1.setDigitalPattern(25, myDigital, 30);
```

#### Funktion setAnalogPattern

Mit der Funktion ```setAnalogPattern``` wird der Neonröhre ein analoges Flacker-Muster zugeordnet.
Das Muster wird beim Starten der Neonröhre abgespielt. Zusätzlich kann die Zeit angegeben werden, 
in deren Rhythmus die einzelnen Zustandsänderungen im Muster erfolgen sollen. Ein analoges Flacker-Muster 
besteht aus einem Feld von Werten zwischen 0 und 255 die für eine entsprechenden Helligkeit der LED stehen. 
Analoge Muster können nur an I/O-Ausgängen mit PWM-Fähigkeiten verwendet werden.

```C++
void setAnalogPattern(
    uint8_t patternRythm = 40,           // Millisekunden zwischen den Statusänderungen in ms.
    const uint8_t *patternCustom = NULL, // Zeiger auf das Custom-Array mit dem Flacker-Muster
    uint8_t patternSize = 0              // Größe des Arrays
);
```

**Beispiele**

Ein analoges Standard-Flacker-Muster der NeonTube-Klasse mit dem Standard-Rhythmus von 40ms pro Status: 

```C++
tube1.setAnalogPattern();
```

Analoges Standard-Flacker-Muster der NeonTube-Klasse, aber mit einem beschleunigten Rhythmus von 20ms pro Status, dies entspricht ca. 50Hz.:

```C++
tube1.setAnalogPattern(20);
```

Verwende ein eigenes Flacker-Muster mit 27 Elementen, verwende dazu einen Rhythmus von 40ms pro Element:

```C++
const uint8_t myAnalog[] = {
    0, 220, 40, 10, 0, 0, 0, 0, 0, 0, 
    220, 80, 20, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 180, 210, 230, 255
};

tube1.setAnalogPattern(40, myDigital, 27);
```

### Funktionen zur Laufzeit

```C++
void function run();
```


## Lizenz
Details entnehmen Sie bitte der Datei LICENSE.md.

Dieses Programm wird OHNE JEGLICHE GEWÄHRLEISTUNG oder GARANTIE weitergegeben.
Lesen die GNU General Public License für weitere Details.

Falls Sie das Toolkit verwenden würde ich mich über Credits freuen. Wenn Sie das Toolkit schätzen und etwas spenden möchten, dann spenden Sie bitte an den verlinkten Kinder- und Jugendhospizdienst Lünen: http://www.akhd-luenen.de