#include <fstream>
#include <iostream>
#include <stdlib.h>

int main()
{
    int x;
    std::ofstream outfile;
    outfile.open("page_file.img", std::ios::binary | std::ios::out);
    for (unsigned long long i = 0; i < 1536 / 4 * 1024 * 1024; ++i) {
        x = rand();
        outfile.write((char*)&x, sizeof(int)); // sizeof can take a type
    }

    outfile.close();
}