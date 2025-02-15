# asd

## Tasks

- Fix GZIP compression
- Refactor slider json format. It is a mess.
  - Refactore sliders to work like buttons (make easier to have any number of sliders)
- Fix Captive portal and DNS
- Joytick not centers if the server is not connected
- JS minify broke JS code
- fix: HTML merging removes checked from checkboxs
- on arduino when the server disconnects, the client don't recognise it.
  - Add Heartbeat Mechanism: Implementing a heartbeat mechanism is the best way to deal with WebSocket disconnections. This involves sending a ping request to the server at regular intervals to check if it's healthy. If the server doesn't respond within a certain time frame, the assume that the connection has dropped and call onDisconnect method

- Implement motor Smoother/filther/kinematics scroll: Azt szeretném hogy ha gázt adok (pl. setSpeed(127)), fokozatosan gyorsuljon fel a motor, ha pedig elveszem a gázt (setSpeed(0)), fokozatosan lassuljon le. Ehhez több ötletem is volt: lehetne egy logaritmikus vagy exponenciális görbével szülni az inputot vagy valamilyen kinematocs scrolling szerű energia megmaradás vektoros szimulációt végezni. Milyen algoritmussal és hogy lehetne ezt megvalósítani? - Traction control system, Anti-Slip Regulation: https://www.youtube.com/watch?v=4dpBhqo6x7Y

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
