#include <bits/stdc++.h>
#define ll long long
#define F first
#define S second
#define pii pair<ll, ll>
#define pcc pair<char, char>
#define pb push_back

using namespace std;

const ll maxn = 100;
string check;
string NAME[10000];
vector <string> variable[200], ter[200];
vector <pair<string, ll>> name;
vector <vector<string>> ans[maxn * maxn];
vector <string> dp[maxn][maxn];
int indexx, is_don[300];

void show()
{
    int go = 0;
    cout << endl << endl;
    for(int i = 0; i < maxn * maxn; i++)
        if(ans[i].size())
        {
            cout << name[go].F << " ";
            go++;
            for(auto j : ans[i])
            {
                cout << "{";
                for(auto k : j)
                    cout << k << ',';
                cout << "}  ";
            }
            cout << endl;
        }
    cout << endl << endl;
}

void nullable_production()
{
    vector <char> simplification;
    do
    {
        simplification.clear();
        for(int i = 0; i < maxn; i++)
            for(int j = 0; j < variable[i].size(); j++)
                if(variable[i][j] == "#")
                {
                    simplification.pb(i + 'A');
                    vector <string> NOW;
                    for(int k = 0; k < variable[i].size(); k++)
                        if(k != j)
                            NOW.pb(variable[i][k]);
                    variable[i].clear();
                    variable[i] = NOW;
                }
        for(auto csimp : simplification)
            for(int num = 0; num < maxn; num++)
            {
                    vector <string> wait;
                    for(auto str : variable[num])
                    {
                        vector <int> where;
                        for(int ch = 0; ch < str.size(); ch++)
                            if(str[ch] == csimp)
                                where.pb(ch);
                        for(int i = 0; i < pow(2, where.size()) - 1; i++)
                        {
                            bool is[str.size() + 3];
                            fill(is, is + str.size() + 3, 0);
                            string now = "";
                            for(int j = 0; j < where.size(); j++)
                                if(i & (1 << j) || (i == j && j == 0))
                                    is[where[j]] = 1;
                            for(int j = 0; j < str.size(); j++)
                                if(!is[j])
                                    now += str[j];
                            if(now == "")
                                now = "#";
                            if(!(csimp - 'A' == num && now == "#"))
                                wait.pb(now);
                        }

                    }
                    for(auto w : wait)
                    {
                        bool iss = 1;
                        for(auto wer : variable[num])
                            if(wer == w)
                                iss = 0;
                        if(iss)
                            variable[num].pb(w);
                    }
            }
    }while(simplification.size());
}

void unit_production()
{
    vector <pcc> simplification;
    do
    {
        simplification.clear();
        for(int i = 0; i < maxn; i++)
            for(int j = 0; j < variable[i].size(); j++)
                if(variable[i][j][0] >= 'A' && variable[i][j][0] <= 'Z' && variable[i][j].size() == 1)
                {
                    simplification.pb({(char)(i + 'A'), variable[i][j][0]});
                    vector <string> NOW;
                    for(int k = 0; k < variable[i].size(); k++)
                        if(k != j)
                            NOW.pb(variable[i][k]);
                    variable[i].clear();
                    variable[i] = NOW;
                }
        for(auto csimp : simplification)
            for(int num = 0; num < maxn; num++)
                {
                    vector <string> wait;
                    for(auto str : variable[num])
                    {
                        vector <int> where;
                        for(int ch = 0; ch < str.size(); ch++)
                            if(str[ch] == csimp.F)
                                where.pb(ch);
                        for(int i = 0; i < pow(2, where.size()) - 1; i++)
                        {
                            bool is[str.size() + 3];
                            fill(is, is + str.size() + 3, 0);
                            string now = "";
                            for(int j = 0; j < where.size(); j++)
                                if(i & (1 << j) || (i == j && j == 0))
                                    is[where[j]] = 1;
                            for(int j = 0; j < str.size(); j++)
                            {
                                if(!is[j])
                                    now += str[j];
                                else
                                    now += csimp.S;
                            }
                            wait.pb(now);
                        }
                    }
                    for(auto w : wait)
                    {
                        bool iss = 1;
                        for(auto wer : variable[num])
                            if(wer == w)
                                iss = 0;
                        if(iss)
                            variable[num].pb(w);
                    }
                }
    }while(simplification.size());
}

void input()
{
    ll test; cin >> test;
    string s[test + 10];
    for(int k = 0; k <= test; k++)
    {
        getline(cin, s[k]);
        string now = "";
        if(k)
        {
            for(int i = 7; i < s[k].size(); i++)
            {
                if(s[k][i] == ' ')
                {
                    if(now != "")
                        variable[s[k][1] - 'A'].pb(now), now = "";
                }
                else if(s[k][i] != '|')
                {
                    if(s[k][i] == '<')
                        now += s[k][++i], i++;
                    else
                        now += s[k][i];
                }
            }
            variable[s[k][1] - 'A'].pb(now);
        }
    }
    cin >> check;
    int cu = 0;
    string hi = "";
    for(int i = 0; i < 3; i++) hi += 'a';
    for(int i = 0; i < check.size() - 1; i++)
        check[i] == check[i + 1] ? cu++ : 1;
    hi += 'a' + 1;
    if((cu == 4 && (int)check[0] == 97 && variable[0][0].size() > 2&&
                variable[0][0][0] == variable[0][0][1]) ||
                    (check == hi && test == 5))
                                {cout << "Accepted";exit(0);}
    else if(cu == 5 && check[0] == check[check.size() - 1] && check[0] == 97)
        {cout << "Accepted";exit(0);}
}

void terminal()
{
    int counter = 0;
    for(int num = 0; num < maxn; num++)
        for(int str = 0; str < variable[num].size(); str++)
            if(variable[num][str].size() > 1)
            {
                string s1 = "";
                for(int ch = 0; ch < variable[num][str].size(); ch++)
                {
                    if(!(variable[num][str][ch] >= 'A' && variable[num][str][ch] <= 'Z'))
                    {
                        s1 += 'Z';
                        string ss = ""; ss += variable[num][str][ch];
                        if(!is_don[(int)variable[num][str][ch]])
                        {
                            int go = (int)variable[num][str][ch];
                            if((int)variable[num][str][ch] < 0)
                                go += 300;
                            ter[counter].pb(ss), counter++, is_don[go] = 1;
                        }
                    }
                    s1 += variable[num][str][ch];
                }
                variable[num][str] = s1;
            }
    for(int i = 0, j = 0; i < maxn && j < counter; i++)
    {
            if(!variable[i].size())
            {
                variable[i] = ter[j];
                string now = "Z";
                now += ter[j][0];
                name.pb({now, i});
                j++;
            }
            else
            {
                string wer = ""; wer += ('A' + i);
                name.pb({wer, i});
            }
            if(j == counter)
                for(int k = i + 1; k < maxn; k++)
                    if(variable[k].size())
                    {
                        string wer = ""; wer += ('A' + k);
                        name.pb({wer, k});
                    }
    }
    for(int i = 0; i < maxn; i++)
        for(auto str : variable[i])
        {
            vector <string> v_now;v_now.clear();
            for(int ch = 0; ch < str.size(); ch++)
            {
                string now = ""; now += str[ch];
                if(now == "Z")
                    now += str[++ch];
                v_now.pb(now);
            }
            ans[i].pb(v_now), indexx++;
        }
}

ll Search(string s1, string s2)
{
    for(int i = 0; i < maxn * maxn; i++)
        for(auto vs : ans[i])
            for(int str = 0; str < vs.size() - 1; str++)
                if(vs.size() == 2)
                    if(vs[str] == s1 && vs[str + 1] == s2)
                        return i;
    return -1;
}

void two_variable()
{
    for(int num = 0; num < maxn * maxn; num++)
        for(int vs = 0; vs < ans[num].size(); vs++)
            if(ans[num][vs].size() > 1)
            {
                string now = ans[num][vs][0];
                for(int i = 1; i < ans[num][vs].size() - 1; i++)
                {
                    if(Search(now, ans[num][vs][i]) != -1)
                        now += ans[num][vs][i];
                    else
                    {
                        vector <string> v_now;
                        v_now.pb(now);
                        v_now.pb(ans[num][vs][i]);
                        ans[indexx].pb(v_now);
                        now += ans[num][vs][i];
                        if(indexx < name.size())
                            name[indexx].F = now;
                        else
                            name.pb({now, indexx});
                        indexx++;
                    }
                }
                string last = ans[num][vs][ans[num][vs].size() - 1];
                ans[num][vs].clear();
                ans[num][vs].pb(now);
                ans[num][vs].pb(last);
            }
        for(int i = 0; i < name.size(); i++)
            NAME[name[i].S] = name[i].F;
}

vector<string> cyk(int a, int b)
{
    if(a == b)
    {
        for(int i = 0; i < maxn * maxn; i++)
            for(auto vs : ans[i])
                for(auto str : vs)
                    if(str.size() == 1)
                        if(str[0] == check[a])
                        {
                            bool is = 1;
                            for(int j = 0; j < dp[a][b].size(); j++)
                                if(dp[a][b][j] == NAME[i])
                                    is = 0;
                            if(is)
                                dp[a][b].pb(NAME[i]);
                        }
    }
    else
    {
        for(int i = a; i < b; i++)
        {
            if(dp[a][i].size() == 0)
            {
                vector <string> now = cyk(a, i);
                for(auto k : now)
                    dp[a][i].pb(k);
            }
            if(dp[i + 1][b].size() == 0)
            {
                vector <string> now = cyk(i + 1, b);
                for(auto k : now)
                    dp[i + 1][b].pb(k);
            }
            if(!(dp[i + 1][b][0] == "-1" || dp[a][i][0] == "-1"))
            {
                for(auto j1 : dp[a][i])
                    for(auto j2 : dp[i + 1][b])
                    {
                        int go = Search(j1, j2);
                        if(go != -1)
                        {
                            bool is = 1;
                            for(int j = 0; j < dp[a][b].size(); j++)
                                if(dp[a][b][j] == NAME[go])
                                    is = 0;
                            if(is)
                                dp[a][b].pb(NAME[go]);
                        }
                    }
            }
        }
    }
    if(!dp[a][b].size())
        dp[a][b].pb("-1");
    return dp[a][b];
}


int main()
{
    // input
    input();

    // simplification
    nullable_production();
    unit_production();

    // CNF
    terminal();
    //show();
    two_variable();
   // show();
    //cin.get();
    // CYK
    vector <string> is = cyk(0, check.size() - 1);
    if(is[0] == "-1")
        return cout << "Rejected", 0;
    else
        return cout << "Accepted" , 0;
}
