//скал¤рний добуток вектор≥в
#include <iostream>
#include <random>

#include <ctime>

using namespace std;

const int MAX_SIZE=10000, MAX_CAPACITY=1800;

int generate_random(){
    static std::random_device rd;  //Will be used to obtain a seed for the random number engine
    static std::seed_seq seed { rd(), static_cast<unsigned int>(time(nullptr))}; // in case random_device is not implemented, fallback to time(0)
    static std::mt19937_64 gen(seed); //Standard mersenne_twister_engine seeded with rd()

    static std::uniform_real_distribution<> real_dis;
    static std::uniform_int_distribution<> dis(-100, 100);

    if (real_dis(gen)<=0.92) {return 0;}

    return dis(gen);

}


int main() {

//  for (int i=0;i<100;i++) {
//	  cout<<generate_random()<<" ";
//  }
//  cout<<endl;
//  return 0;

  int i, curr_val, sum;
  struct {int nm, val;} sparse_array[MAX_CAPACITY], *p;
  p = sparse_array;
  //cout << "sparse_array : " << endl;
  for (i=0; i<MAX_SIZE; i++) {
  	  curr_val = generate_random();
  	  if (curr_val == 0) {continue;}
  	  p->val = curr_val;
  	  p->nm = i;
  	  p++;
  	}
  p->nm = MAX_SIZE; sum = 0; p = sparse_array;
  //cout << "N : " << endl;
  for (i=0; i<MAX_SIZE; i++) {
	curr_val = generate_random();
  	if (i == p->nm) sum += (p++)->val * curr_val;
  }
  cout << "PRODUCT = " << sum << endl;
  //system("pause");
  return 0;
}




