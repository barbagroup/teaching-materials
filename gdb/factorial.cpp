#include <iostream>

int factorial(int N)
{
    int fact;

    for (int i=1; i<=N; i++)
    {
  	fact = fact*i;
    }

    return fact;
}

int main()
{
    std::cout << "Enter a positive integer: " << std::endl;

    int num, num_fact;
    std::cin >> num;

    num_fact = factorial(num);

    std::cout << num << "!" << " = " << num_fact << std::endl;

    return 0;
}
