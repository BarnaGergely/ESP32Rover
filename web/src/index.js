const joystick = document.getElementById('joystick');
const joystickContainer = document.querySelector('.joystick-container');
const slider1 = document.getElementById('slider1');
const slider2 = document.getElementById('slider2');
const toggleReturn = document.getElementById('toggle-return');
const statusLabel = document.getElementById('status');

const url = 'ws://192.168.0.112/';

let joystickOffset = { x: 0, y: 0 };
let isDragging = false;
let xPos = 0;
let yPos = 0;

let socket;

// Initialize WebSocket
function initWebSocket(url) {
    socket = new WebSocket(url); // Replace with your server's IP and port

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
    };

    socket.onerror = function (error) {
        console.error("WebSocket error: ", error);
        updateStatus(false);
    };
}

function sendData(dataObject) {
    if (sendData.lastSent && Date.now() - sendData.lastSent < 200) {
        console.log('Data is being sent too fast, skipping this one:', dataObject);
        return;
    }

    sendData.lastSent = Date.now();
    const dataJson = JSON.stringify(dataObject);
    socket.send(dataJson);
}

// Send joystick position
function sendJoystickData(x, y) {
    const data = { type: 'joystick', x: Math.round(x * 125), y: Math.round(y * (-125)) };
    sendData(data);
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

window.onload = initWebSocket(url);