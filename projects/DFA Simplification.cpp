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
    ll n, mark = 1;
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
        v[find_string(test[0], state)].pb({find_string(test[1], lan), find_string(test[2], state)});
    }
    // group state    0 1
    pair<pii, pii> doo[state.size()], goo[state.size()];
    for(int i = 0; i < state.size(); i++)
    {
        bool is = 1;
        sort(v[i].begin(), v[i].end());
        for(int j = 0; j < final_state.size(); j++)
            if(final_state[j] == state[i])
                doo[i] = {{1, i} , {v[i][0].S, v[i][1].S}}, goo[i] = doo[i], is = 0;
        if(is)
            doo[i] = {{0, i} , {v[i][0].S, v[i][1].S}}, goo[i] = doo[i];
    }
    do
    {
        for(int i = 0; i < state.size(); i++)
        {
            int index = -1;
            for(int j = 0; j < state.size(); j++)
                if(v[doo[i].F.S][0].S == doo[j].F.S)
                    index = j, j = state.size();
            doo[i].S.F = doo[index].F.F;
            for(int j = 0; j < state.size(); j++)
                if(v[doo[i].F.S][1].S == doo[j].F.S)
                    index = j, j = state.size();
            doo[i].S.S = doo[index].F.F;
        }
        doo[0].F.F = 0;
        for(int i = 1; i < state.size(); i++)
            if(doo[i].F.F == doo[i - 1].F.F)
                if(doo[i].S.S != doo[i - 1].S.S || doo[i].S.F != doo[i - 1].S.F)
                {
                    doo[i].F.F = doo[i - 1].F.F + 1;
                    sort(doo, doo + state.size());
                    i--;
                }
        sort(doo, doo + state.size());
        sort(goo, goo + state.size());
        mark = 0;
        for(int i = 0; i < state.size(); i++)
            if(doo[i] != goo[i])
                goo[i] = doo[i], mark = 1;
    }while(mark);
    ll ans =  doo[state.size() - 1].F.F + 1;
    cout << ans;
}
