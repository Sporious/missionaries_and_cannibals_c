//
// Created by iksf on 29/01/19.
//
#include "informed.h"

int32_t score_gamestate(GameState *g) {
    return score_bank(&g->north) - score_bank(&g->south);
}

uint32_t score_bank(BankState *b) {
    return b->missionaries + b->cannibals + b->raft;
}

GameState *best_child_node(Node *n) {

    int32_t best_score = INT32_MIN;
    Node *best_child = NULL;

    for (int i = 0; i < 5; i++) {
        Node *next = n->children[i];
        if (next != NULL) {
            int32_t score = score_gamestate(&next->game_state);
            if (score > best_score) {
                best_score = score_gamestate;
                best_child = next;
            }
        }
    }
    return best_child;

}