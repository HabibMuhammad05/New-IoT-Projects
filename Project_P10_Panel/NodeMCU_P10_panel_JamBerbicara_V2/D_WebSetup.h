// ============================================= EEPROM ======================================
void write_EEPROM(int pos1, int pos2,String strText){
  int pj_strText=strText.length()+1;
  char stringIn[pj_strText];
  strText.toCharArray(stringIn,pj_strText);

  int j=-1;
  for(int i=pos1; i<pos2+1; i++){
    j++;
    if (i<pos1+pj_strText )  {
      EEPROM.write(i, stringIn[j]);
      EEPROM.commit();
    }else{
      EEPROM.write(i, '\0');
      EEPROM.commit();
    }
  }
}

String read_EEPROM(int pos1,int pos2){ 
  int i;
  char c;
  String temp="";
  for (i=pos1; i<pos2; i++){
    c=EEPROM.read(i);
    temp=temp+String(c);
  }
  temp=temp+'\0';
  return temp;
}

void reload_EEPROM(){
  //============= MAIN VAR =============
  T1_SSID  = read_EEPROM(51,100);
  T1_SSID  = T1_SSID.substring(0, T1_SSID.length());
  ssid = T1_SSID.c_str();
  
  T2_PASS  = read_EEPROM(101,150);
  T2_PASS  = T2_PASS.substring(0,T2_PASS.length());
  password = T2_PASS.c_str();
  
  T3_latitude  = read_EEPROM(151,200);
  T3_latitude  = T3_latitude.substring(0, T3_latitude.length());
  lati = atof(T3_latitude.c_str());

  T4_longitude  = read_EEPROM(201,250);
  T4_longitude  = T4_longitude.substring(0,T4_longitude.length());
  longi = atof(T4_longitude.c_str());

  //Serial.println(lati);
  //Serial.println(longi);

}
// ========================================== WEB Interface ==================================
void handleRoot() {
  String T1=T1_SSID.substring(0, 15);
  String T2=T2_PASS.substring(0, 15);
  String T3=T3_latitude.substring(0, 15);
  String T4=T4_longitude.substring(0, 15);

  String html="<!DOCTYPE html>";
  html=html+"  <html lang='en'>";
  html=html+"  <head>";
  html=html+"  <meta charset='UTF-8'>";
  html=html+"  <meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html=html+"  <title>JWS Berbicara Setting Page</title>";
  html=html+"  <style>";
  html=html+"  body {";
  html=html+"      font-family: Arial, sans-serif;";
  html=html+"      background-color: lightslategray;";
  html=html+"      display: flex;";
  html=html+"      justify-content: center;";
  html=html+"     align-items: center;";
  html=html+"      height: 100vh;";
  html=html+"      margin: 0;";
  html=html+"  }";
  html=html+"  .container {";
  html=html+"      background-color: gray;";
  html=html+"      padding: 20px;";
  html=html+"      border-radius: 10px;";
  html=html+"      box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);";
  html=html+"      max-width: 600px;";
  html=html+"      width: 900%;";
  html=html+"  }";
  html=html+"  h1, h2 {";
  html=html+"      color: #333;";
  html=html+"      text-align: center;";
  html=html+"  }";
  html=html+"  table {";
  html=html+"      width: 100%;";
  html=html+"      border-collapse: collapse;";
  html=html+"      margin-top: 20px;";
  html=html+"  }";
  html=html+"  table, th, td {";
  html=html+"      border: 1px solid #ccc;";
  html=html+"  }";
  html=html+"  th, td {";
  html=html+"      padding: 10px;";
  html=html+"      text-align: center;";
  html=html+"  }";
  html=html+"  input[type='text'] {";
  html=html+"      width: 100%;";
  html=html+"      padding: 8px;";
  html=html+"      margin-bottom: 10px;";
  html=html+"      border: 1px solid #ccc;";
  html=html+"      border-radius: 4px;";
  html=html+"      box-sizing: border-box;";
  html=html+"  }";
  html=html+"  input[type='radio'] {";
  html=html+"      margin-right: 5px;";
  html=html+"  }";
  html=html+"  input[type='submit'] {";
  html=html+"      background-color: #4CAF50;";
  html=html+"      color: #fff;";
  html=html+"      padding: 10px 20px;";
  html=html+"      border: none;";
  html=html+"      border-radius: 4px;";
  html=html+"      cursor: pointer;";
  html=html+"      font-size: 16px;";
  html=html+"      width: 100%;";
  html=html+"  }";
  html=html+"  input[type='submit']:hover {";
  html=html+"      background-color: #45a049;";
  html=html+"  }";
  html=html+"  h5 a {";
  html=html+"      color: #007BFF;";
  html=html+"      text-decoration: none;";
  html=html+"      display: block;";
  html=html+"      text-align: center;";
  html=html+"  }";
  html=html+"  </style>";
  html=html+"  </head>";
  html=html+"  <body>";
  html=html+"  <div class='container'>    ";
  html=html+"      <h1>SETTING MENU</h1> ";
  html=html+"      <h2>JWS BERBICARA ESP8266 NTP</h3> ";
  html=html+"      <form action='/overwriteSettings' method='get'> ";
  html=html+"          <table>";
  html=html+"                  <td colspan='2'> ";
  html=html+"                      <label>Setting WiFi untuk disambungkan</label> ";
  html=html+"                  </td> ";
  html=html+"              <tr> ";
  html=html+"                  <td style='width:25%' ><b>SSID WiFi</b></td> ";
  html=html+"                  <td style='width:75%' ><input type='text' name='text1' value='"+T1+"' maxlength='50'></td> ";
  html=html+"              </tr> ";
  html=html+"              <tr> ";
  html=html+"                  <td style='width:25%' ><b>Password WiFi</b></td> ";
  html=html+"                  <td style='width:75%' ><input type='text' name='text2' value='"+T2+"' maxlength='50'></td> ";
  html=html+"              </tr> ";
  html=html+"              <tr> ";
  html=html+"                  <td colspan='2'> ";
  html=html+"                      <label>Setting lokasi untuk jadwal sholat</label> ";
  html=html+"                  </td> ";
  html=html+"              <tr> ";
  html=html+"                  <td style='width:25%' ><b>Latitude</b></td> ";
  html=html+"                  <td style='width:75%' ><input type='text' name='text3' value='"+T3+"' maxlength='50'></td> ";
  html=html+"              </tr> ";
  html=html+"              <tr> ";
  html=html+"                  <td style='width:25%' ><b>Longitude</b></td> ";
  html=html+"                  <td style='width:75%' ><input type='text' name='text4' value='"+T4+"' maxlength='50'></td> ";
  html=html+"              </tr> ";
  html=html+"              <tr> ";
  html=html+"                  <td colspan='2'> ";
  html=html+"                     <input type='submit' name='Save' value='Submit'>";
  html=html+"                     <h5><a href='http://192.168.4.1/update'>© JWS BERBICARA</a></h5>";
  html=html+"                     <h5>";
  html=html+"                       <a href='https://www.instagram.com/Hab_mz'>@Hab_mz</a>";
  html=html+"                     </h5>";
  html=html+"                  </td>";
  html=html+"              </tr> ";
  html=html+"          </table>";
  html=html+"      </form>";
  html=html+"  </div>";
  html=html+"  </body>";
  html=html+"  </html>";
  server.send(200,"html",html);
}

void overwriteSettings(){
  //============= MAIN VAR =============
  String text1 = server.arg("text1");
  write_EEPROM(51, 100, text1);
  
  String text2 = server.arg("text2");
  write_EEPROM(101, 150, text2);
  
  String text3 = server.arg("text3");
  write_EEPROM(151, 200, text3);
  
  String text4 = server.arg("text4");
  write_EEPROM(201, 250, text4);
  
  String html="<!DOCTYPE html>";
  html=html+"<html lang='en'>";
  html=html+"<head>";
  html=html+"<meta charset='UTF-8'>";
  html=html+"<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html=html+"<title>Setting Berhasil!</title>";
  html=html+"<style>";
  html=html+"body {";
  html=html+"    font-family: Arial, sans-serif;";
  html=html+"    text-align: center;";
  html=html+"    background-color: #f4f4f4;";
  html=html+"    display: flex;";
  html=html+"    justify-content: center;";
  html=html+"    align-items: center;";
  html=html+"    height: 100vh;";
  html=html+"    margin: 0;";
  html=html+"}";
  html=html+".container {";
  html=html+"    background-color: #fff;";
  html=html+"    padding: 20px;";
  html=html+"    border-radius: 10px;";
  html=html+"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);";
  html=html+"    max-width: 600px;";
  html=html+"    width: 100%;";
  html=html+"}";
  html=html+"h1, h2 {";
  html=html+"    color: #333;";
  html=html+"}";
  html=html+"</style>";
  html=html+"</head>";
  html=html+"<body>";
  html=html+"<div class='container'>";
  html=html+"    <h1>Setting Done</h1>";
  html=html+"    <h2>SSID WiFi : "+text1+"</h2>";
  html=html+"    <h2>Pass WiFi : "+text2+"</h2>";
  html=html+"    <h2>Latitude  : "+text3+"</h2>";
  html=html+"    <h2>Longitude : "+text4+"</h2>";
  html=html+"</div>";
  html=html+"</body>";
  html=html+"</html>";
  server.send(200, "text/html", html);  

  reload_EEPROM();

  tone(buzzer,300); delay(500); noTone(buzzer);
  tone(buzzer,300); delay(500); noTone(buzzer);
  //Serial.println("Setup done, resetting");
  delay(5000);
  ESP.restart();
//  bInMessages = true;
}
