// Faster method for query available for odd and even block size, if TLE check cp-algo
// Used generic block size. If calc manually : B = sqrt(n)
const int B = 440; 

struct query {
    int L, R, idx;
    bool operator < (const query &x) const {
        if(L / B == x.L / B)
            return R < x.R;
        return L < x.L;
    }
};

// Change add, rem, ans functions according to problem
struct chotoVai_Mo {

    vector<int> a, ans;
    int cur_l = 0, cur_r = -1, cur_sum = 0;

    chotoVai_Mo(vector<int>& arr) : a(arr) {} 

    void add(int x) {
        cur_sum += x;
    }

    void rem(int x){
        cur_sum -= x;
    }

    int get_ans(){
        return cur_sum;
    }

    vector<int> processQueries(vector<query>& queries) {
        ans.resize(queries.size());
        sort(queries.begin(), queries.end());

        for(const auto &q : queries){
            while(cur_l > q.L){
                cur_l--;
                add(a[cur_l]);
            }
            while(cur_r < q.R){
                cur_r++;
                add(a[cur_r]);
            }
            while(cur_l < q.L){
                rem(a[cur_l]);
                cur_l++;
            }
            while(cur_r > q.R){
                rem(a[cur_r]);
                cur_r--;
            }
            ans[q.idx] = get_ans();
        }
        return ans;
    }

};
