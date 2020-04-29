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
}