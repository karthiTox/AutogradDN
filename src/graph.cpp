#include "dn.h"


void dn::graph::traversal(dn::Vertex& node) {
	std::cout << "[tensor]=====================" << std::endl;
	(*node.tensor).print();
	std::cout << "[grad]=====================" << std::endl;
	(*node.grad).print();

	int size = node.parents.size();
	for (int i = 0; i < size; i++) {
		traversal(*node.parents[i]);
	}
}


void dn::graph::backpass(dn::Vertex& node) {
	node.back();

	int size = node.parents.size();
	for (int i = 0; i < size; i++) {
		backpass(*node.parents[i]);
	}
}


void dn::graph::update_loss(dn::Vertex& node, double rate) {
	dn::tensor_ops::applyfn(*node.grad, [&](double r) {return r * rate; }, *node.grad);

	dn::tensor_ops::sub(
		*node.tensor,
		*node.grad,
		*node.tensor
	);

	int size = node.parents.size();
	for (int i = 0; i < size; i++) {
		update_loss(*node.parents[i], rate);
	}
}


void dn::graph::grad_zero(dn::Vertex& node) {
	size_t s = node.grad->data.size();

	for (size_t i = 0; i < s; i++)
	{
		node.grad->data[i] = 0;
	}
	
	int size = node.parents.size();
	for (int i = 0; i < size; i++) {
		grad_zero(*node.parents[i]);
	}
}


void dn::graph::detach(dn::Vertex* node) {
	int size = node->parents.size();
	for (int i = 0; i < size; i++) {
		detach(node->parents[i]);
	}

	node->parents.clear();
}