var t = msg.payload.match(/t=([0-9]+)/)[1];
var cooler = 'off';
if (t >= 30)
    cooler = 'on';
msg.payload = cooler;
return msg;
