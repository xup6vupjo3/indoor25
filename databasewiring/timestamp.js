let currentDate = new Date().toLocaleString([], {timeZone: "Asia/Taipei", hourCycle: 'h23',  seconds: 'long'});
msg.payload = {object:msg.payload, value:currentDate}; 

return msg; 