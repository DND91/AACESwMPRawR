#ifndef STANDARD_RAWR_HPP
#define STANDARD_RAWR_HPP
#include "RawR.hpp"
#include<iostream>
#include<list>
#include<map>

namespace RawR{
  class StandardPacket : public Packet{
    Node* sender;
    void* load;
    bool done;
  public:
    StandardPacket(Node*);
    StandardPacket(Node*,void*);
    virtual void* getLoad();
    virtual void setLoad(void*);
    virtual Node* getSender();
    virtual bool isHandled();
    virtual void handled();
  };

  class StandardRawR : public RawR{
	//Nickname for a constructor to the acctual constructor
	std::map<std::string, Comp_Con> constructors;
	
	//callID to group of calls it belongs to.
	std::map<int, std::string> idToCall;
	
	//All calls that belongs to a Address sorted by CallID
	std::map<std::string, std::map<int,Call*>> public_calls;
	
	//NodeID to the acctual node
	std::map<int, Node*> nodes;
	
	//Hold the current max ID
	NodeID nodeID;
	CallID callID;
  public:
    StandardRawR();
    virtual NodeID addNode();
    virtual void removeNode(NodeID);
    virtual ComponentID addComponent(NodeID, std::string);
    virtual Component* removeComponent(NodeID, ComponentID);
    virtual void call(std::string, Packet*);
	
    virtual void defineConstructor(std::string, Comp_Con);
	virtual Component* getComponent(std::string);
	
    virtual CallID addCall(std::string, Function_Call);
    virtual void removeCall(CallID);
  };
  
  

  class StandardNode : public Node{
  private:
	RawR* rawr;
	//What Address does the id of call have
	std::map<int, std::string> idToCall;
	//What id of call does Address have
	std::map<std::string, int> callToId;
	//Id to call
	std::map<int, Call*> calls;

	//ComponentID to Accutal Component
	std::map<int, Component*> components;

	//IDs
	CallID callID;
	ComponentID componentID;
  public:
    StandardNode(RawR*);
    virtual CallID addCall(std::string, Function_Call);
    virtual void removeCall(CallID);
    virtual ComponentID addComponent(std::string);
    virtual Component* removeComponent(ComponentID);
  };

  class StandardComponent : public Component{
	CallID testID;
  public:
    StandardComponent();
    virtual void init(RawR*,ComponentID, Node*);
    virtual void remove(RawR*, Node*);
	virtual bool shallRemove();
	
	
	void test(Packet*);
  };

  class StandardCall : public Call{
  private:
	Function_Call calling;
	Component* parent;
  public:
	StandardCall(Component*,Function_Call);
	virtual void call(Packet*);
	virtual Component* getParent();
  };
}

#endif
