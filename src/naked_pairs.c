#include "naked_pairs.h"
#include <stdlib.h>
#include <stdio.h>

int find_naked_pairs(Cell **p_cells, Pairs *pairs, int *num_pairs)
{
    int counter = 0;

    for (int i = 0; i < BOARD_SIZE - 1; i++)
    {
        if (p_cells[i]->num_candidates != 2)
        {
            continue;
        }

        for (int j = i + 1; j < BOARD_SIZE; j++)
        {
            if (p_cells[j]->num_candidates != 2)
            {
                continue;
            }

            int *candidates_i = get_candidates(p_cells[i]);
            int *candidates_j = get_candidates(p_cells[j]);

            if (candidates_i[0] == candidates_j[0] && candidates_i[1] == candidates_j[1])
            {
                bool already_counted = false;
                for (int k = 0; k < *num_pairs; k++)
                {
                    if ((pairs[k].cells[0] == p_cells[i] && pairs[k].cells[1] == p_cells[j]) ||
                        (pairs[k].cells[0] == p_cells[j] && pairs[k].cells[1] == p_cells[i]))
                    {
                        already_counted = true;
                        break;
                    }
                }

                if (!already_counted)
                {
                    pairs[*num_pairs].cells[0] = p_cells[i];
                    pairs[*num_pairs].cells[1] = p_cells[j];
                    (*num_pairs)++;

                    for (int k = 0; k < BOARD_SIZE; k++)
                    {
                        if ((p_cells[k]->num_candidates > 1) && (p_cells[k] != p_cells[i]) && (p_cells[k] != p_cells[j]))
                        {
                            for (int l = 0; l < BOARD_SIZE; l++)
                            {
                                if ((p_cells[k]->candidates[l] == 1) && (l == candidates_i[0] - 1 || l == candidates_i[1] - 1))
                                {
                                    unset_candidate(p_cells[k], l+1);
                                }
                            }
                        }
                    }
                    counter++;
                }
            }

            free(candidates_i);
            free(candidates_j);
        }
    }

    return counter;
}

int naked_pairs(SudokuBoard *p_board)
{
    int naked_pairs_counter = 0;
    Pairs pairs[BOARD_SIZE * BOARD_SIZE];
    int num_pairs = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {   
        naked_pairs_counter += find_naked_pairs(p_board->p_rows[i], pairs, &num_pairs);
        naked_pairs_counter += find_naked_pairs(p_board->p_cols[i], pairs, &num_pairs);
        naked_pairs_counter += find_naked_pairs(p_board->p_boxes[i], pairs, &num_pairs);
    }

    return naked_pairs_counter;
}
