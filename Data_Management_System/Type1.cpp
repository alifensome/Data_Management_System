#include<iostream>
#include<vector>
#include<string>
#include "Type1.hpp"

using namespace std;
// function definitions
double Type1::Get_Data(){ return data; }
double Type1::Get_Error(){ return error; }
double Type1::Get_Calib_Factor(){ return calibration_factor; }
string Type1::Get_Date_Stamp(){ return date_stamp; }
void Type1::Info(){
	cout << "Type1 date: " << date_stamp << " data: " << data << "+/-" << error << " calibration factor: " << calibration_factor << endl;
}
void Type1::Set_All(double d, double e, double se){ // function to set all values to whatever input to function
	data = d;
	error = e;
	calibration_factor = se;
};