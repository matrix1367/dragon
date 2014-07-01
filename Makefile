all: clear mylib main

main: main.cpp
	g++ main.cpp -ldl -o dragon
	
mylib: mylib.cpp
	g++ -fPIC -shared mylib.cpp -o mylib.so
	
clear:
	rm -rfv *.o
	rm mylib.so
	rm dragon
