cmd_/home/pi/blink/blink.ko := ld -r  -EL  --build-id=sha1  -T scripts/module.lds -o /home/pi/blink/blink.ko /home/pi/blink/blink.o /home/pi/blink/blink.mod.o;  true
