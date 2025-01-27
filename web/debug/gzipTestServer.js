const expressStaticGzip = require("express-static-gzip");
const express = require('express');
const app = express();
const http = require('http');
const WebSocket = require('ws');
const server = http.createServer(app);
const socket = new WebSocket.Server({ server });

const port = 80;

app.use("/", expressStaticGzip("data"));

app.use("/raw", express.static("web/src"));

socket.on('connection', function connection(ws) {
    ws.on('message', function incoming(data) {
        let doc
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
        } else {
            console.log("Unknown data received");
        }
    });

    ws.send('Connection established');
});

server.listen(port, function () {
    console.log("Server started on http://localhost:" + port);
});