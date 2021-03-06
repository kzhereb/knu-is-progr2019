#include <iostream>
#include <cstdlib>
#define MIN(x, y) ((y)<(x)?(y):(x))
#define MAX(x, y) ((y)<(x)?(x):(y))
using namespace std;


namespace k19lesson8_1 {
const int k = 10;
int arr[k];

void gen(int a[], int);
void aprint(int a[], int);
void smerge(int a[], int);
void srecmg(int a[], int);
void merge(int w[], int, int);

int main() {
	gen(arr, k);  //заповнення масиву псевдовипадковими числами
	aprint(arr, k); //відображення масиву до сортування

	//  smerge(arr, k);  //сортування нерекурсивне
	srecmg(arr, k);  //сортування рекурсивне

	aprint(arr, k); //відображення масиву після сортування
	//system("pause");
	return 0;
}
//-------------------
//нерекурсивне сортування злиттям
void smerge(int a[], int n) {
	int *p, *max_index;
	max_index = a + n;
	for (int len = 1; len < n; len *= 2)
		for (p = a; p + len < max_index; p += 2 * len)
			merge(p, len, MIN(len * 2, max_index - p));
}
//-------------------
//рекурсивне сортування злиттям
void srecmg(int a[], int n) {
	int i;
	if (n > 1) {
		i = n / 2;
		srecmg(a, i);
		srecmg(a + i, n - i);
		merge(a, i, n);
	}
}
//-------------------
//злиття двох впорядкованих підмасивів 0,...,l1-1  та  l1,..., l2

//w = sorted1, sorted2
void merge(int w[], int len1, int len2) {
	int i, *a, *pa, *pb;
	a = new int[len2 + 2];  //створення вспоміжного масиву
	pa = a;
	pb = a + len1 + 1;
	//копіювання у вспоміжний масив
	for (i = 0; i < len1; i++)
		*pa++ = w[i];
	for (i = len1; i < len2; i++)
		*pb++ = w[i];
	//a = sorted1, 0, sorted2, 0
	*pa = *pb = MAX(w[len1-1], w[len2-1]) + 1;
	//a = sorted1, MAX, sorted2, MAX
	pa = a;
	pb = a + len1 + 1;
	for (i = 0; i < len2; i++)
		w[i] = (*pa < *pb ? *pa++ : *pb++);
	delete[] a;
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
}
