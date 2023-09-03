#include <bits/stdc++.h>
using namespace std;

int ct = 0;

void merge(vector<int> &arr, int start, int mid, int end)
{
    vector<int> newArr;
    int l = start, r = mid + 1;

    while(l <= mid || r <= end)
    {
        int lValue = INT_MAX;
        if(l <= mid) lValue = arr[l];
        int rValue = INT_MAX;
        if(r <= end) rValue = arr[r];

        if(lValue > rValue)
        {
            newArr.push_back(rValue);
            r++;
            ct += (mid - l + 1);
        }
        else
        {
            newArr.push_back(lValue);
            l++;
        }
    }
    for(int i = start; i <= end; i++)
    {
        arr[i] = newArr[i - start];
    }
}

void inversionCount(vector<int> &arr, int start, int end)
{
    if(start >= end) return;
    int mid = start + (end - start)/2;
    inversionCount(arr, start, mid);
    inversionCount(arr, mid+1, end);
    merge(arr, start, mid, end);
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    inversionCount(arr, 0, n-1);
    cout << ct << endl;

    return 0;
}