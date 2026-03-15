#include "csvPrinter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 30
#define MAX_CELL 30

struct CSVTable {
    char table[MAX_ROWS][MAX_COLS][MAX_CELL];
    int rows;
    int cols;
    int widthCol[MAX_COLS];
};

CSVTable* createTable(void)
{
    CSVTable* ptr = malloc(sizeof(CSVTable));
    if (ptr != NULL) {
        initTable(ptr);
    }
    return ptr;
}

void deleteTable(CSVTable* table)
{
    free(table);
}

void initTable(CSVTable* ptr)
{
    ptr->rows = 0;
    ptr->cols = 0;
    for (int i = 0; i < MAX_COLS; i++)
        ptr->widthCol[i] = 0;
    for (int i = 0; i < MAX_ROWS; i++)
        for (int j = 0; j < MAX_COLS; j++)
            ptr->table[i][j][0] = '\0';
}

int isNumber(char* str)
{
    char* end;
    strtod(str, &end);
    if (*end == '\0' && *str != '\0')
        return 1;
    return 0;
}

void columnWidth(CSVTable* ptr, int col, char* text)
{
    int len = (int)strlen(text);
    if (len > ptr->widthCol[col])
        ptr->widthCol[col] = len;
}

int readTable(CSVTable* ptr)
{
    FILE* fin = fopen("input.csv", "r");
    if (fin == NULL) {
        perror("input.csv");
        return 0;
    }

    char line[1000];
    int row = 0;
    while (fgets(line, sizeof(line), fin) != NULL && row < MAX_ROWS) {
        size_t pos = strcspn(line, "\n");
        if (pos < sizeof(line))
            line[pos] = '\0';
        int col = 0;
        char* token = strtok(line, ",");
        while (token != NULL && col < MAX_COLS) {
            strncpy(ptr->table[row][col], token, MAX_CELL - 1);
            ptr->table[row][col][MAX_CELL - 1] = '\0';
            columnWidth(ptr, col, token);
            token = strtok(NULL, ",");
            col++;
        }

        if (row == 0)
            ptr->cols = col;

        row++;
    }
    ptr->rows = row;

    fclose(fin);
    return 1;
}

void printline(FILE* fout, CSVTable* ptr, char ch)
{
    for (int j = 0; j < ptr->cols; ++j) {
        fprintf(fout, "+");
        for (int k = 0; k < ptr->widthCol[j] + 2; ++k) {
            fputc(ch, fout);
        }
    }
    fprintf(fout, "+\n");
}

void formatCell(char* dest, int width, char* text)
{
    if (isNumber(text))
        sprintf(dest, " %*s ", width, text);
    else
        sprintf(dest, " %-*s ", width, text);
}

int printTable(CSVTable* ptr)
{
    FILE* fout = fopen("output.txt", "w");
    if (fout == NULL) {
        perror("output.txt");
        return 0;
    }

    printline(fout, ptr, '=');

    fprintf(fout, "|");
    for (int col = 0; col < ptr->cols; col++) {
        fprintf(fout, " %-*s ", ptr->widthCol[col], ptr->table[0][col]);
        if (col != ptr->cols - 1)
            fprintf(fout, "|");
    }
    fprintf(fout, "|\n");

    printline(fout, ptr, '=');

    for (int row = 1; row < ptr->rows; row++) {
        fprintf(fout, "|");
        for (int col = 0; col < ptr->cols; col++) {
            char cell[100];
            formatCell(cell, ptr->widthCol[col], ptr->table[row][col]);
            fprintf(fout, "%s", cell);
            fprintf(fout, "|");
        }
        fprintf(fout, "\n");
        printline(fout, ptr, '-');
    }

    fclose(fout);
    return 1;
}
