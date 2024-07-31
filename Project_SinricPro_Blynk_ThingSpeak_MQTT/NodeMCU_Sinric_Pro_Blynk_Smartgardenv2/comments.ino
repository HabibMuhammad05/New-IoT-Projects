/**********************************************************************************
 *  Download Board ESP8266 NodeMCU : https://github.com/esp8266/Arduino
 *  Download the libraries
 *  ArduinoJson Library: https://github.com/bblanchon/ArduinoJson
 *  arduinoWebSockets Library: https://github.com/Links2004/arduinoWebSockets
 *  SinricPro Library: https://sinricpro.github.io/esp8266-esp32-sdk/
 *  
 *  If you encounter any issues:
 * - check the readme.md at https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md
 * - ensure all dependent libraries are installed
 *   - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#arduinoide
 *   - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#dependencies
 * - open serial monitor and check whats happening
 * - check full user documentation at https://sinricpro.github.io/esp8266-esp32-sdk
 * - visit https://github.com/sinricpro/esp8266-esp32-sdk/issues and check for existing issues or open a new one
 **********************************************************************************/

// Uncomment the following line to enable serial debug output

//0=d3 --(DHTPIN,DHTTYPE)(DHT11,DHT22)

// this is the main configuration
// please put in your deviceId, the PIN for Relay and PIN for flipSwitch
// this can be up to N devices...depending on how much pin's available on your device ;)
// right now we have 4 devicesIds going to 4 relays and 4 flip switches to switch the relay manually


    //{deviceId, {relayPIN,  flipSwitchPIN}}
    
//    {device_ID_3, {  RelayPin3, SwitchPin3 }},
//   {device_ID_4, {  RelayPin4, SwitchPin4 }}   

  // struct for the std::map below

  // this map is used to map flipSwitch PINs to deviceId and handling debounce and last flipSwitch state checks
  // for each device (relay, flipSwitch combination)
  // get the relay pin
  // set relay pin to OUTPUT
  // for each device (relay / flipSwitch combination)
  // create a new flipSwitch configuration
  // set the deviceId
   // set debounce time
   // set lastFlipSwitchState to false (LOW)--
   // get the flipSwitchPIN
    // save the flipSwitch config to flipSwitches map
    // get the relay pin for corresponding device
     // set the new relay state
                                          // get actual millis
                                         // for each flipSwitch in flipSwitches map // get the timestamp when flipSwitch was pressed last time (used to debounce / limit events)

                      // if time is > debounce time...

                                     // get the flipSwitch pin from configuration
              // get the lastFlipSwitchState
                      // read the current flipSwitch state
                               // if the flipSwitchState has changed...

                                                       // if the tactile button is pressed 

                // update lastFlipSwitchChange time
                      // get the deviceId from config
                              // get the relayPIN from config
                            // set the new relay State
  
                      // get Switch device from SinricPro
                     // send the event

     
  
                    // update lastFlipSwitchState
                    // update lastFlipSwitchState
