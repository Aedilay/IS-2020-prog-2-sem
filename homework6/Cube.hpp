#include <iostream>
#include <string>
#include <vector>
#include "Face.hpp"

using namespace std;

class Cubic {
private:
    vector<Face> cube;

    void generalRotation(int i) {
        char a, b, c, d, e, f, g, h;
        a = cube[i][0][0];
        b = cube[i][1][0];
        c = cube[i][2][0];
        d = cube[i][0][1];
        e = cube[i][2][1];
        f = cube[i][0][2];
        g = cube[i][1][2];
        h = cube[i][2][2];

        cube[i][0][0] = f;
        cube[i][1][0] = d;
        cube[i][2][0] = a;
        cube[i][0][1] = g;
        cube[i][2][1] = b;
        cube[i][0][2] = h;
        cube[i][1][2] = e;
        cube[i][2][2] = c;
    }

public:
    Cubic() : cube() {
        cube.emplace_back('Y');
        cube.emplace_back('B');
        cube.emplace_back('R');
        cube.emplace_back('G');
        cube.emplace_back('O');
        cube.emplace_back('W');
    };

    Cubic(Cubic &other) {
        cube.emplace_back('Y');
        cube.emplace_back('B');
        cube.emplace_back('R');
        cube.emplace_back('G');
        cube.emplace_back('O');
        cube.emplace_back('W');

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    cube[i][j][k] = other[i][j][k];
                }
            }
        }
    }

    Face &operator[](int i) {
        return cube[i];
    }

    Cubic &m() {
        char temp1 = cube[0][1][0];
        cube[0][1][0] = cube[1][1][0];
        char temp2 = cube[3][1][2];
        cube[3][1][2] = temp1;
        temp1 = cube[5][1][0];
        cube[5][1][0] = temp2;
        cube[1][1][0] = temp1;

        temp1 = cube[0][1][1];
        cube[0][1][1] = cube[1][1][1];
        temp2 = cube[3][1][1];
        cube[3][1][1] = temp1;
        temp1 = cube[5][1][1];
        cube[5][1][1] = temp2;
        cube[1][1][1] = temp1;

        temp1 = cube[0][1][2];
        cube[0][1][2] = cube[1][1][2];
        temp2 = cube[3][1][0];
        cube[3][1][0] = temp1;
        temp1 = cube[5][1][2];
        cube[5][1][2] = temp2;
        cube[1][1][2] = temp1;

        result.emplace_back("i,");
        return *this;
    }

    Cubic &r() {
        generalRotation(2);
        char temp1 = cube[0][2][0];
        cube[0][2][0] = cube[1][2][0];
        char temp2 = cube[3][0][2];
        cube[3][0][2] = temp1;
        temp1 = cube[5][2][0];
        cube[5][2][0] = temp2;
        cube[1][2][0] = temp1;

        temp1 = cube[0][2][1];
        cube[0][2][1] = cube[1][2][1];
        temp2 = cube[3][0][1];
        cube[3][0][1] = temp1;
        temp1 = cube[5][2][1];
        cube[5][2][1] = temp2;
        cube[1][2][1] = temp1;

        temp1 = cube[0][2][2];
        cube[0][2][2] = cube[1][2][2];
        temp2 = cube[3][0][0];
        cube[3][0][0] = temp1;
        temp1 = cube[5][2][2];
        cube[5][2][2] = temp2;
        cube[1][2][2] = temp1;

        result.emplace_back("d,");
        return *this;
    }

    Cubic &rRev() {
        this->r().r().r();

        for (int i = 0; i < 3; ++i) {
            result.pop_back();
        }
        result.emplace_back("shift + d,");

        return *this;
    }

    Cubic &l() {
        generalRotation(4);
        char temp1 = cube[0][0][2];
        cube[0][0][2] = cube[3][2][0];
        char temp2 = cube[1][0][2];
        cube[1][0][2] = temp1;
        temp1 = cube[5][0][2];
        cube[5][0][2] = temp2;
        cube[3][2][0] = temp1;

        temp1 = cube[0][0][1];
        cube[0][0][1] = cube[3][2][1];
        temp2 = cube[1][0][1];
        cube[1][0][1] = temp1;
        temp1 = cube[5][0][1];
        cube[5][0][1] = temp2;
        cube[3][2][1] = temp1;

        temp1 = cube[0][0][0];
        cube[0][0][0] = cube[3][2][2];
        temp2 = cube[1][0][0];
        cube[1][0][0] = temp1;
        temp1 = cube[5][0][0];
        cube[5][0][0] = temp2;
        cube[3][2][2] = temp1;

        result.emplace_back("a,");
        return *this;
    }

    Cubic &lRev() {
        this->l().l().l();
        for (int i = 0; i < 3; ++i) {
            result.pop_back();
        }
        result.emplace_back("shift + a,");
        return *this;
    }

    Cubic &u() {
        generalRotation(0);
        char temp1 = cube[1][0][0];
        cube[1][0][0] = cube[2][0][0];
        char temp2 = cube[4][0][0];
        cube[4][0][0] = temp1;
        temp1 = cube[3][0][0];
        cube[3][0][0] = temp2;
        cube[2][0][0] = temp1;

        temp1 = cube[1][1][0];
        cube[1][1][0] = cube[2][1][0];
        temp2 = cube[4][1][0];
        cube[4][1][0] = temp1;
        temp1 = cube[3][1][0];
        cube[3][1][0] = temp2;
        cube[2][1][0] = temp1;

        temp1 = cube[1][2][0];
        cube[1][2][0] = cube[2][2][0];
        temp2 = cube[4][2][0];
        cube[4][2][0] = temp1;
        temp1 = cube[3][2][0];
        cube[3][2][0] = temp2;
        cube[2][2][0] = temp1;

        result.emplace_back("w,");
        return *this;
    }

    Cubic &uRev() {
        this->u().u().u();
        for (int i = 0; i < 3; ++i) {
            result.pop_back();
        }
        result.emplace_back("shift + w,");
        return *this;
    }

    Cubic &d() {
        generalRotation(5);
        char temp1 = cube[2][0][2];
        cube[2][0][2] = cube[1][0][2];
        char temp2 = cube[3][0][2];
        cube[3][0][2] = temp1;
        temp1 = cube[4][0][2];
        cube[4][0][2] = temp2;
        cube[1][0][2] = temp1;

        temp1 = cube[2][1][2];
        cube[2][1][2] = cube[1][1][2];
        temp2 = cube[3][1][2];
        cube[3][1][2] = temp1;
        temp1 = cube[4][1][2];
        cube[4][1][2] = temp2;
        cube[1][1][2] = temp1;

        temp1 = cube[2][2][2];
        cube[2][2][2] = cube[1][2][2];
        temp2 = cube[3][2][2];
        cube[3][2][2] = temp1;
        temp1 = cube[4][2][2];
        cube[4][2][2] = temp2;
        cube[1][2][2] = temp1;

        result.emplace_back("x,");
        return *this;
    }

    Cubic &dRev() {
        this->d().d().d();
        for (int i = 0; i < 3; ++i) {
            result.pop_back();
        }
        result.emplace_back("shift + x,");
        return *this;
    }

    Cubic &b() {
        generalRotation(3);
        char temp1 = cube[4][0][0];
        cube[4][0][0] = cube[0][2][0];
        char temp2 = cube[5][0][2];
        cube[5][0][2] = temp1;
        temp1 = cube[2][2][2];
        cube[2][2][2] = temp2;
        cube[0][2][0] = temp1;

        temp1 = cube[4][0][1];
        cube[4][0][1] = cube[0][1][0];
        temp2 = cube[5][1][2];
        cube[5][1][2] = temp1;
        temp1 = cube[2][2][1];
        cube[2][2][1] = temp2;
        cube[0][1][0] = temp1;

        temp1 = cube[4][0][2];
        cube[4][0][2] = cube[0][0][0];
        temp2 = cube[5][2][2];
        cube[5][2][2] = temp1;
        temp1 = cube[2][2][0];
        cube[2][2][0] = temp2;
        cube[0][0][0] = temp1;

        result.emplace_back("f,");
        return *this;
    }

    Cubic &bRev() {
        this->b().b().b();
        for (int i = 0; i < 3; ++i) {
            result.pop_back();
        }
        result.emplace_back("shift + f,");
        return *this;
    }

    Cubic &f() {
        generalRotation(1);
        char temp1 = cube[2][0][2];
        cube[2][0][2] = cube[0][2][2];
        char temp2 = cube[5][0][0];
        cube[5][0][0] = temp1;
        temp1 = cube[4][2][0];
        cube[4][2][0] = temp2;
        cube[0][2][2] = temp1;

        temp1 = cube[2][0][1];
        cube[2][0][1] = cube[0][1][2];
        temp2 = cube[5][1][0];
        cube[5][1][0] = temp1;
        temp1 = cube[4][2][1];
        cube[4][2][1] = temp2;
        cube[0][1][2] = temp1;

        temp1 = cube[2][0][0];
        cube[2][0][0] = cube[0][0][2];
        temp2 = cube[5][2][0];
        cube[5][2][0] = temp1;
        temp1 = cube[4][2][2];
        cube[4][2][2] = temp2;
        cube[0][0][2] = temp1;

        result.emplace_back("s,");
        return *this;
    }

    Cubic &fRev() {
        this->f().f().f();
        for (int i = 0; i < 3; ++i) {
            result.pop_back();
        }
        result.emplace_back("shift + s,");
        return *this;
    }

    void clearRes() {
        result.clear();
    };

    vector<string> result;
};