#include "Huffman.h"

HuffmanTree Huffman(MinHeap H)
{/*假设H->Size个权值已经存在H->data[]->Weight里*/
	int i, num;
	HuffmanTree T;
	BuildMinHeap(H);  //将H->data[]按权值调整为最小堆
	/*此处必须将H->Size的值交给num,因为后面做DeleteMin()和 Insert()函数会改变H->Size的值*/
	num = H->Size;
	for (i = 1; i < num; i++) 
	{  //做 H->Size-1次合并   //此处教科书有问题！
		T = NewHuffmanNode();  //建立一个新的根结点 
		T->Lchild = DeleteMin(H);  //从最小堆中删除一个节点，作为新T的左子结点
		T->Rchild= DeleteMin(H);  //从最小堆中删除一个节点，作为新T的右子结点 
		T->Weight = T->Lchild->Weight + T->Rchild->Weight;  //计算新权值 
		Insert(H, T);  //将新T插入到最小堆 
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
{  /*创建容量为MaxSize的最小堆*/
	MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));
	H->Data = (HuffmanTree*)malloc((MaxSize + 1) * sizeof(HuffmanTree));
	H->Size = 0;
	H->Capacity = MaxSize;
	HuffmanTree T = NewHuffmanNode();
	T->Weight = MinData;  /*定义哨兵-为小于堆中所有可能元素权值的值，便于以后更快操作*/
	T->ch = '\0';
	H->Data[0] = T;
	return H;
}

//插入新增节点
bool  IsFull(MinHeap H)
{
	return (H->Size == H->Capacity);
}

bool IsEmpty(MinHeap H)
{
	return (H->Size == 0);
}

Status Insert(MinHeap H, HuffmanTree item)
{        //将元素item插入到最小堆H中
	int i;
	if (IsFull(H)) 
	{
		printf("最小堆已满\n");
		return ERROR;
	}
	i = ++H->Size;  //i指向插入后堆中的最后一个元素的位置
	for (; H->Data[i / 2]->Weight > item->Weight; i /= 2)  //无哨兵，则增加判决条件 i>1
		H->Data[i] = H->Data[i / 2];  //向下过滤结点
	H->Data[i] = item;   //将item插入
	return OK;
}

HuffmanTree DeleteMin(MinHeap H)
{/*从最小堆H中取出权值为最小的元素，并删除一个结点*/
	int parent, child;
	HuffmanTree MinItem, temp = NULL;
	if (IsEmpty(H)) 
	{
		printf("最小堆为空\n");
		return NULL;
	}
	MinItem = H->Data[1];  //取出根结点-最小的元素-记录下来
	//用最小堆中的最后一个元素从根结点开始向上过滤下层结点
	temp = H->Data[H->Size--];  //最小堆中最后一个元素，暂时将其视为放在了根结点
	for (parent = 1; parent * 2 <= H->Size; parent = child) 
	{
		child = parent * 2;
		if ((child != H->Size) && (H->Data[child]->Weight > H->Data[child + 1]->Weight)) 
		{
			/*有右儿子，并且左儿子权值大于右儿子*/
			child++; //child指向左右儿子中较小者
		}
		if (temp->Weight > H->Data[child]->Weight) 
		{
			H->Data[parent] = H->Data[child];  //向上过滤结点-temp存放位置下移到child位置
		}
		else 
		{
			break;  //找到了合适的位置
		}
	}
	H->Data[parent] = temp;  //temp存放到此处
	return MinItem;
}



MinHeap BuildMinHeap(MinHeap H)
{
	int i, parent, child;
	HuffmanTree temp;
	for (i = H->Size / 2; i > 0; i--) 
	{  //从最后一个父结点开始，直到根结点
		temp = H->Data[i];
		for (parent = i; parent * 2 <= H->Size; parent = child)
		{
			/*向下过滤*/
			child = parent * 2;
			if ((child != H->Size) && (H->Data[child]->Weight > H->Data[child + 1]->Weight)) 
			{/*有右儿子，并且左儿子权值大于右儿子*/
				child++; //child指向左右儿子中较小者
			}
			if (temp->Weight > H->Data[child]->Weight) 
			{
				H->Data[parent] = H->Data[child];  //向上过滤结点-temp存放位置下移到child位置
			}
			else 
			{
				break;  //找到了合适的位置
			}
		}/*结束内部for循环对以H->data[i]为根的子树的调整*/
		H->Data[parent] = temp;  //temp存放到此处  
	}
	return H;
}