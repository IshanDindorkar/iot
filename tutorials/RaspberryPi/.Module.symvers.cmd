cmd_/home/pi/blink/Module.symvers := sed 's/ko$$/o/' /home/pi/blink/modules.order | scripts/mod/modpost -m -a   -o /home/pi/blink/Module.symvers -e -i Module.symvers   -T -
