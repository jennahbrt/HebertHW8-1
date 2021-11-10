/* control_GPIO.cpp
 * Created for 11/11/21 by Jenna Hebert for homework 8
 *
 * Program takes three command line arguments:
 * 1. GPIO # for output
 * 2. hi or low 
 * 3. GPIO # for input
 * */

///////////////////HEADER//////////////////
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;
using std::ofstream;
#define GPIO_PATH "/sys/class/gpio/"
//////////////////////////////////////////
////////////FUNCTIONS////////////////////
string name(string pin){
 ostringstream p;
 p << "gpio" << pin;
 string s = string(p.str());
 string path = GPIO_PATH +s+"/";
 return path;
}


int setDirection(string path, string direction){
  ofstream file;
  file.open((path + "direction").c_str());
    if(!file.is_open()){
	cout << "GPIO: failed to open file" <<endl;
       	return -2;
    }
  file << direction;
  file.close();
  return 0;
}

int setOutput(string path,int val){
  ofstream file;
  file.open((path + "value").c_str());
   if(!file.is_open()){
	cout << "GPIO: failed to open file" <<endl;
	return -12;
	}
 file << to_string(val);
 file.close();
 return 0;
}

 string readVal(string path){
  ifstream file;
  file.open((path + "value").c_str());
     if(!file.is_open()){
	cout << "GPIO: failed to open file" <<endl;
	return "12";
	}
    string input;
    getline(file,input);
   file.close();
   return input;}

//////////////////////////////////////////
int main(int argc, char* argv[]){
 if(argc!=4){
   cout << "Usage is: control GPIO ";
   cout << "gpio_number state gpio-number" << endl;
   cout << "gpio_number: GPIO number to control" << endl;
   cout << "state: hi or low" << endl;
   return 2;
  }
 string out(argv[1]);
 string state(argv[2]);
 string in(argv[3]);
 int value;
  if(state == "hi"){
          value =1;}
  else if(state == "low"){
          value =0;}
  else{
           cout << "invalid command" << endl;}

 //make names 
 string output_path=name(out);
 //cout << output_path << endl;
 string input_path=name(in);

 //set direction 
 setDirection(output_path, "out");
 setDirection(input_path, "in");

//set output 
 setOutput(output_path, value);
//read input 


string val;
val = readVal(input_path);
cout << val << endl;


}
