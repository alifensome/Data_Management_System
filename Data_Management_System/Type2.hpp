#ifndef TYPE2_HPP
#define TYPE2_HPP

#include<iostream>
#include<vector>
#include<string>
#include "Measurement.hpp"

using namespace std;

class Type2 : virtual public Measurement
{
private:
	double data, error, calibration_factor;
	string date_stamp;
public:
	// defult constructor
	Type2() : date_stamp("Defult"), data(0), error(0), calibration_factor(0) {}
	// parameterised constructor
	Type2(string temp_date, double temp_data, double temp_error, double temp_serror) : date_stamp(temp_date), data(temp_data), error(temp_error), calibration_factor(temp_serror) {}
	// destructor
	~Type2() { cout << "Type2 destructor called" << endl; }
	
	// Function declrations
	double Get_Data();
	void Info();
	double Get_Error();
	double Get_Calib_Factor();
	string Get_Date_Stamp();
	void Set_All(double d, double e, double se); // function to set all values to whatever input to function
};
#endif 