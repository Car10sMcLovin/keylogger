# keylogger
Este repositorio contiene un keylogger escrito en lenguaje C para un sistema linux.

CASOS DE USO
Este tipo de programas pueden ser usados para espionaje, robo de contraseñas, cuentas bancarias e informacion sensible. En casos legales pueden ser usados para recuperar datos en caso de que falle un sistema, en auditorias de seguridad para ver que los empleados no filtren informacion de la empresa, etc.
El siguiente programa captura las teclas que se presionan en una terminal y las guarda en un archivo de texto.

INSTRUCCIONES
- Este programa debe correrse en Linux ya que esta hecho para este sistema
- Lo primero que se debe hace es ubicarnos en el directorio donde esta guardado
- Despues debemos compilar el programa adjunto con el comando "gcc keylogger.c -o keylogger"
- Luego de eso lo vamos a ejecutar como root con el comando "sudo ./keylogger"
- Despues de esto, ya todo lo que se escriba se ira guardando en el archivo keylogger.txt
- Si queremos ver en tiempo real lo que se va escribiendo, abrimos otra terminal y ponemos "cat (la ruta del archivo de texto)", despues ponemos "tail -f (la ruta del archivo de texto)"
- Ya solo bastara ir checando en la terminal lo que se va escribiendo.

ADVERTENCIAS
Este tipo de programas puede ser utilizado con fines maliciosos, se recomienda usarlos de manera educativa y siempre apegandose la etica.
