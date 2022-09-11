/* global Log, Module, moment */


Module.register("camera",{

	// Module config defaults.
	defaults: {
		updateInterval: 1000,
		fadeSpeed: 4000
	},

	// Define required scripts.
	getScripts: function() {
		return [
			this.file('cam.css'),
			this.file('tracking-min.js'),
			this.file('face-min.js'),
		];
	},

	// Define start sequence.
	start: function() {
		var self = this;
		Log.info("Starting module>>>>>: " + self.name);

		self.initDone = false;
		var tracker = new tracking.ObjectTracker('face');
		tracker.setInitialScale(1);
		tracker.setStepSize(2);
		tracker.setEdgesDensity(0.1);
		tracker.on('track', function(event) {
			console.log("Found faces=", event.data.length);
			self.sendSocketNotification("GOT_FACE", event.data.length);
		});
		self.tracker = tracker;
		self.hiddenCanvas = document.createElement("canvas");
		self.hiddenCanvas.width = 320;
		self.hiddenCanvas.height = 240;
		self.hiddenCanvasContext = self.hiddenCanvas.getContext("2d");
		setInterval(function() {
			console.log("1 Tracking start!");
			if (self.initDone)
				return;
			console.log("2 Tracking start!");
			var video = document.getElementById('video');
			if (!video)
				return;
			navigator.mediaDevices.getUserMedia(
			    	{	video: true 	
			    		// video: {
			    		// 	//width : {exact : 640},
      					// 	//height : {exact: 480}
			    		// 	//width : {exact : 320},
      					// 	//height : {exact: 240},
      					// 	//minFrameRate: 60,
      					// 	mandatory: {
						// 	minWidth: 640,
						// 	minHeight: 480
						// },
						// optional: [
						// 	{ minFrameRate: 60 }
						// ]
      				}
      			// }
      			).then(function(stream) {
			        // video.src = window.URL.createObjectURL(stream);
			        video.srcObject = stream;
					video.play();
			    });
			self.initDone = true;
			setInterval(function () {
				self.hiddenCanvasContext.drawImage(video, 0, 0, 320, 240);
				tracking.track(self.hiddenCanvas, self.tracker);
			}, 5000);
			/*console.log("Tracking start!");
		      var tracker = new tracking.ObjectTracker('face');
		      tracker.setInitialScale(4);
		      tracker.setStepSize(2);
		      tracker.setEdgesDensity(0.1);

		      tracking.track('#video', tracker, { camera: true });

		      tracker.on('track', function(event) {
		      	console.log("Found faces=", event.data.length);
		      });*/
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
		return el;
	}

});
