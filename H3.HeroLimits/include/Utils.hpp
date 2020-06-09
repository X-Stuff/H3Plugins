#pragma once
/*
    version: 0.0.1

    MIT License

    Copyright (c) 2020 Kaplin Dmitry ( https://t.me/dimitry_kaplin )

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/


/*
 * Declare enum class with ToString() function:
 *
 *   String values are the same as declared in enum. i.e: `cls::ToString(cls::ENUM_VALUE) == "ENUM_VALUE"`
 *
 *   Enum items cannot have specific integer values. i.e. `DECLARE_ENUM_CLASS(cls, value=228)` - will not work
 *
 *   Example of usage:
 *   ```
 *   DECLARE_ENUM_CLASS(MyEnum, First, Second, Third);
 *   // ...
 *   for (auto i = MyEnum::FIRST + 1; i < MyEnum::LAST; ++i)
 *   {
 *       std::cout << MyEnum::ToString(i);
 *   }
 *   ```
 */
#define DECLARE_ENUM_CLASS(name, ...) \
class name\
{\
private: \
    static constexpr char Names[] = #__VA_ARGS__;\
public: \
    enum Values { FIRST = 0, __VA_ARGS__, LAST }; \
    static inline std::string ToString(Values item)\
    {\
        /* Invalid item     */ if (item >= Values::LAST || item <= Values::FIRST) { return ""; }\
        size_t desiredWord = (int)item - 1; \
        int wordStart{ 0 }, wordSize{ 0 }, currentWordIndex{ -1 };\
        \
        for (size_t i = 0; i < sizeof(Names); i++, wordSize++) \
        {\
            if (Names[i] == ',' || (i + 1) == sizeof(Names) )\
            {\
                if (++currentWordIndex == desiredWord)\
                {\
                    return std::string(&Names[wordStart], wordSize);\
                }\
                while (i < sizeof(Names) && ::isspace(Names[i++])); /*fast forward to letter*/ \
                wordStart = i; wordSize = 0;\
            }\
        }\
        return "";\
    }\
};\
inline void operator++ (name::Values& value) { value = static_cast<name::Values>(static_cast<int>(value) + 1); }\
inline name::Values operator+ (const name::Values& value, const int& i) { return static_cast<name::Values>(static_cast<int>(value) + i); }