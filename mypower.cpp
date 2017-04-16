//Author: Christine P. Fornoles
//Subject: ICST103
//Section: N1
//mypower
//Program Specification: To create a program that would demonstrate exponentiation

//Limitations: no output when computed numerator (of the exponent) is too high
//             does not accept mixed fractions for exponent
//             does not accept fraction for base
//Accepts non-integer, improper and proper fractions for exponents
//e.g.
//5 ^ 1/4
//5.6 ^ 0.2
//-27 ^ -1/3

# include <iostream>
# include <iomanip>
# include <cstring>
# include <cstdlib>
# include <sstream> //a header file which was used in this program to convert numbers to strings
using namespace std;

void computeAns (double base1, string expo) {
     int expo_type;

     for (int i = 0; i < expo.length (); i++) {
         if (expo [i] == '.') { expo_type = 1; break; }
         else if (expo [i] == '/') { expo_type = 2; break; }
         else { expo_type = 3; }
     }

     if (expo_type == 1 || expo_type == 2) {
        string left_s, right_s, numerator_s, denominator_s, temp_str, final_str = " ";
        int z = 1, decimalCount = 0, denominator = 1, numerator, left, right, con = 0, sign = 0, den_stat = 0;
        long double ans = 1, final_ans = 0.00, temp = 1.00, expo_n, lower = 1, higher = 1;
        char left_c [50], right_c [50], numerator_c [50], denominator_c [50], final_c [50], expo_c [50];

        //processes decimal exponents and convert it to fraction [proper/improper]
        if (expo_type == 1) {
           for (int i = 0; i < expo.length (); i++) {
               if (expo [i] != '.') {
                  if (z == 1) {
                     left_s += expo [i]; //digits at the left of decimal point
                  }
                  else {
                       right_s += expo [i]; //digits at the right of decimal point
                       decimalCount++;
                  }
               }
               else {
                    z = 2;
               }
           }

           strcpy (left_c, left_s.c_str ());
           left = atoi (left_c);
           strcpy (right_c, right_s.c_str ());
           right = atoi (right_c);
           strcpy (expo_c, expo.c_str ());
           expo_n = atof (expo_c);

           for (int i = 0; i < decimalCount; i++) {
               denominator *= 10;
           }

           if (left == 0) {
              numerator = right;
              if (expo_n < 0) {
                 sign = 1;
              }
           }

           else {
                numerator = (denominator*left) + right;
           }
        }

        else if (expo_type == 2) {
             for (int i = 0; i < expo.length (); i++) {
                 if (expo [i] != '/') {
                    if (z == 1) {
                       numerator_s += expo [i];
                    }
                    else {
                         denominator_s += expo [i];
                    }
                 }
                 else {
                      z = 2;
                 }
             }

             strcpy (numerator_c, numerator_s.c_str ());
             numerator = atoi (numerator_c);
             strcpy (denominator_c, denominator_s.c_str ());
             denominator = atoi (denominator_c);
        }

        if (denominator == 0) {
           cout << "exponent is undefined" << endl;
        }

        int limit;

        if (numerator < 0) {
           numerator *= -1;
           sign = 1;
        }

        if (numerator < denominator) {
           limit = numerator;
        }

        else {
             limit = denominator;
        }

        //simplify [the decimal/proper/improper fraction]
        for (int i = 2; i <= limit; i++) { //the possible factors of both the numerator and denominator
            if (numerator % i == 0 && denominator % i == 0) {
               numerator /= i;
               denominator /= i;
               i = 1;
            }
        }

        //base raise to the numerator of the exponent
        for (int i = 0; i < numerator; i++) {
            ans *= base1;
        }

        if (base1 < 0 && numerator % 2 == 1 && denominator % 2 == 0 && denominator != 0) {
           cout << "invalid input\nit will result to an imaginary number" <<  endl;
        }

        if (ans < 0 && denominator % 2 == 1) {
           ans *= -1;
           den_stat = 1;
        }

        //finding the nth root of (the base raise to the numerator of the exponent)
        for (double c = 0; c < ans; c++) {
            double k = 1, j = c+1;

            //a loop which computes for the root [whole number]
            while (k <= denominator) {
                  lower = lower*c;
                  higher = higher*j;
                  k++;
            }

            if (lower <= ans && higher >= ans) {
               if (lower == ans) {
                  final_ans = c;
                  if (sign == 1) {
                       final_ans = 1/final_ans;
                    }
                  if (den_stat == 1) {
                     final_ans *= -1;
                  }
                  cout << final_ans << endl;
                  c = ans;
               }
               else if (higher == ans) {
                    final_ans = j;
                    if (sign == 1) {
                       final_ans = 1/final_ans;
                    }
                    if (den_stat == 1) {
                       final_ans *= -1;
                    }
                    cout << final_ans << endl;
                    c = ans;
               }
               else if (lower < ans) {
                    ostringstream convert;
                    convert << c; //convert the whole number nth root to string
                    temp_str = convert.str ();
                    temp_str += ".";

                    int y = 0;
                    while (y <= 9) {
                          for (int j = 9; j >= 0; j--) { //a loop which computes for the decimals of the root by trial and error
                              ostringstream convert1;
                              convert1 << j;
                              if (con == 2) {
                                 temp_str = final_str;
                              }

                              temp_str += convert1.str (); //concatenate the whole number to the decimal
                              strcpy (final_c, temp_str.c_str ());
                              final_ans = atof (final_c);
                              for (int i = 0; i < denominator; i++) {
                                  temp *= final_ans;
                              }

                              if (temp > ans) {
                                 if (con == 2) {
                                    final_str = " ";
                                 }

                                 for (int i = 0; i < temp_str.length () - 1; i++) {
                                     final_str += temp_str.substr (i, 1);
                                 }
                                 con = 2;
                              }
                              else if (temp < ans) {
                                   con = 2;
                                   ostringstream convert3;
                                   convert3 << final_ans;
                                   final_str = convert3.str ();

                                   if (j == 0) {
                                      final_str += ".0";
                                   }
                                   j = 0;
                              }
                              temp = 1;
                          }
                          c = ans;
                          y++;
                    }

                    if (sign == 1) {
                       final_ans = 1/final_ans;
                    }

                    if (den_stat == 1) {
                       final_ans *= -1;
                    }

                    cout << setprecision (5) << final_ans << endl;
               }
            }

            else {
                 lower = 1;
                 higher = 1;
            }
        }
     }

     else if (expo_type == 3) {
          char exponent_c [50];
          strcpy (exponent_c, expo.c_str ());
          double exponent1 = atof (exponent_c);

          double ans = 1, ans2; //initialize to 1 and not 0 because it will serve as the product [not sum]
          if (exponent1 < 0) {
             exponent1 *= -1;

             for (int i = 0; i < exponent1; i++) {
                 ans *= base1;
             }

             if (ans == 0) {
                cout << "undefined\n";
             }
             else {
                  ans2 = 1/ans;
                  cout << ans2 << " or " << "1/" << ans << endl;
             }
          }

          else {
               for (int i = 0; i < exponent1; i++) {
                   ans *= base1;
               }
               cout << ans << endl;
          }
     }
}

int main () {
    char ans;

    do {
        double base;
        string exponent_s;
        cout << "Enter the base and the exponent: ";
        cin >> base >> exponent_s;
        computeAns (base, exponent_s);
        cout << "\nAgain? ";
        cin >> ans;
    } while (ans == 'Y' || ans == 'y');

    system ("pause");
    return 0;
}
