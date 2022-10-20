# base64-cpp

A simple modern C++ implementation of base64 encoding/decoding.

## The API

The API consists in a class with two static public methods:

```cpp
class base64
{
public:
    template<class in_iter, class out_iter>
    static out_iter encode(in_iter first, size_t n, out_iter output);
    template<class in_iter, class out_iter>
    static out_iter decode(in_iter first, size_t n, out_iter out);
};
```

See [base64.h](base64.h) for the complete description of these two functions.

## Examples

[encode.cpp](encode.cpp) and [decode.cpp](decode.cpp) are two examples programs,
that can encode or decode the provided input file. They can be built with any
compiler, provided it has C++17 support.