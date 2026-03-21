#pragma once
#include <stdio.h>

typedef struct Node Node;

Node* createNode(char* code, char* name);
/*малое левое вращение*/
Node* rotateLeft(Node* a);
/*малое правое вращение*/
Node* rotateRight(Node* a);
/*большое правое вращение*/
Node* bigRotateRight(Node* node);
/*большое левое вращение*/
Node* bigRotateLeft(Node* node);
/*востанавливает баланс узла*/
Node* balance(Node* node);
/*вставка нового элемента*/
Node* insert(Node* node, char* code, char* name);
/*поиск минимального элемента*/
Node* findMin(Node* node);
/*удаление узла по коду*/
Node* deleteNode(Node* node, char* code);
/*поиск узла*/
Node* find(Node* node, char* code);
/*возвращает название аэропорта по коду*/
char* getName(Node* root, char* code);
/*загрузка данных в файл*/
Node* loadFromFile(char* filename, Node* root, int* count);
/*обход дерева*/
void inorderPrint(Node* node, FILE* fout);
/*сохраняет и записывает дерево в файл*/
void saveToFile(Node* root, char* filename);
/*освобождение памяти всего дерева*/
void freeTree(Node* node);
