#ifndef html_templates_h
#define html_templates_h

#include <avr/pgmspace.h>

const char index_html[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html>
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        <style>
            html {
                font-family: Arial;
                display: inline-block;
                margin: 0px auto;
                text-align: center;
            }
            h2 {
                font-size: 3rem;
            }
        </style>
    </head>
    <body>
        <h1>IoT Teplomer a vlhkomer.</h1>
        <h3>Zadejte SSID a heslo wifi site.</h3>
        <form id="networkForm">
          <label for="ssid">SSID:</label><br>
          <input type="text" id="ssid" name="ssid" placeholder="myNetwork" required><br>
          <br>
          <label for="password">Heslo:</label><br>
          <input type="text" id="password" name="passsword" placeholder="password" required><br><br>
          <br>
          <input type="button" value="Odeslat a restartovat jednotku" onclick="sendSsidAndPassword()">
        </form>

        <br>
        <label id="resultLabel"></label>

        <script type="text/javascript">

            function validate(data, resultElement){
               
                var isValid = true;
                if (data.ssid.length < 1)
                    isValid = false;
                if (data.password.length < 1)
                    isValid = false;

                if (!isValid){
                    resultElement.innerHTML = "Pole ssid a heslo musí být vyplněné!."
                    resultElement.style.color = 'red';
                }

                return isValid;
            }

            function sendSsidAndPassword() {
                var resultElement = document.getElementById("resultLabel");
                var formElement = document.getElementById("networkForm");

                var data = { ssid: formElement.ssid.value, password: formElement.password.value }
                if (!validate(data, resultElement)) return;
                
                var formData = new FormData();
                formData.append("ssid", data.ssid);
                formData.append("password", data.password);
                // TODO: Callback
                var xhttp = new XMLHttpRequest();
                xhttp.open("POST", "api/confirmSsidAndPassword", true);
                xhttp.send(formData);

                resultElement.innerHTML = "Odesláno, jednotka se restartuje."
                resultElement.style.color = 'green';
            }

        </script>
    </body>
</html>
)rawliteral";

#endif
