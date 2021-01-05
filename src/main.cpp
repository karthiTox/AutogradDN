#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

#include "dn.h"
#include "utils.h"
#include "memory_usage.h"

#define log(x) std::cout << x << std::endl

// using stack
void test(){

	dn::Tensor w({ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, { 5, 2 });
	dn::Vertex vw(&w);
	
	dn::Tensor b({ 1, 1, 1, 1, 1 }, { 1, 5 });
	dn::Vertex vb(&b);

	for (int i = 0; i < 2; i++) 
	{
		dn::Tensor a({ 1, 1 }, { 1, 2 });
		dn::Vertex va(&a);

		dn::Tensor wtt(w.data.size(), 0, w.shape);
		dn::Vertex wt(&wtt);
		dn::vertex_ops::transpose(vw, wt);

		dn::Tensor matrest(b.data.size(), 0, b.shape);
		dn::Vertex matres(&matrest);
		dn::vertex_ops::matmul(va, wt, matres);

		dn::Tensor addedt(b.data.size(), 0, b.shape);
		dn::Vertex added(&addedt);
		dn::vertex_ops::add(matres, vb, added);

		dn::Tensor rest(b.data.size(), 0, b.shape);
		dn::Vertex result(&rest);
		dn::vertex_ops::applyfn(added, utils::functions::sig, utils::functions::sigPrime, result);

		dn::Tensor opt({ 1, 0, 1, 0, 1 }, { 1, 5 });
		dn::tensor_ops::sub(*result.tensor, opt, *result.grad);

		dn::graph::backpass(result);
		dn::graph::update_loss(result, 0.04);
	}

	{
		dn::Tensor a({ 1, 1 }, { 1, 2 });
		dn::Vertex va(&a);

		dn::Tensor wtt(w.data.size(), 0, w.shape);
		dn::Vertex wt(&wtt);
		dn::vertex_ops::transpose(vw, wt);

		dn::Tensor matrest(b.data.size(), 0, b.shape);
		dn::Vertex matres(&matrest);
		dn::vertex_ops::matmul(va, wt, matres);

		dn::Tensor addedt(b.data.size(), 0, b.shape);
		dn::Vertex added(&addedt);
		dn::vertex_ops::add(matres, vb, added);

		dn::Tensor rest(b.data.size(), 0, b.shape);
		dn::Vertex result(&rest);
		dn::vertex_ops::applyfn(added, utils::functions::sig, utils::functions::sigPrime, result);

		(*result.tensor).print();
	}
}

void graph_backpass(dn::Vertex* start) {
			dn::graph::backpass(*start);
}

void graph_update_loss(dn::Vertex* start, double rate) {
	dn::graph::update_loss(*start, rate);
}


uint32_t graph_detach(dn::Vertex* start) {
	dn::graph::detach(start);
	return memoryUsage.get_usage();
}
			


// using heap
void test2() {
	dn::Tensor* w = new dn::Tensor({ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, { 5, 2 });
	dn::Vertex* vw = new dn::Vertex(w);
	vw->set_del(false);

	dn::Tensor* b = new dn::Tensor({ 1, 1, 1, 1, 1 }, { 1, 5 });
	dn::Vertex* vb = new dn::Vertex(b);
	vb->set_del(false);

	for (int i = 0; i < 1; i++)
	{
		dn::Tensor* a = new dn::Tensor({ 1, 1 }, { 1, 2 });
		dn::Vertex* va = new dn::Vertex(a);

		dn::Vertex* wt = dn::api::transpose(vw);
		dn::Vertex* matmul = dn::api::matmul(va, wt);
		dn::Vertex* added = dn::api::add(matmul, vb);
		dn::Vertex* afb = dn::api::applyfn(added, utils::functions::sig, utils::functions::sigPrime);
	
		dn::Tensor opt({ 1, 0, 1, 0, 1 }, { 1, 5 });
		dn::tensor_ops::sub(*afb->tensor, opt, *afb->grad);		

		graph_backpass(afb);

		log("grad");
		afb->grad->print_shape();
		afb->grad->print_date();
		afb->tensor->print();

		dn::graph::update_loss(*afb, 0.04);
		dn::graph::detach(afb);
	}

	dn::Tensor* a = new dn::Tensor({ 1, 1 }, { 1, 2 });
	dn::Vertex* va = new dn::Vertex(a);

	dn::Vertex* wt = dn::api::transpose(vw);
	dn::Vertex* matmul = dn::api::matmul(va, wt);
	dn::Vertex* added = dn::api::add(matmul, vb);
	dn::Vertex* afb = dn::api::applyfn(added, utils::functions::sig, utils::functions::sigPrime);


	dn::graph::detach(afb);

	delete w;
	delete vw->grad;
	delete vw;
	delete b;
	delete vb->grad;
	delete vb;
}


int main(){
	memoryUsage.print_usage();
	{
		test2();
	}
	memoryUsage.print_usage();
}