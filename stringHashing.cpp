#include<bits/stdc++.h>
using namespace std;

/*
    basic : For polynomial rolling hash
    H(S) = (sumation(i = 0 to S.size()-1) S[i] * base^i) % MOD
    where base > the number of unique characters that can be present in string
    MOD = prime (must hold) because we need to find inverse MOD, and fermats little theorem
    can be applied to only prime numbers
*/

struct SimpleHash{
    int N;
    int base, mod;
    string s;

    vector<int> pw, inv, Hash, RHash;

    void init(string S, int b, int m){
        s = S;
        N = s.size(), base = b, mod = m;
        pw.resize(N);
        inv.resize(N);
        Hash.resize(N);
        RHash.resize(N);
        precalc();
    }

    int add(int a, int b){
        int res = (a + b) % mod;
        if(res < 0) 
            res += mod;
        return res;
    }

    int mul(int a, int b){
        int res = (a * 1LL * b) % mod;
        if(res < 0) 
            res += mod;
        return res;
    }

    int power(int a, int b){
        int res = 1;
        while(b){
            if(b&1)
                res = mul(res, a);
            a = mul(a, a);
            b >>= 1;
        }
        return res;
    }

    void precalc(){
        pw[0] = inv[0] = 1;
        int pw_inv = power(base, mod-2);

        for (int i = 1; i < N; i++) {
            pw[i] = mul(pw[i - 1], base);
            inv[i] = mul(inv[i - 1], pw_inv);
        }
        build();
    }

    void build(){
        for(int i = 0; i < N; i++){
            Hash[i] = add((i == 0) ? 0 : Hash[i-1], mul(s[i] - 'a' + 1, pw[i]));
            RHash[i] = add((i == 0) ? 0 : RHash[i-1], mul(s[N - i - 1] - 'a' + 1, pw[i]));
        }
    }

    int getHash(int x, int y){
        int res = add(Hash[y], (x == 0) ? 0 : -Hash[x-1]);
        return mul(res, inv[x]);
    }

    int getReverseHash(int x, int y) {
        int res = add(RHash[y], (x == 0) ? 0 : -RHash[x - 1]);
        return mul(res, inv[x]);
    }
};

struct DoubleHash {
    SimpleHash sh1, sh2;

    DoubleHash(string &str) {
        sh1.init(str, 1949313259, 2091573227);
        sh2.init(str, 1997293877, 2117566807);
    }

    pair<int, int> getHash(int x, int y) {
        return {sh1.getHash(x, y), sh2.getHash(x, y)};
    }

    pair<int, int> reverse_hash(int x, int y) {
        return {sh1.getReverseHash(x, y), sh2.getReverseHash(x, y)};
    }
};





