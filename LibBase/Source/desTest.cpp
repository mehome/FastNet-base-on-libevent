#include <iostream>
#include "des.h"
using namespace std;

//int DECRYPT(u_char *key, unsigned char *s, unsigned char *d, unsigned short len);
//int ENCRYPT(u_char *key, unsigned char *s, unsigned char *d, unsigned short len);


int main()
{
	char key[10] = "key";
	char input[20] = "aaa";
	char output[20] = { 0 }; // �������
	char output2[20] = { 0 };  //�������
	
	//���¼��ܣ����output��������˾Ϳ����˰���
	int len = ENCRYPT((u_char *)key, (u_char *)input, (u_char *)output, strlen(input));
	



	//������յ���output�����ܵ�output2�д���
	DECRYPT((u_char *)key, (u_char *)output2, (u_char *)output, len);
	cout << "����:" << output2 << endl;
	

	cin.get();
	return 0;
}