#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void PRINT_MENU(void);		// �⺻ �޴� ��� �Լ�

typedef struct Book
{
	char Title[64];		// å ����
	char Author[64];	// ���� �̸�
	int Price;			// ����
	int Count;			// ����
}Book;

int main(void)
{
	FILE* fin = fopen("books.dat", "rt");		// ���� ����, �б���
	FILE* fout = fopen("purchase.dat", "w");

	if (!fin)	// ������ ���µ��� �ʾ�����
	{
		printf("ERROR : 'books.dat' was NOT OPEN \n\n");		// ���� ��� ��
		return 0;											// ����
	}

	int i = 0;
	Book books[10] = { 0,};				// ����ü �迭 ����
	Book pur_list[3] = { 0, };
	int list_count = 0;

	while (!feof(fin))					// ������ ������
	{
		char M[256] = { 0, };
		char* token = NULL;

		fgets(M, 128, fin);				// �� �� �� �� �б� ����
		
		if (strlen(M) != 0)				
		{
			token = strtok(M, "/\n");			// ���ڿ� �ڸ���
			strcpy(books[i].Title, token);		// Title ����
			
			token = strtok(NULL, "/\n");		// ���ڿ� �ڸ���
			strcpy(books[i].Author, token);		// Author ����
			
			token = strtok(NULL, "/\n");		// ���ڿ� �ڸ���
			books[i].Price = atoi(token);		// Price ����

			token = strtok(NULL, "/\n");		// ���ڿ� �ڸ���
			books[i].Count = atoi(token);		// Count ����
		}

		i++;
		
		if (i == 10)			// ����ü �迭 10���� ���� ������ index �� 10 �� �Ǹ�
			break;				// while �� ��������
	}

	while (1)
	{
		PRINT_MENU();
		int num = 0;
		printf(" > Select menu: ");
		scanf_s("%d", &num);

		if (num == 1)			// show all
		{
			printf("=======================================\n");
			printf("---------------------------------------\n");
			for (int j = 0; j < 10 ; j++)				// 10���� å ���� ���
			{
				printf("Seq.: [%d] \n", j + 1);
				printf("Title: %s \n", books[j].Title);
				printf("Author: %s \n", books[j].Author);
				printf("Price: %d \n", books[j].Price);
				printf("Count: %d \n", books[j].Count);
				if(j<9)
					printf("---------------------------------------\n");
			}
			printf("=======================================\n");
			
			int seq_num = 0;
			printf(" > Input book Seq. [0: go back / other : purchase]:");
			scanf_s("%d", &seq_num);

			if (seq_num == 0)			// 0 �̸� �ٽ� ó�� �޴�
				continue;
			if(seq_num<0 && seq_num>10)			// ���� �ʰ��� ���� ���
				printf("ERROR : INPUT CORRECT NUMBER(1~10) \n\n");

			books[seq_num - 1].Count--;
			if (books[seq_num - 1].Count < 0)
			{
				printf("ERROR : No Stock \n\n");
				continue;
			}

			if (list_count == 0)
			{
				strcpy(pur_list[0].Title, books[seq_num - 1].Title);
				strcpy(pur_list[0].Author, books[seq_num - 1].Author);
				pur_list[0].Price = books[seq_num - 1].Price;
				pur_list[0].Count++;
				list_count++;
				
				printf("=======================================\n");
				printf("Purchased\n");
				printf("---------------------------------------\n");
				printf("Title: %s \n", pur_list[0].Title);
				printf("Author: %s \n", pur_list[0].Author);
				printf("Price: %d \n", pur_list[0].Price);
				printf("Count: %d \n", pur_list[0].Count);
				printf("=======================================\n\n");
				continue;
			}
			else if (list_count == 1)
			{
				if (strcmp(books[seq_num-1].Title,pur_list[0].Title)==0)
				{
					pur_list[0].Count++;
					
					printf("=======================================\n");
					printf("Purchased\n");
					printf("---------------------------------------\n");
					printf("Title: %s \n", pur_list[0].Title);
					printf("Author: %s \n", pur_list[0].Author);
					printf("Price: %d \n", pur_list[0].Price);
					printf("Count: %d \n", pur_list[0].Count);
					printf("=======================================\n\n");
					continue;
				}
				strcpy(pur_list[1].Title, books[seq_num - 1].Title);
				strcpy(pur_list[1].Author, books[seq_num - 1].Author);
				pur_list[1].Price = books[seq_num - 1].Price;
				pur_list[1].Count++;
				list_count++;

				printf("=======================================\n");
				printf("Purchased\n");
				printf("---------------------------------------\n");
				printf("Title: %s \n", pur_list[0].Title);
				printf("Author: %s \n", pur_list[0].Author);
				printf("Price: %d \n", pur_list[0].Price);
				printf("Count: %d \n", pur_list[0].Count);
				printf("---------------------------------------\n\n");
				printf("Title: %s \n", pur_list[1].Title);
				printf("Author: %s \n", pur_list[1].Author);
				printf("Price: %d \n", pur_list[1].Price);
				printf("Count: %d \n", pur_list[1].Count);
				printf("=======================================\n\n");
				continue;
			}
			else if (list_count == 2)
			{
				if (strcmp(books[seq_num - 1].Title, pur_list[0].Title) == 0)
				{
					pur_list[0].Count++;
				
					printf("=======================================\n");
					printf("Purchased\n");
					printf("---------------------------------------\n");
					printf("Title: %s \n", pur_list[0].Title);
					printf("Author: %s \n", pur_list[0].Author);
					printf("Price: %d \n", pur_list[0].Price);
					printf("Count: %d \n", pur_list[0].Count);
					printf("---------------------------------------\n\n");
					printf("Title: %s \n", pur_list[1].Title);
					printf("Author: %s \n", pur_list[1].Author);
					printf("Price: %d \n", pur_list[1].Price);
					printf("Count: %d \n", pur_list[1].Count);
					printf("=======================================\n\n");
					continue;
				}
	
				if (strcmp(books[seq_num - 1].Title, pur_list[1].Title) == 0)
				{
					pur_list[1].Count++;
				
					printf("=======================================\n");
					printf("Purchased\n");
					printf("---------------------------------------\n");
					printf("Title: %s \n", pur_list[0].Title);
					printf("Author: %s \n", pur_list[0].Author);
					printf("Price: %d \n", pur_list[0].Price);
					printf("Count: %d \n", pur_list[0].Count);
					printf("---------------------------------------\n\n");
					printf("Title: %s \n", pur_list[1].Title);
					printf("Author: %s \n", pur_list[1].Author);
					printf("Price: %d \n", pur_list[1].Price);
					printf("Count: %d \n", pur_list[1].Count);
					printf("=======================================\n\n");
					continue;
				}
				strcpy(pur_list[2].Title, books[seq_num - 1].Title);
				strcpy(pur_list[2].Author, books[seq_num - 1].Author);
				pur_list[2].Price = books[seq_num - 1].Price;
				pur_list[2].Count++;
				list_count++;

				printf("=======================================\n");
				printf("Purchased\n");
				printf("---------------------------------------\n");
				printf("Title: %s \n", pur_list[0].Title);
				printf("Author: %s \n", pur_list[0].Author);
				printf("Price: %d \n", pur_list[0].Price);
				printf("Count: %d \n", pur_list[0].Count);
				printf("---------------------------------------\n\n");
				printf("Title: %s \n", pur_list[1].Title);
				printf("Author: %s \n", pur_list[1].Author);
				printf("Price: %d \n", pur_list[1].Price);
				printf("Count: %d \n", pur_list[1].Count);
				printf("---------------------------------------\n\n");
				printf("Title: %s \n", pur_list[2].Title);
				printf("Author: %s \n", pur_list[2].Author);
				printf("Price: %d \n", pur_list[2].Price);
				printf("Count: %d \n", pur_list[2].Count);
				printf("=======================================\n\n");
				continue;
			}
			else
			{
				if (strcmp(books[seq_num - 1].Title, pur_list[0].Title) == 0)
				{
					pur_list[0].Count++;

					printf("=======================================\n");
					printf("Purchased\n");
					printf("---------------------------------------\n");
					printf("Title: %s \n", pur_list[0].Title);
					printf("Author: %s \n", pur_list[0].Author);
					printf("Price: %d \n", pur_list[0].Price);
					printf("Count: %d \n", pur_list[0].Count);
					printf("---------------------------------------\n\n");
					printf("Title: %s \n", pur_list[1].Title);
					printf("Author: %s \n", pur_list[1].Author);
					printf("Price: %d \n", pur_list[1].Price);
					printf("Count: %d \n", pur_list[1].Count);
					printf("---------------------------------------\n\n");
					printf("Title: %s \n", pur_list[2].Title);
					printf("Author: %s \n", pur_list[2].Author);
					printf("Price: %d \n", pur_list[2].Price);
					printf("Count: %d \n", pur_list[2].Count);
					printf("=======================================\n\n");
					continue;
				}

				if (strcmp(books[seq_num - 1].Title, pur_list[1].Title) == 0)
				{
					pur_list[1].Count++;

					printf("=======================================\n");
					printf("Purchased\n");
					printf("---------------------------------------\n");
					printf("Title: %s \n", pur_list[0].Title);
					printf("Author: %s \n", pur_list[0].Author);
					printf("Price: %d \n", pur_list[0].Price);
					printf("Count: %d \n", pur_list[0].Count);
					printf("---------------------------------------\n\n");
					printf("Title: %s \n", pur_list[1].Title);
					printf("Author: %s \n", pur_list[1].Author);
					printf("Price: %d \n", pur_list[1].Price);
					printf("Count: %d \n", pur_list[1].Count);
					printf("---------------------------------------\n\n");
					printf("Title: %s \n", pur_list[2].Title);
					printf("Author: %s \n", pur_list[2].Author);
					printf("Price: %d \n", pur_list[2].Price);
					printf("Count: %d \n", pur_list[2].Count);
					printf("=======================================\n\n");
					continue;
				}
				if (strcmp(books[seq_num - 1].Title, pur_list[2].Title) == 0)
				{
					pur_list[2].Count++;

					printf("=======================================\n");
					printf("Purchased\n");
					printf("---------------------------------------\n");
					printf("Title: %s \n", pur_list[0].Title);
					printf("Author: %s \n", pur_list[0].Author);
					printf("Price: %d \n", pur_list[0].Price);
					printf("Count: %d \n", pur_list[0].Count);
					printf("---------------------------------------\n\n");
					printf("Title: %s \n", pur_list[1].Title);
					printf("Author: %s \n", pur_list[1].Author);
					printf("Price: %d \n", pur_list[1].Price);
					printf("Count: %d \n", pur_list[1].Count);
					printf("---------------------------------------\n\n");
					printf("Title: %s \n", pur_list[2].Title);
					printf("Author: %s \n", pur_list[2].Author);
					printf("Price: %d \n", pur_list[2].Price);
					printf("Count: %d \n", pur_list[2].Count);
					printf("=======================================\n\n");
					continue;
				}
				printf("ERROR : You can purchase 3 kind of books. Try again \n\n");
				continue;
			}
		}
//////////////////////////////////////////////////////////////////////////////////////////
		else if (num == 2)		// search - title
		{
			//char* search_title[100] = { 0, };
			//printf(" > keyword [Title]: ");
			//scanf_s("%s", search_title);
			//printf("=======================================\n");
			//printf("---------------------------------------\n");

			//char* ret;
			//int title_count = 0;
			//for (int a = 0; a < 10; a++)
			//{
			//	ret = strstr(*books[a].Title, search_title);
			//	if (ret != NULL)
			//	{
			//		printf("Seq.: [%d] \n", a + 1);
			//		printf("Title: %s \n", books[a].Title);
			//		printf("Author: %s \n", books[a].Author);
			//		printf("Price: %d \n", books[a].Price);
			//		printf("Count: %d \n", books[a].Count);
			//		if(a<9)
			//			printf("---------------------------------------\n");
			//	}
			//}
			//printf("=======================================\n");

			//int seq_num = 0;
			//printf(" > Input book Seq. [0: go back / other : purchase]:");
			//scanf_s("%d", &seq_num);

			//if (seq_num == 0)			// 0 �̸� �ٽ� ó�� �޴�
			//	continue;
			//else if (seq_num > 0 && seq_num <= 10)		// ���� ���� ���� ������ �� å ���� ���, ���� ��� �߰�
			//{
			//	printf("=======================================\n");
			//	printf("Purchased\n");
			//	printf("---------------------------------------\n");
			//	printf("Title: %s \n", books[seq_num - 1].Title);
			//	printf("Author: %s \n", books[seq_num - 1].Author);
			//	printf("Price: %d \n", books[seq_num - 1].Price);
			//	// ���õ� Ƚ�� ���
			//	printf("=======================================\n\n");

			//	continue;
			//}
			//else						// ���� ���� ���� �ƴϸ� ���� ���
			//{
			//	printf("ERROR : INPUT CORRECT NUMBER \n");
			//	continue;
			//}

		}
		else if( num == 3)		// search - author
		{
			//char search_author[100] = { 0, };
			//printf(" > keyword [Author]: ");
			//scanf_s("%s", search_author);
			//printf("=======================================\n");
			//printf("---------------------------------------\n");
			////////////////////////////////////
			//// ���� �˻�
			////////////////////////////////////

			//int seq_num = 0;
			//printf(" > Input book Seq. [0: go back / other : purchase]:");
			//scanf_s("%d", &seq_num);

			//if (seq_num == 0)			// 0 �̸� �ٽ� ó�� �޴�
			//	continue;
			//else if (seq_num > 0 && seq_num <= 10)		// ���� ���� ���� ������ �� å ���� ���, ���� ��� �߰�
			//{
			//	printf("=======================================\n");
			//	printf("Purchased\n");
			//	printf("---------------------------------------\n");
			//	printf("Title: %s \n", books[seq_num - 1].Title);
			//	printf("Author: %s \n", books[seq_num - 1].Author);
			//	printf("Price: %d \n", books[seq_num - 1].Price);
			//	// ���õ� Ƚ�� ���
			//	printf("=======================================\n\n");

			//	continue;
			//}
			//else						// ���� ���� ���� �ƴϸ� ���� ���
			//{
			//	printf("ERROR : INPUT CORRECT NUMBER \n");
			//	continue;
			//}
		}
		else if (num == 4)		// search - union
		{
			//char search_union[100] = { 0, };
			//printf(" > keyword [Union]: ");
			//scanf_s("%s", search_union);
			//printf("=======================================\n");
			//printf("---------------------------------------\n");
			////////////////////////////////////
			//// ���� �˻�
			////////////////////////////////////

			//int seq_num = 0;
			//printf(" > Input book Seq. [0: go back / other : purchase]:");
			//scanf_s("%d", &seq_num);

			//if (seq_num == 0)			// 0 �̸� �ٽ� ó�� �޴�
			//	continue;
			//else if (seq_num > 0 && seq_num <= 10)		// ���� ���� ���� ������ �� å ���� ���, ���� ��� �߰�
			//{
			//	printf("=======================================\n");
			//	printf("Purchased\n");
			//	printf("---------------------------------------\n");
			//	printf("Title: %s \n", books[seq_num - 1].Title);
			//	printf("Author: %s \n", books[seq_num - 1].Author);
			//	printf("Price: %d \n", books[seq_num - 1].Price);
			//	// ���õ� Ƚ�� ���
			//	printf("=======================================\n\n");

			//	continue;
			//}
			//else						// ���� ���� ���� �ƴϸ� ���� ���
			//{
			//	printf("ERROR : INPUT CORRECT NUMBER \n");
			//	continue;
			//}

		}
		else if (num == 5)		// return the book
		{


		}
		else if (num == 6)		// EXIT
		{
			fclose(fin);
			fclose(fout);
			break;
		}
		else 
		{
			printf("ERROR : INPUT CORRECT NUMBER (1~6) \n");
				continue;
		}
	}

	fin = fopen("books.dat", "w");
	fout = fopen("purchase.dat", "w");

	for (int y = 0; y < list_count; y++)
	{
		fprintf(fout, "%s/", pur_list[y].Title);
		fprintf(fout, "%s/", pur_list[y].Author);
		fprintf(fout, "%d/", pur_list[y].Price);
		fprintf(fout, "%d\n", pur_list[y].Count);
	}
	for (int z = 0; z < 10; z++)
	{
		fprintf(fin, "%s/", books[z].Title);
		fprintf(fin, "%s/", books[z].Author);
		fprintf(fin, "%d/", books[z].Price);
		fprintf(fin, "%d\n", books[z].Count);

	}
	
	fclose(fin);
	fclose(fout);
	return 0;
}

void PRINT_MENU(void)
{
	printf("=======================================\n\n");
	printf("[1] Show all \n");
	printf("[2] Search - title \n");
	printf("[3] Search - author \n");
	printf("[4] Search - union \n");
	printf("[5] return the book \n");
	printf("[6] EXIT \n\n");
	printf("=======================================\n");
}
