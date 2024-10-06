//resistor header file
#ifndef INDUCTOR_H
#define INDUCTOR_H

#include<iostream>
#include<math.h>
#include<complex>
#include <vector>
#include<array>
#include<memory>
#include "component.h"

namespace cop{
class inductor : public component
{
protected:
    double inductance;
public:
    inductor(){inductance=0; impedence=0;} //default
    inductor(const double L_in);
    ~inductor(){}
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