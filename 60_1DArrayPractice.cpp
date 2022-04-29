#include <bits/stdc++.h>

using namespace std;
// If solution not found => Too easy.

void max2_1loop() {
    // Also 'find pair values of maximum sum' will be solved using this.
    // can set them with values of arr[0] and arr[1] accordingly
	int max1 = -1, max2 = -1; 

    int arr[6] {20, 10, 15};;

    for(int i = 0; i < 6; i++) {
        if(arr[i] > max1) {
            max2 = max1;
            max1 = arr[i];
        }
        else if(arr[i] > max2)
            max2 = arr[i];
    }
    cout << max1 << ' ' << max2;
}

void samllest_pair() {
    // (Not verified)
    // Loop to get minimum (A[i] - i)
    // 2nd Loop to get minimum (A[j] + j) (that isn't i from previous one).
    int n = 4;
    int arr[4] {20, 1, 9, 4};
    // Stopped here, are there more efficient way?
    // End of #168
    int ans {9999};
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int temp = arr[j] + arr[i] + j - i;
            ans = min(ans, temp);
        }
    }
    cout << ans;
}

void insert_ordered(stack<int> &ans, int &x) {
    stack<int> temp;

    while(!ans.empty() && ans.top() > x) {
        temp.push(ans.top());
        ans.pop();
    }

    if(ans.size() <= 2)
        ans.push(x);

    while(ans.size() < 3 && !temp.empty()) {
        ans.push(temp.top());
        temp.pop();
    }
}

void print_reversed(stack<int> &ans) {
    if(!ans.empty()) {
        int x = ans.top(); ans.pop();
        print_reversed(ans);
        cout << x << ' ';   
    }
}

void find_3minimum_values() {
    stack<int> ans;
    
    int n, x;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x;
        insert_ordered(ans, x);
    }

    print_reversed(ans);
}

void search_for_anumber() {
    int n, q;
    cin >> n;

    int arr[501];
    for(int i = 0; i < 501; i++)
        arr[i] = -1;
    
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        arr[x] = i;
    }

    cin >> q;
    while(q--) {
        int x;
        cin >> x;
        cout << arr[x] << '\n';
    }
        
}

void UniqueNumbersOfUnorderedList() {
    bool vis[501] {0};
    queue<int> q;

    int n, x;
    cin >> n;
    while(n--) {
        cin >> x;
        if(!vis[x])
            q.push(x);
        
        vis[x] = 1;
    }

    while(!q.empty()) {
        cout << q.front() << ' ';
        q.pop();
    }
}

void SortingNumbers() {
    // There's traditional O(n^2) Solution
    // In this case numbers are between 0 and 500 inclusive, 
    // So similar to last problems, do preprocessing:
    
    int n, x;
    cin >> n;
    int ans[501] {0};;

    for(int i = 0; i < n; i++) {
        cin >> x;
        ans[x]++;
    }

    for(int i = 0; i < 501; i++) {
        if(ans[i] == 0)
            continue;
        
        for(int j = 0; j < ans[i]; j++)
            cout << i << ' ';
    }
}

void RecamansSequence() {
    int arr[201], temp;
    bool vis[1000] {0};
    vis[0] = 1;
    arr[0] = 0;

    for(int i = 1; i < 201; i++) {
        temp = arr[i - 1] - (i - 1) - 1;

        if(vis[temp] || temp <= 0)
            temp = arr[i - 1] + (i - 1) + 1;

        vis[temp] = 1;
        arr[i] = temp;
    }

    int index;
    cin >> index;
    cout << arr[index];
}

void CountIncreasingSubArrays() {
    int n;
    cin >> n;
    int arr[n]; // array not really needed here.

    for(int i = 0; i < n; i++)
        cin >> arr[i];
    
    int ans = 0, sub_ans = 1;
    for(int i = 1; i < n; i++) {
        if(arr[i] >= arr[i - 1])
            sub_ans++;
        else {
            ans += ((sub_ans * (sub_ans + 1)) / 2);
            sub_ans = 1;
        }
    }
    ans += ((sub_ans * (sub_ans + 1)) / 2); // last iteration.
    cout << ans;
}

// My best shot at it.
void JosephusProblem() {
    int n, k;
    cin >> n >> k;

    // - Didn't do the reduction of very large K.
    // If K = 10 and N = 5 => No need of iterating twice for no reason,
    // K % N will get us where we want to go, except it's = 0, so we will make it = N.
    // It reduces with each person that wins, because we can start with K= 10 and N =5, 
    // but end with N = 2, at this moment K = 5 (from first reduction) is again not efficient.
    // ~O(N^2)

    int index = k % n;

    int vis[n + 1] = {0}, vis_count = 1;
    vis[0] = 1;
    if(index == 0)
        index += n;
    vis[index] = 1;
    cout << index << ' ';
    while(vis_count != n) {
        int sub_k = k;
        while(sub_k) {
            index = (index + 1) % (n + 1);
            if(!vis[index])
                sub_k--;
        }
        vis[index] = 1;
        vis_count++;
        cout << index << ' ';
    }
}

// Last part missing here was creating two arrays, one for going_left[], and going_right[]
// in which each ones stores last 0/1 closer to each 1/0, totally adding O(?) + 2n

// ^ Doctor's idea is much better, shorter, and efficient.
// Keep track of difference of zeros - ones in each index,
// when the difference repeats => it means that the #ones and #zeros between
// the first difference and current one is equal => maximize on it.
void LongestSubarray() {
    int n, one_num = 0, zero_num = 0;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
        if(arr[i])
            one_num++;
        else
            zero_num++;
    }

    int start = 0, end = n - 1;
    while(one_num != zero_num) {
        if(one_num > zero_num) {
            if(arr[start] == 1) {
                one_num--;  
                start++;
            } else if(arr[end] == 1) {
                end--;
                one_num--;
            } else {
                // Q: Does it matter if we "eat" from left or right?
                start++;
                zero_num--;
            }
        }
        else {
            if(arr[start] == 0) {
                zero_num--;  
                start++;
            } else if(arr[end] == 0) {
                zero_num--;
                end--;
            } else {
                // Q: Does it matter if we "eat" from left or right?
                start++;
                one_num--;
            }
        }
    }
    cout << start + 1 << ' ' << end + 1 << ' ' << (one_num + zero_num);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    // max2_1loop();
    // samllest_pair();

    // Here we start using preprocessing technique:
    // find_3minimum_values();
    // search_for_anumber();
    // FindMostFrequentNumber= Same as ^.
    // DigitsFrequency = Same as  ^.
    // UniqueNumbersOfUnorderedList(); // same as ^.
    
    // SortingNumbers(); // also same as ^.
    // RecamansSequence(); // #175-1
    // FixedSlidingWindow(); // #175-2 => Not soloved => Redundent from Queues.
    // CountIncreasingSubArrays(); // #175-3
    // JosephusProblem(); // #175-4
    LongestSubarray();
	return 0;
}
