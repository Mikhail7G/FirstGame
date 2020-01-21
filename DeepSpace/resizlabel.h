#ifndef RESIZLABEL_H
#define RESIZLABEL_H
#include <hge.h>
#include <hgesprite.h>

//������ ����� ��������� �������� ��������������� �� ��������� �������� ��� �������� ��������� ��������
extern HGE *hge;

extern hgeSprite *resized_info[];

class dynlabel
{
public:
	float x;//������� �� ������
	float y;
	float table_size;//����� �����
	float font_size;//������ �������(���� 15)

	char newdescr[500];//����� ��������
	int tables;//����� ����� � ��������
	int maxsymbols;//���� ����� �������� � ������

	dynlabel();
	~dynlabel();
	void Render(float x,float y,float table,float font);
	void GetText(char *txt);//��������������� ����� ��������
	char DrawDescr();//���������� ��������������� �����


};


#endif

