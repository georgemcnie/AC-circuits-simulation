//inductor header file
#ifndef non_INDUCTOR_H
#define non_INDUCTOR_H

#include<iostream>
#include<math.h>
#include<complex>
#include <vector>
#include<array>
#include<memory>

#include "inductor.h"

namespace cop{
class para_inductor : public inductor
{
protected:
    double para_c;
    double para_r;
public:
    //default constructor
	para_inductor() : inductor() { para_c = 0; para_r = 0; };
    para_inductor(const double c_in, const double r_in, const double l_in);
    ~para_inductor(){}

    //overriding
    void set_frequency(double f);
    void set_name(int n);
    void basic_details();
    auto clone() const -> std::shared_ptr<component>;

};
}

#endif