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


// [블록 종류][블록 회전][블록 모양][블록 모양]
int BlockShape[7][4][4][4] = {
	{
		// ㅁ 블록
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
		// I 블록 (축 3, 3)
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
		// 역 Z 블록 (축 2, 3)
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
		// Z 블록 (축 2, 3)
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
		// ㄱ 블록
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
		// 역 ㄱ 블록
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
		// T 블록
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

// 화면 좌표 설정
void GotoXY(int x, int y) {
	COORD Pos;
	Pos.X = x * 2;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 콘솔창 세팅
void SetConsole() {
	ConsoleSize();
	RemoveScrollbar();
	RemoveCurser();
}

// 콘솔창 크기 조절
void ConsoleSize() {
	system("mode con cols=43 lines=25");
}

// 콘솔창 스크롤바 삭제
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

// 커서 제거
void RemoveCurser() {
	CONSOLE_CURSOR_INFO curinfo = { 0, };
	curinfo.dwSize = 1;
	curinfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}

// 글자 색 변경
void TextColor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

// 시작화면
void StartScreen() {
	fopen_s(&fp, "Ranking.txt", "a"); // 랭킹을 기록할 메모장이 없으면 생성
	fclose(fp);
	fopen_s(&fp, "Ranking.txt", "r"); // bestScore 출력용
	while (fscanf_s(fp, "%d", &bestScore) == 1);
	fclose(fp);

	TextColor(15);
	GotoXY(0, 5);
	printf("         * * *  T E T R I S  * * *\n\n"); //시작화면 출력
	printf("           ◁ ▷ ▽  : 이동\n");
	printf("              △     : 회전\n");
	printf("              Z      : 역회전\n");
	printf("            Space    : 낙하\n");
	printf("              C      : 음악 On/Off\n");
	printf("              P      : 일시정지\n");
	printf("             ESC     : 게임 종료\n\n");
	printf("             ☆ Press Enter ☆\n\n\n");
	printf("              최고점 : %5d\n\n\n\n\n", bestScore);
	printf("  C드라이브에 tetris.wav가 있다면 C 입력\n");

	while (1) {
		if (_kbhit()) { // 입력이 있으면 실행
			int nkey = _getch();
			if (nkey == Enter) { // Enter면 시작
				system("cls");
				return 0;
			}
			if (nkey == Esc) // Esc면 종료화면 실행
				EndScreen();
			if (nkey == C) { // C로 음악 On/Off
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

// 정지화면
void StopScreen() {
	system("cls");
	TextColor(15);
	GotoXY(6, 12);
	printf("■ 일  시  정  지 ■\n"); // 정지화면 출력

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

				if (1) { // 다음 블록 출력
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
								printf("■");
							}
						}
					}
				}
				return 0;
			}
		}
	}
}

// 게임보드와 임시보드가 같아도 출력
void PrintGameBoardAll() {
	for (int y = 0; y < BORDER_HEIGHT; y++) {
		for (int x = 0; x < BORDER_WIDTH; x++) {
			board[y][x] = copyBoard[y][x]; // 임시보드의 값을 넣어줌  
			switch (board[y][x]) {
			case EMPTY: // 해당칸이 빈 공간이면
				GotoXY(x, y);
				printf("  ");
				break;

			case MBLOCK: // 해당칸이 움직이는 블록이면
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
				printf("■");
				break;

			case OVERLINE: // 해당칸이 게임 오버라인이면
				TextColor(15);
				GotoXY(x, y);
				printf("_ ");
				break;

			case WALL: // 해당칸이 벽이면
				TextColor(15);
				GotoXY(x, y);
				printf("▩");
				break;

			case FBLOCK: // 해당칸이 고정된 블록이면
				TextColor(15);
				GotoXY(x, y);
				printf("□");
				break;
			}
		}
	}
}

// 종료화면
void EndScreen() {
	system("cls"); // 화면 초기화
	TextColor(15);
	GotoXY(6, 12);
	printf("■ 게  임  종  료 ■"); // 종료화면 출력
	GotoXY(1, 23);
	exit(0); // 프로그램 종료
}

// 게임보드 빈 공간으로 초기화
void ResetGameBoard() {
	for (int y = 0; y < BORDER_HEIGHT; y++) { // 게임공간을 빈 공간으로 세팅
		for (int x = 0; x < BORDER_WIDTH; x++)
			copyBoard[y][x] = EMPTY;
	}
}

// 임시보드 벽 및 오버라인 세팅
void ResetCopyGameBoard() {
	for (int y = 0; y < BORDER_HEIGHT; y++) {
		for (int x = 0; x < BORDER_WIDTH; x++) {
			copyBoard[y][x] = EMPTY;
		}
	}
	for (int y = 0; y < BORDER_HEIGHT; y++) {
		for (int x = 0; x < BORDER_WIDTH; x++) {
			if (x == 0 || x == BORDER_WIDTH - 1) // 좌-우 벽 그리기
				copyBoard[y][x] = WALL;

			if (y == BORDER_HEIGHT - 1) // 하단 벽 그리기
				copyBoard[y][x] = WALL;

			if (y == 2 && x != 0 && x != BORDER_WIDTH - 1) // 게임 오버라인 그리기
				copyBoard[y][x] = OVERLINE;
		}
	}
}

// 게임보드 출력
void PrintGameBoard() {
	for (int y = 0; y < BORDER_HEIGHT; y++) {
		for (int x = 0; x < BORDER_WIDTH; x++) {
			if (copyBoard[y][x] != board[y][x]) { // 임시보드가 게임보드와 다른 부분만 출력
				board[y][x] = copyBoard[y][x];
				switch (board[y][x]) {
				case EMPTY: // 해당칸이 빈 공간이면
					GotoXY(x, y);
					printf("  ");
					break;

				case MBLOCK: // 해당칸이 무브블록이면
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
					printf("■");
					break;

				case OVERLINE: // 해당칸이 오버라인이면
					TextColor(15);
					GotoXY(x, y);
					printf("_ ");
					break;

				case WALL: // 해당칸이 벽이면
					TextColor(15);
					GotoXY(x, y);
					printf("▩");
					break;

				case FBLOCK: // 해당칸이 고정블록이면
					TextColor(15);
					GotoXY(x, y);
					printf("□");
					break;
				}
			}
		}
	}
}

// 추가보드 출력
void PrintNextBoard() {
	TextColor(15);

	for (int x = 0; x < BORDER_WIDTH - 6; x++) {
		GotoXY(14 + x, 11);
		printf("▩");
	}
	for (int y = 0; y < BORDER_HEIGHT - 20; y++) {
		GotoXY(13, y + 12);
		printf("▩");
	}
	for (int y = 0; y < BORDER_HEIGHT - 20; y++) {
		GotoXY(20, y + 12);
		printf("▩");
	}
	for (int x = 0; x < BORDER_WIDTH - 6; x++) {
		GotoXY(14 + x, 16);
		printf("▩");
	}
}

// 추가보드 텍스트 출력
void PrintScore() {
	TextColor(14);
	GotoXY(13, 7);
	printf("Clear Num : %3d", clearNum);
	GotoXY(12, 8);
	printf(" S C O R E : %5d", score);
	GotoXY(14, 10);
	printf("< N E X T >");
}

// 현재 블록
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

// 블록 선택
int BlockSelector() {
	cnt++;

	if (cnt > 6) {
		BlockShuffler();
		cnt = 0;
	}
	return shuffleBlock[cnt];
}

// 블록 셔플
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

// 다음 블록 출력
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
				printf("■");
			}
		}
	}
}

// 키보드 입력
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
				else if (CrushCheck(-1, 0, 0) == TRUE) { // 벽에서 회전
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
		if (nkey == P) // P면 정지화면 실행
			StopScreen();
		if (nkey == Esc)
			EndScreen();
	}
}

// 바닥에 닿아도 즉시 고정 안됨
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

// 충돌 체크
int CrushCheck(int blockXODJ, int blockYODJ, int rotateODJ) {
	int tempRotation = (blockRotation + rotateODJ) % 4;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (BlockShape[blockType][tempRotation][y][x] == 1
				&& board[blockY + blockYODJ + y][blockX + blockXODJ + x] > 3) {
				return FALSE; // 겹치면 FALSE
			}
		}
	}
	return TRUE; // 겹치지 않으면 TRUE
}

// 블록 이동
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
	blockX = blockX + inputX; // 입력받은 만큼 x축 이동
	blockY = blockY + inputY; // 입력받은 만큼 y축 이동
	blockRotation = tempRotation;
}

// 움직이는 블록을 고정된 블록으로 변경
void FixBlock() {
	for (int y = 0; y < BORDER_HEIGHT; y++) {
		for (int x = 0; x < BORDER_WIDTH; x++) {
			if (copyBoard[y][x] == MBLOCK) // board를 copyboard로 덮음
				copyBoard[y][x] = FBLOCK; // board를 copyboard로 덮음
		}
	}
	flagNewBlock = 1;
}

// 오버라인 출력
void OverLineDraw() {
	for (int y = 2, x = 1; x < BORDER_WIDTH - 1; x++) {
		if (board[y][x] == EMPTY) { // 블럭이 없다면
			TextColor(15);
			GotoXY(x, y);
			printf("_ ");
		}
	}
}

// 줄 완성시 삭제 및 점수 및 난이도 증가
void LineClean() {
	int blockCount = 0; // 한 줄의 블록 수
	int clearLine = 0; // 삭제할 줄 위치
	int clearCount = 0; // 삭제한 횟수

	for (int y = BORDER_HEIGHT - 2; y > 2 && clearCount < 4; y--) { // 4회 삭제하였다면 체크 안함
		for (int x = 1; x < BORDER_WIDTH - 1; x++) { // 한 줄의 블록 수 체크
			if (copyBoard[y][x] == FBLOCK)
				blockCount++;
		}
		if (blockCount == 10) { // 줄 완성시 삭제
			for (clearLine = y; clearLine > 2; clearLine--) // 위의 줄을 내리기
				for (int x = 1; x < BORDER_WIDTH - 1; x++) {
					if (clearLine == 3) // 가장 윗 줄이면 내리지 않고 비우기
						copyBoard[clearLine][x] = EMPTY;
					else
						copyBoard[clearLine][x] = copyBoard[clearLine - 1][x];
				}
			clearCount++; // 삭제한 횟수 체크
			y++; // 삭제한 줄은 다시 체크
			speedUp += 1; // 난이도 증가에 필요한 줄 수 증가
			clearNum += 1;
		}
		blockCount = 0; // 한 줄의 블록 수 체크 초기화
	}
	if (clearCount == 1)
		score += 100;
	if (clearCount == 2)
		score += 300;
	if (clearCount == 3)
		score += 500;
	if (clearCount == 4)
		score += 700;

	if (speedUp >= 4) { // 줄 완성시 난이도 증가 및 난이도 증가에 필요한 줄 수
		if (speed <= 150)
			speed += 3; // 속도 증가
		speedUp -= 4;
	}
}

// 게임오버화면
void GameOverCheck() {
	for (int x = 1; x < BORDER_WIDTH - 1; x++) {
		if (copyBoard[2][x] == FBLOCK) { // Y가 2인 위치에 고정된 블록이 있으면
			if (score > bestScore)
				Ranking(); //랭킹화면
			for (int i = 0; i < 7; i++) {
				GotoXY(3, 10 + i);
				printf("                                   \n");
			}
			GotoXY(8, 12);
			printf("Enter : ReStart");
			GotoXY(8, 14);
			printf(" Esc : The End");
			Sleep(1000); // 잠시 정지

			while (1) {
				if (_kbhit()) {
					int nkey = _getch();
					if (nkey == Enter) { // 다시 시작
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
					if (nkey == Esc) // 게임 종료
						EndScreen();
				}
			}
		}
	}
}

// 랭킹화면
void Ranking() {
	TextColor(14);
	for (int i = 0; i < 7; i++) {
		GotoXY(3, 10 + i);
		printf("                                   \n");
	}
	GotoXY(8, 12);
	printf("축하드립니다!");
	GotoXY(5, 14);
	printf("최고점을 달성하셨습니다!");

	fopen_s(&fp, "Ranking.txt", "w+"); // 쓰기 모드로 현재 점수 저장
	bestScore = score;
	fprintf(fp, "%d", bestScore);
	fclose(fp);
	Sleep(2000);

	while (1) { // Enter키 입력시 게임오버화면 실행
		if (_kbhit()) {
			int nkey = _getch();
			if (nkey == Enter) {
				return 0;
			}
		}
	}
}