#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int t;
    cin >> t;
    vector<vector<int>> allpair;

    int one = 0, two = 0; // one = even count, two = odd count

    while (t--)
    {
        int n;
        cin >> n;
        vector<int> arr(n);

        for (int i = 0; i < n; ++i)
        {
            cin >> arr[i];
        }

        allpair.push_back(arr);
    }

    // Traverse all arrays
    for (int i = 0; i < allpair.size(); ++i)
    {
        for (int j = 0; j < allpair[i].size(); ++j)
        {
            if (allpair[i][j] % 2 == 0)
                one++; // count even
            else
                two++; // count odd
        }
    }

    if (one > two)
        cout << "Even more";
    else if (two > one)
        cout << "Odd more";
    else
        cout << "Equal";

    return 0;
}
