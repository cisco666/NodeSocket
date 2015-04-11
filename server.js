
var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var port=5000;

app.get('/',function(req,res)
{
	res.sendFile(__dirname + '/index.html')
});

var SerialPort = require("serialport").SerialPort;
var portS="COM3";
var serialPort = new SerialPort(portS, {
  baudrate: 9600
},false);
serialPort.open(function (error) 
{
  	if ( error ) 
  	{
    	console.log('Failed to open port: '+portS+" "+error);
    } 
    else 
    {
    	console.log('Serial Port Opend');
		io.sockets.on('connection', function(socket)
		{
			console.log(' - A User Connected !!!');
		    var lastValue;
		    serialPort.on('data', function(data)
		    {
		    	var readData = data.toString(); 	 
				if(lastValue !== readData)
				{
				  	socket.emit('data', readData);
				}
				lastValue = readData;
		    });
		});
    }
});

http.listen(port, function()
{
  console.log('Listening on port :'+port);
});