#include <bits/stdc++.h>
using namespace std;

bool* dfs(const vector<vector<pair<int,int>>> &g, const bool *mask, int u, int n)
{
	bool *seen = new bool[static_cast<size_t>(n)];
	for (int i = 0; i < n; i++) {seen[i] = false;};
	vector<int> stack;
	stack.push_back(u);
	while (!stack.empty())
	{
		int v = stack.back();
		stack.pop_back();
		for (pair<int,int> k : g.at(v))
		{
			if (!seen[k.first] && mask[k.first])
			{
				stack.push_back(k.first);
			}
		}
		seen[v] = true;
	}
	fflush(stdout);
	return seen;
}

int cost(const vector<vector<pair<int,int>>> &g, const vector<int> &layout, int k, int n)
{
	int c = 0;
	bool *mask = new bool[static_cast<size_t>(n)];
	for (int i = 0; i < n; i++){mask[layout.at(i)] = (i<k)?(false):(true);}
	bool *connected_comp = dfs(g, mask, layout.at(k), n);
	
	/*
	for (int i = 0; i < n; i++){cout << mask[i] << " ";}
	cout << endl;
	for (int i = 0; i < n; i++){cout << connected_comp[i] << " ";}
	cout << endl;
	*/

	for (int i = 0; i < k; i++)
	{
		for (pair<int,int> v : g.at(layout.at(i)))
		{
			if (connected_comp[v.first]){c += v.second;}		
		}
	}
	delete[] mask;
	delete[] connected_comp;
	return c;
}

int width(const vector<vector<pair<int,int>>> &g, const vector<int> &layout, int n)
{
	int m = 0;
	for (int k = 0; k < n; k++)
	{
		m = max(m, cost(g,layout,k,n));
	}
	return m;
}

int fact(int n)
{
	return (n == 0)?1:(n*fact(n-1));
}

int etw(const vector<vector<pair<int,int>>> &g)
{
	int n = g.size();
	vector<int> layout;
	for (int k = 0; k < n; k++) {layout.push_back(k);}
	bool b = true;
	int m = INT_MAX;
	
	int count= 0;
	int tot = fact(n);

	while (b)
	{
		// if (!(count % 100000)){cout << 100*((double)count / (double)tot) << "%" << endl;}
		m = min(m,width(g,layout,n));
		b = next_permutation(layout.begin(),layout.end());
		count++;
	}
	return m;
}

void readGraph()
{
	int n;
	cin >> n;
	vector<vector<pair<int,int>>> g;
	for (int t = 0; t < n; t++)
	{
		vector<pair<int,int>> liste_adj;
		g.push_back(liste_adj);
		int k;
		cin >> k;
		for (int i = 0; i < k; i++)
		{
			int v,m;
			cin >> v >> m;
			g.at(t).push_back(make_pair(v,m));
		}
	}
	int k = etw(g);
	cout << "Edge-treewidth = " << k << endl;
}

