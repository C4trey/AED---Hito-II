#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

struct HeapSegTree {
    int n;
    vector<long long> seg;

    HeapSegTree(const vector<int>& arr) {
        n = arr.size();
        seg.assign(2 * n, 0);

        for (int i = 0; i < n; i++)
            seg[n + i] = arr[i];

        for (int i = n - 1; i > 0; --i)
            seg[i] = seg[i << 1] + seg[i << 1 | 1];
    }

    long long query(int l, int r) {
        long long res = 0;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res += seg[l++];
            if (!(r & 1)) res += seg[r--];
        }
        return res;
    }

    void update(int pos, int val) {
        pos += n;
        seg[pos] = val;
        while (pos > 1) {
            pos >>= 1;
            seg[pos] = seg[pos << 1] + seg[pos << 1 | 1];
        }
    }
};


void header() {
    cout << "+----------------------+-------------+-------------+-------------+\n";
    cout << "| Tamaño del arreglo   | build (ms)  | query (us)  | update (us) |\n";
    cout << "+----------------------+-------------+-------------+-------------+\n";
}

void footer() {
    cout << "+----------------------+-------------+-------------+-------------+\n";
}

void row(int n, long long b, long long q, long long u) {
    cout << "| " << setw(20) << n
         << " | " << setw(11) << b
         << " | " << setw(11) << q
         << " | " << setw(11) << u
         << " |\n";
}

int main() {
    vector<int> sizes = {100000, 500000, 10000000, 20000000};

    header();

    for (int n : sizes) {
        vector<int> arr(n, 1);

        auto t1 = high_resolution_clock::now();
        HeapSegTree st(arr);
        auto t2 = high_resolution_clock::now();
        long long buildT = duration_cast<milliseconds>(t2 - t1).count();

        t1 = high_resolution_clock::now();
        long long q = st.query(0, n - 1);
        t2 = high_resolution_clock::now();
        long long queryT = duration_cast<microseconds>(t2 - t1).count();

        t1 = high_resolution_clock::now();
        st.update(n / 2, 77);
        t2 = high_resolution_clock::now();
        long long updateT = duration_cast<microseconds>(t2 - t1).count();

        row(n, buildT, queryT, updateT);
    }

    footer();
}
