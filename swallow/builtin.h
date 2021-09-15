// Original author: MD Gaziur Rahman Noor

// #ifndef SWALLOW_BUILTIN_H
// #define SWALLOW_BUILTIN_H
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define True true
#define False false

char *inputString(FILE* fp, size_t size){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(*str)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(*str)*len);
}
double myFloor(double x) /* Change this to your liking: long double might
                                             be float in your situation.  */
{
    long double xcopy=x<0?x*-1:x;
    unsigned int zeros=0;
    long double n=1;
    for(n=1;xcopy>n*10;n*=10,++zeros);
    for(xcopy-=n;zeros!=-1;xcopy-=n)
        if(xcopy<0)
        {
            xcopy+=n;
            n/=10;
            --zeros;
        }
    xcopy+=n;
    return x<0?(xcopy==0?x:x-(1-xcopy)):(x-xcopy);
}
/*
 * Builtin formatter function
 * Author: MD Gaziur Rahman Noor
 *
 * Made specifically to work on char* or char[] only.
 * Using any other types might result in a segfault.
 *
 * Example:
 * _format("Hello {}!\n", "world");
 *
 * Output:
 * Hello world!
 *
 */
char *_format(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    // make sure it's not empty or null
    char *result = NULL;
    size_t size = 0;
    size_t fmt_size = strlen(fmt);

    if(fmt_size > 0) {
        result = (char*)malloc(sizeof(char));

        // add one character if it's not possibly format string
        if (*fmt != '{' || !(*(fmt+1) && *(fmt+1) == '}')) {
            result[0] = *fmt;
            size += 1;
            fmt++;
        }
    } else {
        return (char*)"";
    }

    while(*fmt) {
        // check if it's format string
        if (*fmt == '{') {
            if (*(fmt+1) && *(fmt+1) == '}') {
                char *arg = va_arg(args, char*);
                size_t a_size = strlen(arg);

                result = (char*)realloc(result, size + a_size);
                memcpy(result + size, arg, a_size);
                size += a_size;
                fmt++; // ignore '}'
            }
        }
        else {
            // increase size and push char
            result = (char*)realloc(result, size + 1);
            memcpy(result + size, fmt, 1);
            size += 1;
        }

        fmt++;
    }

    // null terminate if it's not null
    if(result) {
        result = (char*)realloc(result, size + 1);
        result[size] = '\0';
    }

    return result;
}

/* _colorprint() implementation */

/*
 * int64_t
 *
 * Put foreground color in first half
 */

// Foreground(text) colors


/*
 * Builtin Color Print Function
 * Author: MD Gaziur Rahman Noor
 *
 * Formats given string specifically so that it is colored as
 * specified when printed to stdout
 *
 * Example:
 * _colorprint("Hello World!", SH_FG_BLACK , true);
 */
void _colorprint(const char *str, char *color, bool reset) {
    int64_t flags;
    if (strcmp(color, "BLACK")==0){
        flags=(30 << 8);
    }
    else if (strcmp(color, "RED")==0){
        flags=(31 << 8);
    }
    else if (strcmp(color, "GREEN")==0){
        flags=(32 << 8);
    }
    else if (strcmp(color, "YELLOW")==0){
        flags=(33 << 8);
    }
    else if (strcmp(color, "BLUE")==0){
        flags=(34 << 8);
    }
    else if (strcmp(color, "MAGENTA")==0){
        flags=(35 << 8);
    }
    else if (strcmp(color, "CYAN")==0){
        flags=(36 << 8);
    }
    else if (strcmp(color, "WHITE")==0){
        flags=(37 << 8);
    }
    int8_t foreground = (flags & 0xFF00) >> 8;
    printf("\e[1;%dm%s", foreground, str);
    if(reset)
        printf("\e[1;0m");
}
double mypow(double base, double power)
{
    double result = 1;
    if (power >= 0)
    {

        while (power--)
        {
            result = result * base;
        }

        return result;
    }
    else if (power < 0)
    {
        while (power++)
        {
            result = result * base;
        }
        return 1 / result;
    }
}

// #endif //SWALLOW_BUILTIN_H