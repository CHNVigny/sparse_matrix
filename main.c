#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 12500
typedef int ElemType;
typedef struct {
	int i, j;//i是行，j是列
	ElemType e;
}Triple;

typedef struct {
	Triple data[MAXSIZE + 1];
	int raw, line, num;//mu, nu, tu,行数，列数，非零元素个数
}TSMatrix;

//这个函数用来写入矩阵
void input_matrix(TSMatrix *tsm)
{
	int cont, line, raw, value;
	tsm->raw = 0;
	tsm->line = 0;
	tsm->num = 0;
	printf("输入多少行？\n");
	scanf("%d", &tsm->raw);
	printf("输入多少列？\n");
	scanf("%d", &tsm->line);
	printf("输入多少个元素？\n");
	scanf("%d", &tsm->num);
	//tsm->num = num;
	printf("按顺序输入每个元素的行、列、值：\n");
	for (int i = 0;i < tsm->num;i++)
	{
		scanf("%d", &raw);
		scanf("%d", &line);
		scanf("%d", &value);
		tsm->data[i].i = raw;
		tsm->data[i].j = line;
		tsm->data[i].e = value;
		/*
		if (raw > tsm->raw)
		{
			tsm->raw = raw;
		}
		if (line > tsm->line)
		{
			tsm->line = line;
		}
		*/
	}
	
}


//写一个函数用来给tsm的元素按照行号由小至大，同一行里列号由小至大的顺序排序
void sort_element(TSMatrix *tsm)
{
	int i, j, k;
	Triple tmp;
	for (i = 0; i < tsm->num-1; i++)
	{
		for (j = 0; j< tsm->num - 1 - i; j++)
		{
			if (tsm->data[j].i>tsm->data[j + 1].i)
			{
				tmp = tsm->data[j];
				tsm->data[j] = tsm->data[j+1];
				tsm->data[j + 1] = tmp;
			}
		}
	}//给行排序完成。注意元素个数是num，不一定raw行全都有元素。
	for (i = 0; i < tsm->num - 1; i++)
	{
		for (j = 0; j < tsm->num - 1 - i; j++)
		{
			for (k = 1; k <= tsm->line - 1 - j; k++)
			{
				if (tsm->data[j].i == tsm->data[j + 1].i && tsm->data[j].j > tsm->data[j + 1].j)
				{
					tmp = tsm->data[j];
					tsm->data[j] = tsm->data[j + 1];
					tsm->data[j + 1] = tmp;
				}
			}
		}
	}
}

//打印元素
void print_element(TSMatrix tsm)
{
	for (int i = 0; i < tsm.num; i++)
	{
		printf("(%d,%d,%d)", tsm.data[i].i, tsm.data[i].j, tsm.data[i].e);
	}
	printf("\n");
}

//打印矩阵
void print_matrix(TSMatrix tsm)
{
	int printed = 0;
	for (int i = 0;i < tsm.raw;i++)
	{
		for (int j = 0;j < tsm.line;j++)
		{
			for (int k = 0;k < tsm.num;k++)
			{
				if (tsm.data[k].i == i&&tsm.data[k].j == j)
				{
					printf("%d\t", tsm.data[k].e);
					printed = 1;
					break;
				}
			}
			if (printed == 0)
			{
				printf("0\t");
			}
			else
				printed = 0;
			
		}
		printf("\n");
	}
}

//矩阵转置
void transform_matrix(TSMatrix tsm_pre, TSMatrix *tsm_aft)
{
	tsm_aft->raw = tsm_pre.line;
	tsm_aft->line = tsm_pre.raw;
	tsm_aft->num = tsm_pre.num;

	int *colnum = (int*)malloc((tsm_pre.line+1)*sizeof(int));//存储每列的非0元的个数
	int *closPos = (int*)malloc((tsm_pre.line+1)*sizeof(int));//存储每列的第一个非零元出现的位置 
	if (tsm_pre.num > 0)
	{
		for (int i = 0; i < tsm_pre.line;i++) //都初始化为0
		{
			colnum[i] = 0;
		}
		for (int i = 0; i < tsm_pre.line; i++) //扫描a里的所有元素，求出每一列中非0元的个数
		{
			colnum[tsm_pre.data[i].j]++;
		}
		closPos[0] = 0;//第0列的第一个非零元素一定在data数组的第0个位置

		for (int i = 1; i < tsm_pre.line;i++) //确定矩阵a中的的第i列中第一个非零元素在b中的位置
		{
			closPos[i] = closPos[i - 1] + colnum[i - 1];//第i列第一个非零元素在data中的位置是它上一列的非零元个数加上上一列第一个非零元在data中的位置
		}
		for (int i = 0; i < tsm_pre.num;i++)
		{
			int k = closPos[tsm_pre.data[i].j]++; //k即矩阵a第j列中第一个非零元素在b中的位置
			tsm_aft->data[k].i = tsm_pre.data[i].j;	//b.getMatrix()[k].setI(a.getMatrix()[i].getJ());
			tsm_aft->data[k].j = tsm_pre.data[i].i;
			tsm_aft->data[k].e = tsm_pre.data[i].e;
			//closPos[tsm_pre.data[i].j]++;//矩阵a第col列中第一个非零元素在b中的位置向前移动一位 
		}
	}

}

int main()
{
	TSMatrix tsm_a, tsm_b;
	input_matrix(&tsm_a);
	sort_element(&tsm_a);
	printf("转置前的矩阵是：\n");
	print_matrix(tsm_a);
	printf("其中的元素为：\n");
	print_element(tsm_a);
	transform_matrix(tsm_a, &tsm_b);
	printf("转置后的矩阵是：\n");
	print_matrix(tsm_b);
	printf("其中的元素为：\n");
	print_element(tsm_b);
	system("pause");
	return 0;
}
