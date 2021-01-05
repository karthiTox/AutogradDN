//#include <iostream>
//#include <vector>
//#include <functional>
//#include <cmath>
//
//
//#include "dn.h"
//#include "utils.h"
//#include "memory_usage.h"
//
//
//#if 1
//
//#include <emscripten/emscripten.h>
//#include <emscripten/bind.h>
//#define Keep_alive EMSCRIPTEN_KEEPALIVE
//#define Bind EMSCRIPTEN_BINDINGS
//
//using namespace emscripten;
//
//#else 
//
//#define Keep_alive //
//#define Bind //
//
//#endif // 1
//
//
//// Binding code
//
//
//
//#define log(x) std::cout << x << std::endl
//
//extern "C" {
//
//	// Tensor 
//	Keep_alive
//	dn::Tensor* create_tensor() {
//		dn::Tensor* a = new dn::Tensor({}, {});
//		return a;
//	}
//
//	Keep_alive
//	uint32_t destroy_tensor(dn::Tensor* a) {
//		delete a;
//		return memoryUsage.get_usage();
//	}
//
//	Keep_alive
//	void set_data(dn::Tensor* a, double* value, int data_length) {
//		a->data.clear();
//		for (size_t i = 0; i < data_length; i++)
//		{
//			a->data.push_back(value[i]);
//		}
//	}
//
//	Keep_alive
//	void set_shape(dn::Tensor* a, double* value, int data_length) {
//		a->shape.clear();
//		for (size_t i = 0; i < data_length; i++)
//		{
//			a->shape.push_back(value[i]);
//		}
//	}
//
//	Keep_alive
//	void print(dn::Tensor* a, int type, int index){
//		switch (type)
//		{
//			case 0: a->print(); break;
//			case 1: a->print_date(); break;
//			case 2: a->print_shape(); break;
//			case 3: a->print_data_at(index);  break;
//			default: a->print();
//		}
//	}
//
//	Keep_alive
//	size_t get_data_length(dn::Tensor* a) {
//		return a->data.size();
//	}
//
//	Keep_alive
//	double* get_data(dn::Tensor* a) {
//		size_t size = a->data.size();
//		
//		double* value = new double[size];
//		
//		for (size_t i = 0; i < size; i++)
//		{
//			value[i] = a->data[i];
//		};
//
//		return value;
//	}
//
//	Keep_alive
//	uint32_t destroy_array(double* a) {
//		delete[] a;
//		return memoryUsage.get_usage();
//	}
//
//	Keep_alive
//	size_t get_shape_length(dn::Tensor* a) {
//		return a->shape.size();
//	}
//
//	Keep_alive
//	double* get_shape(dn::Tensor* a) {
//		size_t size = a->shape.size();
//
//		double* value = new double[size];
//
//		for (size_t i = 0; i < size; i++)
//		{
//			value[i] = a->shape[i];
//		};
//
//		return value;
//	}
//
//	// ops
//
//	Keep_alive
//	dn::Tensor* add_tensor(dn::Tensor* a, dn::Tensor* b) {
//		return dn::api::add(a, b);
//	}
//
//	Keep_alive
//	dn::Tensor* sub_tensor(dn::Tensor* a, dn::Tensor* b) {
//		return dn::api::sub(a, b);
//	}
//
//	Keep_alive
//	dn::Tensor* multiply_tensor(dn::Tensor* a, dn::Tensor* b) {
//		return dn::api::multiply(a, b);
//	}
//
//	Keep_alive
//	dn::Tensor* matmul_tensor(dn::Tensor* a, dn::Tensor* b) {
//		return dn::api::matmul(a, b);
//	}
//
//	Keep_alive
//	dn::Tensor* transpose_no_dim_tensor(dn::Tensor* a) {
//		return dn::api::transpose(a);
//	}
//
//	Keep_alive
//	dn::Tensor* transpose_dim_tensor(dn::Tensor* a, double* dim, int dim_length) {
//		std::vector<int> dimension;
//		for (size_t i = 0; i < dim_length; i++)
//		{
//			dimension.push_back(dim[i]);
//		}
//
//		return dn::api::transpose(a, dimension);
//	}
//
//	Keep_alive
//	dn::Tensor* applyfn_tensor(dn::Tensor* a, int code) {
//		switch (code)
//		{
//		case 1: return dn::api::applyfn(a, utils::functions::sig, utils::functions::sigPrime);
//			break;
//
//		case 2: return dn::api::applyfn(a, utils::functions::tanh, utils::functions::tanhPrime);
//			break;
//
//		case 3: return dn::api::applyfn(a, utils::functions::reLU, utils::functions::reLUprime);
//			break;
//
//		case 4: return dn::api::applyfn(a, utils::functions::floor_fn, utils::functions::floor_delta);
//			break;
//
//		case 5: return dn::api::applyfn(a, utils::functions::ceil_fn, utils::functions::ceil_delta);
//			break;
//
//		case 6: return dn::api::applyfn(a, utils::functions::round_fn, utils::functions::recp_delta);
//			break;
//
//		case 7: return dn::api::applyfn(a, utils::functions::cos_fn, utils::functions::cos_delta);
//			break;
//
//		case 8: return dn::api::applyfn(a, utils::functions::sin_fn, utils::functions::sin_delta);
//			break;
//
//		case 9: return dn::api::applyfn(a, utils::functions::tan_fn, utils::functions::tan_delta);
//			break;
//
//		case 10:return dn::api::applyfn(a, utils::functions::sqrt_fn, utils::functions::sqrt_delta);
//			break;
//
//		case 11:return dn::api::applyfn(a, utils::functions::recp_fn, utils::functions::recp_delta);
//			break;
//
//		default: return dn::api::applyfn(a, utils::functions::sig, utils::functions::sigPrime);
//			break;
//		}
//	}
//
//
//	// vertex
//	Keep_alive
//	dn::Vertex* create_vertex(dn::Tensor* tensor) {
//		dn::Vertex* a = new dn::Vertex(tensor);
//		return a;
//	}
//
//	Keep_alive
//	uint32_t destroy_vertex(dn::Vertex* a) {
//		delete a;
//		return memoryUsage.get_usage();
//	}
//	
//	Keep_alive
//	void set_destroy(dn::Vertex* vertex, int bol){
//		if (bol == 0) {
//			vertex->set_del(false);
//		}else{
//			vertex->set_del(true);
//		}
//	}
//
//	Keep_alive
//	dn::Tensor* get_tensor(dn::Vertex* vertex) {
//		return vertex->tensor;
//	}
//
//	Keep_alive
//	dn::Tensor* get_grad(dn::Vertex* vertex) {
//		return vertex->grad;
//	}
//
//	
//	Keep_alive
//	dn::Vertex* add_vertex(dn::Vertex* a, dn::Vertex* b) {
//		return dn::api::add(a, b);
//	}
//
//	Keep_alive
//	dn::Vertex* sub_vertex(dn::Vertex* a, dn::Vertex* b) {
//		return dn::api::sub(a, b);
//	}
//
//	Keep_alive
//	dn::Vertex* multiply_vertex(dn::Vertex* a, dn::Vertex* b) {
//		return dn::api::multiply(a, b);
//	}
//
//	Keep_alive
//	dn::Vertex* matmul_vertex(dn::Vertex* a, dn::Vertex* b) {
//		return dn::api::matmul(a, b);
//	}
//
//	Keep_alive
//	dn::Vertex* transpose_no_dim_vertex(dn::Vertex* a) {
//		return dn::api::transpose(a);
//	}
//
//	Keep_alive
//	dn::Vertex* transpose_dim_vertex(dn::Vertex* a, double* dim, int dim_length) {
//		std::vector<int> dimension;
//		for (size_t i = 0; i < dim_length; i++)
//		{
//			dimension.push_back(dim[i]);
//		}
//
//		return dn::api::transpose(a, dimension);
//	}
//
//	Keep_alive
//	dn::Vertex* applyfn_vertex(dn::Vertex* a, int code) {
//		switch (code)
//		{
//		case 1: return dn::api::applyfn(a, utils::functions::sig, utils::functions::sigPrime);
//			break;
//
//		case 2: return dn::api::applyfn(a, utils::functions::tanh, utils::functions::tanhPrime);
//			break;
//
//		case 3: return dn::api::applyfn(a, utils::functions::reLU, utils::functions::reLUprime);
//			break;
//
//		case 4: return dn::api::applyfn(a, utils::functions::floor_fn, utils::functions::floor_delta );
//			break;
//
//		case 5: return dn::api::applyfn(a, utils::functions::ceil_fn, utils::functions::ceil_delta);
//			break;
//
//		case 6: return dn::api::applyfn(a, utils::functions::round_fn, utils::functions::recp_delta);
//			break;
//
//		case 7: return dn::api::applyfn(a, utils::functions::cos_fn, utils::functions::cos_delta);
//			break;
//
//		case 8: return dn::api::applyfn(a, utils::functions::sin_fn, utils::functions::sin_delta);
//			break;
//
//		case 9: return dn::api::applyfn(a, utils::functions::tan_fn, utils::functions::tan_delta);
//			break;
//
//		case 10:return dn::api::applyfn(a, utils::functions::sqrt_fn, utils::functions::sqrt_delta);
//			break;
//
//		case 11:return dn::api::applyfn(a, utils::functions::recp_fn, utils::functions::recp_delta);
//			break;
//
//		default: return dn::api::applyfn(a, utils::functions::sig, utils::functions::sigPrime);
//			break;
//		}
//	}
//	
//
//
//
//	Keep_alive
//	void graph_backpass(dn::Vertex* start) {
//		dn::graph::backpass(*start);
//	}
//
//	Keep_alive
//	void graph_grad_zero(dn::Vertex* start) {
//		dn::graph::grad_zero(*start);
//	}
//
//	Keep_alive
//	void graph_update_loss(dn::Vertex* start, double rate) {
//		dn::graph::update_loss(*start, rate);
//	}
//
//	Keep_alive
//	uint32_t graph_detach(dn::Vertex* start) {
//		dn::graph::detach(start);
//		return memoryUsage.get_usage();
//	}
//
//
//
//	Keep_alive
//	uint32_t get_memory_usage(dn::Vertex* start) {
//		return memoryUsage.get_usage();
//	}
//
//}
//
