#include<iostream>
#include<vector>
#include<string>
#include "Type2.hpp"

using namespace std;
// function definitions
double Type2::Get_Data(){ return data; }
double Type2::Get_Error(){ return error; }
double Type2::Get_Calib_Factor(){ return calibration_factor; }
string Type2::Get_Date_Stamp(){ return date_stamp; }
void Type2::Info(){
	cout << "Type2 date: " << date_stamp << " data: " << data << "+/-" << error << " calibration factor: " << calibration_factor << endl;
};
void Type2::Set_All(double d, double e, double se){ // function to set all values to whatever input to function
	data = d;
	error = e;
	calibration_factor = se;
};