

.PHONY: all
all : convexHull435

convexHull435 : convexHull435.o JarvisMarch.o
	g++ JarvisMarch.o convexHull435.o -o convexHull435

convexHull435.o : convexHull435.cpp JarvisMarch.hpp
	g++ -std=c++17 -c convexHull435.cpp

Graham.o : Graham.cpp
	g++ -std=c++11 -c Graham.cpp

Jarvis.o : JarvisMarch.cpp
	g++ -std=c++17 -c JarvisMarch.cpp

ConvexHull.o : ConvexHull.cpp
	g++ -std=c++17 -c ConvexHull.cpp

.PHONY: clean
clean :
	@rm -f *.o convexHull435 hull_G* hull_J* hull_Q*

#generates all hull_J_*.txt files with Jarvis March.
.PHONY: runJ
runJ : convexHull435
	time -o output/test_rectangle10.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J rectangle10.txt
	time -o output/test_rectangle100.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J rectangle100.txt
	time -o output/test_rectangle1000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J rectangle1000.txt
	time -o output/test_rectangle10000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J rectangle10000.txt
	time -o output/test_rectangle100000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J rectangle100000.txt
	time -o output/test_rectangle1000000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J rectangle1000000.txt
	time -o output/test_circle10.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J circle10.txt
	time -o output/test_circle100.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J circle100.txt
	time -o output/test_circle1000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J circle1000.txt
	time -o output/test_circle10000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J circle10000.txt
	time -o output/test_circle100000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J circle100000.txt
	time -o output/test_circle1000000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J circle1000000.txt
	time -o output/test_onCircle10.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J onCircle10.txt
	time -o output/test_onCircle100.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J onCircle100.txt
	time -o output/test_onCircle1000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J onCircle1000.txt
	time -o output/test_onCircle10000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J onCircle10000.txt
	time -o output/test_onCircle100000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J onCircle100000.txt
	time -o output/test_onCircle1000000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J onCircle1000000.txt
	time -o output/test_triangle10.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J triangle10.txt
	time -o output/test_triangle100.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J triangle100.txt
	time -o output/test_triangle1000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J triangle1000.txt
	time -o output/test_triangle10000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J triangle10000.txt
	time -o output/test_triangle100000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J triangle100000.txt
	time -o output/test_triangle1000000.txt -f "Program: %C\nTotal time: %E\n" ./convexHull435 J triangle1000000.txt

#.PHONY: all
#all : convexHull435

#convexHull435 : convexHull435.o Graham.o Jarvis.o ConvexHull.o
#g++ convexHull435.o Graham.o Jarvis.o ConvexHull.o -o convexHull435

#convexHull435.o : convexHull435.cc Graham.hpp Jarvis.hpp ConvexHull.hpp
#g++ -std=c++11 -c convexHull435.cc

#Graham.o : Graham.cpp
#g++ -std=c++11 -c Graham.cpp

#Jarvis.o : Jarvis.cpp
#g++ -std=c++11 -c Jarvis.cpp

#ConvexHull.o : ConvexHull.cpp
#g++ -std=c++11 -c ConvexHull.cpp

#.PHONY: clean
#clean :
#@rm -f *.o convexHull435 hull_G.txt hull_J.txt hull_Q.txt
