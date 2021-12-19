#include "printTree.h"
/* 两个结构体不放在头文件的目的：为了对用户隐蔽 */
typedef struct PrintInfo {
    char* nodeString;
    long long nodeStringSize;
} PrintInfo;

typedef struct Append {
    const char* const charArray[CHARARRAY_SIZE];
    char rightAppend[DEFAULT_APPEND_SIZE];
    char leftAppend[DEFAULT_APPEND_SIZE];
    char blankAppend[DEFAULT_APPEND_SIZE];
    char lineAppend[DEFAULT_APPEND_SIZE];
} Append;

Append appendFormat = {{"┌", "─", "└", "│"}, {0}, {0}, {0}, {0}};
char treePrinterFlag = 0; //记录父节点打印选择
char haveChoose = 0;      //控制用户选择只显示一次
char printChoose = 0;     //记录打印位置选择(控制台或者...)

/* 功能性函数群 */
char* repeat(const char* string, char* stringBuilder, int count) {
    if (string == NULL)
        return NULL;

    while (count-- > 0) {
        strcat(stringBuilder, string);
    }
    return stringBuilder;
}

void toString(BtNode* node, char* getString) {
    _itoa(node->Element, getString, 10);
    if (treePrinterFlag == 'Y' || treePrinterFlag == 'y') {
        char tmpArray[5] = {0};
        strcat(getString, "_p_(");
        if (node->parent != NULL) {
            _itoa(node->parent->Element, tmpArray, 10);
            strcat(getString, tmpArray);
        } else {
            strcat(getString, "NULL");
        }
        strcat(getString, ")");
    }
}

char* blank(unsigned int length, char* stringBuilder) {
    if (length < 0)
        return NULL;
    if (length == 0)
        return "";
    for (int i = 0; i < length; i++) {
        strcat(stringBuilder, " ");
    }
    return stringBuilder;
}

char* saveOldPrefix(char* oldPrefix, unsigned int spaceSize) {
    char* space = (char*)calloc(1, spaceSize);
    strcpy(space, oldPrefix);
    return space;
}

void printString(BtNode* node,
                 char nodePrefix[],
                 char* leftPrefix,
                 char* rightPrefix,
                 PrintInfo* printInfo) {
    BtNode* left = node->left;
    BtNode* right = node->right;

    char string[20] = {0};
    toString(node, string);
    unsigned int length = strlen(string);
    if (length % 2 == 0) {
        length--;
    }
    length = (length >> 1);

    unsigned int oldLeftPrefixSize =
        sizeof(char) * (strlen(leftPrefix) + length + 5);
    char* oldLeftPrefix = saveOldPrefix(
        leftPrefix,
        oldLeftPrefixSize); //根据传入参数动态生成数组,无需考虑内存溢出

    unsigned int oldRightPrefixSize =
        sizeof(char) * (strlen(rightPrefix) + length + 5);
    char* oldRightPrefix = saveOldPrefix(
        rightPrefix,
        oldRightPrefixSize); //根据传入参数动态生成数组,无需考虑内存溢出

    unsigned int tmpArraySize = sizeof(char) * (length + 5);
    char* tmpArray = (char*)calloc(1, tmpArraySize);

    if (right != NULL) {
        strcat(
            oldRightPrefix,
            blank(
                length,
                tmpArray)); // oldRightPrefix初始容量永远大于length,无需担心空间不足

        unsigned int newRightPrefixSize =
            sizeof(char) * (oldRightPrefixSize + DEFAULT_APPEND_SIZE);
        char* newRightPrefix = (char*)calloc(1, newRightPrefixSize);
        strcat(newRightPrefix, oldRightPrefix);
        strcat(newRightPrefix, appendFormat.rightAppend);

        char* newRightPrefix1 = (char*)calloc(1, newRightPrefixSize);
        strcat(newRightPrefix1, oldRightPrefix);
        strcat(newRightPrefix1, appendFormat.lineAppend);

        char* newRightPrefix2 = (char*)calloc(1, newRightPrefixSize);
        memset(newRightPrefix2, 0, newRightPrefixSize);
        strcat(newRightPrefix2, oldRightPrefix);
        strcat(newRightPrefix2, appendFormat.blankAppend);

        printString(
            right, newRightPrefix, newRightPrefix1, newRightPrefix2, printInfo);

        free(newRightPrefix);
        newRightPrefix = NULL;
        free(newRightPrefix1);
        newRightPrefix1 = NULL;
        free(newRightPrefix2);
        newRightPrefix2 = NULL;
    }

    unsigned int newNodeStringSize = sizeof(char) * (strlen(nodePrefix) + 25);
    unsigned int nodeStringHave =
        printInfo->nodeStringSize -
        sizeof(char) * (strlen(printInfo->nodeString) + 1);
    if (newNodeStringSize >= nodeStringHave) {
        printInfo->nodeStringSize += newNodeStringSize << 1;
        char* tmpNodeString =
            realloc(printInfo->nodeString, printInfo->nodeStringSize);
        if (tmpNodeString != NULL) {
            printInfo->nodeString = tmpNodeString;
        } else {
            printf("nodeString扩容失败\n");
            exit(-1);
        }
    }
    strcat(printInfo->nodeString, nodePrefix);
    strcat(printInfo->nodeString, string);
    strcat(printInfo->nodeString, "\n");
    memset(tmpArray, 0, tmpArraySize);
    if (left != NULL) {
        strcat(oldLeftPrefix, blank(length, tmpArray));

        unsigned int newLeftPrefixSize =
            sizeof(char) * (oldLeftPrefixSize + DEFAULT_APPEND_SIZE);
        char* newLeftPrefix = (char*)calloc(1, newLeftPrefixSize);
        strcat(newLeftPrefix, oldLeftPrefix);
        strcat(newLeftPrefix, appendFormat.leftAppend);

        char* newLeftPrefix1 = (char*)calloc(1, newLeftPrefixSize);
        strcat(newLeftPrefix1, oldLeftPrefix);
        strcat(newLeftPrefix1, appendFormat.blankAppend);

        char* newLeftPrefix2 = (char*)calloc(1, newLeftPrefixSize);
        strcat(newLeftPrefix2, oldLeftPrefix);
        strcat(newLeftPrefix2, appendFormat.lineAppend);

        printString(
            left, newLeftPrefix, newLeftPrefix1, newLeftPrefix2, printInfo);

        free(newLeftPrefix);
        newLeftPrefix = NULL;
        free(newLeftPrefix1);
        newLeftPrefix1 = NULL;
        free(newLeftPrefix2);
        newLeftPrefix2 = NULL;
    }

    free(oldLeftPrefix);
    oldLeftPrefix = NULL;
    free(oldRightPrefix);
    oldRightPrefix = NULL;
    free(tmpArray);
    tmpArray = NULL;
}

/* 辅助函数群，从PrinterInit()提炼代码，让PrinterInit()更简洁 */
void flushBuffer() {
    int ch = 0;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

void appendFormat_Init() {
    int length = 2;
    char stringBuilder[20] = {0};

    strcat(appendFormat.rightAppend, appendFormat.charArray[0]);
    strcat(appendFormat.rightAppend,
           repeat(appendFormat.charArray[1], stringBuilder, length));

    memset(stringBuilder, 0, sizeof(stringBuilder));
    strcat(appendFormat.leftAppend, appendFormat.charArray[2]);
    strcat(appendFormat.leftAppend,
           repeat(appendFormat.charArray[1], stringBuilder, length));

    memset(stringBuilder, 0, sizeof(stringBuilder));
    strcat(appendFormat.blankAppend, blank(length + 1, stringBuilder));

    memset(stringBuilder, 0, sizeof(stringBuilder));
    strcat(appendFormat.lineAppend, appendFormat.charArray[3]);
    strcat(appendFormat.lineAppend, blank(length, stringBuilder));
}

PrintInfo* printInfo_Init() {
    PrintInfo* printInfo = (PrintInfo*)calloc(1, sizeof(PrintInfo));
    printInfo->nodeStringSize = sizeof(char) * DEFAULT_NODE_STRING;
    printInfo->nodeString = (char*)calloc(1, printInfo->nodeStringSize);
    return printInfo;
}

void PrinterInit(BtNode* root) {
    if (haveChoose == 0) {
        haveChoose = 1;
        appendFormat_Init();

        printf("是否需要打印出各节点的父节点？ (Y/N) > ");
        scanf("%c", &treePrinterFlag);
        flushBuffer();
        printf("是否需要将树打印到d:\\printTree.txt中？(Y/N) > ");
        scanf("%c", &printChoose);
        flushBuffer();
    }
    PrintInfo* printInfo = printInfo_Init();

    printString(root, "", "", "", printInfo);
    if (printChoose == 'Y' || printChoose == 'y') {
        FILE* pFile = fopen("d:\\printTree.txt", "a+");
        if (pFile != NULL) {
            fputs(printInfo->nodeString, pFile);
            fprintf(pFile, "\n\n==========================================\n");
            fclose(pFile);
        }
    } else {
        printf("%s", printInfo->nodeString);
        printf("\n\n==========================================\n");
    }

    free(printInfo->nodeString);
    printInfo->nodeString = NULL;
    free(printInfo);
    printInfo = NULL;
}