#pragma once

#include <vector>
#include <cmath>

namespace utils {

	std::vector<int> _cstep(std::vector<int> shape);

	std::vector<int> _cstep_change(std::vector<int> step, std::vector<int> dimension);
	
	int _cindex(std::vector<int> index, std::vector<int> step);

	std::vector<int> _findIndex(std::vector<int> shape, std::vector<int> step, int index);

	std::vector<double> _transpose_main(
		std::vector<double> a,
		std::vector<int> shape,
		std::vector<int> step,
		std::vector<int> dimension
	);

	std::vector<double> _mat_mul_2d(
		std::vector<double> a,
		std::vector<int> a_shape,
		std::vector<double> b,
		std::vector<int> b_shape
	);

	std::vector<double> _split_t2d(
		std::vector<double> a,
		std::vector<int> aShape,
		std::vector<double> b,
		std::vector<int> bSshape
	);

	namespace functions {
		
		double sig(double z);
		
		double sigPrime(double z);

		double  tanh(double z);

		double  tanhPrime(double z);

		double  reLU(double z);

		double  reLUprime(double z);

		double floor_fn(double z);

		double floor_delta(double z);

		double ceil_fn(double z);

		double ceil_delta(double z);

		double round_fn(double z);

		double round_delta(double z);

		double cos_fn(double z);

		double cos_delta(double z);

		double sin_fn(double z);

		double sin_delta(double z);

		double tan_fn(double z);

		double tan_delta(double z);

		double sqrt_fn(double z);
		

		double sqrt_delta(double z);

		double recp_fn(double z);

		double recp_delta(double z);
	}
}