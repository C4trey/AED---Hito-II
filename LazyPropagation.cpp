#include <bits/stdc++.h>
using namespace std;

class LazySegmentTree {
private:
    vector<long long> tree, lazy;
    int n;

    void build(vector<int>& arr, int node, int left, int right) {
        if (left == right) {
            tree[node] = arr[left];
            return;
        }
        int mid = (left + right) / 2;
        build(arr, node*2, left, mid);
        build(arr, node*2+1, mid+1, right);
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    void apply_lazy(int node, int left, int right) {
        if (lazy[node] != 0) {
            tree[node] += (right - left + 1) * lazy[node];
            if (left != right) {
                lazy[node*2] += lazy[node];
                lazy[node*2+1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    long long query(int node, int left, int right, int ql, int qr) {
        apply_lazy(node, left, right);

        if (qr < left || ql > right) return 0;

        if (ql <= left && right <= qr) return tree[node];

        int mid = (left + right) / 2;
        return query(node*2, left, mid, ql, qr) +
               query(node*2+1, mid+1, right, ql, qr);
    }

    void update_range(int node, int left, int right, int ql, int qr, int value) {
        apply_lazy(node, left, right);

        if (qr < left || ql > right) return;

        if (ql <= left && right <= qr) {
            lazy[node] += value;
            apply_lazy(node, left, right);
            return;
        }

        int mid = (left + right) / 2;
        update_range(node*2, left, mid, ql, qr, value);
        update_range(node*2+1, mid+1, right, ql, qr, value);

        tree[node] = tree[node*2] + tree[node*2+1];
    }

public:
    LazySegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.assign(4*n, 0);
        lazy.assign(4*n, 0);
        build(arr, 1, 0, n-1);
    }

    long long query(int l, int r) {
        return query(1, 0, n-1, l, r);
    }

    void update_range(int l, int r, int value) {
        update_range(1, 0, n-1, l, r, value);
    }
};

int main() {
    vector<int> arr = {1,2,3,4,5};
    LazySegmentTree st(arr);

    cout << "Suma [0,4]: " << st.query(0, 4) << "\n";

    st.update_range(1, 3, 10);
    cout << "Suma [0,4] después del update: " << st.query(0, 4) << "\n";
}
