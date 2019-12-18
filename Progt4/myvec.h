
#ifndef _vector_
#define _vector_


#include <iostream>

namespace Prog4
{
	template <class INF>
	class vectorIt;

	template <class INF>
	class vector {

		friend class vectorIt< INF>;

	private:

		static const int QUOTA = 10;
		int cnt, cur;
		INF *arr;
	public:

		vector() :cnt(QUOTA), cur(0), arr(new INF[QUOTA]) { };
		vector(const vector<INF> &);
		~vector() { delete[] arr; }
		vector<INF>& operator = (const vector<INF> &);
		int getPos(const int &s) const;
		int size() const { return cur; }
		INF & operator[ ](const int &); // l-value
		const INF & operator[ ](const int &) const; // r-value
		void push_back(const INF&);
		bool empty() const;
		typedef vectorIt<INF> Iterator;
		//friend vectorIt< INF> operator +(vectorIt< INF> a, int b);
		Iterator begin();
		Iterator end();
		Iterator find(const int &) const;
		void erase(vectorIt< INF>);

	};


		template <class INF>
	vector<INF>::vector(const vector< INF> &a) :cnt(a.cnt), cur(a.cur), arr(new INF[a.cnt])
	{
		for (int i = 0; i < cnt; ++i)
			arr[i] = a.arr[i];

	}

		template <class INF>
	vector<INF>& vector< INF>::operator = (const vector< INF> &a) 
	{
		if (this != &a) 
		{
			delete[] arr;
			arr = new INF [cnt = a.cnt];
			cur = a.cur;
			for (int i = 0; i < cnt; ++i)
				arr[i] = a.arr[i];

		}
		return *this;
	}

	template <class INF>
	bool vector< INF>::empty() const
	{
		if (cur == 0)
			return true;
		else
			return false;
	}

	template <class INF>
	void vector< INF>::push_back(const INF& a)
	{ 
		if (cur%10 == 0 && cur!=0)
		{
			INF *old = arr;
			arr = new INF[cnt += QUOTA];
			for (int i = 0; i < cur; ++i)
				arr[i] = old[i];
			delete[] old;
		}
		arr[cur] = a;
		cur++;
	}

		template <class INF>
	int vector<INF>::getPos(const int &s) const
	{
			if ( s>=0 && s<cur)
				return s;

		return -1;
	}


		template <class INF>
	INF & vector<INF>::operator[](const int &s)
	{
		int i = getPos(s);
		if (i < 0) 
		{
			i = cur;
			if (cur >= cnt || cur==cnt-1) 
			{
				INF *old = arr;
				arr = new INF[cnt += QUOTA];
				for (i = 0; i < cur; ++i)
					arr[i] = old[i];
				delete[] old;
			}

			++cur;
		}
		return arr[i];
	}

		template <class INF>
	const INF & vector< INF>::operator[ ](const int &s) const
	{
		int i = getPos(s);
		if (i < 0)
			throw std::exception("Illegal index");
		return arr[i];
	}

		template <class INF>
	vectorIt< INF> vector< INF>::begin()
	{

		return vectorIt<INF>(this->arr);

	}

	template <class INF>
	vectorIt< INF> vector< INF>::end()
	{

		return vectorIt<INF>(this->arr + cur);

	}
		template <class INF>
	vectorIt< INF> vector< INF>::find(const int &s) const
	{
		int i = getPos(s);
		if (i < 0)
			i = cur;
		return vectorIt<INF>(this->arr + i);
	}


	template <class INF>
	void vector< INF>::erase(vectorIt<INF> a)
	{
		for (int i = 0; i < cur; ++i)
			if (vectorIt<INF>(this->arr + i) == a)
			{
				cur--;
				for (int j = i; j < cur; ++j)
				{
					arr[j] = arr[j+1];
				}
				return;
			}
	}



	template <class INF>
	class vectorIt 
	{
	private:

		INF *cur;

	public:

		vectorIt() :cur(0) { }
		vectorIt(INF *a) :cur(a) { }
		int operator !=(const vectorIt< INF> &) const;
		int operator ==(const vectorIt< INF> &) const;
		INF& operator *();
		INF* operator ->();
		vectorIt< INF> operator +=(int a);
		vectorIt<INF>& operator ++();
		vectorIt<INF> operator ++(int);

	};

		template <class INF>
	int vectorIt<INF>::operator !=(const vectorIt< INF> &it) const
	{
		return cur != it.cur;
	}

	template <class INF>
	int vectorIt<INF>::operator ==(
		const vectorIt<INF> &it) const
	{
		return cur == it.cur;
	}


		template <class INF>
	INF& vectorIt< INF>::operator *()
	{
		return *cur;
	}

	template <class INF>
	INF* vectorIt< INF>::operator ->()
	{
		return cur;
	}

		template <class INF>
	vectorIt< INF>& vectorIt<INF>::operator ++()
	{
		++cur;
		return *this;
	}

	template <class INF>
	vectorIt< INF> vectorIt< INF>::operator ++(int)
	{

		vectorIt<INF> res(*this);
		++cur;
		return res;

	}

	template <class INF>
	vectorIt< INF> vectorIt< INF>::operator +=(int a)
	{

		vectorIt<INF> res(*this);
		cur+=a;
		return res;

	}
}

#endif
