clear

g++ -c -I./include src/tinyfiledialogs.c     -o build/tinyfiledialogs.o
g++ -c -I./include src/FileController.cpp    -o build/FileController.o

g++ -c -I./include src/gui/GUI.cpp           -o build/GUI.o

g++ -c -I./include main.cpp                  -o build/main.o

g++ build/tinyfiledialogs.o  build/FileController.o \
    build/GUI.o \
    build/main.o \
    -o build/main.exe -Iinclude -lsfml-graphics -lsfml-window -lsfml-system

./build/main.exe