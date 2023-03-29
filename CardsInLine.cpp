#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
/*
给定整形数组a,数值不同的纸牌排成一条线，玩家A和B依次拿牌，规定A先拿B后拿。
每次只能拿走最左或最右的纸牌，A和B都很聪明，最后数值大的获胜，求胜利者的分数。
如：输入10,20,100,50，输出110；
*/


int Recursion(int l, int r);
int firstR(int l, int r);//先手
int lastR(int l, int r);//后手

int Memory(int l, int r);
int firstM(int l, int r);
int lastM(int l, int r);

int Dynamic(int l, int r);

int a[] = { 4,23,53,233,47,10,20,100,50 };
int main() {
	cout << Recursion(0, 8) << endl;
	cout << Memory(0, 8) << endl;
	cout << Dynamic(0,8) << endl;
	return 0;
}


int Recursion(int l, int r) {
	int fi = firstR(l, r);
	int la = lastR(l, r);
	return max(fi, la);
}
int firstR(int l, int r) {
	if (l == r) return a[l];
	int p1 = a[l] + lastR(l + 1, r);
	int p2 = a[r] + lastR(l, r - 1);
	return max(p1, p2);
}
int lastR(int l, int r) {
	if (l == r) return 0;
	int p1 = firstR(l + 1, r); //对手拿走了l位置的数
	int p2 = firstR(l, r - 1); //对手拿走了r位置的数
	return min(p1, p2);
}

int fir[9][9];
int las[9][9];
int Memory(int l, int r) {
	memset(fir, -1, sizeof(fir));
	memset(las, -1, sizeof(las));
	int fi = firstM(l, r);
	int la = lastM(l, r);
	return max(fi, la);
	return 0;
}
int firstM(int l, int r) {
	int ans = 0;
	if (fir[l][r] != -1) return fir[l][r];
	if (l == r) {
		ans = a[l];
	}
	else {
		int p1 = a[l] + lastM(l + 1, r);
		int p2 = a[r] + lastM(l, r - 1);
		ans = max(p1, p2);
	}
	fir[l][r] = ans;
	return ans;
}
int lastM(int l, int r) {
	int ans = 0;
	if (las[l][r] != -1) return las[l][r];
	if (l != r) {
		int p1 = firstM(l + 1, r);
		int p2 = firstM(l, r - 1);
		ans = min(p1, p2);
	}
	las[l][r] = ans;
	return ans;
}

int fdp[9][9];
int ldp[9][9];
int Dynamic(int l, int r) {
	memset(fdp, -1, sizeof(fdp));
	memset(ldp, -1, sizeof(ldp));
	for (int i = 0; i < 9; i++) {
		fdp[i][i] = a[i];
		ldp[i][i] = 0;
	}
	for (int startCol = 1; startCol < 9; startCol++) {
		int i = 0;
		int j = startCol;
		while (j < 9) {
			fdp[i][j] = max(a[j]+ldp[i][j - 1], a[i]+ldp[i + 1][j]);
			ldp[i][j] = min(fdp[i][j - 1], fdp[i + 1][j]);
			i++; j++;
		}
	}
	return max(fdp[l][r],ldp[l][r]);
}
