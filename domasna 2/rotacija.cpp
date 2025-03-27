#include <iostream>
#include <cmath>
#include <bits/stdc++.h>


using namespace std;

struct Point {
    double e[3];

    Point(double x = 0.0, double y = 0.0, double w = 0.0) {
        e[0] = x;
        e[1] = y;
        e[2] = w;
    }
};

struct Matrix {
    double m[3][3] = {0};
    
    Matrix() {
        for (int i = 0; i < 3; i++) {
            m[i][i] = 1;
        }
    }
    
    Matrix(int v) {
        for (int i = 0; i < 3; i++) {
            m[i][i] = v;
        }
    }
    
    double &at(int x, int y) {
        return m[x][y];
    }
    
    Matrix operator*(const Matrix &second) {
        Matrix result(0);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    result.m[i][j] += m[i][k] * second.m[k][j];
                }
            }
        }
        return result;
    }
    
    Point operator*(const Point &second) {
        Point result;
        for (int i = 0; i < 3; i++) {
            result.e[i] = 0;
            for (int j = 0; j < 3; j++) {
                result.e[i] += m[i][j] * second.e[j];
            }
        }
        return result;
    }
};

class Point3D {
private:
    double x, y, z;
public:
    Point3D(double a = 0, double b = 0, double c = 0) : x(a), y(b), z(c) {}

    Point3D rotateX(double angle) const {
        double rad = angle * M_PI / 180.0;
        double newY = y * cos(rad) - z * sin(rad);
        double newZ = y * sin(rad) + z * cos(rad);
        return Point3D(x, newY, newZ);
    }

    Point3D rotateY(double angle) const {
        double rad = angle * M_PI / 180.0;
        double newX = x * cos(rad) + z * sin(rad);
        double newZ = -x * sin(rad) + z * cos(rad);
        return Point3D(newX, y, newZ);
    }

    Point3D rotateZ(double angle) const {
        double rad = angle * M_PI / 180.0;
        double newX = x * cos(rad) - y * sin(rad);
        double newY = x * sin(rad) + y * cos(rad);
        return Point3D(newX, newY, z);
    }

    Point3D translate(double dx, double dy, double dz) const {
        return Point3D(x + dx, y + dy, z + dz);
    }

    Point3D scale(double sx, double sy, double sz, double cx = 0, double cy = 0, double cz = 0) const {
        double newX = cx + (x - cx) * sx;
        double newY = cy + (y - cy) * sy;
        double newZ = cz + (z - cz) * sz;
        return Point3D(newX, newY, newZ);
    }

    friend ostream &operator<<(ostream &os, const Point3D &p) {
        os << fixed << setprecision(4) << "(" << p.x << ", " << p.y << ", " << p.z << ")\n";
        return os;
    }
};

ostream &operator<<(ostream &os, const Matrix &matrix) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            os << matrix.m[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

ostream &operator<<(ostream &os, const Point &p) {
    os << "[ ";
    for (int i = 0; i < 3; i++) {
        os << p.e[i] << " ";
    }
    os << "]" << endl;
    return os;
}

int main() {
    cout<<"2D:"<<endl;
    Matrix first;
    Matrix second;

    first.m[0][2] = 3;
    second.m[0][0] = 0.5;

    Matrix rot;
    rot.m[0][0] = cos(M_PI / 2);
    rot.m[1][1] = cos(M_PI / 2);
    rot.m[0][1] = -sin(M_PI / 2);
    rot.m[1][0] = sin(M_PI / 2);

    Point p1(3, 1, 1);
    Matrix result = first * second;
    Point p2 = rot * p1;

    cout << p2;
    cout << result;

    cout << "3D:" << endl;
    Point3D p3D1(-1, 5, 0), p3D2(2, 2, 2);
    cout << p3D1.rotateX(-45);
    cout << p3D1.translate(1, 10, -25);
    cout << p3D2.scale(2, 2, 2);
    cout << p3D2.scale(2, 2, 2, 1, 1, 1);
    cout << p3D1.rotateY(180);

    return 0;
}
