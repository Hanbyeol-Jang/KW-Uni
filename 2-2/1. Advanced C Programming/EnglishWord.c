#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int GetRandNum(int maxValue);
int StringLength(char* str);
int CompareString(char* str1, char* str2);
 
int main(void)
{
	char* kors[] = { "농장","계통","통신","보안","기술","방정식","암호화","복호화", };
	char* engs[] = { "farm","lineage","communication","security","technology","equation","encryption","decryption", };
	int wordCnt = sizeof(kors) / sizeof(char*);
	int i;
	char string[15];					// 입력받을 배열 선언
	
	srand(time(NULL));
	for (i = 0; i < wordCnt; i++)
	{
		int iWord = GetRandNum(wordCnt);

		if (kors[iWord] == NULL)				// 영단어 중복되지 않게
		{
			i--;								// continue 시 for문의 다음 단계로 넘어가 i에 +1이 되므로 -1 해줌
			continue;
		}

		printf("%s: ", kors[iWord]);						// 영어 단어의 뜻 출력
		scanf_s("%s", string, sizeof(string));				// 그 뜻에 맞는 영단어를 입력받아 string에 저장

		if (CompareString(string, engs[iWord]) == 0)		// 영단어와 뜻이 일치 하면
			printf("Correct!\n\n");							// 출력
		else												// 일치하지않으면
		{
			while (1)
			{
				printf("Incorrect!\n");												// 출력
				printf("(hint1)First letter: %c \n", engs[iWord][0]);				// 힌트 1 : 영단어의 첫번째 글자 출력
				printf("(hint2)Length: %d \n\n", StringLength(engs[iWord]));		// 힌트 2 : 영단어의 길이 출력

				printf("%s: ", kors[iWord]);						// 틀렸으니 다시 영어 단어의 뜻 출력
				scanf_s("%s", string, sizeof(string));				// 다시 영단어를 입력 받음

				if (CompareString(string, engs[iWord]) == 0)		// 영단어와 뜻이 일치 하면
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
	for (i = 0; str[i] != NULL; i++){}		// 문자열의 끝이 NULL 이므로 그 전까지의 i 값이 문자열의 길이 

	return i;
}

int CompareString(char* str1, char* str2)
{
	for (int i = 0; i <= StringLength(str1); i++)		// 문자 하나하나 비교
	{
		if (str1[i] < str2[i])							// str1[i] 이 str2[i] 보다 작으면 
			return -1;									// 음수 반환
		else if(str1[i]>str2[i])						// 크면
			return 1;									// 양수 반환
	}

	if (StringLength(str1) < StringLength(str2))		// 문자열 str1 까지만 같고, str2이 str1 의 NULL 이후로 더 있을 경우를 고려
		return -1;

	return 0;											// 위의 조건이 모두 해당 되지않는 경우, 즉, 두 문자열이 같을 때
}