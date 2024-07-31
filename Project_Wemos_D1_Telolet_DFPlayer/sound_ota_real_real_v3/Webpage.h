char webpage[] PROGMEM = R"=====(

<!DOCTYPE HTML>
<html>
  <meta name='viewport' content='width=device-width, initial-scale=1'>
  <head>
    <title>webpage sederhana</title>
    <style>
    button {
      margin: 3px 1px 3px 1px;
      display: inline-block; cursor: pointer; box-shadow: 1px 1px 2px 0 rgba(0,0,0,0.2);
      font: normal normal bold 17px/normal "Times New Roman", Times, serif;
      text-shadow:0px 1px 0px #b23e35; color: rgba(255,255,255,1); background: #e06666;
      border-radius:28px; border:1px solid #ffffff; padding:16px 31px;
    }
    hr {
      margin: 47px 10px 47px 10px; border: 2px solid #eee;
    }
    .key { 
      background-color:#ffffff; border-radius:15px; color:#000000; font-size:14px; padding:75px 15px;
    }
    </style>  
  </head>

  <body style="background-color:DodgerBlue;">
    <center>
      <h1>lorem ipsum dolor</h1>
      
      <br>
      <hr/>

      <h3>Player</h3>
      <div>
        <button class="tombol" onclick="window.location = 'http://'+location.hostname+'/player/prev'">Prev</button>
        <button class="tombol" onclick="window.location = 'http://'+location.hostname+'/player/random'">Random</button>
        <button class="tombol" onclick="window.location = 'http://'+location.hostname+'/player/next'">Next</button>
      </div>
      <br/>
      <div>
        <button class="key" onclick="window.location = 'http://'+location.hostname+'/not/do'">1</button>
        <button class="key" onclick="window.location = 'http://'+location.hostname+'/not/re'">2</button>
        <button class="key" onclick="window.location = 'http://'+location.hostname+'/not/mi'">3</button>
        <button class="key" onclick="window.location = 'http://'+location.hostname+'/not/fa'">4</button>
        <button class="key" onclick="window.location = 'http://'+location.hostname+'/not/sol'">5</button>
        <button class="key" onclick="window.location = 'http://'+location.hostname+'/not/la'">6</button>
        <button class="key" onclick="window.location = 'http://'+location.hostname+'/not/si'">7</button>
        <button class="key" onclick="window.location = 'http://'+location.hostname+'/not/do2'">8</button>
      </div>
      
      <br>
      <hr/>
      
      <h3>Musik</h3>
      <div>
        <button class="tombol" onclick="window.location = 'http://'+location.hostname+'/musik/1'">satu</button>
        <button class="tombol" onclick="window.location = 'http://'+location.hostname+'/musik/2'">dua</button>
        <button class="tombol" onclick="window.location = 'http://'+location.hostname+'/musik/3'">Tiga</button>
        <button class="tombol" onclick="window.location = 'http://'+location.hostname+'/musik/4'">Empat</button>
        <button class="tombol" onclick="window.location = 'http://'+location.hostname+'/musik/5'">Lima</button>
        <button class="tombol" onclick="window.location = 'http://'+location.hostname+'/musik/6'">Enam</button>
      </div>
      
      <br>
      <hr/>
      
      <h3>Update Software</h3>
      <div>
        <button class="tombol" onclick="window.location = 'http://'+location.hostname+'/update'">Update</button>
    </center>
  </body>
</html>

)=====";
