#include "utils.h"

namespace utils {
	namespace functions {

		double sig(double z) {
			return 1.0 / (1.0 + exp(-1 * z));
		}

		double sigPrime(double z) {
			return (1.0 / (1.0 + exp(-1 * z))) * (1 - (1.0 / (1.0 + exp(-1 * z))));
		}

		double  tanh(double z) {
			return (exp(z) - exp(-z)) / (exp(z) + exp(-z));
		}

		double  tanhPrime(double z) {
			return 1 - ((exp(z) - exp(-z)) / (exp(z) + exp(-z)) * (exp(z) - exp(-z)) / (exp(z) + exp(-z)));
		}

		double  reLU(double z) {
			if (0 > z) {
				return 0;
			}
			else if (0 < z) {
				return z;
			}
			else {
				return z;
			}
		}

		double  reLUprime(double z) {
			if (z > 0) {
				return 1;
			}
			else {
				return 0;
			}
		}

		double floor_fn(double z){
			return floor(z);
		}

		double floor_delta(double z) {
			double h = 0.05;
			return ((floor_fn(z) - floor_fn(z)) / 2 * h);
		}

		double ceil_fn(double z) {
			return ceil(z);
		}

		double ceil_delta(double z) {
			double h = 0.05;
			return ((ceil_fn(z) - ceil_fn(z)) / 2 * h);
		}

		double round_fn(double z) {
			return round(z);
		}

		double round_delta(double z) {
			double h = 0.05;
			return ((round_fn(z) - round_fn(z)) / 2 * h);
		}

		double cos_fn(double z) {			
			return cos(z);
		}

		double cos_delta(double z) {
			return -1.0 * sin(z);
		}

		double sin_fn(double z) {
			return sin(z);
		}

		double sin_delta(double z) {
			return cos(z);
		}

		double tan_fn(double z) {
			return tan(z);
		}

		double tan_delta(double z) {
			return 1.0/(cos(z)*cos(z));
		}

		double sqrt_fn(double z) {
			return sqrt(z);
		}

		double sqrt_delta(double z) {
			return 0.5 * (pow(z, -0.5));
		}

		double recp_fn(double z) {
			return (1/z);
		}

		double recp_delta(double z) {
			return (pow(z, -2));
		}

	}
}