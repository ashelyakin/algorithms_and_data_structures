#include "tree.h"

int main()
{
	auto t = tree<int>(52);
	t.add(25);
	t.add(17);
	t.add(48);
	t.add(23);
	t.add(28);
	t.add(50);

	t.add(86);
	t.add(68);
	t.add(96);
	t.add(59);
	t.add(80);
	t.add(91);

	t.treeTraverseWidth();

	auto i = t.begin();
	assert(*i == 17);
	for (int c = 0; c < 5; ++c)
	{
		++i;
	}
	--i;
	--i;
	assert(*i == 28);

	i = t.find(1);
	assert(i == nullptr);
	i = t.find(80);
	assert(*i == 80);

	assert(*t.min() == 17);
	assert(*t.max() == 96);

	assert(t.size() == 13);

	//t.testsend();

	/*cout << endl;
	t.deleteNode(80);
	t.treeTraverseWidth();*/

	//демонстрация iter на примере алгоритмов std::find и std::count_if
	//используемый диапазон [begin(), last] т.к. нет реализации end()
	i = find(t.begin(), t.max(), 80);
	assert(*i == 80);
	auto c = count_if(t.begin(), t.max(), [](int x) {return x <30; });
	assert(c == 4);

	cout << endl << "tests succsessful"<<endl;

}