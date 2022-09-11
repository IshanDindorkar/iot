var mosca = require('mosca');

var pubsubSettings = {
    type: 'redis',
    redis: require('redis'),
    host: "localhost",
    port: 6379,
    db: 1,
    return_buffers: true
}

var settings = {
    // port: 1883
    backend: pubsubSettings
}

var server = new mosca.Server(settings);

// fired when mqtt server is ready
server.on('ready', function() {
    console.log('Mosca server is up and running');
})

// firec when a client is connected
server.on('clientConnected', function(client) {
    console.log('Client connected', client.id);
})

// fired when a message is received
server.on('published', function(packet, client) {
    console.log('Published', packet.payload);
})