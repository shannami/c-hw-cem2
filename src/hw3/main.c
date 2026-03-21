#include "avl.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("%s файл базы\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];
    Node* root = NULL;
    int count = 0;

    root = loadFromFile(filename, root, &count);

    char line[300];
    while (1) {
        if (!fgets(line, sizeof(line), stdin))
            break;

        line[strcspn(line, "\n")] = 0;

        if (strncmp(line, "find ", 5) == 0) {
            char* code = line + 5;
            const char* name = getName(root, code);
            if (name)
                printf("%s - %s\n", code, name);
            else
                printf("Аэропорт с кодом '%s' не найден в базе.\n", code);
        }

        else if (strncmp(line, "add ", 4) == 0) {
            char* arg = line + 4;
            char* code = strtok(arg, ":");
            char* name = strtok(NULL, "");
            if (code && name) {
                root = insert(root, code, name);
                count++;
                printf("Аэропорт '%s' добавлен в базу.\n", code);
            } else {
                printf("Неверный формат команды add. Используйте add XXX:Название\n");
            }
        }

        else if (strncmp(line, "delete ", 7) == 0) {
            char* code = line + 7;
            const char* name = getName(root, code);
            root = delete (root, code);
            if (name)
                count--;
            printf("Аэропорт '%s' удалён в базе.\n", code);
        }

        else if (strcmp(line, "save") == 0) {
            saveToFile(root, filename);
            printf("База сохранена: %d аэропортов.\n", count);
        }

        else if (strcmp(line, "quit") == 0) {
            break;
        }

        else {
            printf("Неизвестная команда.\n");
        }
    }

    freeTree(root);
    return 0;
}