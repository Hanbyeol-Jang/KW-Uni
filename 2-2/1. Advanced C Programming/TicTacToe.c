#include <stdio.h>

int horizontal(int(*arr)[3]);			// �������� �������� Ȯ�� �ϴ� �Լ� ����
int vertical(int(*arr)[3]);				// �������� �������� Ȯ�� �ϴ� �Լ� ����
int diagonal(int(*arr)[3]);				// �밢���� �������� Ȯ�� �ϴ� �Լ� ����

int main(void)
{
	int i = 0, j = 0;
	int x, y;							// ����, ����
	int temp[3][3] = { 0, };			// �Է� ���� �迭 ����� ���ÿ� ��� �迭 ��ҵ��� 0���� �ʱ�ȭ
	char board[3][3] = { 0, };			// ��� �� �迭 ����� ���ÿ� ��� �迭 ��ҵ��� 0���� �ʱ�ȭ
						
	for (j = 0; j < 9; j++)
	{
		i = 0;							// ���� �� ���
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
				scanf_s("%d %d", &x, &y);							// ��ǥ �Է�

				if ((x >= 3 || x < 0) || (y >= 3 || y < 0))			// �Էµ� ��ǥ�� ������ ����� ��
				{
					printf("\n Try again. (x>=0 && x<3, y>=0 && y<3) \n");

					i = 0;											// ���� �� ���
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
				if (temp[y][x] != 0)									// �ߺ��� ��ǥ�� �Էµ��� ��
				{
					printf("\n Aleady Exist. Try Again. \n");
					i = 0;												// ���� �� ���
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

			temp[y][x] = 1;						// �Էµ� ��ǥ�� 1 ����
			board[y][x] = 'O';					// ���� ��ġ�� O ����
			printf("\n");

			if(horizontal(temp)==1)				// �¸��� ��찡 �ִ��� Ȯ��
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

				if ((x >= 3 || x < 0) || (y >= 3 || y < 0))			// �Էµ� ��ǥ�� ������ ����� ��
				{
					printf("\n Try again. (x>=0 && x<3, y>=0 && y<3) \n");

					i = 0;										// ���� �� ���
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
				if (temp[y][x] != 0)								// �ߺ��� ��ǥ�� �Էµ��� ��
				{
					printf("\n Aleady Exist. Try Again. \n");
					i = 0;											// ���� �� ���
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

			temp[y][x] = 2;						// �Էµ� ��ǥ�� 2 ����
			board[y][x] = 'X';					// ���� ��ġ�� X ����
			printf("\n");

			if (horizontal(temp) == 1)			// �¸��� ��찡 �ִ��� Ȯ��
				break;
			if (vertical(temp) == 1)
				break;
			if (diagonal(temp) == 1)
				break;
		}
	}

//////////////////////////////////////�ºΰ� ���� ���� ��

	if (j != 9)
	{
		if (j % 2 == 0)				// Player 1 �� �̰��� ��
		{
			i = 0;												// ���� �� ���
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
		else if (j % 2 == 1)	// Player 2 �� �̰��� ��
		{
			i = 0;										// ���� �� ���
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
	
	else							// ����� ��
	{
		i = 0;											// ���� �� ���
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
		if (arr[i][0] == 0 || arr[i][1] == 0 || arr[i][2] == 0)		// �ʱ�ȭ �� 0 ������ �ºο��� ����
			continue;
		if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2])		// ������ Ȯ��
			return 1;												// ��� �����ϸ� 1 ��ȯ
	}
	return 0;														// �������� ������ 0 ��ȯ
}

int vertical(int(*arr)[3])
{
	for (int i = 0; i < 3; i++)
	{
		if (arr[0][i] == 0 || arr[1][i] == 0 || arr[2][i] == 0)		// �ʱ�ȭ �� 0 ������ �ºο��� ����
			continue;
		if (arr[0][i]== arr[1][i] && arr[1][i] == arr[2][i])		// ���� Ȯ��
			return 1;												// ��� �����ϸ� 1 ��ȯ
	}
	return 0;														// �������� ������ 0 ��ȯ
}

int diagonal(int(*arr)[3])
{
	if (arr[0][0] == 0 || arr[1][1] == 0 || arr[2][2] == 0)			// �ʱ�ȭ �� 0 ������ �ºο��� ����
		return 0;												
	else if (arr[0][2] == 0 || arr[1][1] == 0 || arr[2][0] == 0)
		return 0;

	if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2])			// �밢�� Ȯ��
		return 1;													// ��� �����ϸ� 1 ��ȯ
	else if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0])		// �ݴ���� �밢�� Ȯ��
		return 1;													// ��� �����ϸ� 1 ��ȯ

	return 0;														// �������� ������ 0 ��ȯ
}
