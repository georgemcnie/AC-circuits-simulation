//resistor header file
#ifndef non_RESISTOR_H
#define non_RESISTOR_H

#include<iostream>
#include<math.h>
#include<complex>
#include <vector>
#include<array>
#include<memory>

#include "resistor.h"

namespace cop{
class para_resistor : public resistor
{
protected:
    double para_c;
    double para_l;
public:
    //default constructor
	para_resistor() : resistor() { para_c = 0; para_l = 0; };
    para_resistor(const double c_in, const double r_in, const double l_in);
    ~para_resistor(){}

    //overriding
    void set_frequency(double f);
    void set_name(int n);
    void basic_details();
    auto clone() const -> std::shared_ptr<component>;

};
}
#endif