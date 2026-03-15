#include "csvPrinter.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool testIsNumber(void)
{
    bool result = isNumber("123") && isNumber("17.23") && isNumber("-28");
    return result;
}

bool testIsNotNumber(void)
{
    bool result = !isNumber("-16f") && !isNumber("1a.23") && !isNumber("aaa");
    return result;
}

bool testFormatCellNumber(void)
{
    char testbuf[100];
    formatCell(testbuf, 5, "10");
    return strcmp(testbuf, "    10 ") == 0;
}

bool testFormatCellText(void)
{
    char testbuf[100];
    formatCell(testbuf, 5, "Bob");
    return strcmp(testbuf, " Bob   ") == 0;
}

bool testColumnWidth(void)
{
    char testbuf[100];
    formatCell(testbuf, 5, "Hello");
    return strlen(testbuf) == 7;
}

int main(int argc, char* argv[])
{
    if (argc > 1 && strcmp(argv[1], "--test") == 0) {
        if (!testIsNumber() || !testIsNotNumber() || !testFormatCellNumber() || !testFormatCellText() || !testColumnWidth()) {
            printf("Tests failed\n");
            return 1;
        }
        printf("All tests passed\n");
        return 0;
    }
    return 0;
}
