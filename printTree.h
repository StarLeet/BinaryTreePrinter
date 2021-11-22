#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CHARARRAY_SIZE 4
#define DEFAULT_APPENDSIZE 10
#define DEFAULT_PREFIX 500
#define DEFAULT_NODESTRING 1000

typedef struct Append {
    const char* const charArray[CHARARRAY_SIZE];
    char rightAppend[DEFAULT_APPENDSIZE];
    char leftAppend[DEFAULT_APPENDSIZE];
    char blankAppend[DEFAULT_APPENDSIZE];
    char lineAppend[DEFAULT_APPENDSIZE];
} Append;

typedef struct BtNode {
    int Element;
    struct BtNode* parent;
    struct BtNode* left;
    struct BtNode* right;
} BtNode;

typedef struct PrintInfo {
    char* nodeString;
    long long nodeStringSize;
} PrintInfo;

/*   拼接字符串用的  */
char* repeat(const char* string, char* stringBuilder, int count);

/*   节点信息转字符串(模拟了Java的toString)  */
void toString(BtNode* node, char* getString);

/*  空格填充，让树正确打印出来  */
char* blank(int length, char* stringBuilder);

/*  用堆来存储上一次的拼接信息,减小函数栈帧大小,避免过早出现栈溢出,大大提高打印能力   */
char* saveOldPrefix(char* oldPrefix, int spaceSize);

/*    通过递归一行一行拼接打印信息     */
void printString(BtNode* node, char nodePrefix[], char* leftPrefix,
    char* rightPrefix, PrintInfo* printInfo);

/*    打印器初始化
    准备好Apeend结构体的初始化(树干走向打印)
    开辟好nodeString动态(用于存放所有的打印信息)
*/
void init(BtNode* root, BtNode* left, BtNode* right);