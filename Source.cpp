// Data_Mangement_System
// An experimental data management systemDesign and apply a class hierarchy for storing experimental data.
// Alastair Fensome C++ project 20.04.2017

#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include <ctime>
#include <time.h>
#include<fstream>
#include<istream>
#include <random>
#include <algorithm> 

#include "Measurement.hpp"
#include "Type1.hpp"
#include "Type2.hpp"

using namespace std;

// Function declarations
int Menu();
string Get_Date_Time();
double Random_Number(double mean, double std);
template <typename T, typename T2> void Enter_Data_File(vector<T> &v1);
template <typename T, typename T2> void Enter_Data_Manually(vector<T> &v1);
template <typename T, typename T2> void Weighted_Mean(vector<T> &v1, string type);
template <typename T, typename T2> void Artificial_Data(vector<T> &v1);
template <typename T, typename T2> void Save_Data(vector<T> &v1,string name);
template <typename T> void Print_Data(vector<T> &v1);
template <typename T> void Clear_Data(vector<T> &v1);

const int divide_0_flag(-1); // flag called if ever in position where may divide by 0
const int memory_flag(-1);

int main()
{
	cout << Get_Date_Time() << endl; // Print the time and date 
	// Declare and initiate variables
	vector<Type1*> T1_vector;// Vectors of base class pointers for type1 measurments
	vector<Type2*> T2_vector;// Vectors of base class pointers for type2 measurments
	int option; // integer to hold option choice number 

	do { // do loop while exit option is not chosen
		try{ // try block to catch errors 
			option = Menu();
			// option 1 enter data manually
			if (option == '1'){
				cout << "Please enter data for Type1 measurements." << endl;
				Enter_Data_Manually<Type1*,Type1>(T1_vector);
				cout << "Please enter data for Type2 measurements." << endl;
				Enter_Data_Manually<Type2*, Type2>(T2_vector);
			}
			// option 2 enter data from file
			if (option == '2'){
				cout << "Please enter  name of text file data for Type1 measurements." << endl;
				Enter_Data_File<Type1*, Type1>(T1_vector);
				cout << "Please enter  name of text file data for Type2 measurements." << endl;
				Enter_Data_File<Type2*, Type2>(T2_vector);
			}
			// option 3 claculate values and print results out
			if (option == '3'){
				cout << "Data for Type1 measurements:" << endl;
				Print_Data<Type1*>(T1_vector);
				cout << "Data for Type2 measurements:" << endl;
				Print_Data<Type2*>(T2_vector);
				cout << "Type1: " << endl;
				Weighted_Mean<Type1*, Type1>(T1_vector,"Type1");
				cout << "Type2: " << endl;
				Weighted_Mean<Type2*, Type2>(T2_vector,"Type2");
			}

			// option 4 clear all data
			if (option == '4'){
				Clear_Data<Type1*>(T1_vector);
				Clear_Data<Type2*>(T2_vector);
				if (T1_vector.empty() && T2_vector.empty()){
					cout << "All data has been cleared." << endl;
				}
			}
			// option 5 create artificial data
			if (option == '5'){
				cout << "Please enter values for Type1 measurements." << endl;
				Artificial_Data<Type1*, Type1>(T1_vector);
				cout << "Please enter values for Type2 measurements." << endl;
				Artificial_Data<Type2*, Type2>(T2_vector);
			}
			// option 6 save all data
			if (option == '6'){
				cout << "Saving data for Type1 measurements." << endl;
				Save_Data<Type1*, Type1>(T1_vector, "Type1.txt");
				cout << "Saving data for Type2 measurements." << endl;
				Save_Data<Type2*, Type2>(T2_vector, "Type2.txt");
			}
		}
		catch (int errorFlag) // error catching!
		{
			if (errorFlag == divide_0_flag) // divide by zero error!
			{
				cout << "Error: Can not divide by zero." << endl;
				cout << "It is recomened that you clear memory. Enter option 4 to do this now." << endl;
			}
			if (errorFlag == memory_flag) // entered too high number of measurments
			{
				cout << "Error: Too many artificail measurments input." << endl;
			}
		}

	} while (option != '7');
	// the exit option must have been chosen so now must free memory and clear vectors incase user hasnt already done it!
	Clear_Data<Type1*>(T1_vector);// Free memory for type1	
	Clear_Data<Type2*>(T2_vector);// Free memory for type2
	if (T1_vector.empty() && T2_vector.empty()){
		cout << "All data has been cleared." << endl;
	}
	return 0;
}

// FUNCTIONS
// Function to return time and data as a string
string Get_Date_Time() {
	time_t rawtime;
	time(&rawtime);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	char str[26];
	char date[26];
	asctime_s(str, sizeof str, &timeinfo); // time and date using abrivation of month and day of the week  
	strftime(date, 26, "%Y_%m_%d_%H_%M_%S", &timeinfo); // time and date in format suitable for saving year_month_date_hour_minute_second
	time_t time = std::time(nullptr);
	return date;
};
// function to print out the menu screen and check that input value is correct allowing user to choose something to do and returning the correct integer chosen.
int Menu(){
	char input;
	int option(0);
		cout << "\nChoose an option from the menu by entering the corresponding number." << endl;
	do {
		cout << "1. Enter data manually." << endl;
		cout << "2. Enter data from file." << endl;
		cout << "3. Calculate values, account for calibration factor and display results." << endl;
		cout << "4. Clear all data." << endl;
		cout << "5. Create artificial data." << endl;
		cout << "6. Save all data." << endl;
		cout << "7. Exit." << endl;
		cin >> input;
		cout << input << endl;
		if (input == '1' || input == '2' || input == '3' || input == '4' || input == '5' || input == '6' || input == '7'){
			option = input;
			cin.ignore(265, '\n');
		}
		else{
			cin.ignore(265,'\n');
			cout << "Sorry invalid input." << endl;}
	} while (option == 0);
	return option;
}
//Function to allow user to input data manually. Template function allows same function to be used for both Type1 and Type2 objects
template <typename T, typename T2> void Enter_Data_Manually(vector<T> &v1){
	string input_string;
	const string end_char("x"); // character which if entered terminates do loop
	cout << "Enter data manually is the format:\n data error calibration_factor \nEnter 'x' when finished entering data." << endl;
	do {
		double data(0), error(0), calibration_factor(0);
		getline(cin, input_string); // 

		if (input_string.compare(end_char) != 0){ // compare the srings if mystring = x the will return 0 and not exercute this section of code
			stringstream user_input(input_string); // string stream to hold what the user has entered untill it can be split up
			user_input >> data >> error >> calibration_factor; // split up the stringstream into 3 double values
			v1.push_back(new T2(Get_Date_Time(), data, error, calibration_factor));
		}
		else{ // if x is entered break the loop.
			cout << "Finished entering measurments." << endl;
			break;
		}
	} while (true);
}
//Template Function print all the data for a specific Type
template <typename T> void Print_Data(vector<T> &v1){
	// print out info for the objects in a loop
	for (size_t i{ 0 }; i < v1.size(); i++){
		v1[i]->Info();
	}
}
//Template Function to clear all the data for a specific Type
template <typename T> void Clear_Data(vector<T> &v1){
	for (auto vectorit = v1.begin();
		vectorit < v1.end();
		++vectorit)
		delete *vectorit;
	v1.clear();
}

//Function to allow user to input data manually. Template function allows same function to be used for both Type1 and Type2 objects
template <typename T, typename T2> void Enter_Data_File(vector<T> &v1){
	string date_stamp, file_name;
	double data, error, calibration_factor;
	// Open file and check if successful
	getline(cin, file_name);
	fstream myfile;
	myfile.open(file_name); // file name which we will open
	if (!myfile.good()){
		// if the file is not good error message
		cout << "Error: The file could not open correctly." << endl;
		return; // exit (returning nothing) if the file doesnt open properly
	}
	else 
	{ // file sussesfully opens so lets get the data out!
		// Find out how many lines are in the file!
		int line_number{ 0 }; // initiate a variable 
		string line; // line variable to hold string that is each line in file
		while (!myfile.eof()) {     //if not at end of file so continue reading numbers
			getline(myfile, line);
			if (line == "") continue; // if the line is empty then skip rest of loop 
			line_number++;
		}
		cout << "Number of lines in file is " << line_number << endl;
		// Read data from file, ignoring any additional bad data
		myfile.clear(); // clear the end of file marker ( and other things)
		myfile.seekg(0, ios::beg); // seek the beguining of the file
		int i{ 0 };
		int number_of_errors{ 0 };
		while (!myfile.eof()) {     //if not at end of file so continue reading numbers			
			getline(myfile, line);
			if (line == "") continue; // if the line is empty then skip rest of loop
			char character = line.at(0); // Check that the first character is a number (and not an error message) 
			if (isdigit(character)){	// if the line is made of digits 
				stringstream ss(line); // string stream to hold what the user has entered untill it can be split up
				ss >> date_stamp >> data >> error >> calibration_factor; // split up the stringstream into 3 double values
				v1.push_back(new T2(date_stamp, data, error, calibration_factor));
			}
			else { // if there is an error in the line the print the line number and ignore line
				cout << "Error found in line: " << (i) << endl;
				number_of_errors++;
				myfile.ignore(10000, '\n'); // ignore falty line until \n
			}
		}
		int Max_element_number = i; // The element number
		cout << "Number of errors = " << number_of_errors << endl;
	}
	// Close file
	myfile.close();
	if (!myfile.is_open()) {
		cout << "File closed sucessfully." << endl;
	}
	else {
		cout << "Error: The file has not been closed properly." << endl;
	}
}

//Function to allow user to input data manually. Template function allows same function to be used for both Type1 and Type2 objects
template <typename T, typename T2> void Artificial_Data(vector<T> &v1){
	string line, line2;
	double data, error, calibration_factor;
	int num_measurments{ 0 };
	cout << "The program randomly generate data around a mean with a maximum deviation from that mean.\nPlease enter the number of measurments you would like to create." << endl;
	cin >> num_measurments;
	if (num_measurments > 1000000) throw memory_flag; // exception in case of asking to allocate more that 1 million measurments 
	cout << "Please enter a value for data followed a value for error followed by a value for calibration factor.\nFor example for a measurment of 10 +/- 2 with a calibration factor of 1.5 enter \n10 2 1.5" << endl;
	cin >> data >> error >> calibration_factor; // split up into variables 
	// The next line will creat the correct number of objects using loop. The data will be generated using random number function. 
	// The mean of the data will be around the entered value and will vary randomly by the value for the error. The error will do the same but vary by half of the error.
	// The calibration factor will stay constant and is used to skew the random data so when acounted for we get correct answer which was input for mean!
	if (calibration_factor == 0) throw divide_0_flag; // exception in case of dividing by zero
	for (int i{ 0 }; i < num_measurments; i++){
		v1.push_back(new T2(Get_Date_Time(), (Random_Number(data, error) / calibration_factor), Random_Number(error, 0.5*error), calibration_factor));
	}
}

//Function to save data to .txt file
template <typename T, typename T2> void Save_Data(vector<T> &v1, string name){
	ofstream output_file;
	string file_name{ name }, name2{ Get_Date_Time() + " " + name }, name3;
	char input;
	cout << "Choose an option for file name." << endl;
	cout << "1. " << name << endl;
	cout << "2. " << name2 << endl;
	cout << "3. a name of your own choosing." << endl;
	cin >> input;
	if (input == '1'){
		file_name = name;
	}
	if (input == '2'){
		file_name = name2;
	}
	if (input == '3'){
		cout << "Please enter a name." << endl;
		cin.ignore(); // ignore the \n 
		getline(cin, file_name);
	}
	if (input != '1' && input != '2' && input != '3' ){
		cin.ignore(265, '\n'); // ignore up untill new line as input invalid
		cout << "Invalid input" << endl;
		return;
	}
	output_file.open(file_name);
	for (size_t i{ 0 }; i < v1.size(); i++){
		output_file << v1[i]->Get_Date_Stamp() << " " << v1[i]->Get_Data() << " " << v1[i]->Get_Error() << " " << v1[i]->Get_Calib_Factor() << endl;
	}
	output_file.close();// Close file
	if (!output_file.is_open()) { // check that file closed properly
		cout << "File closed sucessfully." << endl;
	}
	else { cout << "Error: The file has not been closed properly." << endl; 
	}
}
// function to compute weighted mean and weighted error on mean
template <typename T, typename T2> void Weighted_Mean(vector<T> &v1, string type){
		double weighted_mean{ 0 }, weighting{ 0 }, data, error, calibration_factor, weighted_mean_error, w;
		int i_max;
	// check there are things in the vector
	if (v1.empty()){
		cout << "Warning no data loaded." << endl;
		return;
	}
	for (size_t i{ 0 }; i < v1.size(); i++){
		data = v1[i]->Get_Data();
		error = v1[i]->Get_Error();
		w = 1 / (pow(error, 2));  // w, incramental weighting which im taking to be 1/error^2
		calibration_factor = v1[i]->Get_Calib_Factor();
		if (calibration_factor == 0) throw divide_0_flag; // exception in case of dividing by zero
		weighted_mean += (data*calibration_factor*w); // account for the calibration factor by timesing data by systemaic error then add them up
		weighting += (w); // add up incramental weightings
		i_max = i+1;
	}
	if (weighting == 0) throw divide_0_flag;// exception in case of dividing by zero
	weighted_mean_error = pow((1 / weighting), 0.5); 
	cout << "Weighted mean = " << (weighted_mean / weighting) << " +/- " << weighted_mean_error << endl;
	cout << "Number of measurments used to form mean: " << i_max << endl;
	// lets now append data into our results file for storage
	ofstream results_file; 
	results_file.open("Results.txt", ios_base::app); // open results fule for appending data onto the end of 
	if (type == "Type1"){ // if its type1 then we will give the experiment a name and date stame as a header in the txt file
		string name{ "No_Name" };
		cout << "Please name this experiment. \nThis name will be used as a title in the results text file." << endl;
		getline(cin,name);
		results_file << "\n" << name << " " << Get_Date_Time() << endl;
	}
	results_file << type << " Weighted mean = " << (weighted_mean / weighting) << " +/- " << weighted_mean_error << endl;
	results_file.close();// Close file
	if (!results_file.is_open()) { // check that file closed properly
	}
	else {
		cout << "Error: The file has not been closed properly." << endl;
	}
	return;
}

// function to return random numbers around a mean with a max deviation from the mean 
double Random_Number(double mean, double max_deviation){
	double random_num = mean + max_deviation*(2*(double)rand() / (double)RAND_MAX - 1);
	return random_num;
}
