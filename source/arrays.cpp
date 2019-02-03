#include <iostream>

using namespace std;
int main()
{
    int security_key_array[4] = {0, 0, 0, 0};
    int pointer_counter = 0;
    int temporary_digit;
    unsigned int digit1 = 0;
    unsigned int digit2 = 0;
    unsigned int digit3 = 0;
    unsigned int digit4 = 0;

    if (*security_key_array == 0)
    {
        cout << "Enter a number" << endl;
        cin >> digit1;
        security_key_array[pointer_counter] = digit1;
        ++pointer_counter;
    }
    else if (*(security_key_array + pointer_counter) == 0)
    {
        cout << "Enter 2nd number" << endl;
        cin >> digit2;
        security_key_array[pointer_counter] = digit2;
        ++pointer_counter;
    }
    else if (*(security_key_array + pointer_counter) == 0)
    {
        cout << "Enter 3rd number" << endl;
        cin >> digit3;
        security_key_array[pointer_counter] = digit3;
        ++pointer_counter;
    }
    else if (*(security_key_array + pointer_counter) == 0)
    {
        cout << "Enter 4th number" << endl;
        cin >> digit4;
        security_key_array[pointer_counter] = digit4;
    }

    for (int i = 0; i < 4; i++)
    {
        cout << security_key_array[i] << " ";
    }
    // temporary_digit = *(security_key_array + pointer_counter); //moving the pointer by 4 from start
    // std::cout << "Array Val: " << temporary_digit << std::endl;

    // // print address of the array's first element
    // cout << "Element 0 has address: " << &array[0] << '\n';
    // cout << "Element 1 has address: " << &array[1] << '\n';

    // // print the value of the pointer the array decays to
    // cout << "The array decays to a pointer holding address: " << array << '\n';

    return 0;
}