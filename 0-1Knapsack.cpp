#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;


//当前index编号的货物，重量不超过bag
int process(vector<int> weights, vector<int> values,int index, int rest) {
    if (rest < 0) { //bag剩余空间小于0了
        return -1;  //代表无效的加了上一步递归的货物
    }
    if (index == weights.size()) { // 下标到了边界，没货了
        return 0;
    }
    //有货,p代表价值
    //不要当前的货
    int p1 =  process(weights, values, index + 1, rest);
    int p2 = 0;
    //要当前的货物
    int next = process(weights, values, index + 1, rest - weights[index]);
    if (next != -1) p2 = values[index] + next; 

    return max(p1, p2);
}

int Recursion(vector<int> weights, vector<int> values,int bag) {
    return process(weights, values, 0, bag);
}


int Dynamic(vector<int> w, vector<int> v, int b) {
    //初始化二维数组dp[][],值设为0
    int n = w.size();
    vector<vector<int>>dp(n + 1);
    for (int i = 0; i <n + 1; i++) {
        vector<int>t(b+1);
        fill(t.begin(), t.end(), 0);
        dp[i]=t;
    }
    //开始填dp表
    for (int i = n-1; i >= 0; i--) {
        for (int rest = 0; rest <= b; rest++) {
            int p1 = dp[i + 1][rest];
            int p2 = 0;
            int next =rest - w[i] < 0 ? -1 : dp[i + 1][rest - w[i]];
            if (next != -1) p2 = v[i] + next;
            dp[i][rest] = max(p1, p2);
        }
    }
    return dp[0][b];
}

int main() {
    vector<int> weights = { 3,2,4,7,3,1,7 };
    vector<int> values = { 5,6,3,19,12,4,2 };
    int bag = 15;
    cout << Recursion(weights, values, bag) << endl;
    cout << Dynamic(weights, values, bag) << endl;
    return 0;
}
