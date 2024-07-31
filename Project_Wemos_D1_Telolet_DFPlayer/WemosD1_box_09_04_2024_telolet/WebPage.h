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
        border-radius:10px; color:#ffffff; font-size:14px; padding:110px 25px;
      }
      .keystop { 
        border-radius:10px; color:#ffffff; font-size:14px; padding:25px 178px;
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
       select {
        width: 90px;
        height: 50px;
        font-size:15px;
        margin-bottom: 10px;
        margin-top: 5px;
        margin-right: 10px;
        outline: 0;
        background: #2f4468;
        color: #fff;
        padding: 4px;
        border-radius: 5px;
        box-shadow: 0 6px #999;
      }
      select:hover {background-color: #1f2e45}
      select:active {
        background-color: #1f2e45;
        box-shadow: 0 4px #666;
        transform: translateY(2px);
      }
      input {
        margin: 10px 1px 3px 1px;
        padding: 15px 30px;
        font-size: 15px;
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
      input:hover {background-color: #1f2e45}
      input:active {
        background-color: #1f2e45;
        box-shadow: 0 4px #666;
        transform: translateY(2px);
      }
    </style>
  </head>
  <body>
    <h1>ESP8266 Audio Web Server</h1>
    <br/>
    <hr>
    <h3>Pilih Lagu</h3>
    <br>
    <div class="slidecontainer">
      <input type="range" min="0" max="30" value="30" class="slider" id="myRange">
      <p>volume: <span id="demo"></span></p>
    </div>
    <br>
    <br>
    <div>
      <form >
        <select id="mySelect">
          <option>Pilih</option>
          <option> 1.Susanti </option> 
          <option> 2.Basuri </option>
          <option> 3.Bebek </option>
          <option> 4.Iaiao </option> 
          <option> 5.Hepi </option>
          <option> 6.Balonku </option> 
          <option> 7.Susu Murni </option> 
          <option> 8.Dibanding </option> 
          <option> 9.Tayo </option> 
          <option> 10.Sholawat </option> 
          <option> 11.Ondel-ondel </option> 
          <option> 12.Ganti mode </option> 
          <option> 13.Random </option> 
          <option> 14.Mangku </option> 
          <option> 15.Mengular </option>
          <option> 16.Mengular V2 </option> 
          <option> 17.Baby Shark </option> 
          <option> 18.Terompet 1 </option> 
          <option> 19.Terompet 2 </option> 
          <option> 20.Cffin </option> 
          <option> 21.Final Countdown </option> 
          <option> 22.Savage </option> 
          <option> 23.Bella Ciao </option> 
          <option> 24.Levan Polkka </option>
          <option> 25.Pirates </option> 
          <option> 26.Spam </option> 
          <option> 27.Kopi </option> 
          <option> 28.Kebalik 1 </option> 
          <option> 29.Kebalik 2 </option> 
          <option> 30.Kebalik 3 </option> 
          <option> 31.Al Fayed 1 </option> 
          <option> 32.Al Fayed 2 </option> 
          <option> 33.Pakistan </option> 
          <option> 34.Kebalik Mengular </option> 
          <option> 35.1 </option> 
          <option> 36.2 </option> 
          <option> 37.3 </option> 
          <option> 38.4 </option> 
          <option> 39.5 </option> 
          <option> 40.6 </option> 
          <option> 41.Almate </option> 
          <option> 42.Guviliibrahim </option> 
          <option> 43.V2Guviliibrahim </option> 
          <option> 44.Naik delman </option> 
          <option> 45.V2Naik delman </option> 
          <option> 46.Transkenzo </option> 
          <option> 47.V2Transkenzo </option> 
          <option> 48.Dibalik Batu </option> 
          <option> 49.Kucing Garong </option> 
          <option> 50.CrazyFrog </option> 
          <option> 51.Winspector </option> 
          <option> 52.Yalawatan </option> 
          <option> 53.Yalawatan 2 </option> 
          <option> 54.Winspector 2 </option> 
          <option> 55.Winspector 3 </option> 
          <option> 56.Winspector 4 </option> 
          <option> 57.Winspector 5 </option> 
          <option> 58.takbiran </option> 
          <option> 59.gatau apa </option> 
        </select>
        <input type="button" onclick="getIndex()" value="Kirim">
        <button class="tombol" onclick="toggleCheckbox('loop')">Loop</button>
        <p>lagu ke: <span id="demosong"></span></p>
      </form>
    </div>
    <div>
        <button class="tombol" onclick="toggleCheckbox('play')">Play All</button>
        <button class="tombol" onclick="toggleCheckbox('ran')">Random</button>
        <button class="tombol" onclick="toggleCheckbox('stop')">Stop</button>
    </div>
    <br>
    <hr>
    <h3>Manual</h3>
    <br>
    <div>
      <button class="key" onmousedown="toggleCheckbox('do');" ontouchstart="toggleCheckbox('do');" onmouseup="toggleCheckbox('Noff');" ontouchend="toggleCheckbox('Noff');">1</button>
      <button class="key" onmousedown="toggleCheckbox('re');" ontouchstart="toggleCheckbox('re');" onmouseup="toggleCheckbox('Noff');" ontouchend="toggleCheckbox('Noff');">2</button>
      <button class="key" onmousedown="toggleCheckbox('mi');" ontouchstart="toggleCheckbox('mi');" onmouseup="toggleCheckbox('Noff');" ontouchend="toggleCheckbox('Noff');">3</button>
      <button class="key" onmousedown="toggleCheckbox('fa');" ontouchstart="toggleCheckbox('fa');" onmouseup="toggleCheckbox('Noff');" ontouchend="toggleCheckbox('Noff');">4</button>
      <button class="key" onmousedown="toggleCheckbox('sol');" ontouchstart="toggleCheckbox('sol');" onmouseup="toggleCheckbox('Noff');" ontouchend="toggleCheckbox('Noff');">5</button>
      <button class="key" onmousedown="toggleCheckbox('la');" ontouchstart="toggleCheckbox('la');" onmouseup="toggleCheckbox('Noff');" ontouchend="toggleCheckbox('Noff');">6</button>
      
    </div>
    <br>
        <button class="keystop" onclick="toggleCheckbox('Nstop')">Stop</button>
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

    function getIndex() {
      document.getElementById("demosong").innerHTML = document.getElementById("mySelect").selectedIndex;
      var song_value = document.getElementById("mySelect").selectedIndex;
      xhr.open("GET", "/song?value="+song_value, true);
      xhr.send();
    }
  </script>
  </body>
</html>

)=====";
