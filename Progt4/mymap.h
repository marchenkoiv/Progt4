
#ifndef _map_
#define _map_

#include<stdio.h>


namespace Prog4
{
	template <typename T, typename G>
	struct Node
	{
		int color;
		const T *key;
		struct Node *left, *right;
		struct Node *parent;
		G *inf;

		void operator =(const Node<T, G>& k);
		bool operator ==(const Node<T, G>& k);
		bool operator !=(const Node<T, G>& k);
		//void operator =(const Node<T, G> k);
	};

	template <class T, class G>
	class map
	{
	private:
		Node<T, G> elist = { 1, nullptr, nullptr, nullptr, nullptr };
		Node<T, G> *EList = &elist;
		Node<T, G> **Root = &EList;



	public:
		map() {};
		~map() {  };
		void Left_rotate(Node<T, G> *x, Node<T, G>*root);
		void Right_rotate(Node<T, G>*x, Node<T, G>*root);
		int RB_Insert(Node<T, G>*x, Node<T, G>**root);
		void RB_Insert_Fixup(Node<T, G>*x, Node<T, G>**root);
		//int D_Add(Node<T, G>**root);
		G& operator [](const T& k);
		int RB_Delete(Node<T, G>*x, Node<T, G>**root);
		int RB_Delete_Fixup(Node<T, G>*x, Node<T, G>**root);
		Node<T, G>* maximum( Node<T, G>x = **root) const;
		Node<T, G>* minimum( Node<T, G>x = **root) const;
		Node<T, G>* next(Node<T, G>x) const;
		Node<T, G>* prev(Node<T, G>x) const;
		int erase(T k);
		int size();
		Node<T, G>find(T& k) const;
		G* findel(T k) const;
		int near(int k, Node<T, G>** root, Node<T, G>** rc);
		//int D_Near( Node<T, G>**root);
		void FreeTree(Node<T, G>* tree);
		void operator =(const map<T, G>& k);
	};

	template<class T, class G>
		void map<T, G>:: Left_rotate(Node<T, G> *x, Node<T, G> *root)
		{
			Node<T, G>*y = x->right, *p = x->parent;
			x->right = y->left;
			if (y->left != EList)
				y->left->parent = x;
			y->parent = p;
			if (p == EList)
				root = y;
			else
			{
				if (p->left == x)
					p->left = y;
				else
					p->right = y;
			}
			y->left = x;
			x->parent = y;
		}

		template<class T, class G>
		void map<T, G>::Right_rotate(Node<T, G> *x, Node<T, G> *root)
		{
			Node<T, G>*y = x->left, *p = x->parent;
			x->left = y->right;
			if (y->right != EList)
				y->right->parent = x;
			y->parent = p;
			if (p == EList)
				root = y;
			else
			{
				if (p->right == x)
					p->right = y;
				else
					p->left = y;
			}
			y->right = x;
			x->parent = y;
		}

		template<class T, class G>
		int map<T, G>::RB_Insert(Node<T, G> *x, Node<T, G> **root)
		{
			Node<T, G>*prev = EList, *ptr = *root;

			while (ptr != EList)
			{
				prev = ptr;
				if (x->key == ptr->key)
					return 2;
				if (x->key < ptr->key)
					ptr = ptr->left;
				else
					ptr = ptr->right;
			}
			x->parent = prev;
			if (prev == EList)
			{
				Root = &x;
				x->left = EList;
				x->right = EList;
				x->color = 1;
				return 0;
			}
			else
			{

				if (x->key < prev->key)
					prev->left = x;
				else
					prev->right = x;
			}
			x->left = EList;
			x->right = EList;
			x->color = 0;
			RB_Insert_Fixup(x, Root);
			return 0;
		}

		template<class T, class G>
		void map<T, G>::RB_Insert_Fixup(Node<T, G> *x, Node<T, G> **root)
		{
			Node<T, G>*p1, *pp, *p2;
			while (x->parent->color == 0)
			{
				p1 = x->parent;
				pp = p1->parent;
				if (p1 == pp->left)
				{
					p2 = pp->right;
					if (p2->color == 0)
					{
						p1->color = 1;
						p2->color = 1;
						pp->color = 0;
						x = pp;
					}
					else
					{
						if (x == p1->right)
						{
							x = p1;
							Left_rotate(x, *root);
							p1 = x->parent;
						}
						p1->color = 1;
						pp->color = 0;
						Right_rotate(pp, *root);
					}
				}
				else
				{
					p2 = pp->left;
					if (p2->color == 0)
					{
						p1->color = 1;
						p2->color = 1;
						pp->color = 0;
						x = pp;
					}
					else
					{
						if (x == p1->left)
						{
							x = p1;
							Right_rotate(x, *root);
							p1 = x->parent;
						}
						p1->color = 1;
						pp->color = 0;
						Left_rotate(pp, *root);
					}
				}
			}
			while (x->parent != EList)
			{
				x = x->parent;
			}
			Root = &x;
			(*Root)->color = 1;
		}


		/*template<class T, class G>
		int map<T, G>::D_Add( map **root)
		{
			int k, rc, n;
			map *x = (map*)malloc(sizeof(map));
			G *info = nullptr;
			printf("Enter key: -->");
			n = getInt(&k);
			if (n == 0)
				return 0;
			if (k == 0)
			{
				puts("Reserved key");
				return 1;
			}
			printf("Enter info:\n");
			info = getStr();
			if (info == nullptr)
				return 0;
			x->key = k;
			x->inf = info;
			rc = find_int(ptab, k, root);
			if (rc != 0)
			{
				rc = RB_Insert(x, root);
				ptab->first[k%ptab->SZ].info = x;
				ptab->first[k%ptab->SZ].key = k;
			}
			else
				rc = 2;
			printf("%s: %d\n", errmsg[rc], k);
			return 1;
		}*/

		template<class T, class G>
	    G& map<T, G>:: operator [](const T& k)
		{
			const T *ky = &k;
			Node<T, G> add = { 1, &k, EList, EList, EList, new G };
			if (*Root == EList)
			{
				RB_Insert(&add, Root);
				G* f= findel(k);
				return  *f;
			}
			Node<T, G>*ptr = maximum(**Root);
			do 
			{
				if (*ptr->key == k)
					return *(ptr->inf);
				ptr = next(*ptr);
			} while (ptr != minimum(**Root));
			RB_Insert(&add, Root);
			G* f = findel(k);
			return *f;
		}

		template<class T, class G>
		void map<T, G>:: operator =(const map<T, G>& k)
		{
			if (this != &k)
			{
				FreeTree(*Root);
				Node<T, G>*p = maximum(**k.Root);
				do
				{

					Node<T, G>*ptr = new Node<T, G>;
					ptr->key = p->key;
					*ptr->inf = *p->inf;
					RB_Insert(ptr, Root);
					p = next(*p);
				} while (p != minimum(**Root));
			}
		}
		template<class T, class G>
		void Node<T, G>:: operator =(const Node<T, G>& k)
		{
			key = k.key;
			color = k.color;
			inf = k.inf;
			left = k.left;
			right = k.right;
			parent = k.parent;
		}

	

		template<class T, class G>
		int map<T, G>::RB_Delete(Node<T, G> *x, Node<T, G> **root)
		{
			Node<T, G>*y = (Node*)malloc(sizeof(Node)), *p = (Node*)malloc(sizeof(Node));
			if (x->left == EList || x->right == EList)
				y = x;
			else
				*y = next(*x);
			if (y->left != EList)
				p = y->left;
			else
				p = y->right;
			p->parent = y->parent;
			if (y->parent == EList)
				*root = p;
			else
				if (y->parent->left->key == y->key)
					y->parent->left = p;
				else
					y->parent->right = p;
			if (y != x)
			{
				x->key = y->key;
				x->inf = y->inf;
			}
			if (y->color == 1)
				RB_Delete_Fixup(p, root);
			free(y);
			return 1;
		}

		template<class T, class G>
		int map<T, G>::RB_Delete_Fixup(Node<T, G> *x, Node<T, G> **root)
		{
			Node<T, G>*p, *w;
			while (x != *root && x->color == 1)
			{
				p = x->parent;
				if (x == p->left)
				{
					w = p->right;
					if (w->color == 0)
					{
						w->color = 1;
						p->color = 0;
						Left_rotate(p, *root);
						w = p->right;
					}
					else
					{
						if (w->left->color == 1 && w->right->color == 1)
						{
							w->color = 0;
							x = p;
						}
						else
						{
							if (w->right->color == 1)
							{
								w->color = 0;
								w->left->color = 1;
								Right_rotate(w, *root);
								w = p->right;
							}
							w->color = p->color;
							p->color = 1;
							w->right->color = 1;
							Left_rotate(p, *root);
							x = *root;
						}
					}
				}
				else
				{
					w = p->left;
					if (w->color == 0)
					{
						w->color = 1;
						p->color = 0;
						Right_rotate(p, *root);
						w = p->left;
					}
					else
					{
						if (w->right->color == 1 && w->left->color == 1)
						{
							w->color = 0;
							x = p;
						}
						else
						{
							if (w->left->color == 1)
							{
								w->color = 0;
								w->right->color = 1;
								Left_rotate(w, *root);
								w = p->left;
							}
							w->color = p->color;
							p->color = 1;
							w->left->color = 1;
							Right_rotate(p, *root);
							x = *root;
						}
					}
				}
			}
			x->color = 1;
			return 1;
		}


		template<class T, class G>
		Node<T, G>* map<T, G>::maximum( Node<T, G> x) const
		{
			
			if (x.left == nullptr || x.left == EList)
				return &x;
			return maximum(*x.left);
		}

		template<class T, class G>
		Node<T, G>* map<T, G>::minimum( Node<T, G> x) const
		{
			if (x.right == nullptr || x.right == EList)
				return &x;
			return minimum(*x.right);
		}

		template<class T, class G>
		Node<T, G>* map<T, G>::next(Node<T, G> x) const
		{
			Node<T, G>* y;
			if (x.right != EList)
				return maximum(*x.right);
			y = x.parent;
			while (y != EList && &x == y->right)
				x = *y;
			y = y->parent;
			return y;
		}

		template<class T, class G>
		Node<T, G>* map<T, G>::prev(Node<T, G> x) const
		{
			Node<T, G>* y;
			if (x.left != EList)
				return minimum(*x.right);
			y = x.parent;
			while (y != EList && &x == y->left)
				x = *y;
			y = y->parent;
			return y;
		}

		template<class T, class G>
		int map<T, G>::erase(T k)
		{
			Node<T, G>d;
			d = find(k);
			if (d != nullptr)
				RB_Delete(d, Root);
			return 1;
		}


		template<class T, class G>
		int map<T, G>::size()
		{
			int k = 0;
			Node<T, G>*ptr = maximum(**Root);
			if (ptr != nullptr)
				k++;
			while (ptr != minimum(**Root))
			{
				k++;
				ptr = next(*ptr);
			}
			return k;
		}

		template<class T, class G>
		Node<T, G> map<T, G>::find(T& k) const
		{
			Node<T, G>*ptr = maximum(*Root);
			while (ptr != minimum(*Root))
			{
				if (ptr->key == k)
					return ptr;
				ptr = next(ptr);
			}
			return nullptr;
		}

		template<class T, class G>
		G* map<T, G>::findel(T k) const
		{
			Node<T, G>*ptr = maximum(**Root);
			do
			{
				if (*ptr->key == k)
					return ptr->inf;
				ptr = next(*ptr);
			} while (ptr != minimum(**Root));
			return nullptr;
		}


		template<class T, class G>
		int map<T, G>::near(int k, Node<T, G>** root, Node<T, G>** rc)
		{
			Node<T, G>*ptr = *root;
			if (ptr == EList)
				return 1;
			near(k, &ptr->left, rc);
			if (abs(ptr->key - k) < abs(k - (*rc)->key) && abs(ptr->key - k) != 0)
				*rc = ptr;
			near(k, &ptr->right, rc);
			return 0;
		}

		/*template<class T, class G>
		int map<T, G>::D_Near( map **root)
		{
			int k, rc, n;
			map *info = (map*)malloc(sizeof(map));
			info->key = INT_MAX;
			printf("Enter key: -->");
			n = getInt(&k);
			if (n == 0)
				return 0;
			rc = near(k, root, &info);
			printf("%s: %d\n", errmsg[rc], k);
			if (rc == 0)
				printf("%d, %s", info->key, info->inf);
			ptab->first[info->key%ptab->SZ].info = info;
			ptab->first[info->key%ptab->SZ].key = info->key;
			return 1;
		}*/

		template<class T, class G>
		void map<T, G>::FreeTree(Node<T, G> *tree)
		{
			if (*tree == *EList)
				return;
			if (*tree->left != *EList)
				FreeTree(tree->left);
			if (*tree->right != *EList)
				FreeTree(tree->right);
			delete tree;
		}
	
		template<class T, class G>
		bool Node<T, G>:: operator ==(const Node<T, G>& k)
		{
			if (key == k.key && inf == k.inf && color == k.color && parent == k.parent && left == k.left && right == k.right)
				return true;
			else
				return false;
		}

		template<class T, class G>
		bool Node<T, G>:: operator !=(const Node<T, G>& k)
		{
			if (key == k.key && inf == k.inf && color == k.color && parent == k.parent && left == k.left && right == k.right)
				return false;
			else
				return true;
		}


	/*template <class T, class G>
	class AssocIt {
	private:


		Pair<T, G> *cur;

	public:

		mapit() :key(nullptr), inf(nullptr) { };
		mapit(T a, G *b) :key(a), inf(b) { };
		int operator !=(const mapit<T, G> &it) const
		{
			return key != it.key;
		}
		int operator ==(const mapit<T, G> &it) const
		{
			return key == it.key;
		}
		mapit<T, G>& operator ++()
		{

			this.next();
			return
		}
		mapit<T, G> operator ++(int);

	};*/

}



#endif