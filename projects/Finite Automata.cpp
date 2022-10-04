#include <bits/stdc++.h>
#define ll long long
#define F first
#define S second
#define pii pair<ll, ll>
#define pb push_back

using namespace std;

const ll maxn = 2e5, inf = 1e9;
vector <pii> v[maxn];

ll find_string(string s, vector <string> findd)
{
    for(int i = 0; i < findd.size(); i++)
        if(s == findd[i])
            return i;
    return -1;
}

int main()
{
    ll n, counter = 0, ans =0;
    string s[3], now = "";
    cin >> s[0] >> s[1] >> s[2] >> n;
    vector <string> state, lan, final_state;
    for(int i = 1; i < s[0].size(); i++)
        s[0][i] != ',' && i != s[0].size() - 1 ? (now += s[0][i]) : (state.pb(now), now = "");
    for(int i = 1; i < s[1].size(); i++)
        s[1][i] != ',' && i != s[1].size() - 1 ? (now += s[1][i]) : (lan.pb(now), now = "");
    for(int i = 1; i < s[2].size(); i++)
        s[2][i] != ',' && i != s[2].size() - 1 ? (now += s[2][i]) : (final_state.pb(now), now = "");
    for(int i = 0; i < n; i++)
    {
        now = "";
        string ss;
        cin >> ss;
        vector <string> test;
        for(int j = 0; j < ss.size(); j++)
            ss[j] != ',' ? (now += ss[j]) : (test.pb(now), now = "");
        test.pb(now);
        if(test[1] == "$")
            v[find_string(test[0], state)].pb({find_string(test[2], state), inf});
        else
            v[find_string(test[0], state)].pb({find_string(test[2], state),find_string(test[1], lan)});
    }
    cin >> now;
    queue <pii> q;
    q.push({0, -1});
    while(q.size() != 0)
    {
        pii ss = q.front();
        q.pop();
        string goo = "";
        goo += now[ss.S + 1];
        if(ss.S == now.size() - 1)
        {
            if(-1 != find_string(state[ss.F], final_state))
                ans = 1;
        }
        else
        {
            for(int i = 0; i < v[ss.F].size(); i++)
                if(v[ss.F][i].S == inf)
                    q.push({v[ss.F][i].F, ss.S});
            for(int i = 0; i < v[ss.F].size(); i++)
                if(v[ss.F][i].S == find_string(goo, lan))
                    q.push({v[ss.F][i].F, ss.S + 1});
        }
    }
    ans ? cout << "Accepted" : cout << "Rejected";
}
