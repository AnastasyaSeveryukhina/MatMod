#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

float h0;
float vx, vy;

float x_t, t, y;
float g = 9.81;

float forward(vector<float> x, int i, float y_0){

    t = (x.at(i) - x_t) / vx;
    y = y_0 + vy * t - g * t * t / 2;

    return y;
}

float back(vector<float> x, int i, float y_0){

    t = (x.at(i) - x[i]) / vx;
    y = y_0 + vy * t - g * t * t / 2;

    return y;
}

int main() {

    ifstream file;
    file.open("in.txt");

    file >> h0;
    file >> vx >> vy;


    vector<float> x;
    x.push_back(0);
    vector<float> h(1);
    h.push_back(h0);

    while (!file.eof()){
        float x_n, h_n;
        file >> x_n >> h_n;
        x.push_back(x_n);
        h.push_back(h_n);
    }
    file.close();

    string direction = "right";
    int i = 1;
    float y_0 = h0;
    x_t = 0;
    forward(x, i, y_0);
    i++;
    while (y > 0 && (i != (x.size())) && (i !=0) ) {

        if (y <= h[i] && direction == "right") {
            direction = "left";
            vx = -vx;
            y_0 = y;
            x_t = x.at(i);
        } else if (y <= h[i] && direction == "left") {
            direction = "right";
            x_t = x.at(i);
            vx = -vx;
            y_0 = y;
        }

        if (direction == "right") {
            i++;
            forward(x, i, y_0);
        } else {
            i--;
            back(x, i, y_0);
        }
    }

    cout << i << endl;
    return 0;
}
