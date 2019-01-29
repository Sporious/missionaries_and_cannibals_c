//
// Created by iksf on 29/01/19.
//

#ifndef MISSIONARIESANDCANNIBALS_MAIN_H
#define MISSIONARIESANDCANNIBALS_MAIN_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint32_t bank_missionaries;
    uint32_t bank_cannibals;
    bool raft;
} BankState;

typedef struct {
    BankState north;
    BankState south;
} ProblemState;

typedef enum Bank {
    North, South
} Bank;

void error(const char *);

BankState *get_bank_state(ProblemState *, Bank);

bool str_has_boat(char *);

ProblemState problemstate_from_string(char *);

void extract_line_to_bankstate(char *, ProblemState *);

uint32_t parse(char *, char);


#endif //MISSIONARIESANDCANNIBALS_MAIN_H
