# builtin-系列函数

## 内置函数系列：\_\_builtin\_\_

在 C++编程中，我们经常需要进行位运算操作。为了方便处理二进制数，C++提供了一组内置函数，称为`__builtin__`系列函数。这些函数能够高效地执行一些位运算操作，使得我们可以更方便地处理二进制数据。本篇文章将介绍一些常用的`__builtin__`函数。

### 1. \_\_builtin_popcount(x)

`__builtin_popcount(x)`函数用于统计一个数 x 的二进制表示中有多少个 1。例如，对于数值 x=5（二进制表示为 101），`__builtin_popcount(x)`的返回值为 2，表示二进制数中有 2 个 1。

### 2. \_\_builtin_clz(x)

`__builtin_clz(x)`函数用于统计一个数 x 的二进制表示中有多少个前导 0。注意，这里要计算表示符号的第一位。可以将其理解为计算前导零的个数（count leading zeroes）。例如，对于数值 x=8（二进制表示为 1000），`__builtin_clz(x)`的返回值为 28，表示二进制数中有 28 个前导 0。

### 3. \_\_builtin_ctz(x)

`__builtin_ctz(x)`函数用于统计一个数 x 的二进制表示中末尾有多少个 0。可以将其理解为计算末尾零的个数（count trailing zeroes）。例如，对于数值 x=16（二进制表示为 10000），`__builtin_ctz(x)`的返回值为 4，表示二进制数中有 4 个末尾 0。

### 4. \_\_builtin_ffs(x)

`__builtin_ffs(x)`函数用于统计一个数 x 的二进制表示中最后一个 1 是从后往前的第几位。例如，对于数值 x=10（二进制表示为 1010），`__builtin_ffs(x)`的返回值为 2，表示二进制数中最后一个 1 是从后往前的第 2 位。

### 5. \_\_builtin_parity(x)

`__builtin_parity(x)`函数用于判断一个数 x 的二进制表示中 1 的个数的奇偶性。返回值为 1 表示 1 的个数为奇数，返回值为 0 表示 1 的个数为偶数。这里的 parity 表示"奇偶性"。例如，对于数值 x=6（二进制表示为 110），`__builtin_parity(x)`的返回值为 0，表示二进制数中 1 的个数为偶数。

需要注意的是，以上函数仅适用于`int`或`unsigned int`范围内的数值。如果超出此范围，需要在函数末尾加上"ll"，例如`__builtin_popcount(x)`应改为`__builtin_popcountll(x)`，在`__builtin_clz(x)`中也因总位数不同而答案有所不同。

另外，C++20 引入了`<bit>`库，并定义了`std::popcount`函数，功能与`__builtin_popcount`相同。`std::popcount`函数的使用方式如下：

```cpp
template<class T>
constexpr int popcount(T x) noexcept;
```

如果你对这些函数的复杂度感兴趣，可以参考[Codeforces 上关于\_\_builtin_popcount()的复杂度证明](https://codeforces.com/blog/entry/59268?#comment-428632)。

## Tips

在使用`__builtin__`系列函数时，有几个注意事项需要注意：

平台兼容性：`__builtin__`系列函数是 GCC 和 Clang 编译器的扩展功能，因此在使用这些函数时，需要确保编译器支持这些扩展。如果你使用的是其他编译器，这些函数可能不可用或具有不同的实现方式。

优化建议：`__builtin__`系列函数通常比手动实现的位运算更高效，因为编译器可以根据硬件平台和编译选项进行优化。然而，对于一些简单的位运算操作，编译器可能会自动进行优化，因此在使用`__builtin__`函数之前，最好进行性能测试，以确定是否真正需要使用这些函数。

> 参考链接：
>
> - [C++ Reference - std::popcount](https://zh.cppreference.com/w/cpp/numeric/popcount)
