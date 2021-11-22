# BinaryTreePrinter
二叉树打印器，C语言实现

# 原创，转载请注明此仓库！！！

## 前言

我们在学习二叉树的知识时,不能非常直观的看到我们所要打印的树,此打印器就是为了方便新手学习树而编写的

## 效果图

<img src="https://cdn.jsdelivr.net/gh/StarLeet/BinaryTreePrinter@master/ImageFile/image-20211123005940798.png" alt="image-20211123005940798" style="zoom:80%;" />
<img src="https://cdn.jsdelivr.net/gh/StarLeet/BinaryTreePrinter@master/ImageFile/image-20211123011220787.png" alt="image-20211123011220787" style="zoom:80%;" />

## 构成要素

1. `printTree.h` 在你的main函数(或者需要打印树的.c文件)中包含此头文件,
2. `BtPrinter.c` 在你的源文件下加入此文件

到此，准备工作已经完成

## 使用方法

当你需要打印树的时候调用`PrinterInit(root,root->left,root->right)`;

这也就是说要想让打印器打印出树,必须要让函数知道你的根节点,根节点的左孩子与右孩子

注意:当你的Node结构体中不含有父节点的指针时，在控制台不得选择打印父节点，否则程序会退出。
如果打印格式不正确，可以考虑更换控制台字体，或者将结果保存到txt文本中,用记事本打开查看
