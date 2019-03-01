#include <iostream>
#include <algorithm>
#include <cstdlib>
//using namespace std;
using std::cout;
using std::endl;

const int k = 10;
int arr[k];

void quick(int *, int *);
void swap(int *, int *);
void gen(int a[], int);
void aprint(int a[], int);
void quicksort_array(int array[], int low, int hi);

int main() {
	gen(arr, k);  //заповнення масиву псевдовипадковими числами
	aprint(arr, k); //відображення масиву до сортування
	quick(&arr[0], &arr[k - 1]);  //сортування
	cout << "Sorted ";
	aprint(arr, k); //відображення масиву після сортування
	quick(&arr[0], &arr[k - 1]);  //сортування
	cout << "Sorted Again ";
	aprint(arr, k); //відображення масиву після сортування

//	gen(arr, k);
//	aprint(arr, k);
//	quicksort_array(arr, 0, k-1);  //сортування
//	cout << "Sorted without pointers ";
//	aprint(arr, k); //відображення масиву після сортування
	//system("pause");
	return 0;
}

//-------------------
//швидке сортування елементів *low, ..., *hi
void quick(int *low, int *hi) {
	int pivot, *left, *right;

	if (hi-low<=1) {
		if (*low > *hi  ) {
			swap(hi, low);
		}
		return;
	}

	if (hi - low > 1) {
		left = low + 1;
		right = hi;
		pivot = *low;
		while (left < right) {
			if (*left <= pivot)
				left++;
			else {
				if (*right <= pivot) {
					swap(left, right);
				}
				right--;
			}
		}

		// pivot <piv <piv ... left=right >piv >piv ...
		// case1: *left<pivot
		// left < < < pivot > > >
		// case2: *left>pivot
		//< < < pivot left=right > > >
		if (*left > pivot)
			left--;
		swap(left, low);

		quick(low, left - 1);
		quick(left + 1, hi);
	}
}

void quicksort_array(int array[], int low, int hi) {
	int pivot, left, right;

	if (hi-low<=1) {
		if (array[low] > array[hi]  ) {
			std::swap(array[hi], array[low]);
		}
		return;
	}

	if (hi - low > 1) {
		left = low + 1;
		right = hi;
		pivot = array[low];
		while (left < right) {
			if (array[left] <= pivot)
				left++;
			else {
				if (array[right] <= pivot) {
					std::swap(array[left], array[right]);
				}
				right--;
			}
		}

		// pivot <piv <piv ... left=right >piv >piv ...
		// case1: *left<pivot
		// left < < < pivot > > >
		// case2: *left>pivot
		//< < < pivot left=right > > >
		if (array[left] > pivot)
			left--;
		std::swap(array[left], array[low]);

		quicksort_array(array, low, left - 1);
		quicksort_array(array, left + 1, hi);
	}
}
//-------------------
//обмін значень *p та *q
void swap(int *p, int *q) {
	int c;
	c = *q;
	*q = *p;
	*p = c;
}
//-------------------
//заповнення масиву псевдовипадковими числами
void gen(int a[], int n) {
	int seed = 16;
	srand(seed);
	for (int i = 0; i < n; i++)
		a[i] = rand();
}
//-------------------
//відображення масиву
void aprint(int a[], int n) {
	cout << "Array: " << endl;
	for (int i = 0; i < n; i++)
		cout << a[i] << ' ';
	cout << endl;
}
