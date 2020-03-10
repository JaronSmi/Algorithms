struct Point 
{ 
   int x, y; 
}; 

Point nextToTop(stack<Point> &S);
int swap(Point &p1, Point &p2);
int distSq(Point p1, Point p2);
int orientation(Point p, Point q, Point r);
int compare(const void *vp1, const void *vp2);
void GrahamScan(Point points[], int n);