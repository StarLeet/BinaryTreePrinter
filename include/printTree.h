//
// Created by starlee on 2021/12/8.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CHARARRAY_SIZE 4
#define DEFAULT_APPEND_SIZE 10
#define DEFAULT_NODE_STRING 1000

/*  将此结构体换成用户自己的结构体，但是名字必须是BtNode  */
typedef struct BtNode {
    int Element;
    struct BtNode* parent;
    struct BtNode* left;
    struct BtNode* right;
} BtNode;

/*    打印器初始化
    准备好Append结构体的初始化(树干走向打印)
    开辟好nodeString动态(用于存放所有的打印信息)
*/
void PrinterInit(BtNode* root);
