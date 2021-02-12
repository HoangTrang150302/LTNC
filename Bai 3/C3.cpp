#include<iostream>
#include<vector>
using namespace std;

bool mirrornum(int);

int main()
{
	int n;
	cin >> n;
	int a, b;
	for (int i = 0; i < n; i++)
	{
		int count = 0;
		cin >> a >> b;
		for(int j = a; j <= b; j++)
		{
			if(mirrornum(j))
			count++;
		}
		cout << count << endl;
	}
	return 0;
}

bool mirrornum(int n)
{
	vector<int> numbers;
	while(n)
	{
		int a = n % 10;
		numbers.push_back(a);
		n = n/10;		
	}
	for (int i = 0; i < numbers.size()/2; i++)
	{
		if(numbers[i] != numbers[numbers.size() - 1 - i])
		{
			return false;
		}
	}
	return true;
}
