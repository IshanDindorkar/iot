var NodeHelper = require("node_helper");

module.exports = NodeHelper.create({

    start: function () {
        // Run pocketsphinx_continuous
        var spawn = require("child_process").spawn;
        var self = this;
        process.env.LD_LIBRARY_PATH = "/usr/local/lib";
        var recog = spawn("/usr/local/bin/pocketsphinx_continuous", [
            "-inmic", "yes", "-adcdev", "plughw:1,0", "-lm", "4074.lm", "-dict", "4074.dic"
        ], { env: process.env, cwd: "/home/pi/MagicMirror/lmtool"});

        recog.stdout.on("data", function (data) {
            var lines = data.toString().split(/[\r\n]+/);
            var cmd;
            lines.forEach(function(ln) {
                if (ln.match(/^[0-9]{9}:\s*JIGSAW/)) {
                    console.log(ln);
                    cmd = ln.replace(/^.*JIGSAW/, 'JIGSAW');
                    console.log(cmd);
                    cmd_1 = cmd.replace(/\s*/,'');
                    console.log(cmd_1);
                    cmd_2 = cmd_1.replace(/\s+/g, '_');
                    cmd = cmd_2;
                }
            });
            console.log("Got command", cmd);
            self.sendSocketNotification(cmd, {});
        });

        recog.stderr.on("data", function (data) {
        });

        recog.on("exit", function (code) {
            console.log("Unexpected exit");
        });

    },
    socketNotificationReceived: function(notification, payload) {
        console.log("Notification received by node helper of scmds");
        console.log(notification);
    }
});