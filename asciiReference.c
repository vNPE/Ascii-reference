#include <stdio.h>
#include <string.h>

#define YELLOW "\x1B[0;33m"
#define GREEN  "\x1B[0;32m"
#define BRIGHT_GREEN "\x1B[92m"
#define RESET  "\x1B[0m"

const char *ctrl_name(int c) {
    switch (c) {
        case 0:  return "NUL"; case 1:  return "SOH"; case 2:  return "STX"; case 3:  return "ETX"; case 4:  return "EOT"; case 5:  return "ENQ";
        case 6:  return "ACK"; case 7:  return "BEL"; case 8:  return "BS";  case 9:  return "HT";  case 10: return "LF";  case 11: return "VT";
        case 12: return "FF";  case 13: return "CR";  case 14: return "SO";  case 15: return "SI";  case 16: return "DLE"; case 17: return "DC1";
        case 18: return "DC2"; case 19: return "DC3"; case 20: return "DC4"; case 21: return "NAK"; case 22: return "SYN"; case 23: return "ETB";
        case 24: return "CAN"; case 25: return "EM";  case 26: return "SUB"; case 27: return "ESC"; case 28: return "FS";  case 29: return "GS";
        case 30: return "RS";  case 31: return "US";  case 127: return "DEL";
        default: {    static char buf[2];    buf[0] = (char)c;    buf[1] = '\0';    return buf;}
    }
}

void printTable(int columns){
    columns = columns/16.5>=8 ? 8 : columns/16.5;
    int space=1;
    printf(YELLOW"Your friendly neighborhood ASCII table:\n"RESET);

    for(int i=0;i<=127;i++){
        printf(BRIGHT_GREEN"%d"RESET":", i);
        for(int j=i; j>=10; space++)
            j/=10;
        for(int j=7-space; j>0; j--)
            printf(" ");

        printf("'"GREEN"%s"RESET"'", ctrl_name(i));
        if(i%columns==columns-1)
            putchar('\n');
        else
            for(int j=7-strlen(ctrl_name(i)); j>0;j--)
                putchar(' ');
        space=1;
    }

}

#ifdef _WIN32
    #include <windows.h>

    void win_size(){
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        printTable(columns);
    }

#elif __linux__
    #include <sys/ioctl.h>

    void linux_size(){
        struct winsize sz;
        ioctl( 0, TIOCGWINSZ, &sz );
        printTable(sz.ws_col);
    }
#endif

int main(void){
    #ifdef _WIN32
        win_size();
    #elif __linux__
        linux_size();
    #endif
        return 0;
}
