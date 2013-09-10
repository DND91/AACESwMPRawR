#include<iostream>
#include"StandardRawR.hpp"

using namespace RawR;

int main(){
	RawR::RawR* rawr = new StandardRawR();
	rawr->defineConstructor<StandardComponent>("Test");
	
	int node = rawr->addNode();
	rawr->addComponent(node, "Test");
	
	rawr->call("Test.Hello", new StandardPacket(0));
	
	//std::cout << "HELLO WORLD\n" << std::endl;
	return 1;
}




