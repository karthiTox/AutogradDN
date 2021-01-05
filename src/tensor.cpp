#include "dn.h"
#include <string>
#include <vector>

dn::Tensor::Tensor() {
}

int dn::Tensor::get_data_length()
{
	return data.size();
}

int dn::Tensor::get_shape_length()
{
	return shape.size();
}

double* dn::Tensor::get_data()
{
	size_t size = data.size();
	double* arr = new double[size];
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = data[i];
	};

	return arr;
}

int* dn::Tensor::get_shape()
{
	size_t size = shape.size();
	int* arr = new int[size];
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = shape[i];
	};
	
	return arr;
}

void dn::Tensor::set_data(double* data)
{
	this->data = std::vector<double>(*data);
}

void dn::Tensor::set_shape(int* shape)
{
	this->shape = std::vector<int>(*shape);
}






dn::Tensor::Tensor(std::vector<double> a, std::vector<int> s) : data(a), shape(s) { }

dn::Tensor::Tensor(size_t count, double val, std::vector<int> sh){
	for (int i = 0; i < count; i++) {
		data.push_back(val);
	}

	for (int s : sh) {
		shape.push_back(s);
	}
};

dn::Tensor::Tensor(const Tensor& sec) { data = sec.data; shape = sec.shape; }

void dn::Tensor::print() {
	std::string ns;

	std::vector<int> t_el;

	size_t size = shape.size();
	for (int i = 0; i < size; i++){
		int t = 1;
		for (int j = i; j < size; j++) {
			t *= shape[j];
		}
		t_el.push_back(t);
	}

	for (int i = 0; i < size; i++) {
		ns.append("[");
	}

	int i = 0;
	int count = 0;
	for (double d : data){
		for (int s : t_el) {
			if(i%s == 0){
				count++;
			}
		}

		if (i != 0) {
			if (count > 0) {
				ns.pop_back();
				for (int i = 0; i < count; i++) {
					ns.append("]");
				}
				ns.append(",");
				for (int i = 0; i < count; i++) {
					ns.append("[");
				}
			}
		}

		ns.append(std::to_string(d));
		ns.append(",");

		i++;
		count = 0;
	}

	ns.pop_back();
	for (int i = 0; i < size; i++) {
		ns.append("]");
	};

	this->print_tensor(ns, size);
};


void dn::Tensor::print_tensor(std::string res, int count){
	std::string& str = res;
	std::cout << "Tensor" << std::endl;

	for (std::string::size_type c = 0; c < str.size(); c++) {		
		if (str[c] == ',' and str[c + 1] == '[') {
			int cn_count = 0;

			for (int cn = c + 1; cn < str.size(); cn++) {
				if (str[cn] != '[') break;
				cn_count += 1;
			}

			for (int i = 0; i < cn_count; i++){
				std::cout << "\n";
			}

			for (int i = 0; i < (count - cn_count); i++){
				std::cout << " ";
			}

			continue;
		}

		else if (str[c] == ',') {
			std::cout << " ";
		}
		else {
			std::cout << str[c];
		}
	}
	
	std::cout << "\n" << std::endl;


}


void dn::Tensor::print_date() {
	std::cout << "[";

	for(double i : data){
		std::cout << " " << i << " ";
	}

	std::cout << "]\n" << std::endl;
};

void dn::Tensor::print_shape() {
	std::cout << "[";

	for (double i : shape) {
		std::cout << " " << i << " ";
	}

	std::cout << "]\n" << std::endl;
};

void dn::Tensor::print_both() {
	std::cout << "Data: " << std::endl;
	print_date();
	std::cout << "Shape: " << std::endl;
	print_shape();
	std::cout << "\n" << std::endl;
};

void dn::Tensor::print_data_at(size_t index) {
	std::cout << data[index] << std::endl;
};
