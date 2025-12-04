#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

struct SegmentTree1D {
    int n;
    vector<long long> tree;

    SegmentTree1D(vector<int>& arr) {
        n = arr.size();
        tree.assign(4*n, 0);
        build(arr, 1, 0, n-1);
    }

    void build(vector<int>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int m = (l+r)/2;
        build(arr, node*2, l, m);
        build(arr, node*2+1, m+1, r);
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    long long query(int node, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int m = (l+r)/2;
        return query(node*2, l, m, ql, qr) +
               query(node*2+1, m+1, r, ql, qr);
    }
};

int main() {
    vector<int> arr(1000000, 1);

    auto start = high_resolution_clock::now();
    SegmentTree1D st(arr);
    auto end = high_resolution_clock::now();

    cout << "Build time: " 
         << duration_cast<milliseconds>(end-start).count()
         << " ms\n";

    start = high_resolution_clock::now();
    long long ans = st.query(1, 0, arr.size()-1, 0, 99999);
    end = high_resolution_clock::now();

    cout << "Query time: " 
         << duration_cast<microseconds>(end-start).count()
         << " us\n";
}
