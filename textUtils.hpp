#pragma once

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "universalUtils.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief text_t *struct

typedef struct text_t
{
    char *buffer;
    char **lines;

    size_t lineCount;
    size_t symbolsCount;
} text_t;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Creates text_t *struct
/// @param filename Name of file
/// @param makeLines Bool flag. If it is true, then text_t *struct will contain array with pointers to the start of lines

void textConstructor (text_t *text, const char *filename, bool makeLines);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Deletes text struct

void textDestructor (text_t *text);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Prints line of text depending on it's index
/// @param lineIndex Index of line

void printLine (text_t *text, size_t lineIndex);

/// @brief Prints text_t *struct buffer

void printText (text_t *text);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
