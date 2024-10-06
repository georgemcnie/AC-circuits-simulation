//resistor header file
#ifndef RESISTOR_H
#define RESISTOR_H

#include "component.h"
#include<iostream>
#include<math.h>
#include<complex>
#include <vector>
#include<array>
#include<memory>

namespace cop{
class resistor : public component
{
protected:
    double resistance;
public:
    resistor(); //default
    resistor(const double r_in); //parameterised
    ~resistor(){}
    double get_frequency(); //no frequency for a resistor
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
