#include "Huffman.h"

int main()
{
	static char FileName[200];	//Դ�ļ�����.txt��
	static int code[256][100];	//����������洢����
	static int codelength[128];	//ASCii���Ӧ�Ĺ��������볤��
	static char decode_name[200];//���������ļ���(_decode.txt)
	int text_length = 0;		//Դ�ļ�����

	HuffmanTree hf=Huffman(MeasuringFrequency(FileName, text_length));	//�����ַ�Ƶ�����ɶ�Ӧ�Ĺ�������
	HuffmanCode(hf, 0, code,codelength);								//���ݹ��������Ӹ���Ҷ�ӷ������ɹ���������
	FileHuffmancodeCreate(FileName,code,codelength);					//���ݹ�������������.huf�ļ�
	FileHuffmanEncode(hf,decode_name);									//���ݹ����������벢���ɽ�����ļ�
	FileComparison(text_length,FileName,decode_name);					//����ǰ���ļ��Ա�

	system("pause");
	return 0;
}