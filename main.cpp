#include <bits/stdc++.h>
#include "etw.h"
#include "randomgraph.h"
using namespace std;

#define N 100000

void printGraph(const vector<vector<pair<int,int>>> &g)
{
	cout << g.size() << endl;
	for (int k = 0; k < g.size(); k++)
	{
		cout << g.at(k).size() << endl;
		for (auto v : g.at(k)) {cout << v.first << " " << v.second << endl;}
	}
}

int degree(const vector<vector<pair<int,int>>> &g, int u)
{
	int d = 0;
	for (auto k : g.at(u)) {d += k.second;}
	return d;
}

int findDegree2(const vector<vector<pair<int,int>>> &g)
{
	for (int k = 0; k < g.size(); k++)
	{
		if (degree(g,k) == 2){return k;}
	}
	return (-1);
}

vector<vector<pair<int,int>>> dissolveVertex (const vector<vector<pair<int,int>>> &g, int u)
{
	vector<vector<pair<int,int>>> g2;
	int v1 = g.at(u).at(0).first;
	int v2 = g.at(u).at(1).first;
	bool addedEdge = false;
	for (int k = 0; k < g.size(); k++)
	{
		vector<pair<int,int>> l;
		g2.push_back(l);
		if (k != u)
		{
			for (auto v : g.at(k))
			{
				if (k == v1 && v.first == v2) {v.second++; addedEdge = true;}
				if (k == v2 && v.first == v1) {v.second++; addedEdge = true;}
				if (v.first != u) {g2.at(k).push_back(v);}
			}
		}	
	}
	if (!addedEdge)
	{
		g2.at(v1).push_back(make_pair(v2,1));
		g2.at(v2).push_back(make_pair(v1,1));
	}
	return g2;
}

void findCounterExample()
{
	random_device rd;
 	mt19937 gen(rd());
	uniform_int_distribution<> distrib(1, N);
	bool found = false;
	vector<vector<pair<int,int>>> g1;
	vector<vector<pair<int,int>>> g2;
	while (!found)
	{
		int randSize = 6 + distrib(gen) % 4;
		double randDensity = (double)distrib(gen)/(double)N;
		g1 = graphGenerator(randSize, randDensity);
		int u = findDegree2(g1);
		if (u != -1)
		{
			g2 = dissolveVertex(g1,u);
			int etw1 = etw(g1);
			int etw2 = etw(g2);
			cout << "Size : " << randSize << ", Before : " << etw1 << ", After : " << etw2 << endl;
			if (etw1 < etw2){found = true;} 
		}
		else {cout << "No degree 2" << endl;}
	}
	printGraph(g1);
	cout << "\n////////////////////////////\n";
	printGraph(g2);
}

int main()
{
	/*auto g = graphGenerator(7,0.5);
	if (findDegree2(g) != -1)
	{
		printGraph(g);
		cout << "////////////////" << endl;
		printGraph(dissolveVertex(g,findDegree2(g)));
	}*/
	findCounterExample();
	return 0;
}
