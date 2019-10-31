#include <bits/stdc++.h>
using namespace std;

int SIZE_OF_BOARD;
int MINE_COUNT;
char DIFFICULTY_LEVEL;
int LENGTH_OF_BOARD;
char *realCondition;
char *playerCondition;
bool *visited;
int max_visitable;
int visited_till_now;
// pair<int, int> CurrentClick;
int currentClickRow;
int currentClickCol;
char currentClickRL;

void setMine(int mine_index);
void getDifficultyLevel()
{
	cout << "Choose Your Difficulty Level:" << endl;
	cout << "e - easy" << endl;
	cout << "m - medium" << endl;
	cout << "h - hard" << endl;
	cin >> DIFFICULTY_LEVEL;
	if (DIFFICULTY_LEVEL == 'e')
	{
		SIZE_OF_BOARD = 10;
		MINE_COUNT = 10;
		LENGTH_OF_BOARD = SIZE_OF_BOARD*SIZE_OF_BOARD;
		visited_till_now = 0;
		max_visitable = SIZE_OF_BOARD*SIZE_OF_BOARD - MINE_COUNT;
	}
	else if (DIFFICULTY_LEVEL == 'm')
	{
		SIZE_OF_BOARD = 18;
		LENGTH_OF_BOARD = SIZE_OF_BOARD*SIZE_OF_BOARD;
		MINE_COUNT = 40;
		visited_till_now = 0;
		max_visitable = SIZE_OF_BOARD*SIZE_OF_BOARD - MINE_COUNT;
	}
	else if (DIFFICULTY_LEVEL == 'h')
	{
		SIZE_OF_BOARD = 24;
		visited_till_now = 0;
		LENGTH_OF_BOARD = SIZE_OF_BOARD*SIZE_OF_BOARD;
		max_visitable = SIZE_OF_BOARD*SIZE_OF_BOARD - MINE_COUNT;
		MINE_COUNT = 99;
	}
	else 
	{
		cout << "Please enter a valid Difficulty Level.";
		getDifficultyLevel();
	}
}

void printBoardCondition()
{
	cout << "PRESENT BOARD CONDITION" << endl << "::::::" << endl;
	cout << "   ";
	for (int i=0; i<SIZE_OF_BOARD; i++)
	{
		cout << i%10  << " ";
	}
	cout << endl;
	for (int i=0; i<SIZE_OF_BOARD ; i++)
	{
		cout << i%10 << "  ";
		for (int j=0 ; j<SIZE_OF_BOARD; j++)
		{
			cout << *(realCondition + i*SIZE_OF_BOARD + j) << " ";
		}
		cout << endl;
	}
}

void printPlayerGameScreen()
{
	cout << "PLAYER GAME SCREEN" << endl << "::::::" << endl;
	cout << "   ";
	for (int i=0; i<SIZE_OF_BOARD; i++)
	{
		cout << i%10  << " ";
	}
	cout << endl;
	for (int i=0; i<SIZE_OF_BOARD ; i++)
	{
		cout << i%10 << "  ";
		for (int j=0 ; j<SIZE_OF_BOARD; j++)
		{
			cout << *(playerCondition + i*SIZE_OF_BOARD + j) << " ";
		}
		cout << endl;
	}	
}

void ClickOnSquare()
{
	//click is between 0 and SIZE_OF_BOARD-1
	cout << "Enter Your Click :: \"row col f/c\" "<< endl;
	cin >> currentClickRow >>currentClickCol >> currentClickRL;
	if (currentClickRow >= SIZE_OF_BOARD || currentClickCol >= SIZE_OF_BOARD || currentClickRow <0 || currentClickCol <0 || (currentClickRL != 'f' && currentClickRL != 'c'))
	{
		cout << "WRONG CLICK" << endl;
		ClickOnSquare();
	}
}

char getBoxState(int row, int col)
{
	return *(realCondition + row * SIZE_OF_BOARD + col);
}

void setBoxState(char state, int row, int col)
{
	*(realCondition + row * SIZE_OF_BOARD + col) = state;
}

void addMines()
{	
	set <int> already_in;
	srand(time(0));
	for (int var1=0; var1<MINE_COUNT; )
	{
		int mine_index =  rand()%LENGTH_OF_BOARD;
		if (already_in.find(mine_index)==already_in.end())
		{
			already_in.insert(mine_index);
			setMine(mine_index);
			var1++;
		}
		else continue;
	}

}


int blober(int row, int col)
{
	// -1 bomb
	// 0 already visited
	// 2 out of bounds 
	// 1 number
	// cout << "row: " << row << " col: " << col << endl;
	if (row < 0 || row >= SIZE_OF_BOARD || col < 0 || col >= SIZE_OF_BOARD)
	{
		// cout << "boom" << endl;
		return 2;
	}
	else if (*(visited + row * SIZE_OF_BOARD + col) == true)
	{
		return 0;
	}
	else if (*(realCondition + row * SIZE_OF_BOARD + col)>='1' && *(realCondition + row * SIZE_OF_BOARD + col)<='9')
	{
		// cout << "boom2" << endl;
		visited_till_now++;
		*(visited + row * SIZE_OF_BOARD + col) = true;	
		*(playerCondition + row * SIZE_OF_BOARD + col) = *(realCondition + row * SIZE_OF_BOARD + col);
		return 1;
	}
	else if (*(realCondition + row * SIZE_OF_BOARD + col) == '-')
	{
		// cout << "boom3" << endl;
		visited_till_now++;
		*(playerCondition + row * SIZE_OF_BOARD + col) = *(realCondition + row * SIZE_OF_BOARD + col);
		*(visited + row * SIZE_OF_BOARD + col) = true;
		// printPlayerGameScreen();
		blober(row+1, col);
		blober(row-1, col);
		blober(row, col+1);
		blober(row, col-1);
		blober(row+1, col+1);
		blober(row-1, col-1);
		blober(row+1, col-1);
		blober(row-1, col+1);
	}
	else
	{
		*(playerCondition + row * SIZE_OF_BOARD + col) = *(realCondition + row * SIZE_OF_BOARD + col);
		cout << "GAME OVER" << endl;
		*(visited + row * SIZE_OF_BOARD + col) = true;
		return -1;
	}
}


int main()
{
	cout << "MINESWEEPER" << endl << "::::" << endl;
	// cout << "Enter Size size of board: ";
	// cin >> SIZE_OF_BOARD;
	getDifficultyLevel();
	realCondition = (char *)malloc(sizeof(char)*LENGTH_OF_BOARD);
	playerCondition = (char *)malloc(sizeof(char)*LENGTH_OF_BOARD);
	visited = (bool *)malloc(sizeof(char)*LENGTH_OF_BOARD);
	for (int i=0; i<SIZE_OF_BOARD ; i++)
	{
		for (int j=0 ; j<SIZE_OF_BOARD; j++)
		{
			 *(realCondition + i*SIZE_OF_BOARD + j) = '-';
			 *(playerCondition + i*SIZE_OF_BOARD + j) = '.';
			 *(visited + i*SIZE_OF_BOARD + j) = false;
		}
	}
	addMines();


	printBoardCondition();
	

	printPlayerGameScreen();
	
	int status = 0;
	while(status != -1)
	{
		ClickOnSquare();
		if (currentClickRL == 'c')
		{
			status = blober(currentClickRow, currentClickCol);
			printPlayerGameScreen();
			if (visited_till_now == max_visitable)
			{
				cout << "GAME COMPLETE" << endl << "YOU WIN" << endl;
				break;
			}	
		}
		else 
		{
			*(playerCondition + currentClickRow * SIZE_OF_BOARD + currentClickCol) = '@';
			printPlayerGameScreen();
		}
		
	}
	free(realCondition);
	free(playerCondition);
	free(visited);

}


void setMine(int mine_index)
{
	*(realCondition + mine_index) = '*';
	int row_index = mine_index / SIZE_OF_BOARD;
	int col_index = mine_index % SIZE_OF_BOARD;
	if (row_index >0 && row_index < SIZE_OF_BOARD-1 && col_index >0 && col_index < SIZE_OF_BOARD-1)
	{
		if (getBoxState(row_index+1, col_index) == '-')
			setBoxState('1', row_index + 1, col_index);
		else if (getBoxState(row_index + 1, col_index) >= '1' && getBoxState(row_index + 1, col_index) <='9')
			setBoxState(getBoxState(row_index+1, col_index) + 1, row_index + 1, col_index);

		if (getBoxState(row_index -1, col_index) == '-')
			setBoxState('1', row_index -1, col_index);
		else if (getBoxState(row_index -1, col_index) >= '1' && getBoxState(row_index -1, col_index) <='9')
			setBoxState(getBoxState(row_index -1, col_index) + 1, row_index -1, col_index);

		if (getBoxState(row_index, col_index+1) == '-')
			setBoxState('1', row_index, col_index+1);
		else if (getBoxState(row_index, col_index+1) >= '1' && getBoxState(row_index, col_index+1) <='9')
			setBoxState(getBoxState(row_index, col_index+1) + 1, row_index, col_index+1);
		
		if (getBoxState(row_index, col_index-1) == '-')
			setBoxState('1', row_index, col_index-1);
		else if (getBoxState(row_index, col_index-1) >= '1' && getBoxState(row_index, col_index-1) <='9')
			setBoxState(getBoxState(row_index, col_index-1) + 1, row_index, col_index-1);

		if (getBoxState(row_index-1, col_index-1) == '-')
			setBoxState('1', row_index-1, col_index-1);
		else if (getBoxState(row_index-1, col_index-1) >= '1' && getBoxState(row_index-1, col_index-1) <='9')
			setBoxState(getBoxState(row_index-1, col_index-1) + 1, row_index-1, col_index-1);

		if (getBoxState(row_index+1, col_index+1) == '-')
			setBoxState('1', row_index+1, col_index+1);
		else if (getBoxState(row_index+1, col_index+1) >= '1' && getBoxState(row_index+1, col_index+1) <='9')
			setBoxState(getBoxState(row_index+1, col_index+1) + 1, row_index+1, col_index+1);

		if (getBoxState(row_index-1, col_index+1) == '-')
			setBoxState('1', row_index-1, col_index+1);
		else if (getBoxState(row_index-1, col_index+1) >= '1' && getBoxState(row_index-1, col_index+1) <='9')
			setBoxState(getBoxState(row_index-1, col_index+1) + 1, row_index-1, col_index+1);

		if (getBoxState(row_index+1, col_index-1) == '-')
			setBoxState('1', row_index+1, col_index-1);
		else if (getBoxState(row_index+1, col_index-1) >= '1' && getBoxState(row_index+1, col_index-1) <='9')
			setBoxState(getBoxState(row_index+1, col_index-1) + 1, row_index+1, col_index-1);
	}
	else if (row_index ==0 && col_index == 0)
	{
		if (getBoxState(row_index+1, col_index) == '-')
			setBoxState('1', row_index + 1, col_index);
		else if (getBoxState(row_index + 1, col_index) >= '1' && getBoxState(row_index + 1, col_index) <='9')
			setBoxState(getBoxState(row_index+1, col_index) + 1, row_index + 1, col_index);

		if (getBoxState(row_index, col_index+1) == '-')
			setBoxState('1', row_index, col_index+1);
		else if (getBoxState(row_index, col_index+1) >= '1' && getBoxState(row_index, col_index+1) <='9')
			setBoxState(getBoxState(row_index, col_index+1) + 1, row_index, col_index+1);
		
		if (getBoxState(row_index+1, col_index+1) == '-')
			setBoxState('1', row_index+1, col_index+1);
		else if (getBoxState(row_index+1, col_index+1) >= '1' && getBoxState(row_index+1, col_index+1) <='9')
			setBoxState(getBoxState(row_index+1, col_index+1) + 1, row_index+1, col_index+1);
	}
	else if (row_index == SIZE_OF_BOARD-1 && col_index == 0)
	{
		if (getBoxState(row_index -1, col_index) == '-')
			setBoxState('1', row_index -1, col_index);
		else if (getBoxState(row_index -1, col_index) >= '1' && getBoxState(row_index -1, col_index) <='9')
			setBoxState(getBoxState(row_index -1, col_index) + 1, row_index -1, col_index);

		if (getBoxState(row_index, col_index+1) == '-')
			setBoxState('1', row_index, col_index+1);
		else if (getBoxState(row_index, col_index+1) >= '1' && getBoxState(row_index, col_index+1) <='9')
			setBoxState(getBoxState(row_index, col_index+1) + 1, row_index, col_index+1);
		
		if (getBoxState(row_index-1, col_index+1) == '-')
			setBoxState('1', row_index-1, col_index+1);
		else if (getBoxState(row_index-1, col_index+1) >= '1' && getBoxState(row_index-1, col_index+1) <='9')
			setBoxState(getBoxState(row_index-1, col_index+1) + 1, row_index-1, col_index+1);
	}
	else if (row_index == SIZE_OF_BOARD-1 && col_index == SIZE_OF_BOARD-1)
	{
		if (getBoxState(row_index -1, col_index) == '-')
			setBoxState('1', row_index -1, col_index);
		else if (getBoxState(row_index -1, col_index) >= '1' && getBoxState(row_index -1, col_index) <='9')
			setBoxState(getBoxState(row_index -1, col_index) + 1, row_index -1, col_index);

		if (getBoxState(row_index, col_index-1) == '-')
			setBoxState('1', row_index, col_index-1);
		else if (getBoxState(row_index, col_index-1) >= '1' && getBoxState(row_index, col_index-1) <='9')
			setBoxState(getBoxState(row_index, col_index-1) + 1, row_index, col_index-1);

		if (getBoxState(row_index-1, col_index-1) == '-')
			setBoxState('1', row_index-1, col_index-1);
		else if (getBoxState(row_index-1, col_index-1) >= '1' && getBoxState(row_index-1, col_index-1) <='9')
			setBoxState(getBoxState(row_index-1, col_index-1) + 1, row_index-1, col_index-1);
	}
	else if (row_index == 0 && col_index == SIZE_OF_BOARD-1)
	{
			if (getBoxState(row_index+1, col_index) == '-')
			setBoxState('1', row_index + 1, col_index);
		else if (getBoxState(row_index + 1, col_index) >= '1' && getBoxState(row_index + 1, col_index) <='9')
			setBoxState(getBoxState(row_index+1, col_index) + 1, row_index + 1, col_index);

		if (getBoxState(row_index, col_index-1) == '-')
			setBoxState('1', row_index, col_index-1);
		else if (getBoxState(row_index, col_index-1) >= '1' && getBoxState(row_index, col_index-1) <='9')
			setBoxState(getBoxState(row_index, col_index-1) + 1, row_index, col_index-1);

		if (getBoxState(row_index+1, col_index-1) == '-')
			setBoxState('1', row_index+1, col_index-1);
		else if (getBoxState(row_index+1, col_index-1) >= '1' && getBoxState(row_index+1, col_index-1) <='9')
			setBoxState(getBoxState(row_index+1, col_index-1) + 1, row_index+1, col_index-1);
	}
	else if (row_index == 0)
	{
			if (getBoxState(row_index+1, col_index) == '-')
			setBoxState('1', row_index + 1, col_index);
		else if (getBoxState(row_index + 1, col_index) >= '1' && getBoxState(row_index + 1, col_index) <='9')
			setBoxState(getBoxState(row_index+1, col_index) + 1, row_index + 1, col_index);

		
		if (getBoxState(row_index, col_index+1) == '-')
			setBoxState('1', row_index, col_index+1);
		else if (getBoxState(row_index, col_index+1) >= '1' && getBoxState(row_index, col_index+1) <='9')
			setBoxState(getBoxState(row_index, col_index+1) + 1, row_index, col_index+1);
		
		if (getBoxState(row_index, col_index-1) == '-')
			setBoxState('1', row_index, col_index-1);
		else if (getBoxState(row_index, col_index-1) >= '1' && getBoxState(row_index, col_index-1) <='9')
			setBoxState(getBoxState(row_index, col_index-1) + 1, row_index, col_index-1);

		
		if (getBoxState(row_index+1, col_index+1) == '-')
			setBoxState('1', row_index+1, col_index+1);
		else if (getBoxState(row_index+1, col_index+1) >= '1' && getBoxState(row_index+1, col_index+1) <='9')
			setBoxState(getBoxState(row_index+1, col_index+1) + 1, row_index+1, col_index+1);

		
		if (getBoxState(row_index+1, col_index-1) == '-')
			setBoxState('1', row_index+1, col_index-1);
		else if (getBoxState(row_index+1, col_index-1) >= '1' && getBoxState(row_index+1, col_index-1) <='9')
			setBoxState(getBoxState(row_index+1, col_index-1) + 1, row_index+1, col_index-1);
	
	}
	else if (col_index == 0)
	{
			if (getBoxState(row_index+1, col_index) == '-')
			setBoxState('1', row_index + 1, col_index);
		else if (getBoxState(row_index + 1, col_index) >= '1' && getBoxState(row_index + 1, col_index) <='9')
			setBoxState(getBoxState(row_index+1, col_index) + 1, row_index + 1, col_index);

		if (getBoxState(row_index -1, col_index) == '-')
			setBoxState('1', row_index -1, col_index);
		else if (getBoxState(row_index -1, col_index) >= '1' && getBoxState(row_index -1, col_index) <='9')
			setBoxState(getBoxState(row_index -1, col_index) + 1, row_index -1, col_index);

		if (getBoxState(row_index, col_index+1) == '-')
			setBoxState('1', row_index, col_index+1);
		else if (getBoxState(row_index, col_index+1) >= '1' && getBoxState(row_index, col_index+1) <='9')
			setBoxState(getBoxState(row_index, col_index+1) + 1, row_index, col_index+1);
		
		
		if (getBoxState(row_index+1, col_index+1) == '-')
			setBoxState('1', row_index+1, col_index+1);
		else if (getBoxState(row_index+1, col_index+1) >= '1' && getBoxState(row_index+1, col_index+1) <='9')
			setBoxState(getBoxState(row_index+1, col_index+1) + 1, row_index+1, col_index+1);

		if (getBoxState(row_index-1, col_index+1) == '-')
			setBoxState('1', row_index-1, col_index+1);
		else if (getBoxState(row_index-1, col_index+1) >= '1' && getBoxState(row_index-1, col_index+1) <='9')
			setBoxState(getBoxState(row_index-1, col_index+1) + 1, row_index-1, col_index+1);
	}
	else if (row_index == SIZE_OF_BOARD-1)
	{

		if (getBoxState(row_index -1, col_index) == '-')
			setBoxState('1', row_index -1, col_index);
		else if (getBoxState(row_index -1, col_index) >= '1' && getBoxState(row_index -1, col_index) <='9')
			setBoxState(getBoxState(row_index -1, col_index) + 1, row_index -1, col_index);

		if (getBoxState(row_index, col_index+1) == '-')
			setBoxState('1', row_index, col_index+1);
		else if (getBoxState(row_index, col_index+1) >= '1' && getBoxState(row_index, col_index+1) <='9')
			setBoxState(getBoxState(row_index, col_index+1) + 1, row_index, col_index+1);
		
		if (getBoxState(row_index, col_index-1) == '-')
			setBoxState('1', row_index, col_index-1);
		else if (getBoxState(row_index, col_index-1) >= '1' && getBoxState(row_index, col_index-1) <='9')
			setBoxState(getBoxState(row_index, col_index-1) + 1, row_index, col_index-1);

		if (getBoxState(row_index-1, col_index-1) == '-')
			setBoxState('1', row_index-1, col_index-1);
		else if (getBoxState(row_index-1, col_index-1) >= '1' && getBoxState(row_index-1, col_index-1) <='9')
			setBoxState(getBoxState(row_index-1, col_index-1) + 1, row_index-1, col_index-1);

		
		if (getBoxState(row_index-1, col_index+1) == '-')
			setBoxState('1', row_index-1, col_index+1);
		else if (getBoxState(row_index-1, col_index+1) >= '1' && getBoxState(row_index-1, col_index+1) <='9')
			setBoxState(getBoxState(row_index-1, col_index+1) + 1, row_index-1, col_index+1);

		
	}
	else if (col_index == SIZE_OF_BOARD-1)
	{
		if (getBoxState(row_index+1, col_index) == '-')
			setBoxState('1', row_index + 1, col_index);
		else if (getBoxState(row_index + 1, col_index) >= '1' && getBoxState(row_index + 1, col_index) <='9')
			setBoxState(getBoxState(row_index+1, col_index) + 1, row_index + 1, col_index);

		if (getBoxState(row_index -1, col_index) == '-')
			setBoxState('1', row_index -1, col_index);
		else if (getBoxState(row_index -1, col_index) >= '1' && getBoxState(row_index -1, col_index) <='9')
			setBoxState(getBoxState(row_index -1, col_index) + 1, row_index -1, col_index);

		if (getBoxState(row_index, col_index-1) == '-')
			setBoxState('1', row_index, col_index-1);
		else if (getBoxState(row_index, col_index-1) >= '1' && getBoxState(row_index, col_index-1) <='9')
			setBoxState(getBoxState(row_index, col_index-1) + 1, row_index, col_index-1);

		if (getBoxState(row_index-1, col_index-1) == '-')
			setBoxState('1', row_index-1, col_index-1);
		else if (getBoxState(row_index-1, col_index-1) >= '1' && getBoxState(row_index-1, col_index-1) <='9')
			setBoxState(getBoxState(row_index-1, col_index-1) + 1, row_index-1, col_index-1);

		if (getBoxState(row_index+1, col_index-1) == '-')
			setBoxState('1', row_index+1, col_index-1);
		else if (getBoxState(row_index+1, col_index-1) >= '1' && getBoxState(row_index+1, col_index-1) <='9')
			setBoxState(getBoxState(row_index+1, col_index-1) + 1, row_index+1, col_index-1);
	
	}


}