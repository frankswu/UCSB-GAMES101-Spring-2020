#include<cmath>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>
#include<iostream>

using std::cout;    using std::endl;

int main(){

    // Basic Example of cpp
    cout << "Example of cpp \n";
    float a = 1.0, b = 2.0;
    cout << a << endl;
    cout << a/b << endl;
    cout << std::sqrt(b) << endl;
    cout << std::acos(-1) << endl;
    cout << std::sin(30.0/180.0*acos(-1)) << endl;

    // Example of vector
    cout << "Example of vector \n";
    // vector definition
    Eigen::Vector3f v(1.0f,2.0f,3.0f);
    Eigen::Vector3f w(1.0f,0.0f,0.0f);
    // vector output
    cout << "Example of output \n";
    cout << v << endl;
    // vector add
    cout << "Example of add \n";
    cout << v + w << endl;
    // vector scalar multiply
    cout << "Example of scalar multiply \n";
    cout << v * 3.0f << endl;
    cout << 2.0f * v << endl;

    // Example of matrix
    cout << "Example of matrix \n";
    // matrix definition
    Eigen::Matrix3f i,j;
    i << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
    j << 2.0, 3.0, 1.0, 4.0, 6.0, 5.0, 9.0, 7.0, 8.0;
    // matrix output
    cout << "Example of output \n";
    cout << i << endl;
    // matrix add i + j
    cout << i + j << endl;
    // matrix scalar multiply i * 2.0
    cout << 2.0 * i << endl;
    // matrix multiply i * j
    cout << i * j << endl;
    // matrix multiply vector i * v
    cout << i * v << endl;

    // hw0
    Eigen::Vector3f P(2.0f, 1.0f, 1.0f);
    Eigen::Matrix3f R;
    float sin45 = std::sin(45.0/180.0*acos(-1)), cos45 = std::cos(45.0/180.0*acos(-1));
    R << cos45, -sin45, 1.0, sin45, cos45, 2.0, 0.0, 0.0, 1.0;

    cout << " -------- hw0 --------- " << endl;
    cout << R << endl;
    cout << P << endl;
    cout << R * P << endl;

    return 0;
}