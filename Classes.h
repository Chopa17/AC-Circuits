//Classes.h by Sam Brind
//class declarations
//header guard
#ifndef PROJECT_H
#define PROJECT_H
//standard library headers
#include <cmath>
#include <complex>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
//using standard namespace
namespace std {
	//abstract base class for components
	class Component {
	protected:
		complex<double> impedance;
	public:
		//default constructor
		Component() : impedance{ 0 } {}
		//destructor
		virtual ~Component() { cout << "Destroying component..." << endl; }
		//pure virtual functions
		virtual double get_frequency() const = 0;
		virtual void set_frequency(const double f) = 0;
		virtual complex<double> get_impedance() const = 0;
		virtual double get_magnitude() const = 0;
		virtual double get_phase() const = 0;
		virtual char text_description() const = 0;
		virtual void details() const = 0;
		virtual void print() const = 0;
	};
	//derived class for resistors
	class Resistor : public Component {
	protected:
		double resistance;
	public:
		//default constructor
		Resistor() : Component() { resistance = 0; }
		//parameterised constructor
		Resistor(const double resistance_in);
		//destructor
		~Resistor() { cout << "Destroying resistor..." << endl; }
		//override virtual functions
		double get_frequency() const { return 0; }
		void set_frequency(const double f);
		complex<double> get_impedance() const;
		double get_magnitude() const;
		double get_phase() const;
		char text_description() const { return 'R'; };
		void details() const;
		void print() const;
	};
	//derived class for capacitors
	class Capacitor : public Component {
	protected:
		double capacitance;
		double frequency;
	public:
		//default constructor
		Capacitor() : Component() { capacitance = 0; frequency = 0; }
		//parameterised constructor
		Capacitor(const double capacitance_in);
		//destructor
		~Capacitor() { cout << "Destroying capacitor..." << endl; }
		//override virtual functions
		double get_frequency() const { return frequency; }
		void set_frequency(const double f);
		complex<double> get_impedance() const;
		double get_magnitude() const;
		double get_phase() const;
		char text_description() const { return 'C'; };
		void details() const;
		void print() const;
	};
	//derived class for inductors
	class Inductor : public Component {
	protected:
		double inductance;
		double frequency;
	public:
		//default constructor
		Inductor() : Component() { inductance = 0; frequency = 0; }
		//parameterised constructor
		Inductor(const double inductance_in);
		//destructor
		~Inductor() { cout << "Destroying inductor..." << endl; }
		//override virtual functions
		double get_frequency() const { return frequency; }
		void set_frequency(const double f);
		complex<double> get_impedance() const;
		double get_magnitude() const;
		double get_phase() const;
		char text_description() const { return 'L'; };
		void details() const;
		void print() const;
	};
	//derived class for real resistors
	class Real_resistor : public Resistor {
	private:
		double frequency;
		double parasitic_capacitance;
		double parasitic_inductance;
	public:
		//default constructor
		Real_resistor() : Resistor() { frequency = 0; parasitic_capacitance = 0; parasitic_inductance = 0; }
		//parameterised constructor
		Real_resistor(const double resistance_in, const double Cp_in, const double Lp_in);
		//destructor
		~Real_resistor() { cout << "Destroying real resistor..." << endl; }
		//override functions
		double get_frequency() const { return frequency; }
		void set_frequency(const double f);
		void details() const;
		void print() const;
	};
	//derived class for real capacitors
	class Real_capacitor : public Capacitor {
	private:
		double parasitic_resistance;
		double parasitic_inductance;
	public:
		//default constructor
		Real_capacitor() : Capacitor() { parasitic_resistance = 0; parasitic_inductance = 0; }
		//parameterised constructor
		Real_capacitor(const double capacitance_in, const double Rp_in, const double Lp_in);
		//destructor
		~Real_capacitor() { cout << "Destroying real capacitor..." << endl; }
		//override functions
		void set_frequency(const double f);
		void details() const;
		void print() const;
	};
	//derived class for real inductors
	class Real_inductor : public Inductor {
	private:
		double parasitic_resistance;
		double parasitic_capacitance;
	public:
		//default constructor
		Real_inductor() : Inductor() { parasitic_resistance = 0; parasitic_capacitance = 0; }
		//parameterised constructor
		Real_inductor(const double inductance_in, const double Rp_in, const double Cp_in);
		//destructor
		~Real_inductor() { cout << "Destroying real inductor..." << endl; }
		//override functions
		void set_frequency(const double f);
		void details() const;
		void print() const;
	};
	//circuit class
	class Circuit {
	private:
		vector<shared_ptr<Component>> components;
		complex <double> impedance;
		double voltage;
		double frequency;
		string text_description;
	public:
		//default constructor
		Circuit() : voltage{ 0 }, frequency{ 0 }, text_description{ "" } {}
		//parameterised constructor
		Circuit(const double voltage_in, const double frequency_in);
		//destructor
		~Circuit() { cout << "Destroying circuit..." << endl; };
		void add_series(const vector<shared_ptr<Component>> components_in);
		void add_parallel(const vector<shared_ptr<Component>> components_in);
		int component_count() const;
		void print() const;
	};
}
#endif