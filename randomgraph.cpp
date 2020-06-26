#include <bits/stdc++.h>
using namespace std;

#define N 100000

vector<vector<pair<int,int>>> graphGenerator(int n, double density)
{
	vector<vector<pair<int,int>>> g;
	random_device rd;
 	mt19937 gen(rd());
	uniform_int_distribution<> distrib(1, N);

	for (int k = 0; k < n; k ++){vector<pair<int,int>> l; g.push_back(l);}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (((double)distrib(gen)/(double)N) < density)
			{
				g.at(i).push_back(make_pair(j,1));
				if (i != j) {g.at(j).push_back(make_pair(i,1));}
			}
		}
	}
	return g;
}
