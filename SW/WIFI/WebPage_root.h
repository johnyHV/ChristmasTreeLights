/**
   @file WebPage_root.h

   @brief domovska WEB stranka
   
   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#ifndef _WEB_PAGE_ROOT_H_
#define _WEB_PAGE_ROOT_H_

const char htmlPageRoot[] PROGMEM = R"=====(

<!doctype html>
<html lang="sk">
<head>
  <meta charset="utf-8">
  <title>ESP8266 - Christmas Lights</title>
  <style>

  /* data table */
  #data {
    font-family: Arial, Helvetica, sans-serif;
    border-collapse: collapse;
    width: 100%;
    table-layout: fixed;
  }

  #data td, #data th {
    border: 1px solid #ddd;
    padding: 8px;
  }

  #data tr:nth-child(even){background-color: #f2f2f2;}

  #data tr:hover {background-color: #ddd;}

  #data th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: left;
    background-color: #4CAF50;
    color: white;
  }
  
  /* select menu */
  select {
    padding: 8px 20px;
    width: 210px;
    border: none;
    border-radius: 4px;
    background-color: #f1f1f1;
  }

  /* submit button */
  input[type=submit] {
    background-color: #4CAF50;
    border: none;
    color: white;
    padding: 10px 32px;
    text-decoration: none;
    margin: 1px 1px;
    cursor: pointer;
  }

  /* text input */
  input[type=text] {
    padding: 8px 20px;
    margin: 1px 1;
    box-sizing: border-box;
    border: 3px solid #ccc;
    -webkit-transition: 0.5s;
    transition: 0.5s;
    outline: none;
    width: 210px;
  }

  input[type=text]:focus {
    border: 3px solid #555;
  }

  /* input table */
  #input {
    font-family: Arial, Helvetica, sans-serif;
    border-collapse: collapse;
    width: 100%;
    table-layout: fixed;
  }

  #input td, #input th {
    border: 0px solid #ddd;
    padding: 1.0px;
  }

  #input th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: left;
    background-color: #4CAF50;
    color: white;
  }

  </style>
  
  <script src="http://code.jquery.com/jquery-1.12.4.js"></script>

  <style>
    body {
      font-family: Arial, Helvetica, sans-serif;
    }

    /* Dashed border */
    hr.dashed {
      border-top: 3px dashed #bbb; 
    }

    /* Dotted border */
    hr.dotted {
      border-top: 3px dotted #bbb;
    }

    /* Solid border */
    hr.solid {
      border-top: 3px solid #bbb;
    }

    /* Rounded border */
    hr.rounded {
      border-top: 8px solid #bbb;
      border-radius: 5px;
    }
  </style>
</head>
<body>

  <center>
    <h2>
      <font color="blue">
        ESP8266 - Christmas Lights
      </font>
    </h2>
  </center>
  <table id="data">
  <tr>
    <th>Typ informacie</th> 
    <th>Hodnota</th>
  </tr>
  <tr>
    <td>Aktualny cas</td><td id="time"></td>
  </tr>
  <tr>
    <td>Aktualny efekt</td><td id="effect"></td>
  </tr>
  <tr>
    <td>Rychlost bikania efektov [ms]</td><td id="EffectSpeed"></td>
  </tr>
  <tr>
    <td>Dlzka svietenia efektu pri nahodnom vybere [s]</td><td id="RandomTime"></td>
  </tr>
  <tr>
    <td>Atomaticke zapnutie a vypnutie svetiel</td><td id="autoOn"></td>
  </tr>
  <tr>
    <td>Efekt pri automatickom zapnuti</td><td id="autoOnEffect"></td>
  </tr>
  <tr>
    <td>Automaticke zapnutie o</td><td id="autoOnTimeOn"></td>
  </tr>
  <tr>
    <td>Automaticke vypnutie o</td><td id="autoOnTimeOff"></td>
  </tr>
  <tr>
    <td>Firmware MCU</td><td id="FirmwareMcu"></td>
  </tr>
  <tr>
    <td>Firmware Wi-Fi</td><td id="FirmwareWifi"></td>
  </tr>
  </table>
  
  <hr class="rounded">

  <center>
    <h2>
      <font color="red"> 
        ESP8266 - Christmas Lights - nastavenie
      </font>
    </h2>
  </center>

  <table id="input">
  <tr>
    <td>
      Nastavenie aktualneho casu
    </td>
    <td>
      <form action="/setTime">
        <label for="stime"></label>
        <input type="text" id="stime" name="stime" value="14:31:11"> <input type="submit">
      </form>
    </td> 
  </tr> 
  </table>

  <hr class="dotted">

  <table id="input">
  <tr>
    <td>
      Vyber aktualneho efektu
    </td>
    <td>
      <form action="/effect">
        <label for="effect"></label>
        <select name="Effect" id="effect">
          <option value="0">OFF</option>
          <option value="1">Cervena</option>
          <option value="2">Zelena</option>
          <option value="3">Modra</option>
          <option value="4">Biela</option>
          <option value="5">Zlta</option>
          <option value="6">Farebne spektrum</option>
          <option value="7">Farebne spektrum hadik</option>
          <option value="8">Farebne spektrum hadik 2</option>
          <option value="9">Cerveno modry hadik</option>
          <option value="A">Party</option>
          <option value="B">Biely hadik</option>
          <option value="C">Biely hadik 2</option>
          <option value="D">effekt 8</option>
          <option value="E">effekt 9</option>
          <option value="F">effekt 10</option>
          <option value="G">effekt 11</option>
          <option value="H">Lava</option>
          <option value="I">Ocean</option>
          <option value="J">Forest</option>
          <option value="K">Random</option>
        </select>
        <input type="submit">
      </form>
    </td>
  </tr>
  </table>

  <hr class="dotted">

  <table id="input">
  <tr>
    <td>
      Rychlost blikania efektov [ms]
    </td>
    <td>
      <form action="/setEffectSpeed">
        <label for="stime"></label>
        <input type="text" id="stime" name="stime" value="100"> 
        <input type="submit">
      </form>
    </td>
  </tr>
  </table>

  <hr class="dotted">

  <table id="input">
  <tr>
    <td>
      Dlzka svietenia efektu pri nahodnom vybere [s]
    </td>
    <td>
      <form action="/setRandomTime">
        <label for="stime"></label>
        <input type="text" id="stime" name="stime" value="30"> 
        <input type="submit">
      </form>
    </td>
  </tr>
  </table>

  <hr class="dotted">

  <h3> Automaticke zapnutie a vypnutie stromceka </h3>
  <table id="input">
    <tr>
      <td>
        Automaticke zapnutie
      </td>
      <td>
        <form action="/autoOn">
          <label for="autoOn"></label>
          <select name="autoOn" id="autoOn">
            <option value="E">Zapnute</option>
            <option value="D">Vypnute</option>
          </select> 
          <input type="submit">
        </form>
      </td>
    </tr>
    <tr>
      <td>
        Vyber efektu
      </td>
      <td>
        <form action="/autoOnEffect">
          <label for="autoOnEffect"></label>
          <select name="autoOnEffect" id="autoOnEffect">
            <option value="0">OFF</option>
            <option value="1">Cervena</option>
            <option value="2">Zelena</option>
          <option value="3">Modra</option>
          <option value="4">Biela</option>
          <option value="5">Zlta</option>
          <option value="6">Farebne spektrum</option>
          <option value="7">Farebne spektrum hadik</option>
          <option value="8">Farebne spektrum hadik 2</option>
          <option value="9">Cerveno modry hadik</option>
          <option value="A">Party</option>
          <option value="B">Biely hadik</option>
          <option value="C">Biely hadik 2</option>
          <option value="D">effekt 8</option>
          <option value="E">effekt 9</option>
          <option value="F">effekt 10</option>
          <option value="G">effekt 11</option>
          <option value="H">Lava</option>
          <option value="I">Ocean</option>
          <option value="J">Forest</option>
          <option value="K">Random</option>
        </select>
          <input type="submit">
        </form>
      </td>
    </tr>

    <tr>
      <td>
        Automaticke zapnutie
      </td>
      <td>
        <form action="/autoOnTimeOn">
          <label for="autoOnTimeOn"></label>
          <input type="text" id="autoOnTimeOn" name="autoOnTimeOn" value="19:00:00"> 
          <input type="submit">
        </form>
      </td>
    </tr>
    
    <tr>
      <td>
        Automaticke vypnutie
      </td>
      <td>
        <form action="/autoOnTimeOff">
          <label for="autoOnTimeOff"></label>
          <input type="text" id="autoOnTimeOff" name="autoOnTimeOff" value="23:00:00"> 
          <input type="submit">
        </form>
      </td>
    </tr>
  </table>

  <hr class="dotted">

  Created by: miroslav.pivovarsky@gmail.com

<script>
(function() {
  var reqData = function() {
    jQuery.ajax({
            url: '/json_input',
            type: 'GET',
            timeout: 30000,
            success: function(data) {
              console.log("Incommming data: ");
              console.log(data);
              var obj = JSON.parse(data);
              console.log(obj);

              $("#time").text(obj.time);
              $("#effect").text(obj.effect);
              $("#autoOn").text(obj.autoOn);
              $("#autoOnEffect").text(obj.autoOnEffect);
              $("#autoOnTimeOn").text(obj.autoOnTimeOn);
              $("#autoOnTimeOff").text(obj.autoOnTimeOff);
              $("#FirmwareMcu").text(obj.FirmwareMcu);
              $("#EffectSpeed").text(obj.EffectSpeed);
              $("#RandomTime").text(obj.RandomTime);
              $("#FirmwareWifi").text(obj.FirmwareWifi);
            },
            error: function(html) {
              console.log("json Timeout or error");
              alert("jquery timeout or comunication error");
            }
        });
  }
  reqData();
  //var t=setTimeout(function(){reqData();},20000)
})();
</script></body></html>

)=====";

#endif
