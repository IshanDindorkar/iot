
var NodeHelper = require("node_helper");
 module.exports = NodeHelper.create({
 start: function () {
    var spawn = require("child_process").spawn;
    var self = this;
    process.env.LD_LIBRARY_PATH = "/usr/local/lib";
    var recog = spawn("/usr/local/bin/pocketsphinx_continuous", [
                "-inmic", "yes", "-adcdev", "plughw:1,0", "-lm", "0277.lm", "-dict", "0277.dic"
            ], { env: process.env, cwd: "/home/pi/MagicMirror/lmtool"});
    recog.stdout.on('data', function(data) {
          var lines = data.toString();
          var trimlines = lines.trim();
          console.log(trimlines);
          var cmd;
    if (trimlines.match(/JIGSAW/)) {
        cmd = trimlines.replace(/^.*JIGSAW/,'JIGSAW').replace(/\s+/g, '_');
       }
          console.log("scmds helper: Got command ", cmd);
          self.sendSocketNotification(cmd, {});
        });
    recog.stderr.on('data', function (data) {
        });
    recog.on('exit', function (code) {
        console.log("Unexpexted Exit");
      });
    }
});
