#include <iostream>

#define MAX 10

using namespace std;

class stack{
	private:
		int TOP = -1;
		int stk[MAX];
	public:
		stack(){
			for(int i = 0;i < MAX; i++){
				stk[i] = -99;
			}
		}
		bool empty(){
			if(TOP == -1)
				return true;
			else
				return false;
		}
		bool full(){
			if(TOP == MAX)
				return true;
			else
				return false;
		}
		void push(int n){
			if(full())
				return;
			else{
				TOP++;
				stk[TOP] = n;
			}
		}
		void pop(){
			if(empty())
				return;
			else{
				stk[TOP] = -99;
				TOP--;
			}
		}
		void display(){
			for(int i = 0; i < MAX; i++ ){
				cout << stk[i] << " ";
			}
			cout<<"/n";
		}
};

int main(){
	stack st;
	st.push(14);
	st.push(15);
	st.display();
	st.pop();
	st.display();
	return 0;
}
