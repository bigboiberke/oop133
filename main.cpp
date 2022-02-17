#include <iostream>
  using namespace std;

int divisorSum(int n)
{
    int sum = 0;

    for(int i = 1; i <= n; ++i)
    {

        for(int j = 1; j * j <= i; ++j)
        {
            if (i % j == 0)
            {
                if (i / j == j)
                    sum += j;
                else
                    sum += j + i / j;
            }
        }
    }
    return sum;
}


int main()
{
    int n = 4;
    cout << " " << divisorSum(n) << endl;

    n = 5;
    cout << " " << divisorSum(n);

    return 0;
}