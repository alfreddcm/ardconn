const express = require('express');
const http = require('http');
const socketIO = require('socket.io');
const SerialPort = require('serialport');

const app = express();
const server = http.createServer(app);
const io = socketIO(server);

const portName = '/dev/cu.wchusbserial1420';  // Change this to match your Arduino's serial port
const serialPort = new SerialPort(portName, { baudRate: 9600 });

serialPort.on('open', () => {
  console.log('Serial port open');
});

app.get('/', (req, res) => {
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', (socket) => {
  console.log('Client connected');

  serialPort.on('data', (data) => {
    const receivedTime = new Date().toLocaleTimeString(); // Get the current time
    const message = data.toString(); // Convert the received data to a string
    console.log(`Received data: ${message} at ${receivedTime}`);
    
    socket.emit('serialData', { message, receivedTime }); // Emit the data to the client
  });

  socket.on('toggleLED', (state) => {
    serialPort.write(state ? '1' : '0'); // Send '1' to turn on the LED and '0' to turn it off
  });
});

server.listen(3000, () => {
  console.log('Server listening on port 3000');
});
