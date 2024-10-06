#ifndef INTERFACE_H
#define INTERFACE_H

#include<iostream>
#include<math.h>
#include<complex>
#include <vector>
#include<array>
#include<memory>
#include <fstream>
#include <regex>
#include <chrono>
#include <thread>

#include "circuit.h"
#include "component.h"
#include "resistor.h"
#include "capacitor.h"
#include "inductor.h"
#include "para_resistor.h"
#include "para_capacitor.h"
#include "para_inductor.h"

using namespace cop;
//using namespace cir;

void menu_1();
void section_break();

//creating components and manipulating component library
int is_created_real(std::string comp_type);
struct parasitic_vals;
parasitic_vals set_parasitic_vals(std::string comp_type);
void create_component();
void delete_component();
void view_library();

//circuit stuff
void select_component();
void series_multiple();
void parallel_multiple();
void save_circuit();
std::shared_ptr<cir::circuit> embedded();
void menu_circuits();
void create_circuit();


#endif