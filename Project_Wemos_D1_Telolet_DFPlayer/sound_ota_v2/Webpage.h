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
  <script>
    var connection = new WebSocket('ws://'+location.hostname+':81/');

    var player_data = "NULL";
    var not_data = "NULL";
    var musik_data = "NULL";

    function send_data(){
      var full_data = '{"PLAYER" :'+player_data+', "NOT" :'+not_data+', "MUSIK" :'+musik_data+'}';
      console.log(full_data);
      connection.send(full_data);
    }

    <! -- -----------------------Player data------------------------------ -->
    function  prev(){
      player_data = "Prev";
      not_data = "NULL";
      musik_data = "NULL";
      
      console.log("Player - Prev");
      send_data();
    }
    function  random(){
      player_data = "Random";
      not_data = "NULL";
      musik_data = "NULL";
      
      console.log("Player - Random");
      send_data();
    }
    function  next(){
      player_data = "Next";
      not_data = "NULL";
      musik_data = "NULL";
      
      console.log("Player - Next");
      send_data();
    }

    <! -- -----------------------not data------------------------------ -->
    function do(){
      player_data = "NULL";
      not_data = "do";
      musik_data = "NULL";
      
      console.log("not - Do");
      send_data();
    }
    function re(){
      player_data = "NULL";
      not_data = "re";
      musik_data = "NULL";
      console.log("not - re");
      send_data();
    }
    function mi(){
      player_data = "NULL";
      not_data = "mi";
      musik_data = "NULL";
      console.log("not - mi");
      send_data();
    }
    function fa(){
      player_data = "NULL";
      not_data = "fa";
      musik_data = "NULL";
      console.log("not - fa");
      send_data();
    }
    function sol(){
      player_data = "NULL";
      not_data = "sol";
      musik_data = "NULL";
      console.log("not - sol");
      send_data();
    }
    function la(){
      player_data = "NULL";
      not_data = "la";
      musik_data = "NULL";
      console.log("not - la");
      send_data();
    }
    function si(){
      player_data = "NULL";
      not_data = "si";
      musik_data = "NULL";
      console.log("not - si");
      send_data();
    }
    function do2(){
      player_data = "NULL";
      not_data = "do2";
      musik_data = "NULL";
      console.log("not - Do2");
      send_data();
    }

    <! -- -----------------------musik data------------------------------ -->
    function satu(){
      player_data = "NULL";
      not_data = "NULL";
      musik_data = 1;
      console.log("musik - Suara 1");
      send_data();
    }
    function dua(){
      player_data = "NULL";
      not_data = "NULL";
      musik_data = 2;
      console.log("musik - Suara 2");
      send_data();
    }
    function tiga(){
      player_data = "NULL";
      not_data = "NULL";
      musik_data = 3;
      console.log("musik - Suara 3");
      send_data();
    }
    function empat(){
      player_data = "NULL";
      not_data = "NULL";
      musik_data = 4;
      console.log("musik - Suara 4");
      send_data();
    }
    function lima(){
      player_data = "NULL";
      not_data = "NULL";
      musik_data = 5;
      console.log("musik - Suara 5");
      send_data();
    }
    function enam(){
      player_data = "NULL";
      not_data = "NULL";
      musik_data = 6;
      console.log("musik - Suara 6");
      send_data();
    }
  </script>
  </head>

  <body style="background-color:DodgerBlue;">
    <center>
      <h1>lorem ipsum dolor</h1>
      
      <br>
      <hr/>

      <h3>Player</h3>
      <div>
        <button onclick="prev()">Prev</button>
        <button onclick="random()">Random</button>
        <button onclick="next()">Next</button>
      </div>
      <br/>
      <div>
        <button class="key" onclick="do()">1</button>
        <button class="key" onclick="re()">2</button>
        <button class="key" onclick="mi()">3</button>
        <button class="key" onclick="fa()">4</button>
        <button class="key" onclick="sol()">5</button>
        <button class="key" onclick="la()">6</button>
        <button class="key" onclick="si()">7</button>
        <button class="key" onclick="do2()">8</button>
      </div>
      
      <br>
      <hr/>
      
      <h3>Musik</h3>
      <div>
        <button  onclick="satu()">satu</button>
        <button  onclick="dua()">dua</button>
        <button  onclick="tiga()">Tiga</button>
        <button  onclick="empat()">Empat</button>
        <button  onclick="lima()">Lima</button>
        <button  onclick="enam()">Enam</button>
      </div>
      
      <br>
      <hr/>
      
      <h3>Update Software</h3>
      <div>
        <button  onclick="window.location = 'http://'+location.hostname+'/update'">Update</button>
    </center>
  </body>
</html>

)=====";
