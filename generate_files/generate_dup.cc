#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

int main ()
{
    char filename[50];
    unsigned long long size = 134217728; // 128M
    int x;

    for (int i = 10; i < 64; ++i) {

        sprintf (filename, "contention_%d", i);

        std::ofstream outfile;
        outfile.open(filename, std::ios::binary | std::ios::out);
        std::cout << "Generating " << filename << std::endl;
        for (unsigned long long i = 0; i < size / sizeof(int); ++i) {
            x = rand();
            outfile.write((char*)&x, sizeof(int)); // sizeof can take a type
        }

        outfile.close();
    }
}