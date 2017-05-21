#include <iostream>
#include <fstream>



using namespace std;

template <class T>
struct Node
{
	T element;
	Node<T> *left, *right, *pparent;
};

template <class T>
class BST {
private:
	Node<T> *root;
	int count;
public:
	BST();
	void show(ostream&cout, Node<T> *Tree);
	void add(const T&);
	bool search(const T&, Node<T> *Tree);
	void input(const string file);
	void output(const string file);
	Node<T>* MinElement(Node<T>* min);
	Node<T>* getroot();
	Node<T>* getcount();
	Node<T>* del(Node<T> *Tree, T el);


};


int main() {
	system("chcp 1251");

	BST<int> MyTree;
	char file1[20] = "File1.txt";
	char file2[20] = "File2.txt";
	MyTree.input(file1);
	MyTree.show(cout, MyTree.getroot());
	MyTree.output(file2);
	if (MyTree.search(10, MyTree.getroot()) == true) {
		cout << "Элемент найден" << endl;
	}
	else cout << "Элемент не найден" << endl;
	MyTree.del(MyTree.getroot(), 4);
	MyTree.show(cout, MyTree.getroot());



	system("pause");

	return 0;
}

template <typename T> BST<T>::BST() {
	root = NULL;
	count = 0;
}

template <typename T> void BST<T>::show(ostream&cout, Node<T> *Tree) {
	if (Tree != NULL) {

		cout << Tree->element << endl;;
		show(cout, Tree->left);
		show(cout, Tree->right);

	}
}

template <typename T> void BST<T>::add(const T &x) {
	Node<T>* daughter = new Node<T>;
	daughter->element = x;
	daughter->left = daughter->right = nullptr;
	Node<T>* parent = root;
	Node<T>* temp = root;

	while (temp)
	{
		parent = temp;
		if (x < temp->element)
			temp = temp->left;
		else temp = temp->right;
	}

	if (!parent)
		root = daughter;
	else {
		if (x < parent->element)
			parent->left = daughter;
		else
			parent->right = daughter;
	}
	count++;
}


template <typename T> Node<T>* BST<T>::getroot() {
	return root;
}

template <typename T> Node<T>* BST<T>::getcount() {
	return count;
}

template <typename T> void BST<T>::input(const string file) {
	ifstream fin(file);
	try
	{
		int temp;
		while (!fin.eof())
		{

			fin >> temp;
			add(temp);

		}
		fin.close();
	}
	catch (int i)
	{
		cout << "This file don't find" << endl;
	}

}

template <typename T> void BST<T>::output(const string file) {
	ofstream fout(file);
	show(fout, root);
	fout.close();
}

template <typename T> bool BST<T>::search(const T&x, Node<T>* Tree) {
	if (Tree == nullptr)
		return false;
	if (x == Tree->element) {
		return true;
	}
	else if (x < Tree->element) {
		search(x, Tree->left);
	}
	else search(x, Tree->right);
}

template <typename T> Node<T>* BST<T>::MinElement(Node<T>* min) {
	if (min->left == nullptr)
		return min;
	else
		return MinElement(min->left);


}



template <typename T>
Node<T>* BST<T>::del(Node<T> *Tree, T el) {
	if (Tree == nullptr) return Tree;
	if (el < Tree->element) Tree->left = del(Tree->left, el);
	else if (el > Tree->element) Tree->right = del(Tree->right, el);
	else if ((Tree->left != nullptr) && (Tree->right != nullptr)) {
		Tree->element = MinElement(Tree->right)->element;
		Tree->right = del(Tree->right, Tree->element);
	}
	else {
		if (Tree->left != nullptr) Tree = Tree->left;
		else Tree = Tree->right;
	}
	count--;
	return Tree;
}
