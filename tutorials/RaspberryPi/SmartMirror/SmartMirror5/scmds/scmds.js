/* global Log, Module, moment */


Module.register("scmds",{
	// Define start sequence.
	start: function() {
		Log.info("Starting module: " + this.name);
		this.sendSocketNotification("OPEN_CONNECTION");
	},

	socketNotificationReceived: function(notification, payload) {
		if (notification.match(/^JIGSAW/)) {
			console.log("notification in scmds", notification);
			this.sendNotification(notification, payload); 
		}
	}

});
