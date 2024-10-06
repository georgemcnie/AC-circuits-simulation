#include"inductor.h"
//INDUCTOR
using namespace cop;

inductor::inductor(const double L_in){
    inductance = L_in;
}
double inductor::get_frequency(){return frequency;}; 
void inductor::set_frequency(double f){
    frequency = 2 * PI * f; 
    std::complex<double> z(0,(frequency*inductance)); //Z=iLw
    impedence = z;
};
std::complex<double> inductor::get_impedance(){return impedence;};
void inductor::set_impedance(std::complex<double> im_in){impedence = im_in;}
double inductor::get_magnitude(){return abs(impedence);};
double inductor::get_phase(){return arg(impedence);};
void inductor::basic_details(){
    std::cout<<"    Inductor has inductance L: "<< inductance*1e3<<"mH"<<std::endl;
}
auto inductor::clone() const->std::shared_ptr<component> 
{
  return std::shared_ptr<component>(new inductor{*this});
}
void inductor::set_name(int n){name = "L" + std::to_string(n);}
void inductor::set_name(std::string n){name = n;}
std::string inductor::get_name(){return name;}