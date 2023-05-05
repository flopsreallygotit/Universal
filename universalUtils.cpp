#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "universalUtils.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void logf (const char *file, const int line, const char *function,
           FILE *output, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    fprintf(output, BOLD MAGENTA "%s:%d | %s | " RESET,
            file, line, function);
            
    vfprintf(output, format, args);

    va_end(args);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void *recalloc (void *pointer, size_t newSize) 
{
    size_t oldSize = malloc_usable_size(pointer);

    pointer = realloc(pointer, newSize);

    CHECKERROR(pointer != NULL &&
               "Can't reallocate memory for pointer.",
               NULL);

    char *newPartPointer = (char *) pointer + oldSize;

    memset(newPartPointer, 0, newSize - oldSize);

    return pointer;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

char *stralloccat(const char *dst, const char *src)
{
    char *string = (char *) calloc (strlen(dst) + strlen(src) + 1, sizeof(char));

    strcpy(string, dst);
    strcat(string, src);

    return string;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int systemf (const char *format, ...)
{
    static const size_t bufferSize = 512;

    va_list arg;
    va_start(arg, format);

    char str[bufferSize] = "";

    vsprintf(str, format, arg); 

    va_end(arg);

    return system(str);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int differenceSign (double firstNumber, 
                    double secondNumber)
{
    static const double epsilon = 1e-9;

    double difference = abs(firstNumber - secondNumber);

    return difference < epsilon * abs(firstNumber) ||
           difference < epsilon * abs(secondNumber);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

double dmin (double firstNumber, 
             double secondNumber)
{
    if (differenceSign(firstNumber, secondNumber) >= 0)
        return firstNumber;

    return secondNumber;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const char *checkFirstArgvAndGetIt (const int argc, const char *argv[])
{
    CHECKERROR(argv != NULL &&
               "Argv pointer can't be NULL.",
               NULL);

    CHECKERROR(argc != 1 &&
               "You need to enter only one argument."
               "Example: ./main flopsreallygot.it", 
               NULL);

    return argv[1];
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
