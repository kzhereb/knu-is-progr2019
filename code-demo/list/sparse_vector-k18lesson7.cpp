//скал¤рний добуток вектор≥в
#include <iostream>
#include <random>

#include <ctime>

using namespace std;

namespace k18lesson7 {

struct Node {int index, val;};

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

void print_sparse_array(Node* array) {
	for (int i=0; i<MAX_CAPACITY;i++) {
		cout<<array[i].index<<": "<<array[i].val<<endl;
		if (array[i].index>=MAX_SIZE) {
			cout<<"Total elements:"<<i<<endl;
			break;}
	}
}


int main_k18lesson7() {

//  for (int i=0;i<100;i++) {
//	  cout<<generate_random()<<" ";
//  }
//  cout<<endl;
//  return 0;

  int i, curr_val, sum;
  Node sparse_array[MAX_CAPACITY], *p;
  int curr_index = 0;
  //cout << "sparse_array : " << endl;
  for (i=0; i<MAX_SIZE; i++) {
  	  curr_val = generate_random();
  	  if (curr_val == 0) {continue;}
  	  p = &(sparse_array[curr_index]);
	  p->val = curr_val;
	  p->index = i;
	  curr_index++;
  	}
  p->index = MAX_SIZE;
  print_sparse_array(sparse_array);

  sum = 0; //p = sparse_array;
  curr_index = 0;
  //cout << "N : " << endl;
  for (i=0; i<MAX_SIZE; i++) {
	curr_val = generate_random();
	p = &(sparse_array[curr_index]);
  	if (i == p->index) {
  		sum += p->val * curr_val;
  		curr_index++;
  		//p++;
  	}
  }
  cout << "PRODUCT = " << sum << endl;
  //system("pause");
  return 0;
}
}



