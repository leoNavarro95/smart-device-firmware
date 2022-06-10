# Smart Device

Este proyecto esta pensado para correr tanto en ESP8266 como en ESP32

## Configuracion de la web

La pagina web esta montada en la carpeta data hubicada en la raiz del projecto. Esta carpeta se encuentra alojada en el sistema de archivos littleFS.

Cada vez que se cambie algo dentro de data para subirlo a la placa basada en ESP hay que ejecutar la tarea de platformio **Upload Filesystem Image**, para realizarlo dar click en el icono a la izquierda de Platformio y buscar dentro de Project Tasks/Platform/Upload Filesystem Image 

## Indicaciones para trabajar con el sistema de archivos