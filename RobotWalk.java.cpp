#include<iostream>
using namespace std;
/*
1~n个位置，目前在m处（1<=m<=n)，可以走k步，要到达p有几种方法？
在1处下一步只能走到2，在n处下一步只能走到n-1，在中间下一步左右都可以走。
*/

int Recursion(int n, int cur, int  rest, int aim);
int Memory(int n, int cur, int  rest, int aim);
int Dynamic(int n, int cur, int  rest, int aim);

int main() {
	int n = 4, m = 2, k = 4, p = 4; //4个位置、目前在2位置，走4步，目标是4位置.
	cout << Recursion(n, m, k, p) << endl;
	cout << Memory(n, m, k, p) << endl;
	cout << Dynamic(n, m, k, p) << endl;
	//输出3 
	return 0;
}

//参数：有1~n个位置，当前位置、剩余步数、目标
//返回从cur出发走过rest步数，最后停在aim的方法数
int Recursion(int n, int cur, int  rest, int aim) { //暴力递归
	if (rest == 0) //不需要走了，走完了
		return cur == aim ? 1 : 0;
	//rest>0
	if (cur == 1) //在1位置，只能1->2;
		return Recursion(n, 2, rest - 1, aim);
	if (cur == n) //在n位置，只能n-1<-n
		return Recursion(n, n - 1, rest - 1, aim);
	//目前在中间位置
	return	Recursion(n, cur - 1, rest - 1, aim) + Recursion(n, cur + 1, rest - 1, aim);
}

int search[1001][1001] = { 0 };
int Memory(int n, int cur, int  rest, int aim) {//记忆化搜索
	if (search[cur][rest]!=0) return search[cur][rest];
	int ans = 0;
	if (rest == 0) //不需要走了，走完了
		ans = (cur == aim ? 1 : 0);
	//rest>0
	else if (cur == 1) //在1位置，只能1->2;
		ans = Memory(n, 2, rest - 1, aim);
	else if (cur == n) //在n位置，只能n-1<-n
		ans = Memory(n, n - 1, rest - 1, aim);
	//目前在中间位置
	else ans = Recursion(n, cur - 1, rest - 1, aim) + Recursion(n, cur + 1, rest - 1, aim);
	search[cur][rest] = ans;
	return ans;
}

int dp[1001][1001] = { 0 }; //[cur][rest]
int Dynamic(int n, int cur, int  rest, int aim) {
	dp[aim][0] = 1;
	for (int j = 1; j <= rest; j++) {
		dp[1][j] = dp[2][j - 1];
		for (int i = 2; i < n;i++) {
			dp[i][j] = dp[i + 1][j - 1] + dp[i - 1][j - 1];
		}
		dp[n][j] = dp[n - 1][j - 1];
	}
	return dp[cur][rest];
}
