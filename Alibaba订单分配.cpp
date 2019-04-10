#include<iostream>
#include<vector>

using namespace std;

//判断能否继续再剩余商品找到bom组合 
bool canSearch(const vector<int> &boms, const vector<int> &left, int  n) {
	for (int i = 0; i < n; i++) {
		if (left[i] - boms[i] < 0) return false;//一旦有一个商品的数量为负，那么这些剩余的商品就不能再组成一个组合，因为组合里不可能有负数
	}
	return true;
}

//判断一个元素数量是m的vector的vec元素是否为0
bool allZero(const vector<int> &vec, int m) {
	for (int i = 0; i < m; i++) {
		if (vec[i] != 0) return false;//有一个不为0，那么整个vector就不为0
	}
	return true;
}
//判断哪种组合最优，
bool isBetter(const vector<int> &left1, const vector<int> &left2, int n, const vector<int> &result1, const vector<int> &result2, int m) {
	//匹配原则1，剩余商品的种类越少越好
	int leftsize1 = 0, leftsize2 = 0;
	for (int i = 0; i < n; i++) {
		if (left1[i] > 0) leftsize1++;//方案1里面剩余商品的种类数，有一个元素大于0， 那么就会剩有一个种类
		if (left2[i] > 0) leftsize2++;
	}
	if (leftsize1 < leftsize2) return true;
	if (leftsize1 > leftsize2) return false;
	//匹配原则2，剩余商品种类数相同的情况下，组合种类越少越好
	int kindsize1 = 0, kindsize2 = 0;
	for (int i = 0; i < m; i++) {
		if (result1[i] > 0) kindsize1++;//result是一种匹配方案，里面的元素就是每个组合的数量
		if (result2[i] > 0) kindsize2++;
	}
	if (kindsize1 <= kindsize2) return true;
	else return false;
}
//寻找所有的组合用
void search(const vector<int> &goods, const vector<vector<int>> &boms, vector<int> left, vector<int> tmpresult, vector<int> &result, int n, int m) {
	bool flag = false;//是否再添加商品组合
	vector<int> tmpleft, tmp_result;
	for (int i = 0; i < m; i++) {
		if (canSearch(boms[i], left, n)) {
			if (!flag) flag = true;//如果查找可以继续添加商品组合把flag置1
			tmpleft = left;
			tmp_result = tmpresult;
			for (int j = 0; j < n; j++) {
				tmpleft[j] = left[j] - boms[i][j];
			}
			tmp_result[i] += 1;
			search(goods, boms, tmpleft, tmp_result, result, n, m);//还能搜索出商品，递归搜索
		}
	}
	if (!flag) {//如果不能再添加商品了，搜索结束，此时得到结果为tmpresult
		//比较tmpresult和result选出一个最优的组合放到result
		if (allZero(result, m)) result = tmpresult;//一开始result全0说明result没有更新，将tmp赋值给他
		else
		{
			//计算在result的挑选方法下，剩余商品currentbestleft
			vector<int> currentbestleft = goods;
			for (int i = 0; i < m; i++)
			{
				int number = result[i];
				for (int j = 0; j < n; j++) {
					currentbestleft[j] -= number * boms[i][j];
				}
			}
			//currentbestleft与left比较
			if (isBetter(left, currentbestleft, n, tmpresult, result, m)) {
				result = tmpresult;
			}
		}
	}
}
//主函数
int main()
{
	int n, m;
	cout << "请输入n和m"<< endl;
	cin >> n >> m;//输入n种商品，m个组合
	vector<int> goods;//输入每种商品的总数,注意这里不要初始化，有过这个小错误，不要再犯
	int a;
	cout << "请输入商品每个总数"<< endl;
	for (int i = 0; i < n; ++i) {//往vector里面输入
		cin >> a;
		goods.push_back(a);
	}

	vector<vector<int>> boms;//输入m个组合，用二维vector表示
	vector<int> bom_tmp;
	int tmp;
	cout << "请输入bom组合"<< endl;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> tmp;
			bom_tmp.push_back(tmp);
		}
		boms.push_back(bom_tmp);
		bom_tmp.clear();
	}

	vector<int> left = goods;
	vector<int> result(m, 0), tmpresult(m, 0);

	search(goods, boms, left, tmpresult, result, n, m);
	cout << "最佳的匹配结果"<< endl;
	for (int i = 0; i < m; i++) {
		cout << result[i];
	}
	return 0;
}
