#include <bits/stdc++.h>
using namespace std;

struct SegmentTree2D {
    int n, m;
    vector<vector<long long>> tree;

    SegmentTree2D(vector<vector<int>>& mat) {
        n = mat.size();
        m = mat[0].size();
        tree.assign(4*n, vector<long long>(4*m, 0));
        build_y(mat, 1, 0, n-1);
    }

    void build_y(vector<vector<int>>& mat, int node_x, int lx, int rx) {
        if (lx != rx) {
            int mx = (lx+rx)/2;
            build_y(mat, node_x*2, lx, mx);
            build_y(mat, node_x*2+1, mx+1, rx);
        }
        build_x(mat, node_x, lx, rx, 1, 0, m-1);
    }

    void build_x(vector<vector<int>>& mat, int nx, int lx, int rx,
                 int ny, int ly, int ry) {

        if (ly == ry) {
            if (lx == rx) tree[nx][ny] = mat[lx][ly];
            else tree[nx][ny] = tree[nx*2][ny] + tree[nx*2+1][ny];
            return;
        }

        int my = (ly+ry)/2;
        build_x(mat, nx, lx, rx, ny*2, ly, my);
        build_x(mat, nx, lx, rx, ny*2+1, my+1, ry);
        tree[nx][ny] = tree[nx][ny*2] + tree[nx][ny*2+1];
    }
};

int main() {
    vector<vector<int>> mat(2000, vector<int>(2000, 1));

    auto start = chrono::high_resolution_clock::now();
    SegmentTree2D st(mat);
    auto end = chrono::high_resolution_clock::now();

    cout << "2D build time: "
         << chrono::duration_cast<chrono::milliseconds>(end-start).count()
         << " ms\n";
}
