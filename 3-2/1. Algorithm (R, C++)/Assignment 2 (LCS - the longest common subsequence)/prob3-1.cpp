#include <iostream>
#include <string>
using namespace std;

int ComputeLength(string x, string y);			// LCS의 길이를 계산하는 함수

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
	cout << "LCS Length: " << ComputeLength(x, y) << endl;	// LCS의 길이 출력
	return 0;
}

int ComputeLength(string x, string y)
{
	int m = 0, n = 0;		// Sequence 의 길이를 넣을 변수 선언 및 초기화
	int i = 1, j = 1;		// Sequence 의 각 요소들을 순차적으로 비교하기 위한 변수
	m = x.length() - 1;		// main 함수에서 공백 문자를 추가했으므로, string 길이에서 -1
	n = y.length() - 1;

	int c[100][100] = { 0, };			// 100 X 100 table, 모든 요소를 0으로 초기화
	
	for (int a = 0; a <= m; a++)
		cout << c[0][a] <<" ";		// 1행 0으로 채움(출력)
	cout << endl;

	for (j = 1; j <= n; j++)		// y 요소 하나씩 비교
	{
		cout << c[j][0] << " ";		// 1열 0으로 채움(출력)
		for (i = 1; i <= m; i++)	// x 요소 하나씩 비교
		{
			if (x[i] == y[j])		// 같은 문자라면,
			{
				c[j][i] = c[j-1][i - 1] + 1;	// 현재 위치에서 행-1, 열-1 값에서 +1 한 후 넣어줌
				cout << c[j][i] << " ";
			}
			else                     // 다른 문자라면, 현재 값의 위 값과 왼쪽 값 중 큰 값을 넣어줌
			{
				if (c[j-1][i] > c[j][i-1])		// 위 값이 왼쪽 값보다 클 때
				{
					c[j][i] = c[j-1][i];			// 위 값(현재 위치에서 행-1 값)을 넣어줌
					cout << c[j][i] << " ";
				}
				else								// 왼쪽 값이 위 값보다 클 때 or 같을 때
				{
					c[j][i] = c[j][i-1];			// 왼쪽 값(현재위치에서 열-1)을 넣어줌
					cout << c[j][i] << " ";
				}
			}
		}
		cout << endl;		// y요소가 다음 문자로 넘어가기전 줄바꿈
	}
	cout << endl;

	return c[n][m];		// LCS의 길이 반환
}
