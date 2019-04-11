#include<iostream>
#include<vector>
#include<string>

using namespace std;

int findLongest(string A, int n, string B, int m) {
	if (n == 0 || m == 0)
		return 0;
	int rs = 0;
	vector<vector<int >> dp(n+1, vector<int> (m+1));
	for (int i = 0; i <n; i++) {
		dp[i][0] = 0;
	}
	for (int j = 0; j <m; j++) {
		dp[0][j] = 0;
	}
	for (int i = 1; i <=n; i++) {//注意一定从1开始，而不是0
		for (int j = 1; j <= m; j++) {
		    if (A[i-1] == B[j-1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
				rs = rs > dp[i][j] ? rs : dp[i][j]; //每次更新记录最大值
			}
			else {
				dp[i][j] = 0;
			}
		}
	}
	return rs;	
}

int main() {
	string stra, strb;
	cout << "请输入第一个字符串 " << endl;
	cin >> stra;
	cout << "请输入第二个字符串" << endl;
	cin >> strb;
	int n = stra.length();
	int m = strb.length();
	int Longest = findLongest(stra, n, strb, m);
	cout << "最长公共子串的长度" << endl;
	cout << Longest;
	return 0;
}
