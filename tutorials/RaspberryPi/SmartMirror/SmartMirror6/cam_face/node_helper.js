
var NodeHelper = require("node_helper");
var exec = require('child_process').exec;
module.exports = NodeHelper.create({
	// Subclass start method.
	start: function() {
		var self = this;
		console.log("Starting module+++++++++++: " + this.name);
		self.displayState = 'ON';
		/*setInterval(function () {
			if (self.displayOnState)
				self.displayOff();
			else
				self.displayOn()
		}, 10000);*/
	},

	advanceState: function (event) {
		var self = this;
		switch (self.displayState) {
		case 'ON':
			if (event == 'NO_FACE')
				self.wait(true);
			break;
		case 'OFF':
			if (event == 'FACE')
				self.trigger(true);
			break;
		case 'WAIT':
			if (event == 'FACE')
				self.wait(false);
			break;
		}
	},
	trigger: function (on) {
		var self = this;
		self.displayState = 'TRIGGER';
		if (on)
			self.displayOn();
		else
			self.displayOff();
	},
	wait: function (start) {
		var self = this;
		if (start) {
			self.displayState = 'WAIT';
			console.log("Waiting to turn off");
			self.waiting = setTimeout(function () {
				self.trigger(false);
			}, 60000);
		} else {
			console.log("Cancelling turn off");
			clearTimeout(self.waiting);
			self.displayState = 'ON';
		}

	},
	// Subclass socketNotificationReceived received.
	socketNotificationReceived: function(notification, payload) {
		var self = this;
		if (notification === "GOT_FACE") {
			console.log("Got faces", payload);
			if (payload > 0)
				self.advanceState('FACE');
			else
				self.advanceState('NO_FACE');
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
			self.displayState = 'OFF';
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
				self.displayState = 'ON';
			})
		});
	}

});
