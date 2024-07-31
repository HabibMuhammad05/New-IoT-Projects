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
      <input type="range" min="0" max="30" value="15" class="slider" id="myRange">
      <p>volume: <span id="demo"></span></p>
    </div>
    <br>
    <br>
    <div>
      <form >
        <select id="mySelect">
          <option>Pilih</option>
          <option> Susanti </option> 
          <option> Basuri </option>
          <option> Bebek </option>
          <option> Iaiao </option> 
          <option> Hepi </option>
          <option> Balonku </option> 
          <option> Susu Murni </option> 
          <option> Dibanding </option> 
          <option> Tayo </option> 
          <option> Sholawat </option> 
          <option> Ondel-ondel </option> 
          <option> Ganti mode </option> 
          <option> Random </option> 
          <option> Mangku </option> 
          <option> Mengular </option>
          <option> Mengular V2 </option> 
          <option> Baby Shark </option> 
          <option> Terompet 1 </option> 
          <option> Terompet 2 </option> 
          <option> Coffin </option> 
          <option> Final Countdown </option> 
          <option> Savage </option> 
          <option> Bella Ciao </option> 
          <option> Levan Polkka </option>
          <option> Pirates </option> 
          <option> Spam </option> 
          <option> Tiktok 1 </option> 
          <option> Tiktok 2 </option> 
        </select>
        <input type="button" onclick="getIndex()" value="Kirim">
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
      <button class="key" onmousedown="toggleCheckbox('si');" ontouchstart="toggleCheckbox('si');" onmouseup="toggleCheckbox('Noff');" ontouchend="toggleCheckbox('Noff');">7</button>
      <button class="key" onmousedown="toggleCheckbox('do2');" ontouchstart="toggleCheckbox('do2');" onmouseup="toggleCheckbox('Noff');" ontouchend="toggleCheckbox('Noff');">8</button>
      
    </div>
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
