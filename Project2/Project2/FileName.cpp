#include <stdio.h>
int arr[10];
void xian(int n)
{
	for (int i = 0; i <= n; i++)
	{
		
			printf("");
		printf("%d", arr[i]);
	}
	printf("\n");
	return;
}
void fun(int i, int j ,int n)
{
	if (j >= n)
		return;
	for(int k=j;k<=n;k++)
	{
		arr[i] = k;
		xian(i);
		fun(i + 1, k + 1, n);
	}
	return;
}
int main(int argc, char const* argv[])
{
	int n;
	scanf_s("%d", &n);
	fun(0, 1, n);

	return 0;
}