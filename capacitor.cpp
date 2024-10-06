#include "capacitor.h"
//CAPACITOR class implementation for capacitor.h
using namespace cop;
//CONSTRUCTOR
capacitor::capacitor(const double c_in){
    capacitance = c_in;
}
double capacitor::get_frequency(){return frequency;}; //no frequency for a resistor
void capacitor::set_frequency(double f){
    frequency = 2 * PI * f; 
    std::complex<double> z(0,-1/(frequency*capacitance)); //Z=-j/wc
    impedence = z;
};
std::complex<double> capacitor::get_impedance(){return impedence;};
void capacitor::set_impedance(std::complex<double> im_in){impedence = im_in;}
double capacitor::get_magnitude(){return abs(impedence);};
double capacitor::get_phase(){return arg(impedence);};
void capacitor::basic_details(){
    std::cout<<"    Capacitor has capacitance c: "<< capacitance*1e9<<"nF"<<std::endl;
}

auto capacitor::clone() const->std::shared_ptr<component> 
{
  return std::shared_ptr<component>(new capacitor{*this});
}
void capacitor::set_name(int n){name = "C" +std::to_string(n);}
void capacitor::set_name(std::string n){name=n;}
std::string capacitor::get_name(){return name;}