all: compile link

compile: 
	g++ -c coins_oop.cpp -I"C:\Users\scott\libraries\SFML-2.5.1\include" -DSFML_STATIC

link:
	g++ coins_oop.o -o minions -L"C:\Users\scott\libraries\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

clean:
	rm -f main *.coins_oop
