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
        pw.resize(N, 1), inv.resize(N, 1), Hash.resize(N, 0), RHash.resize(N, 0);
    }

    int add(int a, int b){
        int res = (a + b) % mod;
        if(res < 0) 
            res += mod;
        return res;
    }

    int mul(int a, int b){
        int64_t res = (a * 1LL * b) % mod;
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

    int precalc(){
        for(int i = 1; i < N; i++)
            pw[i] = mul(pw[i-1], base);

        int pw_inv = power(base, mod-2); // we are calculating this because we need p^(-1) at every step see below
        for(int i = 1; i < N; i++)
            inv[i] = mul(inv[i-1], pw_inv); // basically p^(-8) = p^(-7) * p^(-1)
    }

    void build(){
        for(int i = 0; i < N; i++){
            Hash[i] = add((i == 0) ? 0 : Hash[i-1], mul(s[i] - 'a' + 1, pw[i]));
            RHash[i] = add((i == 0) ? 0 : RHash[i-1], mul(s[N - i - 1] - 'a' + 1, pw[i]));
        }
    }

    int getHash(int x, int y){
        int res = add(Hash[y], (x == 0) ? 0 : -Hash[x-1]);
        res = mul(res, inv[x]);
        return res;
    }

    int getReverseHash(int x, int y) {
        int res = add(RHash[y], (x == 0) ? 0 : -RHash[x - 1]);
        res = mul(res, inv[x]);
        return res;
    }
};

struct DoubleHash {
    SimpleHash sh1, sh2;

    DoubleHash(string str) {
        sh1.init(str, 359, 1111211111);
        sh1.precalc();
        sh1.build();

        sh2.init(str, 709, 1111115111);
        sh2.precalc();
        sh2.build();
    }

    pair<int, int> getHash(int x, int y) {
        return {sh1.getHash(x, y), sh2.getHash(x, y)};
    }

    pair<int, int> reverse_hash(int x, int y) {
        return {sh1.getReverseHash(x, y), sh2.getReverseHash(x, y)};
    }
};



