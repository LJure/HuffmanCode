#include "Huffman.h"

Status HuffmanCode(HuffmanTree BST, int depth,int code[][100], int codelength[128])  //depth为目前编码到哈夫曼树的深度（层次） 
{
	static int cd[100];		/*临时存储哈夫曼编码*/
	if (BST)	/*从根到叶子节点编码*/
	{
		if ((BST->Lchild == NULL) && (BST->Rchild== NULL)) 
		{  //找到了叶结点
			if(BST->Weight!=0)
			{
				codelength[BST->ch] = depth;
				printf("字符%c的哈夫曼编码为：", BST->ch);
				for (int i=0; i < depth; i++)
					code[BST->ch][i] = cd[i];
				for (int i=0; i < depth; i++)
					printf("%d", code[BST->ch][i]);
				printf("\n"); 
			}
		}
		else 
		{
			cd[depth] = 0 ;  //往左子树方向编码为0 
			HuffmanCode(BST->Lchild, depth + 1, code,codelength);
			cd[depth] = 1 ;  //往右子树方向编码为1 
			HuffmanCode(BST->Rchild, depth + 1, code,codelength);
		}
	}
	return OK;
}

MinHeap MeasuringFrequency(char FileName[200],int& text_length)
{
	printf("请输入文件名(需要加后缀名): ");
	scanf_s("%s", FileName,200);
	FILE* fp1 = fopen(FileName, "r");
	FILE* fp2 = fopen(FileName, "r");
	int char_num[128] = { 0 };  //根据ASCII表，有128个字符
	int char_number = 0;
	int i, l = 0,n=0;
	unsigned char c;
	HuffmanTree T, BT = NULL;
	//初始化文件，若不存在则退出
	if (fp1 == NULL) 
	{
		printf("读取文件失败或文件不存在！请重试！\n");
		return ERROR;
	}
	//统计字符频率及字符串长度
	while (!feof(fp1)) 
	{
		c = fgetc(fp1);
		char_num[c]++;
		text_length++;
	}
	rewind(fp1);
	//统计字符串中有多少种不同字符
	for (i = 0; i < 128; i++) 
	{
		if (char_num[i] != 0)
			char_number++;
	}
	//创建以字符频率为权值、以字符种类为数量的哈夫曼堆
	MinHeap H = CreateMinHeap(2*char_number);
	for (i = 1; i <2*char_number; i++)
	{
		T = NewHuffmanNode();
		T->Weight = 0;
		H->Data[i] = T;
	}
	n = 1;
	for ( i = 0; i <=128; i++)
	{
		if (char_num[i] != 0)
		{
			H->Data[n]->ch = i;
			H->Data[n]->Weight = char_num[i];
			n++;
		}
	}
	H->Size = char_number;
	fclose(fp1);
	//结果输出
	printf("文本长度：%d    字符种类：%d\n", text_length, char_number);
	printf("按照ASCII码排列，字符出现频率如下：\n");
	for (i = 0; i < 128; i++) 
	{
		if (char_num[i] != 0) 
		{
			if (i == 32)
				printf("空格：%d\n", char_num[i]);
			else if (i == 13)
				printf("回车：%d\n", char_num[i]);
			else if (i == 10)
				printf("换行：%d\n", char_num[i]);
			else
				printf("%c：%d\t\t", i, char_num[i]);
			l++;
			if (l % 5 == 0)
				printf("\n");
		}
	}
	printf("\n");
	return H;
}

Status FileHuffmancodeCreate(char FileName[200],int code[][100], int codelength[128])
{
	int ch;
	char code_name[200];
	int i;
	for (i = 0; i < 200; i++)
	{
		code_name[i] = FileName[i];
		if (code_name[i] == '.')
			break;
	}
	code_name[i++] = '_';
	code_name[i++] = 'c';
	code_name[i++] = 'o';
	code_name[i++] = 'd';
	code_name[i++] = 'e';
	code_name[i++] = '.';
	code_name[i++] = 'h';
	code_name[i++] = 'u';
	code_name[i++] = 'f';
	code_name[i++] = '\0';
	//向.huf文件中写入编码后的数据
	FILE* fp_souce = fopen(FileName, "r");
	FILE* fp_code = fopen(code_name, "w");
	if (fp_souce == NULL)
	{
		printf("文件打开失败!!!\n");
		return ERROR;
	}
	while ((ch = fgetc(fp_souce)) != EOF)
	{
		for (int i = 0; i < codelength[ch]; i++)
		{
			fprintf(fp_code, "%d", code[ch][i]);	//将int类型的哈夫曼编码写入文件
		}
	}
	printf("\n编译成功!\n");
	fclose(fp_souce);
	fclose(fp_code);
	return OK;
}

Status FileHuffmanEncode(HuffmanTree BST, char decode_name[200])
{
	char ch;
	int i,code_length = 0;
	volatile int cnt = 0;
	char code_name[200];
	HuffmanTree temp;
	printf("请输入想要译码的文件名(需要加后缀名): ");
	scanf_s("%s", code_name,200);
	for (i = 0; i < 200; i++)
	{
		decode_name[i] = code_name[i];
		if (code_name[i] == '_')
		{
			i++;
			break;
		}
	}
	decode_name[i++] = 'd';
	decode_name[i++] = 'e';
	decode_name[i++] = 'c';
	decode_name[i++] = 'o';
	decode_name[i++] = 'd';
	decode_name[i++] = 'e';
	decode_name[i++] = '.';
	decode_name[i++] = 't';
	decode_name[i++] = 'x';
	decode_name[i++] = 't';
	decode_name[i++] = '\0';
	//向_decode.txt文件中写入解码后的数据
	FILE* fp_code = fopen(code_name, "r");
	FILE* fp_decode = fopen(decode_name, "w");
	i = 0;
	while (!feof(fp_code))
	{
		ch = fgetc(fp_code);
		code_length++;
	}
	printf("huf文件长度为：%d\n", code_length);
	rewind(fp_code);
	while (1)
	{
		if (cnt >=code_length)
			break;
		temp = BST;
		while(1)	/*从根到叶子节点解码*/
		{
			if ((temp->Lchild==NULL) && (temp->Rchild==NULL))
				break;
			ch = fgetc(fp_code);
			if (ch == '0')
			{
				temp = temp->Lchild;
			}
			else
			{
				temp = temp->Rchild;
			}
			cnt++;	//计数已解码的哈夫曼码长度
			if (cnt >= code_length)
				break;
		}
		if((temp->Lchild==NULL)&&(temp->Rchild==NULL))		//找到叶子节点
			fputc(temp->ch, fp_decode);
	}
	fclose(fp_code);
	fclose(fp_decode);
	printf("\n译码成功!\n");
	free(BST);
	return OK;
}

Status FileComparison(int text_length, char FileName[200],char decode_name[200])
{
	int i;
	char ch1, ch2;
	float error_num = 0.0, percentage = 0.0;
	FILE* source = fopen(FileName, "r");
	FILE* decode = fopen(decode_name, "r");
	//逐个字符进行比较，不一样则计数，一样则跳过看下一个字符
	for (i = 0; i < text_length; i++) 
	{
		ch1 = fgetc(source);
		ch2 = fgetc(decode);
		if (ch1 != ch2)
			error_num++;
	}
	percentage = (text_length - error_num) / text_length;
	printf("源文件与译码文件相比，错误个数为：%d，相似率为：%.2f%%\n", (int)error_num, percentage * 100);
	return OK;
}