#include <bits/stdc++.h>

using namespace std;

void TriangularMatrix() {
    int n, x;
    int sum_upper = 0, sum_lower = 0;
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> x;
            if (j >= i)
                sum_upper += x;
            
            if(i >= j)
                sum_lower += x;
        }
    }

    cout << sum_lower << '\n' << sum_upper;
}

void Transpose() {
    int n, m;
    cin >> n >> m;
    // int arr[n][m]; No need to store it :)
    int arrT[m][n];

    int index_i = 0, index_j = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> arrT[index_i][index_j];
            index_i++;

            if(index_i >= m)
                index_j++, index_i = 0;
        }
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            cout << arrT[i][j] << ' ';
        }
        cout << '\n';
    }
}

int n, m;
int arr[1024][1024];
int i_index[] {-1, -1, 0, +1, +1, +1, 0, -1};
int j_index[] {0, +1, +1, +1, 0, -1, -1, -1};

bool isMountain(int i, int j) {
    bool itis = true;

    for(int index = 0; index < 8; index++) {

        int new_i = i + i_index[index];
        int new_j = j + j_index[index];
        if(new_i >= 0 && new_i < n && new_j >= 0 && new_j < m) {
            if(arr[i][j] < arr[new_i][new_j]) {
                itis = false;
                break;
            }
        }  
    }
    return itis;
}

void FindMountains() {
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> arr[i][j];

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(isMountain(i, j))
                cout << i << ' ' << j << '\n';

}

void ActiveRobot() {
    int n, m, q;
    cin >> n >> m >> q;

    int i = 0, j = 0;
    int mov, sz;
    while(q--) {
        cin >> mov >> sz;
        if(mov == 1) {
            i = (((i - sz) % n) + n) % n; // in case of negative values.
        } else if(mov == 2) {
            j = (((j + sz) % m) + m) % m;
        } else if(mov == 3) {
            i = (((i + sz) % n) + n) % n;
        } else {
            j = (((j - sz) % m) + m) % m;
        }
        cout << i << ' ' << j << '\n';
    }
}

void Flatten3dArray() { 
    int depth, rows, cols, x;
    cin >> depth >> rows >> cols;
    cin >> x;
    if(x == 1) {
        int d, r, c;
        cin >> d >> r >> c;
        cout << (d * (rows * cols)) + (r * cols) + c;
    } else {
        // Using modulous is much better. #202
        cin >> x;
        int d = x / (rows * cols);
        int r = (x - (d * rows * cols)) / cols;
        int c = (x - (d * rows * cols) - (r * cols));
        cout << d << ' ' << r << ' ' << c;
    }
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    // TriangularMatrix();
    // Transpose();
    // FindMountains();
    // ActiveRobot();
    Flatten3dArray();
    return 0;
}