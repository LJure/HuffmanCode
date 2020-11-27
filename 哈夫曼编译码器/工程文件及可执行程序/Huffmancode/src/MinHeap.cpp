#include "Huffman.h"

HuffmanTree Huffman(MinHeap H)
{/*����H->Size��Ȩֵ�Ѿ�����H->data[]->Weight��*/
	int i, num;
	HuffmanTree T;
	BuildMinHeap(H);  //��H->data[]��Ȩֵ����Ϊ��С��
	/*�˴����뽫H->Size��ֵ����num,��Ϊ������DeleteMin()�� Insert()������ı�H->Size��ֵ*/
	num = H->Size;
	for (i = 1; i < num; i++) 
	{  //�� H->Size-1�κϲ�   //�˴��̿��������⣡
		T = NewHuffmanNode();  //����һ���µĸ���� 
		T->Lchild = DeleteMin(H);  //����С����ɾ��һ���ڵ㣬��Ϊ��T�����ӽ��
		T->Rchild= DeleteMin(H);  //����С����ɾ��һ���ڵ㣬��Ϊ��T�����ӽ�� 
		T->Weight = T->Lchild->Weight + T->Rchild->Weight;  //������Ȩֵ 
		Insert(H, T);  //����T���뵽��С�� 
	}
	T = DeleteMin(H);
	return T;
}

HuffmanTree NewHuffmanNode()
{
	HuffmanTree BST = (HuffmanTree)malloc(sizeof(TreeNode)); 
	BST->Weight = 0;
	BST->Lchild= BST->Rchild= NULL;
	return BST;
}

MinHeap CreateMinHeap(int MaxSize)
{  /*��������ΪMaxSize����С��*/
	MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));
	H->Data = (HuffmanTree*)malloc((MaxSize + 1) * sizeof(HuffmanTree));
	H->Size = 0;
	H->Capacity = MaxSize;
	HuffmanTree T = NewHuffmanNode();
	T->Weight = MinData;  /*�����ڱ�-ΪС�ڶ������п���Ԫ��Ȩֵ��ֵ�������Ժ�������*/
	T->ch = '\0';
	H->Data[0] = T;
	return H;
}

//���������ڵ�
bool  IsFull(MinHeap H)
{
	return (H->Size == H->Capacity);
}

bool IsEmpty(MinHeap H)
{
	return (H->Size == 0);
}

Status Insert(MinHeap H, HuffmanTree item)
{        //��Ԫ��item���뵽��С��H��
	int i;
	if (IsFull(H)) 
	{
		printf("��С������\n");
		return ERROR;
	}
	i = ++H->Size;  //iָ��������е����һ��Ԫ�ص�λ��
	for (; H->Data[i / 2]->Weight > item->Weight; i /= 2)  //���ڱ����������о����� i>1
		H->Data[i] = H->Data[i / 2];  //���¹��˽��
	H->Data[i] = item;   //��item����
	return OK;
}

HuffmanTree DeleteMin(MinHeap H)
{/*����С��H��ȡ��ȨֵΪ��С��Ԫ�أ���ɾ��һ�����*/
	int parent, child;
	HuffmanTree MinItem, temp = NULL;
	if (IsEmpty(H)) 
	{
		printf("��С��Ϊ��\n");
		return NULL;
	}
	MinItem = H->Data[1];  //ȡ�������-��С��Ԫ��-��¼����
	//����С���е����һ��Ԫ�شӸ���㿪ʼ���Ϲ����²���
	temp = H->Data[H->Size--];  //��С�������һ��Ԫ�أ���ʱ������Ϊ�����˸����
	for (parent = 1; parent * 2 <= H->Size; parent = child) 
	{
		child = parent * 2;
		if ((child != H->Size) && (H->Data[child]->Weight > H->Data[child + 1]->Weight)) 
		{
			/*���Ҷ��ӣ����������Ȩֵ�����Ҷ���*/
			child++; //childָ�����Ҷ����н�С��
		}
		if (temp->Weight > H->Data[child]->Weight) 
		{
			H->Data[parent] = H->Data[child];  //���Ϲ��˽��-temp���λ�����Ƶ�childλ��
		}
		else 
		{
			break;  //�ҵ��˺��ʵ�λ��
		}
	}
	H->Data[parent] = temp;  //temp��ŵ��˴�
	return MinItem;
}



MinHeap BuildMinHeap(MinHeap H)
{
	int i, parent, child;
	HuffmanTree temp;
	for (i = H->Size / 2; i > 0; i--) 
	{  //�����һ������㿪ʼ��ֱ�������
		temp = H->Data[i];
		for (parent = i; parent * 2 <= H->Size; parent = child)
		{
			/*���¹���*/
			child = parent * 2;
			if ((child != H->Size) && (H->Data[child]->Weight > H->Data[child + 1]->Weight)) 
			{/*���Ҷ��ӣ����������Ȩֵ�����Ҷ���*/
				child++; //childָ�����Ҷ����н�С��
			}
			if (temp->Weight > H->Data[child]->Weight) 
			{
				H->Data[parent] = H->Data[child];  //���Ϲ��˽��-temp���λ�����Ƶ�childλ��
			}
			else 
			{
				break;  //�ҵ��˺��ʵ�λ��
			}
		}/*�����ڲ�forѭ������H->data[i]Ϊ���������ĵ���*/
		H->Data[parent] = temp;  //temp��ŵ��˴�  
	}
	return H;
}