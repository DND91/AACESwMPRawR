#ifndef RAWR_HPP
#define RAWR_HPP
#include<functional>
#include<boost/tr1/functional.hpp>
#include<iostream>

namespace RawR{
  class Component;
  class Node;
  class Call;
/*class Packet;
  class Call;
  class Node;
  class RawR;*/
  
  
  typedef std::function<Component*()> Comp_Con;
  typedef unsigned long int CallID;
  typedef unsigned long int NodeID;
  typedef unsigned long int ComponentID;

  class Packet{
  public:
	virtual ~Packet() {}
    virtual void* getLoad() = 0;
    virtual void setLoad(void*) = 0;
    virtual Node* getSender() = 0;
    virtual bool isHandled() = 0;
    virtual void handled() = 0;
  };

  typedef std::function<void(Packet*)> Function_Call;

  class RawR{
	public:
	virtual ~RawR() {}
    virtual NodeID addNode() = 0;
    virtual void removeNode(NodeID) = 0;
    virtual ComponentID addComponent(NodeID, std::string) = 0;
    virtual Component* removeComponent(NodeID, ComponentID) = 0;
    virtual void call(std::string, Packet*) = 0;
	
    virtual void defineConstructor(std::string, Comp_Con) = 0;
	virtual Component* getComponent(std::string) = 0;
	
    virtual CallID addCall(std::string, Call*) = 0;
    virtual void removeCall(CallID) = 0;
	
	template<class T>
    void defineConstructor(std::string);
  };
  
  template<class T>
    void RawR::defineConstructor(std::string con)
    {
        defineConstructor(con, [](){ return new T(); });
    }

  class Node{
	public:
	virtual ~Node() {}
    virtual CallID addCall(std::string, Call*) = 0;
    virtual void removeCall(CallID) = 0;
    virtual ComponentID addComponent(std::string) = 0;
    virtual Component* removeComponent(ComponentID) = 0;

    template<class T>
    inline CallID addCall(std::string, void (T::*f)(Packet*)) const;
  };

  template<class T>
  CallID Node::addCall(std::string call, void (T::*f)(Packet*)) const {
    return addCall(call, std::tr1::bind(f, (T*)(this), std::tr1::placeholders::_1));
  }

  class Component{
  public:
	virtual ~Component() {}
    virtual void init(RawR*,Node*) = 0;
    virtual void remove(RawR*, Node*) = 0;
	
	virtual bool shallRemove() = 0;
	
	template<class T>
        inline CallID addCall(RawR*,std::string, void (T::*f)(Packet*)) const;
	template<class T>
        inline CallID addCall(Node*,std::string, void (T::*f)(Packet*)) const;
  };

  template<class T>
    CallID Component::addCall(RawR* rawr,std::string call, void (T::*f)(Packet*)) const {
        return rawr->addCall(call, std::tr1::bind(f, (T*)(this), std::tr1::placeholders::_1));
    }
	
  template<class T>
    CallID Component::addCall(Node* node,std::string call, void (T::*f)(Packet*)) const {
        return node->addCall(call, std::tr1::bind(f, (T*)(this), std::tr1::placeholders::_1));
    }

  class Call{
  public:
	virtual ~Call() {}
	virtual Component* getParent() = 0;
    virtual void call(Packet*) = 0;
  };
  
}

#endif
