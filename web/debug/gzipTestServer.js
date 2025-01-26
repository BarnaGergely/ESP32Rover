var express = require("express");
var expressStaticGzip = require("express-static-gzip");
var app = express();

app.use("/", expressStaticGzip("data"));

app.listen(3000);
console.log("Server started on http://localhost:3000");