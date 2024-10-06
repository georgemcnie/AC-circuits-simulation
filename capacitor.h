//resistor header file
#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "component.h"
#include<iostream>
#include<math.h>
#include<complex>
#include <vector>
#include<array>
#include<memory>

namespace cop{
class capacitor : public component
{
protected:
    double capacitance;
public:
    //default constructor
	capacitor(){capacitance=0; impedence=0;};
    capacitor(const double c_in);
    ~capacitor(){}
    double get_frequency(); 
    void set_frequency(double f);
    std::complex<double> get_impedance();
    void set_impedance(std::complex<double> im_in);
    double get_magnitude();
    double get_phase();
    void basic_details();
    void set_name(int n);
    void set_name(std::string n);
    std::string get_name();
    auto clone() const -> std::shared_ptr<component>;
};
}
#endif