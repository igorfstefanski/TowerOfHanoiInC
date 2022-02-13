#ifndef HANOI_DECLARATIONS_H
#define HANOI_DECLARATIONS_H

#include <stdbool.h>

#define DELAY 12
#define NO_DISCS 3
#define NO_PEGS 3
#define PEG_WIDTH 10
#define SELECTION_HEIGHT 200
#define DISC_STEP 5

typedef struct
{
	int xLeftTop;
	int yLeftTop;
	int xRightBottom;
	int yRightBottom;
	int xCenter;
} disc;

typedef struct
{
	int xLeftTop;
	int yLeftTop;
	int xRightBottom;
	int yRightBottom;
	int xCenter;
	int height;
} peg;

void push(int gameState[NO_PEGS][NO_DISCS], int pegsTops[NO_PEGS], int whichPeg,
		  int** pDiscSelected);
int pop(int gameState[NO_PEGS][NO_DISCS], int pegsTops[NO_PEGS], int whichPeg);
int peek(int gameState[NO_PEGS][NO_DISCS], int pegsTops[NO_PEGS], int whichPeg);

void makePegs(peg pegs[NO_PEGS]);
void makeDiscs(disc discs[NO_DISCS], peg pegs[NO_PEGS]);
void makeStacks(int gameState[NO_PEGS][NO_DISCS], int pegsTops[NO_PEGS]);

void drawPegs(peg pegs[NO_PEGS]);
void drawDiscs(disc discs[NO_DISCS]);
void drawHelpText();
void drawWinText();
void redrawScreen(disc discs[NO_DISCS], peg pegs[NO_PEGS]);

void selectDisc(int gameState[NO_PEGS][NO_DISCS], int pegsTops[NO_PEGS],
				disc discs[NO_DISCS], peg pegs[NO_PEGS], int whichPeg,
				int* pDiscSelected);
void moveDisc(int gameState[NO_PEGS][NO_DISCS], int pegsTops[NO_PEGS],
			  disc discs[NO_DISCS], peg pegs[NO_PEGS], int whichPeg,
			  int* pDiscSelected);

void reset(peg pegs[NO_PEGS], disc discs[NO_DISCS],
		   int gameState[NO_PEGS][NO_DISCS], int pegsTops[NO_PEGS],
		   int* pKeyPressed, bool* pIsSelected, int* pDiscSelected);
bool isWon(int gameState[NO_PEGS][NO_DISCS]);
void winScreen(bool* pIsRunning, disc discs[NO_DISCS], peg pegs[NO_PEGS]);

#endif
