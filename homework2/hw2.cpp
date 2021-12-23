#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

float h0;
float vx, vy;

float x_t, t, y;
float g = 9.81;

float step(float x_c, float h_c, float vx_, float vy_, float x_n) {
    t = (x_n - x_c) / vx_;
    y = h_c + vy_ * t - g * t * t / 2;
    return y;
}


pair<int,float> forward(int i, float vx_, float vy_, vector<float> x, vector<float> h, float y_n) {
    int i_next = i + 1;
    y = step(x[i], y_n, vx_, vy_, x[i_next]);
//     cout << "forward: "<< i_next << " "  << x[i_next] << " "<< y << " " << h[i_next] << endl;
    while (y > 0 && (i_next != (x.size())) && (y > h[i_next])) {
        i_next++;
        y = step(x[i], y_n, vx_, vy_, x[i_next]);
//         cout << "forward: "<< i_next << " "  << x[i_next] << " "<< y << " " << h[i_next] << endl;
    }
    return pair<int, float>(i_next, y);
}

pair<int, float> back(int i, float vx_, float vy_, vector<float> x, vector<float> h, float y_n) {
    int i_next = i - 1;
    y = step(x[i], y_n, vx_, vy_, x[i_next]);
//     cout << "back: "<< i_next << " "  << x[i_next] << " "<< y << " " << h[i_next] << endl;
    i_next--;
    while (y > 0 && (i_next >= 0) && (y > h[i_next])) {
        y = step(x[i], y_n, vx_, vy_, x[i_next]);
        i_next--;
//         cout << "forward: "<< i_next << " "  << x[i_next] << " "<< y << " " << h[i_next] << endl;
    }
    return pair<int, float>(i_next, y);

}

int main() {

    ifstream file;
    file.open("in.txt");

    file >> h0;
    file >> vx >> vy;


    vector<float> x;
    x.push_back(0);
    vector<float> h;
    h.push_back(h0);

    float x_n, h_n;
    file >> x_n >> h_n;
    if (x_n == 0) {
        cout << 0 << endl;
    } else {
        x.push_back(x_n);
        h.push_back(h_n);
        while (!file.eof()) {
            file >> x_n >> h_n;
            x.push_back(x_n);
            h.push_back(h_n);
        }
        file.close();

        string direction = "right";
        int i = 0;
        auto p = forward(i, vx, vy, x, h, h0);
        i = p.first;
        y = p.second;

        while (y > 0 && (i != (x.size())) && (i >= 0)) {
            cout << "bumm" << endl;
            vx = -vx;
            if (direction == "right") {
                direction = "left";
                p = back(i, vx, vy, x, h, y);
            } else {
                direction = "right";
                p = forward(i, vx, vy, x, h, y);
            }
            i = p.first;
            y = p.second;
        }

        if (i <= 0) {
            cout << 0 << endl;
        } else {
                cout << i-1 << endl;
            }
    }
    return 0;
}
