CXX = g++ -std=c++11
FLAGS = -g

main: Expr.o Unifier.o Backchain.o
	$(CXX) $(FLAGS) main.cpp Expr.o Unifier.o Backchain.o -o proj

Expr.o:
	$(CXX) $(FLAGS) -c Expr.cpp

Unifier.o: Expr.o
	$(CXX) $(FLAGS) -c Unifier.cpp Expr.o

Backchain.o: Expr.o Unifier.o
	$(CXX) $(FLAGS) -c Backchain.cpp Expr.o Unifier.o

clean:
	rm *.o