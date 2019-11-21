#include <bits/stdc++.h>
#define pb push_back
#define pii pair<ll, ll>
#define nyan "(=^･ω･^=)"
#define read_input         freopen("in.txt","r", stdin)
#define print_output       freopen("out.txt","w", stdout)
typedef long long ll;
typedef long double ld;
using namespace std;

const ll maxn = 1e5+10;

struct event {
    int x, st, ed, val;
} a[2*maxn];

struct segtree {
    ll tree[6*maxn];
    ll lazy[6*maxn];

    void propagate(int at, int L, int R) {
        if(lazy[at]) {
            tree[at] += lazy[at];
            if(L != R) {
                lazy[at*2] += lazy[at];
                lazy[at*2+1] += lazy[at];
            }
            lazy[at] = 0;
        }
    }

    void update(int at, int L, int R, int l, int r, int val) {
        propagate(at, L, R);
        if(L > r || R < l) return;
        if(L >= l && R <= r) {
            lazy[at] += val;
            propagate(at, L, R);
            return;
        }
        int mid = L + R >> 1;
        update(at<<1, L, mid, l, r, val);
        update(at<<1|1, mid+1, R, l, r, val);

        tree[at] = max(tree[at<<1], tree[at<<1|1]);
    }
} s;


int main()
{  
    freopen("lazy.in", "r", stdin);
    freopen("lazy.out", "w", stdout);

    int n, k; cin >> n >> k;
    vector<int> D;

    for(int i = 0, x, y, g; i < n; i++) {
        cin >> g >> x >> y;
        int v = x+y, u = x-y;

        D.pb(v-k); D.pb(v+k);

        a[2*i] = {u-k, v-k, v+k, g};
        a[2*i+1] = {u+k+1, v-k, v+k, -g};
    }
    sort(D.begin(), D.end());
    D.resize(unique(D.begin(), D.end()) - D.begin());

    for(int i = 0; i < n; i++) {
        int u = lower_bound(D.begin(), D.end(), a[2*i].st) - D.begin() + 1;
        int v = lower_bound(D.begin(), D.end(), a[2*i].ed) - D.begin() + 1;

        a[2*i].st = a[2*i+1].st = u;
        a[2*i].ed = a[2*i+1].ed = v;
    }

    sort(a, a+2*n, [](const event a, const event b) -> bool 
    { return a.x < b.x;} );

    ll mx = 0;
    for(int i = 0; i < 2*n; i++) {
        int d = i;
        while(d < 2*n && a[i].x == a[d].x) {
            s.update(1, 1, 2*n, a[d].st, a[d].ed, a[d].val);
            d++;
        } mx = max(mx, s.tree[1]);
        i = d-1;
    }

    cout << mx << endl;

    return 0;   
} 
