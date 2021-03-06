# Another Fork of Arduino-PrintStream
A simple library that adds `std::cout`-like support for the Arduino using the 
`<<`-operator. This fork has been made convenient for use with Arduino 
running on STM32 and ESP32 processors. 

## Example usage

```cpp
#include <PrintStream.h>

void setup () 
{
    Serial.begin (115200);
    Serial << "Hello, World!" << endl;

    Serial << "Counting to 0xf in hexadecimal: "
           << hex << noleadingzeros << showbase;
    for (int index = 0; index < 0x10; index++)
    {
        Serial << index << ' ';
    }
    Serial << dec << endl;

    float voltage = analogRead (A0) * 3.3 / 4095.0;
    Serial << "The voltage on analog pin A0 is " << setprecision (3) 
           << voltage << " V." << endl;
}

void loop ()
{
}
```

## Installation
### Generic
Download the library as a ZIP file, and import it into the Arduino IDE as 
explained [here](https://www.arduino.cc/en/guide/libraries#toc4).

### Into a VSCode Project
Add the following lines to your project's `platformio.ini` file:

    lib_deps =
        https://github.com/spluttflob/Arduino-PrintStream.git

