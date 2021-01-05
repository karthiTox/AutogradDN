#include "utils.h"
#include "dn.h"

dn::Vertex& dn::vertex_ops::add(Vertex& a, Vertex& b, Vertex& res) {
	dn::tensor_ops::add(*a.tensor, *b.tensor, *res.tensor);

	res.parents = { &a, &b };

	res.back = [&]() {
		dn::tensor_ops::add(*res.grad, *a.grad, *a.grad);
		dn::tensor_ops::add(*res.grad, *b.grad, *b.grad);
	};

	return res;
};

dn::Vertex& dn::vertex_ops::sub(dn::Vertex& a, dn::Vertex& b, dn::Vertex& res) {
	dn::tensor_ops::sub(*a.tensor, *b.tensor, *res.tensor);

	res.parents = { &a, &b };

	res.back = [&]() {
		dn::tensor_ops::add(*res.grad, *a.grad, *a.grad);

		dn::Tensor ngrad((*res.grad).data.size(), 0, (*res.grad).shape);
		dn::tensor_ops::applyfn(*res.grad, [](double r) { return r * -1; }, ngrad);
		dn::tensor_ops::add(ngrad, *b.grad, *b.grad);
	};

	return res;
};

dn::Vertex& dn::vertex_ops::multiply(dn::Vertex& a, dn::Vertex& b, dn::Vertex& res) {
	dn::tensor_ops::multiply(*a.tensor, *b.tensor, *res.tensor);

	res.parents = { &a, &b };

	res.back = [&]() {
		dn::Tensor gradb((*a.tensor).data.size(), 0, (*a.tensor).shape);
		dn::tensor_ops::multiply(*res.grad, *a.tensor, gradb);

		dn::Tensor grada((*a.tensor).data.size(), 0, (*a.tensor).shape);
		dn::tensor_ops::multiply(*res.grad, *b.tensor, grada);

		dn::tensor_ops::add(grada, *a.grad, *a.grad);
		dn::tensor_ops::add(gradb, *b.grad, *b.grad);
	};

	return res;
};

dn::Vertex& dn::vertex_ops::applyfn(
	dn::Vertex& a,
	const std::function<double(double)> fn,
	const std::function<double(double)> deltafn,
	dn::Vertex& res
) {
	dn::tensor_ops::applyfn(*a.tensor, fn, *res.tensor);

	res.parents = { &a };

	res.back = [&res, &a, deltafn]() {

		dn::Tensor da(
			(*a.tensor).data.size(), 0, (*a.tensor).shape);
		dn::tensor_ops::applyfn(*a.tensor, deltafn, da);

		dn::Tensor grad((*a.tensor).data.size(), 0, (*a.tensor).shape);
		dn::tensor_ops::multiply(*res.grad, da, grad);

		dn::tensor_ops::add(grad, *a.grad, *a.grad);

	};

	return res;
};

dn::Vertex& dn::vertex_ops::transpose(dn::Vertex& a, std::vector<int>& dimension, dn::Vertex& res) {
	dn::tensor_ops::transpose(*a.tensor, dimension, *res.tensor);
	(*res.grad).shape = res.tensor->shape;

	res.parents = { &a };

	res.back = [&]() {
		dn::Tensor grad((*a.grad).data.size(), 0, (*a.grad).shape);

		dn::tensor_ops::transpose(*res.grad, dimension, grad);
		dn::tensor_ops::add(grad, *a.grad, *a.grad);
	};

	return res;
};

dn::Vertex& dn::vertex_ops::transpose(dn::Vertex& a, dn::Vertex& res) {
	dn::tensor_ops::transpose(*a.tensor, *res.tensor);
	(*res.grad).shape = res.tensor->shape;

	res.parents = { &a };

	res.back = [&]() {
		dn::Tensor grad((*a.grad).data.size(), 0, (*a.grad).shape);

		dn::tensor_ops::transpose(*res.grad, grad);
		dn::tensor_ops::add(grad, *a.grad, *a.grad);
	};

	return res;
};

dn::Vertex& dn::vertex_ops::matmul(dn::Vertex& a, dn::Vertex& b, dn::Vertex& res) {
	dn::tensor_ops::matmul(*a.tensor, *b.tensor, *res.tensor);
	(*res.grad).shape = res.tensor->shape;

	res.parents = { &a, &b };

	res.back = [&]() {
		dn::Tensor at((*a.tensor).data.size(), 0, (*a.tensor).shape);
		dn::Tensor bt((*b.tensor).data.size(), 0, (*b.tensor).shape);
		dn::Tensor grada((*a.grad).data.size(), 0, (*a.grad).shape);
		dn::Tensor gradb((*b.grad).data.size(), 0, (*b.grad).shape);

		dn::tensor_ops::transpose(*a.tensor, at);
		dn::tensor_ops::transpose(*b.tensor, bt);

		dn::tensor_ops::matmul(*res.grad, bt, grada);
		dn::tensor_ops::matmul(at, *res.grad, gradb);

		dn::tensor_ops::add(grada, *a.grad, *a.grad);
		dn::tensor_ops::add(gradb, *b.grad, *b.grad);
	};

	return res;
};