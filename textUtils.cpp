#include <stdlib.h>
#include <sys/stat.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "textUtils.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static void getLineCount (text_t *text)
{
    text->lineCount = 1; // We have a guarantee that file contains minimum 1 line.

    for (size_t bufferIndex = 0; text->buffer[bufferIndex] != '\0'; bufferIndex++)
        if (text->buffer[bufferIndex] == '\n')
            text->lineCount++;

    return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static ISERROR createBuffer (text_t *text, FILE *file)
{
    struct stat fileStatBuffer;
    fstat(fileno(file), &fileStatBuffer);
    text->symbolsCount = (size_t) fileStatBuffer.st_size;

    text->buffer = (char *) calloc (text->symbolsCount + 1, sizeof(char));

    CHECKERROR(text->buffer != NULL &&
               "Can't allocate memory for buffer.",
               ALLOCATIONERROR);

    CHECKERROR(fread(text->buffer, sizeof(char), text->symbolsCount, file) != 0 &&
               "Can't read from file.",
               WRONGFILE);

    return NOTERROR;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static ISERROR createLines (text_t *text)
{
    getLineCount(text);

    text->lines = (char **) calloc (text->lineCount, sizeof(char *));

    CHECKERROR(text->lines != NULL &&
               "Can't allocate memory for lines buffer.",
               ALLOCATIONERROR);

    text->lines[0] = text->buffer;

    size_t lineIndex = 1; // We've already filled zero index 
    for (size_t bufferIndex = 0; text->buffer[bufferIndex] != '\0'; bufferIndex++)
        if (text->buffer[bufferIndex] == '\n')
        {
            text->lines[lineIndex] = text->buffer + bufferIndex + 1;

            lineIndex++;
        }
    

    return NOTERROR;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void textConstructor (text_t *text, const char *filename, bool makeLines)
{
    CHECKERROR(filename != NULL &&
               "Can't create text_t struct with NULL input.",
               (void) NULL);

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        PUTERROR("Can't open file.");
        fprintf(stderr, BOLD RED "FILE: '%s'\n" RESET, filename);

        return;
    }

    CHECKERROR(createBuffer(text, file) == NOTERROR &&
               "Can't create buffer for text_t *struct.", 
               (void) NULL);

    if (makeLines)
    {
        CHECKERROR(createLines(text) == NOTERROR &&
                   "Can't create lines buffer from text_t *struct.", 
                   (void) NULL);
    }

    else
        text->lines = NULL;

    fclose(file);

    return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void textDestructor (text_t *text)
{
    free(text->lines); // Lines is NULL / Pointer to allocated memory && free(NULL) is accepted in C/C++
    free(text->buffer);

    *text = {
                .buffer = NULL,
                .lines  = NULL,
                
                .lineCount    = 0,
                .symbolsCount = 0
            };

    return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void printLine (text_t *text, size_t lineIndex)
{
    if (text->lines == NULL)
        return;

    if (lineIndex >= text->lineCount)
    {
        PUTWARNING("Line doesn't exist");

        return;
    }

    for (size_t symbolIndex = 0; 
         text->lines[lineIndex][symbolIndex] != '\n' &&
         text->lines[lineIndex][symbolIndex] != '\0'; 
         symbolIndex++)
         putchar(text->lines[lineIndex][symbolIndex]);

    putchar('\n');

    return;    
}

void printText (text_t *text)
{
    printf("%s", text->buffer);

    return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
