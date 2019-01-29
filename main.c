#include "main.h"

void error(const char *e) {
    printf("%s\n", e);
    abort();
}

BankState *get_bank_state(ProblemState *p, Bank b) {
    switch (b) {
        case North:
            return &p->north;
        case South:
            return &p->south;
        default:
            error("Invalid bank state");
    }
}

ProblemState problemstate_from_string(char *s) {
    if (s == NULL) {
        error("Invalid string");
    }
    char *line = strtok(s, "\n");
    ProblemState ps;
    do {
        if (line != NULL) {

            extract_line_to_bankstate(line, &ps);
            line = strtok(line, NULL);
        }
    } while (line != NULL);
    return ps;

}

void extract_line_to_bankstate(char *line, ProblemState *p) {
    if (p == NULL || line == NULL) {
        error("null ptr exception");
    }

    BankState *c;
    switch (*line) {
        case 'N':
            c = &p->north;
            break;
        case 'S':
            c = &p->south;
            break;
        default:
            error("Invalid character");
            break;
    }

    line = &line[3];
    c->bank_cannibals = parse(line, 'c');
    c->bank_missionaries = parse(line, 'c');
    c->raft = str_has_boat(line);
}

bool str_has_boat(char *line) {
    uint32_t len = strlen(line);
    return line[len] == 'R';
}

uint32_t parse(char *line, char d) {
    uint32_t i = 0;
    char *m = memchr(line, d, 20);
    char *s = &m[-1];
    while (*s != ' ') {
        s--;
        i++;
    }
    char *str = malloc(i + 1);
    memcpy(str, s, i);
    return (uint32_t) atoi(str);
}

int main() {

    char *example = "N: 0m 0c\n"
                    "S: 3m 3c R";
    printf("%s\n", example);
    ProblemState p = problemstate_from_string(example);
    printf("%d %d", p.north.bank_missionaries, p.north.bank_cannibals);
    return 0;

}