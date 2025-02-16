// This file is generated by `build_file_system_image.py`. Do not edit it. Run Build Filesystem Image to update it.
// Source Files: `web/src/index.html` and its dependencies
const char index_html[] PROGMEM = R"rawliteral(<html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><link rel='icon' href='data:image/svg+xml,<svg xmlns=%22http://www.w3.org/2000/svg%22 viewBox=%220 0 100 100%22><text y=%221em%22 font-size=%2280%22>🎮</text></svg>'><style>:root{--clr-text-on-dark-bg:white;--clr-bg-1:#f0f0f0;--clr-bg-2:#e0e0e0;--clr-bg-3:#ccc;--clr-bg-joy:radial-gradient(circle,var(--clr-bg-1),var(--clr-bg-3));--clr-bg-cont:linear-gradient(135deg,var(--clr-bg-1),var(--clr-bg-2));--clr-btn:#28a745;--clr-success:#28a745;--clr-failed:#dc3545;--clr-brd-joy:1px solid #bbb}*{box-sizing:border-box}body{font-family:'Arial',sans-serif;font-size:16px;display:flex;flex-direction:column;align-items:center;justify-content:top;margin:0;padding:0;background-color:var(--clr-bg-1);box-sizing:border-box}.container{display:flex;flex-direction:column;align-items:center;gap:5px;padding:0px 0.5rem 0px 0.5rem;background:var(--clr-bg-cont);border:1px solid #ccc;border-radius:1rem;box-shadow:0 4px 8px rgba(0,0,0,0.1);width:100%}@media (min-width:768px){.container{width:400px;margin:1rem}}.joystick-container{position:relative;width:70%;aspect-ratio:1/1;background:var(--clr-bg-joy);border-radius:50%;box-shadow:0 8px 16px rgba(0,0,0,0.2);border:1px solid var(--clr-brd-joy);display:flex;justify-content:center;align-items:center}.joystick-container::before,.joystick-container::after{content:'';position:absolute;background-color:#cfcfcf}.joystick-container::before{width:1px;height:100%;top:0;left:50%;transform:translateX(-50%)}.joystick-container::after{width:100%;height:1px;top:50%;left:0;transform:translateY(-50%)}.joystick{position:absolute;width:70px;height:70px;background:radial-gradient(circle,#007bff,#0056b3);border-radius:50%;top:50%;left:50%;transform:translate(-50%,-50%);box-shadow:0 8px 16px rgba(0,0,0,0.2);touch-action:none;border:2px solid #004080;z-index:1}.sliders{width:100%;display:flex;flex-direction:column;justify-content:center;align-items:center;padding:10px;gap:10px}.slider-container{width:100%;display:flex;flex-direction:column;align-items:center}.slider{-webkit-appearance:none;appearance:none;width:100%;height:15px;background:linear-gradient(to right,green,red);outline:none;opacity:0.7;transition:opacity .2s;border-radius:10px}.slider:hover{opacity:1}.slider::-webkit-slider-thumb{-webkit-appearance:none;appearance:none;width:25px;height:25px;background:#4CAF50;cursor:pointer;border-radius:5px}.slider::-moz-range-thumb{width:25px;height:30px;background:#4CAF50;cursor:pointer;border-radius:5px}.buttons{width:100%;display:flex;justify-content:space-around;flex-wrap:wrap;gap:0.5rem}.button{height:60px;width:20%;background-color:var(--clr-btn);border:none;color:var(--clr-text-on-dark-bg);font-size:16px;border-radius:10px;box-shadow:0 4px 8px rgba(0,0,0,0.2);cursor:pointer;transition:background-color 0.3s ease;margin:5px;user-select:none}.button.switch-on{background-color:#ff0707}.button.push-active{background-color:#0056b3;user-select:none}.common-label{font-size:16px;font-weight:bold;margin-right:1px;color:#333}.toggle-checkbox{width:20px;height:20px;cursor:pointer;accent-color:#007bff}.check-button-container{display:flex;justify-content:left;width:100%;align-items:center;gap:5px}header{width:100%;display:flex;justify-content:space-between;align-items:top;margin-bottom:1rem}.menu-toggle{line-height:normal;font-size:2rem;color:gray;padding:0.5rem}.status-label{font-size:1rem;font-weight:bold;height:fit-content;padding:5px 10px;border-radius:0 0 0.5rem 0.5rem;color:var(--clr-text-on-dark-bg)}.status-connected{background-color:var(--clr-success)}.status-disconnected{background-color:var(--clr-failed)}details{width:100%;padding:0.5rem}details summary{width:fit-content;padding:0.8rem;border-radius:1rem;border:2px solid #ccc}.overlay{height:100%;width:0;position:fixed;z-index:2;left:0;top:0;background-color:rgba(0,0,0,0.9);color:var(--clr-text-on-dark-bg);overflow-x:hidden;overflow-y:auto;transition:0.5s}.overlay-content{position:relative;top:10%;padding:1rem}.overlay .closebtn{color:#818181;text-decoration:none;position:absolute;top:20px;right:45px;font-size:60px}</style><title>Robot controller</title></head><body><div id='terminalOverlay' class='overlay'><a href='javascript:void(0)' class='closebtn' onclick='closeLogMenu()'>x</a><div class='overlay-content'><div id='logs' class='logs'></div></div></div><dialog id='optionsOverlay'><button onclick='closeOptionsMenu()'>Close</button><p>This modal dialog has a groovy backdrop!</p></dialog><div class='container'><header><div class='menu-toggle'><span onclick='openLogMenu()'><\></span></div><div id='status' class='status-label status-disconnected'>Disconnected</div><div class='menu-toggle'><span onclick='openOptionsMenu()'>O</span></div></header><div><p>placeholder for sensor meassurements</p></div><div class='check-button-container'><label class='common-label' for='toggle-return'>RTH:</label><input class='toggle-checkbox' type='checkbox' id='toggle-return' onchange='handleToggleChange()'><label class='common-label' for='toggle-sl'>SL:</label><input class='toggle-checkbox' type='checkbox' id='toggle-sl' onchange='handleSL()'></div><div style='text-align: center;'><span id='joystick-value-display'></span></div><div class='joystick-container'><div class='joystick' id='joystick'></div></div><div class='sliders'><div class='slider-container'><label class='common-label' id='labelslider1' for='slider1'>Acceleration</label><input type='range' id='slider1' class='slider' min='0' max='100' value='0' onchange="sendSliderData('slider1')"></div><div class='slider-container'><label class='common-label' id='labelslider2' for='slider2'>Slider 2: 0</label><input type='range' id='slider2' class='slider' min='0' max='100' value='0' onchange="sendSliderData('slider2')"></div></div><div class='buttons'><button id='switch5' class='button' onclick='toggleSwitch(5)'>SW 5</button><button id='switch6' class='button' onclick='toggleSwitch(6)'>SW 6</button><button id='switch7' class='button' onclick='toggleSwitch(7)'>SW 7</button><button id='switch8' class='button' onclick='toggleSwitch(8)'>SW 8</button><button id='push5' class='button' onmousedown='sendPushData(5, 1)' onmouseup='sendPushData(5, 0)' ontouchstart='sendPushData(5, 1)' ontouchend='sendPushData(5, 0)'>Push 5</button><button id='push6' class='button' onmousedown='sendPushData(6, 1)' onmouseup='sendPushData(6, 0)' ontouchstart='sendPushData(6, 1)' ontouchend='sendPushData(6, 0)'>Push 6</button><button id='push7' class='button' onmousedown='sendPushData(7, 1)' onmouseup='sendPushData(7, 0)' ontouchstart='sendPushData(7, 1)' ontouchend='sendPushData(7, 0)'>Push 7</button><button id='push8' class='button' onmousedown='sendPushData(8, 1)' onmouseup='sendPushData(8, 0)' ontouchstart='sendPushData(8, 1)' ontouchend='sendPushData(8, 0)'>Push 8</button></div><script>const joystick = document.getElementById('joystick');
const joystickContainer = document.querySelector('.joystick-container');
const toggleReturn = document.getElementById('toggle-return');
const statusLabel = document.getElementById('status');

const url = `ws://${window.location.hostname}/ws`;

let joystickOffset = { x: 0, y: 0 };
let isDragging = false;
let xPos = 0;
let yPos = 0;

let socket;

// Initialize WebSocket
function initWebSocket(url) {
    socket = new WebSocket(`ws://${window.location.hostname}/ws`);

    socket.onopen = function () {
        console.log("WebSocket connection opened");
        updateStatus(true);
    };

    socket.onmessage = function (event) {
        handleWebsocketMessage(event);
    };

    socket.onclose = function () {
        console.log("WebSocket connection closed");
        updateStatus(false);
        setTimeout(initWebSocket(url), 1000); // try to reconnect in every second
    };

    socket.onerror = function (error) {
        console.error("WebSocket error: ", error);
        updateStatus(false);
    };
}

function handleWebsocketMessage(event) {
    const data = JSON.parse(event.data);
    switch (data.type) {
        case "log":
            handleLog(data.message);
            break;
        default:
            console.log('Unknown message type:', data.type);
            break;
    }
}

function handleLog(message) {
    console.log("[Robot] ", message);
    const logsElement = document.getElementById('logs');
    const logEntry = document.createElement('p');
    logEntry.textContent = message;
    logsElement.appendChild(logEntry);
}

function sendData(dataObject) {
    const dataJson = JSON.stringify(dataObject);
    socket.send(dataJson);
}

// Send joystick position
function sendJoystickAndMotorData(x, y) {

    // Make the stop command priority to always send it
    let priority = false
    if (x === 0 && y === 0) {
        priority = true;
    }

    // send the normal packages with a 200ms interval, to prevent overloading the server
    // the priority packages can be sent anytime
    if (!priority && sendJoystickAndMotorData.lastSent && Date.now() - sendJoystickAndMotorData.lastSent < 200) {
        return;
    }
    sendJoystickAndMotorData.lastSent = Date.now();

    // Send joystick data to server
    const joyX = Math.round(x * 127);
    const joyY = Math.round(y * (-127));
    const data = { type: 'joystick', x: joyX, y: joyY };
    sendData(data, priority);
    console.log("Joystick data sent: ", data);

    // limit rotation to 50% throttle
    x = x * 0.5;

    // Send motor data to server
    const motorData = convertJoystickDataToMotorData(x, y);

    // show data on joysticks value display
    document.getElementById('joystick-value-display').innerHTML = `joyX: ${joyX} joyY: ${joyY}; motor1: ${motorData.motor1} motor2: ${motorData.motor2}`;

    sendMotorData("leftDrive", motorData.motor1);
    sendMotorData("rightDrive", motorData.motor2);
}

function convertJoystickDataToMotorData(rotate, drive) {
    // Source: https://xiaoxiae.github.io/Robotics-Simplified-Website/drivetrain-control/arcade-drive/
    let leftMotor = 0;
    let rightMotor = 0;

    // variables to determine the quadrants
    const maximum = Math.max(Math.abs(drive), Math.abs(rotate));
    let total = drive + rotate;
    let difference = drive - rotate;

    if (drive >= 0) {
        if (rotate >= 0) {  // I quadrant
            leftMotor = maximum;
            rightMotor = difference;
        } else {            // II quadrant
            leftMotor = total;
            rightMotor = maximum;
        }
    } else {
        if (rotate >= 0) {  // IV quadrant
            leftMotor = total;
            rightMotor = -maximum;
        } else {            // III quadrant
            leftMotor = -maximum;
            rightMotor = difference;
        }
    }

    // Normalize left and right motor value to -127 to 127
    leftMotor = Math.round(leftMotor * -127);
    rightMotor = Math.round(rightMotor * -127);

    return { motor1: leftMotor, motor2: rightMotor };
}

function sendMotorData(id, x) {
    const data = { type: 'motor', id: id, value: x };
    sendData(data);
}

// Send slider data
function sendSliderData(id) {
    const data = { type: 'slider', id: id, value: document.getElementById(id).value };
    // set the slider label to the slider name and then value of the slider like Slider 1: 50
    document.getElementById('label' + id).innerHTML = "Acceleration: " + slider1.value;
    sendData(data)
}

function initSliders() {
    // initialize the sliders to 0
    document.getElementById('slider1').value = 0;
    document.getElementById('slider2').value = 0;
}
initSliders();

// Toggle switch
function toggleSwitch(id) {
    const button = document.getElementById('switch' + id);
    const isOn = button.classList.toggle('switch-on');  // Toggle switch status
    const value = isOn ? 1 : 0;
    const data = { type: 'switch', id: id, value: value };
    sendData(data);
}

// Send push button data
function sendPushData(id, value) {
    const button = document.getElementById('push' + id);
    const data = { type: 'push', id: id, value: value };
    sendData(data);

    // Add visual effect on press
    if (value === 1) {
        button.classList.add('push-active');
    } else {
        button.classList.remove('push-active');
    }
}

// Joystick drag and reset
joystick.addEventListener('mousedown', startDrag);
joystick.addEventListener('touchstart', startDrag, { passive: true });


function startDrag(event) {
    //event.preventDefault(); TODO: Causes exception, but I dont know why does it needed
    isDragging = true;

    document.addEventListener('mousemove', dragJoystick);
    document.addEventListener('mouseup', stopDrag);
    document.addEventListener('touchmove', dragJoystick, { passive: true });
    document.addEventListener('touchend', stopDrag);

    const rect = joystickContainer.getBoundingClientRect();

    if (event.touches) {
        joystickOffset.x = event.touches[0].clientX - rect.left - xPos;
        joystickOffset.y = event.touches[0].clientY - rect.top - yPos;
    } else {
        joystickOffset.x = event.clientX - rect.left - xPos;
        joystickOffset.y = event.clientY - rect.top - yPos;
    }
}

function dragJoystick(event) {
    if (!isDragging) return;

    const rect = joystickContainer.getBoundingClientRect();
    const limitRadius = rect.width / 2 - joystick.offsetWidth / 2;

    if (event.touches) {
        xPos = event.touches[0].clientX - rect.left - joystickOffset.x;
        yPos = event.touches[0].clientY - rect.top - joystickOffset.y;
    } else {
        xPos = event.clientX - rect.left - joystickOffset.x;
        yPos = event.clientY - rect.top - joystickOffset.y;
    }

    const distance = Math.sqrt(xPos * xPos + yPos * yPos);
    if (distance > limitRadius) {
        const angle = Math.atan2(yPos, xPos);
        xPos = limitRadius * Math.cos(angle);
        yPos = limitRadius * Math.sin(angle);
    }

    joystick.style.left = `${xPos + rect.width / 2}px`;
    joystick.style.top = `${yPos + rect.height / 2}px`;

    // Send joystick data to server
    sendJoystickAndMotorData(xPos / limitRadius, yPos / limitRadius);
}

function stopDrag() {
    isDragging = false;
    document.removeEventListener('mousemove', dragJoystick);
    document.removeEventListener('mouseup', stopDrag);
    document.removeEventListener('touchmove', dragJoystick);
    document.removeEventListener('touchend', stopDrag);

    if (toggleReturn.checked) {
        sendJoystickAndMotorData(0, 0);
        xPos = 0;
        yPos = 0;
        joystick.style.left = '50%';
        joystick.style.top = '50%';
    }
}
function updateStatus(isConnected) {
    if (isConnected) {
        statusLabel.textContent = 'Connected';
        statusLabel.classList.remove('status-disconnected');
        statusLabel.classList.add('status-connected');

    } else {
        statusLabel.textContent = 'Disconnected';
        statusLabel.classList.remove('status-connected');
        statusLabel.classList.add('status-disconnected');
    }
}
function handleToggleChange() {
    if (toggleReturn.checked) {
        sendJoystickAndMotorData(0, 0);
        xPos = 0;
        yPos = 0;
        joystick.style.left = '50%';
        joystick.style.top = '50%';
    } else {
        console.log('Return to Home is disabled');
        // Add your logic here for when the checkbox is unchecked
    }
}

function handleSL() {
    // make the container unscrollable when the checkbox is checked
    if (document.getElementById('toggle-sl').checked) {
        // disable touch action of container
        document.querySelector('.container').style.touchAction = 'none';
    } else {
        // enable touch action of container
        document.querySelector('.container').style.touchAction = 'auto';
    }
}

window.onload = initWebSocket(url);

/* Open when someone clicks on the span element */
function openLogMenu() {
    document.getElementById("terminalOverlay").style.width = "100%";
}

/* Close when someone clicks on the "x" symbol inside the overlay */
function closeLogMenu() {
    document.getElementById("terminalOverlay").style.width = "0%";
}

function openOptionsMenu() {
    document.getElementById("optionsOverlay").showModal();
}

function closeOptionsMenu() {
    document.getElementById("optionsOverlay").close();
}</script></div></body></html>)rawliteral";