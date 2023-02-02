class Stacks{

	final private int MAX = 10;
	private int TOP = -1;
	private int[] stk = new int[MAX];

	Stacks(){
		for(int i = 0; i < MAX;i++){
			stk[i] = -99;
		}
	}
	boolean empty(){
		if(TOP == -1)
			return true;
		else
			return false;
	}
	boolean full(){
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
				System.out.println(stk[i]);;
			}
			System.out.println("\n");
		}
}
public class stack{
	public static void main(String[] args) {
		Stacks stck = new Stacks();
		stck.display();
		stck.push(19);
		stck.push(16);
		stck.display();
		stck.pop();
		stck.display();
	}
}
