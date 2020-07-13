CXX = g++

all:
	$(CXX) -I./ chess.cpp chess-ui.cpp -o chess $(CXXFLAGS)
