#include "naked_triples.h"
#include <stdlib.h>
#include <stdio.h>

int find_naked_triples(Cell **p_cells, Triple *triples, int *num_triples)
{
    int counter = 0;

    for (int i = 0; i < BOARD_SIZE - 2; i++)
    {
        if (p_cells[i]->num_candidates < 2 || p_cells[i]->num_candidates > 3)
        {
            continue;
        }

        for (int j = i + 1; j < BOARD_SIZE - 1; j++)
        {
            if (p_cells[j]->num_candidates < 2 || p_cells[j]->num_candidates > 3)
            {
                continue;
            }

            for (int k = j + 1; k < BOARD_SIZE; k++)
            {
                if (p_cells[k]->num_candidates < 2 || p_cells[k]->num_candidates > 3)
                {
                    continue;
                }

                int naked_triples_candidates[BOARD_SIZE] = {0};

                int *candidates_i = get_candidates(p_cells[i]);
                int *candidates_j = get_candidates(p_cells[j]);
                int *candidates_k = get_candidates(p_cells[k]);

                for (int l = 0; l < p_cells[i]->num_candidates; l++)
                {
                    naked_triples_candidates[candidates_i[l]-1] += 1;
                }

                for (int l = 0; l < p_cells[j]->num_candidates; l++)
                {
                    naked_triples_candidates[candidates_j[l]-1] += 1;
                }

                for (int l = 0; l < p_cells[k]->num_candidates; l++)
                {
                    naked_triples_candidates[candidates_k[l]-1] += 1;
                }

                free(candidates_i);
                free(candidates_j);
                free(candidates_k);

                int count = 0;
                for (int l = 0; l < BOARD_SIZE; l++)
                {
                    if (naked_triples_candidates[l] >= 1)
                    {
                        count++;
                    }
                    if (count > 3)
                    {
                        continue;
                    }
                }

                if (count == 3)
                {   
                    bool already_counted = false;
                    for (int l = 0; l < *num_triples; l++)
                    {
                        if ((triples[l].cells[0] == p_cells[i] && triples[l].cells[1] == p_cells[j] && triples[l].cells[2] == p_cells[k]) ||
                            (triples[l].cells[0] == p_cells[i] && triples[l].cells[1] == p_cells[k] && triples[l].cells[2] == p_cells[j]) ||
                            (triples[l].cells[0] == p_cells[j] && triples[l].cells[1] == p_cells[i] && triples[l].cells[2] == p_cells[k]) ||
                            (triples[l].cells[0] == p_cells[j] && triples[l].cells[1] == p_cells[k] && triples[l].cells[2] == p_cells[i]) ||
                            (triples[l].cells[0] == p_cells[k] && triples[l].cells[1] == p_cells[i] && triples[l].cells[2] == p_cells[j]) ||
                            (triples[l].cells[0] == p_cells[k] && triples[l].cells[1] == p_cells[j] && triples[l].cells[2] == p_cells[i]))
                        {
                            already_counted = true;
                            break;
                        }
                    }

                    if (!already_counted)
                    {
                        triples[*num_triples].cells[0] = p_cells[i];
                        triples[*num_triples].cells[1] = p_cells[j];
                        triples[*num_triples].cells[2] = p_cells[k];
                        (*num_triples)++;

                        for (int l = 0; l < BOARD_SIZE; l++)
                        {
                            if (naked_triples_candidates[l] >= 1)
                            {
                                for (int m = 0; m < BOARD_SIZE; m++)
                                {
                                    if ((p_cells[m]->num_candidates > 1) && (p_cells[m] != p_cells[i]) && (p_cells[m] != p_cells[j]) && (p_cells[m] != p_cells[k]))
                                    {
                                        for (int n = 0; n < BOARD_SIZE; n++)
                                        {
                                            if ((p_cells[m]->candidates[n] == 1) && (n == l))
                                            {
                                                unset_candidate(p_cells[m], l+1);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        counter++;
                    }
                }
            }
        }
    }

    return counter;
}

int naked_triples(SudokuBoard *p_board)
{
    int naked_triples_counter = 0;
    Triple triples[BOARD_SIZE * BOARD_SIZE];
    int num_triples = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {   
        naked_triples_counter += find_naked_triples(p_board->p_rows[i], triples, &num_triples);
        naked_triples_counter += find_naked_triples(p_board->p_cols[i], triples, &num_triples);
        naked_triples_counter += find_naked_triples(p_board->p_boxes[i], triples, &num_triples);
    }

    return naked_triples_counter;
}