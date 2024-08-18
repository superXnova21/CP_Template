#include<bits/stdc++.h>
using namespace std;

pair<int, int> extended_gcd(int a, int b){
    if(b == 0) return {1, 0};
    auto [x1, y1] = extended_gcd(b, a % b);
    int x = y1, y = x1 - (a / b) * y1;
    return {x, y};
}
