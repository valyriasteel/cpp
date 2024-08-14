#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <deque>
# include <vector>
# include <iostream>

class PmergeMe
{
	private:
		std::vector<int> _vector;
		std::deque<int> _deque;
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &copy);
		PmergeMe& operator=(const PmergeMe &copy);
		~PmergeMe();
		PmergeMe(char **av);
		void sorting();
		void print(std::string str);

		template <typename T>
		void insertSort(T &container, int first, int last)
		{
			int i, j, key;
			for (i = first + 1; i <= last; i++)
			{
				key = container[i];
				j = i - 1;
				while (j >= first && container[j] > key)
				{
					container[j + 1] = container[j];
					j = j - 1;
				}
				container[j + 1] = key;
			}
		}

		template <typename T>
		void merge(T &container, int first, int mid, int last)
		{
			int i, j, k;
			int n1 = mid - first + 1;
			int n2 = last - mid;
			T L(n1), R(n2);
			for (i = 0; i < n1; i++)
				L[i] = container[first + i];
			for (j = 0; j < n2; j++)
				R[j] = container[mid + 1 + j];
			i = 0;
			j = 0;
			k = first;
			while (i < n1 && j < n2)
			{
				if (L[i] <= R[j])
				{
					container[k] = L[i];
					i++;
				}
				else
				{
					container[k] = R[j];
					j++;
				}
				k++;
			}
			while (i < n1)
			{
				container[k] = L[i];
				i++;
				k++;
			}
			while (j < n2)
			{
				container[k] = R[j];
				j++;
				k++;
			}
		}
		
		template <typename T>
		void mergeInsertionSort(T &container, int first, int last)
		{
			if (first < last)
			{
				int mid = (first + last) / 2;
				if (last - first + 1 <= 10)
					insertSort(container, first, last);
				else
				{
					mergeInsertionSort(container, first, mid);
					mergeInsertionSort(container, mid + 1, last);
					merge(container, first, mid, last);
				}
			}
		}

		class InvalidArgument : public std::exception
		{
			public:
				const char* what() const throw()
				{
					return "Error: invalid argument use: ./PmergeMe \"<expression>\" or quotes not";
				}
		};

		class InvalidExpression : public std::exception
		{
			public:
				const char* what() const throw()
				{
					return "Error";
				}
		};
};

#endif