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
    </style>
  </head>
  <body>
    <h1>ESP8266 Audio Web Server</h1>
    <br/>
    <hr>
    <h3>Kontrol Manual</h3>
    <br>
    <div>
        <button class="tombol" onclick="toggleCheckbox('play')">Play</button>
        <button class="tombol" onclick="toggleCheckbox('ran')">Random</button>
        <button class="tombol" onclick="toggleCheckbox('stop')">Stop</button>
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
      <button class="tombol" onclick="toggleCheckbox('1')">satu</button>
      <button class="tombol" onclick="toggleCheckbox('2')">dua</button>
      <button class="tombol" onclick="toggleCheckbox('3')">tiga</button>
      <button class="tombol" onclick="toggleCheckbox('4')">empat</button>
      <button class="tombol" onclick="toggleCheckbox('5')">lima</button>
      <button class="tombol" onclick="toggleCheckbox('6')">enam</button>
    </div>
    <br>
    <hr>
    <h3>Software Update</h3>
    <br>
      <button onclick="window.location = 'http://'+location.hostname+'/update'">UPDATE</button>
   <br>
   <br>
   <script>
   function toggleCheckbox(x) {
     var xhr = new XMLHttpRequest();
     xhr.open("GET", "/" + x, true);
     xhr.send();
   }
  </script>
  </body>
</html>

)=====";
