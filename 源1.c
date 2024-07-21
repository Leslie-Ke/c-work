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
		printf("电脑在一分钟后关机，输入‘大哥’取消\n");
		scanf("%s", input);
		if (strcmp(input, "大哥") == 0)
		{
			system("shutdown -a");
			break;
		}

	}
	return 0;
}