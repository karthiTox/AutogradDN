#include "dn.h"

dn::Vertex::Vertex(Tensor* a, std::vector<Vertex*> par, std::function<void()> b)
	: tensor(a), parents(par), back(b) {
	grad = new Tensor(a->data.size(), 0, a->shape);	
};

dn::Vertex::Vertex(Tensor* a): tensor(a){
	grad = new Tensor(a->data.size(), 0, a->shape);	

	parents = {};

	back = []() {};

}

void dn::Vertex::set_del(bool y){
	del_while_detach = y;
}

dn::Vertex::~Vertex() {
	
};

