#include "dn.h"

bool check_length(std::vector<int>& a, std::vector<int>& b) {
	if (a.size() != b.size()) return false;

	return true;
}

bool check_shape(std::vector<int>& a, std::vector<int>& b) {
	int size = a.size();
	for (int i = 0; i < size; i++) {
		if (a[i] != b[i]) return false;
	};

	return true;
}

dn::Tensor* dn::api::add(dn::Tensor* a, dn::Tensor* b) {
	dn::Tensor* result = new dn::Tensor(a->data.size(), 0, a->shape);
	dn::tensor_ops::add(*a, *b, *result);
	return result;
}

dn::Vertex* dn::api::add(dn::Vertex* a, dn::Vertex* b) {
	dn::Tensor* rt = new dn::Tensor((*a->tensor).data.size(), 0, (*a->tensor).shape);
	dn::Vertex* result = new dn::Vertex(rt);
	dn::vertex_ops::add(*a, *b, *result);
	return result;
}

dn::Tensor* dn::api::sub(dn::Tensor* a, dn::Tensor* b) {
	dn::Tensor* result = new dn::Tensor(a->data.size(), 0, a->shape);
	dn::tensor_ops::sub(*a, *b, *result);
	return result;
}

dn::Vertex* dn::api::sub(dn::Vertex* a, dn::Vertex* b) {
	dn::Tensor* rt = new dn::Tensor((*a->tensor).data.size(), 0, (*a->tensor).shape);
	dn::Vertex* result = new dn::Vertex(rt);
	dn::vertex_ops::sub(*a, *b, *result);
	return result;
}

dn::Tensor* dn::api::multiply(dn::Tensor* a, dn::Tensor* b) {
	dn::Tensor* result = new dn::Tensor(a->data.size(), 0, a->shape);
	dn::tensor_ops::multiply(*a, *b, *result);
	return result;
}

dn::Vertex* dn::api::multiply(dn::Vertex* a, dn::Vertex* b) {
	dn::Tensor* rt = new dn::Tensor((*a->tensor).data.size(), 0, (*a->tensor).shape);
	dn::Vertex* result = new dn::Vertex(rt);
	dn::vertex_ops::multiply(*a, *b, *result);
	return result;
}

dn::Tensor* dn::api::applyfn(
	dn::Tensor* a,
	const std::function<double(double)> fn,
	const std::function<double(double)> deltafn
) {
	dn::Tensor* result = new dn::Tensor(a->data.size(), 0, a->shape);
	dn::tensor_ops::applyfn(*a, fn, *result);
	return result;
}


dn::Vertex* dn::api::applyfn(
	dn::Vertex* a,
	const std::function<double(double)> fn,
	const std::function<double(double)> deltafn
) {
	dn::Tensor* rt = new dn::Tensor((*a->tensor).data.size(), 0, (*a->tensor).shape);
	dn::Vertex* result = new dn::Vertex(rt);
	dn::vertex_ops::applyfn(*a, fn, deltafn, *result);
	return result;
}


dn::Tensor* dn::api::transpose(dn::Tensor* a, std::vector<int> dimension) {
	dn::Tensor* result = new dn::Tensor(a->data.size(), 0, a->shape);
	dn::tensor_ops::transpose(*a, dimension, *result);
	return result;
}


dn::Tensor* dn::api::transpose(dn::Tensor* a) {
	dn::Tensor* result = new dn::Tensor(a->data.size(), 0, a->shape);
	dn::tensor_ops::transpose(*a, *result);
	return result;
}


dn::Vertex* dn::api::transpose(dn::Vertex* a, std::vector<int> dimension) {
	dn::Tensor* rt = new dn::Tensor((*a->tensor).data.size(), 0, (*a->tensor).shape);
	dn::Vertex* result = new dn::Vertex(rt);
	dn::vertex_ops::transpose(*a, dimension, *result);
	return result;
}


dn::Vertex* dn::api::transpose(dn::Vertex* a) {
	dn::Tensor* rt = new dn::Tensor((*a->tensor).data.size(), 0, (*a->tensor).shape);
	dn::Vertex* result = new dn::Vertex(rt);
	dn::vertex_ops::transpose(*a, *result);
	return result;
}

dn::Tensor* dn::api::matmul(dn::Tensor* a, dn::Tensor* b) {
	int size = 1;
	size_t tsize = a->shape.size();
	for (int i = 0; i < tsize - 1; i++) {
		size *= a->shape[i];
	}
	size *= b->shape[tsize - 1];

	dn::Tensor* result = new dn::Tensor(size, 0, a->shape);
	dn::tensor_ops::matmul(*a, *b, *result);
	return result;
}

dn::Vertex* dn::api::matmul(dn::Vertex* a, dn::Vertex* b) {
	int size = 1;
	size_t tsize = (*a->tensor).shape.size();
	for (int i = 0; i < tsize - 1; i++) {
		size *= (*a->tensor).shape[i];
	}
	size *= (*b->tensor).shape[tsize - 1];

	dn::Tensor* rt = new dn::Tensor(size, 0, (*a->tensor).shape);
	dn::Vertex* result = new dn::Vertex(rt);
	dn::vertex_ops::matmul(*a, *b, *result);
	return result;
}