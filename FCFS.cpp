#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
     cout<<"Enter the number of process: ";
    cin >> n;

    vector<int> at(n), bt(n), id(n);
    vector<int> wt(n), tat(n);

    cout<<"Enter the arrival time: ";
    for (int i = 0; i < n; i++) {
        cin >> at[i];
        id[i] = i + 1;
    }

    cout<<"Enter the burst time: ";

    for (int i = 0; i < n; i++) {
        cin >> bt[i];
    }

    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;

    sort(idx.begin(), idx.end(), [&](int a, int b) {
        if (at[a] == at[b]) return id[a] < id[b];
        return at[a] < at[b];
    });

    int time = 0;
    double totalWT = 0, totalTAT = 0;

    vector<int> finalWT(n), finalTAT(n);

    // Gantt Chart
    cout << "\nGantt Chart:\n|";

    for (int i = 0; i < n; i++) {
        int k = idx[i];

        if (time < at[k]) {
            cout << " Idle |";
            time = at[k];
        }

        cout << " P" << id[k] << " |";

        wt[k] = time - at[k];
        tat[k] = wt[k] + bt[k];

        finalWT[k] = wt[k];
        finalTAT[k] = tat[k];

        time += bt[k];

        totalWT += wt[k];
        totalTAT += tat[k];
    }

    cout << "\n0";
    time = 0;

    for (int i = 0; i < n; i++) {
        int k = idx[i];

        if (time < at[k]) {
            time = at[k];
            cout << "    " << time;
        }

        time += bt[k];
        cout << "    " << time;
    }


    cout << "\n\nProcess| Arrival Time| Burst Time| Waiting Time| TurnAround Time\n";

    for (int i = 0; i < n; i++) {
        cout << "  P" << id[i] << "         "
             << at[i] << "            "
             << bt[i] << "           "
             << finalWT[i] << "             "
             << finalTAT[i] << endl;
    }

    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage TurnAround Time: " << totalTAT / n;

    return 0;
}
