#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 12500
typedef int ElemType;
typedef struct {
	int i, j;//i���У�j����
	ElemType e;
}Triple;

typedef struct {
	Triple data[MAXSIZE + 1];
	int raw, line, num;//mu, nu, tu,����������������Ԫ�ظ���
}TSMatrix;

//�����������д�����
void input_matrix(TSMatrix *tsm)
{
	int cont, line, raw, value;
	tsm->raw = 0;
	tsm->line = 0;
	tsm->num = 0;
	printf("��������У�\n");
	scanf("%d", &tsm->raw);
	printf("��������У�\n");
	scanf("%d", &tsm->line);
	printf("������ٸ�Ԫ�أ�\n");
	scanf("%d", &tsm->num);
	//tsm->num = num;
	printf("��˳������ÿ��Ԫ�ص��С��С�ֵ��\n");
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


//дһ������������tsm��Ԫ�ذ����к���С����ͬһ�����к���С�����˳������
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
	}//����������ɡ�ע��Ԫ�ظ�����num����һ��raw��ȫ����Ԫ�ء�
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

//��ӡԪ��
void print_element(TSMatrix tsm)
{
	for (int i = 0; i < tsm.num; i++)
	{
		printf("(%d,%d,%d)", tsm.data[i].i, tsm.data[i].j, tsm.data[i].e);
	}
	printf("\n");
}

//��ӡ����
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

//����ת��
void transform_matrix(TSMatrix tsm_pre, TSMatrix *tsm_aft)
{
	tsm_aft->raw = tsm_pre.line;
	tsm_aft->line = tsm_pre.raw;
	tsm_aft->num = tsm_pre.num;

	int *colnum = (int*)malloc((tsm_pre.line+1)*sizeof(int));//�洢ÿ�еķ�0Ԫ�ĸ���
	int *closPos = (int*)malloc((tsm_pre.line+1)*sizeof(int));//�洢ÿ�еĵ�һ������Ԫ���ֵ�λ�� 
	if (tsm_pre.num > 0)
	{
		for (int i = 0; i < tsm_pre.line;i++) //����ʼ��Ϊ0
		{
			colnum[i] = 0;
		}
		for (int i = 0; i < tsm_pre.line; i++) //ɨ��a�������Ԫ�أ����ÿһ���з�0Ԫ�ĸ���
		{
			colnum[tsm_pre.data[i].j]++;
		}
		closPos[0] = 0;//��0�еĵ�һ������Ԫ��һ����data����ĵ�0��λ��

		for (int i = 1; i < tsm_pre.line;i++) //ȷ������a�еĵĵ�i���е�һ������Ԫ����b�е�λ��
		{
			closPos[i] = closPos[i - 1] + colnum[i - 1];//��i�е�һ������Ԫ����data�е�λ��������һ�еķ���Ԫ����������һ�е�һ������Ԫ��data�е�λ��
		}
		for (int i = 0; i < tsm_pre.num;i++)
		{
			int k = closPos[tsm_pre.data[i].j]++; //k������a��j���е�һ������Ԫ����b�е�λ��
			tsm_aft->data[k].i = tsm_pre.data[i].j;	//b.getMatrix()[k].setI(a.getMatrix()[i].getJ());
			tsm_aft->data[k].j = tsm_pre.data[i].i;
			tsm_aft->data[k].e = tsm_pre.data[i].e;
			//closPos[tsm_pre.data[i].j]++;//����a��col���е�һ������Ԫ����b�е�λ����ǰ�ƶ�һλ 
		}
	}

}

int main()
{
	TSMatrix tsm_a, tsm_b;
	input_matrix(&tsm_a);
	sort_element(&tsm_a);
	printf("ת��ǰ�ľ����ǣ�\n");
	print_matrix(tsm_a);
	printf("���е�Ԫ��Ϊ��\n");
	print_element(tsm_a);
	transform_matrix(tsm_a, &tsm_b);
	printf("ת�ú�ľ����ǣ�\n");
	print_matrix(tsm_b);
	printf("���е�Ԫ��Ϊ��\n");
	print_element(tsm_b);
	system("pause");
	return 0;
}
