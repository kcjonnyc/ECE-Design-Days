var SerialPort = require("serialport");

module.exports = function(app, passport) {

    app.get('/', function(req, res) {
        res.render('index.pug');

        // serial port initialization:
        var serialport = require('serialport'), // include the serialport library
            SerialPort = serialport, // make a local instance of serial
            portName = 'COM5', // get the port name from the command line
            portConfig = {
                baudRate: 9600,
                // call myPort.on('data') when a newline is received:
                parser: serialport.parsers.readline('\n')
            };

        // open the serial port:
        var myPort = new SerialPort(portName, portConfig);

        myPort.on('open', openPort); // called when the serial port opens
    });

    app.post('/sendspeed', function(req, res) {

        function openPort() {
            var brightness = 0; // the brightness to send for the LED
            console.log('port open');
            console.log('baud rate: ' + myPort.options.baudRate);

            // since you only send data when the port is open, this function
            // is local to the openPort() function:
            function sendData() {
                // convert the value to an ASCII string before sending it:
                myPort.write(req.body.speed); // TO CHANGE THE SPEED OF THE MOTOR
                // SECTION TO INCREMEMENT THE BRIGHTNESS OF THE LED
                /*console.log('Sending ' + brightness + ' out the serial port');
                // increment brightness by 50 points. Rollover if > 255:
                if (brightness < 255) {
                     brightness+= 50;
                } else {
                     brightness = 0;
                }*/
            }
            // set an interval to update the info 2 times per second: FOR AUTOMATED CHANGES
            setInterval(sendData, 500);
        }
        console.log("SUCCESSFUL CHANGE OF THE SPEED");
        console.log(req.body.speed);
        res.redirect('/')
    });

    app.post('/motor', function(req, res) {

        function openPort() {

            // since you only send data when the port is open, this function
            // is local to the openPort() function:
            function sendData() {
                // convert the value to an ASCII string before sending it:
                myPort.write(req.body.motor);

            }
            // set an interval to update the info 2 times per second: FOR AUTOMATED CHANGES
            setInterval(sendData, 500);
        }
        console.log("SUCCESSFUL CHANGE OF THE MOTOR");
        console.log(req.body.motor);
        res.redirect('/')
    });

};
