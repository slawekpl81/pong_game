sfml-lib = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
cpp-std = c++17


start: build
# 	echo "*** Run APP ***"
	./sfml-app

build:
# 	echo "*** Build APP ***"
	$(CXX) main.cpp Bat.cpp Ball.cpp -std=$(cpp-std) -o sfml-app $(sfml-lib)



clear:
	rm -f sfml-app
