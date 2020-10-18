#include "PrintStream.h"

#ifdef ARDUINO

 /* #define OCT 8 */

static uint8_t formatPrintStream = DEC;
static bool boolalphaPrintStream = false;
static bool leadingZerosPrintStream = true;
static int8_t precisionPrintStream = 2;       // Fix a warning: use signed int8
static char byteSeparatorPrintStream = '\0';
enum lettercasePrintStream : char {
    LOWERCASE = 0x7F,
    UPPERCASE = 0x5F
};
static lettercasePrintStream casePrintStream = LOWERCASE;
static bool showbasePrintStream = false;

template <class T>
Print &printIntegral(Print &printer, T i);

Print &endl(Print &printer) {
  printer.println();
//   printer.flush();
  return printer;
}

Print &uppercase(Print &printer) {
  casePrintStream = UPPERCASE;
  return printer;
}

Print &nouppercase(Print &printer) {
  casePrintStream = LOWERCASE;
  return printer;
}

Print &showbase(Print &printer) {
  showbasePrintStream = true;
  return printer;
}

Print &noshowbase(Print &printer) {
  showbasePrintStream = false;
  return printer;
}

Print &flush(Print &printer) {
//   printer.flush();
  return printer;
}

Print &hex(Print &printer) {
  formatPrintStream = HEX;
  return printer;
}

/* Print &oct(Print &printer) {
  formatPrintStream = OCT;
  return printer;
} */

Print &bin(Print &printer) {
  formatPrintStream = BIN;
  return printer;
}

Print &dec(Print &printer) {
  formatPrintStream = DEC;
  return printer;
}

Print &boolalpha(Print &printer) {
  boolalphaPrintStream = true;
  return printer;
}
Print &noboolalpha(Print &printer) {
  boolalphaPrintStream = false;
  return printer;
}

Print &leadingzeros(Print &printer) {
  leadingZerosPrintStream = true;
  return printer;
}
Print &noleadingzeros(Print &printer) {
  leadingZerosPrintStream = false;
  return printer;
}

Print &operator<<(Print &printer, const __FlashStringHelper *s) {
    printer.print(s);
    return printer;
}
Print &operator<<(Print &printer, const String &s) {
    printer.print(s);
    return printer;
}
Print &operator<<(Print &printer, const char s[]) {
    printer.print(s);
    return printer;
}
Print &operator<<(Print &printer, char c) {
    printer.print(c);
    return printer;
}
Print &operator<<(Print &printer, unsigned char i) {
    return printIntegral(printer, i);
}
Print &operator<<(Print &printer, int i) {
    return printIntegral(printer, i);
}
Print &operator<<(Print &printer, unsigned int i) {
    return printIntegral(printer, i);
}
Print &operator<<(Print &printer, int8_t i) {
    return printIntegral(printer, i);
}
Print &operator<<(Print &printer, long i) {
    return printIntegral(printer, i);
}
Print &operator<<(Print &printer, unsigned long i) {
    return printIntegral(printer, i);
}
Print &operator<<(Print &printer, double d) {
    printer.print(d, precisionPrintStream);
    return printer;
}
Print &operator<<(Print &printer, const Printable& p) {
    printer.print(p);
    return printer;
}
Print &operator<<(Print &printer, bool b) {
    if (boolalphaPrintStream)
        printer.print(b ? F("true") : F("false"));
    else
        printer.print(b);
    return printer;
}

template <class T>
Print &printIntegral(Print &printer, T i) {
    switch (formatPrintStream)
    {
    case DEC:
        printer.print(i);
        break;
    case HEX:
        printHex(printer, i);
        break;
    case BIN:
        printBin(printer, i);  
        break;
    /* case OCT:
        printOct(printer, i);  
        break; */
    }
    return printer;
}

Print &operator<<(Print &printer, manipulator pf) {
  return pf(printer);
}

_Setbase setbase(uint8_t __base) { 
    return { __base }; 
}
Print &operator<<(Print &printer, _Setbase __f) {
    formatPrintStream = __f._M_base;
    return printer; 
}

_Setbytesep setbytesep(char __bytesep) { 
    return { __bytesep }; 
}
Print &operator<<(Print &printer, _Setbytesep __f) {
    byteSeparatorPrintStream = __f._M_bytesep;
    return printer; 
}

_Setprecision setprecision(int __n) {
    return { __n };
}
Print &operator<<(Print &printer, _Setprecision __f) {
    precisionPrintStream = __f._M_n;
    return printer;
}

static char nibble_to_hex(uint8_t nibble) {  // convert a 4-bit nibble to a hexadecimal character
  nibble &= 0xF;
  return nibble > 9 ? nibble - 10 + ('a' & casePrintStream) : nibble + '0';
}

#if __BYTE_ORDER != __LITTLE_ENDIAN
#error "Byte order not supported"
#endif

template <class T>
void printHex(Print &printer, T val)
{
    if (showbasePrintStream)
        printer.print(F("0x"));
    bool nonZero = false;
    for (int i = sizeof(val) - 1; i >= 0; i--)
    {
        uint8_t currByte = ((uint8_t *)&val)[i];
        if (currByte != 0 || i == 0)
            nonZero = true;
        if (leadingZerosPrintStream || nonZero) {
            printer.print(nibble_to_hex(currByte >> 4));
            printer.print(nibble_to_hex(currByte));
            if (byteSeparatorPrintStream && i)
                printer.print(byteSeparatorPrintStream);
        }
    }
}

template <class T>
void printBin(Print &printer, T val)
{
    if (showbasePrintStream)
        printer.print(F("0b"));
    bool nonZero = false;
    for (int i = sizeof(val) - 1; i >= 0; i--)
    {
        uint8_t currByte = ((uint8_t *)&val)[i]; 
        for (int j = 7; j >= 0; j--)
        {
            uint8_t currBit = currByte & 0x80;
            if (currBit != 0 || (i == 0 && j == 0))
                nonZero = true;
            if (leadingZerosPrintStream || nonZero)
                printer.print(currBit ? '1' : '0');
            currByte <<= 1;
        }
        if (byteSeparatorPrintStream && i && (leadingZerosPrintStream || nonZero))
            printer.print(byteSeparatorPrintStream);
    }
}


/* template <class T>
void printOct(Print &printer, T val)
{
    ; // TODO
} */

#endif