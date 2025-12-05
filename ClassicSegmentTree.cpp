#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

struct SegmentTree {
    int n;
    vector<long long> tree;

    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        tree.assign(4 * n, 0);
        build(arr, 1, 0, n - 1);
    }

    void build(const vector<int> &arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, node * 2, l, mid);
        build(arr, node * 2 + 1, mid + 1, r);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    long long query(int node, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return query(node * 2, l, mid, ql, qr)
             + query(node * 2 + 1, mid + 1, r, ql, qr);
    }

    void update(int node, int l, int r, int pos, int val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) update(node * 2, l, mid, pos, val);
        else update(node * 2 + 1, mid + 1, r, pos, val);

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
};

void printRow(int size, long long tBuild, long long tQuery, long long tUpdate) {
    cout << left
        << setw(15) << size
        << setw(20) << tBuild
        << setw(20) << tQuery
        << setw(20) << tUpdate
        << "\n";
}

int main() {
    vector<int> sizes = {100000, 500000, 10000000, 20000000, 30000000};

    cout << "\nRESULTADOS EXPERIMENTALES (Segment Tree Clásico)\n\n";
    cout << left
        << setw(15) << "Tamaño"
        << setw(20) << "Build (ms)"
        << setw(20) << "Query (us)"
        << setw(20) << "Update (us)"
        << "\n";

    cout << string(75, '-') << "\n";

    for (int n : sizes) {

        vector<int> arr(n, 1);

        auto start = high_resolution_clock::now();
        SegmentTree st(arr);
        auto end = high_resolution_clock::now();
        long long buildTime = duration_cast<milliseconds>(end - start).count();

        start = high_resolution_clock::now();
        long long q = st.query(1, 0, n - 1, 0, n - 1);
        end = high_resolution_clock::now();
        long long queryTime = duration_cast<microseconds>(end - start).count();

        start = high_resolution_clock::now();
        st.update(1, 0, n - 1, n / 2, 5);
        end = high_resolution_clock::now();
        long long updateTime = duration_cast<microseconds>(end - start).count();

        printRow(n, buildTime, queryTime, updateTime);
    }

    return 0;
}
