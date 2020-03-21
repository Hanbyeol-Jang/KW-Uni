#include <stdio.h>

int horizontal(int(*arr)[3]);			// 가로줄이 동일한지 확인 하는 함수 선언
int vertical(int(*arr)[3]);				// 세로줄이 동일한지 확인 하는 함수 선언
int diagonal(int(*arr)[3]);				// 대각선이 동일한지 확인 하는 함수 선언

int main(void)
{
	int i = 0, j = 0;
	int x, y;							// 세로, 가로
	int temp[3][3] = { 0, };			// 입력 받을 배열 선언과 동시에 모든 배열 요소들을 0으로 초기화
	char board[3][3] = { 0, };			// 출력 할 배열 선언과 동시에 모든 배열 요소들을 0으로 초기화
						
	for (j = 0; j < 9; j++)
	{
		i = 0;							// 게임 판 출력
		while (i < 4)					
		{
			printf("  --- --- --- \n");
			
			if (i == 4)
				break;
			if(i!=3)
				printf(" | %c | %c | %c | \n", board[i][0], board[i][1], board[i][2]);

			i++;
		}

/////////////////////////////// Player 1
		if (j % 2 == 0)	
		{
			while (1)
			{
				printf("\n [Player 1] Enter your location [x y]: ");
				scanf_s("%d %d", &x, &y);							// 좌표 입력

				if ((x >= 3 || x < 0) || (y >= 3 || y < 0))			// 입력된 좌표가 범위를 벗어났을 때
				{
					printf("\n Try again. (x>=0 && x<3, y>=0 && y<3) \n");

					i = 0;											// 게임 판 출력
					while (i < 4)
					{
						printf("  --- --- --- \n");

						if (i == 4)
							break;
						if (i != 3)
							printf(" | %c | %c | %c | \n", board[i][0], board[i][1], board[i][2]);

						i++;
					}
					continue;
				}
				if (temp[y][x] != 0)									// 중복된 좌표가 입력됐을 때
				{
					printf("\n Aleady Exist. Try Again. \n");
					i = 0;												// 게임 판 출력
					while (i < 4)
					{
						printf("  --- --- --- \n");

						if (i == 4)
							break;
						if (i != 3)
							printf(" | %c | %c | %c | \n", board[i][0], board[i][1], board[i][2]);

						i++;
					}
					continue;
				}
				break;

			}

			temp[y][x] = 1;						// 입력된 좌표에 1 삽입
			board[y][x] = 'O';					// 같은 위치에 O 삽입
			printf("\n");

			if(horizontal(temp)==1)				// 승리한 경우가 있는지 확인
				break;
			if(vertical(temp)==1)
				break;
			if(diagonal(temp)==1)
				break;
		}

/////////////////////////////// Player 2
		else							
		{
			while (1)
			{
				printf("\n [Player 2] Enter your location [x y]: ");
				scanf_s("%d %d", &x, &y);

				if ((x >= 3 || x < 0) || (y >= 3 || y < 0))			// 입력된 좌표가 범위를 벗어났을 때
				{
					printf("\n Try again. (x>=0 && x<3, y>=0 && y<3) \n");

					i = 0;										// 게임 판 출력
					while (i < 4)
					{
						printf("  --- --- --- \n");

						if (i == 4)
							break;
						if (i != 3)
							printf(" | %c | %c | %c | \n", board[i][0], board[i][1], board[i][2]);

						i++;
					}
					continue;
				}
				if (temp[y][x] != 0)								// 중복된 좌표가 입력됐을 때
				{
					printf("\n Aleady Exist. Try Again. \n");
					i = 0;											// 게임 판 출력
					while (i < 4)
					{
						printf("  --- --- --- \n");

						if (i == 4)
							break;
						if (i != 3)
							printf(" | %c | %c | %c | \n", board[i][0], board[i][1], board[i][2]);

						i++;
					}
					continue;
				}
				break;
			}

			temp[y][x] = 2;						// 입력된 좌표에 2 삽입
			board[y][x] = 'X';					// 같은 위치에 X 삽입
			printf("\n");

			if (horizontal(temp) == 1)			// 승리한 경우가 있는지 확인
				break;
			if (vertical(temp) == 1)
				break;
			if (diagonal(temp) == 1)
				break;
		}
	}

//////////////////////////////////////승부가 결정 났을 때

	if (j != 9)
	{
		if (j % 2 == 0)				// Player 1 이 이겼을 때
		{
			i = 0;												// 게임 판 출력
			while (i < 4)
			{
				printf("  --- --- --- \n");

				if (i == 4)
					break;
				if (i != 3)
					printf(" | %c | %c | %c | \n", board[i][0], board[i][1], board[i][2]);

				i++;
			}
			printf(" Winner is [Player 1] \n\n");
		}
		else if (j % 2 == 1)	// Player 2 이 이겼을 때
		{
			i = 0;										// 게임 판 출력
			while (i < 4)
			{
				printf("  --- --- --- \n");

				if (i == 4)
					break;
				if (i != 3)
					printf(" | %c | %c | %c | \n", board[i][0], board[i][1], board[i][2]);

				i++;
			}
			printf(" Winner is [Player 2] \n\n");
		}
	}
	
	else							// 비겼을 때
	{
		i = 0;											// 게임 판 출력
		while (i < 4)
		{
			printf("  --- --- --- \n");

			if (i == 4)
				break;
			if (i != 3)
				printf(" | %c | %c | %c | \n", board[i][0], board[i][1], board[i][2]);

			i++;
		}
		printf("\n Draw \n\n");
	}

	return 0;
}

int horizontal(int(*arr)[3])
{
	for (int i = 0; i < 3; i++)
	{
		if (arr[i][0] == 0 || arr[i][1] == 0 || arr[i][2] == 0)		// 초기화 된 0 값들은 승부에서 제외
			continue;
		if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2])		// 가로줄 확인
			return 1;												// 모두 동일하면 1 반환
	}
	return 0;														// 동일하지 않으면 0 반환
}

int vertical(int(*arr)[3])
{
	for (int i = 0; i < 3; i++)
	{
		if (arr[0][i] == 0 || arr[1][i] == 0 || arr[2][i] == 0)		// 초기화 된 0 값들은 승부에서 제외
			continue;
		if (arr[0][i]== arr[1][i] && arr[1][i] == arr[2][i])		// 세로 확인
			return 1;												// 모두 동일하면 1 반환
	}
	return 0;														// 동일하지 않으면 0 반환
}

int diagonal(int(*arr)[3])
{
	if (arr[0][0] == 0 || arr[1][1] == 0 || arr[2][2] == 0)			// 초기화 된 0 값들은 승부에서 제외
		return 0;												
	else if (arr[0][2] == 0 || arr[1][1] == 0 || arr[2][0] == 0)
		return 0;

	if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2])			// 대각선 확인
		return 1;													// 모두 동일하면 1 반환
	else if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0])		// 반대방향 대각선 확인
		return 1;													// 모두 동일하면 1 반환

	return 0;														// 동일하지 않으면 0 반환
}
