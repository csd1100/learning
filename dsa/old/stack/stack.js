var TOP = -1;
var MAX = 10;
var stack = [];
function empty(){
	if(TOP == -1)
	 	return true;
	else
		return false;
}
function full(){
	if(TOP == MAX)
	 	return true;
	else
		return false;
}
function push(n){
	if(full()){
		return;
	}else{
		TOP++;
		stack[TOP] = n;
	}
}
function pop(){
	if(empty()){
		return;
	}else{
		stack[TOP] = -99;
		TOP--;
	}
}
function stackInit(){
	for(let i = 0;i < MAX; i++){
		stack[i]=-99;
	}
}
function display(){
	for(let i = 0;i < MAX; i++){
		console.log(stack[i]+" ")
	}
	console.log("\n");
}
stackInit();
display();
push(15);
push(18);
push(20);
display();
pop();
display();
pop();
display();
