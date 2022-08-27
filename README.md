# WebSerial

WebSerial is a Serial Monitor for ESP8266 & ESP32 Microcontrollers that can be accessed remotely via a web browser. Webpage is stored in program memory of the microcontroller.

## Preview

![Preview](https://s2.loli.net/2022/08/27/U9mnFjI7frNGltO.png)

## Upgrade to Pro?

I'm sorry that the current version is already the Pro version. XD

## Features

- Works on Websockets
- Realtime logging
- Any number of Serial Monitors can be opened on the browser
- Uses Async Webserver for better performance

## Dependencies

For ESP8266:

- ESP8266 Arduino Core - (latest)
- ESPAsyncTCP - v1.2.2
- ESPAsyncWebServer - v1.2.3

For ESP32:

- ESP32 Arduino Core - (latest)
- AsyncTCP - v1.1.1
- ESPAsyncWebServer - v1.2.3

## Documentation

WebSerial is very similar to the default Serial Monitor Library of Arduino.

Please see `Demo` examples for better understanding on how to setup WebSerial for your Project: Click Here

WebSerial has 2 main functions:

- `print`
- `println`

`print` - simply prints the data sent over WebSerial without any newline character.

`println` - prints the data sent over WebSerial with a newline character.

Both functions support the following datatypes: `String`, `const char`, `char`, `int`, `uint8_t`, `uint16_t`, `uint32_t`, `double`, `float`.

To Access Webserial: Go to `<IP Address>/webserial` in your browser ( where `<IP Address>` is the IP of your ESP).

## Contributions

Every Contribution to this repository is highly appriciated! Don't fear to create pull requests which enhance or fix the library as ultimatly you are going to help everybody.

## License

WebSerial is licensed under General Public License v3 ( GPLv3 ).
