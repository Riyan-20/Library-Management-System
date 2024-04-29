#include<iostream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;

template<class T>
class author_list {   // list for Author names 
	class node {
	public:
		T data;
		node* next;
	};

public:
	node* head;
	node* tail;

	author_list() {     // default constructor
		head = NULL;
		tail = NULL;
	}

	void insert_in_list(T element) {  // inserting elements at tail
		node* temp = new node;
		temp->data = element;
		temp->next = NULL;
		if (head == NULL) {
			head = temp;
			tail = temp;
		}
		else {
			tail->next = temp;
			tail = temp;
		}
	}

	void print_list() {    // printing elements
		node* temp = head;
		while (temp != NULL) {
			cout << temp->data << "  ";
			temp = temp->next;
		}
		cout << endl;
	}
};


class record {     // book record
public:
	int ISSN;
	string book_title;
	string author_names;
	int reference_books;
	int issuable_books;
public:

	record() {   // default constructor
		ISSN = 0;
	}

	record(int n, string b_t, int r_copies, int i_copies, string name) {    // parameterized constructor
		ISSN = n;
		book_title = b_t;
		reference_books = r_copies;
		issuable_books = i_copies;
		author_names = name;
	}


};


template < class T>
struct book
{
public:
	record book_record;
	int key;
	book* next;     // pointer that keeps the address of the next record of chain

	book(book* n = 0)
	{
		next = n;
	}

	book(int k, record r) {
		key = k;
		book_record = r;
	}

};

template <class T>
class hash_table
{
private:
	int table_size;
	vector <T> book_vector;
	int Curr_elements;     // total number of elements in hash table

public:
	hash_table(int const table_size = 100)      // Initially setting size to 100
	{
		book_vector.resize(table_size);
		this->table_size = table_size;
		Curr_elements = 0;
	}
	void insert(int const key, record& o)      //inserts ISSN and book record 
	{
		int index;
		int a, b, p;
		srand(key);
		p = 47;
		a = rand();
		b = rand() % p;
		int k = (a * key) + b;
		index = (k % p) % table_size;    //using universal hashing to find index 

		book<int>* pt = book_vector[index].next;   //pointer pointing the index
		if (pt)
		{
			for (; pt->next; pt = pt->next);    //this loop takes pt to the location of insertion
			pt->next = new book<int>(key, o);
		}
		else
		{
			book_vector[index].next = new book<int>(key, o);
		}
		Curr_elements++;      //incrementing total elements
	}

	bool delete_record(const int key)      //finds index by comparing elements of table with ISSN and deletes it
	{
		int index;
		int a, b, p;
		srand(key);
		p = 47;
		a = rand();
		b = rand() % p;
		int k = (a * key) + b;
		index = (k % p) % table_size;     //finding index

		book<int>* pt = book_vector[index].next;

		if (!pt) {
			return false;
		}
		if (pt->key == 0) {
			return false;
		}
		for (; pt; pt = pt->next)   //comparing indexes
		{
			if (pt->key == key)
			{
				delete_(pt);
				Curr_elements--;

				return true;
			}
		}

		return false;
	}

	T* find_record(const int key) const          //finds index by comparing elements of table with ISSN and returns it
	{
		int index;
		int a, b, p;
		srand(key);
		p = 47;
		a = rand();
		b = rand() % p;
		int k = (a * key) + b;
		index = (k % p) % table_size;        //finding index 

		book<int>* pt = book_vector[index].next;
		book<int>* pt2 = NULL;

		if (!pt) {
			return pt;
		}if (pt->key == 0) {
			return pt2;
		}

		for (; pt; pt = pt->next)
		{
			if (pt->key == key)        // comparing elements of table with ISSN 
			{
				break;
			}
			else {
				break;
			}
		}

		return pt;
	}

	T* delete_(book<int>*& ptr) {
		book<int>* pt = NULL;
		delete pt;
		ptr->key = 0;
		return ptr;
	}

	~hash_table()                           //destructor
	{
		for (int i = 0; i < table_size; i++)
		{
			book<int>* pt = (book_vector[i]).next;

			for (; pt;)
			{
				book<int>* pt2 = pt->next;
				delete pt;
				pt = pt2;

			}
			(book_vector[i]).next = 0;
		}
	}

	T* check_record(const int key) const          //finds index by comparing elements of table with ISSN and returns it
	{
		int index;
		int a, b, p;
		srand(key);
		p = 47;
		a = rand();
		b = rand() % p;
		int k = (a * key) + b;
		index = (k % p) % table_size;        //finding index 

		book<int>* pt = book_vector[index].next;

		if (!pt) {
			return pt;
		}

		for (; pt; pt = pt->next)
		{
			if (pt->key == key)        // comparing elements of table with ISSN 
			{
				break;
			}
			else {
				break;
			}
		}
		return pt;
	}

	void create_book_record() {

		int number;
		int ref_num;
		int cop_num;
		string bookname;
		string name;

		cout << endl << "Enter ISSN : " << endl;
		cin >> number;
		book<int>* pt = check_record(number);

		if (pt)    // checks uniqueness of ISSN
		{
			cout << "ISSN already exists..." << endl;
		}
		else {
			cout << "Enter Book Name : " << endl;
			cin >> bookname;
			cout << "Enter Author of book : " << endl;
			cin >> name;
			cout << "Enter number of copies available as reference book : " << endl;
			cin >> ref_num;
			cout << "Enter number of copies available as issuable book : " << endl;
			cin >> cop_num;

			record r(number, bookname, ref_num, cop_num, name);      //creates record object 
			insert(number, r);         // inserting ISSN and book record
		}
	}

	void review_book_record() {
		int n;
		cout << "Enter ISSN of book you want to review : " << endl;
		cin >> n;
		book<int>* pt = find_record(n);       // Finds location of book record
		if (pt)
		{

			cout << endl << "-------------------------------------------------------------- " << endl;
			cout << "ISSN of book : " << pt->book_record.ISSN << endl;
			cout << "Title of book : " << pt->book_record.book_title << endl;
			cout << "Author name of book : " << pt->book_record.author_names << endl;
			cout << "Number of reference copies of book : " << pt->book_record.reference_books << endl;
			cout << "Number of issuable copies of book : " << pt->book_record.issuable_books << endl;
			cout << endl << "-------------------------------------------------------------- " << endl;

		}
		else
			cout << endl << "ISSN not found" << endl;
	}

	void update_book_record() {

		int n;
		cout << "Enter ISSN of book whom record you want to update : " << endl;
		cin >> n;


		book<int>* pt = find_record(n);    // Finds location of book record
		if (pt)
		{
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

			// Updating book record

			pt->book_record.book_title = bookname;
			pt->book_record.author_names = name;
			pt->book_record.reference_books = ref_num;
			pt->book_record.issuable_books = cop_num;

			cout << endl << "Book record is updated..." << endl;

		}
		else
		{
			cout << endl << "ISSN not found" << endl;
		}



	}

	void delete_book_record() {
		int n;
		cout << "Enter ISSN of book you want to delete : " << endl;
		cin >> n;
		if (delete_record(n))       // deletes book record
		{
			cout << "Book record deleted..." << endl;
		}
		else
		{
			cout << endl << "ISSN not found..." << endl;
		}

	}

};




int main() {

	hash_table < book <int> >obj;       // Book type hash_table object

	int n;
	while (1) {
		system("cls");
		cout << "Enter 1 to Create a book record : " << endl;
		cout << "Enter 2 to Review a book record : " << endl;
		cout << "Enter 3 to Update a book record : " << endl;
		cout << "Enter 4 to Delete a book record : " << endl;

		cout << endl;
		cout << "Enter a number : " << endl;
		cin >> n;
		if (n == 1) {
			obj.create_book_record();
		}
		if (n == 2) {
			obj.review_book_record();
		}
		if (n == 3) {
			obj.update_book_record();
		}
		if (n == 4) {
			obj.delete_book_record();
		}

		char c;
		cout << endl << "Enter C to continue : " << endl;
		cin >> c;


	}



	system("Pause");
}