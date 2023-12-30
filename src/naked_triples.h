#pragma once

#include "sudoku.h"
typedef struct {
    Cell *cells[3];
} Triple;

int naked_triples(SudokuBoard *p_board);