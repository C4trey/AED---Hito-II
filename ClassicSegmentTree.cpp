#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    vector<long long> tree;
    int n;

    void build(vector<int>& arr, int node, int left, int right) {
        if (left == right) {
            tree[node] = arr[left];
            return;
        }
        int mid = (left + right) / 2;
        build(arr, 2*node, left, mid);
        build(arr, 2*node+1, mid+1, right);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    long long query(int node, int left, int right, int ql, int qr) {
        if (qr < left || ql > right) return 0;
        if (ql <= left && right <= qr) return tree[node];

        int mid = (left + right) / 2;
        return query(2*node, left, mid, ql, qr)
             + query(2*node+1, mid+1, right, ql, qr);
    }

    void update(int node, int left, int right, int idx, int value) {
        if (left == right) {
            tree[node] = value;
            return;
        }
        int mid = (left + right)/2;
        if (idx <= mid) update(2*node, left, mid, idx, value);
        else update(2*node+1, mid+1, right, idx, value);

        tree[node] = tree[2*node] + tree[2*node+1];
    }

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.assign(4*n, 0);
        build(arr, 1, 0, n-1);
    }

    long long query(int l, int r) {
        return query(1, 0, n-1, l, r);
    }

    void update(int idx, int value) {
        update(1, 0, n-1, idx, value);
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree st(arr);

    cout << "Suma [1,4] = " << st.query(1, 4) << "\n"; // 1 3 5 7 9 11, 3+5+7+9=24
    st.update(2, 10);
    cout << "Nueva suma [1,4] = " << st.query(1, 4) << "\n"; // 1 3 10 7 9 11, 3+10+7+9=29
}