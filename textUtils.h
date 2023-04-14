#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "universalUtils.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Text struct.

typedef struct text
{
    char *buffer;
    char **lines;

    size_t lineCount;
    size_t symbolsCount;
}text;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Creates text struct.
/// @param input Name of input file.

text *textConstructor (const char *input);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Deconstructs latex struct.
/// @param Text Pointer to text struct.

void textDestructor (text *Text);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Prints line of text depending on it's index.
/// @param Text Pointer to text struct.
/// @param line_idx Index of line.

void printLine (text *Text, size_t line_idx);

/// @brief Prints text.
/// @param Text Pointer to text struct.

void printText (text *Text);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif