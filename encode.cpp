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

#include <iostream>
#include "base64.h"
#include <filesystem>

#define NBLOCKS     4

int main(int argc, char const *argv[])
{
    if(argc < 2){
        std::cerr << "encode <input file> [output file]\n"
            "If no output file is provided, the result will"
            " be written to standard output\n";
        return 1;
    }
    FILE *fIn = fopen(argv[1], "rb");
    if(!fIn){
        perror(argv[1]); return 1;
    }
    FILE* output = argc > 2? fopen(argv[2], "w") : stdout;
    if(!output){
        perror(argv[2]);
        return 1;
    }
    size_t n = std::filesystem::file_size(argv[1]);
    unsigned char buf[3 * NBLOCKS];
    char outBuf[4 * NBLOCKS + 1]{0};
    size_t k;
    while ((k = fread(buf, 1, sizeof(buf), fIn)))
    {
        char *p = base64::encode(buf, k, outBuf);
        fwrite(outBuf, 1, p - outBuf, output);
    }
    fclose(fIn);
    
    return 0;
}
