// Description: Given the arrival and departure times of all trains that reach a railway station, 
// the task is to find the minimum number of platforms required for the railway station so that no train waits.

// TIME COMPLEXTIY : O(N * logN)

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n; cin >> n;
    vector<pair<int, int>> arr(n);
    for (int i = 0; i < n; i++)
    {
        int start, end;
        cin >> start >> end;
        arr[i] = {start, end};
    }
    sort(arr.begin(), arr.end());

    priority_queue<int, vector<int>, greater<int>> waitingTime;
    waitingTime.push(arr[0].second);

    int ct = 1;
    for (int i = 1; i < n; i++)
    {
        if(arr[i].first >= waitingTime.top())
        {
            waitingTime.pop();
        }
        else 
        {
            ct++;
        }
        waitingTime.push(arr[i].second);
    }
    cout << ct << endl;

    return 0;
}
