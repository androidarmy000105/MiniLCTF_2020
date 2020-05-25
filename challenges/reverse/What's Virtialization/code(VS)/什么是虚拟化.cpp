// What's Virtialization.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int NNA(int a, int b);
int N(int a);
int A(int a, int b);
int O(int a, int b);
int XO(int a, int b);

int add(int a, int b);
int sub(int a, int b);
int mult(int a, int b);

int FNVHash1(char* data);

int num[9] = {1,1,2,3,5,8,13,21,34};
//char flag[] = "MiniLCTF{Wh@t_iS_virti@liz@tiOn}";
char ch[] = "020408";
//char ah[] = "}[^]|{dtKcXxDmYgoNY@D]pTYHp@Yw^O";    //32

char ah1[] = "}[^]|{";    //6     
char ah2[] = "dtKcXxDmYgoNY";     //13     
char ah3[] = "@D]pTYHp@Yw^O";    //13
char input[100];
char temp[100];
int main()
{
	printf("Welcome to MiniLCTF!\n");
	printf("Plz input your flag:");
	scanf_s("%s", input, 100);
	int len = strlen(input);
	int f = 100;
	if ((len*len + num[0] * num[0] >= num[2] * len*num[0]) && (O(len, num[1]) == num[8] - num[0]))    //if(len==6)
	{
		int i = 0;
		int j = 0;

		for (i = 0; i < 6; i++)
		{
			temp[i] = (char)XO((int)input[i], (int)ch[j]);						//temp[i]=(char)(input[i]^ch[j])
			j = (j + num[0]) % (num[1] + num[4]);								//j=(j+1)%6
			if (A((int)temp[i], (int)ah1[i]) != (int)temp[i])					//if(temp[i]!=ah1[i])
			{
				f = A(f, XO(num[3] / 3, num[0]));								//f=0;
			}
		}
		if (O(f, num[8]) != num[7] + num[6])									//if(f!=0)
		{
			for (i = 0; i < 13; i++)
			{
				temp[i + 6] = (char)XO((int)input[i + 6], (int)ch[j]);			//temp[i+6]=(char)(input[i+6]^ch[j])
				j = (j + num[1]) % (num[2] * num[3]);							//j=(j+1)%6
				if (A((int)temp[i + 6], (int)ah2[i]) != (int)temp[i + 6])		//if(temp[i+6]!=ah2[i])
				{
					f = A(f, XO(num[5] / 2 - 3, num[1]));						//f=0;
				}

			}
			if (O(f, num[7]) != num[6] + num[5])								//if(f!=0)
			{
				for (i = 0; i < 13; i++)										
				{
					temp[i + 19] = (char)XO((int)input[i + 19], (int)ch[j]);	//temp[i+19]=(char)(input[i+19]^ch[j])
					j = (j + num[2] / 2) % (num[5] - num[2]);					//j=(j+1)%6
					if (A((int)temp[i + 19], (int)ah3[i]) != (int)temp[i + 19])	//if(temp[i+19]!=ah3[i])
					{
						f = A(f, XO(num[7] / 7, num[3]));						//f=0
					}
				}
				if (N(f) != f - num[0])											//if(f!=0)
				{
					if (FNVHash1(input)== 420679468)
					{
						printf("\nCongratulations! Your flag is right!");
						getchar();
					}
					

				}
			}

		}
	}
	getchar();
	return 0;
}

int NNA(int a, int b)
{
	return ~a & ~b;
}

int N(int a)            //   ~
{
	return NNA(a, a);
}

int A(int a, int b)      // &
{
	return NNA(N(a), N(b));
}

int O(int a, int b)     // |
{
	return NNA(NNA(a, b), NNA(a, b));
}
int XO(int a, int b)    //  ^
{
	return NNA(A(a, b), NNA(a, b));
}

int FNVHash1(char* data)
{
	const int p = 16777619;
	int hash = (int)2166136261L;
	int len = strlen(data);
	for (int i = 0; i<len; i++)
		hash = (hash ^ (int)data[i]) * p;
	hash += hash << 13;
	hash ^= hash >> 7;
	hash += hash << 3;
	hash ^= hash >> 17;
	hash += hash << 5;
	return hash;
}




// 流平整代码（）

/*
int main()
{
	int next = 0;
	int len;
	int f;
	int i, j;
	for (;;)
		switch (next)
		{
		case 0:
			printf("Welcome to MiniLCTF!\n");
			printf("Plz input your flag:");
			next = 1;
			break;
		case 1:
			scanf_s("%s", input, 100);
			len = strlen(input);
			f = 100;
			next = 2;
			break;
		case 2:
			if ((len*len + num[0] * num[0] >= num[2] * len*num[0]) && (O(len, num[1]) == num[8] - num[0]))
				next = 3;
			else next = 23;  //跳转到结尾 
			break;
		case 3:
			i = 0;
			j = 0;
			next = 4;
			break;
		case 4:                    //循环1 
			if (i<6)	next = 5;
			else next = 9;
			break;
		case 5:
			temp[i] = (char)XO((int)input[i], (int)ch[j]);
			j = (j + num[0]) % (num[1] + num[4]);
			next = 6;
			break;
		case 6:
			if (A((int)temp[i], (int)ah1[i]) != (int)temp[i])
				next = 7;
			else next = 8;
			break;
		case 7:
			f = A(f, XO(num[3] / 3, num[0]));
			next = 8;
			break;
		case 8:
			i++;
			next = 4;
			break;
		case 9:
			if (O(f, num[8]) != num[7] + num[6]) { next = 10; i = 0; }
			else next = 23;
			break;
		case 10:
			if (i<13) next = 11;                   //循环2 
			else next = 15;
			break;
		case 11:
			temp[i + 6] = (char)XO((int)input[i + 6], (int)ch[j]);
			j = (j + num[1]) % (num[2] * num[3]);
			next = 12;
			break;
		case 12:
			if (A((int)temp[i + 6], (int)ah2[i]) != (int)temp[i + 6])
				next = 13;
			else next = 14;
			break;
		case 13:
			f = A(f, XO(num[5] / 2 - 3, num[1]));
			next = 14;
			break;
		case 14:
			i++;
			next = 10;
			break;
		case 15:
			if (O(f, num[7]) != num[6] + num[5]) { next = 16; i = 0; }
			else next = 23;
			break;
		case 16:
			if (i<13) next = 17;                                //循环3 
			else next = 21;
			break;
		case 17:
			temp[i + 19] = (char)XO((int)input[i + 19], (int)ch[j]);
			j = (j + num[2] / 2) % (num[5] - num[2]);
			next = 18;
			break;
		case 18:
			if (A((int)temp[i + 19], (int)ah3[i]) != (int)temp[i + 19])
				next = 19;
			else next = 20;
			break;
		case 19:
			f = A(f, XO(num[7] / 7, num[3]));
			next = 20;
			break;
		case 20:
			i++;
			next = 16;
			break;
		case 21:
			if (N(f) != f - num[0])
				next = 22;
			else next = 23;
		case 22:
			printf("\nCongratulations! Your flag is right!");
			getchar();
			next = 23;
		case 23:
			getchar();
			return 0;
		}
}
*/