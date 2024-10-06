//resistor header file
#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<iostream>
#include<math.h>
#include<complex>
#include <vector>
#include<array>
#include<memory>
#include<sstream>
#include <iomanip>
#include <cmath>
#include<string>
#include<algorithm>
#include<regex>
#include <sstream>

#include"component.h"
using namespace cop;

namespace cir{
class circuit {
	private:
		std::vector<std::shared_ptr<cop::component>> circuit_components;
		std::complex<double>impedance;
		double voltage;
		double frequency;
		std::string text_description;
	public:
		//default constructor
		circuit() : voltage{0}, frequency{0}{}
		//parameterised constructor
		circuit(const double v_in, const double f_in);
		//destructor
		~circuit() {};
        void add_circ_components(std::shared_ptr<cop::component> component_in);
        int components_in_circuit();
        std::vector<std::shared_ptr<cop::component>> last_x_in_components(int x);
		void add_series(const std::shared_ptr<component> component_in);
		void add_parallel(const std::shared_ptr<component> component_in);
        std::string info();
		double get_frequency();
		void add_series(std::shared_ptr<circuit> ec);
		void add_parallel(std::shared_ptr<circuit> ec);
		void set_frequency(const double f_in);
		std::string get_description();
		void set_impedence(std::complex<double> im_in);
		std::complex<double> get_impedence();
};
}

#endif