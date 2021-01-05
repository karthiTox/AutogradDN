#include <vector>
#include <cmath>

namespace utils {

	std::vector<int> _cstep(std::vector<int> shape) {
		std::vector<int> res;
		int size = shape.size();
		for (int s = 0; s < size; s++) {
			if (s == shape.size() - 1)
				res.push_back(1);
			else {
				int red = 1;
				for (int l = s + 1; l < size; l++) {
					red *= shape[l];
				};
				res.push_back(red);
			}
		}

		return res;
	}

	std::vector<int> _cstep_change(std::vector<int> step, std::vector<int> dimension) {
		std::vector<int> res = step;
		for (int d = 0; d < dimension.size(); d++) {
			res[d] = step[dimension[d]];
		};
		return res;
	}

	int _cindex(std::vector<int> index, std::vector<int> step) {
		int res = 0;
		for (int i = 0; i < index.size(); i++) {
			res += index[i] * step[i];
		};
		return res;
	}

	std::vector<int> _findIndex(std::vector<int> shape, std::vector<int> step, int index) {
		std::vector<int> _s = shape;
		for (int s = 0; s < shape.size(); s++) {
			_s[s] = shape[s] * step[s];
			_s[s] = floor((index % _s[s]) / step[s]);
		}

		return _s;
	}

	std::vector<double> _transpose_main(
		std::vector<double> a,
		std::vector<int> shape,
		std::vector<int> step,
		std::vector<int> dimension
	) {
		std::vector<int> _step = _cstep(_cstep_change(shape, dimension));
		std::vector<double> result;

		size_t size = a.size();
		for (int ia = 0; ia < size; ia++) {
			std::vector<int> findex = _findIndex(shape, step, ia);
			findex = _cstep_change(findex, dimension);
			
			int ni = 0;

			size_t fsize = findex.size();
			for (size_t sh = 0; sh < fsize; sh++) {
				ni += findex[sh] * _step[sh];
			}

			result.push_back(a[ni]);
		};

		return result;
	}

	std::vector<double> _mat_mul_2d(
		std::vector<double> a,
		std::vector<int> a_shape,
		std::vector<double> b,
		std::vector<int> b_shape
	){
		int col_step = a_shape[a_shape.size() - 1];
		
		std::vector<int> dim = b_shape;
		for (int i = 0; i < dim.size(); i++) {
			dim[i] = dim.size() - 1 - i;
		}

		std::vector<double> b_data = _transpose_main(
			b, 
			b_shape, 
			_cstep(b_shape), 
			dim
		);
		
		std::vector<int> bShape = _cstep_change(b_shape, dim);

		std::vector<double> res;		

		for (int r = 0; r < a.size() / col_step; r++) {

			for (int c = 0; c < b_shape[b_shape.size() - 1]; c++) {
				std::vector<double> a_m;
				for (int lta = r * col_step; lta < r * col_step + col_step; lta++) {
					a_m.push_back(a[lta]);
				}

				std::vector<double> b_m;
				for (int ltb = c * col_step; ltb < c * col_step + col_step; ltb++) {
					b_m.push_back(b_data[ltb]);
				}

				double tot = 0;
				for (int i = 0; i < a_m.size(); i++) {
					tot += a_m[i] * b_m[i];
				}
				res.push_back(tot);
			}

		};

		return res;
	}

	std::vector<double> _split_t2d(
		std::vector<double> a,
		std::vector<int> aShape,
		std::vector<double> b,
		std::vector<int> bSshape
	){

		std::vector<int> a_shape = { aShape[aShape.size() - 2], aShape[aShape.size() - 1] };
		std::vector<int> b_shape = { bSshape[bSshape.size() - 2], bSshape[bSshape.size() - 1] };

		int tot_el_a = a_shape[0] * a_shape[1];
		int tot_el_b = b_shape[0] * b_shape[1];

		std::vector<double> res;

		for (int i = 0; i < a.size() / tot_el_a; i++) {
			std::vector<double> ad;
			std::vector<double> bd;

			for (int la = i * tot_el_a; la < i * tot_el_a + tot_el_a; la++) {
				ad.push_back(a.at(la));
			}

			for (int lb = i * tot_el_b; lb < i * tot_el_b + tot_el_b; lb++) {
				bd.push_back(b.at(lb));
			}

			for (double v : _mat_mul_2d(
				ad, a_shape,
				bd, b_shape
			)) res.push_back(v);
		};

		return res;
	}
}
