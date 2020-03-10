// Jaron Smith, jms642@zips.uakron.edu
//Graham Scan and Jarvis March implementation from GeeksforGeeks.com

//ABSTRACT GRAHAM SCAN AWAY TO OTHER FILES
//FIX JARVIS MARCH
//ADD QUICK HULL IMPLEMENTATION
//ADD TIMERS

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <iostream>
#include "Jarvis.hpp"
#include "Graham.hpp"


int main(int argc, char *argv[])
{   
   if (argc < 3) 
      std::cout << "wrong format! should be \"a.exe algType dataFile\"";
   else {
      std::string algType = argv[1];
      std::string dataFilename = argv[2];

      std::string outputFile = "";
      //read your data points from dataFile (see class example for the format)
      
      if (algType[0]=='G') {
         //call your Graham Scan algorithm to solve the problem
         outputFile = "hull_G.txt";
      } 
      else if (algType[0]=='J') {
         //call your Javis March algorithm to solve the problem
         outputFile = "hull_J.txt";
      }
      else { //default 
         //call your Quickhull algorithm to solve the problem
         outputFile = "hull_Q.txt";
      }
      
      //write your convex hull to the outputFile (see class example for the format)
      //you should be able to visulize your convex hull using the "ConvexHull_GUI" program.
   }
} 


// Driver program to test above functions 
int main() 
{ 
   Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, 
               {3, 0}, {0, 0}, {3, 3}}; 
   int n = sizeof(points)/sizeof(points[0]); 
   convexHull(points, n); 
   return 0; 
} 

