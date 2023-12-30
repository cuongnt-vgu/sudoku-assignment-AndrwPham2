#pragma once

#include "sudoku.h"

typedef struct {
    
    Cell *cells[2];

} Pairs;

int naked_pairs(SudokuBoard *p_board);
int find_naked_pairs(Cell **p_cells, Pairs *pairs, int *num_pairs);