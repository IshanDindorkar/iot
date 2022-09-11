
var NodeHelper = require("node_helper");
var exec = require('child_process').exec;
module.exports = NodeHelper.create({
	// Subclass start method.
	start: function() {
		var self = this;
		console.log("Starting module+++++++++++: " + this.name);
		self.displayOnState = true;
		/*setInterval(function () {
			if (self.displayOnState)
				self.displayOff();
			else
				self.displayOn()
		}, 10000);*/
	},

	// Subclass socketNotificationReceived received.
	socketNotificationReceived: function(notification, payload) {
		if (notification === "GOT_FACE") {
		}
	},
	displayOff: function () {
		var self = this;
		console.log("Turning display OFF...");
		exec("/opt/vc/bin/tvservice -o", function (err, out) {
			if (err) {
				console.error("OFF error", err);
				return;
			}
			console.log("Display is OFF");
			self.displayOnState = false;
		});
	},
	displayOn: function () {
		var self = this;
		console.log("Turning display ON...");
		exec("/opt/vc/bin/tvservice -p", function (err, out) {
			if (err) {
				console.error("ON error", err);
				return;
			}
			exec("/usr/bin/xset dpms force on", function (err, out) {
				if (err) {
					console.error("ON error", err);
					return;
				}
				console.log("Display is ON");
				self.displayOnState = true;
			})
		});
	}

});
