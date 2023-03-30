#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;

/*
* 1对应A,2对应B......26对应Z
* 给定数字字符串"111",可以转换为"AAA"、"KA"、"AK"
* 给定字符串s,返回有多少转换结果
*/

int process(string s,int i) {
    if (i == s.size()) return 1;//到达字符串边界，找到一种解决方法
    //i没到达边界情况：
    if (s[i] == '0') return 0; //让i独自面对0的情况，说明之前的决策有问题一，方法不存在
        //s[i]!='0'，两种可能，一种是i单独转换，一种是i和i+1一起转换
    int ways = process(s, i + 1);//情况一
    if(i+1<s.size()&& (s[i]-'0')*10+(s[i+1]-'0')<27)
        ways += process(s, i + 2); //符合条件，则加上条件二

    return ways;
}
int Recursion(string s) {
    return process(s,0);
}

int Dynamic(string s) {
    int n = s.size();
    vector<int>dp(n+1);
    fill(dp.begin(), dp.end(), 0);
    //i位置值以来i+1和i+2，从右往左填表
    dp[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] != '0') {
            int ways = dp[i + 1];
            if (i + 1 < s.size() && (s[i] - '0') * 10 + (s[i + 1] - '0') < 27)
                ways += dp[i + 2];
            dp[i] = ways;
        }
    }
    return dp[0];
}

int main() {
    string s = "125111391";
    
    cout << Recursion(s) << endl;
    cout << Dynamic(s) << endl;
    return 0;
}
