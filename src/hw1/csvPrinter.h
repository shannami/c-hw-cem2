#pragma once
#include <stdio.h>

typedef struct CSVTable CSVTable;

CSVTable* createTable(void);
/*освобождение памяти*/
void deleteTable(CSVTable* table);
/*инициализации таблицы*/
void initTable(CSVTable* ptr);
/*чтение входного файла*/
int readTable(CSVTable* ptr);
/*печать таблицы в выходной файл*/
int printTable(CSVTable* ptr);
/*печать разделителя строк в выходной файл*/
void printline(FILE* fout, CSVTable* ptr, char ch);
/*проверка типа данных(число/текст)*/
int isNumber(char* str);
/*вычисление ширины столбца*/
void columnWidth(CSVTable* ptr, int col, char* text);
/*выравнивание(текст-слева, числа-справа)*/
void formatCell(char* dest, int width, char* text);
