//resistor header file
#ifndef non_CAPACITOR_H
#define non_CAPACITOR_H

#include<iostream>
#include<math.h>
#include<complex>
#include <vector>
#include<array>
#include<memory>

#include "capacitor.h"

namespace cop{
class para_capacitor : public capacitor
{
protected:
    double para_r;
    double para_l;
public:
    //default constructor
	para_capacitor() : capacitor() { para_r = 0; para_l = 0; };
    para_capacitor(const double c_in, const double r_in, const double l_in);
    ~para_capacitor(){}

    //overriding
    void set_frequency(double f);
    void set_name(int n);
    void basic_details();
    auto clone() const -> std::shared_ptr<component>; 

};
}

#endif