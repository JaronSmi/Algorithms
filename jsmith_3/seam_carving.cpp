/* Jaron Smith - 4203199
	Algorithms Project 3 - Seam Carving

	Description:
	This project is executed with a valid pgm file name and 2 parameters
	for number of vertical and horizontal seams to remove.

	Seams are removed by calculating energy grid then Cumulative
	energy grid.
	
	The grid is resized for each seam removal and remaining vals are
	transferred to new grid.
*/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstring>

void read_pgm_file(const std::string & int** &, int &, int &, int &);
void process_image_seams(int** &, int &, int &);
void output_processed_pgm(int** const &, const int, const int, const int, const std::string &);
void clockwise_ninety(int** &, int &, int &);
void counter_clockwise_ninety(int** &, int &, int &);

int main(int argc, char *argv[]){
	//check for 4 args
	if(argc){
		std::cout << "Wrong number of arguments entered. 4 are required.\n";
		return 0;
	}

	int vertical_to_remove = std::atoi(argv[2]);
	int horizontal_to_remove = std::atoi(argv[3]);
	//checks that x & y dimensions are non-neg
	if(vertical_to_remove < 0 || horizontal_to_remove < 0){
		std::cout << "ERROR: Invalid Arguments \n";
		return 0;
	}

	std::string filename = argv[1];
	int** grid;
	int x_dim, y_dim, max_grey;
	read_pgm_file(filename, grid, x_dim, y_dim, max_grey);
	//Vertical Seam Process
	for(int i = 0; i < vertical_to_remove; i++){
		process_image_seams(grid, x_dim, y_dim);
	}
	//Horizontal Seam Process
	for(int i = 0; i < horizontal_to_remove; i++){
		counter_clockwise_ninety(grid, x_dim, y_dim);
		process_image_seams(grid, x_dim, y_dim);
		clockwise_ninety(grid, x_dim, y_dim);
	}
	output_processed_pgm(grid, x_dim, y_dim, max_grey, filename);
	delete [] grid;
	return 0;
}

/* 
	Iterates through an inputted pgm file and dynamically creates a 
	2D grid based upon pgm file values. 
PARAMS:
	a valid string pgm filename, an int* to an int*, 3 ref ints to 
	keep track of dimensions
*/
void read_pgm_file(const std::string & filename, int** & grid, int & x_dim,
	int & y_dim, int & max_grey)
{
	std::ifstream pgm_file;
	pgm_file.open(filename);
	std::string input, comment;
	bool dimensions_flag = true, max_greyscale_flag = true;
	int grid_values = 0, x = 0, y = 0;
	pgm_file >> input;
	if (input != "P2")
	{
		std::cout << "ERROR: valid pgm files must begin with P2\n";
		return;
	}
	while (pgm_file >> input)
	{
		// Skip comment lines
		if (input == "#" || input[0] == '#')
		{
			std::getline(pgm_file, comment);
		}
		// Process dimension values
		else if (dimensions_flag)
		{
			x_dim = std::stoi(input);
			pgm_file >> input;
			y_dim = std::stoi(input);
			// Create the grid
			// Define total rows first
			grid = new int*[y_dim];
			for (int i = 0; i < y_dim; ++i)
				// Total columns
				grid[i] = new int[x_dim];
			dimensions_flag = false;
		}
		else if (max_greyscale_flag)
		{
			max_grey = std::stoi(input);
			max_greyscale_flag = false;
		}
		// Populate grid
		else
		{
			// Determine if current row is at limit
			if (x == x_dim)
			{
				// Reset at new row
				x = 0;
				y++;
				grid[y][x] = std::stoi(input);
				x++;
			}
			else
			{
				grid[y][x] = std::stoi(input);
				x++;
			}
			// Keep track of total inputs
			grid_values++;
		}
	}
	pgm_file.close();
	// Used mainly for testing
	if (grid_values != (x_dimension * y_dimension))
	{
		std::cout << "ERROR: total value and grid do not match!!\n";
	}
}