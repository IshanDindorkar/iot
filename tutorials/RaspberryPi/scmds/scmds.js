Module.register("scmds", {
    // Leave this module as it is since we don't have to display anything
    start: function () {
        Log.info("Starting module: " + this.name);
        this.sendSocketNotification("OPEN_CONNECTION", {});
    },

    socketNotificationReceived: function(notification, payload) {
        Log.info("notification in scmds");
        Log.info(notification);
		this.sendNotification(notification, payload); 
	}
});