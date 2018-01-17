#include <math.h>
#include <float.h>



#include <iostream>
using namespace std;
#endif



bool stringToFloat(const char input[], float& value);


bool stringToFloat(const char input[], float& value) 
{
    float maximum = FLT_MAX;
    float minimum = FLT_MIN;
    int index = 0;
    float decimal = 0;
    int counter = 0;
    int exponent = 0;
    bool negative_exp = false;
    bool has_sign = false;
    bool is_negative = false;

    while (input[index] != '.'){
        index++;

        if (input[index] == 0){
          break;
        }
    }

    if (input[0] == '+' || input[0] == '-'){
      for (int i = 1; i < index; i++){
        int digit = input[i] -'0';
        if (input[1]-'0' == 0){
          value = 0;
          break;
        }
        maximum -= digit*pow(10,(index-1-i));
        minimum -= digit*pow(10,(index-1-i));
        if (maximum <0 || minimum >0){
          return false;
        }
        if (digit >= 0 && digit <= 9){
          value += digit*pow(10,(index-1-i));
        }
        else{
          return false;
        }
      }
      if (input[0] =='-'){
        is_negative = true;
        value *= -1;
      }
    }

    else{
      for (int i =0; i<index; i++){
        int digit = input[i]-'0';
        if (input[0]-'0' == 0){
          value = 0;
          break;
        }
        maximum -= digit*pow(10,(index-1-i));
        minimum -= digit*pow(10,(index-1-i));
        if (maximum <0 || minimum >0){
          return false;
        }
        if (digit >= 0 && digit <= 9){
          value += digit*pow(10,(index-1-i));
        }
        else{
          return false;
        }
      }
    }

    if (input[index] == '.'){
      while (input[index+1] != 0 && input[index+1] != 'e' && input[index+1] != 'E'){
        int digit = input[index+1]-'0';
        if (digit >= 0 && digit <= 9){
          decimal = decimal*10 + digit;
        }
        else{
          return false;
        }
        counter++;
        index++;
      }
    }

    decimal = decimal*pow(10,-counter);
    if (value < 0 || is_negative==true){
      value -=decimal;
    }
    else{
      value += decimal;
    }

    if (input[index+1] == 'e' || input[index+1] == 'E'){
      while (input[index+2] !=0){
        if (input[index+2] == '-' || input[index+2] == '+'){
          has_sign = true;
          if (input[index+2] == '-'){
            negative_exp = true;
          }
          else{
            negative_exp = false;
          }
          int digit = input[index+3]-'0';
          if (digit >= 0 && digit <= 9){
            exponent = exponent*10 + digit;
          }
          else{
            return false;
          }
        }
        else if(has_sign == false){
          int digit = input[index+2]-'0';
          if (digit >= 0 && digit <= 9){
            exponent = exponent*10 + digit;
          }
          else{
            return false;
          }
        }
        index++;
      }
    }

    if (negative_exp == true){
      exponent *=-1;
    }

    value = value*pow(10,exponent);
    return true;
}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
//
//
int main(const int argc, const char* const argv[]) {
  
  // Some test driver code here ....
  float argv1;

  if (argc < 2) {
    cerr << "Error: Usage: " << argv[0] << " <float>" << endl;
    return -1;
  }

  if (stringToFloat(argv[1],argv1)) 
    cout << "argv[1] is a float with value: " << argv1 <<endl;
  else
    cout << "argv[1] is not a float. argv[1]: " <<argv1 << endl;
  return 0;
}

#endif