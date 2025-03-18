#include <iostream>
using namespace std;

size_t len(const char* text) noexcept __attribute__((hot)) __attribute__((pure));
size_t len(const char* text) noexcept  {
    using number_t = unsigned long long;
    const number_t* blocks = reinterpret_cast<const number_t*>(text);
    number_t response = 0;
    number_t block = 0;

    constexpr number_t mask = 0x8080808080808080;
    constexpr number_t sub  = 0x0101010101010101;
    constexpr number_t bytes = sizeof(number_t);

    while (true) {
        block = *blocks++;
        if ((block - sub) & ~block & mask) {
            const char* block_end = reinterpret_cast<const char*>(&block);
            for (number_t i = 0; i < bytes; i++) {
                if (block_end[i] == '\0') {
                    return (response * bytes) + i;
                }
            }
        }
        response++;
    }
}

int main(){
    cout << len("hello world");
}
