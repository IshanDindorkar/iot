
var NodeHelper = require("node_helper");

module.exports = NodeHelper.create({
	// Subclass start method.
	start: function() {
		console.log("Starting module: " + this.name);
	},

	// Subclass socketNotificationReceived received.
	socketNotificationReceived: function(notification, payload) {
		var self = this;
		if (notification === "GET_COOKIE") {
			var fc = require('child_process').exec('/usr/games/fortune -s', function (err, f) {
				if (err)
					return;
				self.sendSocketNotification("GOT_COOKIE", f.toString());	
			});
			return;
		}
	},

});
