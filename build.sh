clear

g++ -c -I./include src/tinyfiledialogs.c     -o build/tinyfiledialogs.o
g++ -c -I./include src/FileController.cpp    -o build/FileController.o
g++ -c -I./include src/Randomizer.cpp        -o build/Randomizer.o

g++ -c -I./include src/gui/GUI.cpp           -o build/GUI.o


g++ -c -I./include src/clustering/AHC.cpp    -o build/AHC.o

g++ -c -I./include main.cpp                  -o build/main.o

g++ build/tinyfiledialogs.o  build/FileController.o build/Randomizer.o \
    build/GUI.o \
    build/AHC.o \
    build/main.o \
    -o build/main.exe -Iinclude -lsfml-graphics -lsfml-window -lsfml-system -I/usr/include

./build/main.exe