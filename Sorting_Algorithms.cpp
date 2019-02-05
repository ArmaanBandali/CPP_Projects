//This code implements different sortiing algorithms and quantifies run-times 
//by counting the number of comparisons done


#include <iostream>
#include <vector>
#include <algorithm>
#include "cmpt_error.h"
#include "Priority_queue.h"
#include <numeric>

using namespace std;

class heap : public Priority_queue {
	public:
		virtual ~heap() {

		}

		heap(vector<int>& t) {
			num_comparisons = 0;
			int size = t.size();
			int k = 0;
			int temp = 0;
			for (int j = 0; j < size; j++) {
				bool even = 0;
				min_heap.push_back(t[j]);
				k = min_heap.size()-1;
				if (j == 0) {
					continue;
				}
				if (k % 2 == 0) {
					even = true;
				}
				while (k != 0) {
					if (even){
						num_comparisons++;
						if (min_heap[k] < min_heap[k / 2 - 1]) {
							temp = min_heap[k];
							min_heap[k] = min_heap[k / 2 - 1];
							min_heap[k / 2 - 1] = temp;
							k = k / 2 - 1;
						}
						else {
							break;
						}
					}
					else {
						num_comparisons++;
						if (min_heap[k] < min_heap[k / 2]) {
							temp = min_heap[k];
							min_heap[k] = min_heap[k / 2];
							min_heap[k / 2] = temp;
							k = k / 2;
						}
						else {
							break;
						}
					}
				}
			}
		}

		// Pre-condition:
		//    none
		// Post-condition:
		//    Returns true if there are 0 items in this priority queue.
		virtual bool empty() const {
			return min_heap.empty();
		}

		// Pre-condition:
		//    none
		// Post-condition:
		//    Puts x into this priority queue. If x is already in the priority
		//    queue, then nothing is added (i.e. duplicates are not allowed).
		virtual void insert(int x) {}

		// Pre-condition:
		//    !empty()
		// Post-condition:
		//    Removes and returns the smallest element from this priority queue.
		virtual int pop_min() {
			int i = 0;
			int temp = 0;
			bool even = 0;
			int min = min_heap[0];
			if (min_heap.size() == 1) {
				temp = min_heap[0];
				min_heap.erase(min_heap.begin());
				return temp;
			}
			min_heap[0] = min_heap[min_heap.size()-1];
			min_heap.pop_back();
			while (i*2+2<min_heap.size()) {
				if (min_heap[2 * i + 1] > min_heap[2 * i + 2]) {
					even = true;
				}
				if (even) {
					if (min_heap[i] > min_heap[2 * i + 2]) {
						temp = min_heap[i];
						min_heap[i] = min_heap[2 * i + 2];
						min_heap[2 * i + 2] = temp;
						i = 2 * i + 2;
					}
					else {
						break;
					}
				}
				else {
					if (min_heap[i] > min_heap[2 * i + 1]) {
						temp = min_heap[i];
						min_heap[i] = min_heap[2 * i + 1];
						min_heap[2 * i + 1] = temp;
						i = 2 * i + 1;
					}
					else {
						break;
					}
				}
			}
			if (i * 2 + 1 < min_heap.size()) {
				if (min_heap[i] > min_heap[2 * i + 1]) {
					temp = min_heap[i];
					min_heap[i] = min_heap[2 * i + 1];
					min_heap[2 * i + 1] = temp;
				}
			}
			return min;
		}

		int number_comparisons() {
			return num_comparisons;
		}

	private:
		vector<int> min_heap;
		int num_comparisons;
};

class unsortedV : public Priority_queue {
	public:
		virtual ~unsortedV() {

		}

		unsortedV(vector<int>& t){
			for (int i = 0; i < t.size(); i++) {
				unsorted.push_back(t[i]);
			}
			num_comparisons = 0;
		}

		// Pre-condition:
		//    none
		// Post-condition:
		//    Returns true if there are 0 items in this priority queue.
		virtual bool empty() const {
			return unsorted.empty();
		}

		// Pre-condition:
		//    none
		// Post-condition:
		//    Puts x into this priority queue. If x is already in the priority
		//    queue, then nothing is added (i.e. duplicates are not allowed).
		virtual void insert(int x) {}

		// Pre-condition:
		//    !empty()
		// Post-condition:
		//    Removes and returns the smallest element from this priority queue.
		virtual int pop_min() {
			int min = 0;
			int temp = 0;
			min = unsorted[0];
			for (int i = 1; i < unsorted.size(); i++) {
				if (min > unsorted[i]) {
					temp = i;
					min = unsorted[i];
				}
				num_comparisons++;
			}
			unsorted.erase(unsorted.begin()+temp);
			return min;
		}

		int number_comparisons() {
			return num_comparisons;
		}

	private:
		vector<int> unsorted;
		int num_comparisons;
};

class sortedV : public Priority_queue {
public:
	virtual ~sortedV() {

	}

	sortedV(vector<int>& t) {
		num_comparisons = 0;
		int size = t.size();
		int temp = 0;
		int temp2 = 0;
		int min = 0;
		for (int i = 0; i < size; i++) {
			temp = t[0];
			t.erase(t.begin());
			sorted.insert(sorted.begin(), temp);
			for (int j = 0; j < sorted.size(); j++) {
				if (j != sorted.size()-1) {
					num_comparisons++;
					if (sorted[j] > sorted[j + 1]) {
						temp2 = sorted[j];
						sorted[j] = sorted[j + 1];
						sorted[j + 1] = temp2;
					}
					else {
						break;
					}
				}
			}
		}
	}

	// Pre-condition:
	//    none
	// Post-condition:
	//    Returns true if there are 0 items in this priority queue.
	virtual bool empty() const {
		return sorted.empty();
	}

	// Pre-condition:
	//    none
	// Post-condition:
	//    Puts x into this priority queue. If x is already in the priority
	//    queue, then nothing is added (i.e. duplicates are not allowed).
	virtual void insert(int x) {}

	// Pre-condition:
	//    !empty()
	// Post-condition:
	//    Removes and returns the smallest element from this priority queue.
	virtual int pop_min() {
		int temp = sorted[0];
		sorted.erase(sorted.begin());
		return temp;
	}

	int number_comparisons() {
		return num_comparisons;
	}

private:
	vector<int> sorted;
	int num_comparisons;
};

// Pre-condition:
//    none
// Post-condition:
//    v is re-arranged into ascending sorted order
void selection_sort(vector<int>& v) {
	int temp = v.size();
	unsortedV pri_Queue(v);
	v.clear();
	for (int i = 0; i < temp; i++) {
		v.push_back(pri_Queue.pop_min());
	}
	cout << endl << "For the random vector of size " << temp << " the number of comparisons for selection sort is " << pri_Queue.number_comparisons();
}

// Pre-condition:
//    none
// Post-condition:
//    v is re-arranged into ascending sorted order
void insertion_sort(vector<int>& v) {
	int temp = v.size();
	sortedV pri_Queue(v);
	v.clear();
	for (int i = 0; i < temp; i++) {
		v.insert(v.begin(),pri_Queue.pop_min());
	}
	cout << endl<< "For the random vector of size " << temp << " the number of comparisons for insertion sort is " << pri_Queue.number_comparisons();
}

// Pre-condition:
//    none
// Post-condition:
//    v is re-arranged into ascending sorted order
void heap_sort(vector<int>& v) {
	int temp = v.size();
	heap pri_Queue(v);
	v.clear();
	for (int i = 0; i < temp; i++) {
		v.insert(v.begin(), pri_Queue.pop_min());
	}
	cout << endl << "For the random vector of size " << temp << " the number of comparisons for heap sort is " << pri_Queue.number_comparisons();
}

void clib_sort(vector<int>& v) {
	int temp = v.size();
	int num_comparisons = 0;
	sort(v.begin(), v.end(), [&num_comparisons](int i, int j) {
		num_comparisons++;
		return (i < j); });
	cout << endl << "For the random vector of size " << temp << " the number of comparisons done by the standard library sort is " << num_comparisons;
}


int main() {

	vector<int> test{0};
	for (int i = 5000; i <= 100000; i=i + 5000) {
		vector<int> temp(i);
		iota(temp.begin(), temp.end(), 1);
		random_shuffle(temp.begin(), temp.end());
		test = temp;
		selection_sort(temp);
		temp = test;
		insertion_sort(temp);
		temp = test;
		//heap_sort(temp);
		//temp = test;
		clib_sort(temp);
	}
	




	return 0;
}