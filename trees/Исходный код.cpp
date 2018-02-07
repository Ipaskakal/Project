#include <iostream>
#include <fstream>
#include <string>

#define RED false
#define BLACK true

using namespace std;

struct RBtree
{
	RBtree* parent;
	RBtree* left;
	RBtree* right;
	bool color;
	int value;
	int size;
	RBtree(RBtree* par) : parent(par), color(BLACK), left(NULL), right(NULL),size(0){}
};

struct List
{
	int field;
	RBtree* point;
	List* next;
	List(int x, RBtree* RB) :field(x), point(RB), next(NULL){}
};

RBtree *NIL = new RBtree(nullptr);

RBtree * uncle( RBtree* n);

RBtree * broth( RBtree* n);

RBtree * grandparent( RBtree* n);

void delete_val( RBtree* n, int val);


void insert(RBtree *&n, int val);

void insert1( RBtree* n);

void insert2( RBtree* n);

void insert3( RBtree* n);

void insert4( RBtree* n);

void insert5( RBtree* n);

void delete1( RBtree* n);

void delete2( RBtree* n);

void delete3( RBtree* n);

void delete4( RBtree* n);

bool is_nil( RBtree* n);

void show(RBtree* n,int x,int y);

void import_from_file(RBtree*& RB);

void output_numeration(List*& list);

RBtree* value_by_index(RBtree* RB, int x);

int index_by_value(RBtree* RB);

int main()
{
	RBtree* RB = new RBtree (NULL);
	int n = 0;
	int val;
	while (n != 8)
	{
		cout << "1-insert\n";
		cout << "2-delete\n";
		cout << "3-test balance RB(output count of black and red leafs for every NIL)\n";
		cout << "4-test numeration(output numeration of every element by rows)\n";
		cout << "5-input from file\n";
		cout << "6-find leaf by index\n";
		cout << "7-find index of leaf\n";
		cout << "8-exit\n";
		cin >> n;
		switch (n)
		{
		case 1:
		{
				  cin >> val;
				  insert(RB, val);
				  while (RB->parent != NULL)
					  RB = RB->parent;
				  break;
		}
		case 2:
		{
				  cin >> val;
				  delete_val(RB, val);
				  while (RB->parent != NULL)
					  RB = RB->parent;
				  break;
		}
		case 3:
		{
				  int count = 0;
				  int count1 = 0;
				  show(RB, count, count1);
				  break;
		}
		case 4:
		{
				  List* list = new List(1, RB);
				  output_numeration(list);
				  break;
		}
		case 5:
		{
				  import_from_file(RB);
				  cout << "count of numbers " << RB->size << endl;
				  break;
		}
		case 6:
		{
				  cout << "input index between 1 and "<<RB->size<<":\n";
				  int k;
				  cin >> k;
				  while (k<1 || k>RB->size)
				  {
					  cin >> k;
				  }
				  cout << value_by_index(RB, k)->value << endl;
				  break;
		}
		case 7:
		{
				  cout << "input value of leaf:\n";
				  int k;
				  cin >> k;
				  RBtree* temp = RB;
				  while (!is_nil(temp) && temp->value != k)
				  {
					  if (temp->value > k) temp = temp->left;
					  if (temp->value < k) temp = temp->right;
				  }
				  if (!is_nil(temp) && temp->value == k) cout << index_by_value(temp);
				  else cout << " this value doesnt exist";
				  break;
		}
		}
		cout << "\n\n\n\n\n";
	}
	return 0;
}

int index_by_value(RBtree* RB)
{
	int x = RB->left->size + 1;
	while (RB->parent)
	{
		if (RB == RB->parent->left) RB = RB->parent;
		else
		if (RB == RB->parent->right) 
		{
			x += RB->parent->left->size + 1; RB = RB->parent;
		}
	}
	return x;
}

RBtree* value_by_index(RBtree* RB, int x)
{
	if (!is_nil(RB))
	{
		int tem = RB->left->size + 1;
		if (x == tem) return RB;
		else if (x < tem) return value_by_index(RB->left, x);
		else return value_by_index(RB->right, x - tem);
	}
	 else return 0;
}

void output_numeration(List*& list)
{
	if (list)
	{
		List* temp = list;
		cout << list->point->size << ' ';
		if (!is_nil(list->point->left))
		{
			while (temp->next) temp = temp->next;
			temp->next = new List(list->field + 1, list->point->left);
		}
		if (!is_nil(list->point->right))
		{
			while (temp->next) temp = temp->next;
			temp->next = new List(list->field + 1, list->point->right);
		}
		if (list->next)
		{
			temp = list;
			list = list->next;
			if (list->field > temp->field) cout << endl;
			delete(temp);
			output_numeration(list);

		}
	}
}

void show(RBtree* n,int x,int y)
{
	if (!is_nil(n))
	{
		
		if (n->color == BLACK)
		{
			
			show(n->left, x+1,y);
			show(n->right, x+1,y);
		}
		else
		{
			show(n->left, x,y+1);
			show(n->right, x,y+1);
		}
	}
	else cout <<' '<< x << ' '<< y<<endl;
}

void import_from_file(RBtree*& RB)
{
	cout << "input name of file:\n";
	string s;
	cin >> s;
	ifstream fin(s);
	if (!fin.is_open())
		cout << "cant find file\n";
	else
	{
		int k;
		while (!fin.eof())
		{
			fin >> k;
			insert(RB, k);
			while (RB->parent != NULL)
				RB = RB->parent;
		}
		fin.close();
	}
}

bool is_nil( RBtree* n)
{
	if (n==NIL)
		return 1;
	return 0;
}

void insert(RBtree *&n, int val)
{
	RBtree* temp = n;
	RBtree *prev = nullptr;
	while ((temp->left != NULL) && (temp->right != NULL))
	{
		prev = temp;
		if (temp->value > val)
		{
			temp->size++; 
			if (!is_nil(temp->left)) 
				temp = temp->left;
			else break;
		}
		else if (temp->value < val)
		{
			temp->size++;
			if (!is_nil(temp->right))
				temp = temp->right;
			else break;
		}
		else
		{
			while (temp)
			{
				temp = temp->parent;
				if (temp) temp->size--;
			}
			return;
		}
	};
	if (prev )
	{
		if (prev->value>val)
		{
			prev->left = new RBtree(prev);
			prev->left->value = val;
			prev->left->color = RED;
			prev->left->size = 1;
			prev->left->left = NIL;
			prev->left->right = NIL;
			insert1(prev->left);
		}
		else
		{
			prev->right = new RBtree(prev);
			prev->right->value = val;
			prev->right->color = RED;
			prev->right->size = 1;
			prev->right->left = NIL;
			prev->right->right = NIL;
			insert1(prev->right);
		}
		
	}
	else
	{
		n = new RBtree(nullptr);
		n->value = val;
		n->size = 1;
		n->left = NIL;
		n->right = NIL;
		insert1(n);
	}
	
	
}

RBtree * grandparent( RBtree* n)
{
	if ((n != NULL) && (n->parent != NULL))
		return n->parent->parent;
	else
		return NULL;
}

RBtree * uncle( RBtree* n)
{
	struct RBtree* g = grandparent(n);
	if (g == NULL)
		return NULL; 
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}

RBtree * broth( RBtree* n)
{
	if (n->parent->left == n)
		return n->parent->right;
	else
		return n->parent->left;
}

void rotate_left( RBtree* n)
{
	struct RBtree* temp = n->right;

	temp->parent = n->parent; 
	if (n->parent != NULL)
	{
		if (n->parent->left == n)
			n->parent->left = temp;
		else
			n->parent->right = temp;
	}

	n->right = temp->left;
	if (temp->left != NULL&&!is_nil(temp->left))
		temp->left->parent = n;

	n->parent = temp;
	temp->left = n;
	n->parent->size = n->size;
	n->size = n->left->size + n->right->size + 1;
}

void rotate_right( RBtree* n)
{
	struct RBtree *temp = n->left;

	temp->parent = n->parent; 
	if (n->parent != NULL) 
	{
		if (n->parent->left == n)
			n->parent->left = temp;
		else
			n->parent->right = temp;
	}

	n->left = temp->right;
	if (temp->right != NULL&&!is_nil(temp->right))
		temp->right->parent = n;

	n->parent = temp;
	temp->right = n;
	n->parent->size = n->size;
	n->size = n->left->size + n->right->size + 1;
}

void insert1( RBtree* n)
{
	if (n->parent == NULL)
		n->color = BLACK;
	else
		insert2(n);
}

void insert2( RBtree* n)
{
	if (n->parent->color == BLACK )
		return;
	else
		insert3(n);
}

void insert3( RBtree* n)
{
	struct RBtree *u = uncle(n), *g;

	if ((u != NULL) && (u->color == RED)) 
	{
		n->parent->color = BLACK;
		u->color = BLACK;
		g = grandparent(n);
		g->color = RED;
		insert1(g);
	}
	else
	{
		insert4(n);
	}
}

void insert4( RBtree* n)
{
	struct RBtree *g = grandparent(n);

	if ((n == n->parent->right) && (n->parent == g->left))
	{
		rotate_left(n->parent);
		n = n->left;
	}
	else if ((n == n->parent->left) && (n->parent == g->right))
	{
		
		rotate_right(n->parent);
		n = n->right;
	}
	insert5(n);
}

void insert5( RBtree  *n)
{
	struct RBtree *g = grandparent(n);

	n->parent->color = BLACK;
	g->color = RED;
	if ((n == n->parent->left) && (n->parent == g->left)) 
	{
		g->color = RED;
		n->parent->color = BLACK;
		rotate_right(g);
		
	}
	else 
	{
		g->color = RED;
		n->parent->color = BLACK;
		rotate_left(g);
	}
}


void delete_val( RBtree* n, int val)
{
	RBtree* temp = n;
	while (!is_nil(n) && (n->value != val))
	{
		if (n->value > val)
		{
			temp = n;
			temp->size--;
			n = n->left;
		}
		else if (n->value < val)
		{
			temp = n;
			temp->size--;
			n = n->right;
		}
	}
	if (n->value == val) delete1(n);
	else
	{
		while (temp)
		{
			temp->size++;
			temp = temp->parent;
		}
		cout << "not found";
	}
}

void delete1( RBtree* n)
{
	if (is_nil(n->left) && is_nil(n->right))
	{
		if (n->parent)
		{
			if (n->parent->left == n)
			{
				n->parent->left = n->left;
				n->left->color = BLACK;
				n->left->parent = n->parent;
				if (n->color == BLACK) delete4(n->parent->left);
				delete(n);
			}
			else
			{
				n->parent->right = n->right;
				n->right->color = BLACK;
				n->right->parent = n->parent;
				if (n->color == BLACK) delete4(n->parent->right);
				delete(n);
			}
		}
		
	}
	else
	delete2(n);

}

void delete2( RBtree* n)
{
	if (is_nil(n->left) && (!is_nil(n->right)))
	{
		if (n->parent)
		{
			if (n->parent->left == n)
			{
				n->parent->left = n->right;
				n->right->parent = n->parent;
				if (n->color == BLACK) delete4(n->parent->left);
			}

			else
			{
				n->parent->right = n->right;
				n->right->parent = n->parent;
				if (n->color == BLACK) delete4(n->parent->right);
			}
			
		}
		else {
			n = n->right;
			n->parent = NULL;
		}
		delete(n);

		
	}
	else
	if (is_nil(n->right) && (!is_nil(n->left)))
	{
		if (n->parent)
		{
			if (n->parent->left == n)
			{
				n->parent->left = n->left;
				n->left->parent = n->parent;
				if (n->color == BLACK) delete4(n->parent->left);
			}
			else
			{
				n->parent->right = n->left;
				n->left->parent = n->parent;
				if (n->color == BLACK) delete4(n->parent->right);
			}
			
		}
		else {
			n = n->left;
			n->parent = NULL;
		}

		delete(n);
		
	}
	else
		delete3(n);
}

void delete3( RBtree* n)
{
	n->size--;
	RBtree* temp = n->right;
	while (!is_nil(temp->left))
	{
		temp->size--;
		temp = temp->left;
	}
	n->value = temp->value;
	delete1(temp);
}

void delete4( RBtree* n)
{
	n->color = BLACK;
	if (broth(n)->color == RED)
	{
		if (n->parent->left = n)
			rotate_left(n->parent);
		else
			rotate_right(n->parent);
		n->parent->color = RED;
		n->parent->parent->color = BLACK;
		delete4(n);
	}
	else if ((broth(n)->left->color == BLACK) && (broth(n)->right->color == BLACK))
	{
		if (n->parent->color == RED)
		{
			broth(n)->color = RED;
			n->parent->color = BLACK;
			delete4(n->parent);
		}
	}
	else
	{
		if ((broth(n)->left->color == RED) && (broth(n)->right->color == BLACK))
		{
			if (n->parent->left == n)
			{
				broth(n)->color = RED;
				broth(n)->left->color = BLACK;
				rotate_right(broth(n));
				delete4(n);
			}
			else
			{
				broth(n)->left->color = BLACK;
				broth(n)->color = n->parent->color;
				n->parent->color = BLACK;
				rotate_right(n->parent);
				NIL->parent = nullptr; return;
			}
		}
		else
		if (broth(n)->right->color == RED)
		{
			if (n->parent->left == n)
			{
				broth(n)->right->color = BLACK;
				broth(n)->color = n->parent->color;
				n->parent->color = BLACK;
				rotate_left(n->parent);
				NIL->parent = nullptr; return;
			}
			else
			{
				broth(n)->color = RED;
				broth(n)->right->color = BLACK;
				rotate_left(broth(n));
				delete4(n);
			}
		}
	}
}

