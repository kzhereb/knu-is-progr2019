#include <iostream>
using namespace std;

const int STACK_SIZE = 100;
struct mem {
  int ns, xs, ys;
} st[STACK_SIZE];
int current_index=STACK_SIZE;

int acc(int, int, int);
void adds(int, int, int);
void reads(int& , int& , int&);
int accrec(int, int, int);
int smacc(int, int);

int main(){
	int n, x, y;
	cout << "Function Ackermann n= x= y=" << endl;
	cin >> n >> x >> y; cout << endl;
	cout << "Function value (recursive) = " << accrec(n, x, y) << endl;
	cout << "Function value (stack)     = " << acc(n, x, y) << endl;
	//system("pause");
  return 0;
}
//--------------------------------
//рекурсивна функція Аккермана
int accrec(int n, int x, int y){
  return (n&&y ?
     accrec(n-1, accrec(n, x, y-1), x) :
     smacc(n, x));
}

bool stack_empty() {
	return current_index >= STACK_SIZE;
}

//--------------------------------
//нерекурсивна функція Аккермана
int acc(int ni, int xi, int yi) {
  int t, n, x, y;
  adds(ni, xi, yi);
  do {

  	reads(n,x,y);
  	if (n&&y) adds(n, x, y-1);
  	else {
  		  t = smacc(n, x);
  		  if (++current_index < STACK_SIZE){
  		  	  reads(n,x,y); current_index++;
  		  	  adds(n-1, t, x);
  		  	}
  		}
	} while (!stack_empty());
  return t;
}



//--------------------------------
//функція Аккермана при n=0|y=0
int smacc(int n, int x){
  switch (n) {
    case 0: return x+1;
    case 1: return x;
    case 2: return 0;
    case 3: return 1;
    default: return 2;}
}

//--------------------------------
//додавання в стек st нової трійки
void adds(int ni, int xi, int yi) {
  if (current_index--) {
  	  st[current_index].ns = ni; st[current_index].xs = xi; st[current_index].ys = yi;
  	}
  else cout << "Stack full" << endl;
}
//--------------------------------
//читання з стека st трійки
void reads(int& n, int& x, int& y) {
  n = st[current_index].ns; x = st[current_index].xs; y = st[current_index].ys;
}



