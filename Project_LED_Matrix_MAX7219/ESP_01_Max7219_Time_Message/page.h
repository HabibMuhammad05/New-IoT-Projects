const char MAIN_index[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
    <head>
        <title>ESP32 Weather Station</title>
        <script>
        var Effectl  = "";
        var Effectr  = "";
        var State  = "";
        var Message  = "";
        var data_val1  = 0;
        var data_val2  = 0;
      function DisplayCurrentTime() {
          var dt = new Date();
  var weekday = new Array(7);
  weekday[0] = "Sunday";
  weekday[1] = "Monday";
  weekday[2] = "Tuesday";
  weekday[3] = "Wednesday";
  weekday[4] = "Thursday";
  weekday[5] = "Friday";
  weekday[6] = "Saturday";
  var dow = weekday[dt.getDay()];
document.getElementById("datetime").innerHTML = (dow) +" "+ (dt.toLocaleString());
        setTimeout('DisplayCurrentTime()', 1000);
      };
        function GetMessage()
        {
          var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      
                            Message = this.responseXML.getElementsByTagName("analog")[0].childNodes[0].nodeValue;
    }
  var Mycolor = new Array(7);
  Mycolor[0] = "#ff0000";
  Mycolor[1] = "#ff00ff";
  Mycolor[2] = "#00ffff";
  Mycolor[3] = "#ff0000";
  Mycolor[4] = "#00ff00";
  Mycolor[5] = "#0000ff";
  Mycolor[6] = "#000000";
var c = document.getElementById("mesg");
var ctx = c.getContext("2d");
var gradient = ctx.createLinearGradient(0, 0, c.width, 0);
  for (var i=0; i<10; i++) {
  var d = Math.floor(Math.random() * 7);
gradient.addColorStop(i/10, Mycolor[d]);
  }
ctx.beginPath();
ctx.font = "20px Verdana";
ctx.fillStyle = gradient;
ctx.fillText(Message,10,15,screen.availWidth/2);
  }
  xhttp.open("GET", "readMesge", true);
  xhttp.send();
            setTimeout('GetMessage()', 4000);
        };
        function GetArduinoInputs()
        {
          var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      
                            data_val1 = this.responseXML.getElementsByTagName("analog")[0].childNodes[0].nodeValue;
                            data_val2  = this.responseXML.getElementsByTagName("analog")[1].childNodes[0].nodeValue;
    }
document.getElementById("Temperatue1").innerHTML = data_val1;
document.getElementById("Humidity1").innerHTML = data_val2;
  }
  xhttp.open("GET", "readtmhu", true);
  xhttp.send();
            setTimeout('GetArduinoInputs()', 5000);
            
        };
        function GetState()
        {
          var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
                            State = this.responseXML.getElementsByTagName("analog")[0].childNodes[0].nodeValue;
                            Effectl  = this.responseXML.getElementsByTagName("analog")[1].childNodes[0].nodeValue;
                            Effectr  = this.responseXML.getElementsByTagName("analog")[2].childNodes[0].nodeValue;
    }
document.getElementById("megsg1").innerHTML = "Mode 1";
document.getElementById("megsg2").innerHTML = "Mode 2";
document.getElementById("megsg3").innerHTML = "Mode 3";
document.getElementById("megsg4").innerHTML = "Star Eff " + Effectl;
document.getElementById("megsg5").innerHTML = "End Eff " + Effectr;
document.getElementById("megsg6").innerHTML = "PAUSE TIME";
document.getElementById("megsg7").innerHTML = "Send Message"; 
document.getElementById("megsg8").innerHTML = "Update Time"; 
document.getElementById("megsg9").innerHTML = "Set Speed"; 
document.getElementById("megsg10").innerHTML = "Set Constare"; 
    var elem = document.getElementById("megsg4");
    elem.style.color = "#00ffff";
    elem.style.fontSize = "26px";
    elem.style.fontWeight = "bold";
    var elem = document.getElementById("megsg5");
    elem.style.color = "#00ffff";
    elem.style.fontSize = "26px";
    elem.style.fontWeight = "bold";
    var elem = document.getElementById("megsg6");
    elem.style.color = "#ff00ff";
    elem.style.fontSize = "26px";
    elem.style.fontWeight = "bold";
    var elem = document.getElementById("megsg7");
    elem.style.color = "#ff0000";
    elem.style.fontSize = "26px";
    elem.style.fontWeight = "bold";
    var elem = document.getElementById("megsg8");
    elem.style.color = "#0000ff";
    elem.style.fontSize = "26px";
    elem.style.fontWeight = "bold";
    var elem = document.getElementById("megsg9");
    elem.style.color = "#00ff00";
    elem.style.fontSize = "26px";
    elem.style.fontWeight = "bold";
    var elem = document.getElementById("megsg10");
    elem.style.color = "#ffff00";
    elem.style.fontSize = "26px";
    elem.style.fontWeight = "bold";
    if (State == "1") {
    var elem = document.getElementById("megsg1");
    // Appling styles on element
    elem.style.color = "#ff00ff";
    elem.style.fontSize = "26px";
    elem.style.fontWeight = "bold";
  } else if (State == "2") {
    var elem = document.getElementById("megsg2");
    // Appling styles on element
    elem.style.color = "#ff00ff";
    elem.style.fontSize = "26px";
    elem.style.fontWeight = "bold";
  } else if (State == "3") {
    var elem = document.getElementById("megsg3");
    // Appling styles on element
    elem.style.color = "#ff00ff";
    elem.style.fontSize = "26px";
    elem.style.fontWeight = "bold";
  } 
  }
  xhttp.open("GET", "readState", true);
  xhttp.send();
            setTimeout('GetState()', 4000);
            
        };
      document.addEventListener('DOMContentLoaded', function() {
        DisplayCurrentTime(),GetMessage(),GetArduinoInputs(),GetState();
      }, false);
    </script>
      <style>

  body {
  text-align: center;
  margin: 5;
  padding: 5;
  background-color: rgba(72,72,72,0.4);
  }
  marquee{
  width: 100%;
      font-size: 20px;
  font-weight:700;
      color: #ff0000;
      font-family: sans-serif;
      }
.slider {
  -webkit-appearance: none;
  width: 100%;
  height: 15px;
  background: #ffff00;
  outline: none;
  opacity: 0.7;
  -webkit-transition: .2s;
  transition: opacity .2s;
}
.slider:hover {
  opacity: 1;
}
.slider::-moz-range-thumb {
  width: 15px;
  height: 25px;
  background: #FF0F50;
  cursor: pointer;
}
       .onoffswitch {
      font-size: 25px; background: #000000; color: #ffffff;
        -webkit-user-select:none; -moz-user-select:none; -ms-user-select: none;
    }
    .onoffswitch-submit {
        display: none;
    }
    .onoffswitch-label {
        display: block; overflow: hidden; cursor: pointer;
        border: 2px solid #E60E40; border-radius: 11px;
    }
    .onoffswitch-inner {
        display: block; width: 200%; margin-left: -100%;
        transition: margin 0.3s ease-in 0s;
    }
    .onoffswitch-submit:checked + .onoffswitch-label .onoffswitch-inner {
        margin-left: 0;
    }
  .data-input {
  background-color: #bbbbff;
  font-size:26px;
  color:red;
  border: 5px solid #444444;
  -moz-border-radius: 7px;
  -webkit-border-radius: 7px;
  }
  .button-blue {
  padding: 5px 5px 5px 5px;
  width: 100%;
  border: #000000 solid 3px;
  background-color: #ff00ff;
  color:white;
  font-size:20px;
  padding-bottom:5px;
  font-weight:700;
  -moz-border-radius: 2px;
  -webkit-border-radius: 7px;
  }
  .button-blue:hover {
  background-color: #0000ff;
  color: #ff00ff;
  }
  .button-b {
  padding: 5px 5px 5px 5px;
  width: 100%;
  border: #000000 solid 3px;
  background-color: #ffffff;
  color: #ff00ff;
  font-size:20px;
  padding-bottom:5px;
  font-weight:700;
  -moz-border-radius: 2px;
  -webkit-border-radius: 7px;
  }
  .text {
  background-color: #ff0000;
  font-size:76px;
  color: #ffff99;
  }
  table {
  text-align: center;
  border: 2px solid #ff00ff;
  background-color: #ffffff;
  width:100%;
  color: #0000ff;
  -moz-border-radius: 7px;
  -webkit-border-radius: 7px;
  }
  h1 {
  color: #ff0000;
  background-color: #ffff00;
  -moz-border-radius: 7px;
  -webkit-border-radius: 7px;
  }
  div {
  border: 2px solid #ff0000;
  background-color: #bbbbff;
  color: #ff0000;
  -moz-border-radius: 7px;
  -webkit-border-radius: 7px;
  }
  td {
  border: 2px solid #ff0000;
  background-color: #ffff00;
  padding: 16px;
  -moz-border-radius: 7px;
  -webkit-border-radius: 7px;
  }
  </style>
    </head>
    <body>
    <table>
   <tr>
        <td class="button-b" style='width:65%'>
  <marquee style="width:95%"><canvas id="mesg" width="800" height="16"></canvas></marquee></td>
        <td class="button-b" style='width:35%'>
  <span id="datetime"></span></td>
</tr>
</table>
    <table>
   <tr>
        <td style='width:12%'>
  <form action="/stat1" method="POST">
      <div class="onoffswitch">
        <input type="submit" name="stat" class="onoffswitch-submit" id="mymodea">
        <label class="onoffswitch-label" for="mymodea">
            <span id="megsg1"></span>
        </label>
    </div>
  </form></td>
        <td style='width:12%'>
  <form action="/stat2" method="POST">
      <div class="onoffswitch">
        <input type="submit" name="stat" class="onoffswitch-submit" id="mymodeb">
        <label class="onoffswitch-label" for="mymodeb">
            <span id="megsg2"></span>
        </label>
    </div>
  </form></td>
        <td style='width:12%'>
  <form action="/stat3" method="POST">
      <div class="onoffswitch">
        <input type="submit" name="stat" class="onoffswitch-submit" id="mymodec">
        <label class="onoffswitch-label" for="mymodec">
            <span id="megsg3"></span>
        </label>
    </div>
  </form></td>
        <td style='width:17%'>
  <form action="/EffectL" method="POST">
      <div class="onoffswitch">
        <input type="submit" name="stat" class="onoffswitch-submit" id="mymoded">
        <label class="onoffswitch-label" for="mymoded">
            <span id="megsg4"></span>
        </label>
    </div>
  </form></td>
        <td style='width:17%'>
  <form action="/EffectR" method="POST">
      <div class="onoffswitch">
        <input type="submit" name="stat" class="onoffswitch-submit" id="mymodee">
        <label class="onoffswitch-label" for="mymodee">
            <span id="megsg5"></span>
        </label>
    </div>
  </form></td>
        <td style='width:20%'>
  <form action="/pTime" method="POST">
      <div class="onoffswitch">
        <input type="range" name="pausetime" min="0" max="10" value="5" class="slider" style="width:60%" id="myPausetime">
          <b>  <span id="pausetime"></span>s</b>
        <input type="submit" name="stat" class="onoffswitch-submit" id="mymodef">
        <label class="onoffswitch-label" for="mymodef">
            <span id="megsg6"></span>
        </label>
    </div>
 <script>
var slider0 = document.getElementById("myPausetime");
var output0 = document.getElementById("pausetime");
output0.innerHTML = slider0.value;

slider0.oninput = function() {
  output0.innerHTML = this.value;
}
 </script>
  </form></td>
</tr>
</table>
    <table>
   <tr>
        <td style='width:75%'>
  <form action="/MeMessg" method="POST">
      <div class="onoffswitch">
        <input type="text" name="Message" maxlength="655" class="button-white" style="width:95%;height:35px;font-size:30px" id="myMes">
        <input type="submit" name="stat" class="onoffswitch-submit" id="mymodeg">
        <label class="onoffswitch-label" for="mymodeg">
            <span id="megsg7"></span>
        </label>
    </div>
  </form></td>
        <td style='width:25%'>
  <form action="/resttime" method="POST">
      <div class="onoffswitch">
        <b style="width:8%">GMT+</b>
        <input type="number" value="0" name="restmie" min="-12" max="+12" class="button-blue" style="width:25%">
        <input type="submit" name="stat" class="onoffswitch-submit" id="mymodeh">
        <label class="onoffswitch-label" for="mymodeh">
            <span id="megsg8"></span>
        </label>
    </div>
  </form></td>
</tr>
</table>
    <table>
   <tr>
        <td style='width:50%'>
  <form action="/MeSpeed" method="POST">
      <div class="onoffswitch">
        <input type="range" name="Speed" min="0" max="100" value="50" class="slider" style="width:80%" id="mySpeed">
          <b>  <span id="speed"></span></b>
        <input type="submit" name="stat" class="onoffswitch-submit" id="mymodei">
        <label class="onoffswitch-label" for="mymodei">
            <span id="megsg9"></span>
        </label>
    </div>
 <script>
var slider2 = document.getElementById("mySpeed");
var output2 = document.getElementById("speed");
output2.innerHTML = slider2.value;
slider2.oninput = function() {
  output2.innerHTML = this.value;
}
 </script>
  </form></td>
        <td style='width:50%'>
  <form action="/Meconst" method="POST">
      <div class="onoffswitch">
        <input type="range" name="constare" min="0" max="10" value="5" class="slider" style="width:80%" id="myconstare">
  <b>  <span id="constare"></span></b>
        <input type="submit" name="stat" class="onoffswitch-submit" id="mymodej">
        <label class="onoffswitch-label" for="mymodej">
            <span id="megsg10"></span>
        </label>
    </div>
 <script>
var slider3 = document.getElementById("myconstare");
var output3 = document.getElementById("constare");
output3.innerHTML = slider3.value;
slider3.oninput = function() {
  output3.innerHTML = this.value;
}
 </script>
  </form></td>
</tr>
</table>
    <table>
   <tr>
        <td style='width:50%'>
   <b style= "color: #ff0000;font-size:45px">Temperatue</b></td>
        <td style='width:50%'>
   <b style= "color: #ff0000;font-size:45px">Humidity</b></td>
  </tr>
   <tr>
        <td style='width:50%'>
   <b style= "color: #ff0000;font-size:35px"><span id="Temperatue1"></span> &deg;C</b></td>
        <td style='width:50%'>
   <b style= "color: #ff0000;font-size:35px"><span id="Humidity1"></span> % RH</b></td>
  </tr>
   <tr>
        <td style='width:50%'>
  <form action="/restart" method="POST">
  <input type="submit" name = "rerset" value="Restart ESP8266" class="button-blue">
  </form></td>
        <td style='width:50%'>
  <form action="/" method="POST">
  <input type="submit" value="Home" class="button-blue">
  </form></td></tr>
    </table>
    </body>
</html>
)=====";
