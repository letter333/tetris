#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define ARROW 224
#define LEFT 75
#define RIGHT 77
#define	UP 72
#define	DOWN 80
#define SPACEBAR 32
#define C 99
#define Z 122
#define P 112
#define Enter 13
#define Esc 27
#define BORDER_WIDTH 12
#define BORDER_HEIGHT 24
#define TRUE 1
#define FALSE 0

#pragma comment(lib, "winmm.lib")
#define SOUND_FILE_NAME "C:\\tetris.wav"
#define _CRT_SECURE_NO_WARNINGS


// [��� ����][��� ȸ��][��� ���][��� ���]
int BlockShape[7][4][4][4] = {
	{
		// �� ���
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		}
	},
	{
		// I ��� (�� 3, 3)
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0}
		},
		{
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0}
		}
	},
	{
		// �� Z ��� (�� 2, 3)
		{
			{0, 0, 0, 0},
			{0, 0, 1, 1},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{1, 1, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0}
		}
	},
	{
		// Z ��� (�� 2, 3)
		{
			{0, 0, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 1},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0}
		}
	},
	{
		// �� ���
		{
			{0, 0, 0, 0},
			{0, 0, 0, 1},
			{0, 1, 1, 1},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
		},
		{
			{0, 0, 0, 0},
			{1, 1, 1, 0},
			{1, 0, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 1, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0}
		}
	},
	{
		// �� �� ���
		{
			{0, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 1},
			{0, 0, 0, 1},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 1, 1, 0}
		}
	},
	{
		// T ���
		{
			{0, 1, 0, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{1, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0}

		},
		{
			{0, 1, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0}
		}
	}
};

enum { EMPTY = 0, MBLOCK = 1, OVERLINE = 2, SBLOCK = 3, WALL = 4, FBLOCK = 5 };
int blockX;
int blockY;
int blockRotation = 0;
int blockType;
int board[BORDER_HEIGHT][BORDER_WIDTH];
int flagNewBlock;
int copyBoard[BORDER_HEIGHT][BORDER_WIDTH];
int nextBlockType;
int flagNextBlock;
int speedUp = 0;
int speed = 0;
int score = 0;
int flagCrush;
int shuffleBlock[7];
int cnt;
int clearNum = 0;
int soundOnOff = 0;

FILE* fp = NULL;
int bestScore;


void GotoXY(int, int);
void SetConsole();
void ConsoleSize();
void RemoveCurser();
void RemoveScrollbar();
void TextColor(int);

void StartScreen();
void StopScreen();
void EndScreen();

void ResetGameBoard();
void ResetCopyGameBoard();
void PrintGameBoard();
void OverLineDraw();
void PrintGameBoardAll();
void PrintNextBoard();
void PrintScore();

void Keyboard();
void BlockShuffler();
int BlockSelector();
void NewBlock();
void PrintNextBlock();

int CrushCheck(int, int, int);
void FixBlock();
void LineClean();
void GameOverCheck();
void Ranking();

void Move(int, int, int);
void Drop();


void main() {
	cnt = 7;
	srand(time(NULL));
	SetConsole();

	StartScreen();

	ResetGameBoard();
	ResetCopyGameBoard();
	PrintGameBoard();
	PrintNextBoard();
	PrintScore();

	NewBlock();

	while (1) {
		if (flagNewBlock == 1)
			NewBlock();
		Keyboard();
		Drop();
		OverLineDraw();
		LineClean();
		PrintScore();
		GameOverCheck();
		PrintGameBoard();
		Sleep(150 - speed);
	}
}

// ȭ�� ��ǥ ����
void GotoXY(int x, int y) {
	COORD Pos;
	Pos.X = x * 2;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// �ܼ�â ����
void SetConsole() {
	ConsoleSize();
	RemoveScrollbar();
	RemoveCurser();
}

// �ܼ�â ũ�� ����
void ConsoleSize() {
	system("mode con cols=43 lines=25");
}

// �ܼ�â ��ũ�ѹ� ����
void RemoveScrollbar() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

// Ŀ�� ����
void RemoveCurser() {
	CONSOLE_CURSOR_INFO curinfo = { 0, };
	curinfo.dwSize = 1;
	curinfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}

// ���� �� ����
void TextColor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

// ����ȭ��
void StartScreen() {
	fopen_s(&fp, "Ranking.txt", "a"); // ��ŷ�� ����� �޸����� ������ ����
	fclose(fp);
	fopen_s(&fp, "Ranking.txt", "r"); // bestScore ��¿�
	while (fscanf_s(fp, "%d", &bestScore) == 1);
	fclose(fp);

	TextColor(15);
	GotoXY(0, 5);
	printf("         * * *  T E T R I S  * * *\n\n"); //����ȭ�� ���
	printf("           �� �� ��  : �̵�\n");
	printf("              ��     : ȸ��\n");
	printf("              Z      : ��ȸ��\n");
	printf("            Space    : ����\n");
	printf("              C      : ���� On/Off\n");
	printf("              P      : �Ͻ�����\n");
	printf("             ESC     : ���� ����\n\n");
	printf("             �� Press Enter ��\n\n\n");
	printf("              �ְ��� : %5d\n\n\n\n\n", bestScore);
	printf("  C����̺꿡 tetris.wav�� �ִٸ� C �Է�\n");

	while (1) {
		if (_kbhit()) { // �Է��� ������ ����
			int nkey = _getch();
			if (nkey == Enter) { // Enter�� ����
				system("cls");
				return 0;
			}
			if (nkey == Esc) // Esc�� ����ȭ�� ����
				EndScreen();
			if (nkey == C) { // C�� ���� On/Off
				if (soundOnOff == 0) {
					PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					soundOnOff += 1;
				}
				else {
					PlaySound(NULL, 0, 0);
					soundOnOff = 0;
				}
			}
		}
	}
}

// ����ȭ��
void StopScreen() {
	system("cls");
	TextColor(15);
	GotoXY(6, 12);
	printf("�� ��  ��  ��  �� ��\n"); // ����ȭ�� ���

	while (1) {
		if (_kbhit()) {
			int nkey = _getch();
			if (nkey == C) {
				if (soundOnOff == 0) {
					PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					soundOnOff += 1;
				}
				else {
					PlaySound(NULL, 0, 0);
					soundOnOff = 0;
				}
			}
			if (nkey == P) {
				system("cls");
				PrintGameBoardAll();
				PrintNextBoard();
				PrintScore();

				if (1) { // ���� ��� ���
					if (nextBlockType == 0)
						TextColor(4);
					if (nextBlockType == 1)
						TextColor(2);
					if (nextBlockType == 2)
						TextColor(9);
					if (nextBlockType == 3)
						TextColor(10);
					if (nextBlockType == 4)
						TextColor(11);
					if (nextBlockType == 5)
						TextColor(12);
					if (nextBlockType == 6)
						TextColor(13);

					for (int y = 0; y < 4; y++) {
						for (int x = 0; x < 4; x++) {
							GotoXY(15 + x, 12 + y);
							if (BlockShape[blockType][0][y][x] == 1) {
								printf("  ");
							}
						}
					}
					for (int y = 0; y < 4; y++) {
						for (int x = 0; x < 4; x++) {
							GotoXY(15 + x, 12 + y);
							if (BlockShape[nextBlockType][0][y][x] == 1) {
								printf("��");
							}
						}
					}
				}
				return 0;
			}
		}
	}
}

// ���Ӻ���� �ӽú��尡 ���Ƶ� ���
void PrintGameBoardAll() {
	for (int y = 0; y < BORDER_HEIGHT; y++) {
		for (int x = 0; x < BORDER_WIDTH; x++) {
			board[y][x] = copyBoard[y][x]; // �ӽú����� ���� �־���  
			switch (board[y][x]) {
			case EMPTY: // �ش�ĭ�� �� �����̸�
				GotoXY(x, y);
				printf("  ");
				break;

			case MBLOCK: // �ش�ĭ�� �����̴� ����̸�
				if (blockType == 0)
					TextColor(4);
				if (blockType == 1)
					TextColor(2);
				if (blockType == 2)
					TextColor(9);
				if (blockType == 3)
					TextColor(10);
				if (blockType == 4)
					TextColor(11);
				if (blockType == 5)
					TextColor(12);
				if (blockType == 6)
					TextColor(13);
				GotoXY(x, y);
				printf("��");
				break;

			case OVERLINE: // �ش�ĭ�� ���� ���������̸�
				TextColor(15);
				GotoXY(x, y);
				printf("_ ");
				break;

			case WALL: // �ش�ĭ�� ���̸�
				TextColor(15);
				GotoXY(x, y);
				printf("��");
				break;

			case FBLOCK: // �ش�ĭ�� ������ ����̸�
				TextColor(15);
				GotoXY(x, y);
				printf("��");
				break;
			}
		}
	}
}

// ����ȭ��
void EndScreen() {
	system("cls"); // ȭ�� �ʱ�ȭ
	TextColor(15);
	GotoXY(6, 12);
	printf("�� ��  ��  ��  �� ��"); // ����ȭ�� ���
	GotoXY(1, 23);
	exit(0); // ���α׷� ����
}

// ���Ӻ��� �� �������� �ʱ�ȭ
void ResetGameBoard() {
	for (int y = 0; y < BORDER_HEIGHT; y++) { // ���Ӱ����� �� �������� ����
		for (int x = 0; x < BORDER_WIDTH; x++)
			copyBoard[y][x] = EMPTY;
	}
}

// �ӽú��� �� �� �������� ����
void ResetCopyGameBoard() {
	for (int y = 0; y < BORDER_HEIGHT; y++) {
		for (int x = 0; x < BORDER_WIDTH; x++) {
			copyBoard[y][x] = EMPTY;
		}
	}
	for (int y = 0; y < BORDER_HEIGHT; y++) {
		for (int x = 0; x < BORDER_WIDTH; x++) {
			if (x == 0 || x == BORDER_WIDTH - 1) // ��-�� �� �׸���
				copyBoard[y][x] = WALL;

			if (y == BORDER_HEIGHT - 1) // �ϴ� �� �׸���
				copyBoard[y][x] = WALL;

			if (y == 2 && x != 0 && x != BORDER_WIDTH - 1) // ���� �������� �׸���
				copyBoard[y][x] = OVERLINE;
		}
	}
}

// ���Ӻ��� ���
void PrintGameBoard() {
	for (int y = 0; y < BORDER_HEIGHT; y++) {
		for (int x = 0; x < BORDER_WIDTH; x++) {
			if (copyBoard[y][x] != board[y][x]) { // �ӽú��尡 ���Ӻ���� �ٸ� �κи� ���
				board[y][x] = copyBoard[y][x];
				switch (board[y][x]) {
				case EMPTY: // �ش�ĭ�� �� �����̸�
					GotoXY(x, y);
					printf("  ");
					break;

				case MBLOCK: // �ش�ĭ�� �������̸�
					if (blockType == 0)
						TextColor(4);
					if (blockType == 1)
						TextColor(2);
					if (blockType == 2)
						TextColor(9);
					if (blockType == 3)
						TextColor(10);
					if (blockType == 4)
						TextColor(11);
					if (blockType == 5)
						TextColor(12);
					if (blockType == 6)
						TextColor(13);
					GotoXY(x, y);
					printf("��");
					break;

				case OVERLINE: // �ش�ĭ�� ���������̸�
					TextColor(15);
					GotoXY(x, y);
					printf("_ ");
					break;

				case WALL: // �ش�ĭ�� ���̸�
					TextColor(15);
					GotoXY(x, y);
					printf("��");
					break;

				case FBLOCK: // �ش�ĭ�� ��������̸�
					TextColor(15);
					GotoXY(x, y);
					printf("��");
					break;
				}
			}
		}
	}
}

// �߰����� ���
void PrintNextBoard() {
	TextColor(15);

	for (int x = 0; x < BORDER_WIDTH - 6; x++) {
		GotoXY(14 + x, 11);
		printf("��");
	}
	for (int y = 0; y < BORDER_HEIGHT - 20; y++) {
		GotoXY(13, y + 12);
		printf("��");
	}
	for (int y = 0; y < BORDER_HEIGHT - 20; y++) {
		GotoXY(20, y + 12);
		printf("��");
	}
	for (int x = 0; x < BORDER_WIDTH - 6; x++) {
		GotoXY(14 + x, 16);
		printf("��");
	}
}

// �߰����� �ؽ�Ʈ ���
void PrintScore() {
	TextColor(14);
	GotoXY(13, 7);
	printf("Clear Num : %3d", clearNum);
	GotoXY(12, 8);
	printf(" S C O R E : %5d", score);
	GotoXY(14, 10);
	printf("< N E X T >");
}

// ���� ���
void NewBlock() {
	blockX = 4;
	blockY = 0;
	blockRotation = 0;

	if (flagNextBlock == 0) {
		blockType = BlockSelector();
		flagNextBlock = 1;
	}
	else
		blockType = nextBlockType;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (BlockShape[blockType][blockRotation][y][x])
				copyBoard[blockY + y][blockX + x] = MBLOCK;
		}
	}
	flagNewBlock = 0;
	PrintNextBlock();
}

// ��� ����
int BlockSelector() {
	cnt++;

	if (cnt > 6) {
		BlockShuffler();
		cnt = 0;
	}
	return shuffleBlock[cnt];
}

// ��� ����
void BlockShuffler() {
	int j, temp;

	for (int i = 0; i < 7; i++) {
		shuffleBlock[i] = i;
	}
	for (int i = 0; i < 7; i++) {
		j = rand() % 7;
		temp = shuffleBlock[i];
		shuffleBlock[i] = shuffleBlock[j];
		shuffleBlock[j] = temp;
	}
}

// ���� ��� ���
void PrintNextBlock() {
	nextBlockType = BlockSelector();

	if (nextBlockType == 0)
		TextColor(4);
	if (nextBlockType == 1)
		TextColor(2);
	if (nextBlockType == 2)
		TextColor(9);
	if (nextBlockType == 3)
		TextColor(10);
	if (nextBlockType == 4)
		TextColor(11);
	if (nextBlockType == 5)
		TextColor(12);
	if (nextBlockType == 6)
		TextColor(13);

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			GotoXY(15 + x, 12 + y);
			if (BlockShape[blockType][0][y][x] == 1) {
				printf("  ");
			}
		}
	}
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			GotoXY(15 + x, 12 + y);
			if (BlockShape[nextBlockType][0][y][x] == 1) {
				printf("��");
			}
		}
	}
}

// Ű���� �Է�
void Keyboard() {
	if (_kbhit()) {
		int nkey = _getch();
		if (nkey == ARROW) {
			nkey = _getch();
			switch (nkey) {
			case LEFT:
				if (CrushCheck(-1, 0, 0) == TRUE) {
					Move(-1, 0, 0);
				}
				break;

			case RIGHT:
				if (CrushCheck(1, 0, 0) == TRUE) {
					Move(1, 0, 0);
				}
				break;

			case DOWN:
				if (CrushCheck(0, 1, 0) == TRUE) {
					Move(0, 1, 0);
				}
				break;

			case UP:
				if (CrushCheck(0, 0, 1) == TRUE)
					Move(0, 0, 1);
				else if (CrushCheck(-1, 0, 0) == TRUE) { // ������ ȸ��
					Move(-1, 0, 0);

					for (int rotateMoveY = 0;; rotateMoveY--) {
						for (int rotateMoveX = 0; rotateMoveX < 3; rotateMoveX++) {
							for (int n = 0; n < 2; n++) {
								rotateMoveX *= -1;
								if (CrushCheck(rotateMoveX, rotateMoveY, 1) == TRUE) {
									Move(rotateMoveX, rotateMoveY, 1);
									return;
								}
							}
						}
					}
				}
				else if (CrushCheck(1, 0, 0) == TRUE) {
					Move(1, 0, 0);

					for (int rotateMoveY = 0;; rotateMoveY--) {
						for (int rotateMoveX = 0; rotateMoveX < 3; rotateMoveX++) {
							for (int n = 0; n < 2; n++) {
								rotateMoveX *= -1;
								if (CrushCheck(rotateMoveX, rotateMoveY, 1) == TRUE) {
									Move(rotateMoveX, rotateMoveY, 1);
									return;
								}
							}
						}
					}
				}
				break;
			}
		}
		if (nkey == Z) {
			if (CrushCheck(0, 0, -1) == TRUE)
				Move(0, 0, -1);
			else if (CrushCheck(-1, 0, 0) == TRUE) {
				Move(-1, 0, 0);

				for (int rotateMoveY = 0;; rotateMoveY--) {
					for (int rotateMoveX = 0; rotateMoveX < 3; rotateMoveX++) {
						for (int n = 0; n < 2; n++) {
							rotateMoveX *= -1;
							if (CrushCheck(rotateMoveX, rotateMoveY, -1) == TRUE) {
								Move(rotateMoveX, rotateMoveY, -1);
								return;
							}
						}
					}
				}
			}
			else if (CrushCheck(1, 0, 0) == TRUE) {
				Move(1, 0, 0);

				for (int rotateMoveY = 0;; rotateMoveY--) {
					for (int rotateMoveX = 0; rotateMoveX < 3; rotateMoveX++) {
						for (int n = 0; n < 2; n++) {
							rotateMoveX *= -1;
							if (CrushCheck(rotateMoveX, rotateMoveY, -1) == TRUE) {
								Move(rotateMoveX, rotateMoveY, -1);
								return;
							}
						}
					}
				}
			}
		}
		if (nkey == SPACEBAR) {
			while (1) {
				if (CrushCheck(0, 1, 0) == TRUE) {
					Move(0, 1, 0);
				}
				else {
					FixBlock();
					break;
				}
			}
		}
		if (nkey == C) {
			if (soundOnOff == 0) {
				PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				soundOnOff += 1;
			}
			else {
				PlaySound(NULL, 0, 0);
				soundOnOff = 0;
			}
		}
		if (nkey == P) // P�� ����ȭ�� ����
			StopScreen();
		if (nkey == Esc)
			EndScreen();
	}
}

// �ٴڿ� ��Ƶ� ��� ���� �ȵ�
void Drop() {
	if (CrushCheck(0, 1, 0) == TRUE && flagCrush == 0) {
		Move(0, 1, 0);
	}
	else if (CrushCheck(0, 1, 0) == TRUE && flagCrush == 1) {
		flagCrush = 0;
	}
	else if (CrushCheck(0, 1, 0) == FALSE && flagCrush == 0) {
		flagCrush = 1;
	}
	else if (CrushCheck(0, 1, 0) == FALSE && flagCrush == 1) {
		FixBlock();
		flagCrush = 0;
	}
}

// �浹 üũ
int CrushCheck(int blockXODJ, int blockYODJ, int rotateODJ) {
	int tempRotation = (blockRotation + rotateODJ) % 4;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (BlockShape[blockType][tempRotation][y][x] == 1
				&& board[blockY + blockYODJ + y][blockX + blockXODJ + x] > 3) {
				return FALSE; // ��ġ�� FALSE
			}
		}
	}
	return TRUE; // ��ġ�� ������ TRUE
}

// ��� �̵�
void Move(int inputX, int inputY, int rotate) {
	int tempRotation = blockRotation + rotate;

	if (tempRotation > 3) {
		tempRotation = 0;
	}
	else if (tempRotation < 0) {
		tempRotation = 3;
	}

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (BlockShape[blockType][blockRotation][y][x] == 1) {
				copyBoard[blockY + y][blockX + x] = EMPTY;
			}
		}
	}
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (BlockShape[blockType][tempRotation][y][x] == 1) {
				copyBoard[blockY + y + inputY][blockX + x + inputX] = MBLOCK;
			}
		}
	}
	blockX = blockX + inputX; // �Է¹��� ��ŭ x�� �̵�
	blockY = blockY + inputY; // �Է¹��� ��ŭ y�� �̵�
	blockRotation = tempRotation;
}

// �����̴� ����� ������ ������� ����
void FixBlock() {
	for (int y = 0; y < BORDER_HEIGHT; y++) {
		for (int x = 0; x < BORDER_WIDTH; x++) {
			if (copyBoard[y][x] == MBLOCK) // board�� copyboard�� ����
				copyBoard[y][x] = FBLOCK; // board�� copyboard�� ����
		}
	}
	flagNewBlock = 1;
}

// �������� ���
void OverLineDraw() {
	for (int y = 2, x = 1; x < BORDER_WIDTH - 1; x++) {
		if (board[y][x] == EMPTY) { // ���� ���ٸ�
			TextColor(15);
			GotoXY(x, y);
			printf("_ ");
		}
	}
}

// �� �ϼ��� ���� �� ���� �� ���̵� ����
void LineClean() {
	int blockCount = 0; // �� ���� ��� ��
	int clearLine = 0; // ������ �� ��ġ
	int clearCount = 0; // ������ Ƚ��

	for (int y = BORDER_HEIGHT - 2; y > 2 && clearCount < 4; y--) { // 4ȸ �����Ͽ��ٸ� üũ ����
		for (int x = 1; x < BORDER_WIDTH - 1; x++) { // �� ���� ��� �� üũ
			if (copyBoard[y][x] == FBLOCK)
				blockCount++;
		}
		if (blockCount == 10) { // �� �ϼ��� ����
			for (clearLine = y; clearLine > 2; clearLine--) // ���� ���� ������
				for (int x = 1; x < BORDER_WIDTH - 1; x++) {
					if (clearLine == 3) // ���� �� ���̸� ������ �ʰ� ����
						copyBoard[clearLine][x] = EMPTY;
					else
						copyBoard[clearLine][x] = copyBoard[clearLine - 1][x];
				}
			clearCount++; // ������ Ƚ�� üũ
			y++; // ������ ���� �ٽ� üũ
			speedUp += 1; // ���̵� ������ �ʿ��� �� �� ����
			clearNum += 1;
		}
		blockCount = 0; // �� ���� ��� �� üũ �ʱ�ȭ
	}
	if (clearCount == 1)
		score += 100;
	if (clearCount == 2)
		score += 300;
	if (clearCount == 3)
		score += 500;
	if (clearCount == 4)
		score += 700;

	if (speedUp >= 4) { // �� �ϼ��� ���̵� ���� �� ���̵� ������ �ʿ��� �� ��
		if (speed <= 150)
			speed += 3; // �ӵ� ����
		speedUp -= 4;
	}
}

// ���ӿ���ȭ��
void GameOverCheck() {
	for (int x = 1; x < BORDER_WIDTH - 1; x++) {
		if (copyBoard[2][x] == FBLOCK) { // Y�� 2�� ��ġ�� ������ ����� ������
			if (score > bestScore)
				Ranking(); //��ŷȭ��
			for (int i = 0; i < 7; i++) {
				GotoXY(3, 10 + i);
				printf("                                   \n");
			}
			GotoXY(8, 12);
			printf("Enter : ReStart");
			GotoXY(8, 14);
			printf(" Esc : The End");
			Sleep(1000); // ��� ����

			while (1) {
				if (_kbhit()) {
					int nkey = _getch();
					if (nkey == Enter) { // �ٽ� ����
						system("cls");
						ResetGameBoard();
						ResetCopyGameBoard();
						PrintGameBoardAll();
						PrintNextBoard();
						NewBlock();
						cnt = 7;
						speedUp = 0;
						clearNum = 0;
						score = 0;
						speed = 0;
						return 0;
					}
					if (nkey == Esc) // ���� ����
						EndScreen();
				}
			}
		}
	}
}

// ��ŷȭ��
void Ranking() {
	TextColor(14);
	for (int i = 0; i < 7; i++) {
		GotoXY(3, 10 + i);
		printf("                                   \n");
	}
	GotoXY(8, 12);
	printf("���ϵ帳�ϴ�!");
	GotoXY(5, 14);
	printf("�ְ����� �޼��ϼ̽��ϴ�!");

	fopen_s(&fp, "Ranking.txt", "w+"); // ���� ���� ���� ���� ����
	bestScore = score;
	fprintf(fp, "%d", bestScore);
	fclose(fp);
	Sleep(2000);

	while (1) { // EnterŰ �Է½� ���ӿ���ȭ�� ����
		if (_kbhit()) {
			int nkey = _getch();
			if (nkey == Enter) {
				return 0;
			}
		}
	}
}