#include "hidden_singles.h"

int is_unique(Cell **p_cells, Cell *cell)
{
  int tmp[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    if (p_cells[i] == cell)
      continue;
    if (p_cells[i]->num_candidates == 1)
    {
      tmp[p_cells[i]->value - 1] -= 1;
      continue;
    }
    int *p = get_candidate(p_cells[i]);
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      tmp[j] -= p[j];
    }
  }
  for (int i = 0; i < BOARD_SIZE; i++)
    if (tmp[i] == 1)
      return i + 1;
  return 0;
}

int find_hidden_single_values(SudokuBoard *p_board, Cell *cell)
{
  int tmp;
  tmp = is_unique(p_board->p_rows[cell->row_index], cell);
  if (tmp != 0)
    return tmp;
  tmp = is_unique(p_board->p_cols[cell->col_index], cell);
  if (tmp != 0)
    return tmp;
  tmp = is_unique(p_board->p_boxes[cell->box_index], cell);
  return tmp;
}
void update_hidden_singles(SudokuBoard *p_board) {
  // Loop through all cells again
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int col = 0; col < BOARD_SIZE; col++) {
      Cell *cell = &p_board->data[row][col];

      // Check if cell has a hidden single based on its candidate count
      // int value = find_hidden_single_values(p_board, cell);
      if (cell->value > 0) {
        // Found single candidate, update cell value
        set_candidates(cell, &cell->value, 1); // Update with first candidate (assumed single)
      }
    }
  }
}
int hidden_singles(SudokuBoard *p_board)
{
  int total_placed_singles = 0;
  for (int row = 0; row < BOARD_SIZE; ++row)
  {
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
      Cell *cell = &p_board->data[row][col];
      if (cell->num_candidates == 1)
        continue; // Skip already filled cells

      // Place all found hidden singles

      int value = find_hidden_single_values(p_board, cell);
      if (value != 0)
      {
        cell->value = value;
        total_placed_singles++;
      }
    }

  }
  if (total_placed_singles > 0)
    update_hidden_singles(p_board); 
  return total_placed_singles;
}