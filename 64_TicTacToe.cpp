// Last task in DS Dr. Mostafa Course!
#include <bits/stdc++.h>

using namespace std;

// I think can be separated to more classes :U
class TicTacToe {
private:
    // Doesn't look beautiful.
    vector<vector<char>> plan;
    int sz { };
    bool turn = 0;
    int x_count = 0, y_count = 0;
    char play[2] {'x', 'o'};
    int i_mov[8] {-1, -1, 0, +1, +1, +1, 0, -1};
    int j_mov[8] {0, +1, +1, +1, 0, -1, -1, -1};

public:
    TicTacToe(const int &plan_sz = 3) : sz(plan_sz) {
        if(sz < 3)
            sz = 3;

        plan.resize(sz);
        for(int i = 0; i < sz; i++)
            plan[i].resize(sz);
        
        for(int i = 0; i < sz; i++)
            for(int j = 0; j < sz; j++)
                plan[i][j] = '.';
        PrintPlan();
    }

    // Has many responsbilities.
    void Play() {
        cout << "Player " << play[turn] << " Turn ";
        cout << "Enter location i j: ";

        int i, j;
        cin >> i >> j;
        i--, j--;
        while(!isValidPlay(i, j)) {
            cout << "Invalid play! Try again.\n";
            cin >> i >> j;
            i--, j--;
        }

        plan[i][j] = play[turn];
        if(turn)
            x_count++;
        else
            y_count++;
        

        PrintPlan();
        if(isWon(i, j)) {
            cout << "Player " << play[turn] << " Won!\n"; 
            return;
        } else if(isDraw()) {
            cout << "Game ended in a draw!\n";
            return;
        }

        turn = !turn;
        Play();
    }

    bool isWon(int i, int j) {
        int CountXOarr[4] = {0};
        int counter_idx = 4;
        int ans = 0;
        for(int idx = 0; idx < 4; idx++) {
    
            CountXOarr[idx] = CountXO(i + i_mov[idx], j + j_mov[idx], idx)
                            + CountXO(i + i_mov[counter_idx], j + j_mov[counter_idx], counter_idx);

            if((CountXOarr[idx] + 1) > ans)
                ans = CountXOarr[idx] + 1;
            
            counter_idx++;
        }
        // can be inceremented to support more than 3 X/O in a row.
        // I noticed in doc solution he verifies diagonals, columns and rows only.
        // Which can mean correct is ans >= sz only,
        // and would have saved me some time thinking :)
        return (ans >= 3); 
    }

    int CountXO(int i, int j, int mov) {
        if(!isValidCount(i, j))
            return 0;
        
        return 1 + CountXO(i + i_mov[mov], j + j_mov[mov], mov);
    }

    bool isDraw() {
        return x_count + y_count == (sz * sz);
    }

    void PrintPlan() {
        for(int i = 0; i < sz; i++) {
            for(int j = 0; j < sz; j++) {
                cout << plan[i][j];
            }
            cout << '\n';
        }
    }

    bool isValidPlay(const int &i, const int &j) {
        if(i < 0 || i >= sz || j < 0 || j >= sz)
            return false;
        else if(plan[i][j] != '.')
            return false;

        return true;
    }

    bool isValidCount(int i, int j) {
        if(i < 0 || i >= sz || j < 0 || j >= sz)
            return false;
        else if(plan[i][j] != play[turn])
            return false;

        return true;
    }
};

int main() {
    int sz = 3;
    cout << "Enter TicTacToe size: ";
    cin >> sz;
    TicTacToe game(sz);
    game.Play();

    cout << "\nBye :)";
    return 0;
}