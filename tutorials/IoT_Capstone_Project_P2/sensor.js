// Server IP
if (process.argv.length <= 2) {
    console.log("Usage: node sensor.js SERVER-IP");
    process.exit(-1);
}
var server = process.argv[2];

// MQTT client
try {
    var mqtt = require('mqtt');
    var client  = mqtt.connect('mqtt://' + server);
}
catch(error) {
    console.log("Please install mqtt client library using: npm install mqtt");
    process.exit(-1);
}

var id = 1; // Sensor ID
var timer = null;

client.on('connect', function(){
    timer = setInterval(function(){
        var t = newT(); // Temperature
        var h = newH(); // Humidity
        var payload = 'log,id=' + id + ' t=' + t + ',h=' + h;
        console.log(payload);
        client.publish('sensor', payload);
    }, 3000);
});

client.on('disconnect', function(){
    clearTimeout(timer);
});

// Functions to generate cyclic values
var pT = 0, pH = 0;
function newT() {
    pT += 0.03;
    return 28 + Math.floor(5.2 * Math.sin(pT));
}
function newH() {
    pH += 0.05;
    return 48 + Math.floor(10.2 * Math.cos(pH));
}
