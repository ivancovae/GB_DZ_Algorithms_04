#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

void solution00();
void solution01();
void solution02();

void menu();

// Задание выполнил Иванцов Александр Евгеньевич
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");
	int select = 0;

	do
	{
		menu();
		scanf("%i", &select);
		switch (select)
		{
		case 1:
			solution00();
			break;
		case 2:
			solution01();
			break;
		case 3:
			solution02();
			break;
		case 0:
			printf("Программа закончила свое выполнение.\n");
			break;
		default:
			printf("Некорректный символ, введите значения из списка меню.\n");
		}
	} while (select != 0);
	system("pause");
	return 0;
}

void menu()
{
	printf("Меню выбора решения задания:\n\n");

	printf("1. Решение задачи 1\n");
	printf("2. Решение задачи 2\n");
	printf("3. Решение задачи 3\n");
	printf("0. Завершение выполнения программы\n");
}

void descriptionTask(char *task)
{
	printf("\n##########################################\n");
	printf("\nУсловие задачи:\n");
	printf(task);
}

void endTask()
{
	printf("\n##########################################\n\n");
}

#define N 8
#define M 8

void Print(int n, int m, int a[N][M])
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			printf("%4d", a[i][j]);
		printf("\n");
	}
}

// Задание 1: *Количество маршрутов с препятствиями. Реализовать чтение массива с препятствием и нахождение количество маршрутов.
void solution00()
{
	descriptionTask("*Количество маршрутов с препятствиями. Реализовать чтение массива с препятствием и нахождение количество маршрутов.\n");
	// Ввод данных
	int A[N][M];
	int Map[N][M] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 0,
		0, 0, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0
	};
	int i, j;
	for (j = 0; j < M; j++)
		A[0][j] = (Map[0][j] == 0) ? 0 : 1; // Первая строка заполнена единицами или нулями в соответствии с картой

	for (i = 1; i < N; i++)
	{
		A[i][0] = (Map[i][0] == 0) ? 0 : 1;
		for (j = 1; j < M; j++)
			A[i][j] = (Map[i][j] == 0) ? (A[i][j - 1] + A[i - 1][j]) : 0;
	}

	// Решение
	printf("Результат: \n");
	Print(N, M, A);

	endTask();
}

// Рекурсивное решение
int lcs_length_rec(char *first_str, char *second_str)
{
	int result;
	if (*first_str == '\0' || *second_str == '\0') result = 0;
	else if (*first_str == *second_str) result = 1 + lcs_length_rec(first_str + 1, second_str + 1);
	else result = max(lcs_length_rec(first_str + 1, second_str), lcs_length_rec(first_str, second_str + 1));
	return result;
}

#define FIRST_SIZE 11
#define SECOND_SIZE 10
char first_str[FIRST_SIZE] = { 'G', 'E', 'E', 'K', 'B', 'R', 'A', 'I', 'N', 'S' };
char second_str[SECOND_SIZE] = { 'G', 'E', 'E', 'K', 'M', 'I', 'N', 'D', 'S'};

int lcs_array[FIRST_SIZE][SECOND_SIZE];

// Инициализация таблицы
void lcs_init()
{
	for (int i = 0; i <= FIRST_SIZE; i++)
		for (int j = 0; j <= SECOND_SIZE; j++)
			lcs_array[i][j] = -1;
}

char *A, *B;

int lcs_subprogram(int i, int j);
// Решение через таблицу
int lcs_length(char *f_str, char *s_str)
{
	A = f_str;
	B = s_str;
	lcs_init();
	return lcs_subprogram(0, 0);
}

int lcs_subprogram(int i, int j)
{
	if (lcs_array[i][j] < 0)
	{
		if (*A == '\0' || *B == '\0') lcs_array[i][j] = 0;
		else if (*A == *B) lcs_array[i][j] = 1 + lcs_length(A + 1, B + 1);
		else lcs_array[i][j] = max(lcs_length(A + 1, B), lcs_length(A, B + 1));
	}
	return lcs_array[i][j];
}

// Итерационное решение (итерационно, быстрее чем рекусивное, не требует инициализации таблицы)
int lcs_length_iteration(char *f_str, char *s_str)
{
	A = f_str;
	B = s_str;

	int i, j;

	for (i = FIRST_SIZE; i >= 0; i--)
	{
		for (j = SECOND_SIZE; j >= 0; j--)
		{
			if (A[i] == '\0' || B[j] == '\0') lcs_array[i][j] = 0;
			else if (A[i] == B[j]) lcs_array[i][j] = 1 + lcs_array[i + 1][j + 1];
			else lcs_array[i][j] = max(lcs_array[i + 1][j], lcs_array[i][j + 1]);
		}
	}
	return lcs_array[0][0];
}

char lcs_str[max(FIRST_SIZE, SECOND_SIZE)];

void printLCS()
{
	int count = 0;
	int i = 0,j = 0;

	while (i < FIRST_SIZE && j < SECOND_SIZE)
	{
		if (first_str[i] == second_str[j])
		{
			lcs_str[count++] = first_str[i];
			i++; j++;
		}
		else if (lcs_array[i + 1][j] >= lcs_array[i][j + 1]) i++;
		else j++;
	}

	for (i = 0; i < count; i++)
	{
		printf("%c", lcs_str[i]);
	}
	printf("\n");
}

void printTable()
{
	for (int i = 0; i < FIRST_SIZE; i++)
	{
		for (int j = 0; j < SECOND_SIZE; j++)
		{
			printf("%i", lcs_array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// Задание 2: Решить задачу о нахождении длины максимальной последовательности с помощью матрицы
void solution01()
{
	descriptionTask("Решить задачу о нахождении длины максимальной последовательности с помощью матрицы\n");
	// Ввод данных

	printf("Первое слово: ");
	for (int i = 0; i < FIRST_SIZE; i++)
	{
		printf("%c", first_str[i]);
	}
	printf("\n");

	printf("Второе слово: ");
	for (int i = 0; i < SECOND_SIZE; i++)
	{
		printf("%c", second_str[i]);
	}
	printf("\n");
	
	// Решение
	printf("Результат: \n");
	int result = lcs_length_iteration(first_str, second_str);
	//printTable();
	printLCS();
	endTask();
}

#define BOARD_ROW 5
#define BOARD_COLUMN 5

int board[BOARD_ROW][BOARD_COLUMN];

// варианты перемещения коня 
const int dx[8] = {		2,	1,	-1,	-2,	-2,	-1,	 1,	 2 };
const int dy[8] = {		1,	2,	 2,	 1,	-1,	-2,	-2,	-1 };

// Выводим доску на экран
void PrintBoard(int a[BOARD_COLUMN][BOARD_ROW])
{
	int i, j;
	for (i = 0; i < BOARD_COLUMN; i++)
	{
		for (j = 0; j < BOARD_ROW; j++)
			printf("%4d", a[i][j]);
		printf("\n");
	}
}
void Zero(int a[BOARD_COLUMN][BOARD_ROW])
{
	int i, j;
	for (i = 0; i < BOARD_COLUMN; i++)
		for (j = 0; j < BOARD_ROW; j++)
			a[i][j] = 0;
}

int nextStep(int x, int y, int step)
{
	board[x][y] = step;
	int res = 0;
	int i;
	for (i = 0; i < 8; i++)
	{
		int x1 = x + dx[i];
		int y1 = y + dy[i];

		if ((x1 >= 0) && (y1 >= 0) && (x1 < BOARD_COLUMN) && (y1 < BOARD_ROW) && (board[x1][y1] == 0))
		{
			if (nextStep(x1, y1, step + 1))
			{
				printf("Point (%2d, %2d) -> (%2d, %2d) - Step %2d -> %2d\n", x, y, x1, y1, step, step + 1);
				return 1;
			}
			else
			{
				board[x1][y1] = 0;
			}
		}
	}
	if (step == BOARD_COLUMN * BOARD_ROW)
	{
		return 1;
	}
	return res;
}

// Задание 3: ***Требуется обойти конём шахматную доску размером NxM, пройдя через все поля доски по одному разу.Здесь алгоритм решения такой же как и в задаче о 8 ферзях.Разница только в проверке
//				положения коня.
void solution02()
{
	descriptionTask("***Требуется обойти конём шахматную доску размером NxM, пройдя через все поля доски по одному разу.Здесь алгоритм решения такой же как и в задаче о 8 ферзях. Разница только в проверке положения коня.\n");
	// Ввод данных
	
	// Решение
	printf("Результат: \n");	
			
	for (int i = 0; i < BOARD_COLUMN; i++)
	{
		for (int j = 0; j < BOARD_ROW; j++)
		{
			int step = 1;
			printf("\n Решение начиная из точки (%4d, %4d):\n", i, j);
			Zero(board);
			int res = nextStep(i, j, step);
			if (res == 1)
			{				
				PrintBoard(board);
				printf("\n");
			}
			else 
			{
				printf("Решение начиная из точки (%4d, %4d) не существует.\n", i, j);
			}
		}
	}

	endTask();
}