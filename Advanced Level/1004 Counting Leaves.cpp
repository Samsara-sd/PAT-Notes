//简单的DFS，从树的根节点开始向下搜索
#include <iostream>
#include <array>

using namespace std;

struct TreeNode
{
	int ChildAmount;
	array<int, 201> ChildNodes;
};

void countLeafPerLevel(int ThisNode, const array<TreeNode, 201>& PedigreeTree, array<int, 201>& LeafAmountChart, int Height, int& MaxHeight)
{
	MaxHeight = ( Height > MaxHeight ? Height : MaxHeight );

	if (PedigreeTree[ThisNode].ChildAmount == 0)
	{
		LeafAmountChart[Height]++;
	}
	else
	{
		for (int iter = 0; iter < PedigreeTree[ThisNode].ChildAmount; ++iter)
		{
			countLeafPerLevel(PedigreeTree[ThisNode].ChildNodes[iter], PedigreeTree, LeafAmountChart, Height + 1, MaxHeight);
		}
	}
}

int main(void)
{
	int NodeAmount, NonLeafNodeAmount;
	cin >> NodeAmount >> NonLeafNodeAmount;
	array<TreeNode, 201> PedigreeTree;
	array<int, 201> LeafAmountChart;
	for (auto &iter : PedigreeTree)  //Initilization
	{
		iter.ChildAmount = 0;
	}
	for (auto &iter : LeafAmountChart)  //Initilization
	{
		iter = 0;
	}

	for (int iter = 1; iter <= NonLeafNodeAmount; ++iter)  //Input tree's information
	{
		int TempFather, TempChildAmount, TempChild;
		cin >> TempFather >> TempChildAmount;
		PedigreeTree[TempFather].ChildAmount = TempChildAmount;
		for (int jter = 0; jter < TempChildAmount; jter++)
		{
			cin >> PedigreeTree[TempFather].ChildNodes[jter];
		}
	}

	int Height = 1;
	countLeafPerLevel(01, PedigreeTree, LeafAmountChart, 1, Height); //DFS

	for (int iter = 1; iter < Height; ++iter)
	{
		cout << LeafAmountChart[iter] << " ";
	}
	cout << LeafAmountChart[Height];

	return 0;
}