# Monitoramento de Nível com ESP32 e MQTT

Este projeto realiza a leitura de nível de um tanque usando sensor ultrassônico com ESP32, enviando dados via MQTT para supervisão e acionamento de alarme.

## Funcionalidades
- Leitura de nível em cm.
- Envio de dados via MQTT.
- Acionamento de alarme se nível crítico.

## Tecnologias
- ESP32
- MQTT (Broker público HiveMQ)
- Sensor Ultrassônico HC-SR04
- Arduino IDE / Wokwi

## Circuito
<img width="571" height="351" alt="image" src="https://github.com/user-attachments/assets/8975362a-6b8b-45df-883a-c0ce592a2039" />


## Código
O código-fonte está no arquivo `codigo.ino`.

## configuração node-red 
-Nó MQTT IN com broker HiveMQ, tópico "Tanque/Nivel"
-Nó Gauge para criação da interface,  Label "Nivel (%)" Value format "{{value}}"
-Nó Debug para depuração no node-red

<img width="781" height="476" alt="image" src="https://github.com/user-attachments/assets/2cc92efb-2fe4-4262-8504-3992b467fb6e" />


## dashboard 

<img width="1366" height="639" alt="image" src="https://github.com/user-attachments/assets/1ff75a84-9f12-48fe-97cf-4b30b9e81ce7" />

## Simulação no Wokwi
(https://wokwi.com/projects/439092813250800641)

## Como usar
- Com o IP de onde está o node-red.
- acessar com o link no navegar utilizando por exemplo (http://<IP-do-computador>:1880/ui)

