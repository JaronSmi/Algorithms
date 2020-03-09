// You need to complete this program for your second project.

#include <string>
#include <iostream>
#include <stdlib.h> 
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm> // used for std::qsort
#include <set> // used for jarvis
#include <memory>
#include <utility>
#include <ctime>
#include <cmath>

// Object for holding each pair read in from test.txt
struct coordinate_pair
{
   int x_coord;
   int y_coord;
   coordinate_pair(int x, int y) : x_coord(x), y_coord(y) {}
   bool operator==(coordinate_pair p2)
   {
      if (x_coord == p2.x_coord && y_coord == p2.y_coord)
      {
         return true;
      }
      return false;
   }
   bool operator<(const coordinate_pair & p2) const
   {
      return true;
   }
};

coordinate_pair P0(0, 0); // Global needed for compare to work in Graham

int main(int argc, char *argv[])
{   
   if (argc < 3) 
      std::cout << "wrong format! should be \"a.exe algType test.txt\"" << std::endl;
   else {
      std::string algType = argv[1];
      std::string dataFilename = argv[2];
      std::string outputFile = "";
      std::ofstream output_hull;
      std::ifstream input_file;
      input_file.open("test.txt");
      std::string str_x_coord;
      std::string str_y_coord;
      std::vector<coordinate_pair> all_coordinate_pairs;
      // Retrieve all coordinates from test.txt, format, and store
      while (input_file >> str_x_coord && input_file >> str_y_coord)
      {
         coordinate_pair new_pair(std::stoi(str_x_coord), std::stoi(str_y_coord));
         all_coordinate_pairs.push_back(new_pair);
      }
      // vars for analyzing runtimes
      clock_t start, stop;
      // GRAHAM SCAN
      if (algType[0]=='G') 
      {
         start = clock();
         // Assign p0 to first coordinate
         coordinate_pair p0 = all_coordinate_pairs[0];
         int swap_pos;
         // Traverse all remaining points and assign p0 to smallest y coord
         // O(n) time
         for (int i = 1; i < all_coordinate_pairs.size(); ++i)
         {
            // new point has smaller y coord OR same y coord but new point has smaller x
            if (all_coordinate_pairs[i].y_coord < p0.y_coord ||
               all_coordinate_pairs[i].y_coord == p0.y_coord && all_coordinate_pairs[i].x_coord < p0.x_coord)
            {
               p0 = all_coordinate_pairs[i];
               swap_pos = i;
            }
         }
         // Swap p0 to index 0 and tmp to old p0 index
         coordinate_pair tmp = all_coordinate_pairs[0];
         all_coordinate_pairs[0] = p0;
         all_coordinate_pairs[swap_pos] = tmp;
         // Update global
         P0 = p0;
         // Sort remaining n-1 based on angle with respect to p0
         // O(n log n)
         std::qsort(&all_coordinate_pairs[1], all_coordinate_pairs.size()-1, sizeof(coordinate_pair), compare);
         int vec_size = 1;
         // Check for points with same angle and remove point with smaller distance to p0
         for (int i = 1; i < all_coordinate_pairs.size(); ++i)
         {
            while (i < all_coordinate_pairs.size() - 1 && direction(p0, all_coordinate_pairs[i], all_coordinate_pairs[i+1]) == 0)
            {
               ++i;
            }
            all_coordinate_pairs[vec_size] = all_coordinate_pairs[i];
            ++vec_size;
         }
         // Push values onto stack
         std::stack<coordinate_pair> tmp_stk;
         tmp_stk.push(p0);
         tmp_stk.push(all_coordinate_pairs[1]);
         tmp_stk.push(all_coordinate_pairs[2]);
         // Traverse sorted points O(n)
         for (int i = 3; i < vec_size; ++i)
         {
            while (direction(second_top(tmp_stk), tmp_stk.top(), all_coordinate_pairs[i]) != 2)
            {
               tmp_stk.pop();
            }
            tmp_stk.push(all_coordinate_pairs[i]);
         }
         // Stop clock once all points are pushed onto stack
         stop = clock();
         std::cout << "GRAHAM SCAN size " << all_coordinate_pairs.size() << " : " << double(stop - start) / double(CLOCKS_PER_SEC) << std::endl;     
         // Declare final vec to store hull
         std::vector<coordinate_pair> hull_points;
         while (!tmp_stk.empty())
         {
            hull_points.push_back(tmp_stk.top());
            tmp_stk.pop();
         }
         outputFile = "hull_G.txt";
         output_hull.open(outputFile);
         for (int i = 0; i < hull_points.size(); ++i)
         {
            output_hull << hull_points[i].x_coord << " " << hull_points[i].y_coord << std::endl;
         }
      } 

      // JARVIS MARCH
      else if (algType[0]=='J') 
      {
         start = clock();
         std::set<coordinate_pair> result = jarvis_hull(all_coordinate_pairs, all_coordinate_pairs.size());
         stop = clock();
         std::cout << "JARVIS MARCH size " << all_coordinate_pairs.size() << " : " << double(stop - start) / double(CLOCKS_PER_SEC) << std::endl;
         outputFile = "hull_J.txt";
         output_hull.open(outputFile);
         for (std::set<coordinate_pair>::iterator it = result.begin(); it != result.end(); ++it)
         {
            output_hull << it->x_coord << " " << it->y_coord << std::endl;
         }
      }

      // QUICKHULL
      else 
      {
         int n = all_coordinate_pairs.size();
         start = clock();
         std::vector<coordinate_pair> answer = outerTrees(all_coordinate_pairs);
         stop = clock();
         std::cout << "QUICKHULL size " << n << " : " << double(stop - start) / double(CLOCKS_PER_SEC) << std::endl;
         outputFile = "hull_Q.txt";
         output_hull.open(outputFile);
         for (int i = 0; i < answer.size(); ++i)
         {
            output_hull << answer[i].x_coord << " " << answer[i].y_coord << std::endl;
         }
      }
   }
   return 0;
}

int compare(const void* point1, const void* point2)
{
   coordinate_pair* p1 = (coordinate_pair*)point1;
   coordinate_pair* p2 = (coordinate_pair*)point2;
   int dir = direction(P0, *p1, *p2);
   if (dir == 0)
   {
      return (squaredDist(P0, *p2) >= (squaredDist(P0, *p1)) ? -1 : 1);
   }
   return (dir == 2) ? -1 : 1;
}

int direction(coordinate_pair a, coordinate_pair b, coordinate_pair c)
{
   int val = (b.y_coord - a.y_coord) * (c.x_coord - b.x_coord) 
             - (b.x_coord - a.x_coord) * (c.y_coord - b.y_coord);
   if (val == 0)
   {
      return 0;
   }
   else if (val < 0)
   {
      // counter-clockwise
      return 2;
   }
   else
   {
      // clockwise
      return 1;
   }
}

int squaredDist(coordinate_pair p1, coordinate_pair p2)
{
   return ((p1.x_coord - p2.x_coord) * (p1.x_coord - p2.x_coord) 
          + (p1.y_coord - p2.y_coord) * (p1.y_coord - p2.y_coord));
}

coordinate_pair second_top(std::stack<coordinate_pair> & stk)
{
   coordinate_pair tmp = stk.top();
   stk.pop();
   coordinate_pair res = stk.top();
   stk.push(tmp);
   return res;
}

std::set<coordinate_pair> jarvis_hull(std::vector<coordinate_pair> & points, int n)
{
   coordinate_pair start = points[0];
   // Find the point with smallest x coord
   for (int i = 0; i < n; ++i)
   {
      if (points[i].x_coord < start.x_coord)
      {
         start = points[i];
      }
   }
   coordinate_pair current = start;
   std::set<coordinate_pair> result;
   result.insert(start);
   std::vector<coordinate_pair>* collinear_points = new std::vector<coordinate_pair>;
   while (true)
   {
      coordinate_pair next_target = points[0];
      for (int i = 1; i < n; i++)
      {
         if (points[i] == current)
         {
            continue;
         }
         int val = cross_product(current, next_target, points[i]);
         if (val > 0)
         {
            next_target = points[i];
            collinear_points = new std::vector<coordinate_pair>;
         }
         else if (val == 0)
         {
            if (distance(current, next_target, points[i]) < 0)
            {
               collinear_points->push_back(next_target);
               next_target = points[i];
            }
            else
            {
               collinear_points->push_back(points[i]);
            }
         }
      }
      std::vector<coordinate_pair>::iterator it;
      for (it = collinear_points->begin(); it != collinear_points->end(); it++)
      {
         result.insert(*it);
      }
      if (next_target == start)
      {
         break;
      }
      result.insert(next_target);
      current = next_target;
   }
   return result;
}

int cross_product(coordinate_pair a, coordinate_pair b, coordinate_pair c)
{
   int y1 = a.y_coord - b.y_coord;
   int y2 = a.y_coord - c.y_coord;
   int x1 = a.x_coord - b.x_coord;
   int x2 = a.x_coord - c.x_coord;
   return y2*x1 - y1*x2;
}

int distance(coordinate_pair a, coordinate_pair b, coordinate_pair c)
{
   int y1 = a.y_coord - b.y_coord;
   int y2 = a.y_coord - c.y_coord;
   int x1 = a.x_coord - b.x_coord;
   int x2 = a.x_coord - c.x_coord;
   int item1 = (y1*y1 + x1*x1);
   int item2 = (y2*y2 + x2*x2);
   if(item1 == item2)
   {
      return 0; //when b and c are in same distance from a
   }
   else if(item1 < item2)
   {
      return -1; //when b is closer to a
   }
   return 1; //when c is closer to a
}

static bool mycmp (coordinate_pair &a, coordinate_pair&b)
{
   return a.x_coord < b.x_coord;
}

int testSide(coordinate_pair &a, coordinate_pair &b, coordinate_pair &c)
{
   return (b.x_coord - a.x_coord) * (c.y_coord - a.y_coord) 
            - (b.y_coord - a.y_coord) * (c.x_coord - a.x_coord);
}

double distPointLine(coordinate_pair &A, coordinate_pair &B, coordinate_pair &C) 
{
        // dist(line: ax+by+c=0, and point(x0, y0)): (a*x0 + b*y0 + c)/sqrt(a^2+b^2)
        // line: (y2-y1)*x - (x2-x1)*y + x2*y1 - y2*x1 = 0
        int a = B.y_coord - A.y_coord, b = B.x_coord - A.x_coord;
        return abs((a*C.x_coord - b*C.y_coord + B.x_coord*A.y_coord - B.y_coord*A.x_coord)/sqrt(a*a + b*b));
}

std::vector<coordinate_pair> ret;

void FindHull(std::vector<coordinate_pair> &points, coordinate_pair &A, coordinate_pair &B) {
        if (points.empty())
            return;
        
        int idx = 0;
        double dist = distPointLine(A, B, points[0]);
        for (int i=1; i<points.size(); i++) {
            if (distPointLine(A, B, points[i]) > dist) {
                dist = distPointLine(A, B, points[i]);
                idx = i;
            }
        }
        ret.push_back(points[idx]);
        
        std::vector<coordinate_pair> R, T;
        for (int i=0; i<points.size(); i++) {
            if (i != idx) {
                int tmp = testSide(A, points[idx], points[i]);
                if (tmp >= 0)
                    R.push_back(points[i]);
                else {
                    tmp = testSide(points[idx], B, points[i]);
                    if (tmp >= 0)
                        T.push_back(points[i]);
                }
            }
        }
        FindHull(R, A, points[idx]);
        FindHull(T, points[idx], B);
        
        return;
    }

    std::vector<coordinate_pair> outerTrees(std::vector<coordinate_pair>& points) {
        // find the convex hull; use QuickHull algorithm
        if (points.size() <= 1)
            return points;
        
        // find the left most and right most two points
        sort(points.begin(), points.end(), mycmp);
        ret.push_back(points[0]);
        ret.push_back(points.back());
        
        // test whether a point on the left side right side or on the line
        std::vector<coordinate_pair> Left, Right, Online;
        for (int i=1; i<points.size()-1; i++) {
            int tmp = testSide(points[0], points.back(), points[i]);
            if (tmp < 0)
                Right.push_back(points[i]);
            else if (tmp > 0)
                Left.push_back(points[i]);
            else
                Online.push_back(points[i]);
        }
        // if Upper or Down is empty, Online should be pushed into ret
        if (Left.empty() || Right.empty())
            for (int i=0; i<Online.size(); i++)
                ret.push_back(Online[i]);

        FindHull(Left, points[0], points.back());
        FindHull(Right, points.back(), points[0]);
        
        return ret;
    }