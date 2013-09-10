#include"StandardRawR.hpp"

using namespace RawR;


/** STANDARD PACKET **/

StandardPacket::StandardPacket(Node* node) : sender(node), load(0), done(false) { }
StandardPacket::StandardPacket(Node* node, void* l) : sender(node), load(l), done(false) { }

void* StandardPacket::getLoad(){ return load; }

void StandardPacket::setLoad(void* v) { load = v; }

Node* StandardPacket::getSender() { return sender; }

bool StandardPacket::isHandled() { return done; }

void StandardPacket::handled() { done = true; }

/** STANDARD RAWR **/

StandardRawR::StandardRawR() {
	callID = 0;
	nodeID = 0;
}

NodeID StandardRawR::addNode() { 
	int id = nodeID++;
	nodes[id] = new StandardNode(this);
	return id;
}

void StandardRawR::removeNode(NodeID id) {
	Node* node = nodes[id];
	nodes.erase(id);
	delete node;
}

ComponentID StandardRawR::addComponent(NodeID id, std::string a) { 
	return nodes[id]->addComponent(a);
}

Component* StandardRawR::removeComponent(NodeID idN, ComponentID idC) { 
	return nodes[idN]->removeComponent(idC);
}

void StandardRawR::call(std::string a, Packet* p){
	if(public_calls.size() == 0)
		return;

	for(auto ite = public_calls[a].begin(); ite != public_calls[a].end(); ){
		(*ite).second->call(p);
		
		

		if(p->isHandled())
			return;
		ite++;
	}
}

void StandardRawR::defineConstructor(std::string a, Comp_Con c) {
	constructors[a] = c;
}

Component* StandardRawR::getComponent(std::string a) {
	return constructors[a]();
}

CallID StandardRawR::addCall(std::string a, Call* ca) {
	int id = callID++;
	idToCall[id] = a;
	public_calls[a][id] = new StandardCall(ca);
	return id;
}

void StandardRawR::removeCall(CallID id) {
	Call* c = public_calls[idToCall[id]][id];
	public_calls[idToCall[id]].erase(id);
	idToCall.erase(id);
	delete c;
}

/** STANDARD NODE **/

StandardNode::StandardNode(RawR* r) : rawr(r) {
	callID = 0;
	componentID = 0;
}

CallID StandardNode::addCall(std::string address, Function_Call ca) { 
	int id = callID++;
	idToCall[id] = address;
	callToId[address] = id;
	calls[id]= new StandardCall(ca);
	return id;
 }

void StandardNode::removeCall(CallID id) {
	callToId.erase(idToCall[id]);
	idToCall.erase(id);
	Call* c = calls[id];
	calls.erase(id);
	delete c;
}

ComponentID StandardNode::addComponent(std::string n) { 
	int id = componentID++;
	components[id] = rawr->getComponent(n);
	if(components[id] != 0)
		components[id]->init(rawr, id,this);
	return 0; 
}
Component* StandardNode::removeComponent(ComponentID id) { 
	Component* comp = components[id];
	components.erase(id);
	comp->remove(rawr,this);
	return comp; 
}

/** STANDARD COMPONET **/

StandardComponent::StandardComponent() {
	
}

void StandardComponent::init(RawR* rawr,ComponentID id, Node* node) {
	parent = node;
	myID = id;
	testID = addCall(rawr, "Test.Hello", &StandardComponent::test);
}

void StandardComponent::remove(RawR* rawr, Node* node) {
	rawr->removeCall(testID);
}

bool shallRemove(){
	return true;
}

void StandardComponent::test(Packet* packet){
	std::cout << "HELLO ACE!\n" << std::endl;
	packet->handled();
}

/** STANDARD CALL **/

StandardCall::StandardCall(Component* p,Function_Call c) : parent(p), calling(c) {}

void StandardCall::call(Packet* p) {
	calling(p);
}

Component* StandardCall::getParent(){
	return parent;
}






