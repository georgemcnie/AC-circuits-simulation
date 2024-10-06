//non-member functions

#include "interface.h"

static std::vector<std::shared_ptr<component>> component_library; //library of pointers to components
static std::unique_ptr<cir::circuit> user_circuit;

//to have a break between sections
void section_break(){std::cout<<"****************************************************"<<std::endl;}

//template to have a numeric input, so can input float or int and will validate them depending on what needed
template <class c_type> c_type valid_numeric_input(c_type min,c_type max) 
{
  c_type input;
  while (true) {
    std::cin >> input;
    if (std::cin.fail()) { // If nothing is entered it will be true
      std::cin.clear(); // For resetting the bits
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore() is used to clear the wrong input entered
      std::cout <<"Please enter a valid input: ";
      continue; //runs loop again
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove the additional input from the stream
    if (std::cin.gcount() > 1) { // it will return more than 1 if there is something which is not extracted properly
     std::cout <<"Please enter a valid input: ";
     continue; 
    }
    if (input > max || input < min){
        std::cout <<"Please enter a input in valid range: ";
        continue; 
    }
    break;
  }
  return input;
}

//*****************NON MEMBER FUNCTIONS FOR COMPONENTS IN LIBRARY*****************

int is_created_real(std::string comp_type){
    std::cout<<"Is the "<< comp_type<<" Ideal(1) or Real(2): ";
    int option = valid_numeric_input<int>(1,2);
    return option;
}

//struct to store parastitic values of a real (non-ideal) component
struct parasitic_vals {
    double r;
    double c;
    double l;
};

parasitic_vals set_parasitic_vals(std::string comp_type) {
    parasitic_vals parasitic_vals;
    std::cout << "Enter the parasitic resistance of"<< comp_type<<" (ohms): ";
    parasitic_vals.r = valid_numeric_input<double>(0.0, 1000000000.0);
    std::cout << "Enter the parasitic capacitance of"<< comp_type<<" (nF): ";
    parasitic_vals.c = valid_numeric_input<double>(0,10000000) * 1e-9;
    std::cout << "Enter the parasitic inductance of"<< comp_type<<" (mH): ";
    parasitic_vals.l = valid_numeric_input<double>(0,10000000) * 1e-3;
    return parasitic_vals;
}


void create_component(){
    section_break();
    int type;
    std::cout<<"You have decided to create a component to add to the library"<<std::endl;
    std::cout<<"What would you like to create? A resistor (1), capacitor (2) or inductor(3): ";
    int option = valid_numeric_input<int>(1,3);
    switch (option) {
        case 1:{
            double r;
            type = is_created_real("resistor");
            if(type==1){
                std::cout << "Enter the resistance of resistor (ohms): ";
                r = valid_numeric_input<double>(0.0, 1000000000.0);
                try{component_library.emplace_back(new resistor(r));
                }
                //catch any exception of bad memory allocation
                catch (std::bad_alloc) {
                    std::cerr<<"Memory allocation failed!"<<std::endl;
                    exit(1); //exit program with error code 3
                }
                break;
            }else{
                parasitic_vals vals = set_parasitic_vals("resistor");
                try{component_library.emplace_back(new para_resistor(vals.c, vals.r, vals.l));//make para
                }
                //catch any exception of bad memory allocation
                catch (std::bad_alloc) {
                    std::cerr<<"Memory allocation failed!"<<std::endl;
                    exit(1); //exit program with error code 3
                }
                break;
            }
        }
        case 2:{
            double c;
            type = is_created_real("capacitor");
            if(type==1){
                std::cout << "Enter the capacitance of capacitor (nF): ";
                c = valid_numeric_input<double>(0.0, 1000000000.0);
                try{component_library.emplace_back(new capacitor(c*1e-9));
                }
                //catch any exception of bad memory allocation
                catch (std::bad_alloc) {
                    std::cerr<<"Memory allocation failed!"<<std::endl;
                    exit(1); //exit program with error code 3
                } 
                break;
            }else{
                parasitic_vals vals = set_parasitic_vals("capacitor");
                try{component_library.emplace_back(new para_capacitor(vals.c, vals.r, vals.l));//make para
                }
                //catch any exception of bad memory allocation
                catch (std::bad_alloc) {
                    std::cerr<<"Memory allocation failed!"<<std::endl;
                    exit(1); //exit program with error code 3
                }
                break;
            }
        }
        case 3:{
            double l;
            type = is_created_real("inductor");
            if(type==1){
                std::cout << "Enter the inductance of inductor (mH): ";
                l = valid_numeric_input<double>(0.0, 1000000000.0);
                try{component_library.emplace_back(new inductor(l*1e-3)); 
                }
                //catch any exception of bad memory allocation
                catch (std::bad_alloc) {
                    std::cerr<<"Memory allocation failed!"<<std::endl;
                    exit(1); //exit program with error code 3
                }
                break;
            }else{
                parasitic_vals vals = set_parasitic_vals("inductor");
                try{component_library.emplace_back(new para_inductor(vals.c, vals.r, vals.l));//make para
                }
                //catch any exception of bad memory allocation
                catch (std::bad_alloc) {
                    std::cerr<<"Memory allocation failed!"<<std::endl;
                    exit(1); //exit program with error code 3
                }
                break;
            }
        }
    }
}

void delete_component(){
    section_break();
    if (component_library.size()==0){
        std::cout<<"You have no components to delete"<<std::endl;
        return;
    }
    int choice;
    std::cout << "Enter which number component you wish to delete: " << std::endl;
    choice = valid_numeric_input<int>(1,component_library.size()); choice-=1;    
    const auto& ptr = component_library[choice];
    std::cout<<"ERASING COMPONENT: \n"; ptr->basic_details(); 
    component_library.erase(component_library.begin()+choice);
}

void view_library(){
    for (size_t i = 0; i < component_library.size(); i++) {
    const auto& ptr = component_library[i];
    std::cout<<"Component "<< i+1<<": "<<std::endl;
    ptr->basic_details();
    }
}

//*************** NON MEMBER FUNCTIONS FOR THE MAKING A COMPONENT***********

void select_component(){
    std::cout << "Select component "<< (user_circuit->components_in_circuit()+1)<<" in circuit from component library\n"
                 "Input by typing the component number: ";
    int circuit_comp_in = valid_numeric_input<int>(1, component_library.size());
    user_circuit->add_circ_components(component_library[circuit_comp_in - 1]);
}

//to add multiple components in series
void series_multiple(){
    section_break();
    std::cout<<"ADDING IN SERIES"<<std::endl;
    std::cout<<"How many components do you want to add in series: ";
    int series_num = valid_numeric_input<int>(1, 20);
    for(int i=0; i<series_num; i++){
        select_component();
        user_circuit->add_series(user_circuit->last_x_in_components(1)[0]);
    }
}

//to add multiple components in parallel
//so have a branch with x components to add
void parallel_multiple(){
    section_break();
    std::cout<<"ADDING IN PARALLEL"<<std::endl;
    std::complex<double> impedence_branch(0,0);
    std::string text_desc="";
    std::cout<<"How many components do you want to add in parallel: ";
    int series_num = valid_numeric_input<int>(1, 20);
    for(int i=0; i<series_num; i++){
        select_component();
        if(i==0){
            text_desc = "[" + user_circuit->last_x_in_components(1)[0]->get_name() + "]";
        } else{text_desc = "["+text_desc+"]" + "-[" + user_circuit->last_x_in_components(1)[0]->get_name() + "]";}
        impedence_branch+= user_circuit->last_x_in_components(1)[0]->get_impedance();
    }
    try{
    std::shared_ptr<resistor> virtual_component(new resistor());//make a virtual component with impedence of branch
    virtual_component->set_impedance(impedence_branch);
    virtual_component->set_name(text_desc);
    user_circuit->add_parallel(virtual_component);
    }
    //catch any exception of bad memory allocation
	catch (std::bad_alloc) {
		std::cerr<<"Memory allocation failed!"<<std::endl;
		exit(1); //exit program with error code 3
	}

}

//to save circuit to a file
void save_circuit(){
    std::string input;
    std::regex pattern("[A-Za-z0-9_]+");
    std::cout<<"What would you like to name your file";
    while(!std::regex_match(input, pattern)) {
        std::cout << "Enter a string of letters, numbers and underscores only: ";
        std::getline(std::cin, input);
    }
    input += ".txt"; 
    try{
    std::ofstream output_file(input, std::ios::out);
    if (output_file.is_open()) {
        output_file << user_circuit->info();
        output_file.close();
        std::cout << "File saved successfully!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2)); //to see message
    } else {
        std::cerr << "Error opening output file!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    } catch (const std::exception& e) { //catches any unthought errors that may occur
    std::cerr << "Exception: " << e.what() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    }   
}

//to add a embedded circuit
//this func provides a menu for this
std::shared_ptr<cir::circuit> embedded(){
    section_break();
    std::cout<<"************CREATING EMBEDDED*************"<<std::endl;
    try{std::shared_ptr<cir::circuit> embed_circuit(new cir::circuit);
        int option;
    bool run = true;
    embed_circuit->set_frequency(user_circuit->get_frequency());
    std::cout << "Select component "<< (embed_circuit->components_in_circuit()+1)<<" in embedded circuit from component library\n"
                 "Input by typing the component number: ";
    int circuit_comp_in = valid_numeric_input<int>(1, component_library.size());
    embed_circuit->add_circ_components(component_library[circuit_comp_in - 1]);
    while(run){
    section_break();
    std::cout<<"What would you like to do to your embedded circuit\n"
                "1) Add a component in series \n"
                "2) Add a component in parallel\n"
                "3) Print embedded circuit so far \n"
                "4) Finish embedded circuit"<<std::endl;
    std::cout<<"Enter which option you would like: ";
    option = valid_numeric_input<int>(1,4);
    switch (option) {
        case 1:
            section_break();
            std::cout<<"ADDING IN SERIES"<<std::endl;
            select_component();
            embed_circuit->add_series(embed_circuit->last_x_in_components(1)[0]);
            break;
        case 2:
            section_break();
            std::cout<<"ADDING IN PARALLEL"<<std::endl;
            select_component();
            embed_circuit->add_parallel(embed_circuit->last_x_in_components(1)[0]);
            embed_circuit->info();
            break;
        case 3:
            section_break();
            std::cout<<"******************PRINTING CIRCUIT******************"<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout<<embed_circuit->info()<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
            break;
        case 4:
            run = false;
            break;
        }
    }
    return embed_circuit;
    }
    //catch any exception of bad memory allocation
	catch (std::bad_alloc) {
		std::cerr<<"Memory allocation failed!"<<std::endl;
		exit(1); //exit program with error code 3
	}
}

void menu_circuits(){
    int option;
    bool run = true;
    while(run){
    section_break();
    std::cout<<"What would you like to do to your circuit\n"
                "1) Add a component in series \n"
                "2) Add a component in parallel\n"
                "3) Add multiple components in series\n"
                "4) Add multiple components in parallel\n"
                "5) Add embedded circuit in series\n"
                "6) Add embedded circuit in parallel\n"
                "7) Print circuit so far \n"
                "8) Print component library \n"
                "9) Save circuit to file \n"
                "10) Return to main menu"<<std::endl;
    std::cout<<"Enter which option you would like: ";
    option = valid_numeric_input<int>(1,10);
    switch (option) {
        case 1:
            section_break();
            std::cout<<"ADDING IN SERIES"<<std::endl;
            select_component();
            user_circuit->add_series(user_circuit->last_x_in_components(1)[0]);
            break;
        case 2:
            section_break();
            std::cout<<"ADDING IN PARALLEL"<<std::endl;
            select_component();
            user_circuit->add_parallel(user_circuit->last_x_in_components(1)[0]);
            user_circuit->info();
            break;
        case 3:
            section_break();
            series_multiple();
            break;
        case 4:
            section_break();
            parallel_multiple();
            break;
        case 5:{
            std::shared_ptr<cir::circuit> created_em = embedded();
            user_circuit->add_series(created_em);
            break;
        }
        case 6:{ 
            std::shared_ptr<cir::circuit> created_em = embedded();
            user_circuit->add_parallel(created_em);
            break;
        }
        case 7:
            section_break();
            std::cout<<"*****************PRINTING CIRCUIT*******************"<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout<<user_circuit->info()<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(4));
            break;
        case 8:
            view_library();
            break;
        case 9:
            section_break();
            save_circuit();
            break;
        case 10:
            run=false;
            break;
        }
    }
}

//to create a new circuit
void create_circuit(){
    //set up circuit power supply
	double frequency{0}; double voltage{0}; int circ_number_components{0};
	std::cout<<"Enter frequency is the power supply (in Hertz): ";
	frequency = valid_numeric_input<double>(0.000000000001, 1000000000000000000);
	std::cout << "Enter voltage is the power supply (in Volts): ";
	voltage = valid_numeric_input<double>(0.000000000001, 1000000000000000000);
    try{user_circuit.reset(new cir::circuit(voltage, frequency));
    }
    //catch any exception of bad memory allocation
	catch (std::bad_alloc) {
		std::cerr<<"Memory allocation failed!"<<std::endl;
		exit(1); //exit program with error code 3
	}
    section_break();
    std::cout << "The component library is: "<<std::endl; 
    view_library();
    section_break();
    select_component(); //sets the first component in the circuit so can add to it now
    //user_circuit->add_series(user_circuit->last_x_in_components(1)[0]);
    menu_circuits();
}

//prints main functions
void menu_1(){
    int option;
    section_break();
    std::cout<<"                   MAIN MENU                      \n";
    std::cout<<"1) Add a component to the component library\n"
                "2) Remove a component from the component library\n"
                "3) View the component library\n"
                "4) Create a new circuit\n"
                "5) Exit the program"<<std::endl;
    std::cout<<"Enter which option you would like: ";
    option = valid_numeric_input<int>(1,5);
    switch (option) {
        case 1:
            create_component();
            break;
        case 2:
            delete_component();
            break;
        case 3:
            section_break();
            if(component_library.size() == 0){
                std::cout<<"You have nothing in your component library yet!"<<std::endl;
                break;
            }
            view_library();
            break;
        case 4:
            section_break();
            if(component_library.size() == 0){
                std::cout<<"You have nothing in your component library yet!"<<std::endl;
                break;
            }
            create_circuit();
            break;
        case 5:
            //delete memory here £££
            component_library.clear();
            std::cout<<"Thank you for using this program\n"
                        "All memory used delted, pls give me good grade xx"<<std::endl;
            exit(0);
            
    }
}
