all:
	g++ -Wall LatticeVisualizer.cpp BinRelation.cpp Poset.cpp Node.cpp -lSDL2 -o lv
