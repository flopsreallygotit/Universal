#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "universalUtils.h"

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

void *recalloc (void *ptr, size_t newSize) 
{
    size_t oldSize = malloc_usable_size(ptr);

    ptr = realloc(ptr, newSize);
    char *endptr = (char *) ptr;

    for (size_t idx = oldSize; idx < newSize; idx++) 
        endptr[idx] = 0;

    return ptr;
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
    va_list arg;
    va_start(arg, format);

    char str[512] = "";

    vsprintf(str, format, arg); 

    va_end(arg);

    return system(str);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int differenceSign (double firstNumber, 
                    double secondNumber)
{
    static const double epsilon = 1e-9;

    const double difference = firstNumber - secondNumber;

    if (difference > epsilon)
        return  1;
    if (difference < -epsilon)
        return -1;
    
    return 0;
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

const char *simpleCommandLineParser (const int argc, const char *argv[])
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
