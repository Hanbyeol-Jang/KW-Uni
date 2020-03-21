#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int GetRandNum(int maxValue);
int StringLength(char* str);
int CompareString(char* str1, char* str2);
 
int main(void)
{
	char* kors[] = { "����","����","���","����","���","������","��ȣȭ","��ȣȭ", };
	char* engs[] = { "farm","lineage","communication","security","technology","equation","encryption","decryption", };
	int wordCnt = sizeof(kors) / sizeof(char*);
	int i;
	char string[15];					// �Է¹��� �迭 ����
	
	srand(time(NULL));
	for (i = 0; i < wordCnt; i++)
	{
		int iWord = GetRandNum(wordCnt);

		if (kors[iWord] == NULL)				// ���ܾ� �ߺ����� �ʰ�
		{
			i--;								// continue �� for���� ���� �ܰ�� �Ѿ i�� +1�� �ǹǷ� -1 ����
			continue;
		}

		printf("%s: ", kors[iWord]);						// ���� �ܾ��� �� ���
		scanf_s("%s", string, sizeof(string));				// �� �濡 �´� ���ܾ �Է¹޾� string�� ����

		if (CompareString(string, engs[iWord]) == 0)		// ���ܾ�� ���� ��ġ �ϸ�
			printf("Correct!\n\n");							// ���
		else												// ��ġ����������
		{
			while (1)
			{
				printf("Incorrect!\n");												// ���
				printf("(hint1)First letter: %c \n", engs[iWord][0]);				// ��Ʈ 1 : ���ܾ��� ù��° ���� ���
				printf("(hint2)Length: %d \n\n", StringLength(engs[iWord]));		// ��Ʈ 2 : ���ܾ��� ���� ���

				printf("%s: ", kors[iWord]);						// Ʋ������ �ٽ� ���� �ܾ��� �� ���
				scanf_s("%s", string, sizeof(string));				// �ٽ� ���ܾ �Է� ����

				if (CompareString(string, engs[iWord]) == 0)		// ���ܾ�� ���� ��ġ �ϸ�
				{
					printf("Correct!\n\n");
					break;
				}
			}

		}

		kors[iWord] = NULL;
	}
	return 0;
}

int GetRandNum(int maxValue)
{
	return rand() % maxValue;
}

int StringLength(char* str)
{
	int i;
	for (i = 0; str[i] != NULL; i++){}		// ���ڿ��� ���� NULL �̹Ƿ� �� �������� i ���� ���ڿ��� ���� 

	return i;
}

int CompareString(char* str1, char* str2)
{
	for (int i = 0; i <= StringLength(str1); i++)		// ���� �ϳ��ϳ� ��
	{
		if (str1[i] < str2[i])							// str1[i] �� str2[i] ���� ������ 
			return -1;									// ���� ��ȯ
		else if(str1[i]>str2[i])						// ũ��
			return 1;									// ��� ��ȯ
	}

	if (StringLength(str1) < StringLength(str2))		// ���ڿ� str1 ������ ����, str2�� str1 �� NULL ���ķ� �� ���� ��츦 ���
		return -1;

	return 0;											// ���� ������ ��� �ش� �����ʴ� ���, ��, �� ���ڿ��� ���� ��
}