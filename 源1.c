#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	char input[20] = { 0 };
	system("shutdown -s -t 60");
	while (1)
	{
		printf("������һ���Ӻ�ػ������롮��硯ȡ��\n");
		scanf("%s", input);
		if (strcmp(input, "���") == 0)
		{
			system("shutdown -a");
			break;
		}

	}
	return 0;
}