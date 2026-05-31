#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int n, quantums;
    
    cout << "Enter number of processes: ";
    cin >> n;

    int burstTime[n];
    int remainingTime[n];
    int completed = 0;
    int time = 0;
    int completedTime[n];
    int waitingTime[n];
    int turnAround[n];

    cout << "Enter the burst time: \n";
    for (int i = 0; i < n; ++i)
    {
        cout << "Enter P. " << i + 1 << ": ";
        cin >> burstTime[i];
    }

    cout << "Enter the time quantum: ";
    cin >> quantums;

    for (int i = 0; i < n; ++i)
    {
        remainingTime[i] = burstTime[i];
    }

    cout << "Execution order: \n";
    while (completed < n)
    {
        for (int i = 0; i < n; ++i)
        {
            if (remainingTime[i] > 0)
            {
                if (remainingTime[i] > quantums)

                {
                    time += quantums;
                    remainingTime[i] -= quantums;

                    cout << "P " << i + 1 << " -> ";
                }
                else
                {
                    time += remainingTime[i];
                    remainingTime[i] = 0;
                    completed++;

                    completedTime[i] = time;

                    cout << "P " << i + 1 << " -> ";
                }
            }
        }
    }
    cout << "\n\n Process Time: \n";

    for(int i = 0 ; i < n ; ++i)
    {
        turnAround[i] = completedTime[i];
        waitingTime[i] = turnAround[i] - burstTime[i];
    }

    cout << "P \t BT \t CT \t TAT \t WT\n";
    for(int i = 0 ; i < n ; ++i)
    {
        cout << "P " << i + 1 << "\t"
            << burstTime[i] << "\t"
            << completedTime[i] << "\t"
            << turnAround[i] << "\t"
            << waitingTime[i] << "\n";
    }

    return 0;
}
