cmd_/home/pi/blink/modules.order := {   echo /home/pi/blink/blink.ko; :; } | awk '!x[$$0]++' - > /home/pi/blink/modules.order
