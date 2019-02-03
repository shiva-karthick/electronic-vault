#include <iostream>

using namespace std;
int main()
{
    int security_key_array[4] = {0, 0, 0, 0};
    int pointer_counter = 0;
    unsigned int digit1 = 0;
    unsigned int digit2 = 0;
    unsigned int digit3 = 0;
    unsigned int digit4 = 0;

    if (*security_key_array == 0)
    {

        security_key_array[pointer_counter] = digit1;
        ++pointer_counter;
    }
    else if (*(security_key_array + pointer_counter) == 0)
    {

        security_key_array[pointer_counter] = digit2;
        ++pointer_counter;
    }
    else if (*(security_key_array + pointer_counter) == 0)
    {

        security_key_array[pointer_counter] = digit3;
        ++pointer_counter;
    }
    else if (*(security_key_array + pointer_counter) == 0)
    {

        security_key_array[pointer_counter] = digit4;
    }

    return 0;
}