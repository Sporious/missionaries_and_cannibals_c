
#include "main.h"

static bool done = false;

void error(const char *e) {
    printf("%s\n", e);
    abort();
}

void print(GameState *g) {
    if (g != NULL) {

        printf("N:%d %d %d S:%d %d %d\n", g->north.missionaries, g->north.cannibals, g->north.raft,
               g->south.missionaries,
               g->south.cannibals, g->south.raft);
    }
}

Node *tree_from_string(char *input) {
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
    Node *tree = calloc(sizeof(Node), 1);
    GameState *g = &tree->game_state;
    g->north = parse_line(lines[0]);
    g->south = parse_line(lines[1]);

    //Cleanup
    for (int i = 0; i < 2; i++) {
        free(lines[i]);
    }

    return tree;
}

int main() {
    char input[] = "N: 0m 0c\nS: 3m 3c R";
    char target[] = "N: 3m 3c R\nS: 0m 0c";

    Node *tree = tree_from_string(input);
    uint32_t target_hash = 0;


    {
        Node *target_node = tree_from_string(target);
        target_hash = hash_node(target_node);
        if (target_hash == 0)
            error("Invalid end state");
    }
    gen_child_gamestates(tree, target_hash);
    //Cleanup
    free_tree(tree);
    return 0;
}


void gen_child_gamestates(Node *parent_node, uint32_t hash_target) {
    if (done) {
        return;
    }
    for (size_t m = 0; m <= 2; m++) {
        for (size_t c = 0; c <= 2; c++) {
            add_gamestate_to_parent(parent_node, m, c, hash_target);
        }
    }

}

void add_gamestate_to_parent(Node *parent_node, uint32_t missionaries, uint32_t cannibals, uint32_t hash_target) {
    if (parent_node != NULL) {
        GameState *parent = &parent_node->game_state;
        if ((missionaries > cannibals) && (missionaries + cannibals) > 0) {
            GameState child;
            memcpy(&child, parent, sizeof(GameState));


            BankState *current, *other;
            if (child.north.raft) {
                current = &child.north;
                other = &child.south;
            } else {
                current = &child.south;
                other = &child.north;
            }

            current->raft = false;
            other->raft = true;

            if (current->cannibals >= cannibals && current->missionaries >= missionaries) {
                current->missionaries -= missionaries;
                current->cannibals -= cannibals;
                other->missionaries += missionaries;
                other->cannibals += cannibals;


                if (check_parent_hashes(parent_node, hash(&child), hash_target)) {
                    add_child_to_node(parent_node, child, hash_target);
                }
            }

        }
    }
}


BankState parse_line(char *line) {
    char *word = strtok(&line[3], " ");
    BankState b;
    b.raft = false;
    while (word != NULL) {
        char c = word[strlen(word) - 1];
        if (c == 'R') {
            b.raft = true;
        } else if (c == 'm' || c == 'c') {
            word[strlen(word) - 1] = '\0';
        }
        if (c == 'm') {
            b.missionaries = atoi(word);
        } else if (c == 'c') {
            b.cannibals = atoi(word);
        }
        word = strtok(NULL, " ");
    }
    return b;
}


void add_child_to_node(Node *n, GameState g, uint32_t hash_target) {
    if (n != NULL) {
        Node *new_node = calloc(sizeof(Node), 1);
        new_node->game_state = g;
        new_node->parent = n;

        if (hash(&g) == hash_target) {
            on_complete(new_node);
        }
        for (size_t i = 0; i < 5; i++) {
            if (n->children[i] == NULL) {
                n->children[i] = new_node;
                gen_child_gamestates(n->children[i], hash_target);
                return;
            }
        }
    }
}


void free_tree(Node *n) {
    if (n != NULL) {
        for (size_t i = 0; i < 5; i++) {
            Node *child = n->children[i];
            if (child != NULL) {
                free_tree(child);
            }
        }
        free(n);
    }
}

void on_complete(Node *node) {
    done = true;
    size_t i = 0;
    Node **answers_array, *current_node;
    answers_array = calloc(sizeof(size_t), 30);
    current_node = node;

    do {
        answers_array[i] = current_node;
        current_node = current_node->parent;
        i++;
    } while (current_node != NULL);

    print_answers_array(answers_array, i);

}

void print_answers_array(Node **answers_array, size_t i) {
    puts("Result path:");
    for (size_t j = 0; j < i; j++) {
        printf("%zu: ", j);
        print(&answers_array[j]->game_state);
    }

}

Node *get_root(Node *n) {
    Node *t = n;
    while (t->parent != NULL) {
        t = t->parent;
    }
    return t;
}

uint32_t hash(GameState *g) {

    if (g != NULL) {
        return g->north.raft * 100000 + g->north.missionaries * 10000 + g->south.missionaries * 1000 +
               g->north.cannibals * 100 + g->north.cannibals * 10 + g->south.raft;
    } else { return 0; }
}

uint32_t hash_node(Node *n) {
    if (n == NULL)
        return 0;
    return hash(&n->game_state);
}

bool check_parent_hashes(Node *root, uint32_t hash_value, uint32_t hash_target) {
    if (root == NULL) {
        return true;
    }

    uint32_t hash = hash_node(root);
     if (hash_node(root) != hash_value) {
        return check_parent_hashes(root->parent, hash_value, hash_target);
    }

    return false;

}