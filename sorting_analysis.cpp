#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<random>
#include<functional>
#include<chrono>

template <class iter>
void print_container(iter b, iter e)
{
    if(b <= e){
        while(b != e)
        {
            std::cout << (*b) << " ";
            b++;
        }
        std::cout << std::endl;
    }
}

void bubble_sort(std::vector<int> & v)
{
	for (int i = (int)(v.size()) - 1; i >= 0; i--) {
		for (int j = 1; j <= i; j++) {
			if (v[j-1] > v[j]) {
				std::swap(v[j-1],v[j]);
			}
		}
	}
}

void merge_sort(std::vector<int>::iterator first, std::vector<int>::iterator last)
{
    if (last - first > 1) {
        std::vector<int>::iterator middle = first + (last - first) / 2;
        merge_sort(first, middle);
        merge_sort(middle, last);
        std::inplace_merge(first, middle, last);
    }
}

void insertion_sort(std::vector<int> & v)
{
    for (auto i = v.begin(); i != v.end(); ++i) {
        std::rotate(std::upper_bound(v.begin(), i, *i), i, i+1);
    }
}

void selection_sort(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    for (std::vector<int>::iterator i = begin; i != end; ++i) {
        std::vector<int>::iterator mIter = std::min_element(i, end);
        std::iter_swap(i, mIter);
    }
}

bool check(const std::vector<int> & v)
{
    return is_sorted(v.begin(), v.end());
}

void benchmark()
{
	const int nElem = 1000;
	std::vector<int> v;

	// fill the vectors with random numbers
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dis(0, 999);

    std::vector<int> v1(nElem), v2(nElem), v3(nElem), v4(nElem);
    std::generate(v1.begin(), v1.end(), std::bind(dis, std::ref(mt)));
    std::generate(v2.begin(), v2.end(), std::bind(dis, std::ref(mt)));
    std::generate(v3.begin(), v3.end(), std::bind(dis, std::ref(mt)));
    std::generate(v4.begin(), v4.end(), std::bind(dis, std::ref(mt)));


    // print_container(v1.begin(), v1.end()); print_container(v2.begin(), v2.end()); print_container(v3.begin(), v3.end());

    std::chrono::steady_clock::time_point start1 = std::chrono::steady_clock::now();
    bubble_sort(v1);
    std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
    std::cout << "bubble sort:  " << nElem << " values time taken " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count()
    << " microseconds\n";
    std::cout << ((    (check(v1)) ? ("success") : ("error")  )) << std::endl;

    std::chrono::steady_clock::time_point start2 = std::chrono::steady_clock::now();
    merge_sort(v2.begin(), v2.end());
    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
    std::cout << "merge sort:  " << nElem << " values time taken " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count()
    << " microseconds\n";
    std::cout << ((    (check(v2)) ? ("success") : ("error")  )) << std::endl;

    std::chrono::steady_clock::time_point start3 = std::chrono::steady_clock::now();
    insertion_sort(v3);
    std::chrono::steady_clock::time_point end3 = std::chrono::steady_clock::now();
    std::cout << "insertion sort:  " << nElem << " values time taken " << std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3).count()
    << " microseconds\n";
    std::cout << ((    (check(v3)) ? ("success") : ("error")  )) << std::endl;

    std::chrono::steady_clock::time_point start4 = std::chrono::steady_clock::now();
    selection_sort(v4.begin(), v4.end());
    std::chrono::steady_clock::time_point end4 = std::chrono::steady_clock::now();
    std::cout << "selection sort:  " << nElem << " values time taken " << std::chrono::duration_cast<std::chrono::microseconds>(end4 - start4).count()
    << " microseconds\n";
    std::cout << ((    (check(v4)) ? ("success") : ("error")  )) << std::endl;
}

int main()
{
	benchmark();
	return 0;
}
