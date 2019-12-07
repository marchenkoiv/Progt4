
#ifndef _map_
#define _map_

#include<iostream>


namespace Prog4
{
	template <typename T, typename G>
	class mymapit;

	template <typename T, typename G>
	class mymap
	{
	private:
		using Node = mymap<T, G>;
		int color;
		T key;
		struct Node *left, *right;
		struct Node *parent;
		G *inf;
		Node elist = { 1, 0, nullptrptr, nullptrptr, nullptrptr };
		Node *EList = &elist;
		Node **root = EList;



	public:
		friend class mymapit<T,G>;
		Node() : color(1), key(0), left(nullptr), right(nullptr), parent(nullptr), inf(nullptr) {};
		~mymap() { FreeTree(**root); }
		typedef mymapit<T, G> Iterator;


		void Left_rotate(Node *x)
		{
			Node *y = x->right, *p = x->parent;
			x->right = y->left;
			if (y->left != EList)
				y->left->parent = x;
			y->parent = p;
			if (p == EList)
				*root = y;
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

		void Right_rotate(Node *x)
		{
			Node *y = x->left, *p = x->parent;
			x->left = y->right;
			if (y->right != EList)
				y->right->parent = x;
			y->parent = p;
			if (p == EList)
				*root = y;
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

		int RB_Insert(Node *x)
		{
			Node *prev = EList, *ptr = *root;

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
				*root = x;
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
			RB_Insert_Fixup(x, root);
			return 0;
		}

		void RB_Insert_Fixup(Node *x, Node **root)
		{
			Node *p1, *pp, *p2;
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
			*root = x;
			(*root)->color = 1;
		}



		int D_Add(Table *ptab, Node **root)
		{
			int k, rc, n;
			Node *x = (Node*)malloc(sizeof(Node));
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
		}


		G& operator [](const T& k)
		{
			Node *ptr = begin(*root);
			while (ptr != end(*root))
			{
				if (ptr->key == k)
					return ptr->inf;
				ptr = next(ptr);
			}
			return nullptr;
		}


		int RB_Delete(Node*x, Node **root)
		{
			Node *y = (Node*)malloc(sizeof(Node)), *p = (Node*)malloc(sizeof(Node));
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

		int RB_Delete_Fixup(Node *x, Node **root)
		{
			Node *p, *w;
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

		Iterator begin(Node x = **root)
		{
			if (x.left == EList)
				return x;
			return begin(*x.left);
		}

		Iterator end(Node x = **root)
		{
			if (x.right == EList)
				return x;
			return end(*x.right);
		}

		Iterator next(Node x)
		{
			Node* y;
			if (x.right != EList)
				return begin(*x.right);
			y = x.parent;
			while (y != EList && &x == y->right)
				x = *y;
			y = y->parent;
			return *y;
		}

		Node prev(Node x)
		{
			Node* y;
			if (x.left != EList)
				return end(*x.right);
			y = x.parent;
			while (y != EList && &x == y->left)
				x = *y;
			y = y->parent;
			return *y;
		}

		int erase(T k)
		{
			d = findel(k);
			if (d != nullptr)
				RB_Delete(d, root);
			return 1;
		}

		int size()
		{
			int k = 0;
			Node *ptr = begin(*root);
			if (ptr != nullptr)
				k++;
			while (ptr != end(*root))
			{
				k++;
				ptr = next(ptr);
			}
			return k;
		}

		Iterator find(T& k) const
		{
			Node *ptr = begin(*root);
			while (ptr != end(*root))
			{
				if (ptr->key == k)
					return ptr;
				ptr = next(ptr);
			}
			return nullptr;
		}

		int near(int k, Node** root, Node** rc)
		{
			Node *ptr = *root;
			if (ptr == EList)
				return 1;
			near(k, &ptr->left, rc);
			if (abs(ptr->key - k) < abs(k - (*rc)->key) && abs(ptr->key - k) != 0)
				*rc = ptr;
			near(k, &ptr->right, rc);
			return 0;
		}


		int D_Near(Table *ptab, Node **root)
		{
			int k, rc, n;
			Node *info = (Node*)malloc(sizeof(Node));
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
		}

		void FreeTree(Node * tree)
		{
			if (tree->left != EList)
				FreeTree(tree->left);
			if (tree->right != EList)
				FreeTree(tree->right);
			delete tree;
		}
	};


	template <class T, class G>
	class AssocIt {
	private:


		Pair<T, G> *cur;

	public:

		mymapit() :key(nullptr), inf(nullptr) { };
		mymapit(T a, G *b) :key(a), inf(b) { };
		int operator !=(const mymapit<T, G> &it) const
		{
			return key != it.key;
		}
		int operator ==(const mymapit<T, G> &it) const
		{
			return key == it.key;
		}
		mymapit<T, G>& operator ++()
		{

			this.next();
			return
		}
		mymapit<T, G> operator ++(int);

	};

}



#endif