char webpage[] PROGMEM = R"=====(

<!DOCTYPE HTML><html>
  <head>
    <title>ESP Web Server</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body { font-family: Arial; text-align: center; margin:0px auto; padding-top: 30px; background-color: dodgerblue;}
      button {
        margin: 3px 1px 3px 1px;
        padding: 10px 20px;
        font-size: 24px;
        text-align: center;
        outline: none;
        color: #fff;
        background-color: #2f4468;
        border: none;
        border-radius: 5px;
        box-shadow: 0 6px #999;
        cursor: pointer;
        -webkit-tap-highlight-color: rgba(0,0,0,0);
      }  
      button:hover {background-color: #1f2e45}
      button:active {
        background-color: #1f2e45;
        box-shadow: 0 4px #666;
        transform: translateY(2px);
      }
      .key { 
        border-radius:10px; color:#ffffff; font-size:14px; padding:110px 30px;
      }
      .tombol { padding: 15px 30px; font-size: 14px; margin: 3px 1px 3px 10px;}
      hr {
        margin: 30px 10px 30px 10px; border: 2px solid #eee;
      }
      .slidecontainer {
        width: 100%; /* Width of the outside container */
      }

      /* Mouse-over effects */
      .slider:hover {
        opacity: 1; /* Fully shown on mouse-over */
      }
      .slider {
        -webkit-appearance: none;
        width: 75%;
        height: 15px;
        border-radius: 5px;  
        background: #2f4468;
        outline: none;
        opacity: 0.7;
        -webkit-transition: .2s;
        transition: opacity .2s;
      }
      .slider::-webkit-slider-thumb {
        -webkit-appearance: none;
        appearance: none;
        width: 25px;
        height: 25px;
        border-radius: 50%; 
        border: 1px;
        background: #999;
        cursor: pointer;
      }
    </style>
  </head>
  <body>
    <h1>ESP8266 Audio Web Server</h1>
    <br/>
    <hr>
    <h3>Kontrol</h3>
    <br>
    <div class="slidecontainer">
      <input type="range" min="0" max="30" value="15" class="slider" id="myRange">
      <p>volume: <span id="demo"></span></p>
    </div>
    <div>
        <button class="tombol" onclick="toggleCheckbox('play')">+</button>
        <button class="tombol" onclick="toggleCheckbox('ran')">Random</button>
        <button class="tombol" onclick="toggleCheckbox('stop')">-</button>
    </div>
    <br>
    <br>
    <div>
      <button class="key" onmousedown="toggleCheckbox('do');" ontouchstart="toggleCheckbox('do');" onmouseup="toggleCheckbox('Noff');" ontouchend="toggleCheckbox('Noff');">1</button>
      <button class="key" onmousedown="toggleCheckbox('re');" ontouchstart="toggleCheckbox('re');" onmouseup="toggleCheckbox('Noff');" ontouchend="toggleCheckbox('Noff');">2</button>
      <button class="key" onmousedown="toggleCheckbox('mi');" ontouchstart="toggleCheckbox('mi');" onmouseup="toggleCheckbox('Noff');" ontouchend="toggleCheckbox('Noff');">3</button>
      <button class="key" onmousedown="toggleCheckbox('fa');" ontouchstart="toggleCheckbox('fa');" onmouseup="toggleCheckbox('Noff');" ontouchend="toggleCheckbox('Noff');">4</button>
      <button class="key" onmousedown="toggleCheckbox('sol');" ontouchstart="toggleCheckbox('sol');" onmouseup="toggleCheckbox('Noff');" ontouchend="toggleCheckbox('Noff');">5</button>
      <button class="key" onmousedown="toggleCheckbox('la');" ontouchstart="toggleCheckbox('la');" onmouseup="toggleCheckbox('Noff');" ontouchend="toggleCheckbox('Noff');">6</button>
      <button class="key" onmousedown="toggleCheckbox('si');" ontouchstart="toggleCheckbox('si');" onmouseup="toggleCheckbox('Noff');" ontouchend="toggleCheckbox('Noff');">7</button>
      <button class="key" onmousedown="toggleCheckbox('do2');" ontouchstart="toggleCheckbox('do2');" onmouseup="toggleCheckbox('Noff');" ontouchend="toggleCheckbox('Noff');">8</button>
      
    </div>
    <br>
    <hr>
    <h3>Pilih Musik</h3>
    <br>
    <div>
      <button class="tombol" onclick="toggleCheckbox('1')">Susanti</button>
      <button class="tombol" onclick="toggleCheckbox('2')">Basuri</button>
      <button class="tombol" onclick="toggleCheckbox('3')">Bebek</button>
      <button class="tombol" onclick="toggleCheckbox('4')">iaiao</button>
      <button class="tombol" onclick="toggleCheckbox('5')">hepi</button>
      <button class="tombol" onclick="toggleCheckbox('6')">balonku</button>
      <button class="tombol" onclick="toggleCheckbox('7')">sumur</button>
      <button class="tombol" onclick="toggleCheckbox('8')">banding</button>
      <button class="tombol" onclick="toggleCheckbox('9')">tayo</button>
      <button class="tombol" onclick="toggleCheckbox('10')">sholawat</button>
      <button class="tombol" onclick="toggleCheckbox('11')">ondel</button>
      <button class="tombol" onclick="toggleCheckbox('12')">ran1</button>
      <button class="tombol" onclick="toggleCheckbox('13')">ran2</button>
    </div>
    <br>
    <hr>
    <h3>Software Update</h3>
    <br>
      <button onclick="window.location = 'http://'+location.hostname+'/update'">Update</button>
   <br>
   <br>
   <script>
    var xhr = new XMLHttpRequest();
    var slider = document.getElementById("myRange");
    var output = document.getElementById("demo");
    output.innerHTML = slider.value;

    slider.oninput = function() {
      output.innerHTML = this.value;
      var slider_value = document.getElementById("myRange").value;
      xhr.open("GET", "/slider?value="+slider_value, true);
      xhr.send();
    }

   function toggleCheckbox(x) {
     xhr.open("GET", "/" + x, true);
     xhr.send();
   }
  </script>
  </body>
</html>

)=====";
