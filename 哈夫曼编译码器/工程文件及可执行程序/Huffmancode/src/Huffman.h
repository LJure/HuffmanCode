#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define OK 1;
#define ERROR 0;
#define MinData -10		/*随着堆元素的具体值而改变*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

typedef int Status;
//定义哈夫曼树结构
typedef struct TreeNode* HuffmanTree;
struct TreeNode
{
	int Weight;		//权值
	char ch;		//ASCii字符
	HuffmanTree Lchild;
	HuffmanTree Rchild;
};
//定义堆结构
typedef struct HeapStruct* MinHeap;
struct HeapStruct {
	HuffmanTree* Data;  //存储堆元素的数组  存储时从下标1开始
	int Size;  //堆的当前元素的个数
	int Capacity;  //堆的最大容量
};

//读取文件，统计各个字符出现频率,将频率作为权值生成堆
MinHeap MeasuringFrequency(char FileName[200],int& text_length);
//构造新的哈夫曼树
HuffmanTree NewHuffmanNode();
//创建容量为MaxSize的最小堆
MinHeap CreateMinHeap(int MaxSize);
//将元素item插入到最小堆H中
Status Insert(MinHeap H, HuffmanTree item);
//从最小堆H中取出权值为最小的元素，并删除一个结点
HuffmanTree DeleteMin(MinHeap H);
//将H->data[]按权值调整为最小堆
MinHeap BuildMinHeap(MinHeap H);
//最小堆构造哈夫曼树
HuffmanTree Huffman(MinHeap H);
//各个字符Huffman编码
Status HuffmanCode(HuffmanTree BST, int depth,int code[][100],int codelength[128]);
//生成.huf文件
Status FileHuffmancodeCreate(char FileName[200],int code[][100], int codelength[128]);
//对.huf文件进行译码
Status FileHuffmanEncode(HuffmanTree BST, char decode_name[200]);
//文档对比
Status FileComparison(int text_length, char FileName[200], char decode_name[200]);