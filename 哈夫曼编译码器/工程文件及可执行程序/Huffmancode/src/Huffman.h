#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define OK 1;
#define ERROR 0;
#define MinData -10		/*���Ŷ�Ԫ�صľ���ֵ���ı�*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

typedef int Status;
//������������ṹ
typedef struct TreeNode* HuffmanTree;
struct TreeNode
{
	int Weight;		//Ȩֵ
	char ch;		//ASCii�ַ�
	HuffmanTree Lchild;
	HuffmanTree Rchild;
};
//����ѽṹ
typedef struct HeapStruct* MinHeap;
struct HeapStruct {
	HuffmanTree* Data;  //�洢��Ԫ�ص�����  �洢ʱ���±�1��ʼ
	int Size;  //�ѵĵ�ǰԪ�صĸ���
	int Capacity;  //�ѵ��������
};

//��ȡ�ļ���ͳ�Ƹ����ַ�����Ƶ��,��Ƶ����ΪȨֵ���ɶ�
MinHeap MeasuringFrequency(char FileName[200],int& text_length);
//�����µĹ�������
HuffmanTree NewHuffmanNode();
//��������ΪMaxSize����С��
MinHeap CreateMinHeap(int MaxSize);
//��Ԫ��item���뵽��С��H��
Status Insert(MinHeap H, HuffmanTree item);
//����С��H��ȡ��ȨֵΪ��С��Ԫ�أ���ɾ��һ�����
HuffmanTree DeleteMin(MinHeap H);
//��H->data[]��Ȩֵ����Ϊ��С��
MinHeap BuildMinHeap(MinHeap H);
//��С�ѹ����������
HuffmanTree Huffman(MinHeap H);
//�����ַ�Huffman����
Status HuffmanCode(HuffmanTree BST, int depth,int code[][100],int codelength[128]);
//����.huf�ļ�
Status FileHuffmancodeCreate(char FileName[200],int code[][100], int codelength[128]);
//��.huf�ļ���������
Status FileHuffmanEncode(HuffmanTree BST, char decode_name[200]);
//�ĵ��Ա�
Status FileComparison(int text_length, char FileName[200], char decode_name[200]);