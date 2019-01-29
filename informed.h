//
// Created by iksf on 29/01/19.
//

#ifndef MISSIONARIESANDCANNIBALS2_INFORMED_H
#define MISSIONARIESANDCANNIBALS2_INFORMED_H

#include "main.h"

uint32_t score_bank(BankState *b);

int32_t score_gamestate(GameState *g);

GameState *best_child_node(Node *n);

#endif //MISSIONARIESANDCANNIBALS2_INFORMED_H
