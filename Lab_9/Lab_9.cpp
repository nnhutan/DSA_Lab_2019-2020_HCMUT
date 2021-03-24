#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

#include <algorithm>
string abc(long long int n)
{
    if (n == 2)
        return "101";
    if (n == 3)
        return "111";
    string tmp = abc(n / 2);
    if (tmp.size() > pow(10, 5))
        return tmp;
    return tmp + to_string(n % 2) + tmp;
}
long long int sumOfOnes(long long int n, long long int l, long long int r)
{
    string tan = abc(n);
    long long int m = count(tan.begin() + l, tan.begin() + r + 1, '1');
    if (l == r)
        m--;
    return m;
}

int main()
{
    long long int n = pow(2, 50);
    cout << sumOfOnes(n - 3759872349, 1, pow(10, 5));
    return 0;
}