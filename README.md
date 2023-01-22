# WebSerialLite

WebSerial is a Serial Monitor for ESP8266 & ESP32 Microcontrollers that can be accessed remotely via a web browser. Webpage is stored in program memory of the microcontroller.

## Preview

![Preview](https://s2.loli.net/2022/08/27/U9mnFjI7frNGltO.png)

[DemoVideo](https://www.bilibili.com/video/BV1Jt4y1E7kj)

## Upgrade to Pro?

I'm sorry that the current version is already the Pro version. XD

## Features

- Works on WebSockets
- Realtime logging
- Any number of Serial Monitors can be opened on the browser
- Uses Async Webserver for better performance
- Light weight (<3k)
- Timestamp
- Event driven

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

WebSerialLite is very similar to the default Serial Monitor Library of Arduino.

Please see `Demo` examples for better understanding on how to setup WebSerialLite for your Project.

WebSerialLite has 2 main functions:

- `print`
- `println`

`print` - simply prints the data sent over WebSerialLite without any newline character.

`println` - prints the data sent over WebSerialLite with a newline character.

Both functions support the following datatypes: `String`, `const char`, `char`, `int`, `uint8_t`, `uint16_t`, `uint32_t`, `double`, `float`.

To Access WebSerialLite: Go to `<IP Address>/webserial` in your browser ( where `<IP Address>` is the IP of your ESP).

## FAQ

1. **last `println` not being received** [#4](https://github.com/asjdf/WebSerialLite/issues/4)
   > This issue is not caused by this library. As you can see in <https://github.com/me-no-dev/ESPAsyncWebServer/blob/f71e3d427b5be9791a8a2c93cf8079792c3a9a26/src/AsyncWebSocket.cpp#L550> , they limit the length of queue, and they define the max length of queue to 8 for ESP8266, you can check in <https://github.com/me-no-dev/ESPAsyncWebServer/blob/f71e3d427b5be9791a8a2c93cf8079792c3a9a26/src/AsyncWebSocket.h#L30>.
   >
   > So if you want to send many messages through websocket rapidly, I recommend you make a temp storage. Or you can edit the ESPAsyncWebServer to solve this problem. By the way, I create a PR try to let user config the WS_MAX_QUEUED_MESSAGES (esphome/ESPAsyncWebServer#10), hope it can be proved.

## Contributions

Every Contribution to this repository is highly appreciated! Don't fear to create pull requests which enhance or fix the library as ultimately you are going to help everybody.

## License

WebSerialLite is licensed under General Public License v3 ( GPLv3 ).
