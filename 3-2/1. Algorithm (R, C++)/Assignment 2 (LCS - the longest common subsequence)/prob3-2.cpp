#include <iostream>
#include <string>
using namespace std;

string PrintLCS(string x, string y);	// LCS를 출력하는 함수
string Reverse(string LCS);				/* tracing backwards시 string이 반대로 저장되는 것을
										 다시 reverse 시키는 함수*/
int main(void)
{
	string x = "";			// string형 변수 선언 (Sequence 2개)
	string y = "";

	cout << "Enter 1st Sequence:" << endl;
	getline(cin, x);						// 첫 번째 Sequence 입력받아 x 에 저장
	x = " " + x;							// table 가장자리를 0으로 채우기 위해 공백문자 삽입
	cout << "Enter 2nd Sequence:" << endl;
	getline(cin, y);						// 두 번째 Sequence 입력받아 y 에 저장
	y = " " + y;							// 공백문자 삽입

	cout << endl;
	cout << "LCS:" << PrintLCS(x, y) << endl;	// LCS 출력

	return 0;
}

string PrintLCS(string x, string y)
{
	string LCS="";			// LCS를 담을 string 선언
	int m = 0, n = 0;		// Sequence 의 길이를 넣을 변수 선언 및 초기화
	int i = 1, j = 1;		// Sequence 의 각 요소들을 순차적으로 비교하기 위한 변수
	m = x.length() - 1;		// main 함수에서 공백 문자를 추가했으므로, string 길이에서 -1
	n = y.length() - 1;

	int c[100][100] = { 0, };			// 100 X 100 table, 모든 요소를 0으로 초기화

	for (j = 1; j <= n; j++)		// y 요소 하나씩 비교
	{
		for (i = 1; i <= m; i++)	// x 요소 하나씩 비교
		{
			if (x[i] == y[j])		// 같은 문자라면,
			{
				c[j][i] = c[j - 1][i - 1] + 1;	// 현재 위치에서 행-1, 열-1 값에서 +1 한 후 넣어줌
			}
			else                     // 다른 문자라면, 현재 값의 위 값과 왼쪽 값 중 큰 값을 넣어줌
			{
				if (c[j - 1][i] > c[j][i - 1])		// 위 값이 왼쪽 값보다 클 때
				{
					c[j][i] = c[j - 1][i];			// 위 값(현재 위치에서 행-1 값)을 넣어줌
				}
				else								// 왼쪽 값이 위 값보다 클 때 or 같을 때
				{
					c[j][i] = c[j][i - 1];			// 왼쪽 값(현재위치에서 열-1)을 넣어줌
				}
			}
		}
	}
	
	i = m;		// tracing backwards 전 변수 초기화
	j = n;		// : 배열의 끝에서 부터 확인해야 하므로, 배열의 길이를 넣어줌
	
	while (1)			// 2 Sequence의 모든 요소들을 비교하는 Loop
	{
		if (i == 0 || j == 0)			// 모두 확인 했으면 Loop를 빠져나감 
			break;

		if (c[j][i] == c[j][i - 1])		// 현재 값이 왼쪽 값과 같다면
		{
			i--;						// 왼쪽으로 이동
			continue;
		}
		else if (c[j][i] == c[j - 1][i])	// 현재 값이 위 값과 같다면
		{
			j--;							// 위로 이동
			continue;
		}
		else							// 현재 값이 왼쪽 값과도 다르고 위쪽 값과도 다르다
		{								// 즉, 대각선 + 1 한 경우이다
			LCS = LCS + x[i];			// 대각선 + 1 한 경우는 2 Sequence의 요소를 비교시,
			i--;						// 두 문자가 같을 때 이므로, 그 값을 LCS에 넣어준다
			j--;						// 그 후, 대각석으로 이동
			continue;
		}
	}
	LCS = Reverse(LCS);				// tracing backwards 했으므로 string 을 reverse 시킨다

	return LCS;						// 완성된 LCS 반환
}

string Reverse(string LCS)
{
	string temp = "";				// 임시로 사용할 string 선언
	int len = 0;						// string의 길이를 담을 변수 선언
	len = LCS.length()-1;				// 배열의 index는 0부터 시작하므로 길이-1 해줌

	for (int i = 0; i <= len; i++)
	{
		temp = temp + LCS[len - i];		// string의 마지막 문자부터 시작해 차례로 넣어준다
	}

	return temp;				// reverse 된 string 반환
}
