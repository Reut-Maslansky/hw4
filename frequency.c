#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_LETTERS ((int)26)
typedef enum {
    FALSE = 0, TRUE = 1
} boolean;

typedef struct Node {
    long unsigned int count;
    struct Node *children[NUM_LETTERS];
    boolean isEndOfWord;
} node;


node *build() {
    node *root = NULL;
    root = (node *) malloc(sizeof(node));
    if (root) {
        root->count = 0;
        root->isEndOfWord = FALSE;
        for (int i = 0; i < NUM_LETTERS; i++)
            root->children[i] = NULL;
    }
    return root;
}

void insert(node *root, char *string) {
    boolean flag = FALSE;
    //lowerCase
    for (char *i = string; i < string + strlen(string); i++) {
        i[0] = tolower(i[0]);
        if ((i[0]) >= 'a' && (i[0]) <= 'z')
            flag = TRUE;
    }
    if (flag) {
        node *n = root;
            int index;
            for (int i = 0; i < strlen(string); i++) {
                if ((string[i]) >= 'a' && (string[i]) <= 'z') {
                    index = (int) (string[i]) - (int) ('a');
                    if (!n->children[index]) {
                        n->children[index] = build();
                    }
                    n = n->children[index];
                }
            }
            n->count++;
            n->isEndOfWord = TRUE;
    }
}

void printTrieUp(node *root, char *str, int level) {

    if (root->isEndOfWord) {
        str[level] = '\0';
        printf("%s\t%lu\n", str, root->count);
    }

    for (int i = 0; i < NUM_LETTERS; i++) {
        if (root->children[i]) {
            str[level] = i + 'a';
            printTrieUp(root->children[i], str, level + 1);
        }
    }
}

void printTrieDown(node *root, char str[], int level) {

    for (int i = NUM_LETTERS - 1; i >= 0; i--) {
        if (root->children[i]) {
                str[level] = i + 'a';
                printTrieDown(root->children[i], str, level + 1);
        }
    }

        if (root->isEndOfWord) {
            str[level] = '\0';
            printf("%s\t%lu\n", str, root->count);
        }
}

void freedom(node *root) {
    for (int i = 0; i < NUM_LETTERS; i++) {
        if (root->children[i]) {
            freedom(root->children[i]);
        }
    }
    free(root);
}

int main(int argc, char **argv) {
    node *root = build();
    char ch;
    char *string = NULL;
    int size;
    while (ch != EOF) {
        size = 0;
        ch = 'x';
        while (ch != ' ' && ch != '\0' && ch != '\n') {
            string = realloc(string, ++size);
            if (string) {
                ch = getchar();
                if (ch == EOF) {
                    break;
                }
                string[size - 1] = ch;
            }
        }

        if (string) {
            insert(root, string);
            free(string);
            string = NULL;
        }
    }
    char *str = (char *) malloc(sizeof(char));
    if (argc == 2) {
        if (*argv[1] == 'r') {
            printTrieDown(root, str, 0);
        }
    } else
        printTrieUp(root, str, 0);

    free(str);
    freedom(root);

    return 0;
}

