/* global Log, Module, moment */


Module.register("cam",{

	// Module config defaults.
	defaults: {
		updateInterval: 1000,
		fadeSpeed: 4000
	},

	// Define required scripts.
	getScripts: function() {
		return [
			this.file('cam.css')
		];
	},

	// Define start sequence.
	start: function() {
		Log.info("Starting module>>>>>: " + this.name);

		this.initDone = false;

		// Schedule update timer.
		var self = this;
		//self.sendSocketNotification("GET_COOKIE", {});
		//self.updateDom(this.config.fadeSpeed);
		setInterval(function() {
			if (self.initDone)
				return;
			var video = document.getElementById('video');
			console.log("CAM video=", video);
			if (!video)
				return;
			// Get access to the camera!
			if(navigator.mediaDevices && navigator.mediaDevices.getUserMedia) {
			    // Not adding `{ audio: true }` since we only want video now
			    navigator.mediaDevices.getUserMedia(
			    	{ 
			    		video: true/*{
			    			width : {exact : 640},
      						height : {exact: 480}
			    			width : {exact : 320},
      						height : {exact: 240},
      						minFrameRate: 60,
      					}*/
      				}
      			).then(function(stream) {
			        video.src = window.URL.createObjectURL(stream);
			        video.play();
			    });
			}

			self.initDone = true;
		}, this.config.updateInterval);
	},

	socketNotificationReceived: function(notification, payload) {
		/*if (notification === "GOT_COOKIE") {
			this.cookie = payload;
			this.updateDom(this.config.fadeSpeed);
			return;
		}*/
	},


	// Override dom generator.
	getDom: function() {

		var el = document.createElement("div");
		el.innerHTML = '<div class="fullscreen"><video class="flip" id="video" autoplay></video></div>';
			console.log("CAM getDom=", el);
		return el;
	}

});
