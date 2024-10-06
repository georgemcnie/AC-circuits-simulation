#include "resistor.h"
//RESISTOR
//param constructor
using namespace cop;

resistor::resistor(double r_in){ 
    resistance = r_in;
    impedence = r_in;
}
resistor::resistor(){
    resistance=0;
    impedence=0;
}  
double resistor::get_frequency(){frequency =0; return frequency;}; //no frequency for a resistor
void resistor::set_frequency(double f){};
std::complex<double> resistor::get_impedance(){return impedence;}
void resistor::set_impedance(std::complex<double> im_in){impedence = im_in;}
double resistor::get_magnitude(){return abs(impedence);}
double resistor::get_phase(){return arg(impedence);}
void resistor::basic_details(){
    std::cout<<"    Resistor has resistance r: "<< resistance<<" ohms"<<std::endl;
}

auto resistor::clone() const->std::shared_ptr<component> 
{
  return std::shared_ptr<component>(new resistor{*this});
}
void resistor::set_name(int n){name = "R" + std::to_string(n);}
void resistor::set_name(std::string n){name = n;}
std::string resistor::get_name(){return name;}
