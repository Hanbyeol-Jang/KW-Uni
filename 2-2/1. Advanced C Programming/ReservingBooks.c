#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void PRINT_MENU(void);		// 기본 메뉴 출력 함수

typedef struct Book
{
	char Title[64];		// 책 제목
	char Author[64];	// 저자 이름
	int Price;			// 가격
	int Count;			// 수량
}Book;

int main(void)
{
	FILE* fin = fopen("books.dat", "rt");		// 파일 오픈, 읽기모드
	FILE* fout = fopen("purchase.dat", "w");

	if (!fin)	// 파일이 오픈되지 않았으면
	{
		printf("ERROR : 'books.dat' was NOT OPEN \n\n");		// 에러 출력 후
		return 0;											// 종료
	}

	int i = 0;
	Book books[10] = { 0,};				// 구조체 배열 선언
	Book pur_list[3] = { 0, };
	int list_count = 0;

	while (!feof(fin))					// 파일의 끝까지
	{
		char M[256] = { 0, };
		char* token = NULL;

		fgets(M, 128, fin);				// 한 줄 한 줄 읽기 위해
		
		if (strlen(M) != 0)				
		{
			token = strtok(M, "/\n");			// 문자열 자르기
			strcpy(books[i].Title, token);		// Title 저장
			
			token = strtok(NULL, "/\n");		// 문자열 자르기
			strcpy(books[i].Author, token);		// Author 저장
			
			token = strtok(NULL, "/\n");		// 문자열 자르기
			books[i].Price = atoi(token);		// Price 저장

			token = strtok(NULL, "/\n");		// 문자열 자르기
			books[i].Count = atoi(token);		// Count 저장
		}

		i++;
		
		if (i == 10)			// 구조체 배열 10으로 선언 했으니 index 가 10 이 되면
			break;				// while 문 빠져나감
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
			for (int j = 0; j < 10 ; j++)				// 10개의 책 정보 출력
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

			if (seq_num == 0)			// 0 이면 다시 처음 메뉴
				continue;
			if(seq_num<0 && seq_num>10)			// 범위 초과시 에러 출력
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

			//if (seq_num == 0)			// 0 이면 다시 처음 메뉴
			//	continue;
			//else if (seq_num > 0 && seq_num <= 10)		// 범위 안의 수가 맞으면 그 책 정보 출력, 구매 목록 추가
			//{
			//	printf("=======================================\n");
			//	printf("Purchased\n");
			//	printf("---------------------------------------\n");
			//	printf("Title: %s \n", books[seq_num - 1].Title);
			//	printf("Author: %s \n", books[seq_num - 1].Author);
			//	printf("Price: %d \n", books[seq_num - 1].Price);
			//	// 선택된 횟수 출력
			//	printf("=======================================\n\n");

			//	continue;
			//}
			//else						// 범위 안의 수가 아니면 에러 출력
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
			//// 저자 검색
			////////////////////////////////////

			//int seq_num = 0;
			//printf(" > Input book Seq. [0: go back / other : purchase]:");
			//scanf_s("%d", &seq_num);

			//if (seq_num == 0)			// 0 이면 다시 처음 메뉴
			//	continue;
			//else if (seq_num > 0 && seq_num <= 10)		// 범위 안의 수가 맞으면 그 책 정보 출력, 구매 목록 추가
			//{
			//	printf("=======================================\n");
			//	printf("Purchased\n");
			//	printf("---------------------------------------\n");
			//	printf("Title: %s \n", books[seq_num - 1].Title);
			//	printf("Author: %s \n", books[seq_num - 1].Author);
			//	printf("Price: %d \n", books[seq_num - 1].Price);
			//	// 선택된 횟수 출력
			//	printf("=======================================\n\n");

			//	continue;
			//}
			//else						// 범위 안의 수가 아니면 에러 출력
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
			//// 통합 검색
			////////////////////////////////////

			//int seq_num = 0;
			//printf(" > Input book Seq. [0: go back / other : purchase]:");
			//scanf_s("%d", &seq_num);

			//if (seq_num == 0)			// 0 이면 다시 처음 메뉴
			//	continue;
			//else if (seq_num > 0 && seq_num <= 10)		// 범위 안의 수가 맞으면 그 책 정보 출력, 구매 목록 추가
			//{
			//	printf("=======================================\n");
			//	printf("Purchased\n");
			//	printf("---------------------------------------\n");
			//	printf("Title: %s \n", books[seq_num - 1].Title);
			//	printf("Author: %s \n", books[seq_num - 1].Author);
			//	printf("Price: %d \n", books[seq_num - 1].Price);
			//	// 선택된 횟수 출력
			//	printf("=======================================\n\n");

			//	continue;
			//}
			//else						// 범위 안의 수가 아니면 에러 출력
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
