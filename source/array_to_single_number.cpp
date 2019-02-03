#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int security_key_array[] = {1, 2, 3, 4};
    int result = 0;

    for (int i_result = 0; i_result < 4; i_result++)
    {
        result *= 10;
        result += security_key_array[i_result];
    }

    cout << result;
    return 0;
}
