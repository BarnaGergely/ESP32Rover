// This file is generated by `build_file_system_image.py`. Do not edit it. Run Build Filesystem Image to update it.
// Source Files: `web/src/index.html` and its dependencies
const char index_html[] PROGMEM = R"rawliteral(<html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><meta name='color-scheme' content='dark light'><style>:root{--clr-bg-1:#f0f0f0;--clr-bg-2:#e0e0e0;--clr-bg-3:#ccc;--clr-bg-joy:radial-gradient(circle,var(--clr-bg-1),var(--clr-bg-3));--clr-bg-cont:linear-gradient(135deg,var(--clr-bg-1),var(--clr-bg-2));--clr-btn:#28a745;--clr-success:#28a745;--clr-failed:#dc3545;--clr-brd-joy:1px solid #bbb}body{font-family:'Arial',sans-serif;display:flex;flex-direction:column;align-items:center;justify-content:top;height:100vh;margin:2px;padding:5px;background-color:var(--clr-bg-1);box-sizing:border-box}.container{display:flex;flex-direction:column;align-items:center;gap:5px;padding:0px 15px 0px 15px;background:var(--clr-bg-cont);border:1px solid #ccc;border-radius:15px;box-shadow:0 4px 8px rgba(0,0,0,0.1);margin:10px auto;max-width:95%}.joystick-container{position:relative;width:250px;height:250px;background:var(--clr-bg-joy);border-radius:50%;box-shadow:0 8px 16px rgba(0,0,0,0.2);border:1px solid var(--clr-brd-joy);display:flex;justify-content:center;align-items:center}.joystick-container::before,.joystick-container::after{content:'';position:absolute;background-color:#cfcfcf}.joystick-container::before{width:1px;height:100%;top:0;left:50%;transform:translateX(-50%)}.joystick-container::after{width:100%;height:1px;top:50%;left:0;transform:translateY(-50%)}.joystick{position:absolute;width:50px;height:50px;background:radial-gradient(circle,#007bff,#0056b3);border-radius:50%;top:50%;left:50%;transform:translate(-50%,-50%);box-shadow:0 8px 16px rgba(0,0,0,0.2);touch-action:none;border:2px solid #004080;z-index:1}.joystick::before{content:'';position:absolute;width:10px;height:10px;background-color:rgb(121,25,25);border-radius:50%;top:50%;left:50%;transform:translate(-50%,-50%);box-shadow:0 2px 4px rgba(0,0,0,0.2)}.sliders{display:flex;flex-direction:column;justify-content:center;align-items:center;padding:10px;gap:10px}.slider-container{display:flex;flex-direction:column;align-items:center}.slider{-webkit-appearance:none;appearance:none;width:300px;height:15px;background:linear-gradient(to right,green,red);outline:none;opacity:0.7;transition:opacity .2s;border-radius:10px}.slider:hover{opacity:1}.slider::-webkit-slider-thumb{-webkit-appearance:none;appearance:none;width:25px;height:25px;background:#4CAF50;cursor:pointer;border-radius:5px}.slider::-moz-range-thumb{width:25px;height:30px;background:#4CAF50;cursor:pointer;border-radius:5px}.buttons{display:flex;justify-content:space-around;width:330px;flex-wrap:wrap}.button{width:70px;height:60px;background-color:var(--clr-btn);border:none;color:white;font-size:16px;border-radius:10px;box-shadow:0 4px 8px rgba(0,0,0,0.2);cursor:pointer;transition:background-color 0.3s ease;margin:5px;user-select:none}.button.switch-on{background-color:#ff0707}.button.push-active{background-color:#0056b3;user-select:none}.common-label{font-size:16px;font-weight:bold;margin-right:1px;color:#333}.toggle-checkbox{width:20px;height:20px;cursor:pointer;accent-color:#007bff}.check-button-container{display:flex;justify-content:left;width:100%;align-items:center;gap:5px}.status-label{font-size:14px;font-weight:bold;padding:5px 10px;border-radius:5px;color:#fff}.status-connected{background-color:var(--clr-success)}.status-disconnected{background-color:var(--clr-failed)}</style><title>ESP8266/32 Joystick Control</title></head><body><div class='container'><div id='status' class='status-label status-disconnected'>Disconnected</div><div class='buttons'><button id='switch1' class='button' onclick='toggleSwitch(1)'>SW 1</button><button id='switch2' class='button' onclick='toggleSwitch(2)'>SW 2</button><button id='switch3' class='button' onclick='toggleSwitch(3)'>SW 3</button><button id='switch4' class='button' onclick='toggleSwitch(4)'>SW 4</button><button id='push1' class='button' onmousedown='sendPushData(1, 1)' onmouseup='sendPushData(1, 0)' ontouchstart='sendPushData(1, 1)' ontouchend='sendPushData(1, 0)'>Push 1</button><button id='push2' class='button' onmousedown='sendPushData(2, 1)' onmouseup='sendPushData(2, 0)' ontouchstart='sendPushData(2, 1)' ontouchend='sendPushData(2, 0)'>Push 2</button><button id='push3' class='button' onmousedown='sendPushData(3, 1)' onmouseup='sendPushData(3, 0)' ontouchstart='sendPushData(3, 1)' ontouchend='sendPushData(3, 0)'>Push 3</button><button id='push4' class='button' onmousedown='sendPushData(4, 1)' onmouseup='sendPushData(4, 0)' ontouchstart='sendPushData(4, 1)' ontouchend='sendPushData(4, 0)'>Push 4</button></div><div class='check-button-container'><label class='common-label' for='toggle-return'>RTH:</label><input class='toggle-checkbox' type='checkbox' id='toggle-return' onchange='handleToggleChange()'><label class='common-label' for='toggle-sl'>SL:</label><input class='toggle-checkbox' type='checkbox' id='toggle-sl' onchange='handleSL()'></div><div class='joystick-container'><div class='joystick' id='joystick'></div></div><div class='sliders'><div class='slider-container'><label class='common-label' id='labelslider1' for='slider1'>Slider 1: 0</label><input type='range' id='slider1' class='slider' min='0' max='100' value='0' onchange='sendSlider1Data()'></div><div class='slider-container'><label class='common-label' id='labelslider2' for='slider2'>Slider 2: 0</label><input type='range' id='slider2' class='slider' min='0' max='100' value='0' onchange='sendSlider2Data()'></div></div><div class='buttons'><button id='switch5' class='button' onclick='toggleSwitch(5)'>SW 5</button><button id='switch6' class='button' onclick='toggleSwitch(6)'>SW 6</button><button id='switch7' class='button' onclick='toggleSwitch(7)'>SW 7</button><button id='switch8' class='button' onclick='toggleSwitch(8)'>SW 8</button><button id='push5' class='button' onmousedown='sendPushData(5, 1)' onmouseup='sendPushData(5, 0)' ontouchstart='sendPushData(5, 1)' ontouchend='sendPushData(5, 0)'>Push 5</button><button id='push6' class='button' onmousedown='sendPushData(6, 1)' onmouseup='sendPushData(6, 0)' ontouchstart='sendPushData(6, 1)' ontouchend='sendPushData(6, 0)'>Push 6</button><button id='push7' class='button' onmousedown='sendPushData(7, 1)' onmouseup='sendPushData(7, 0)' ontouchstart='sendPushData(7, 1)' ontouchend='sendPushData(7, 0)'>Push 7</button><button id='push8' class='button' onmousedown='sendPushData(8, 1)' onmouseup='sendPushData(8, 0)' ontouchstart='sendPushData(8, 1)' ontouchend='sendPushData(8, 0)'>Push 8</button></div></div><script>const joystick = document.getElementById('joystick');
const joystickContainer = document.querySelector('.joystick-container');
const slider1 = document.getElementById('slider1');
const slider2 = document.getElementById('slider2');
const toggleReturn = document.getElementById('toggle-return');
const statusLabel = document.getElementById('status');

const url = 'ws://127.0.0.1/';  // Replace with your server's IP and port

let joystickOffset = { x: 0, y: 0 };
let isDragging = false;
let xPos = 0;
let yPos = 0;

let socket;

// Initialize WebSocket
function initWebSocket(url) {
    socket = new WebSocket(url);

    socket.onopen = function () {
        console.log("WebSocket connection opened");
        updateStatus(true);
    };

    socket.onmessage = function (event) {
        console.log("Message from server: ", event.data);
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

function sendData(dataObject, priority = false) {

    // send the normal packages with a 200ms interval, to prevent overloading the server
    // the priority packages can be sent anytime
    if (!priority && sendData.lastSent && Date.now() - sendData.lastSent < 200) {
        return;
    }

    sendData.lastSent = Date.now();
    const dataJson = JSON.stringify(dataObject);
    socket.send(dataJson);
}

// Send joystick position
function sendJoystickData(x, y) {
    const data = { type: 'joystick', x: Math.round(x * 125), y: Math.round(y * (-125)) };

    // Make the stop command priority to always send it
    let priority = false
    if (x === 0 && y === 0) {
        priority = true;
    }

    sendData(data, priority);
}

// Send slider data
function sendSlider1Data() {
    const data = { slider1: slider1.value };
    // set the slider label to the slider name and then value of the slider like Slider 1: 50
    document.getElementById('labelslider1').innerHTML = "Slider 1: " + slider1.value;
    sendData(data)
}

// Send slider data
function sendSlider2Data() {
    const data = { slider2: slider2.value };
    document.getElementById('labelslider2').innerHTML = "Slider 2: " + slider2.value;
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
    sendJoystickData(xPos / limitRadius, yPos / limitRadius);
}

function stopDrag() {
    isDragging = false;
    document.removeEventListener('mousemove', dragJoystick);
    document.removeEventListener('mouseup', stopDrag);
    document.removeEventListener('touchmove', dragJoystick);
    document.removeEventListener('touchend', stopDrag);

    if (toggleReturn.checked) {
        sendJoystickData(0, 0);
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
        sendJoystickData(0, 0);
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

window.onload = initWebSocket(url);</script></body></html>)rawliteral";