#include "Huffman.h"

int main()
{
	static char FileName[200];	//源文件名（.txt）
	static int code[256][100];	//哈夫曼编码存储数组
	static int codelength[128];	//ASCii码对应的哈夫曼编码长度
	static char decode_name[200];//解码生成文件名(_decode.txt)
	int text_length = 0;		//源文件长度

	HuffmanTree hf=Huffman(MeasuringFrequency(FileName, text_length));	//根据字符频率生成对应的哈夫曼树
	HuffmanCode(hf, 0, code,codelength);								//根据哈夫曼树从根到叶子方向生成哈夫曼编码
	FileHuffmancodeCreate(FileName,code,codelength);					//根据哈夫曼编码生成.huf文件
	FileHuffmanEncode(hf,decode_name);									//根据哈夫曼树解码并生成解码后文件
	FileComparison(text_length,FileName,decode_name);					//解码前后文件对比

	system("pause");
	return 0;
}