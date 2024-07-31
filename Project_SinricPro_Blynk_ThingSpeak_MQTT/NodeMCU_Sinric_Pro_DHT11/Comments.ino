

/*
 * Example for how to use SinricPro Temperaturesensor device:
 * - setup a temperature sensor device
 * - send temperature event to SinricPro server when temperature has changed
 * 
 * DHT Sensor is connected to D5 on ESP8266 devices / GPIO5 on ESP32 devices
 *
 * DHT Library used in this example: https://github.com/markruys/arduino-DHT
 * 
 * If you encounter any issues:
 * - check the readme.md at https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md
 * - ensure all dependent libraries are installed
 *   - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#arduinoide
 *   - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#dependencies
 * - open serial monitor and check whats happening
 * - check full user documentation at https://sinricpro.github.io/esp8266-esp32-sdk
 * - visit https://github.com/sinricpro/esp8266-esp32-sdk/issues and check for existing issues or open a new one
 */

/* bool onPowerState(String deviceId, bool &state) 
 *
 * Callback for setPowerState request
 * parameters
 *  String deviceId (r)
 *    contains deviceId (useful if this callback used by multiple devices)
 *  bool &state (r/w)
 *    contains the requested state (true:on / false:off)
 *    must return the new state
 * 
 * return
 *  true if request should be marked as handled correctly / false if not
 */


/* handleTemperatatureSensor()
 * - Checks if Temperaturesensor is turned on
 * - Checks if time since last event > EVENT_WAIT_TIME to prevent sending too much events
 * - Get actual temperature and humidity and check if these values are valid
 * - Compares actual temperature and humidity to last known temperature and humidity
 * - Send event to SinricPro Server if temperature or humidity changed
 */



// setup function for WiFi connection


// setup function for SinricPro


// main setup function

//  temperature = dht.getTemperature() * 1.8f + 32;  // get actual temperature in °F

// Uncomment the following line to enable serial debug output

//  SinricPro.restoreDeviceStates(true); // Uncomment to restore the last known state from the server.

// get actual temperature in °C

 //0=d3 --(DHTPIN,DHTTYPE)(DHT11,DHT22)

   //ZAINI MIFTAH   m
    //120812rj    1qazmlp0

     //D4

     //timeout 120s
