#include <iostream>
#include<string>
#include<cstring>
using namespace std;

class list;
class Dnode {
public:
	int data;
	Dnode* prev;
	Dnode* next;
	string title_book;
	string author_name;
	int ref_book;
	int cop_book;
};

class AVL {
public:
	class node {
	public:

		Dnode* ptr;

		int height;
		node* left;
		node* right;
		int ISSN;

		node() {
		}

		node(int num) {
			ISSN = num;
			left = right = NULL;
			height = 0;
			ptr = NULL;
		}
	};

	node* root;

public:

	AVL() {
		root = NULL;
	}

	int get_height(node* t) {
		if (t == NULL)
		{
			return -1;
		}
		else
			return t->height;
	}

	int balanceFactor(node* t) {
		if (t == NULL)
		{
			return 0;
		}
		else
			return (get_height(t->left) - get_height(t->right));
	}

	void insert(node*& t, int num, Dnode*& p) {
		if (t == NULL) {
			t = new node();
			t->ISSN = num;
			t->left = t->right = NULL;
			t->ptr = p;
			t->height = 0;
		}
		else {
			if (num > t->ISSN) {
				insert(t->right, num, p);
				if (get_height(t->left) - get_height(t->right) == -2) {
					if (num > t->right->ISSN) {
						rotate_left(t);
					}
					else
						double_rotate_left(t);
				}
			}
			else if (num < t->ISSN) {
				insert(t->left, num, p);
				if (get_height(t->left) - get_height(t->right) == 2) {
					if (num > t->right->ISSN) {
						rotate_right(t);
					}
					else
						double_rotate_right(t);
				}
			}
			t->height = 1 + max(get_height(t->left), get_height(t->right));

		}
		
	}

	void insert(int num, Dnode*& p) {
		insert(root, num, p);
	}

	void rotate_right(node*& x) {
		node* y = x->left;
		x->left = y->right;
		y->right = x;
		x->height = 1 + max(get_height(x->left), get_height(x->right));
		y->height = 1 + max(x->height, get_height(y->right));
		x = y;
	}

	void double_rotate_right(node*& x) {
		rotate_left(x->left);
		rotate_right(x);
	}

	void rotate_left(node*& x) {
		node* y = x->right;
		x->right = y->left;
		y->left = x;
		x->height = 1 + max(get_height(x->left), get_height(x->right));
		y->height = 1 + max(x->height, get_height(y->right));
		x = y;
	}


	int max(int a, int b)
	{
		return (a > b) ? a : b;
	}

	int getBalance(node* N)
	{
		if (N == NULL)
			return 0;
		return height(N->left) -
			height(N->right);
	}



	void double_rotate_left(node*& x) {
		rotate_right(x->right);
		rotate_left(x);
	}

	void in_print() {
		in_print(root);
	}

	void in_print(node* t) {
		if (t != NULL) {
			in_print(t->left);
			cout << "ISSN of books : " << t->ISSN << endl;
			check_print(t->ptr);
			in_print(t->right);
		}
	}




	int height(node* N)
	{
		if (N == NULL)
			return 0;
		return N->height;
	}

	

	node* Right_Rotate(node* b)
	{
		node* a = b->left;
		node* Temp = a->right;
 
		a->right = b;
		b->left = Temp;
		
		b->height = max(height(b->left),
			height(b->right)) + 1;
		a->height = max(height(a->left),
			height(a->right)) + 1;

		return a;
	}

	node* Left_Rotate(node* a)
	{
		node* b = a->right;
		node* Temp = b->left;

		b->left = a;
		a->right = Temp;

		a->height = max(height(a->left),
			height(a->right)) + 1;
		b->height = max(height(b->left),
			height(b->right)) + 1;

		
		return b;
	}


	node* Minimum_val_node(node* t)
	{
		node* curr = t;

		while (curr->left != NULL)
			curr = curr->left;

		return curr;
	}


	//void delete_list_node(Dnode* p) {
	//	if (p != NULL) {
	//		Dnode* temp_next = p->next;
	//		Dnode* temp_prev = p->prev;
	//		// delete temp_prev->next; 
	//			temp_prev->next = temp_next;
	//		temp_next->prev = temp_prev;
	//		delete p;

	//	}

	//}


	node* Delete_avl_Node(node* root, int key)
	{

		if (root == NULL)
			return root;

		if (key < root->ISSN)
			root->left = Delete_avl_Node(root->left, key);

		else if (key > root->ISSN)
			root->right = Delete_avl_Node(root->right, key);

		else
		{
			if ((root->left == NULL) ||
				(root->right == NULL))
			{
				node* temp = root->left ?
					root->left :
					root->right;

				if (temp == NULL)
				{
					temp = root;
					root = NULL;
				}
				else 
					*root = *temp; 
				free(temp);
			}
			else
			{
				
				node* temp = Minimum_val_node(root->right);
				
				root->ISSN = temp->ISSN;

				root->right = Delete_avl_Node(root->right,
					temp->ISSN);
			}
		}
		if (root == NULL)
			return root;

		  
		root->height = 1 + max(height(root->left),
			height(root->right));

		int balance = getBalance(root);

		if (balance > 1 &&
			getBalance(root->left) >= 0)
			return Right_Rotate(root);

		// Left Right Case 
		if (balance > 1 &&
			getBalance(root->left) < 0)
		{
			root->left = Left_Rotate(root->left);
			return Right_Rotate(root);
		}

		// Right Right Case 
		if (balance < -1 &&
			getBalance(root->right) <= 0)
			return Left_Rotate(root);

		// Right Left Case 
		if (balance < -1 &&
			getBalance(root->right) > 0)
		{
			root->right = Right_Rotate(root->right);
			return Left_Rotate(root);
		}

		return root;
	}



	void Delete_avl_Node(int x) {
		Delete_avl_Node(root, x);
	}


	void check_print(Dnode* p) {

		if (p != NULL) {
			cout << endl << "-------------------------------------------------------------- " << endl;
			cout << "ISSN of book : " << p->data << endl;
			cout << "Title of book : " << p->title_book << endl;
			cout << "Author name of book : " << p->author_name << endl;
			cout << "Number of reference copies of book : " << p->ref_book << endl;
			cout << "Number of issuable copies of book : " << p->cop_book << endl;
			cout << endl << "-------------------------------------------------------------- " << endl;
		}

	}

	void review_record() {
		int n;
		cout << "Enter ISSN of book you want to review : " << endl;
		cin >> n;
		print_record(n);
		//	in_print();
	}

	void print_record(node* t, int nm) {

		if (t == NULL) {

			return;
		}
		else if (nm == t->ISSN) {

			check_print(t->ptr);
			return;
		}
		else if (nm > t->ISSN) {
			print_record(t->right, nm);
		}
		else if (nm < t->ISSN) {
			print_record(t->left, nm);
		}

	}

	void print_record(int nm) {
		print_record(root, nm);
	}




	void PrintRoot(node* t)
	{
		cout << t->ISSN;
	}

	void PrintRoot()
	{
		PrintRoot(root);
	}

};

class list {
public:
	Dnode* head;
	Dnode* tail;
public:
	list() {
		head = NULL;
		tail = NULL;
	}

	void insert(int const num, string title, string name, int ref, int copy, AVL& o) {   //insertion
		Dnode* temp = new Dnode;
		temp->data = num;
		temp->title_book = title;
		temp->author_name = name;
		temp->ref_book = ref;
		temp->cop_book = copy;
		temp->next = NULL;
		temp->prev = NULL;

		if (head == NULL) {
			head = temp;
			tail = temp;
			tail->next = nullptr;
		}
		else {
			tail->next = temp;
			temp->prev = tail;
			temp->next = nullptr;
			tail = temp;
		}

		o.insert(num, temp);
	}

	void print() {         //print
		Dnode* temp = head;
		while (temp != NULL) {
			cout << "ISSN of book : " << temp->data << endl;
			cout << "Title of book : " << temp->title_book << endl;
			cout << "Author name of book : " << temp->author_name << endl;
			cout << "Number of reference copies of book : " << temp->ref_book << endl;
			cout << "Number of issuable copies of book : " << temp->cop_book << endl;
			cout << endl << "-------------------------------------------------------------- " << endl;
			temp = temp->next;
		}
	}

	void create_book_record(list& l, AVL& o) {

		int number;
		int ref_num;
		int cop_num;
		string bookname;
		string name;


		cout << "Enter ISSN : " << endl;
		cin >> number;
		cout << "Enter Book Name : " << endl;
		cin >> bookname;
		cout << "Enter Author of book : " << endl;
		cin >> name;
		cout << "Enter number of copies available as reference book : " << endl;
		cin >> ref_num;
		cout << "Enter number of copies available as issuable book : " << endl;
		cin >> cop_num;


		l.insert(number, bookname, name, ref_num, cop_num, o);

	}

	void change_record(Dnode* t) {

		int ref_num;
		int cop_num;
		string bookname;
		string name;

		cout << "Update Book Name : " << endl;
		cin >> bookname;
		cout << "Update Author of book : " << endl;
		cin >> name;
		cout << "Update number of copies available as reference book : " << endl;
		cin >> ref_num;
		cout << "Update number of copies available as issuable book : " << endl;
		cin >> cop_num;

		t->title_book = bookname;
		t->author_name = name;
		t->ref_book = ref_num;
		t->cop_book = cop_num;

	}

	void update_record(list& l, int nm, AVL::node* t) {
		if (t != NULL) {

			if (nm == t->ISSN) {

				change_record(t->ptr);
			}

			else if (nm > t->ISSN) {
				update_record(l, nm, t->right);
			}

			else if (nm < t->ISSN) {
				update_record(l, nm, t->left);
			}

			/*update_record(l, nm, t->left);

			if (t->ISSN == nm) {
				change_record(t->ptr);
			}
			update_record(l, nm, t->right);*/

		}
	}

	void update_record(list& l, AVL& o) {
		int number;
		cout << "Enter ISSN of book whom record you want to update: " << endl;
		cin >> number;
		update_record(l, number, o.root);
	}


	void delete_record(AVL& o) {
		int n;
		cout << "Enter ISSN of book record you want to delete : " << endl;
		cin >> n;
		o.Delete_avl_Node(n);
	}

};






int main() {
	AVL tree;
	list obj;
	int n;
	while (1) {
		system("cls");
		cout << "Enter 1 to Create a book record : " << endl;
		cout << "Enter 2 to Review a book record : " << endl;
		cout << "Enter 3 to Update a book record : " << endl;
		cout << "Enter 4 to Delete a book record : " << endl;
		cout << "Enter 0 to print record of all books : " << endl;
		cout << endl;
		cout << "Enter a number : " << endl;
		cin >> n;
		if (n == 1) {
			obj.create_book_record(obj, tree); 
		}
		if (n == 2) {
			tree.review_record();
		}
		if (n == 3) {
			obj.update_record(obj, tree);
		}
		if (n == 4) {
			obj.delete_record(tree);
		}
		if (n == 0) {
			tree.in_print();
		}
		char c;
		cout << "Enter C to continue : " << endl;
		cin >> c;

	}


	system("pause");
}