#include "para_capacitor.h"

using namespace cop;

//param constructor
para_capacitor::para_capacitor(const double c_in, const double r_in, const double l_in){
    capacitance = c_in;
    para_r = r_in;
    para_l = l_in;
}

void para_capacitor::set_frequency(double f){
    frequency = 2 * PI * f; 
    std::complex<double> z(para_r, frequency*para_l - 1 / (frequency*capacitance)); // Z = Rp + i(wLp - 1/wC)
    impedence = z;
};

void para_capacitor::set_name(int n){name = "Real C" +std::to_string(n);}

void para_capacitor::basic_details(){
    std::cout<<"    Real Capacitor has capacitance c: "<< capacitance*1e9<<"nF"<<std::endl;
    std::cout<<"                   has parasitic resistance r: "<< para_r<<"ohms"<<std::endl;
    std::cout<<"                   has parasitic inductance l: "<< para_l*1e3<<"mH"<<std::endl;
}

auto para_capacitor::clone() const->std::shared_ptr<component> 
{
  return std::shared_ptr<component>(new para_capacitor{*this});
}