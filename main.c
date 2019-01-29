
#include "main.h"

void error(const char *e) {
    printf("%s\n", e);
    abort();
}

int main() {
    char input[] = "N: 0m 0c\nS: 3m 3c R";
    char *line = strtok(input, "\n");
    char *lines[2];
    for (int i = 0; i < 2; i++) {
        lines[i] = calloc(30, 1);
    }
    while (line != NULL) {
        if (*line == 'N') {
            strcpy(lines[0], line);
        } else if (*line == 'S') {
            strcpy(lines[1], line);
        } else {
            error("An error occurred");
        }
        line = strtok(NULL, "\n");
    }

    Node *tree = malloc(sizeof(Node));
    GameState *g = &tree->game_state;
    g->north = parse_line(lines[0]);
    g->south = parse_line(lines[1]);
    for (int i = 0; i < 2; i++) {
        free(lines[i]);
    }

    free_tree(tree);


}


BankState parse_line(char *line) {
    char *word = strtok(&line[3], " ");
    BankState b;
    while (word != NULL) {
        char c = word[strlen(word) - 1];
        if (c == 'R') {
            b.raft = true;
        }
        if (c == 'm' || c == 'c') {
            word[strlen(word) - 1] = '\0';
        }
        if (c == 'm') {
            b.missionaries = atoi(word);
        }
        if (c == 'c') {
            b.cannibals = atoi(word);
        }
        word = strtok(NULL, " ");
    }
    return b;
}


void add_child_to_node(Node *n, GameState g) {
    Node *new = malloc(sizeof(Node));
    new->game_state = g;

    int i = 0;
    while (i < 5) {
        if (n->children[i] == NULL) {
            n->children[i] = &new;
            return;
        }
    }
}



void free_tree(Node *n) {
    for (int i = 0; i < 5; i++) {
        if (n->children[i] != NULL) {
            free_tree(n->children[i]);
        }
    }
    free(n);
}