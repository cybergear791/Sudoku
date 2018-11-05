//Sudoku Solver cs480
//Created By Nick Flouty & Joey Robinson

#include <iostream>	//use of cout
#include <istream>	//use of >> from file
#include <fstream>	//to open read a file
#include <vector>	//use of vector
#include <string>	//use of string
#include <sstream>
#include <string.h>	//for c_str
using namespace std;

//Checks if board has ny missing numbers.
bool noZeros(vector<vector<int>> input, int &row, int &col)
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (input[i][j] == 0)
			{	
				row = i;
				col = j;
				return false;
			}
	return true;
}

//Checks if that num is already present in that row.
bool inRow(vector<vector<int>> input, int row, int num)
{
	for (int i = 0; i < 9; i++)
		if (input[row][i] == num)
			return true;
	return false;
}

//Checks if that num is already present in that col.
bool inCol(vector<vector<int>> input, int col, int num)
{
	for (int i = 0; i < 9; i++)
		if (input[i][col] == num)
			return true;
	return false;
}

//Checks if that num is already present in its 3x3 box.
bool inBox(vector<vector<int>> input, int row, int col,int num)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (input[i + row][j + col] == num)
				return true;
	return false;
}

//Checks if that num is a valid number for that spot.
bool isValid(vector<vector<int>> input, int row, int col, int num)
{
	return !inRow(input, row, num) && !inCol(input, col, num) && !inBox(input, row - (row % 3), col - (col % 3), num);
}

//Prints the sudoku solution in standard output. 
void print_sudoku(vector<vector<int>> input)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			cout << input[i][j];
		cout << "\n";
	}
}

//Returns true if it has succsessfly filled the vector with a non-zero number.
bool sukoku_solver(vector<vector<int>> &input)
{
	int row;
	int col;

	if (!noZeros(input,row,col))
	{
		for (int i = 1; i <= 9; i++)
		{
			if (isValid(input, row, col, i))
			{
				input[row][col] = i;
				if (sukoku_solver(input))
					return true;
				input[row][col] = 0;
			}
		}
		return false;														
	}
	return true;
}		

int main()
{
	ifstream file;
	file.open("input.txt");

	vector<string> input(9);
	while (!file.eof()) //reads the file into a string vector
	{
		for (int i = 0; i < 9; i++)
		{
			file >> input[i];
		}
	}

	vector<vector<int>> sudokuBoard;
	vector<int> rowInput(9);

	for (int i = 0; i < 9; i++)
	{
		sudokuBoard.push_back(rowInput);
		char char_array[10]; // creates a character array for the first string of the vector

		strncpy_s(char_array, input[i].c_str(),9); //copies the string into the character array
		for (int j = 0; j < 9; j++)
		{
			int num = char_array[j] - '0'; //changes the char to an int
			sudokuBoard[i][j] = num;
		}
	}
	
	//This prints out the original board, to test if it is correct
	/*for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << sudokuBoard[i][j];
		}
		cout << endl;
	}*/
	
	file.close();

	if (sukoku_solver(sudokuBoard))
		print_sudoku(sudokuBoard);
	else
		cout << "No possible solution exists.\n";
	
	system("PAUSE");
	return 0;
}