#include "para_inductor.h"
using namespace cop;

//param constructorinductor
para_inductor::para_inductor(const double c_in, const double r_in, const double l_in){
    inductance = l_in;
    para_c = c_in;
    para_r = r_in;
}

void para_inductor::set_frequency(double f){
    frequency = 2 * PI * f; 
    std::complex<double> numerator(para_r, frequency*inductance);
    std::complex<double> denom(1 - frequency*frequency*para_c*inductance, frequency*para_r*para_c);
    std::complex<double> z = numerator / denom; //Z = Rp + iwL / (1 - w^2CpL) + iwRpCp
    impedence = z;
};

void para_inductor::set_name(int n){name = "Real L" +std::to_string(n);}

void para_inductor::basic_details(){
    std::cout<<"    Real inductor has inductance c: "<< inductance*1e3<<"mH"<<std::endl;
    std::cout<<"                   has parasitic capacitance c: "<< para_c*1e9<<"nF"<<std::endl;
    std::cout<<"                   has parasitic resistance r: "<< para_r<<"ohms"<<std::endl;
}

auto para_inductor::clone() const->std::shared_ptr<component> 
{
  return std::shared_ptr<component>(new para_inductor{*this});
}