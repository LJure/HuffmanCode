#include "Huffman.h"

Status HuffmanCode(HuffmanTree BST, int depth,int code[][100], int codelength[128])  //depthΪĿǰ���뵽������������ȣ���Σ� 
{
	static int cd[100];		/*��ʱ�洢����������*/
	if (BST)	/*�Ӹ���Ҷ�ӽڵ����*/
	{
		if ((BST->Lchild == NULL) && (BST->Rchild== NULL)) 
		{  //�ҵ���Ҷ���
			if(BST->Weight!=0)
			{
				codelength[BST->ch] = depth;
				printf("�ַ�%c�Ĺ���������Ϊ��", BST->ch);
				for (int i=0; i < depth; i++)
					code[BST->ch][i] = cd[i];
				for (int i=0; i < depth; i++)
					printf("%d", code[BST->ch][i]);
				printf("\n"); 
			}
		}
		else 
		{
			cd[depth] = 0 ;  //���������������Ϊ0 
			HuffmanCode(BST->Lchild, depth + 1, code,codelength);
			cd[depth] = 1 ;  //���������������Ϊ1 
			HuffmanCode(BST->Rchild, depth + 1, code,codelength);
		}
	}
	return OK;
}

MinHeap MeasuringFrequency(char FileName[200],int& text_length)
{
	printf("�������ļ���(��Ҫ�Ӻ�׺��): ");
	scanf_s("%s", FileName,200);
	FILE* fp1 = fopen(FileName, "r");
	FILE* fp2 = fopen(FileName, "r");
	int char_num[128] = { 0 };  //����ASCII����128���ַ�
	int char_number = 0;
	int i, l = 0,n=0;
	unsigned char c;
	HuffmanTree T, BT = NULL;
	//��ʼ���ļ��������������˳�
	if (fp1 == NULL) 
	{
		printf("��ȡ�ļ�ʧ�ܻ��ļ������ڣ������ԣ�\n");
		return ERROR;
	}
	//ͳ���ַ�Ƶ�ʼ��ַ�������
	while (!feof(fp1)) 
	{
		c = fgetc(fp1);
		char_num[c]++;
		text_length++;
	}
	rewind(fp1);
	//ͳ���ַ������ж����ֲ�ͬ�ַ�
	for (i = 0; i < 128; i++) 
	{
		if (char_num[i] != 0)
			char_number++;
	}
	//�������ַ�Ƶ��ΪȨֵ�����ַ�����Ϊ�����Ĺ�������
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
	//������
	printf("�ı����ȣ�%d    �ַ����ࣺ%d\n", text_length, char_number);
	printf("����ASCII�����У��ַ�����Ƶ�����£�\n");
	for (i = 0; i < 128; i++) 
	{
		if (char_num[i] != 0) 
		{
			if (i == 32)
				printf("�ո�%d\n", char_num[i]);
			else if (i == 13)
				printf("�س���%d\n", char_num[i]);
			else if (i == 10)
				printf("���У�%d\n", char_num[i]);
			else
				printf("%c��%d\t\t", i, char_num[i]);
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
	//��.huf�ļ���д�����������
	FILE* fp_souce = fopen(FileName, "r");
	FILE* fp_code = fopen(code_name, "w");
	if (fp_souce == NULL)
	{
		printf("�ļ���ʧ��!!!\n");
		return ERROR;
	}
	while ((ch = fgetc(fp_souce)) != EOF)
	{
		for (int i = 0; i < codelength[ch]; i++)
		{
			fprintf(fp_code, "%d", code[ch][i]);	//��int���͵Ĺ���������д���ļ�
		}
	}
	printf("\n����ɹ�!\n");
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
	printf("��������Ҫ������ļ���(��Ҫ�Ӻ�׺��): ");
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
	//��_decode.txt�ļ���д�����������
	FILE* fp_code = fopen(code_name, "r");
	FILE* fp_decode = fopen(decode_name, "w");
	i = 0;
	while (!feof(fp_code))
	{
		ch = fgetc(fp_code);
		code_length++;
	}
	printf("huf�ļ�����Ϊ��%d\n", code_length);
	rewind(fp_code);
	while (1)
	{
		if (cnt >=code_length)
			break;
		temp = BST;
		while(1)	/*�Ӹ���Ҷ�ӽڵ����*/
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
			cnt++;	//�����ѽ���Ĺ������볤��
			if (cnt >= code_length)
				break;
		}
		if((temp->Lchild==NULL)&&(temp->Rchild==NULL))		//�ҵ�Ҷ�ӽڵ�
			fputc(temp->ch, fp_decode);
	}
	fclose(fp_code);
	fclose(fp_decode);
	printf("\n����ɹ�!\n");
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
	//����ַ����бȽϣ���һ���������һ������������һ���ַ�
	for (i = 0; i < text_length; i++) 
	{
		ch1 = fgetc(source);
		ch2 = fgetc(decode);
		if (ch1 != ch2)
			error_num++;
	}
	percentage = (text_length - error_num) / text_length;
	printf("Դ�ļ��������ļ���ȣ��������Ϊ��%d��������Ϊ��%.2f%%\n", (int)error_num, percentage * 100);
	return OK;
}