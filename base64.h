#pragma once

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

#include <stdint.h>

class base64
{
private:
    static constexpr const char* _table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    static constexpr char _inv_table[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0, 63, 52, 53, 54, 55, 56, 
        57, 58, 59, 60, 61, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0, 0, 0, 0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
    };
public:
    /**
     * Encodes the data pointed at by first into base64
     * @tparam in_iter: Input iterator type. Must satisfy the requirements of LegacyInputIterator
     * @tparam out_iter: Output iterator type. Must satisfy the requirements of LegacyOutputIterator
     * @param first: An iterator to the beginning of the data
     * @param n: The size of the data to be encoded, in bytes
     * @param output: An iterator in which the encoded data will be written
     * @return An iterator pointing to just after the end of the encoded data
    */
    template<class in_iter, class out_iter>
    static inline out_iter encode(in_iter first, size_t n, out_iter output)
    {
        uint32_t buf;
        for(; n > 2; n -= 3){
            buf = *first++;
            buf = (buf << 8) | *first++;
            buf = (buf << 8) | *first++;
            *output++ = _table[(buf >> 18) & 63];
            *output++ = _table[(buf >> 12) & 63];
            *output++ = _table[(buf >>  6) & 63];
            *output++ = _table[buf & 63];
        }
        switch (n)
        {
        case 1:
            buf = (uint32_t)*first++ << 4;
            *output++ = _table[buf >> 6];
            *output++ = _table[buf & 63];
            *output++ = '=';
            break;
        case 2:
            buf = *first++;
            buf = (buf << 10) | ((uint32_t)*first++ << 2);
            *output++ = _table[buf >> 12];
            *output++ = _table[(buf >> 6) & 63];
            *output++ = _table[buf & 63];
            break;
        default: return output;
        }
        *output++ = '=';
        return output;
    }
     /**
     * Decodes the base64 string pointed at by first
     * @tparam in_iter: Input iterator type. Must satisfy the requirements of LegacyInputIterator
     * @tparam out_iter: Output iterator type. Must satisfy the requirements of LegacyOutputIterator
     * @param first: An iterator to the beginning of the base64 string
     * @param n: The length of the base64 string. If n is not a multiple of 4, 
     * the characters of the incomplete block will be ignored
     * @param output: An iterator in which the decoded data will be written
     * @return An iterator pointing to just after the end of the decoded data
    */
    template<class in_iter, class out_iter>
    static inline out_iter decode(in_iter first, size_t n, out_iter out)
    {
        n &= ~3ULL;
        uint32_t buf;
        for(; n != 4; n -= 4)
        {
            buf = _inv_table[*first++];
            buf = (buf << 6) | _inv_table[*first++]; 
            buf = (buf << 6) | _inv_table[*first++]; 
            buf = (buf << 6) | _inv_table[*first++];
            *out++ = buf >> 16;
            *out++ = (buf >> 8) & 0xff;
            *out++ = buf & 0xff;
        }
        for(n = buf = 0; *first != '=' && n < 4; ++n)
            buf = (buf << 6) | _inv_table[*first++];
        switch (n)
        {
        case 2:
            *out++ = buf >> 4;
            break;
        case 3:
            *out++ = buf >> 10;
            *out++ = (buf >> 2) & 0xff;
            break;
        case 4:
            *out++ = buf >> 16;
            *out++ = (buf >> 8) & 0xff;
            *out++ = buf & 0xff;
            break;
        default: break;
        }
        return out;
    }
};
