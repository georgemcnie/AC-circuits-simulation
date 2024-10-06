#include "para_resistor.h"
using namespace cop;

//param constructorresistor
para_resistor::para_resistor(const double c_in, const double r_in, const double l_in){
    resistance = r_in;
    para_c = c_in;
    para_l = l_in;
}

void para_resistor::set_frequency(double f){
    frequency = 2 * PI * f; 
    std::complex<double> numerator(resistance, frequency*para_l);
	std::complex<double> denominator(1 - frequency*frequency*para_c*para_l, frequency*resistance*para_c);
	std::complex<double> z = numerator / denominator; //z = R + iwLp / (1 - w^2CpLp) + iwRCp
    impedence = z;
};

void para_resistor::set_name(int n){name = "Real R" +std::to_string(n);}

void para_resistor::basic_details(){
    std::cout<<"    Real resistor has resistance r: "<< resistance<<"ohms"<<std::endl;
    std::cout<<"                   has parasitic capacitance c: "<< para_c*1e9<<"nF"<<std::endl;
    std::cout<<"                   has parasitic inductance l: "<< para_l*1e3<<"mH"<<std::endl;
}

auto para_resistor::clone() const->std::shared_ptr<component> 
{
  return std::shared_ptr<component>(new para_resistor{*this});
}