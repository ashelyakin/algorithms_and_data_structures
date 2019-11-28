#pragma once

#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

template <typename T>
class tree
{

	template <typename T>
	struct node
	{

		T data;
		node<T>* parent;
		node<T>* left;
		node<T>* right;


		//конструктор
		//x - data, p - parent, l - left, r - right
		node(T x, node* p = nullptr, node* l = nullptr, node* r = nullptr) : data(x), parent(p), left(l), right(r) {}


	};
	
	
	node<T> *root;

	int helpSize(node<T>* p)
	{
		if (p == nullptr) return 0;
		if (p->left == nullptr && p->right == nullptr)
			return 1;
		if (p->left == nullptr)
			return 1+helpSize(p->right);
		if (p->right == nullptr)
			return 1+helpSize(p->left);
		return 1+helpSize(p->left) + helpSize(p->right);
	}

public:
	
	
	template <typename T>
	class iter :public std::iterator<std::bidirectional_iterator_tag, T>
	{
		
	
	public:
		
		node<T>* it;

		//конструктор по умолчанию
		iter() :it(nullptr) {}

		//конструктор 
		iter(node<T>*p) :it(p) {}  //спрятать в private

		//конструктор копий
		iter(const iter& mit) : it(mit.it) {}

		//оператор ++ префиксный
		iter& operator++()
		{
			node<T>* res = it;
			/*auto en = res->right;
			if (en->right==en && en->left==en)    // если пытаемся перейти на end()
				throw exception("iter<T>::operator ++() :tree pointer out of bounds");*/
			if (res->right != nullptr)
			{
				res = res->right;
				while (res->left != nullptr)
					res = res->left;
				it = res;
				return *this;
			}
			else
			{
				node<T>* par = res->parent;
				if (par->left == res)
				{
					it = par;
					return *this;
				}
				else
					while (par->left != res)
					{
						res = par;
						par = par->parent;
					}
				it = par;
				return *this;
			}
		}

		//оператор -- префиксный
		iter& operator--()
		{
			/*if (it->left == it && it->right == it) //проверка если итератор на end()
			{
				it = it->parent;
				return *this;
			}*/
			if (it->left == nullptr)
			{
				node<T>* res = it;
				node<T> *par = res->parent;
				while (par->left == res && par->parent != nullptr)
				{
					res = par;
					par = par->parent;
				}
				if (par->parent == nullptr && par->left == res)    //для begin()
					throw exception("iter<T>::operator --() :tree pointer out of bounds");  
			}
			node<T>* res = it;
			if (res->left != nullptr)
			{
				res = res->left;
				while (res->right != nullptr)
					res = res->right;
				it = res;
				return *this;
			}
			else
			{
				node<T>* par = res->parent;
				if (par->right == res)
				{
					it = par;
					return *this;
				}
				else
					while (par->right != res)
					{
						res = par;
						par = par->parent;
					}
				it = par;
				return *this;
			}
		}

		//разыменование
		T const operator*()
		{
			if (it==nullptr)
				throw exception("iter<T>::operator*() :pointer == nullptr");
			else
				return it->data;
		}

		//operator==
		bool operator==(const iter& mit) const
		{
			return it == mit.it;
		}

		//operator!=
		bool operator!=(const iter& mit) const
		{
			return it != mit.it;
		}

	};


	//конструктор по умолчанию
	tree()
	{
		root = nullptr;
	}
	
	//конструктор
	//x - data, l - left, r - right
	tree(T x, node<T>* l = nullptr, node<T>* r = nullptr)
	{
		root = new node<T>(x, nullptr, l, r);
	}
	
	//begin()
	iter<T> begin() const
	{
		iter<T> res (root);
		while (res.it->left != nullptr)
		{
			res.it = res.it->left;
		}
		return res;
	}

	//end()  
	iter<T> end() const
	{
		return iter<T>(nullptr);
	}


	//добавление в БДП
	void add(T x) 
	{
		auto i = root;
		auto res = i;
		while (i!=nullptr)
		{
			res = i;
			if (x < i->data)
			{
				i = i->left;
			}
			else
				i = i->right;
				
		}
		if (root != nullptr)
		{
			i = new node<T>(x, res, nullptr, nullptr);
			if (res->data < x)
				res->right = i;
			else
				res->left = i;
		}
		else
		{
			root = new node<T>(x, nullptr, nullptr, nullptr);
		}
		
	}


	//Вывод на экран «по слоям» – с использованием очереди
	void treeTraverseWidth() const
	{
		if (root != nullptr)
		{
			queue<node<T>*> q;
			q.push(root);
			while (q.size() > 0)
			{
				auto x = q.front();
				q.pop();
				cout << x->data << " ";
				if (x->left != nullptr)
					q.push(x->left);
				if (x->right != nullptr)
					q.push(x->right);
			}
		}
	}

	//Поиск элемента в дереве
	iter<T> find(T x) const    
	{
		if (root==nullptr)
			throw exception("Empty Tree");
		node<T> *res = root;
		while (res!=nullptr)
		{
			if (x > res->data)
				res = res->right;
			else if (x < res->data)
				res = res->left;
			else if (x == res->data)
				return iter<T>(res);
		}
		return iter<T>(res);
	}

	//Возвращает минимальный элемент в дереве
	iter<T> min() const    
	{
		return begin();
	}

	//Возвращает максимальный элемент в дереве
	iter<T> max() const  
	{
		if (root == nullptr)
			throw exception("Empty Tree");
		node<T> *res = root;
		while (res->right!=nullptr)
			res = res->right;
		return iter<T>(res);
	}

	//возвращает количество элементов в дереве
	int size() const
	{
		return helpSize(root);
	}

	//Удаление узла  !!доработать
	void deleteNode(T x)  
	{
		node<T>*del = find(x).it;
		if (del == nullptr)
			return;
		if (del->right==nullptr && del->left==nullptr)  //Удаление листа
		{
			if (del->parent->right == del)
				del->parent->right = nullptr;
			else del->parent->left = nullptr;
			delete del;
		}
		else if (del->right!=nullptr || del->left!=nullptr) //Удаление узла с одним потомком
		{
			node<T>*ch;
			if (del->right!=nullptr)
				ch = del->right;
			else ch = del->left;
			node<T>*par = del->parent;
			if (par->right == del)
				par->right = ch;
			else
				par->left = ch;
			ch->parent = par;
			delete del;
		}
		else if (del != root)  // Удаление узла, если он не корень
		{
			node<T>*par = del->parent;
			node<T>*ch = del->left;
			if (par->right == del)
				par->right = ch;
			else par->left = ch;
			ch->parent = par;
			node<T>* res = ch;
			while (res->right != nullptr)
				res = res->right;
			res->right = del->right;
			del->right->parent = res;
			delete del;
		}
		else  //Удаление корня
		{
			node<T>*ch = del->left;
			node<T>* res = ch;
			while (res->right != nullptr)
				res = res->right;
			res->right = del->right;
			del->right->parent = res;
			root = ch;
			delete del;
		}

	} 

};


