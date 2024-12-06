struct segtree{
 
    int size;
    vector<long long> sums;
 
    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        sums.assign(2 * size, 0LL);
    }

    int operation(int x, int y) {
        return __gcd(x, y);
    }
 
    void build(vector<int>& a, int x, int lx, int rx){
        if(rx-lx == 1){
            if(lx < (int) a.size()){
                sums[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        sums[x] = operation(sums[2 * x + 1], sums[2 * x + 2]);
    }
 
    void build(vector<int>& a){
        build(a, 0, 0, size);
    }
 
    void set(int i, int v, int x, int lx, int rx){
        if(rx - lx == 1){
            sums[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        if(i < m){
            set(i, v, 2 * x + 1, lx, m);
        } else{
            set(i, v, 2 * x + 2, m, rx);
        }
        sums[x] = operation(sums[2 * x + 1], sums[2 * x + 2]);
    }
 
    void set(int i, int v){
        set(i, v, 0, 0, size);
    }
 
    long long query(int l, int r, int x, int lx, int rx){
        if(l >= rx || lx >= r) return 0;
        if(lx >= l && rx <= r) return sums[x];
        int m = (lx + rx) / 2;
        long long s1 = query(l, r, 2 * x + 1, lx, m);
        long long s2 = query(l, r, 2 * x + 2, m, rx);
        return operation(s1, s2);
    }
 
    long long query(int l, int r){
        return query(l, r, 0, 0, size);
    }
 
};
