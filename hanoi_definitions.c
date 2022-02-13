#include "hanoi_declarations.h"
#include "primlib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

void push(int gameState[NO_PEGS][NO_DISCS], int pegsTops[NO_PEGS], int whichPeg, int** pDiscSelected)
{
	if (pegsTops[whichPeg] < NO_DISCS)
    {
		gameState[whichPeg][pegsTops[whichPeg]++] = **pDiscSelected;
	}
    else
    {
		return;
	}
}

int pop(int gameState[NO_PEGS][NO_DISCS], int pegsTops[NO_PEGS], int whichPeg)
{
	if (pegsTops[whichPeg] > 0)
    {
		int discSelected = gameState[whichPeg][--pegsTops[whichPeg]];
		gameState[whichPeg][pegsTops[whichPeg]] = -1;
		return discSelected;
	}
    else
    {
		return -1;
	}
}

int peek(int gameState[NO_PEGS][NO_DISCS], int pegsTops[NO_PEGS], int whichPeg)
{
	if (pegsTops[whichPeg] > 0)
    {
		return gameState[whichPeg][pegsTops[whichPeg] - 1];
	}
    else
    {
		return -1;
	}
}

void makePegs(peg pegs[NO_PEGS])
{
	for (int i = 0; i < NO_PEGS; i++)
    {
		pegs[i].xLeftTop = gfx_screenWidth() / (NO_PEGS + 1) +
						   (i * gfx_screenWidth() / (NO_PEGS + 1)) -
						   (PEG_WIDTH * 0.5);
		pegs[i].yLeftTop = gfx_screenHeight() / 2;
		pegs[i].xRightBottom = pegs[i].xLeftTop + PEG_WIDTH;
		pegs[i].yRightBottom = gfx_screenHeight();
		pegs[i].xCenter = pegs[i].xRightBottom - PEG_WIDTH / 2;
		pegs[i].height = pegs[i].yRightBottom - pegs[i].yLeftTop;
	}
}

void makeDiscs(disc discs[NO_DISCS], peg pegs[NO_PEGS])
{
	for (int i = 0; i < NO_DISCS; i++)
    {
		if (!i)
        {
			discs[i].yRightBottom = gfx_screenHeight();
		}
        else
        {
			discs[i].yRightBottom = discs[i - 1].yLeftTop;
		}
		if (NO_DISCS > 6)
        {
			if (NO_PEGS > 4)
            {
				discs[i].xLeftTop = pegs[0].xCenter -
									((pegs[1].xCenter - pegs[0].xCenter) / 2) +
									(i * NO_DISCS * 0.5);
				discs[i].yLeftTop = discs[i].yRightBottom - (pegs[0].height / (NO_DISCS + 3));
				discs[i].xRightBottom = pegs[0].xCenter +
					((pegs[1].xCenter - pegs[0].xCenter) / 2) -
					(i * NO_DISCS * 0.5);
				discs[i].xCenter = (discs[i].xRightBottom - discs[i].xLeftTop) / 2 +
					discs[i].xLeftTop;
			}
            else
            {
				discs[i].xLeftTop = pegs[0].xCenter -
									((pegs[1].xCenter - pegs[0].xCenter) / 3) +
									(i * NO_DISCS * 1);
				discs[i].yLeftTop =
					discs[i].yRightBottom - (pegs[0].height / (NO_DISCS + 3));
				discs[i].xRightBottom = pegs[0].xCenter +
					((pegs[1].xCenter - pegs[0].xCenter) / 3) -
					(i * NO_DISCS * 1);
				discs[i].xCenter =
					(discs[i].xRightBottom - discs[i].xLeftTop) / 2 +
					discs[i].xLeftTop;
			}
		}
        else
        {
			if (NO_PEGS > 4)
            {
				discs[i].xLeftTop = pegs[0].xCenter -
									((pegs[1].xCenter - pegs[0].xCenter) / 2) +
									(i * NO_DISCS * 2);
				discs[i].yLeftTop = discs[i].yRightBottom - (pegs[0].height / (NO_DISCS + 3));
				discs[i].xRightBottom = pegs[0].xCenter +
					((pegs[1].xCenter - pegs[0].xCenter) / 2) -
					(i * NO_DISCS * 2);
				discs[i].xCenter =
					(discs[i].xRightBottom - discs[i].xLeftTop) / 2 +
					discs[i].xLeftTop;
			}
            else
            {
				discs[i].xLeftTop = pegs[0].xCenter -
									((pegs[1].xCenter - pegs[0].xCenter) / 3) +
									(i * NO_DISCS * 3);
				discs[i].yLeftTop = discs[i].yRightBottom - (pegs[0].height / (NO_DISCS + 3));
				discs[i].xRightBottom = pegs[0].xCenter +
					((pegs[1].xCenter - pegs[0].xCenter) / 3) -
					(i * NO_DISCS * 3);
				discs[i].xCenter =
					(discs[i].xRightBottom - discs[i].xLeftTop) / 2 +
					discs[i].xLeftTop;
			}
		}
	}
}

void makeStacks(int gameState[NO_PEGS][NO_DISCS], int pegsTops[NO_PEGS])
{
	for (int i = 0; i < NO_PEGS; i++)
    {
		for (int j = 0; j < NO_DISCS; j++)
        {
			if (!i)
            {
				gameState[i][j] = j;
			}
            else
            {
				gameState[i][j] = -1;
			}
		}
	}

	for (int j = 0; j < NO_PEGS; j++)
    {
		if (!j)
        {
			pegsTops[j] = NO_DISCS;
		}
        else
        {
			pegsTops[j] = 0;
		}
	}
}

void drawPegs(peg pegs[NO_PEGS])
{
	for (int i = 0; i < NO_PEGS; i++)
    {
		gfx_filledRect(pegs[i].xLeftTop, pegs[i].yLeftTop, pegs[i].xRightBottom,
					   pegs[i].yRightBottom, WHITE);
	}
}

void drawDiscs(disc discs[NO_DISCS])
{
	for (int i = 0; i < NO_DISCS; i++)
    {
		gfx_filledRect(discs[i].xLeftTop, discs[i].yLeftTop,
					   discs[i].xRightBottom, discs[i].yRightBottom, MAGENTA);
	}
}

void drawHelpText()
{
	gfx_textout(0, 0, "QUIT - ESC", WHITE);
	gfx_textout(gfx_screenWidth() / 1.07, 0, "RESET - R", WHITE);
}

void drawWinText()
{
	gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
	gfx_textout(0, 0, "QUIT - ESC", WHITE);
	gfx_textout(gfx_screenWidth() / 2, 100, "Congratulations! You won!", GREEN);

	gfx_updateScreen();
	SDL_Delay(DELAY);
}

void redrawScreen(disc discs[NO_DISCS], peg pegs[NO_PEGS])
{
	gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
	drawPegs(pegs);
	drawDiscs(discs);
	drawHelpText();

	gfx_updateScreen();
	SDL_Delay(DELAY);
}

void selectDisc(int gameState[NO_PEGS][NO_DISCS], int pegsTops[NO_PEGS],
				disc discs[NO_DISCS], peg pegs[NO_PEGS], int whichPeg,
				int* pDiscSelected)
{
	*pDiscSelected = pop(gameState, pegsTops, whichPeg);

	while (discs[*pDiscSelected].yRightBottom > SELECTION_HEIGHT)
    {
		discs[*pDiscSelected].yLeftTop -= DISC_STEP;
		discs[*pDiscSelected].yRightBottom -= DISC_STEP;

		redrawScreen(discs, pegs);
	}
}

void moveDisc(int gameState[NO_PEGS][NO_DISCS], int pegsTops[NO_PEGS],
			  disc discs[NO_DISCS], peg pegs[NO_PEGS], int whichPeg,
			  int* pDiscSelected)
{
	if (discs[*pDiscSelected].xCenter < pegs[whichPeg].xCenter)
    {
		while (discs[*pDiscSelected].xCenter < pegs[whichPeg].xCenter)
        {
			discs[*pDiscSelected].xLeftTop += DISC_STEP;
			discs[*pDiscSelected].xRightBottom += DISC_STEP;
			discs[*pDiscSelected].xCenter += DISC_STEP;

			redrawScreen(discs, pegs);
		}
	}
    else
    {
		while (discs[*pDiscSelected].xCenter > pegs[whichPeg].xCenter)
        {
			discs[*pDiscSelected].xLeftTop -= DISC_STEP;
			discs[*pDiscSelected].xRightBottom -= DISC_STEP;
			discs[*pDiscSelected].xCenter -= DISC_STEP;

			redrawScreen(discs, pegs);
		}
	}

	int discOnTop = peek(gameState, pegsTops, whichPeg);

	if (discOnTop == -1)
    {
		while (discs[*pDiscSelected].yRightBottom < gfx_screenHeight())
        {
			discs[*pDiscSelected].yLeftTop += DISC_STEP;
			discs[*pDiscSelected].yRightBottom += DISC_STEP;

			redrawScreen(discs, pegs);
		}
	}
    else
    {
		while (discs[*pDiscSelected].yRightBottom < discs[discOnTop].yLeftTop)
        {
			discs[*pDiscSelected].yLeftTop += DISC_STEP;
			discs[*pDiscSelected].yRightBottom += DISC_STEP;

			redrawScreen(discs, pegs);
		}
	}

	push(gameState, pegsTops, whichPeg, &pDiscSelected);
}

void reset(peg pegs[NO_PEGS], disc discs[NO_DISCS],
		   int gameState[NO_PEGS][NO_DISCS], int pegsTops[NO_PEGS],
		   int* pKeyPressed, bool* pIsSelected, int* pDiscSelected)
{
	makePegs(pegs);
	makeDiscs(discs, pegs);
	makeStacks(gameState, pegsTops);

	*pKeyPressed = 0;
	*pIsSelected = false;
	*pDiscSelected = -1;
}

bool isWon(int gameState[NO_PEGS][NO_DISCS])
{
	for (int i = 0; i < NO_DISCS; i++)
    {
		if (gameState[NO_PEGS - 1][i] == -1)
        {
			return false;
		}
	}
	return true;
}

void winScreen(bool* pIsRunning, disc discs[NO_DISCS], peg pegs[NO_PEGS])
{
	drawWinText();

	int keyPressed = gfx_getkey();
	if (keyPressed == SDLK_ESCAPE)
    {
		*pIsRunning = false;
	}
}
