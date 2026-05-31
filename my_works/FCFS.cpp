#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int n;
    cout << "Enter the number of process: ";
    cin >> n;

    int burstTime[n];
    int completedTime[n];
    int turnAround[n];
    int waitingTime[n];

    cout << "Enter the burst time: \n";

    for (int i = 0; i < n; ++i)
    {
        cout << "Enter P[" << i + 1 << "] : ";
        cin >> burstTime[i];
    }

    int time = 0;
    for (int i = 0; i < n; ++i)
    {
        time += burstTime[i];
        completedTime[i] = time;
    }

    for (int i = 0; i < n; ++i)
    {
        turnAround[i] = completedTime[i];
        waitingTime[i] = turnAround[i] - burstTime[i];
    }

    cout << "Process \t BurstTime \t CompletedTime \t TurnAroundTime \t WaitingTime\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "P[" << i + 1 << "] : " << "\t\t"
             << burstTime[i] << "\t\t\t"
             << completedTime[i] << "\t\t\t"
             << turnAround[i] << "\t\t\t"
             << waitingTime[i] << "\n";
    }

    return 0;
}
