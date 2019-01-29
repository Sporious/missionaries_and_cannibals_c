//
// Created by iksf on 29/01/19.
//

#ifndef MISSIONARIESANDCANNIBALS2_MAIN_H
#define MISSIONARIESANDCANNIBALS2_MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint32_t missionaries;
    uint32_t cannibals;
    bool raft;
} BankState;

typedef struct {
    BankState north;
    BankState south;
} GameState;


typedef struct Node {
    GameState game_state;
    struct Node *parent;
    struct Node *children[5];
} Node;

BankState parse_line(char *line);

void error(const char *e);


void add_child_to_node(Node *n, GameState g);

void free_tree(Node *n);


#endif //MISSIONARIESANDCANNIBALS2_MAIN_H
