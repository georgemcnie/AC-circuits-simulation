#include"circuit.h"
using namespace cir;

//param constructor
circuit::circuit(const double v_in, const double f_in){
    voltage=v_in; frequency=f_in; impedance=0;
    text_description = "V= " + std::to_string(v_in);
}

//to add components to the circuit
//makes a clone from the library so can change name and do other things in future
void circuit::add_circ_components(std::shared_ptr<component> component_in){
    circuit_components.emplace_back(component_in->clone());
    circuit_components.back()->set_frequency(frequency);
    circuit_components.back()->set_name(circuit_components.size()); 
    if(circuit_components.size()==1){
        impedance = circuit_components.back()->get_impedance();
        text_description = "["+text_description+"]" + "-["+ circuit_components.back()->get_name()+"]";
    }
}

//gets number of components in circuit
int circuit::components_in_circuit(){
    return circuit_components.size();
}

double circuit::get_frequency(){return frequency;}
void circuit::set_frequency(const double f_in){frequency=f_in;}
std::string circuit::get_description(){return text_description;}
void circuit::set_impedence(std::complex<double> im_in){impedance=im_in;}
std::complex<double> circuit::get_impedence(){return impedance;}


//returns a vector of size x, these are the last ones added to the circuit
std::vector<std::shared_ptr<component>> circuit::last_x_in_components(int x){
    int count = 0;
    std::vector<std::shared_ptr<component>> out;
    // Iterate over the vector in reverse order and print the last x elements
    for (auto it = circuit_components.rbegin(); it != circuit_components.rend(); ++it) {
        if (count == x) {
            break;
        }
        out.emplace_back(*it);
        ++count;
    }
    return out;
}

void circuit::add_series(const std::shared_ptr<component> component_in){
    impedance+=(component_in)->get_impedance();
    text_description = "["+text_description+"]" + "-[" + component_in->get_name() + "]";
}

void circuit::add_parallel(const std::shared_ptr<component> component_in){
    impedance= std::pow(std::pow(impedance, -1) + std::pow(component_in->get_impedance(), -1), -1);
    text_description = "{" + text_description + "} || {" + component_in->get_name() + "}";
}

//output stuff in the circuit
std::string circuit::info(){
    std::stringstream info;
    std::string spaces(8, ' ');

    info << text_description << "\n";
    info << "The impedance of the circuit is " << std::setprecision(3) << impedance << "\n";
    info << "With phase shift " << std::setprecision(3) << std::arg(impedance) << "\n";
    info << "And magnitude " << std::setprecision(3) << std::abs(impedance) << "\n";
    info << "---------------CIRCUIT COMPONENTS---------------\n";
    info << std::setw(15) << "Component"
         << std::setw(15) << "Impedance"
         << std::setw(15) << "Magnitude"
         << std::setw(15) << "Phase\n";
    for (auto it = circuit_components.rbegin(); it != circuit_components.rend(); ++it) {
        info << std::setw(15) << (*it)->get_name()
             << std::setw(15) << std::setprecision(3) << (*it)->get_impedance()
             << std::setw(15) << std::setprecision(3) << (*it)->get_magnitude()
             << std::setw(15) << std::setprecision(3) << (*it)->get_phase() << "\n";
    }
    return info.str();
}


//to add embedded circuits
//same function but overloaded with a shared pointer of an embedded circuit
void circuit::add_series(std::shared_ptr<circuit> ec){
    std::string ec_text = ec->get_description();

    //add numbers to string stream so that they are consistent with main circuit numbering    
    size_t pos = 0;
    int x=1;
    while ((pos = ec_text.find_first_of("0123456789", pos)) != std::string::npos) {
        size_t end_pos = ec_text.find_first_of("}] ", pos);
        int num = std::stoi(ec_text.substr(pos, end_pos - pos));
        num += x;
        ec_text.replace(pos, end_pos - pos, std::to_string(num));
        pos = end_pos;
        x++;
    }
    
    //removes the empty bracket as its embedded and doesn't have a voltage source to put into it
    size_t position = 0;
    while ((position = ec_text.find("[]-", position)) != std::string::npos) {
        ec_text.erase(position, 3);
    }
    //will get all components in ec as extremely improbable there will be 10000 components
    std::vector<std::shared_ptr<component>> ec_comps = ec->last_x_in_components(10000);
    //change names to line up with ones in main circuit, so numbered correctly
    int count{1};
    for (auto it = ec_comps.rbegin(); it != ec_comps.rend(); ++it) {
        (*it)->set_name(circuit_components.size()+count);
        circuit_components.emplace_back(*it);
    }

    impedance+= ec->get_impedence();
    text_description = "["+text_description+"]" + "-[" + ec_text + "]";
}

void circuit::add_parallel(std::shared_ptr<circuit> ec){
    std::string ec_text = ec->get_description();

    //add numbers to string stream so that they are consistent with main circuit numbering    
    size_t pos = 0;
    int x=1;
    while ((pos = ec_text.find_first_of("0123456789", pos)) != std::string::npos) {
        size_t end_pos = ec_text.find_first_of("}] ", pos);
        int num = std::stoi(ec_text.substr(pos, end_pos - pos));
        num += x;
        ec_text.replace(pos, end_pos - pos, std::to_string(num));
        pos = end_pos;
        x++;
    }
    
    //removes the empty bracket as its embedded and doesn't have a voltage source to put into it
    size_t position = 0;
    while ((position = ec_text.find("[]-", position)) != std::string::npos) {
        ec_text.erase(position, 3);
    }

    std::cout<<ec->get_impedence()<<std::endl;
    impedance+= ec->get_impedence();
    text_description = "["+text_description+"]" + "-[" + ec_text + "]";

    //will get all components in ec as extremely improbable there will be 10000 components
    std::vector<std::shared_ptr<component>> ec_comps = ec->last_x_in_components(10000);
    //change names to line up with ones in main circuit, so numbered correctly
    int count{1};
    for (auto it = ec_comps.rbegin(); it != ec_comps.rend(); ++it) {
        (*it)->set_name(circuit_components.size()+count);
        circuit_components.emplace_back(*it);
    }

    impedance= std::pow(std::pow(impedance, -1) + std::pow(ec->get_impedence(), -1), -1);
    text_description = "{" + text_description + "} || {" + ec_text + "}";

}