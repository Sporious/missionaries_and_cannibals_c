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


void add_child_to_node(Node *n, GameState g, uint32_t target_hash);

void free_tree(Node *n);


void add_gamestate_to_parent(Node *parent_node, uint32_t missionaries, uint32_t cannibals, uint32_t hash_target);

void gen_child_gamestates(Node *parent_node, uint32_t hash_target);


void on_complete(Node *node);

void print_answers_array(Node **answers_array, size_t argc);

void print(GameState *g);

uint32_t hash(GameState *g);

uint32_t hash_node(Node *n);

bool check_parent_hashes(Node *root, uint32_t hash_value, uint32_t hash_target);

#endif //MISSIONARIESANDCANNIBALS2_MAIN_H
