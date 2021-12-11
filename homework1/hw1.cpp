#include <iostream>
#include <valarray>
#include <cmath>
#include <fstream>


float x_n, y_n;
float x_0, y_0;
float max_dl = 0;
float max_dr = 0;
float max_l[2] = {0, 0};
float max_r[2] = {0, 0};


float location() {

    float k_p = x_n*y_0 - x_0*y_n;

    return k_p;
}

float val_d(){

    float d = abs (x_n*y_0 - x_0*y_n) / sqrt(pow(x_n,2) + pow(y_n,2));

    return d;
}

int main() {
    std::ifstream file("in.txt");
    file >> x_n >> y_n;
    while (!file.eof()) {
        file >> x_0 >> y_0;

        float k_p = location();
        float d = val_d();

        if (k_p == 0) {
            d = 0;
        } else if (k_p > 0) {

            if (d >= max_dl) {
                max_dl = d;
                max_l[0] = x_0;
                max_l[1] = y_0;
            }
        } else {
            if (d >= max_dr) {
                max_dr = d;
                max_r[0] = x_0;
                max_r[1] = y_0;
            }
        }
    }
    file.close();
    
    std::cout << "Leftmost: " << max_l[0] << " " << max_l[1] << std::endl;
    std::cout << "Rightmost: " << max_r[0] << " " << max_r[1] << std::endl;
    
    return 0;
}
