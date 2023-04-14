#include <stdlib.h>
#include <sys/stat.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "textUtils.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static void getSymbolsCount (text *Text, FILE *file)
{
    struct stat fileStatBuffer;
    fstat(fileno(file), &fileStatBuffer);
    Text->symbolsCount = (size_t) fileStatBuffer.st_size;

    return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static void getLineCount (text *Text)
{
    Text->lineCount = 1; // We have a guarantee that file contains minimum 1 line.

    for (size_t buffer_idx = 0; Text->buffer[buffer_idx] != '\0'; buffer_idx++)
        if (Text->buffer[buffer_idx] == '\n')
            Text->lineCount++;

    return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static ISERROR createBuffer (text *Text, FILE *file)
{
    getSymbolsCount(Text, file);

    Text->buffer = (char *) calloc (Text->symbolsCount + 1, sizeof(char));

    CHECKERROR(Text->buffer != NULL &&
               "Can't allocate memory for buffer.",
               ALLOCATIONERROR);

    fread(Text->buffer, sizeof(char), Text->symbolsCount, file);

    return NOTERROR;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static ISERROR createLines (text *Text)
{
    getLineCount(Text);

    Text->lines = (char **) calloc (Text->lineCount, sizeof(char *));

    CHECKERROR(Text->lines != NULL &&
               "Can't allocate memory for lines buffer.",
               ALLOCATIONERROR);

    Text->lines[0] = Text->buffer;

    size_t line_idx   = 1; // We've already filled zero index 
    size_t buffer_idx = 0;

    while (Text->buffer[buffer_idx] != '\0')
    {
        if (Text->buffer[buffer_idx] == '\n')
        {
            Text->lines[line_idx] = Text->buffer + buffer_idx + 1;

            line_idx++;
        }

        buffer_idx++;
    }

    return NOTERROR;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

text *textConstructor (const char *input)
{
    CHECKERROR(input != NULL &&
               "Can't create text struct with null input.",
               NULL);

    text *Text = (text *) calloc (1, sizeof(text));

    CHECKERROR(Text != NULL &&
               "Can't allocate memory for text struct.",
               NULL);

    FILE *file = fopen(input, "r");

    if (file == NULL)
    {
        PUTERROR("Can't open file.");
        fprintf(stderr, BOLD RED "FILE: '%s'\n" RESET, input);

        free(Text);
        Text = NULL;

        return NULL;
    }

    CHECKERROR(createBuffer(Text, file) == NOTERROR &&
               "Can't create buffer for text struct.", 
               NULL);

    CHECKERROR(createLines(Text) == NOTERROR &&
               "Can't create lines buffer from text struct.", 
               NULL);

    fclose(file);

    return Text;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void textDestructor (text *Text)
{
    if (Text == NULL)
        return;

    free(Text->lines);
    free(Text->buffer);

    Text->lines  = NULL;
    Text->buffer = NULL;

    Text->symbolsCount = 0;
    Text->lineCount    = 0;

    free(Text);
    Text = NULL;

    return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void printLine (text *Text, size_t line_idx)
{
    if (Text == NULL)
        return;

    if (line_idx >= Text->lineCount)
    {
        PUTWARNING("Line doesn't exist");

        return;
    }

    for (size_t symbol_idx = 0; 
         Text->lines[line_idx][symbol_idx] != '\n' &&
         Text->lines[line_idx][symbol_idx] != '\0'; 
         symbol_idx++)
         putchar(Text->lines[line_idx][symbol_idx]);

    putchar('\n');

    return;    
}

void printText (text *Text)
{
    if (Text == NULL)
        return;

    for (size_t line_idx = 0; line_idx < Text->lineCount; line_idx++)
        printLine(Text, line_idx);

    return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
