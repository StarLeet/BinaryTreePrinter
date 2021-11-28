#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CHARARRAY_SIZE 4
#define DEFAULT_APPENDSIZE 10
#define DEFAULT_PREFIX 500
#define DEFAULT_NODESTRING 1000

 /*  将此结构体换成用户自己的结构体，但是名字必须是BtNode  */
typedef struct BtNode {
    int Element;
    struct BtNode* parent;
    struct BtNode* left;
    struct BtNode* right;
} BtNode;

/*    打印器初始化
    准备好Apeend结构体的初始化(树干走向打印)
    开辟好nodeString动态(用于存放所有的打印信息)
*/
void PrinterInit(BtNode* root);
