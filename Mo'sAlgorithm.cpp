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

    void add(int i) {
        cur_sum += a[i];
    }

    void rem(int i){
        cur_sum -= a[i];
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
                add(cur_l);
            }
            while(cur_r < q.R){
                cur_r++;
                add(cur_r);
            }
            while(cur_l < q.L){
                rem(cur_l);
                cur_l++;
            }
            while(cur_r > q.R){
                rem(cur_r);
                cur_r--;
            }
            ans[q.idx] = get_ans();
        }
        return ans;
    }

};
