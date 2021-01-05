#include "utils.h"
#include "dn.h"

dn::Tensor& dn::tensor_ops::add(Tensor& a, Tensor& b, Tensor& res) {
	int size = a.data.size();
	for (int i = 0; i < size; i++) {
		res.data[i] = a.data[i] + b.data[i];
	}
	res.shape = a.shape;
	return res;
};


dn::Tensor& dn::tensor_ops::sub(dn::Tensor& a, dn::Tensor& b, dn::Tensor& res) {
	int size = a.data.size();

	for (int i = 0; i < size; i++) {
		res.data[i] = a.data[i] - b.data[i];
	}
	res.shape = a.shape;

	return res;
};

dn::Tensor& dn::tensor_ops::multiply(dn::Tensor& a, dn::Tensor& b, dn::Tensor& res) {
	int size = a.data.size();
	for (int i = 0; i < size; i++) {
		res.data[i] = a.data[i] * b.data[i];
	}
	res.shape = a.shape;

	return res;
};

dn::Tensor& dn::tensor_ops::applyfn(dn::Tensor& a, const std::function<double(double)>& fn, dn::Tensor& res) {
	int size = a.data.size();
	for (int i = 0; i < size; i++) {
		res.data[i] = fn(a.data[i]);
	}
	res.shape = a.shape;

	return res;
};

dn::Tensor& dn::tensor_ops::transpose(dn::Tensor& a, std::vector<int> dimension, dn::Tensor& res) {
	res.data = utils::_transpose_main(a.data, a.shape, utils::_cstep(a.shape), dimension);
	res.shape = utils::_cstep_change(a.shape, dimension);
	return res;
};


dn::Tensor& dn::tensor_ops::transpose(dn::Tensor& a, dn::Tensor& res) {
	std::vector<int> dimension = a.shape;
	int size = dimension.size();
	for (int i = 0; i < size; i++) {
		dimension[i] = dimension.size() - 1 - i;
	}
	res.data = utils::_transpose_main(a.data, a.shape, utils::_cstep(a.shape), dimension);
	res.shape = utils::_cstep_change(a.shape, dimension);
	return res;
};


dn::Tensor& dn::tensor_ops::matmul(dn::Tensor& a, dn::Tensor& b, dn::Tensor& res) {
	int asize = a.shape.size();
	int bsize = b.shape.size();

	if (asize > 1 && bsize > 1) {
		if (a.shape[asize - 1] != b.shape[asize - 2])
			return a;

		if (asize > 2) {
			for (int s = 0; s < asize - 2; s++) {
				if (a.shape[s] != b.shape[s])
					return a;
			}
		}

	}
	else {
		return dn::tensor_ops::multiply(a, b, res);
	}



	res.data = utils::_split_t2d(a.data, a.shape, b.data, b.shape);
	res.shape = a.shape;
	res.shape[res.shape.size() - 1] = b.shape[b.shape.size() - 1];

	return res;
}