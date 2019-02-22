//скал¤рний добуток вектор≥в
#include <iostream>
#include <random>

#include <ctime>

using namespace std;

const int NN=10000, KK=800;

int generate_random(){
    static std::random_device rd;  //Will be used to obtain a seed for the random number engine
    static std::seed_seq seed { rd(), static_cast<unsigned int>(time(nullptr))}; // in case random_device is not implemented, fallback to time(0)
    static std::mt19937_64 gen(seed); //Standard mersenne_twister_engine seeded with rd()

    static std::uniform_int_distribution<> dis(1, 6);

    return dis(gen);

}


int main() {

  for (int i=0;i<100;i++) {
	  cout<<generate_random()<<" ";
  }
  cout<<endl;
  return 0;

  int i, inp, sum;
  struct {int nm, val;} M[KK], *p;
  p = M;
  cout << "M : " << endl;
  for (i=0; i<NN; i++) {
  	  cin >> inp;
  	  if (p->val = inp) (p++)->nm = i;
  	}
  p->nm = NN; sum = 0; p = M;
  cout << "N : " << endl;
  for (i=0; i<NN; i++) {
    cin >> inp;
  	if (i == p->nm) sum += (p++)->val * inp;
  }
  cout << "SUM = " << sum << endl;
  system("pause");
  return 0;
}




