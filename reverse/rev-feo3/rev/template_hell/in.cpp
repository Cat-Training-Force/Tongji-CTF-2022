#include <iostream>
#include <algorithm>

constexpr char flag[] = "tjctf{dO_YoU_L1K3_73mPlA73}";

template <size_t N>
struct StringWrapper
{
    constexpr StringWrapper(const char (&str)[N])
    {
        std::copy_n(str, N, value);
    }
    char value[((N - 1) | 7) + 1] {};
};

template <char V1, char V2, char V3, char V4>
struct Pack
{
    static constexpr uint32_t Result = (V1 << 24) | (V2 << 16) | (V3 << 8) | V4;
};

template <uint64_t ...>
struct Buffer {};

template <size_t R, uint32_t S, uint32_t V0, uint32_t V1, uint32_t K0, uint32_t K1, uint32_t K2, uint32_t K3>
struct EncryptRound2;

template <size_t R, uint32_t S, uint32_t V0, uint32_t V1, uint32_t K0, uint32_t K1, uint32_t K2, uint32_t K3>
struct EncryptRound1
{
    static constexpr uint64_t Result = EncryptRound2<R, S, V0 + (((V1<<4) + K0) ^ (V1 + S) ^ ((V1>>5) + K1)), V1, K0, K1, K2, K3>::Result;
};

template <uint32_t S, uint32_t V0, uint32_t V1, uint32_t K0, uint32_t K1, uint32_t K2, uint32_t K3>
struct EncryptRound1<32, S, V0, V1, K0, K1, K2, K3>
{
    static constexpr uint64_t Result = (uint64_t)V0 + ((uint64_t)V1<<32);
};

template <size_t R, uint32_t S, uint32_t V0, uint32_t V1, uint32_t K0, uint32_t K1, uint32_t K2, uint32_t K3>
struct EncryptRound2
{
    static constexpr uint64_t Result = EncryptRound1<R + 1, S + 0x9e3779b9, V0, V1 + (((V0<<4) + K2) ^ (V0 + S) ^ ((V0>>5) + K3)), K0, K1, K2, K3>::Result;
};

template <size_t I, StringWrapper S, uint32_t K1, uint32_t K2, uint32_t K3, uint32_t K4, uint64_t ... B>
struct EncryptInner
{
    using Result = typename EncryptInner<I - 8, S, K1, K2, K3, K4, EncryptRound1<0, 0x9e3779b9, Pack<S.value[I - 1], S.value[I - 2], S.value[I - 3], S.value[I - 4]>::Result, Pack<S.value[I - 5], S.value[I - 6], S.value[I - 7], S.value[I - 8]>::Result, K1, K2, K3, K4>::Result, B...>::Result;
};

template <StringWrapper S, uint32_t K1, uint32_t K2, uint32_t K3, uint32_t K4, uint64_t ... B>
struct EncryptInner<0, S, K1, K2, K3, K4, B...>
{
    using Result = Buffer<B...>;
};

template <StringWrapper S, uint32_t K1, uint32_t K2, uint32_t K3, uint32_t K4>
struct Encrypt
{
    using Result = typename EncryptInner<sizeof(S), S, K1, K2, K3, K4>::Result;
};

template <class T, class U>
struct Compare
{
    static constexpr bool Result = false;
};

template <class T>
struct Compare<T, T>
{
    static constexpr bool Result = true;
};

int main()
{
    if (Compare<Encrypt<flag, 1, 2, 3, 4>::Result, Buffer<10435682917396780182ul, 11573329636734790446ul, 16744400265220154028ul, 17205172499520047268ul>>::Result)
        std::cout << "Correct! Your flag is " << flag << std::endl;
    else
        std::cout << "Wrong!" << std::endl;
    return 0;
}