#ifndef TYPE1_HPP
#define TYPE1_HPP

#include<iostream>
#include<vector>
#include<string>
#include "Measurement.hpp"

using namespace std;

class Type1 : virtual public Measurement
{
private:
	double data, error, calibration_factor; 
	string date_stamp;
public:
	// defult constructor
	Type1() : date_stamp("Defult"), data(0), error(0), calibration_factor(0) {}
	// parameterised constructor
	Type1(string temp_date, double temp_data, double temp_error, double temp_serror) : date_stamp(temp_date), data(temp_data), error(temp_error), calibration_factor(temp_serror) {}
	// destructor
	~Type1() { cout << "Type1 destructor called" << endl; }

	// Function declarations
	double Get_Data();
	double Get_Error(); 
	double Get_Calib_Factor(); 
	string Get_Date_Stamp(); 
	void Info();
	void Set_All(double d, double e, double se); // function to set all values to whatever input to function;
};
#endif 