# Arduino & Raspberry Pi driver for nRF24L01(+) 2.4GHz Wireless Transceiver

This version has been forked from the original maniacsbug and modified for working with Arduino and Teensy3.
In the library config file there's an option for enable/disable all print features and save space. The option is:

<code>#define PRINTFENABLED</code>

Comment out will disable all printouts from library in arduino and teensy.
Modified a little bit the original maniacsbug examples to ensure compatibility with Teensy3. The printf.h file included
in every example has changed and the original example just need this line added:
<code>

RF24 radio(9,10);

//add this for compatibility to Teensy3 and printf
#if defined(__arm__) && defined(CORE_TEENSY)
#define printf radio.kprintf
#endif
//end

</code>
Notice that if you instance the library differently (es. <code> RF24 wifi(9,10); </code>) you need to modify the line
<code>#define printf radio.kprintf</code> accordly. Like <code>#define printf wifi.kprintf</code>

This is needed just for printf, if you don't use printf in your code the library works as is, yust remember to comment out
<code>#define PRINTFENABLED</code> in library config file to save a lot of space/ram.

Design Goals: 

* Maximally compliant with the intended operation of the chip
* Easy for beginners to use
* Consumed with a public interface that's similiar to other Arduino standard libraries
* Built against the standard SPI library. 
* Support popular platform

* Modifications to the RF24 library in this fork is backward compatible. A single
  enhancement which may cause issue, is code which relies on the driver to power down the
  radio, as a side effect. The radio is no longer powered down after each transmit. Rather,
  the application must take responsibility for power management. Normally this is
  achieved by use of powerDown and powerUp. If you wish to maximize power efficiency,
  you must call powerDown after transmit (write, startWrite).

Please refer to links :

* [Blog on setting up both Arduino UNO & Raspberry Pi] (http://arduino-for-beginners.blogspot.com/2013/02/setup-nordic-nrf24l01-rf-modules-to.html)
* [Documentation Main Page](http://maniacbug.github.com/RF24)
* [RF24 Class Documentation](http://maniacbug.github.com/RF24/classRF24.html)
* [Source Code](https://github.com/maniacbug/RF24)
* [Downloads](https://github.com/maniacbug/RF24/archives/master)
* [nRF24L01+ datasheet](http://www.nordicsemi.com/eng/nordic/download_resource/8765/2/27999719 )




