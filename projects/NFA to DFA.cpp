#include <bits/stdc++.h>
#define ll long long
#define F first
#define S second
#define pii pair<ll, ll>
#define pb push_back
#define vl vector <int>
#define vll vector<vector<int>>
#define Size_S v[s][v[s].size() - 1]
#define Size_f v[f][v[f].size() - 1]

using namespace std;

const ll maxn = 2e5, inf = 1e9;
vector <pii> vv[maxn];

ll find_string(string s, vector <string> findd)
{
    for(int i = 0; i < findd.size(); i++)
        if(s == findd[i])
            return i;
    return -1;
}

vl DFS(int s, vector<vll> v)
{
	queue <int> q;
    vl test;
	test.pb(s);
	int kol = Size_S.size();
	for(int i = 0; i < kol; i++)  test.pb(v[s][v[s].size() - 1][i]), q.push(test[i]);
	while(!q.empty())
    {
		int f = q.front();q.pop();
		if(!Size_f.empty())
		{
			int goo = Size_f.size();
			for(int i = 0; i < goo; i++)
			{
				int doo = Size_f[i];
				if(find(test.begin(),test.end(), doo) == test.end()) test.pb(doo), q.push(doo);
			}
		}
	}
	return test;
}
int main(){
    ll nn, counter = 0;
    string s[3], now = "";
    cin >> s[0] >> s[1] >> s[2] >> nn;
    vector <string> state, lan, final_state;
    for(int i = 1; i < s[0].size(); i++)
        s[0][i] != ',' && i != s[0].size() - 1 ? (now += s[0][i]) : (state.pb(now), now = "");
    for(int i = 1; i < s[1].size(); i++)
        s[1][i] != ',' && i != s[1].size() - 1 ? (now += s[1][i]) : (lan.pb(now), now = "");
    for(int i = 1; i < s[2].size(); i++)
        s[2][i] != ',' && i != s[2].size() - 1 ? (now += s[2][i]) : (final_state.pb(now), now = "");
    for(int i = 0; i < nn; i++)
    {
        now = "";
        string ss;
        cin >> ss;
        vector <string> test;
        for(int j = 0; j < ss.size(); j++)
            ss[j] != ',' ? (now += ss[j]) : (test.pb(now), now = "");
        test.pb(now);
        if(test[1] == "$")
            vv[find_string(test[0], state)].pb({find_string(test[2], state), inf});
        else
            vv[find_string(test[0], state)].pb({find_string(test[2], state),find_string(test[1], lan)});
    }
	vector <vll> doo, FINAL;
	for(int i = 0; i < state.size(); i++)
    {
		vll v;
		for(int j = 0; j < lan.size(); j++)
		{
			vector <int> t;
			for(int k = 0; k <vv[i].size(); k++)
				if(vv[i][k].S == j) t.pb(vv[i][k].F);
			v.pb(t);
		}
		vl t;
		for(int k = 0; k < vv[i].size(); k++)
            if(vv[i][k].S == inf) t.pb(vv[i][k].F);
		v.pb(t);doo.pb(v);
	}
	vll ans;
	ans.pb(DFS(0, doo));
	queue <vl> q;
	q.push(ans[0]);
	while(!q.empty())
    {
		vl goo = q.front();
		q.pop();vll v;
		for(int i = 0; i < lan.size(); i++)
		{
			vl test;
			set <int> s;
			for(int j = 0; j < goo.size(); j++)
				for(int k = 0; k < doo[goo[j]][i].size(); k++)
				{
					vl index_1 = DFS(doo[goo[j]][i][k],doo);
					for(int h = 0; h < index_1.size(); h++)
						if(s.find(index_1[h]) == s.end()) s.insert(index_1[h]);
				}
			for(auto xx : s) test.pb(xx); v.pb(test);
			if(find(ans.begin(), ans.end(), test) == ans.end()) ans.pb(test), q.push(test);
		}
		FINAL.pb(v);
	}
	cout << ans.size();
}
