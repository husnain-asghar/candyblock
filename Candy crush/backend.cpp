#include<iostream>
#include<time.h>
#include "backend.h";
#include"frontend.h";
#include<windows.h>
#include"variables.h";
#include<fstream>
#include<sstream>
using namespace std;

//                   RED=11,Yellow=17, Green=19, Blue=7,Orange=13;
//horizontal_Striped RED=22,Yellow=34,Green=38,Blue=14,Orange=26;
//vertical_Striped   RED=33,Yellow=51,Green=57,Blue=21,Orange=39;
//wrapped            RED=44,Yellow=68,Green=76,Blue=28,Orange=52;
//Candy Bomb=999;

void display(int grid[row][column])
{
	for (int k = 0; k < row; k++)
	{
		for (int x = 0; x < column; x++)
		{
			cout << grid[k][x] << " ";
		}
		cout << endl;
	}
}

void shift(int grid[row][column])
{
	int x = 0;
	while (x < 82)
	{
		for (int j = column - 1; j >= 0; j--)
		{
			for (int i = row - 1; i >= 0; i--)
			{
				if (grid[i][j] == -3)
				{
					if (i == 0)
						grid[i][j] = -1;
					else
					{
						if (grid[i - 1][j] !=-3 || grid[i - 1][j] == -1)
						{
							grid[i][j] = grid[i - 1][j];
							grid[i - 1][j] = -3;
						}
					}
				}
			}
		}

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				if (grid[i][j] != 0)
				{
					x++;
				}
				else if (grid[i][j] == -3) 
				{
					x = 0;
				}
			}
		}
	}
}

void initialize(int grid[row][column])
{
	srand(time(0));

	int x;
	for (int f = 0; f < 90; f++)
	{
		x = rand() % 5;
		initial[f] = simple_candies[x];
	}
	for (int f = 90; f < 94; f++)
	{
		x = rand() % 5;
		initial[f] = horizontal_striped[x];
	}
	for (int f = 94; f < 98; f++)
	{
		x = rand() % 5;
		initial[f] = vertical_striped[x];
	}
	for (int f = 98; f < 99; f++)
	{
		x = rand() % 5;
		initial[f] = wrapped_candy[x];
	}
	
	initial[99] = 999;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			int k = rand() % 100;
			grid[i][j] = initial[k];
		}
	}
}

void refill(int grid[row][column])
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (grid[i][j] == -1)
			{
				int z = rand() % 100;
				grid[i][j] = initial[z];
			}
		}
	}
}

int initialMatchCheck(int grid[row][column])
{
	//horizontal check 
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			int x = grid[i][j];
			if (x % 11 == 0)
				x = 11;
			else if (x % 17 == 0)
				x = 17;
			else if (x % 19 == 0)
				x = 19;
			else if (x % 7 == 0)
				x = 7;
			else if (x % 13 == 0)
				x = 13;

			if (grid[i][j] % x == grid[i][j + 1] % x && grid[i][j + 1] % x == grid[i][j + 2] % x)
			{
				grid[i][j] = -1;
				grid[i][j + 1] = -1;
				grid[i][j + 2] = -1;
				return 0;
			}
		}
	}// horizontal end

	//vertical check
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < column; j++)
		{
			int x = grid[i][j];
			if (x % 11 == 0)
				x = 11;
			else if (x % 17 == 0)
				x = 17;
			else if (x % 19 == 0)
				x = 19;
			else if (x % 7 == 0)
				x = 7;
			else if (x % 13 == 0)
				x = 13;

			if (grid[i][j] % x == grid[i + 1][j] % x && grid[i + 1][j] % x == grid[i + 2][j] % x)
			{
				grid[i][j] = -1;
				grid[i + 1][j] = -1;
				grid[i + 2][j] = -1;
				return 0;
			}
		}
	}
	//vertical end
	return -1;
}


void candybomb(int grid[][column])
{
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int x = grid[i][j];
			if (x % 11 == 0)
				x = 11; //Red candy
			else if (x % 17 == 0)
				x = 17;  //Yellow candy
			else if (x % 19 == 0)
				x = 19;  //Green candy
			else if (x % 7 == 0)
				x = 7;  //Blue candy
			else if (x % 13 == 0)
				x = 13;  //Orange candy 
				
			if (grid[i][j] % x == grid[i][j + 1] % x && grid[i][j + 1]% x == grid[i][j + 2] % x && grid[i][j + 2] % x == grid[i][j + 3]% x && grid[i][j + 3] % x == grid[i][j + 4]% x)
			{
				if (grid[i][j] != -3)
				{
					if (grid[i][j] / x == 3)
					{
						for (int k = 0; k < row; k++)  //vertical stripe elimination
						{
							grid[k][j] = -3;
						}
					}
					if (grid[i][j + 1] / x == 3)
					{
						for (int k = 0; k < row; k++)  //vertical stripe elimination
						{
							grid[k][j + 1] = -3;
						}
					}
					if (grid[i][j + 2] / x == 3)
					{
						for (int k = 0; k < row; k++)  //vertical stripe elimination
						{
							grid[k][j + 2] = -3;
						}
					}
					if (grid[i][j + 3] / x == 3)
					{
						for (int k = 0; k < row; k++)  //vertical stripe elimination
						{
							grid[k][j + 3] = -3;
						}
					}
					if (grid[i][j + 4] / x == 3)
					{
						for (int k = 0; k < row; k++)  //vertical stripe elimination
						{
							grid[k][j + 4] = -3;
						}
					}
					if (grid[i][j] / x == 2 || grid[i][j + 1] / x == 2 || grid[i][j + 2] / x == 2 || grid[i][j + 3] / x == 2 || grid[i][j + 4] / x == 2)
					{
						for (int k = 0; k < column; k++)  //horizontal stripe elimination
						{
							grid[i][k] = -3;
						}
					}
					grid[i][j] = -3;
					grid[i][j + 1] = -3;
					grid[i][j + 2] = 999;
					grid[i][j + 3] = -3;
					grid[i][j + 4] = -3;
				}
		}
	}
			
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			int x = grid[i][j];
			if (x % 11 == 0)
				x = 11; //Red 
			else if (x % 17 == 0)
				x = 17;  //Yellow 
			else if (x % 19 == 0)
				x = 19;  //Green
			else if (x % 7 == 0)
				x = 7;  //Blue
			else if (x % 13 == 0)
				x = 13;  //Orange
			if (grid[i][j] % x == grid[i + 1][j]% x && grid[i + 1][j]% x == grid[i + 2][j]% x && grid[i + 2][j]% x == grid[i + 3][j]% x && grid[i + 3][j]% x == grid[i + 4][j]% x)
			{
				if (grid[i][j] != -3)
				{
					if (grid[i][j] / x == 3 || grid[i + 1][j] / x == 3 || grid[i + 2][j] / x == 3 || grid[i + 3][j] / x == 3 || grid[i + 4][j] / x == 3)
					{
						for (int k = 0; k < row; k++)  //vertical stripe elimination
						{
							grid[k][j] = -3;
						}
					}
					if (grid[i][j] / x == 2)
					{
						for (int k = 0; k < column; k++)  //horizontal stripe elimination
						{
							grid[i][k] = -3;
						}
					}
					if (grid[i + 1][j] / x == 2)
					{
						for (int k = 0; k < column; k++)  //horizontal stripe elimination
						{
							grid[i + 1][k] = -3;
						}
					}
					if (grid[i + 2][j] / x == 2)
					{
						for (int k = 0; k < column; k++)  //horizontal stripe elimination
						{
							grid[i + 2][k] = -3;
						}
					}
					if (grid[i + 3][j] / x == 2)
					{
						for (int k = 0; k < column; k++)  //horizontal stripe elimination
						{
							grid[i + 3][k] = -3;
						}
					}
					if (grid[i + 4][j] / x == 2)
					{
						for (int k = 0; k < column; k++)  //horizontal stripe elimination
						{
							grid[i + 4][k] = -3;
						}
					}
					grid[i][j] = -3;
					grid[i + 1][j] = -3;
					grid[i + 2][j] = 999;
					grid[i + 3][j] = -3;
					grid[i + 4][j] = -3;
	
				}
			}
			}
		}
	}
}

void swap(int grid[][column],int a1,int b1,int a2,int b2)
{
	if(a1!=-1 && b1!=-1 && a2!=-1 && b2!=-1)
	{
		if ((a2 == a1 + 1 && b2 == b1) || ( a2 == a1 - 1 && b2 == b1) || ( a2 == a1 && b2 == b1 + 1)  || (a2 == a1 && b2 == b1 - 1))
		{
			int temp = grid[a1][b1];
			grid[a1][b1] = grid[a2][b2];
			grid[a2][b2] = temp;	
			eliminatecolorbomb(grid, a1, b1, a2, b2);
			score(scoreGrid, grid);
            copyOfGrid(scoreGrid, grid);

			wrappedPlusStriped(grid, a1, b1, a2, b2);
			score(scoreGrid, grid);
            copyOfGrid(scoreGrid, grid);

			eliminateWrappedPlusWrapped(grid, a1, b1, a2, b2);
			score(scoreGrid, grid);
            copyOfGrid(scoreGrid, grid);

			x1 = -1;
			Y1 = -1;
			x2 = -1;
			y2 = -1;
			turns--;
		}
		else
		{
			x1 = -1;
			Y1 = -1;
			x2 = -1;
			y2 = -1;
		}
	}
}

void simplythree(int grid[][column])
{
	//horizontal check for all same type of candies
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			int x = grid[i][j];
			if (x % 11 == 0)
				x = 11; //Red
			else if (x % 17 == 0)
				x = 17;  //Yellow
			else if (x % 19 == 0)
				x = 19;  //Green
			else if (x % 7 == 0)
				x = 7;  //Blue
			else if (x % 13 == 0)
				x = 13;  //Orange


			if (grid[i][j] % x == grid[i][j + 1] % x && grid[i][j + 1] % x == grid[i][j + 2] % x)
			{	
				if (grid[i][j] != -3)
				{
					if (grid[i][j] / x == 3)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < row; k++)  //vertical stripe elimination
						{
							grid[k][j] = -3;
						}
					}
					if (grid[i][j + 1] / x == 3)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < row; k++)  //vertical stripe elimination
						{
							grid[k][j + 1] = -3;
						}
					}
					if (grid[i][j + 2] / x == 3)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < row; k++)  //vertical stripe elimination
						{
							grid[k][j + 2] = -3;
						}
					}
					if (grid[i][j] / x == 2 || grid[i][j + 1] / x == 2 || grid[i][j + 2] / x == 2)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < column; k++)  //horizontal stripe elimination
						{
							grid[i][k] = -3;
						}
					}
					eliminatewrappedcandy(grid);
					grid[i][j] = -3;
					grid[i][j + 1] = -3;
					grid[i][j + 2] = -3;
				}
			}
		}
	}// horizontal end

	//vertical check of all same type of candies
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < column; j++)
		{
			int x = grid[i][j];
			if (x % 11 == 0)
				x = 11; //Red
			else if (x % 17 == 0)
				x = 17;  //Yellow
			else if (x % 19 == 0)
				x = 19;  //Green
			else if (x % 7 == 0)
				x = 7;  //Blue
			else if (x % 13 == 0)
				x = 13;  //Orange

			if (grid[i][j] % x == grid[i + 1][j] % x && grid[i + 1][j] % x == grid[i + 2][j] % x)
			{
				if (grid[i][j] != -3)
				{
					if (grid[i][j] / x == 3 || grid[i + 1][j] / x == 3 || grid[i + 2][j] / x == 3)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < row; k++)  //vertical stripe elimination
						{
							grid[k][j] = -3;
						}
					}
					if (grid[i][j] / x == 2)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < column; k++)  //horizontal stripe elimination
						{
							grid[i][k] = -3;
						}
					}
					if (grid[i + 1][j] / x == 2)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < column; k++)  //horizontal stripe elimination
						{
							grid[i + 1][k] = -3;
						}
					}
					if (grid[i + 2][j] / x == 2)
					{
						eliminatewrappedcandy(grid);

						for (int k = 0; k < column; k++)  //horizontal stripe elimination
						{
							grid[i + 2][k] = -3;
						}
					}
					eliminatewrappedcandy(grid);
					grid[i][j] = -3;
					grid[i + 1][j] = -3;
					grid[i + 2][j] = -3;
				}
			}
		}
	}
}// end of function

void eliminatecolorbomb(int grid[row][column], int a1, int b1, int a2, int b2)
{
	if (grid[a1][b1] == 999 && grid[a2][b2] == 999)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				grid[i][j] = -3;
			}
		}
	}

	int x;
	if (grid[a1][b1] == 999)
	{
		x = grid[a2][b2];
    }
	else 
	{
		x = grid[a1][b1];
	}
	if (x % 11 == 0)
		x = 11; //Red candy
	else if (x % 17 == 0)
		x = 17;  //Yellow candy
	else if (x % 19 == 0)
		x = 19;  //Green candy
	else if (x % 7 == 0)
		x = 7;  //Blue candy
	else if (x % 13 == 0)
		x = 13;  //Orange wrapped candy 

	if(grid[a1][b1]== 999 || grid[a2][b2]== 999)
	{
		if(grid[a1][b1]/x==1 || grid[a2][b2]/x==1)
		{
			for(int i=0;i<row;i++)
			{
				for(int j=0;j<column;j++)
				{
					if(grid[i][j] % x == 0)
					{
						if(grid[i][j] / x == 3)
						{
							for(int k=0;k<row;k++)
							{
								grid[k][j] = -3;
							}
						}
						if(grid[i][j] / x == 2)
						{
							for(int k=0;k<column;k++)
							{
								grid[i][k] = -3;
							}
						}					
						grid[i][j] = -3;
						grid[a1][b1] = -3;
						grid[a2][b2] = -3;
					}
				}
			}
		}
	}
	if(grid[a1][b1]== 999 || grid[a2][b2]== 999) //colorbomb plus horizontal striped candy
	{
		if(grid[a1][b1]/x==2 || grid[a2][b2]/x==2)
		{
			for(int i=0;i<row;i++)
			{
				for(int j=0;j<column;j++)
				{
					if(grid[i][j] % x == 0)
					{
						grid[i][j] = x*2;
						for (int k = 0; k < row; k++)
						{
							for (int l = 0; l < column; l++)
							{
								if (grid[k][l] == x * 2)
								{
									for (int m = 0; m < column; m++)
									{
										grid[k][m] = -3;
										grid[a1][b1] = -3;
										grid[a2][b2] = -3;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if(grid[a1][b1]== 999 || grid[a2][b2]== 999) //colorbomb plus vertical striped candy
	{
		if(grid[a1][b1]/x==3 || grid[a2][b2]/x==3)
		{
			for(int i=0;i<row;i++)
			{
				for(int j=0;j<column;j++)
				{
					if(grid[i][j] % x == 0)
					{
						grid[i][j] = x*3;
						for (int k = 0; k < row; k++)
						{
							for (int l = 0; l < column; l++)
							{
								if (grid[k][l] == x * 3)
								{
									for (int m = 0; m < row; m++)
									{
										grid[m][l] = -3;
										grid[a1][b1] = -3;
										grid[a2][b2] = -3;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if (grid[a1][b1] == 999 || grid[a2][b2] == 999) //colorbomb plus wrapped candy
	{	
		if (grid[a1][b1] / x == 4 || grid[a2][b2] / x == 4)
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					if (grid[i][j] % x == 0)
					{
						grid[i][j] = x * 4;
						for (int k = 0; k < row; k++)
						{
							for (int l = 0; l < column; l++)
							{
								if (grid[k][l] == x * 4)
								{
									eliminatethreeBythree(k, l);
								}
							}
						}
					}
				}
			}
		}
	}
}

void wrappedcandy(int grid[][column]) //checks for formation of wrapped candy and forms it
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			int  w = grid[i][j]; //wrapped candy being formed
			if (w % 11 == 0)
				w = 44; //Red wrapped candy
			else if (w % 17 == 0)
				w = 68;  //Yellow wrapped candy
			else if (w % 19 == 0)
				w = 76;  //Green wrapped candy
			else if (w % 7 == 0)
				w = 28;  //Blue wrapped candy
			else if (w % 13 == 0)
				w = 52;  //Orange wrapped candy 

			int x = grid[i][j];
			if (x % 11 == 0)
				x = 11; //Red wrapped candy
			else if (x % 17 == 0)
				x = 17;  //Yellow wrapped candy
			else if (x % 19 == 0)
				x = 19;  //Green wrapped candy
			else if (x % 7 == 0)
				x = 7;  //Blue wrapped candy
			else if (x % 13 == 0)
				x = 13;  //Orange wrapped candy   

			if (grid[i][j] % x == grid[i][j + 1] % x && grid[i][j + 1] % x == grid[i][j + 2] % x && grid[i][j + 2] % x == grid[i + 1][j] % x && grid[i + 1][j] % x == grid[i + 2][j] % x)
			{
				if (grid[i][j] / x == 3 || grid[i + 1][j] / x == 3 || grid[i + 2][j] / x == 3)
					{eliminatewrappedcandy(grid);
						for (int k = 0; k < row; k++) //vertical stripe elimination
						{
							grid[k][j] = -3;
						}
					}

				if (grid[i][j + 1] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j + 1] = -3;
					}
				}

				if (grid[i][j + 2] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j + 2] = -3;
					}
				}
				
				if (grid[i][j] / x == 2 || grid[i][j + 1] / x == 2 || grid[i][j + 2] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i][k] = -3;
					}
				}

				if (grid[i + 1][j] / x == 2) //horizontal stripe elimination
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)
					{
						grid[i + 1][k] = -3;
					}
				}

				if (grid[i + 2][j] / x == 2)//horizontal stripe elimination
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)
					{
						grid[i + 2][k] = -3;
					}
				}
				eliminatewrappedcandy(grid);
				grid[i][j] = -3;                //    _ _
				grid[i][j + 1] = -3;            //  |
				grid[i][j + 2] = -3;            //  |   
				grid[i + 1][j] = -3;            //  |      shape
				grid[i + 2][j] = w;
			}

			if (grid[i][j] % x == grid[i + 1][j] % x && grid[i + 1][j] % x == grid[i + 2][j] % x && grid[i + 2][j] % x == grid[i + 2][j + 1] % x && grid[i + 2][j + 1] % x == grid[i + 2][j + 2] % x)
			{

				if (grid[i][j] / x == 3 || grid[i + 1][j] / x == 3 || grid[i + 2][j] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j] = -3;
					}
				}
				if (grid[i + 2][j + 1] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j + 1] = -3;
					}
				}
				if (grid[i + 2][j + 2] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j + 2] = -3;
					}
				}
				if (grid[i][j] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i][k] = -3;
					}
				}
				if (grid[i + 1][j] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i + 1][k] = -3;
					}
				}
				if (grid[i + 2][j] / x == 2 || grid[i + 2][j + 1] / x == 2 || grid[i + 2][j + 2] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i + 2][k] = -3;
					}
				}
				eliminatewrappedcandy(grid);
				grid[i][j] = -3;
				grid[i + 1][j] = -3;
				grid[i + 2][j] = w;                        //  |
				grid[i + 2][j + 1] = -3;                   //  |
				grid[i + 2][j + 2] = -3;                   //  | _ _  shape
			}

			if (grid[i][j] % x == grid[i + 1][j] % x && grid[i + 1][j] % x == grid[i + 2][j] % x && grid[i + 2][j] % x == grid[i + 1][j + 1] % x && grid[i + 1][j + 1] % x == grid[i + 1][j + 2] % x)
			{
				
				if (grid[i][j] / x == 3 || grid[i + 1][j] / x == 3 || grid[i + 2][j] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j] = -3;
					}
				}
				if (grid[i + 2][j + 1] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j + 1] = -3;
					}
				}
				if (grid[i + 2][j + 2] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j + 2] = -3;
					}
				}
				if (grid[i][j] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i][k] = -3;
					}
				}
				if (grid[i + 1][j] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i + 1][k] = -3;
					}
				}
				if (grid[i + 2][j] / x == 2 || grid[i + 2][j + 1] / x == 2 || grid[i + 2][j + 2] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i + 2][k] = -3;
					}
				}
				eliminatewrappedcandy(grid);
				grid[i][j] = -3;
				grid[i + 1][j] = -3;
				grid[i + 2][j] = w;                        //  |  
				grid[i + 1][j + 1] = -3;                   //  | - -
				grid[i + 1][j + 2] = -3;                   //  |      shape
			}

		}
	}

	for (int i = 0; i < 7; i++)
	{
		for (int j = column - 1; j > 1; j--)
		{
			int  w = grid[i][j];
			if (w % 11 == 0)
				w = 44; //Red wrapped candy
			else if (w % 17 == 0)
				w = 68;  //Yellow wrapped candy
			else if (w % 19 == 0)
				w = 76;  //Green wrapped candy
			else if (w % 7 == 0)
				w = 28;  //Blue wrapped candy
			else if (w % 13 == 0)
				w = 52;  //Orange wrapped candy

			int x = grid[i][j];
			if (x % 11 == 0)
				x = 11; //Red wrapped candy
			else if (x % 17 == 0)
				x = 17;  //Yellow wrapped candy
			else if (x % 19 == 0)
				x = 19;  //Green wrapped candy
			else if (x % 7 == 0)
				x = 7;  //Blue wrapped candy
			else if (x % 13 == 0)
				x = 13;  //Orange wrapped candy   


			if (grid[i][j] % x == grid[i + 1][j] % x && grid[i + 1][j] % x == grid[i + 2][j] % x && grid[i + 2][j] % x == grid[i][j - 1] % x && grid[i][j - 1] % x == grid[i][j - 2] % x)
			{
				
				if (grid[i][j] / x == 3 || grid[i + 1][j] / x == 3 || grid[i + 2][j] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j] = -3;
					}
				}
				if (grid[i][j - 1] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j - 1] = -3;
					}
				}
				if (grid[i][j - 2] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j - 2] = -3;
					}
				}
				if (grid[i][j] / x == 2 || grid[i][j - 1] / x == 2 || grid[i][j - 2] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i][k] = -3;
					}
				}
				if (grid[i + 1][j] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i + 1][k] = -3;
					}
				}
				if (grid[i + 2][j] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i + 2][k] = -3;
					}
				}
				eliminatewrappedcandy(grid);
				grid[i][j] = -3;
				grid[i + 1][j] = -3;                        //  _ _  
				grid[i + 2][j] = w;                         //      |
				grid[i][j - 1] = -3;                        //      |
				grid[i][j - 2] = -3;                        //      |  shape
			}

			if (grid[i][j] % x == grid[i + 1][j] % x && grid[i + 1][j] % x == grid[i + 2][j] % x && grid[i + 2][j] % x == grid[i + 2][j - 1] % x && grid[i + 2][j - 1] % x == grid[i + 2][j - 2] % x)
			{
				
				if (grid[i][j] / x == 3 || grid[i + 1][j] / x == 3 || grid[i + 2][j] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j] = -3;
					}
				}
				if (grid[i + 2][j - 1] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j - 1] = -3;
					}
				}
				if (grid[i + 2][j - 2] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j - 2] = -3;
					}
				}
				if (grid[i][j] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i][k] = -3;
					}
				}
				if (grid[i + 1][j] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i + 1][k] = -3;
					}
				}
				if (grid[i + 2][j] / x == 2 || grid[i + 2][j - 1] / x == 2 || grid[i + 2][j - 2] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i + 2][k] = -3;
					}
				}
				eliminatewrappedcandy(grid);
				grid[i][j] = -3;
				grid[i + 1][j] = -3;             //     |
				grid[i + 2][j] = w;              //     |
				grid[i + 2][j - 1] = -3;         // _ _ |  shape
				grid[i + 2][j - 2] = -3;
			}

			if (grid[i][j] % x == grid[i + 1][j] % x && grid[i + 1][j] % x == grid[i + 2][j] % x && grid[i + 2][j] % x == grid[i + 1][j - 1] % x && grid[i + 1][j - 1] % x == grid[i + 1][j - 2] % x)
			{
				
				if (grid[i][j] / x == 3 || grid[i + 1][j] / x == 3 || grid[i + 2][j] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j] = -3;
					}
				}

				if (grid[i + 1][j - 1] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j - 1] = -3;
					}
				}

				if (grid[i + 1][j - 3] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j - 2] = -3;
					}
				}
				if (grid[i][j] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i][k] = -3;
					}
				}

				if (grid[i + 1][j] / x == 2 || grid[i + 1][j - 1] / x == 2 || grid[i + 1][j - 2] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i + 1][k] = -3;
					}
				}

				if (grid[i + 2][j] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i + 2][k] = -3;
					}
				}
				eliminatewrappedcandy(grid);
				grid[i][j] = -3;
				grid[i + 1][j] = -3;
				grid[i + 2][j] = w;                         //      |  
				grid[i + 1][j - 1] = -3;                    //  - - | 
				grid[i + 1][j - 2] = -3;                    //      |   shape
			}
		}
	}

	for (int i = 0; i < 7; i++)
	{
		for (int j = 1; j < column - 2; j++)
		{
			int  w = grid[i][j];
			if (w % 11 == 0)
				w = 44; //Red wrapped candy
			else if (w % 17 == 0)
				w = 68;  //Yellow wrapped candy
			else if (w % 19 == 0)
				w = 76;  //Green wrapped candy
			else if (w % 7 == 0)
				w = 28;  //Blue wrapped candy
			else if (w % 13 == 0)
				w = 52;  //Orange wrapped candy

			int x = grid[i][j];
			if (x % 11 == 0)
				x = 11; //Red wrapped candy
			else if (x % 17 == 0)
				x = 17;  //Yellow wrapped candy
			else if (x % 19 == 0)
				x = 19;  //Green wrapped candy
			else if (x % 7 == 0)
				x = 7;  //Blue wrapped candy
			else if (x % 13 == 0)
				x = 13;  //Orange wrapped candy   

			if (grid[i][j] % x == grid[i + 1][j] % x && grid[i + 1][j] % x == grid[i + 2][j] % x && grid[i + 2][j] % x == grid[i + 2][j - 1] % x && grid[i + 2][j - 1] % x == grid[i + 2][j + 1] % x)
			{
				if (grid[i][j] / x == 3 || grid[i + 1][j] / x == 3 || grid[i + 2][j] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j] = -3;
					}
				}
				if (grid[i + 2][j - 1] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j-1] = -3;
					}
				}
				if (grid[i + 2][j + 1] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j+1] = -3;
					}
				}
				if (grid[i][j] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i][k] = -3;
					}
				}
				if (grid[i + 1][j] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i+1][k] = -3;
					}
				}
				if (grid[i + 2][j] / x == 2 || grid[i + 2][j - 1] / x == 2 || grid[i + 2][j + 1] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i+2][k] = -3;
					}
				}
				eliminatewrappedcandy(grid);
				grid[i][j] = -3;
				grid[i + 1][j] = -3;
				grid[i + 2][j] = w;                         //      |  
				grid[i + 2][j - 1] = -3;                    //      | 
				grid[i + 2][j + 1] = -3;                    //    _ | _  shape
			}

			if (grid[i][j] % x == grid[i + 1][j] % x && grid[i + 1][j] % x == grid[i + 2][j] % x && grid[i + 2][j] % x == grid[i][j - 1] % x && grid[i][j - 1] % x == grid[i][j + 1] % x)
			{
				
				if (grid[i][j] / x == 3 || grid[i + 1][j] / x == 3 || grid[i + 2][j] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j] = -3;
					}
				}
				if (grid[i][j - 1] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j-1] = -3;
					}
				}
				if (grid[i][j + 1] / x == 3)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < row; k++)  //vertical stripe elimination
					{
						grid[k][j+1] = -3;
					}
				}
				if (grid[i][j] / x == 2 || grid[i][j - 1] / x == 2 || grid[i][j + 1] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i][k] = -3;
					}
				}
				if (grid[i + 1][j] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i+1][k] = -3;
					}
				}
				if (grid[i + 2][j] / x == 2)
				{eliminatewrappedcandy(grid);
					for (int k = 0; k < column; k++)  //horizontal stripe elimination
					{
						grid[i+2][k] = -3;
					}
				}
				eliminatewrappedcandy(grid);
				grid[i][j] = -3;
				grid[i + 1][j] = -3;                        //    _   _
				grid[i + 2][j] = w;                         //      |  
				grid[i][j - 1] = -3;                        //      | 
				grid[i][j + 1] = -3;                        //      |    shape
			}
		}
	}
}
void stripedcandies(int grid[][column]) //checks for fomation of stripped candy and forms it
{
	//horizontal check for all same type of candies
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			int  w = grid[i][j]; //h.striped candy being formed
			if (w % 11 == 0)
				w = 22; //Red h.striped candy
			else if (w % 17 == 0)
				w = 34;  //Yellow h.striped candy
			else if (w % 19 == 0)
				w = 38;  //Green h.striped candy
			else if (w % 7 == 0)
				w = 14;  //Blue h.striped candy
			else if (w % 13 == 0)
				w = 26;  //Orange h.striped candy 

			int x = grid[i][j];
			if (x % 11 == 0)
				x = 11; //Red
			else if (x % 17 == 0)
				x = 17;  //Yellow
			else if (x % 19 == 0)
				x = 19;  //Green
			else if (x % 7 == 0)
				x = 7;  //Blue
			else if (x % 13 == 0)
				x = 13;  //Orange  

			if (grid[i][j] % x == grid[i][j + 1] % x && grid[i][j + 1] % x == grid[i][j + 2] % x && grid[i][j + 2] % x == grid[i][j + 3] % x)
			{
				if (grid[i][j] != -3)
				{
					if (grid[i][j] / x == 3)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < row; k++)  //vertical stripe elimination
						{
							grid[k][j] = -3;
						}
					}
					if (grid[i][j + 1] / x == 3)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < row; k++)  //vertical stripe elimination
						{
							grid[k][j + 1] = -3;
						}
					}
					if (grid[i][j + 2] / x == 3)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < row; k++)  //vertical stripe elimination
						{
							grid[k][j + 2] = -3;
						}
					}
					if (grid[i][j + 3] / x == 3)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < row; k++)  //vertical stripe elimination
						{
							grid[k][j + 3] = -3;
						}
					}
					if (grid[i][j] / x == 2 || grid[i][j + 1] / x == 2 || grid[i][j + 2] / x == 2 || grid[i][j + 3] / x == 2)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < column; k++)  //horizontal stripe elimination
						{
							grid[i][k] = -3;
						}
					}
					eliminatewrappedcandy(grid);
					grid[i][j] = -3;
					grid[i][j + 1] = -3;
					grid[i][j + 2] = -3;
					grid[i][j + 3] = w;
				}
			}
		}
	}// horizontal end

	//vertical check of all same type of candies
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < column; j++)
		{
			int  w = grid[i][j];
			if (w % 11 == 0)
				w = 22; //Red v.striped candy
			else if (w % 17 == 0)
				w = 51;  //Yellow v.striped candy
			else if (w % 19 == 0)
				w = 57;  //Green v.striped candy
			else if (w % 7 == 0)
				w = 21;  //Blue v.striped candy
			else if (w % 13 == 0)
				w = 39;  //Orange v.striped candy

			int x = grid[i][j];
			if (x % 11 == 0)
				x = 11; //Red
			else if (x % 17 == 0)
				x = 17;  //Yellow
			else if (x % 19 == 0)
				x = 19;  //Green
			else if (x % 7 == 0)
				x = 7;  //Blue
			else if (x % 13 == 0)
				x = 13;  //Orange

			if (grid[i][j] % x == grid[i + 1][j] % x && grid[i + 1][j] % x == grid[i + 2][j] % x && grid[i + 2][j] % x == grid[i + 3][j] % x)
			{
				if (grid[i][j] != -3)
				{
					if (grid[i][j] / x == 3 || grid[i + 1][j] / x == 3 || grid[i + 2][j] / x == 3 || grid[i + 3][j] / x == 3)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < row; k++)  //vertical stripe elimination
						{
							grid[k][j] = -3;
						}
					}
					if (grid[i][j] / x == 2)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < column; k++)  //horizontal stripe elimination
						{
							grid[i][k] = -3;
						}
					}
					if (grid[i + 1][j] / x == 2)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < column; k++)  //horizontal stripe elimination
						{
							grid[i + 1][k] = -3;
						}
					}
					if (grid[i + 2][j] / x == 2)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < column; k++)  //horizontal stripe elimination
						{
							grid[i + 2][k] = -3;
						}
					}
					if (grid[i + 3][j] / x == 2)
					{
						eliminatewrappedcandy(grid);
						for (int k = 0; k < column; k++)  //horizontal stripe elimination
						{
							grid[i + 3][k] = -3;
						}
					}
					eliminatewrappedcandy(grid);
					grid[i][j] = -3;
					grid[i + 1][j] = -3;
					grid[i + 2][j] = -3;
					grid[i + 3][j] = w;
					
				}
			}
		}
	}
}

void copyOfGrid(int scoreGrid[][column],int grid[row][column])
{
	
    for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
		{
			scoreGrid[i][j] = grid[i][j];
		}
	}
}

void score(int scoreGrid[][column], int grid[][column])
{

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			int  w = scoreGrid[i][j];
			if (w % 11 == 0)
				w = 30; //Red
			else if (w % 17 == 0)
				w = 30;  //Yellow
			else if (w % 19 == 0)
				w = 40;  //Green
			else if (w % 7 == 0)
				w = 50;  //Blue
			else if (w % 13 == 0)
				w = 60;  //Orange

			if (grid[i][j] != scoreGrid[i][j])
			{
				if (grid[i][j] == -3)
				{
					points = points + w;
				}
			}
		}
	}
}

void savetofile()
{
	ofstream myfile;
	myfile.open("grid.txt");

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			myfile << grid[i][j] << " ";

		}
		myfile << endl;
	}
	myfile << turns;
	myfile << endl;
	myfile << points;
	myfile << endl;
	myfile.close();
}
void pastetogrid()
{
	ifstream myfile;
	myfile.open("grid.txt");

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			myfile >> grid[i][j];
		}
	}
	myfile >> turns;
	myfile >> points;
	myfile.close();
}

void wrappedPlusStriped(int grid[row][column], int a1, int b1,int a2,int b2)
{

	int x = grid[a1][b1];
	if (x % 11 == 0)
		x = 11; //Red
	else if (x % 17 == 0)
		x = 17;  //Yellow
	else if (x % 19 == 0)
		x = 19;  //Green
	else if (x % 7 == 0)
		x = 7;  //Blue
	else if (x % 13 == 0)
		x = 13;  //Orange

	int y = grid[a2][b2];
	if (y % 11 == 0)
		y = 11; //Red
	else if (y % 17 == 0)
		y = 17;  //Yellow
	else if (y % 19 == 0)
		y = 19;  //Green
	else if (y % 7 == 0)
		y = 7;  //Blue
	else if (y % 13 == 0)
		y = 13;  //Orange

	if (grid[a1][b1] / x == 2 || grid[a1][b1] / x == 3)
	{
		if (grid[a2][b2] / y == 4)
		{
			for (int k = 0; k < column; k++)
			{
				grid[k][b2] = -3;
				if(b2 + 1<column)
					grid[k][b2 + 1] = -3;
				if(b2 - 1>=0)
					grid[k][b2 - 1] = -3;
			}
			for (int k = 0; k < row; k++)
			{
				grid[a2][k] = -3;
				if(a1 + 1<row)
					grid[a2 + 1][k] = -3;
				if(a1 - 1 >= 0)
					grid[a2 - 1][k] = -3;
			}
		}
	}
	else if (grid[a2][b2] / y == 3 || grid[a2][b2] / y == 2)
	{
		if (grid[a1][b1] / x == 4)
		{
			for (int k = 0; k < column; k++)
			{
				grid[k][b1] = -3;
				if(b1 + 1<column)
					grid[k][b1 + 1] = -3;
				if(b1 - 1>=0)
					grid[k][b1 - 1] = -3;
			}
			for (int k = 0; k < row; k++)
			{
				grid[a1][k] = -3;
				if(a1 + 1<row)
					grid[a1 + 1][k] = -3;
				if(a1 - 1>=0)
					grid[a1 - 1][k] = -3;
			}
		}
	}
}

void eliminatewrappedcandy(int grid[row][column])
{
	int pak40 = 11;
	for (int pak38 = 0; pak38 < 5; pak38++) {
		if (pak38 == 0) {
			pak40 = 11;
		}
		else if (pak38 == 1) {
			pak40 = 17;
		}
		else if (pak38 == 2) {
			pak40 = 19;
		}
		else if (pak38 == 3) {
			pak40 = 7;
		}
		else if (pak38 == 4) {
			pak40 = 13;
		}
		//vertical top left corner OK
		if (((grid[0][0] % pak40 == grid[1][0] % pak40) && (grid[1][0] % pak40 == grid[2][0] % pak40) && (grid[0][0] % pak40 == grid[2][0] % pak40))) {
			if (grid[0][0] / pak40 == 4) {
				grid[0][0] = -3;
				grid[1][0] = -3;
				grid[2][0] = -3;
				grid[0][1] = -3;
				grid[1][1] = -3;
			}
		}
		//horizontal top left corner OK
		if (((grid[0][0] % pak40 == grid[0][1] % pak40) && (grid[0][1] % pak40 == grid[0][2] % pak40) && (grid[0][0] % pak40 == grid[0][2] % pak40))) {
			if (grid[0][0] / pak40 == 4) {
				grid[0][0] = -3;
				grid[0][1] = -3;
				grid[1][0] = -3;
				grid[1][1] = -3;
				grid[0][2] = -3;

			}
		}
		//vertical top right corner OK
		if (((grid[0][8] % pak40 == grid[1][8] % pak40) && (grid[1][8] % pak40 == grid[2][8] % pak40) && (grid[0][8] % pak40 == grid[2][8] % pak40))) {
			if (grid[0][8] / pak40 == 4) {
				grid[0][8] = -3;
				grid[1][8] = -3;
				grid[2][8] = -3;
				grid[0][7] = -3;
				grid[1][7] = -3;
			}
		}
		//horizontal top right corner OK
		if (((grid[0][8] % pak40 == grid[0][7] % pak40) && (grid[0][7] % pak40 == grid[0][6] % pak40) && (grid[0][6] % pak40 == grid[0][8] % pak40))) {
			if (grid[0][8] / pak40 == 4) {
				grid[0][8] = -3;
				grid[0][7] = -3;
				grid[0][6] = -3;
				grid[1][8] = -3;
				grid[1][7] = -3;
			}
		}
		//vertical bottom left corner OK
		if (((grid[8][0] % pak40 == grid[7][0] % pak40) && (grid[7][0] % pak40 == grid[6][0] % pak40) && (grid[8][0] % pak40 == grid[6][0] % pak40))) {
			if (grid[8][0] / pak40 == 4) {
				grid[8][0] = -3;
				grid[7][0] = -3;
				grid[6][0] = -3;
				grid[8][1] = -3;
				grid[7][1] = -3;
			}
		}
		//horizontal bottom left corner OK
		if (((grid[8][0] % pak40 == grid[8][1] % pak40) && (grid[8][1] % pak40 == grid[8][2] % pak40) && (grid[8][2] % pak40 == grid[8][0] % pak40))) {
			if (grid[8][0] / pak40 == 4) {
				grid[8][0] = -3;
				grid[8][1] = -3;
				grid[8][2] = -3;
				grid[7][0] = -3;
				grid[7][1] = -3;
			}
		}
		//vertical bottom right corner OK
		if (((grid[8][8] % pak40 == grid[7][8] % pak40) && (grid[7][8] % pak40 == grid[6][8] % pak40) && (grid[8][8] % pak40 == grid[6][8] % pak40))) {
			if (grid[8][8] / pak40 == 4) {
				grid[7][8] = -3;
				grid[6][8] = -3;
				grid[8][8] = -3;
				grid[8][7] = -3;
				grid[7][7] = -3;
			}
		}
		//horizontal bottom right corner OK
		if (((grid[8][8] % pak40 == grid[8][7] % pak40) && (grid[8][7] % pak40 == grid[8][6] % pak40) && (grid[8][6] % pak40 == grid[8][8] % pak40))) {
			if (grid[8][8] / pak40 == 4) {
				grid[8][8] = -3;
				grid[8][7] = -3;
				grid[8][6] = -3;
				grid[7][8] = -3;
				grid[7][7] = -3;
			}
		}
		
		
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column-1; j++)
			{
				// for pak40
				if (((grid[i][j] % pak40 == grid[i + 1][j] % pak40) && (grid[i + 1][j] % pak40 == grid[i + 2][j] % pak40) && (grid[i][j] % pak40 == grid[i + 2][j] % pak40)))
				{//clearing 3x3 grid with wrapped candy as point of origin if it is not on boundary
					if (i < 9 && i>-1) {


						if (grid[i + 1][j] / pak40 == 4) {

							if ((i + 1 > -1) && (i + 1 < 9)) {
								grid[i + 1][j] = -3;
								if ((j + 1 > -1) && (j + 1 < 9)) {
									grid[i + 1][j + 1] = -3;
								}
								if ((j - 1 > -1) && (j - 1 < 9)) {
									grid[i + 1][j - 1] = -3;
								}
							}

							grid[i][j] = -3;
							if ((j + 1 > -1) && (j + 1 < 9)) {
								grid[i][j + 1] = -3;
							}
							if ((j - 1 > -1) && (j - 1 < 9)) {
								grid[i][j - 1] = -3;
							}

							if ((i + 2 > -1) && (i + 2 < 9)) {
								grid[i + 2][j] = -3;
								if ((j + 1 > -1) && (j + 1 < 9)) {
									grid[i + 2][j + 1] = -3;
								}
								if ((j - 1 > -1) && (j - 1 < 9)) {
									grid[i + 2][j - 1] = -3;
								}
							}


						}
						else if (grid[i][j] / pak40 == 4) {

							if ((i + 1 > -1) && (i + 1 < 9)) {
								grid[i + 1][j] = -3;
								if ((j + 1 > -1) && (j + 1 < 9)) {
									grid[i + 1][j + 1] = -3;
								}
								if ((j - 1 > -1) && (j - 1 < 9)) {
									grid[i + 1][j - 1] = -3;
								}
							}

							grid[i][j] = -3;
							if ((j + 1 > -1) && (j + 1 < 9)) {
								grid[i][j + 1] = -3;
							}
							if ((j - 1 > -1) && (j - 1 < 9)) {
								grid[i][j - 1] = -3;
							}

							if ((i - 1 > -1) && (i - 1 < 9)) {
								grid[i - 1][j] = -3;
								if ((j + 1 > -1) && (j + 1 < 9)) {
									grid[i - 1][j + 1] = -3;
								}
								if ((j - 1 > -1) && (j - 1 < 9)) {
									grid[i - 1][j - 1] = -3;
								}
							}
						}

						else if (grid[i + 2][j] / pak40 == 4) {
							if ((i + 1 > -1) && (i + 1 < 9)) {
								grid[i + 1][j] = -3;
								if ((j + 1 > -1) && (j + 1 < 9)) {
									grid[i + 1][j + 1] = -3;
								}
								if ((j - 1 > -1) && (j - 1 < 9)) {
									grid[i + 1][j - 1] = -3;
								}
							}
							if ((i + 2 > -1) && (i + 2 < 9)) {
								grid[i + 2][j] = -3;
								if ((j + 1 > -1) && (j + 1 < 9)) {
									grid[i + 2][j + 1] = -3;
								}
								if ((j - 1 > -1) && (j - 1 < 9)) {
									grid[i + 2][j - 1] = -3;
								}
							}
							if ((i + 3 > -1) && (i + 3 < 9)) {
								grid[i + 3][j] = -3;
								if ((j + 1 > -1) && (j + 1 < 9)) {
									grid[i + 3][j + 1] = -3;
								}
								if ((j - 1 > -1) && (j - 1 < 9)) {
									grid[i + 3][j - 1] = -3;
								}
							}
						}
					}
				}
			}

		}

		for (int j = 0; j < column-2; j++) {

			for (int i = 0; i < row; i++) {
				if ((grid[i][j] % pak40 == grid[i][j + 1] % pak40) && (grid[i][j + 1] % pak40 == grid[i][j + 2] % pak40) && (grid[i][j] % pak40 == grid[i][j + 2] % pak40)) {
					if (j > -1 && j < 9) {

						
						if (grid[i][j] / pak40 == 4) {

							grid[i][j] = -3;
							if ((j + 1 > -1) && (j + 1 < 9)) {
								grid[i][j + 1] = -3;
							}
							if ((j - 1 > -1) && (j - 1 < 9)) {
								grid[i][j - 1] = -3;
							}
							if ((i + 1 > -1) && (i + 1 < 9)) {
								grid[i + 1][j] = -3;
								if ((j + 1 > -1) && (j + 1 < 9)) {
									grid[i + 1][j + 1] = -3;
								}
								if ((j - 1 > -1) && (j - 1 < 9)) {
									grid[i + 1][j - 1] = -3;
								}
							}
							if ((i - 1 > -1) && (i - 1 < 9)) {
								grid[i - 1][j] = -3;
								if ((j + 1 > -1) && (j + 1 < 9)) {
									grid[i - 1][j + 1] = -3;
								}
								if ((j - 1 > -1) && (j - 1 < 9)) {
									grid[i - 1][j - 1] = -3;
								}
							}

						}
						else if (grid[i][j + 1] / pak40 == 4) {
							if (j + 1 < 9) {

								grid[i][j] = -3;
								grid[i][j + 1] = -3;
								if (j + 2 < 9) {
									grid[i][j + 2] = -3;
								}
								if ((i + 1) < 9) {
									grid[i + 1][j] = -3;
									if (j + 1 < 9) {
										grid[i + 1][j + 1] = -3;
									}
									if (j + 2 < 9) {
										grid[i + 1][j + 2] = -3;
									}
								}
								if ((i - 1) > -1) {
									grid[i - 1][j] = -3;
									if (j + 1 < 9) {
										grid[i + 1][j + 1] = -3;
									}
									if (j + 2 < 9) {
										grid[i + 1][j + 2] = -3;
									}
								}
							}

						}
						else if (grid[i][j + 2] / pak40 == 4) {

							grid[i][j] = -3;
							if (j + 1 < 9) {
								grid[i][j + 1] = -3;
							}
							if (j + 2 < 9) {
								grid[i][j + 2] = -3;
							}
							if (j + 3 < 9) {
								grid[i][j + 3] = -3;
							}
							if (i + 1 < 9) {
								if (j + 1 < 9) {
									grid[i + 1][j + 1] = -3;
								}
								if (j + 2 < 9) {
									grid[i + 1][j + 2] = -3;
								}
								if (j + 3 < 9) {
									grid[i + 1][j + 3] = -3;
								}
							}
							if (i - 1 > -1) {
								if (j + 1 < 9) {
									grid[i - 1][j + 1] = -3;
								}
								if (j + 2 < 9) {
									grid[i - 1][j + 2] = -3;
								}
								if (j + 3 < 9) {
									grid[i - 1][j + 3] = -3;
								}
							}
						}
					}
				}
			}
		}
		
		}
}
void eliminatethreeBythree(int k,int l)
{
	if (k == 0 && l == 0) //top left corner
	{
		grid[k][l] = -3;
		grid[k][l + 1] = -3;
		grid[k + 1][l] = -3;
		grid[k + 1][l + 1] = -3;
	}
	else if (k == 8 && l == 0) //bottom left corner
	{
		grid[k][l] = -3;
		grid[k][l + 1] = -3;
		grid[k - 1][l] = -3;
		grid[k - 1][l + 1] = -3;
	}
	else if (k == 0 && l == 8) //top rkght corner
	{
		grid[k][l] = -3;
		grid[k][l - 1] = -3;
		grid[k + 1][l] = -3;
		grid[k + 1][l - 1] = -3;
	}
	else if (k == 8 && l == 8) //bottom rkght corner
	{
		grid[k][l] = -3;
		grid[k - 1][l] = -3;
		grid[k][l - 1] = -3;
		grid[k - 1][l - 1] = -3;
	}
	else if (k == 0 && (l > 0 && l < 8)) //top row
	{
		grid[k][l] = -3;
		grid[k][l + 1] = -3;
		grid[k][l - 1] = -3;
		grid[k + 1][l] = -3;
		grid[k + 1][l + 1] = -3;
		grid[k + 1][l - 1] = -3;
	}
	else if (k == 8 && (l > 0 && l < 8)) //bottom row
	{
		grid[k][l] = -3;
		grid[k - 1][l] = -3;
		grid[k - 1][l + 1] = -3;
		grid[k - 1][l - 1] = -3;
		grid[k][l - 1] = -3;
		grid[k][l + 1] = -3;
	}
	else if ((k > 0 && k < 8) && l == 0) // first column
	{
		grid[k][l] = -3;
		grid[k][l + 1] = -3;
		grid[k + 1][l + 1] = -3;
		grid[k - 1][l + 1] = -3;
		grid[k - 1][l] = -3;
		grid[k + 1][l] = -3;
	}
	else if ((k > 0 && k < 8) && l == 8) //last column
	{
		grid[k][l] = -3;
		grid[k - 1][l] = -3;
		grid[k + 1][l] = -3;
		grid[k][l - 1] = -3;
		grid[k - 1][l - 1] = -3;
		grid[k + 1][l - 1] = -3;
	}
	else if ((k > 0 && k < 8) && (l > 0 && l < 8)) //middle
	{
		grid[k][l] = -3;
		grid[k - 1][l] = -3;
		grid[k + 1][l] = -3;
		grid[k][l + 1] = -3;
		grid[k][l - 1] = -3;
		grid[k - 1][l + 1] = -3;
		grid[k - 1][l - 1] = -3;
		grid[k + 1][l + 1] = -3;
		grid[k + 1][l - 1] = -3;
	}
}
void eliminateWrappedPlusWrapped(int grid[row][column],int a1,int b1,int a2,int b2)
{
	int x = grid[a1][b1];
	if (x % 11 == 0)
		x = 11; //Red
	else if (x % 17 == 0)
		x = 17;  //Yellow
	else if (x % 19 == 0)
		x = 19;  //Green
	else if (x % 7 == 0)
		x = 7;  //Blue
	else if (x % 13 == 0)
		x = 13;  //Orange

	int y = grid[a2][b2];
	if (y % 11 == 0)
		y = 11; //Red
	else if (y % 17 == 0)
		y = 17;  //Yellow
	else if (y % 19 == 0)
		y = 19;  //Green
	else if (y % 7 == 0)
		y = 7;  //Blue
	else if (y % 13 == 0)
		y = 13;  //Orange

	if (grid[a1][b1] / x == 4)
	{
		if (grid[a2][b2] / y == 4)
		{  
			//entire horizontal at origin
			grid[a1][b1] = -3;
			if (a1 + 1 < 9) {
				grid[a1 + 1][b1] = -3;
			}
			if (a1 + 2 < 9) {
				grid[a1 + 2][b1] = -3;
			}
			if (a1 - 1 > -1) {
				grid[a1 - 1][b1] = -3;
			}
			if (a1 - 2 > -1) {
				grid[a1 - 2][b1] = -3;
			}
			for (int pz4 = 1; pz4 < 3; pz4++) {
				if ((b1 + pz4) < 9) {
					grid[a1][b1 + pz4] = -3;
				}
				if ((a1 + 1 < 9) && (b1 + pz4 < 9)) {
					grid[a1 + 1][b1 + pz4] = -3;
				}
				if ((a1 + 2 < 9) && (b1 + pz4 < 9)) {
					grid[a1 + 2][b1 + pz4] = -3;
				}
				if ((a1 - 1 > -1) && (b1 + pz4 < 9)) {
					grid[a1 - 1][b1 + pz4] = -3;
				}
				if ((a1 - 2 > -1) && (b1 + pz4 < 9)) {
					grid[a1 - 2][b1 + pz4] = -3;
				}

			}
			for (int pz5 = -2; pz5 < 0; pz5++) {
				if ((b1 + pz5) < 9) {
					grid[a1][b1 + pz5] = -3;
				}
				if ((a1 + 1 < 9) && (b1 + pz5 > -1)) {
					grid[a1 + 1][b1 + pz5] = -3;
				}
				if ((a1 + 2 < 9) && (b1 + pz5 > -1)) {
					grid[a1 + 2][b1 + pz5] = -3;
				}
				if ((a1 - 1 > -1) && (b1 + pz5 > -1)) {
					grid[a1 - 1][b1 + pz5] = -3;
				}
				if ((a1 - 2 > -1) && (b1 + pz5 > -1)) {
					grid[a1 - 2][b1 + pz5] = -3;
				}

			}

		}

	}
}