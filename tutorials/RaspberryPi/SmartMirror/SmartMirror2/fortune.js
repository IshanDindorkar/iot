/* global Log, Module, moment */


Module.register("fortune",{

	// Module config defaults.
	defaults: {
		updateInterval: 60000,
		fadeSpeed: 1000
	},

	// Define required scripts.
	getScripts: function() {
		return [];
	},

	// Define start sequence.
	start: function() {
		Log.info("Starting module: " + this.name);
		// Schedule update timer.
		var self = this;
		self.cookie = '';
		self.show = true;
		self.sendSocketNotification("GET_COOKIE", {});
		setInterval(function() {
			self.sendSocketNotification("GET_COOKIE", {});
			
		}, this.config.updateInterval);
	},

	socketNotificationReceived: function(notification, payload) {
		if (notification === "GOT_COOKIE") {
			this.cookie = payload;
			this.updateDom(this.config.fadeSpeed);
		}
	},
	notificationReceived: function (notification, payload) {
		if (notification === "JIGSAW_SHOW_FORTUNE") {
			this.show = true;
			this.updateDom(this.config.fadeSpeed);
		} else if (notification == "JIGSAW_HIDE_FORTUNE") {
			this.show = false;
			this.updateDom(this.config.fadeSpeed);
		}
	},

	// Override dom generator.
	getDom: function() {
		//var fc = document.createTextNode(this.cookie);
		var fc = document.createElement("span");
		if (this.show)
			fc.innerHTML = this.cookie;
		else
			fc.innerHTML = '';
		fc.style.fontSize = '60%';
		var wrapper = document.createElement("div");
		wrapper.className = "thin xlarge bright";
		wrapper.appendChild(fc);

		return wrapper;
	}

});
