#include <string>
#include <iostream>
#include <stdlib.h>
#define GRID_SIZE 3

using namespace std;

class Game
{
private:char grid[GRID_SIZE][GRID_SIZE];

public:
	void CheckWin()
	{
		const char* WINNING_MOVES[8] = {"123", "456", "789", "147", "258", "369", "159", "753"};
		
		for (int i = 0; i < 8; i++)
		{
			bool winner = true;
			char prevGrid = '0';
			const char* WINNING_MOVE = WINNING_MOVES[i];
			
			for (int index = 0; index < 3; index++)
			{
				char character = WINNING_MOVE[index];
				
				int inputNum = character - '0';
				int gridSpace = inputNum - 1;
				
				int row = gridSpace / GRID_SIZE;
				int col = gridSpace % GRID_SIZE;
				
				char gridChar = grid[row][col];
				
				if (prevGrid == '0')
				{
					prevGrid = gridChar;
				}
				else if(prevGrid == gridChar)
				{
					continue;
				}else
				{
					winner = false;
					break;
				}
			}
			
			if (winner)
			{
				puts("********** We have a winner! **********");
				printf("Looks like %c won, congratulations!", prevGrid);
				exit(0);
			}
		}
	}

	void AskTurn()
	{
		string input;
		
		while (true)
		{
			puts("Where would you like to play?");
			getline(cin, input);
			
			if(input != "")
			{
				char entered = input.c_str()[0];
				
				if(entered >= '1' && entered <= '9')
				{
					int inputNum  = entered - '0';
					int index = inputNum - 1;
					
					int row = index / 3;
					int col = index % 3;
					
					char gridPos = grid[row][col];
					
					if (gridPos == 'X' || gridPos == 'O')
					{
						puts("That grid position is already taken!");
					}
					else
					{
						grid[row][col] = 'X';
						break;
					}
				}
				else
				{
					puts("You have to play in the range 1-9!");
				}
			}else
			{
				puts("You must enter something!");
			}
		}
	}
	
	void BuildGrid()
	{
		int number = 1;
		for (int x = 0; x < GRID_SIZE; x++)
		{
			for (int y = 0; y < GRID_SIZE; y++)
			{
				grid[x][y] = to_string(number).c_str()[0];
				number += 1;
			}
		}
	}
	
	void aiTurn()
	{
		while (true)
		{
			int compChoice = (rand() % 9 ) + 1;
			int row = (compChoice - 1) / 3;
			int col = (compChoice - 1) % 3;
			char gridPos = grid[row][col];
			
			if (gridPos == 'X' || gridPos == 'O')
			{
			
			} else
			{
				printf("The computer will play at %d. \n", compChoice);
				grid[row][col] = 'O';
				break;
			}
		}
	}
	
	void DisplayGrid()
	{
		printf("-------------\n");
		for (int x = 0; x < GRID_SIZE; x++)
		{
			printf("| ");
			for (int y = 0; y < GRID_SIZE; y++)
			{
				printf("%c | ", grid[x][y]);
			}
			printf("\n-------------\n");
		}
	}
	
	[[noreturn]] Game()
	{
		BuildGrid();
		CheckWin();
		DisplayGrid();
		
		while (true)
		{
			AskTurn();
			DisplayGrid();
			CheckWin();
			
			aiTurn();
			DisplayGrid();
			CheckWin();
		}
	}
};

int main(int argc, char *argv[])
{
	Game game;
	return 0;
}
