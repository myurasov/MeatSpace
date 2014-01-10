server.log("Device Started");
 
arduino <- hardware.uart12;
 
R <- "";
M <- "";
 
function arduinoData() {
    local b = arduino.read();
    while(b != -1) {
        if (b > 200) { // Y
          b = b - 200;
          R = "Ralph=" + b;
        } else if (b > 100) {
          b = b - 100;
          M = "Mike=" + b;
          agent.send("update", R + ";" + M);
        }
        b = arduino.read();
    }
}


 
arduino.configure(9600, 8, PARITY_NONE, 1, NO_CTSRTS, arduinoData);
agent.send("update", "-");

 
