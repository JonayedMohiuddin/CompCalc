// Description: Given the arrival and departure times of all trains that reach a railway station, 
// the task is to find the minimum number of platforms required for the railway station so that no train waits.

// TIME COMPLEXTIY : O(N * 2400)

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n; cin >> n;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> arriving;
    priority_queue<int, vector<int>, greater<int>> waiting;

    for (int i = 0; i < n; i++)
    {
        int start, end;
        cin >> start >> end;
        arriving.push({start, end});
    }

    int maxAns = 0, cur = 0;
    int timer = 0;
    while(timer <= 2400)
    {
        while(waiting.size() > 0 && timer >= waiting.top())
        {
            waiting.pop();
            cur--;
        }
        while(arriving.size() > 0 && timer >= arriving.top().first)
        {
            int departure = arriving.top().second;
            arriving.pop();
            waiting.push(departure);
            cur++;
            maxAns = max(cur, maxAns);
        }

        timer++;
    }

    cout << maxAns << endl;

    return 0;
}
