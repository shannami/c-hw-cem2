#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* code;
    char* name;
    struct Node* leftChild;
    struct Node* rightChild;
    int balance;
} Node;

Node* createNode(char* code, char* name)
{
    Node* node = malloc(sizeof(Node));
    if (node) {
        node->code = malloc(strlen(code) + 1);
        strcpy(node->code, code);
        node->name = malloc(strlen(name) + 1);
        strcpy(node->name, name);
        node->leftChild = NULL;
        node->rightChild = NULL;
        node->balance = 0;
    }
    return node;
}

Node* rotateLeft(Node* a)
{
    Node* b = a->rightChild;
    Node* c = b->leftChild;

    b->leftChild = a;
    a->rightChild = c;

    return b;
}

Node* rotateRight(Node* a)
{
    Node* b = a->leftChild;
    Node* c = b->rightChild;

    b->rightChild = a;
    a->leftChild = c;

    return b;
}

Node* bigRotateRight(Node* node)
{
    node->leftChild = rotateLeft(node->leftChild);
    return rotateRight(node);
}

Node* bigRotateLeft(Node* node)
{
    node->rightChild = rotateRight(node->rightChild);
    return rotateLeft(node);
}

Node* balance(Node* node)
{
    if (node->balance == 2) {
        if (!node->rightChild)
            return node;
        if (node->rightChild->balance >= 0)
            return rotateLeft(node);
        return bigRotateLeft(node);
    }
    if (node->balance == -2) {
        if (!node->leftChild)
            return node;
        if (node->leftChild->balance <= 0)
            return rotateRight(node);
        return bigRotateRight(node);
    }
    return node;
}

Node* insert(Node* node, char* code, char* name)
{
    if (!node) {
        return createNode(code, name);
    }

    int cmp = strcmp(code, node->code);
    if (cmp < 0) {
        node->leftChild = insert(node->leftChild, code, name);
        --node->balance;
    } else if (cmp > 0) {
        node->rightChild = insert(node->rightChild, code, name);
        ++node->balance;
    } else {
        free(node->name);
        node->name = malloc(strlen(name) + 1);
        strcpy(node->name, name);
        return node;
    }
    return balance(node);
}

Node* findMin(Node* node)
{
    if (!node)
        return NULL;
    while (node->leftChild) {
        node = node->leftChild;
    }
    return node;
}

Node* delete (Node* node, char* code)
{
    if (!node)
        return NULL;

    int cmp = strcmp(code, node->code);
    if (cmp < 0) {
        node->leftChild = delete (node->leftChild, code);
        ++node->balance;
    } else if (cmp > 0) {
        node->rightChild = delete (node->rightChild, code);
        --node->balance;
    } else {
        if (node->leftChild == NULL && node->rightChild == NULL) {
            free(node->code);
            free(node->name);
            free(node);
            return NULL;
        }
        if (node->leftChild == NULL) {
            Node* t = node->rightChild;
            free(node->code);
            free(node->name);
            free(node);
            return t;
        }
        if (node->rightChild == NULL) {
            Node* t = node->leftChild;
            free(node->code);
            free(node->name);
            free(node);
            return t;
        }
        Node* min = findMin(node->rightChild);
        free(node->code);
        node->code = malloc(strlen(min->code) + 1);
        strcpy(node->code, min->code);
        free(node->name);
        node->name = malloc(strlen(min->name) + 1);
        strcpy(node->name, min->name);
        node->rightChild = delete (node->rightChild, min->code);
        --node->balance;
    }
    return balance(node);
}

Node* find(Node* node, char* code)
{
    if (!node)
        return NULL;
    int cmp = strcmp(code, node->code);
    if (cmp == 0)
        return node;
    if (cmp < 0)
        return find(node->leftChild, code);
    return find(node->rightChild, code);
}

char* getName(Node* root, char* code)
{
    Node* node = find(root, code);
    if (node)
        return node->name;
    return NULL;
}

Node* loadFromFile(char* filename, Node* root, int* count)
{
    FILE* fin = fopen(filename, "r");
    if (!fin) {
        perror(filename);
        return root;
    }

    char line[500];
    while (fgets(line, sizeof(line), fin)) {
        line[strcspn(line, "\n")] = 0;
        if (line[0] == '\0')
            continue;
        char* code = strtok(line, ":");
        char* name = strtok(NULL, "");
        root = insert(root, code, name);
        (*count)++;
    }

    fclose(fin);
    printf("Загружено %d аэропортов. Система готова к работе.\n", *count);
    return root;
}

void inorderPrint(Node* node, FILE* fout)
{
    if (!node)
        return;
    inorderPrint(node->leftChild, fout);
    fprintf(fout, "%s:%s\n", node->code, node->name);
    inorderPrint(node->rightChild, fout);
}

void saveToFile(Node* root, char* filename)
{
    FILE* fout = fopen(filename, "w");
    if (!fout) {
        perror(filename);
        return;
    }
    inorderPrint(root, fout);
    fclose(fout);
}

void freeTree(Node* node)
{
    if (!node)
        return;
    freeTree(node->leftChild);
    freeTree(node->rightChild);
    free(node->code);
    free(node->name);
    free(node);
}
