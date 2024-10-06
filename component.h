//classes header file
#ifndef COMPONENT_H
#define COMPONENT_H

#include<iostream>
#include<math.h>
#include<complex>
#include <vector>
#include<array>
#include<memory>
#define PI 3.14159 

namespace cop{
class component //pure virtual class, has children resistor, capacitor and inductor
{
protected:
    std::complex<double> impedence; //universal to all derived classes
    double frequency;
    std::string name;
public:
    //default constructor
    component(){}
    //destructor
    ~component() {}
    //pure virtual functions
    virtual double get_frequency() = 0;
    virtual void set_frequency(double f) = 0;
    virtual std::complex<double> get_impedance()= 0;
    virtual void set_impedance(std::complex<double> im_in)=0;
    virtual double get_magnitude()  = 0;
    virtual double get_phase() = 0;
    virtual void basic_details() = 0;
    virtual void set_name(int n) = 0;
    virtual void set_name(std::string n) = 0;
    virtual std::string get_name() = 0; 
    //clones the component wanted to  
    virtual auto clone() const -> std::shared_ptr<component> = 0;
};
}


#endif