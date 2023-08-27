#include <bits/stdc++.h>
using namespace std;

vector<int> adj[52]; // (a-z), (~a-~z)
vector<int> rev_adj[52];
vector<bool> vis;
vector<bool> added;
vector<int> cc_count_array;
vector<bool> ans;
vector<int> serial;
int scc_count = 0;

int toNegate(int a)
{
    if (a < 26)
    {
        return a + 26;
    }
    else
    {
        return a - 26;
    }
}

void buildEdge(int u, int v)
{
    adj[u].push_back(v);
    rev_adj[v].push_back(u);
    added[u] = true;
    added[v] = true;
    added[toNegate(u)] = true;
    added[toNegate(v)] = true;
}

void dfs1(int node)
{
    vis[node] = true;
    for(auto curr : adj[node])
    {
        if(added[curr] && !vis[curr])
        {
            dfs1(curr);
        }
    }
    serial.push_back(node);
}

void dfs2(int node)
{
    vis[node] = true;
    cc_count_array[node] = scc_count;
    for(auto curr : rev_adj[node])
    {
        if(added[curr] && !vis[curr])
        {
            dfs2(curr);
        }
    }
}

string pr(int i)
{
    string str = "";
    if(i < 26)
    {
        str += (char)(i + 'a');
    }
    else
    {
        str = "~";
        str += (char)(i + 'a' - 26);
    }
    return str;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    vis.resize(52, false);
    added.resize(52, false);
    ans.resize(52, false);
    cc_count_array.resize(52, -1);

    int line_number;
    cin >> line_number;
    cin.ignore();

    for (int i = 0; i < line_number; i++)
    {
        string s;
        getline(cin, s);

        int u = -1, v = -1;

        if (s.size() == 1)
        {
            u = s[0] - 'a';
            buildEdge(toNegate(u), u);
        }
        else if (s.size() == 2)
        {
            u = s[1] - 'a';
            buildEdge(u, toNegate(u));
        }
        else if (s.size() == 3)
        {
            u = s[0] - 'a';
            v = s[2] - 'a';
            buildEdge(toNegate(u), v);
        }
        else if (s.size() == 4)
        {
            if (s[0] == '~')
            {
                u = s[1] - 'a';
                v = s[3] - 'a';
                buildEdge(u, v);
            }
            else
            {
                u = s[0] - 'a';
                v = s[3] - 'a';
                buildEdge(toNegate(u), toNegate(v));
            }
        }
        else if (s.size() == 5)
        {
            u = s[1] - 'a';
            v = s[4] - 'a';
            buildEdge(u, toNegate(v));
        }
    }
    
    fill(vis.begin(), vis.end(), false);
    for (int i = 0; i < 52; i++)
    {
        if(added[i] && !vis[i])
        {
            dfs1(i);
        }
    }
    reverse(serial.begin(), serial.end());
    
    fill(vis.begin(), vis.end(), false);
    scc_count = 0;
    for (int j = 0; j < serial.size(); j++)
    {
        int i = serial[j];
        if(added[i] && !vis[i])
        {
            scc_count++;
            dfs2(i);
        }
    }

    bool result = true;
    for(int i = 0; i < 26; i++)
    {
        if(added[i])
        {
            if(cc_count_array[i] == cc_count_array[toNegate(i)])
            {
                result = false;
                break;
            }
            else if(cc_count_array[i] < cc_count_array[toNegate(i)])
            {
                ans[i] = false;
                ans[toNegate(i)] = true;
            }
            else
            {
                ans[i] = true;
                ans[toNegate(i)] = false;
            }
        }
    }

    if(result)
    {
        for (int i = 0; i < 26; i++)
        {
            if(added[i])
            {
                if(ans[i])
                {
                    cout << (char)(i+'a') << ' ' << "true" << endl;
                }
                else
                {
                    cout << (char)(i+'a') << ' ' << "false" << endl;
                }
            }
        }
    }
    else
    {
        cout << "No assignment possible";
    }

    return 0;
}
