/*
 * TITLE:   TOWER OF HANOI IN C
 * AUTHOR:  Igor Stefański
 * DATE: March 2020
 * DESCRIPTION:
 * The aim of the exercise was to write a well-known Tower of Hanoi game,
 * using simple graphics library which is based on basic primitives from
 * the SDL_gfx library.
 * 
 * Task was introduced on Programming & Data Structures course.
 * 2019/2020 Academic Year
 * Technical University of Lodz, Computer Science
 */

#include "hanoi_declarations.h"
#include "primlib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	bool isRunning = true;
    bool isSelected;

	peg pegs[NO_PEGS];
	disc discs[NO_DISCS];

	int gameState[NO_PEGS][NO_DISCS];
	int pegsTops[NO_PEGS];
	int keyPressed, discSelected;

	if (gfx_init())
    {
        exit(3);
    }

	reset(pegs, discs, gameState, pegsTops, &keyPressed, &isSelected, &discSelected);

	while (isRunning)
    {
		keyPressed = gfx_pollkey();

		if (keyPressed == SDLK_ESCAPE)
        {
			isRunning = false;
		}
		if (keyPressed == SDLK_r)
        {
			reset(pegs, discs, gameState, pegsTops, &keyPressed, &isSelected, &discSelected);
		}

		if (!isSelected)
        {
			if (keyPressed > '0' && keyPressed <= (NO_PEGS + 48))
            {
				if (peek(gameState, pegsTops, keyPressed - '1') != -1)
                {
					selectDisc(gameState, pegsTops, discs, pegs, keyPressed - '1', &discSelected);
					isSelected = true;
				}
			}
		}
        else
        {
			if (keyPressed > '0' && keyPressed <= (NO_PEGS + 48))
            {
				if (peek(gameState, pegsTops, keyPressed - '1') < discSelected)
                {
					moveDisc(gameState, pegsTops, discs, pegs, keyPressed - '1', &discSelected);
					isSelected = false;
				}
			}
		}

		redrawScreen(discs, pegs);

		if (isWon(gameState))
        {
			winScreen(&isRunning, discs, pegs);
		}
	}

	return 0;
}
