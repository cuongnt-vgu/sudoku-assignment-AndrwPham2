#pragma once

#include "sudoku.h"
struct Triple_impl
{
    Cell *cell1;
    Cell *cell2;
    Cell *cell3;
    int *arr; 
};

typedef struct Triple_impl HiddenTriples;
void unset_hidden_triple_values(HiddenTriples *hiddenTriples, int *num_hidden_triples);
int find_hidden_triple_values(Cell **p_cells, int *hidden_triple_values);
void find_hidden_triples(Cell **p_cells, HiddenTriples *p_hidden_triples, int *p_counter);
int hidden_triples(SudokuBoard *p_board);