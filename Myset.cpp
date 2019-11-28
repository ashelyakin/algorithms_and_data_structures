#include "tree.h"
#include<set>
#include <cmath> 
#include <ctime>
#include <locale>

template <typename T>
class Myset
{

	tree<T> myset;

	
public:
	

	Myset()
	{ 
		myset = tree<T>();
	}


	void insert(T x)
	{
		myset.add(x);
	}

	
	bool contains(T x)
	{
		auto res = myset.find(x);
		if (res == nullptr)
			return false;
		else
			return true;
	}

	void erase(T x)
	{
		myset.deleteNode(x);
	}

	void print()
	{
		myset.treeTraverseWidth();
	}

	int size()
	{
		return myset.size();
	}
};

int erythMyset(const int& n)
{
	assert(n >= 2);
	Myset<int> primes;
	for (int i = 2; i <=n; ++i)
		primes.insert(i);
	auto c = round(sqrt(n));
	for (int i = 2; i <= c; ++i)
	{
		if (primes.contains(i))
		{		
			auto x = i+i;
			while (x <= n)
			{
				primes.erase(x);
				x += i;
			}
		}
	}
	return primes.size();
}

int erythSet(const int& n)
{
	assert(n >= 2);
	set<int> primes;
	for (int i = 2; i <= n; ++i)
		primes.insert(i);
	auto c = round(sqrt(n));
	for (int i = 2; i <= c; ++i)
	{
		if (primes.find(i)!=primes.end())
		{
			auto x = i + i;
			while (x <= n)
			{
				primes.erase(x);
				x += i;
			}
		}
	}
	return primes.size();
}

int main()
{
	setlocale(LC_ALL, "Russian");
	//проверка Myset
	Myset<int> s;
	s.insert(50);
	s.insert(25);
	s.insert(75);
	assert(s.contains(50));
	assert(!s.contains(2));
	s.erase(75);
	assert(!s.contains(75));
	s.insert(100);
	s.insert(3);
	s.insert(10);
	s.erase(100);
	assert(s.size() == 4);


	//проверка erythMyset и erythSet

	assert(erythMyset(2) == 1);
	assert(erythMyset(10) == 4);
	assert(erythMyset(12) == 5);
	assert(erythMyset(13) == 6);

	assert(erythSet(2) == 1);
	assert(erythSet(10) == 4);
	assert(erythSet(12) == 5);
	assert(erythSet(13) == 6);

	cout << "tests succsessful" << endl;

	//сравнение со стандартным set

	erythMyset(10000);
	int t = clock();
	cout << "ƒл€ вычислени€ erythMyset(10000) понадобилось "<< ((float)t) / CLOCKS_PER_SEC << " секунд"<<endl;
	t = clock();
	erythSet(10000);
	cout << "ƒл€ вычислени€ erythSet(10000) понадобилось " << ((float)t) / CLOCKS_PER_SEC << " секунд" << endl;

	/*ƒл€ вычислени€ erythMyset(100000) понадобилось 37.036 секунд
	ƒл€ вычислени€ erythSet(100000) понадобилось 37.04 секунд*/
}