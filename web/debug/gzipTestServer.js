const expressStaticGzip = require("express-static-gzip");
const express = require('express');
const app = express();
const http = require('http');
const webSocket = require('ws');
const server = http.createServer(app);
const wss = new webSocket.Server({ noServer: true });

const port = 80;

app.use("/", expressStaticGzip("data"));
app.use("/raw", express.static("web/src"));

server.on('upgrade', (request, socket, head) => {
    const pathname = request.url;

    if (pathname === '/ws') {
        wss.handleUpgrade(request, socket, head, (ws) => {
            wss.emit('connection', ws, request);
        });
    } else {
        socket.destroy();
    }
});

wss.on('connection', function connection(ws) {
    ws.on('message', function incoming(data) {
        let doc;
        try {
            doc = JSON.parse(data);
        } catch (error) {
            console.error("Failed to parse JSON:", error);
            return;
        }

        if (doc.type === "joystick") {
            console.log("Joystick data received: " + "x:", doc.x, "y:", doc.y);
        } else if (doc.slider1 > 0) {
            console.log("Slider 1 data received: " + "Slider 1:", doc.slider1);
        } else if (doc.slider2 > 0) {
            console.log("Slider 2 data received: " + "Slider 2:", doc.slider2);
        } else if (doc.type === "switch") {
            console.log("Switch data received: " + "Switch ID:", doc.id, "Value:", doc.value);
        } else if (doc.type === "push") {
            console.log("Push button data received: " + "Push button ID:", doc.id, "Value:", doc.value);
        } else if (doc.type === "motor") {
            console.log("Motor data received: " + "Motor ID:", doc.id, "Value:", doc.value);
        } else {
            console.log("Unknown data received");
        }
    });

    ws.send('Connection established');
});

server.listen(port, () => {
    console.log(`Server is listening on port http://localhost:${port}`);
});