# asd

## Tasks

- Fix Little FS
- Add invert to led library
- Fix Captive portal and DNS
- fix SimpleDebugLog redefinition warnings
- Joytick not centers if the server is not connected
- Setup Arduino Websocket server
- JS minify broke JS code
- Refactore sliders to work like buttons (make easier to have any number of sliders)
- fix: HTML merging removes checked from checkboxs
- on arduino when the server disconnects, the client don't recognise it.
  - Add Heartbeat Mechanism: Implementing a heartbeat mechanism is the best way to deal with WebSocket disconnections. This involves sending a ping request to the server at regular intervals to check if it's healthy. If the server doesn't respond within a certain time frame, the assume that the connection has dropped and call onDisconnect method

<https://github.com/rlogiacco/BatterySense>
<https://github.com/ESP32Async/ESPAsyncWebServer>
<https://github.com/TheArduinist/DRV8833>
<https://parvaiz.pk/posts/virtual-joystick-for-arduino/>
<https://github.com/parvaizahmad/virtualJoystickESP>

## Running gzip test server

1. `npm install`
2. `npm run gzipStart`

## Wokwi

- Build after every change
