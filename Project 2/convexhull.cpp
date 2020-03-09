// Jaron Smith, jms642@zips.uakron.edu
//Graham Scan and Jarvis March implementation from GeeksforGeeks.com

//ABSTRACT GRAHAM SCAN AWAY TO OTHER FILES
//FIX JARVIS MARCH
//ADD TIMERS

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <iostream>
#include <stack>
#include <bits/stdc++.h> //Jarvis March

using namespace std;

struct Point 
{ 
   int x, y; 
}; 

Point p0;


Point nextToTop(stack<Point> &S);
int swap(Point &p1, Point &p2);
int distSq(Point p1, Point p2);
int orientation(Point p, Point q, Point r);
int compare(const void *vp1, const void *vp2);
void GrahamScan(Point points[], int n);


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


// A utility function to find next to top in a stack 
Point nextToTop(stack<Point> &S) 
{ 
   Point p = S.top(); 
   S.pop(); 
   Point res = S.top(); 
   S.push(p); 
   return res; 
} 

// A utility function to swap two points 
int swap(Point &p1, Point &p2) 
{ 
   Point temp = p1; 
   p1 = p2; 
   p2 = temp; 
} 

// A utility function to return square of distance 
// between p1 and p2 
int distSq(Point p1, Point p2) 
{ 
   return (p1.x - p2.x)*(p1.x - p2.x) + 
      (p1.y - p2.y)*(p1.y - p2.y); 
} 

// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point p, Point q, Point r) 
{ 
   int val = (q.y - p.y) * (r.x - q.x) - 
         (q.x - p.x) * (r.y - q.y); 

   if (val == 0) return 0; // colinear 
   return (val > 0)? 1: 2; // clock or counterclock wise 
} 

// A function used by library function qsort() to sort an array of 
// points with respect to the first point 
int compare(const void *vp1, const void *vp2) 
{ 
Point *p1 = (Point *)vp1; 
Point *p2 = (Point *)vp2; 

// Find orientation 
int o = orientation(p0, *p1, *p2); 
if (o == 0) 
   return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1; 

return (o == 2)? -1: 1; 
} 

// Prints convex hull of a set of n points. 
void GrahamScan(Point points[], int n) 
{ 
   // Find the bottommost point 
   int ymin = points[0].y, min = 0; 
   for (int i = 1; i < n; i++) 
   { 
      int y = points[i].y; 

      // Pick the bottom-most or chose the left 
      // most point in case of tie 
      if ((y < ymin) || (ymin == y && 
         points[i].x < points[min].x)) 
         ymin = points[i].y, min = i; 
   } 

   // Place the bottom-most point at first position 
   swap(points[0], points[min]); 

   // Sort n-1 points with respect to the first point. 
   // A point p1 comes before p2 in sorted output if p2 
   // has larger polar angle (in counterclockwise 
   // direction) than p1 
   p0 = points[0]; 
   qsort(&points[1], n-1, sizeof(Point), compare); 

   // If two or more points make same angle with p0, 
   // Remove all but the one that is farthest from p0 
   // Remember that, in above sorting, our criteria was 
   // to keep the farthest point at the end when more than 
   // one points have same angle. 
   int m = 1; // Initialize size of modified array 
   for (int i=1; i<n; i++) 
   { 
      // Keep removing i while angle of i and i+1 is same 
      // with respect to p0 
      while (i < n-1 && orientation(p0, points[i], 
                              points[i+1]) == 0) 
         i++; 


      points[m] = points[i]; 
      m++; // Update size of modified array 
   } 

   // If modified array of points has less than 3 points, 
   // convex hull is not possible 
   if (m < 3) return; 

   // Create an empty stack and push first three points 
   // to it. 
   stack<Point> S; 
   S.push(points[0]); 
   S.push(points[1]); 
   S.push(points[2]); 

   // Process remaining n-3 points 
   for (int i = 3; i < m; i++) 
   { 
      // Keep removing top while the angle formed by 
      // points next-to-top, top, and points[i] makes 
      // a non-left turn 
      while (orientation(nextToTop(S), S.top(), points[i]) != 2) 
         S.pop(); 
      S.push(points[i]); 
   } 

   // Now stack has the output points, print contents of stack 
   while (!S.empty()) 
   { 
      Point p = S.top(); 
      cout << "(" << p.x << ", " << p.y <<")" << endl; 
      S.pop(); 
   } 
} 

//JARVIS MARCH STARTS HERE
//LOOK FOR REPEATED FUNCTIONS, ABSTRACT WHERE POSSIBLE
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point p, Point q, Point r) 
{ 
   int val = (q.y - p.y) * (r.x - q.x) - 
         (q.x - p.x) * (r.y - q.y); 

   if (val == 0) return 0; // colinear 
   return (val > 0)? 1: 2; // clock or counterclock wise 
} 

// Prints convex hull of a set of n points. 
void convexHull(Point points[], int n) 
{ 
   // There must be at least 3 points 
   if (n < 3) return; 

   // Initialize Result 
   vector<Point> hull; 

   // Find the leftmost point 
   int l = 0; 
   for (int i = 1; i < n; i++) 
      if (points[i].x < points[l].x) 
         l = i; 

   // Start from leftmost point, keep moving counterclockwise 
   // until reach the start point again. This loop runs O(h) 
   // times where h is number of points in result or output. 
   int p = l, q; 
   do
   { 
      // Add current point to result 
      hull.push_back(points[p]); 

      // Search for a point 'q' such that orientation(p, x, 
      // q) is counterclockwise for all points 'x'. The idea 
      // is to keep track of last visited most counterclock- 
      // wise point in q. If any point 'i' is more counterclock- 
      // wise than q, then update q. 
      q = (p+1)%n; 
      for (int i = 0; i < n; i++) 
      { 
      // If i is more counterclockwise than current q, then 
      // update q 
      if (orientation(points[p], points[i], points[q]) == 2) 
         q = i; 
      } 

      // Now q is the most counterclockwise with respect to p 
      // Set p as q for next iteration, so that q is added to 
      // result 'hull' 
      p = q; 

   } while (p != l); // While we don't come to first point 

   // Print Result 
   for (int i = 0; i < hull.size(); i++) 
      cout << "(" << hull[i].x << ", "
         << hull[i].y << ")\n"; 
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

