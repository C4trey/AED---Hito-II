#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

struct LazySegTree {
    int n;
    vector<long long> tree, lazy;

    LazySegTree(const vector<int>& arr) {
        n = arr.size();
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(arr, 1, 0, n - 1);
    }

    void build(const vector<int>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int m = (l + r) / 2;
        build(arr, node * 2, l, m);
        build(arr, node * 2 + 1, m + 1, r);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void push(int node, int l, int r) {
        if (lazy[node] != 0) {
            tree[node] += (r - l + 1) * lazy[node];
            if (l != r) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update_range(int node, int l, int r, int ql, int qr, int val) {
        push(node, l, r);
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            lazy[node] += val;
            push(node, l, r);
            return;
        }
        int m = (l + r) / 2;
        update_range(node * 2, l, m, ql, qr, val);
        update_range(node * 2 + 1, m + 1, r, ql, qr, val);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    long long query(int node, int l, int r, int ql, int qr) {
        push(node, l, r);
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int m = (l + r) / 2;
        return query(node * 2, l, m, ql, qr) +
               query(node * 2 + 1, m + 1, r, ql, qr);
    }
};


void printTableHeader() {
    cout << "+----------------------+-------------+-------------+-------------+\n";
    cout << "| Tamaño del arreglo   | build (ms)  | query (us)  | update (us) |\n";
    cout << "+----------------------+-------------+-------------+-------------+\n";
}

void printTableRow(int n, long long tb, long long tq, long long tu) {
    cout << "| " << setw(20) << n
         << " | " << setw(11) << tb
         << " | " << setw(11) << tq
         << " | " << setw(11) << tu
         << " |\n";
}

void printTableFooter() {
    cout << "+----------------------+-------------+-------------+-------------+\n";
}

int main() {
    vector<int> sizes = {100000, 500000, 10000000, 20000000};

    printTableHeader();

    for (int n : sizes) {
        vector<int> arr(n, 1);

        auto t1 = high_resolution_clock::now();
        LazySegTree st(arr);
        auto t2 = high_resolution_clock::now();

        long long buildTime = duration_cast<milliseconds>(t2 - t1).count();

        t1 = high_resolution_clock::now();
        long long q = st.query(1, 0, n - 1, 0, n - 1);
        t2 = high_resolution_clock::now();
        long long queryTime = duration_cast<microseconds>(t2 - t1).count();

        t1 = high_resolution_clock::now();
        st.update_range(1, 0, n - 1, 100, n - 200, 5);
        t2 = high_resolution_clock::now();
        long long updateTime = duration_cast<microseconds>(t2 - t1).count();

        printTableRow(n, buildTime, queryTime, updateTime);
    }

    printTableFooter();
}
