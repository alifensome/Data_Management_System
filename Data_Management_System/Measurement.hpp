#ifndef MEASUREMENT_HPP
#define MEASUREMENT_HPP

#include<iostream>
#include<vector>
#include<string>
using namespace std;

// Abstract base class as interface only for measurments
class Measurement
{
private:
	double data, error, calibration_factor; // variables common to all types of measurment (Type1 and Type2)
	string date_stamp;
public:
	virtual ~Measurement(){ cout << "Destroying Measurement" << endl; } // virtual Destructor
	virtual void Info() = 0; // pure virtual function   
	virtual double Get_Data() = 0; // pure virtual access function to be overriden to get data
	virtual double Get_Error() = 0; // pure virtual access function 
	virtual double Get_Calib_Factor() = 0; // pure virtual access function 
	virtual string Get_Date_Stamp() = 0; // pure virtual access function 
	virtual void Set_All(double d, double e, double se) = 0; // pure virtual to set all data values
};

#endif 