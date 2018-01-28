//Classes.cpp by Sam Brind
//class member function definitions
#include "Classes.h" //include header file
//use standard namespace
namespace std {
	//declare constant value for pi
	const double pi = acos(-1.0);
	//function to validate for a positive double
	void positive_double(const double double_in, const string double_name) {
		//double must be greater than zero
		if (double_in <= 0) {
			cout << double_name << " must be greater than zero to construct component!" << endl;
			exit(1); //exit program with error code 1
		}
	}
	//component class member functions
	//parameterised constructors
	Resistor::Resistor(const double resistance_in) {
		positive_double(resistance_in, "Resistance");
		resistance = resistance_in;
		impedance = resistance; //set impedance, Z = R
	}
	Capacitor::Capacitor(const double capacitance_in) {
		positive_double(capacitance_in, "Capacitance");
		capacitance = capacitance_in;
	}
	Inductor::Inductor(const double inductance_in) {
		positive_double(inductance_in, "Inductance");
		inductance = inductance_in;
	}
	Real_resistor::Real_resistor(const double resistance_in, const double Cp_in, const double Lp_in) : Resistor(resistance_in) {
		positive_double(Cp_in, "Parasitic_capacitance");
		positive_double(Lp_in, "Parasitic_inductance");
		parasitic_capacitance = Cp_in;
		parasitic_inductance = Lp_in;
	}
	Real_capacitor::Real_capacitor(const double capacitance_in, const double Rp_in, const double Lp_in) : Capacitor(capacitance_in) {
		positive_double(Rp_in, "Parasitic_resistance");
		positive_double(Lp_in, "Parasitic inductance");
		parasitic_resistance = Rp_in;
		parasitic_inductance = Lp_in;
	}
	Real_inductor::Real_inductor(const double inductance_in, const double Rp_in, const double Cp_in) : Inductor(inductance_in) {
		positive_double(Rp_in, "Parasitic_resistance");
		positive_double(Cp_in, "Parasitic capacitance");
		parasitic_resistance = Rp_in;
		parasitic_capacitance = Cp_in;
	}
	//set frequency functions
	void Resistor::set_frequency(const double f) {
		//do nothing
	}
	void Capacitor::set_frequency(const double f) {
		frequency = 2 * pi*f; //w = 2pi*f
		//set impedance
		complex<double> Z(0, -1 / (frequency*capacitance)); //Z = -i/wC
		impedance = Z;
	}
	void Inductor::set_frequency(const double f) {
		frequency = 2 * pi*f; //w = 2pi*f
		//set impedance
		complex<double> Z(0, frequency*inductance); //Z = iwL	
		impedance = Z;
	}
	void Real_resistor::set_frequency(const double f) {
		frequency = 2 * pi*f; //w =2pi*f
		//set impedance
		complex<double> top(resistance, frequency*parasitic_inductance);
		complex<double> bottom(1 - frequency*frequency*parasitic_capacitance*parasitic_inductance, frequency*resistance*parasitic_capacitance);
		complex<double> Z = top / bottom; //Z = R + iwLp / (1 - w^2CpLp) + iwRCp
		impedance = Z;
	}
	void Real_capacitor::set_frequency(const double f) {
		frequency = 2 * pi*f; //w =2pi*f
		//set impedance
		complex<double> Z(parasitic_resistance, frequency*parasitic_inductance - 1 / (frequency*capacitance)); // Z = Rp + i(wLp - 1/wC)
		impedance = Z;
	}
	void Real_inductor::set_frequency(const double f) {
		frequency = 2 * pi*f; //w =2pi*f
		//set impedance
		complex<double> top(parasitic_resistance, frequency*inductance);
		complex<double> bottom(1 - frequency*frequency*parasitic_capacitance*inductance, frequency*parasitic_resistance*parasitic_capacitance);
		complex<double> Z = top / bottom; //Z = Rp + iwL / (1 - w^2CpL) + iwRpCp
		impedance = Z;
	}
	//get impedance functions
	complex<double> Resistor::get_impedance() const {
		return impedance;
	}
	complex<double> Capacitor::get_impedance() const {
		return impedance;
	}
	complex<double> Inductor::get_impedance() const {
		return impedance;
	}
	//get magnitude functions
	double Resistor::get_magnitude() const {
		return abs(impedance); //|Z|
	}
	double Capacitor::get_magnitude() const {
		return abs(impedance);
	}
	double Inductor::get_magnitude() const {
		return abs(impedance);
	}
	//get phase functions
	double Resistor::get_phase() const {
		return arg(impedance); //arg(Z)
	}
	double Capacitor::get_phase() const {
		return arg(impedance);
	}
	double Inductor::get_phase() const {
		return arg(impedance);
	}
	//details functions (print a short one-line summary of the component)
	void Resistor::details() const {
		cout << resistance << " Ohm-Resistor" << endl;
	}
	void Capacitor::details() const {
		cout << capacitance << "F-Capacitor" << endl;
	}
	void Inductor::details() const {
		cout << inductance << "H-Inductor" << endl;
	}
	void Real_resistor::details() const {
		cout << resistance << " Ohm-Resistor with " << parasitic_capacitance << "F and " << parasitic_inductance << "H parasitic effects" << endl;
	}
	void Real_capacitor::details() const {
		cout << capacitance << "F-Capacitor with " << parasitic_resistance << " Ohm and " << parasitic_inductance << "H parasitic effects" << endl;
	}
	void Real_inductor::details() const {
		cout << inductance << "H-Inductor with " << parasitic_resistance << " Ohm and " << parasitic_capacitance << "F parasitic effects" << endl;
	}
	//print functions (print details and impedance)
	void Resistor::print() const {
		//print resistor details
		details();
		cout << "	Impedance:" << endl;
		cout << "		Magnitude: " << get_magnitude() << " Ohms" << endl;
		cout << "		phase shift: " << get_phase() << " rads" << endl;
	}
	void Capacitor::print() const {
		//print capacitor details
		details();
		cout << "	Impedance:" << endl;
		cout << "		Magnitude: " << get_magnitude() << " Ohms" << endl;
		cout << "		phase shift: " << get_phase() << " rads" << endl;
	}
	void Inductor::print() const {
		//print inductor details
		details();
		cout << "	Impedance:" << endl;
		cout << "		Magnitude: " << get_magnitude() << " Ohms" << endl;
		cout << "		phase shift: " << get_phase() << " rads" << endl;
	}
	void Real_resistor::print() const {
		//print real resistor details
		details();
		cout << "	Impedance:" << endl;
		cout << "		Magnitude: " << get_magnitude() << " Ohms" << endl;
		cout << "		phase shift: " << get_phase() << " rads" << endl;
	}
	void Real_capacitor::print() const {
		//print real capacitor details
		details();
		cout << "	Impedance:" << endl;
		cout << "		Magnitude: " << get_magnitude() << " Ohms" << endl;
		cout << "		phase shift: " << get_phase() << " rads" << endl;
	}
	void Real_inductor::print() const {
		//print real inductor details
		details();
		cout << "	Impedance:" << endl;
		cout << "		Magnitude: " << get_magnitude() << " Ohms" << endl;
		cout << "		phase shift: " << get_phase() << " rads" << endl;
	}
	//circuit class member functions
	//parameterised constructor
	Circuit::Circuit(const double voltage_in, const double frequency_in) {
		//validate V,f values
		if (voltage_in <= 0 || frequency_in <= 0) {
			cout << "Voltage and frequency must be greater than zero to construct an AC circuit!" << endl;
			exit(2); //exit program with error code 2
		}
		//set V and f
		voltage = voltage_in;
		frequency = frequency_in;
		//initialise text description as blank
		text_description = "";
	}
	//add multiple components in series
	void Circuit::add_series(const vector<shared_ptr<Component>> components_in) {
		//iterate over components
		for (auto iterator{ components_in.begin() }; iterator != components_in.end(); iterator++) {
			//set the component frequency
			(*iterator)->set_frequency(frequency);
			//Z = Z1 + Z2
			impedance += (*iterator)->get_impedance();
			//add component pointer to circuit components vector
			components.push_back(*iterator);
			//add component to circuit text
			text_description += (*iterator)->text_description();
		}
	}
	//add multiple components in parrallel
	void Circuit::add_parallel(const vector<shared_ptr<Component>> components_in) {
		//declare variables to store details of components_in connected in a line
		complex<double> line_impedance(0, 0); string line_text{ "" };
		//iterate over components
		for (auto iterator{ components_in.begin() }; iterator != components_in.end(); iterator++) {
			//set the component frequency 
			(*iterator)->set_frequency(frequency);
			//sum component impedance and circuit text in series
			line_impedance += (*iterator)->get_impedance();
			line_text += (*iterator)->text_description();
			//add component pointer to circuit components vector
			components.push_back(*iterator);
		}
		//add line of impedance and circuit text to circuit in parallel
		impedance = pow(pow(impedance, -1) + pow(line_impedance, -1), -1); //Z = (1/Z1 + 1/Z2)^-1
		text_description += "\n" + line_text;
	}
	//function to return no of components
	int Circuit::component_count() const {
		return components.size(); //length of components vector
	}
	//print circuit function
	void Circuit::print() const {
		cout << "Circuit:" << endl;
		cout << "	Frequency: " << frequency << "Hz" << endl;
		//print circuit impedance
		cout << "	Circuit impedance:" << endl;
		cout << "		Magnitude: " << abs(impedance) << " Ohms" << endl;
		cout << "		phase shift: " << arg(impedance) << " rads" << endl;
		//circuit voltage and current
		cout << "	Voltage: " << voltage << "V" << endl;
		cout << "	Current: " << voltage / abs(impedance) << "A" << endl;
		cout << "		Lags voltage by " << arg(impedance) << " rads" << endl;
		//print component impedances
		cout << "	Component impedances:" << endl;
		//iterate over components vector
		for (auto iterator{ components.begin() }; iterator != components.end(); iterator++) {
			cout << "	";
			(*iterator)->print(); //print component details
		}
		//print circuit diagram
		cout << "	Circuit diagram:" << endl;
		int lines{ 0 }, length{ 0 }, line_length{ 0 }; string line;
		stringstream text_stream;
		text_stream << text_description; //read circuit text into a string stream
	    //count the no of \n to determine the no of lines
		lines = count(text_description.begin(), text_description.end(), '\n') + 1;
		//determine the length of the longest line
		for (int i{ 0 }; i < lines; i++) {
			getline(text_stream, line); //read a line
			line_length = line.length();
			if (line_length > length) { length = line_length; } //check line length
		}
		//adjust line length for wires e.g.-R-R-, L = 2L+1
		length += (length + 1);
		//reset stringstream back to the beginning
		text_stream.seekg(0, text_stream.beg);
		//print a line at a time
		for (int i{ 0 }; i < lines; i++) {
			getline(text_stream, line); //read a line
			line_length = line.length();
			unsigned int scale = (unsigned int)round(length / pow(2, line_length)) + 1; //declare a scale for line spacing, round(L/2^l) + 1
			if (line.length() == (length - 1) / 2) { scale = 1; } //check if this line is the longest, then scale must be 1
			stringstream current_line;
			current_line << line; //read the current line into a stringstream
			//check if its the 1st line
			if (i == 0) {
				cout << "		V-"; //print the power supply
			} else {
				//print power supply connections
				//check if its inbetween 1st and last line
				if (i != 0 && i != lines - 1) { cout << "		| "; }
				//check if its the last line
				if (i == lines - 1) { cout << "		--"; }
			}
			//loop through line
			for (int j{ 0 }; j < line_length; j++) {
				//print a scale no of wires
				cout << string(scale, '-');
				char component;
				//read a component character from the line stream
				current_line >> component;
				//print component
				cout << component;
			}
			//add enough wires to fill remaining space
			cout << string(length + 1 - line_length*(scale + 1), '-');
			cout << "-" << endl;
			//if not on the last line of a multiple line diagram or any single line diagram
			if (i != lines - 1 || lines == 1) {
				//print parallel connection
				cout << "		| |" << string(length, ' ') << "|" << endl;
			}
			//for a single line need to add remaining wires to finish circuit
			if (lines == 1) {
				cout << "		--" << string(length + 2, '-') << endl;
			}
		}
		cout << endl;
	}
}