/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/

#include <fstream>
#include <iostream>
#include <filesystem>
#include "base64.h"

#define NBLOCKS     4

int main(int argc, char const *argv[])
{
    if(argc < 2){
        std::cerr << "decode <input file> [output file]\n"
        "If no output file is provided, the result will"
        " be written to standard output\n";
        return 1;
    }
    std::ifstream inputFile(argv[1]);
    if(!inputFile.is_open()){
        perror(argv[1]);
        return 1;
    }
    std::istreambuf_iterator<char> it(inputFile);
    size_t n = std::filesystem::file_size(argv[1]);
    if(argc < 3)
        base64::decode(it, n, std::ostreambuf_iterator<char>(std::cout));
    else{
        std::ofstream of(argv[2]);
        if(!of.is_open()){
            perror(argv[2]); return 1;
        }
        base64::decode(it, n, std::ostreambuf_iterator<char>(of));
    }
    return 0;
}
