#include <bits/stdc++.h>
using namespace std;

// CONSTANTS
const string NOT_SIGN = "~";
const int TOTAL_NODE = 26 * 2;

// GLOBAL ARRAYs
vector<vector<int>> graph(TOTAL_NODE, vector<int>());
vector<vector<int>> reverseGraph(TOTAL_NODE, vector<int>());
vector<bool> exists(TOTAL_NODE, false);
vector<bool> visited(TOTAL_NODE, false);

// ============================================================================= //
// ===================== INPUT PROCESSING & GRAPH BUILDING ===================== //
// ============================================================================= //

// a = 0, ~a = 1, b = 2, ~b = 3, ab = -1, ~dc = -1
int toNode(string &str)
{
    if(!isalpha(str[str.size() - 1])) return -1;
    return (str[str.size() - 1] - 'a') * 2 + (str.size() > 1);
}

string toString(int val)
{
    string str;
    if(val & 1) str += NOT_SIGN;
    str += (char)('a' + val / 2);
    return str;
}

int complement(int node)
{
    return node ^ 1; // 0 -> 1, 1 -> 0, 2 -> 3, 3 -> 2 , xor changes parity of last bit 
}

void addEdge(int u, int v)
{
    graph[u].push_back(v);
    reverseGraph[v].push_back(u);
    exists[u] = exists[v] = true; // mark u, v as exists
    exists[complement(u)] = exists[complement(v)] = true; // mark ~u, ~v as exists
}

void parseInputLine(string &line)
{
    int i = 0, literalCount = 0;
    vector<int> nodes(2);
    while (i < line.size())
    {
        if (line[i] != ' ')
        {
            string str;
            while (i < line.size() && line[i] != ' ') str += line[i++]; // split by space and get first one/two literals
            nodes[literalCount++] = toNode(str);
            if(literalCount >= 2) break;
        }
        i++;
    }

    if(literalCount == 2)
    {
        // a or b , both cant be false so if one is false other must be true
        addEdge(complement(nodes[0]), nodes[1]); // ~a -> b and reverese graph b -> ~a
        addEdge(complement(nodes[1]), nodes[0]); // ~b -> a and reverese graph a -> ~b
    }
    else if(literalCount == 1)
    {
        addEdge(complement(nodes[0]), nodes[0]); // ~a -> a and reverese graph a -> ~a
    }
}

// ========================================================================= //
// ===================== SCC AND SCC-INDEX CALCULATION ===================== //
// ========================================================================= //

void dfsSortByOutTime(int node, vector<int> &order)
{
    visited[node] = true;
    for(int curr : graph[node])
    {
        if(!exists[curr] || visited[curr]) continue;
        dfsSortByOutTime(curr, order);
    }
    order.push_back(node);
}

void dfsGetSCC(int node, vector<int> &sccIndexList, int sccIndex)
{
    visited[node] = true;
    sccIndexList[node] = sccIndex;
    for(int curr : reverseGraph[node])
    {
        if(!exists[curr] || visited[curr]) continue;
        dfsGetSCC(curr, sccIndexList, sccIndex);
    }
}

// ========================================================= //
// ===================== MAIN FUNCTION ===================== //
// ========================================================= //

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n; 
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string inputStr;
        getline(cin >> ws, inputStr);
        parseInputLine(inputStr);
    }

    // Kosaraju's Algorithm for SCC and SCC-Index Calculation 

    // 1. Sort nodes by out time
    visited.resize(TOTAL_NODE, false);
    vector<int> order;
    for (int i = 0; i < TOTAL_NODE; i++)
    {
        if(!exists[i] || visited[i]) continue;
        dfsSortByOutTime(i, order); 
    }
    reverse(order.begin(), order.end()); // reverse to get sorted by out time 

    // 2. DFS on reverse graph in order of out time
    fill(visited.begin(), visited.end(), false); // reset visited
    vector<int> ccIndexList(TOTAL_NODE, 0);
    int ccIndex = 1;
    for(int node : order)
    {
        if(!exists[node] || visited[node]) continue;
        dfsGetSCC(node, ccIndexList, ccIndex);
        ccIndex++;
    }

    bool possible = true;
    vector<int> assignment(TOTAL_NODE, true);
    for (int i = 0; i < TOTAL_NODE; i++)
    {
        if(!exists[i]) continue; // if node does not exist then no need to check (just for optimization)

        if(ccIndexList[i] == ccIndexList[complement(i)]) // i -...-> ~i -...-> i , No possbile valid assignment as any assignment creates contradiction
        {
            possible = false;
            break;
        }
        else if(ccIndexList[i] < ccIndexList[complement(i)]) // i -...-> ~i , So if i is true then ~i must be false, which is contradiction. So, i must be false and ~i must be true
        {
            assignment[i] = false;
            assignment[complement(i)] = true;
        }
        else // ~i -...-> i , So if ~i is true then i must be false, which is contradiction. So, ~i must be false and i must be true
        {
            assignment[i] = true;
            assignment[complement(i)] = false;
        }
    }
    
    if(possible)
    {
        for (int i = 0; i < 26; i++)
        {
            if(!exists[i*2]) continue;
            cout << toString(i*2) << " " << (assignment[i*2]? "true" : "false") << endl;
        }
    }
    else
    {
        cout << "No assignment possible";
    }

    return 0;
}

// py check.py input.txt output.txt