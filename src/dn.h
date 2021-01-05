#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <memory>

namespace dn {


	class Tensor {
	private:
		void print_tensor(std::string res, int count);
	public:

		std::vector<double> data;
		std::vector<int> shape;

		Tensor(std::vector<double> a, std::vector<int> s);		
		Tensor(size_t count, double val, std::vector<int> sh);
		Tensor();
		void print();
		void print_date();
		void print_shape();
		void print_both();
		void print_data_at(size_t index);

		Tensor(const Tensor& sec);		

		double* get_data();
		int* get_shape();

		int get_data_length();
		int get_shape_length();


		void set_data(double* data);
		void set_shape(int* shape);

	};

	class Vertex {
	public:
		Tensor* tensor;
		Tensor* grad;
		std::vector<Vertex*> parents;
		std::function<void()> back;
		bool del_while_detach = true;

		Vertex( Tensor* a, std::vector<Vertex*> par, std::function<void()> b );
		Vertex( Tensor* a );

		void set_del(bool y);

		~Vertex();
	};

	namespace tensor_ops {


		dn::Tensor& add(Tensor& a, Tensor& b, Tensor& res);
		dn::Tensor& sub(dn::Tensor& a, dn::Tensor& b, dn::Tensor& res);
		dn::Tensor& multiply(dn::Tensor& a, dn::Tensor& b, dn::Tensor& res);
		dn::Tensor& applyfn(dn::Tensor& a, const std::function<double(double)>& fn, dn::Tensor& res);

		dn::Tensor& transpose(dn::Tensor& a, std::vector<int> dimension, dn::Tensor& res);
		dn::Tensor& transpose(dn::Tensor& a, dn::Tensor& res);
		dn::Tensor& matmul(dn::Tensor& a, dn::Tensor& b, dn::Tensor& res);

	}

	namespace vertex_ops {


		dn::Vertex& add(Vertex& a, Vertex& b, Vertex& res);
		dn::Vertex& sub(dn::Vertex& a, dn::Vertex& b, dn::Vertex& res);
		dn::Vertex& multiply(dn::Vertex& a, dn::Vertex& b, dn::Vertex& res);
		dn::Vertex& applyfn(
			dn::Vertex& a,
			const std::function<double(double)> fn,
			const std::function<double(double)> deltafn,
			dn::Vertex& res
		);

		dn::Vertex& transpose(dn::Vertex& a, std::vector<int>& dimension, dn::Vertex& res);
		dn::Vertex& transpose(dn::Vertex& a, dn::Vertex& res);
		dn::Vertex& matmul(dn::Vertex& a, dn::Vertex& b, dn::Vertex& res);
	}


	namespace api {

		dn::Tensor* add(dn::Tensor* a, dn::Tensor* b);
		dn::Vertex* add(dn::Vertex* a, dn::Vertex* b);

		dn::Tensor* sub(dn::Tensor* a, dn::Tensor* b);
		dn::Vertex* sub(dn::Vertex* a, dn::Vertex* b);

		dn::Tensor* multiply(dn::Tensor* a, dn::Tensor* b);
		dn::Vertex* multiply(dn::Vertex* a, dn::Vertex* b);

		dn::Tensor* applyfn(
			dn::Tensor* a,
			const std::function<double(double)> fn,
			const std::function<double(double)> deltafn
		);
		dn::Vertex* applyfn(
			dn::Vertex* a,
			const std::function<double(double)> fn,
			const std::function<double(double)> deltafn
		);

		
		dn::Tensor* transpose(dn::Tensor* a, std::vector<int> dimension);		
		dn::Vertex* transpose(dn::Vertex* a, std::vector<int> dimension);		
				
		dn::Tensor* transpose(dn::Tensor* a);
		dn::Vertex* transpose(dn::Vertex* a);

		dn::Tensor* matmul(dn::Tensor* a, dn::Tensor* b);
		dn::Vertex* matmul(dn::Vertex* a, dn::Vertex* b);
	
	}


	namespace graph{
		
		void traversal(dn::Vertex& node);
		void backpass(dn::Vertex& node);		
		void update_loss(dn::Vertex& node, double rate);
		void grad_zero(dn::Vertex& node);
		void detach(dn::Vertex* node);

	}
};