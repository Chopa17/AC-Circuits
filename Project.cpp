//Project.cpp by Sam Brind
//computes impedance of AC circuits with arbitary numbers of components
//main program code
#include "Classes.h" //include header file
//use standard namespace
using namespace std;
//declare static variables
static int component_count{ 0 }; //count of components
static vector<shared_ptr<Component>> component_library; //library of pointers to components
static unique_ptr<Circuit> current_circuit; //pointer to the current user circuit
//function to get a user input that is a single character from accepted values in values string
char char_validation(string value, string values) {
	char input; string input_string; string rest{ "" }; int start;
	getline(cin, input_string); //take a line of user input
	start = input_string.find_first_not_of(" "); //find first character
    //if there are character other than whitespace
	if (start != string::npos) {
		input = tolower(input_string[start]); //set the first character as lowercase input
		rest = input_string.substr(start + 1); //string after character
	}
	//loop while there is a blank line, char other than allowed values and any trailing characters
	while (start == string::npos || values.find(input) == string::npos || rest.find_first_not_of(" ") != string::npos) {
		cerr << "Input isn't one of " << value << "!" << endl;
		getline(cin, input_string); //take a line of user input
		start = input_string.find_first_not_of(" "); //find first character
		//if there are character other than whitespace
		if (start != string::npos) {
			input = tolower(input_string[start]);; //set the first character as lowercase input
			rest = input_string.substr(start + 1); //string after character
		}
	}
	//return valid char
	return input;
}
//function to get a user input that is a positive double in the range [min,max]
double double_validation(string value, double min, double max) {
	double input;
	cin >> input; //try and take input double
	//loop while input fails or has trailing characters or is negative/zero or is out of range
	while (cin.fail() || cin.peek() != '\n' || input <= 0 || input < min || input > max) {
		//check if input was out of range
		if (input > 0 && input < min || input > max) {
			cerr << value << " is invalid, please enter a number between " << min << " and " << max << "!" << endl;
		} else {
			//number was invalid
			cerr << value << " must be a positive number!" << endl;
		}
		cin.clear(); //clear cin fail bit
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore characters in buffer up to new line
		cin >> input; //take a new input
	}
	cin.clear(); //clear cin fail bit
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore characters in buffer up to new line
	//return valid double
	return input;
}
//function to get a user input that is a positive integer
int int_validation(string value) {
	int input;
	cin >> input; //try and take input integer
	//loop while input fails or has trailing characters or negative
	while (cin.fail() || cin.peek() != '\n' || input < 0) {
		cerr << value << " must be a positive number!" << endl;
		cin.clear(); //clear cin fail bit
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore characters in buffer up to new line
		cin >> input; //take a new input
	}
	cin.clear(); //clear cin fail bit
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore characters in buffer up to new line
	//return valid integer
	return input;
}
//function to create a component
void create_component() {
	char type, ideal; double property{0}, parasitic, parasitic_2;
	//get type of component
	cout << "What type of component do you want to create ?\n(Resisitor[R]/[Capacitor[C]/Inductor[L])" << endl;
	type = char_validation("R/C/L", "rcl");
	//get whether its real or ideal component
	cout << "Is the component ideal or real (ie. including parasitic effects)?\n(Ideal[I]/Real[R])" << endl;
	ideal = char_validation("I/R", "ir");
	//get valid numerical property e.g. resistance and push back a component pointer to component library
	if (type == 'r') {
		cout << "What is the resistance (in Ohms)?" << endl;
		property = double_validation("Resistance", 1e-09, 1e11);
		if (ideal == 'i') {
			//construct an ideal resistor
			component_library.emplace_back(new Resistor(property));
		} else {
			//get parasitic values
			cout << "What is the parasitic capacitance (in Farads)?" << endl;
			parasitic = double_validation("Parasatic capacitance", 0, 1e-11);
			cout << "What is the parasitic inductance (in Henries)?" << endl;
			parasitic_2 = double_validation("Parasatic inductance", 0, 1e-08);
			//construct non ideal resistor
			component_library.emplace_back(new Real_resistor(property, parasitic, parasitic_2));
		}
	}
	if (type == 'c') {
		cout << "What is the capacitance (in Farads)?" << endl;
		property = double_validation("Capacitance", 1e-15, 1e04);
		if (ideal == 'i') {
			//construct an ideal capacitor
			component_library.emplace_back(new Capacitor(property));
		} else {
			//get parasitic values
			cout << "What is the parasitic resistance (in Ohms)?" << endl;
			parasitic = double_validation("Parasatic resistance", 0, 1);
			cout << "What is the parasitic inductance (in Henries)?" << endl;
			parasitic_2 = double_validation("Parasatic inductance", 0, 1e-08);
			//construct non ideal capacitor
			component_library.emplace_back(new Real_capacitor(property, parasitic, parasitic_2));
		}
	}
	if (type == 'l') {
		cout << "What is the inductance (in Henries)?" << endl;
		property = double_validation("Inductance", 1e-13, 1e04);
		if (ideal == 'i') {
			//construct an ideal inductor
			component_library.emplace_back(new Inductor(property));
		} else {
			//get parasitic values
			cout << "What is the parasitic resistance (in Ohms)?" << endl;
			parasitic = double_validation("Parasatic resistance", 0, 1);
			cout << "What is the parasitic capacitance (in Farads)?" << endl;
			parasitic_2 = double_validation("Parasatic capacitance", 0, 1e-11);
			//construct non ideal inductor
			component_library.emplace_back(new Real_inductor(property, parasitic, parasitic_2));
		}
	}
	component_count += 1; //increment count of components
}
//fucntion to print component library
void print_library() {
	cout << "Component library:" << endl;
	cout << "Pointer - Component" << endl;
	//check there are components
	if (component_count != 0) {
		//iterate over library
		for (auto iterator{ component_library.begin() }; iterator != component_library.end(); iterator++) {
			cout << distance(component_library.begin(), iterator) + 1 << " - "; //print position in library
			(*iterator)->details(); //print component details
		}
	}
}
//function to get user input set of pointers to component library
vector<shared_ptr<Component>> get_pointers() {
	vector<shared_ptr<Component>> components;
	int pointer;
	//loop indefinitely
	while (true) {
		pointer = int_validation("Pointer"); //take a valid user integer
		//break out of loop if user enters 0
		if (pointer == 0) { break; }
		//check that the number is in the component library range
		if (pointer > component_count) {
			cerr << "Pointer is not within the component library!" << endl;
		} else {
			//pointer is within component library
			components.push_back(component_library[pointer - 1]); //add component pointer to vector
		}
	}
	//return a vector of valid pointers
	return components;
}
//function to add components in series
void add_component_series() {
	cout << "Which component(s) do you want to add in series?\n (enter 0 to stop input)" << endl;
	//add user input pointed components in series
	current_circuit->add_series(get_pointers());
}
//function to add components in parallel
void add_component_parallel() {
	cout << "Which component(s) do you want to add in parallel?\n (enter 0 to stop input)" << endl;
	//add user input pointed components in parallel
	current_circuit->add_parallel(get_pointers());
}
//declare a circuit function, so it can be called by the menu function and vice versa
void circuit();
//declare menu function
void menu() {
	//loop indefinitely
	while (true) {
		//print the menu
		cout << "What do you want to do?" << endl;
		cout << "	c - create a component" << endl;
		cout << "	s - add component(s) in series" << endl;
		cout << "	p - add component(s) in parallel" << endl;
		cout << "	d - print circuit details" << endl;
		cout << "	n - delete current circuit and start a new one" << endl;
		cout << "	e - exit the program" << endl;
		char input;
		input = char_validation("c/s/p/d/n/e", "cspdne"); //take valid user input
		switch (input) {
		//create a component
		case 'c':
			//run create component function
			create_component();
			break;
		//add components in series
		case 's':
			//check if the user hasn't created any components
			if (component_count == 0) {
				cerr << "Component library is empty, please create some components!" << endl;
				break;
			}
			//print component library
			print_library();
			//run add components in series function
			add_component_series();
			break;
		//add components in parallel
		case 'p':
			//check components are there for a parallel connection
			if (current_circuit->component_count() == 0) {
				cerr << "There must be serially connected components before connecting any components in parallel!" << endl;
				break;
			}
			//print component library
			print_library();
			//run add components in parrallel function
			add_component_parallel();
			break;
	    //print circuit details
		case 'd':
			//check components are there to be printed
			if (current_circuit->component_count() == 0) {
				cerr << "Circuit currently contains no components!" << endl;
				break;
			}
			//print the circuit details
			current_circuit->print();
			break;
		//delete current circuit and start a new one
		case 'n':
			//remove current_circuit pointer
			current_circuit = nullptr;
			//call circuit function
			circuit();
			break;
	    //exit program
		case 'e':
			component_library.clear(); //clear the component library vector
			exit(0); //exit the program without an error code
			break;
		default:
			break;
		}
	}
}
//declare function to set up a new circuit
void circuit() {
	//set up circuit power supply
	double frequency{ 0 }, voltage{ 0 };
	cout << "What frequency is the power supply (in Hertz)?" << endl;
	frequency = double_validation("Frequency", 0.01, 1e09);
	cout << "What voltage is the power supply (in Volts)?" << endl;
	voltage = double_validation("Voltage", 1e-06, 1e08);
	current_circuit.reset(new Circuit(voltage, frequency)); //create circuit and assign to static pointer
	menu(); //run menu function
}
//declare main program function
int main() {
	try {
		cout << "AC circuits by Sam Brind" << endl;
		//run circuit function
		circuit();
	}
	//catch any exception of bad memory allocation
	catch (bad_alloc) {
		cerr << "Memory allocation failed!" << endl;
		exit(3); //exit program with error code 3
	}
	return 0;
}