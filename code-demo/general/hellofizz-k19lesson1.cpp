#include <iostream>
//using namespace std;




int main() {
	using std::cout;
	using std::endl;
	using std::cin;
//	//cout<<"Hello world\n";
//	cout<<"Hello ";
//	cout.flush();
//	cout<<"world"<<endl;
//	while(true) {  }

	int input_number;
	cout<<"Enter number:"<<endl;
	cin>>input_number;
	if (!(input_number % 3))  { cout<<"Fizz"; }
	if (input_number % 5 == 0)
		cout<<"Buzz";
	cout<<endl;
    return 0;
}
