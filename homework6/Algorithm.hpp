#include <random>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <tuple>
#include <set>
#include "Cube.hpp"

using namespace std;

class Algorithm {
public:
    explicit Algorithm(Cubic &cube_) : cube(cube_), number(3) {}

    Cubic &getCube() {
        return cube;
    }

    vector<string> mixCube(int t) {
        vector<string> ans;
        std::uniform_int_distribution<> rand(0, 7);
        for (int i = 0; i < t; i++) {
            int p = rand(number);
            switch (p) {
                case 0: {
                    cube.u();
                    ans.emplace_back("w");
                }
                    break;
                case 1: {
                    cube.uRev();
                    ans.emplace_back("shift + w");
                }
                    break;
                case 2: {
                    cube.rRev();
                    ans.emplace_back("d");
                }
                    break;
                case 3: {
                    cube.r();
                    ans.emplace_back("shift + d");
                }
                    break;
                case 4: {
                    cube.l();
                    ans.emplace_back("a");
                }
                    break;
                case 5: {
                    cube.lRev();
                    ans.emplace_back("shift + a");
                }
                    break;
                case 6: {
                    cube.f();
                    ans.emplace_back("s");
                }
                    break;
                case 7: {
                    cube.fRev();
                    ans.emplace_back("shift + s");
                }
                    break;
                default: {
                }
            }
        }

        return ans;
    }

    bool isSolved() {
        for (int i = 0; i < 6; i++) {
            char check_col = cube[i][0][0];
            for (int y = 0; y < 3; y++) {
                for (int x = 0; x < 3; x++) {
                    if (check_col != cube[i][x][y]) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    bool status() {
        map<char, int> stat;
        stat.insert(make_pair('R', 0));
        stat.insert(make_pair('G', 0));
        stat.insert(make_pair('B', 0));
        stat.insert(make_pair('Y', 0));
        stat.insert(make_pair('O', 0));
        stat.insert(make_pair('W', 0));

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    int a = stat.find(cube[i][j][k])->second;
                    stat.find(cube[i][j][k])->second = a + 1;
                }
            }
        }

        for (auto c : stat) {
            if (c.second != 9) {
                cout << "Wrong state!" << endl;
                cout << "[";
                for (auto c1 : stat) {
                    cout << " " << c1.first << " - " << c1.second;
                }
                cout << "]" << endl;
                return false;
            }
        }

        return true;
    }

    bool checkInvariant() {
        if (!status()) {
            return false;
        } else {
            auto bad_corner = make_tuple(-1, -1, -1);
            auto bad_pair = make_pair(-1, -1);

            if (GetCorner('Y', 'R', 'G') == bad_corner ||
                GetCorner('Y', 'G', 'O') == bad_corner ||
                GetCorner('Y', 'O', 'B') == bad_corner ||
                GetCorner('B', 'Y', 'R') == bad_corner ||
                GetCorner('W', 'O', 'G') == bad_corner ||
                GetCorner('G', 'W', 'R') == bad_corner ||
                GetCorner('R', 'W', 'B') == bad_corner ||
                GetCorner('B', 'W', 'O') == bad_corner) {
                return false;
            }

            if (getPair('O', 'W') == bad_pair ||
                    getPair('O', 'G') == bad_pair ||
                    getPair('B', 'O') == bad_pair ||
                    getPair('O', 'Y') == bad_pair ||
                    getPair('G', 'R') == bad_pair ||
                    getPair('R', 'B') == bad_pair ||
                    getPair('R', 'W') == bad_pair ||
                    getPair('R', 'Y') == bad_pair ||
                    getPair('B', 'Y') == bad_pair ||
                    getPair('Y', 'G') == bad_pair ||
                    getPair('W', 'G') == bad_pair ||
                    getPair('W', 'B') == bad_pair) {
                return false;
            }

            set<char> central_seg;
            for (int i = 0; i < 6; i++) {
                central_seg.emplace(cube[i][1][1]);
            }
            if (central_seg.size() != 6) {
                return false;
            }

            map<char, char> central_colors = {
                    {'W', 'Y'},
                    {'R', 'O'},
                    {'B', 'G'},
                    {'Y', 'W'},
                    {'O', 'R'},
                    {'G', 'B'}
            };

            if ((central_colors[cube[1][1][1]] != cube[3][1][1]) ||
                (central_colors[cube[2][1][1] != cube[4][1][1]]) ||
                (central_colors[cube[0][1][1]] != cube[5][1][1])) {
                return false;
            }

        }
        return true;
    }

    bool comleteCube() {

        cube.clearRes();

        compileCross();

        compileCorners();

        compileSecondLayer();

        compileWhiteWrongCross();

        makeWhiteCrossRight();

        rotateCorners();

        return checkInvariant() && isSolved();
    }

private:
    Cubic cube;

    static bool equals(const vector<char> &c1, vector<char> c2) {
        if (c1.size() != c2.size()) {
            return false;
        }
        for (char it : c1) {
            if (find(c2.begin(), c2.end(), it) == c2.end()) {
                return false;
            }
        }
        return true;
    }

    pair<int, int> getPair(char c1, char c2) {
        if ((cube[1][1][0] == c1 && cube[0][1][2] == c2) ||
            (cube[1][1][0] == c2 && cube[0][1][2] == c1)) {
            return {1, 0};
        }
        if ((cube[1][2][1] == c1 && cube[2][0][1] == c2) ||
            (cube[1][2][1] == c2 && cube[2][0][1] == c1)) {
            return {1, 2};
        }
        if ((cube[1][1][2] == c1 && cube[5][1][0] == c2) ||
            (cube[1][1][2] == c2 && cube[5][1][0] == c1)) {
            return {1, 5};
        }
        if ((cube[1][0][1] == c1 && cube[4][2][1] == c2) ||
            (cube[1][0][1] == c2 && cube[4][2][1] == c1)) {
            return {1, 4};
        }

        if ((cube[2][1][0] == c1 && cube[0][2][1] == c2) ||
            (cube[2][1][0] == c2 && cube[0][2][1] == c1)) {
            return {2, 0};
        }
        if ((cube[2][2][1] == c1 && cube[3][0][1] == c2) ||
            (cube[2][2][1] == c2 && cube[3][0][1] == c1)) {
            return {2, 3};
        }
        if ((cube[2][1][2] == c1 && cube[5][2][1] == c2) ||
            (cube[2][1][2] == c2 && cube[5][2][1] == c1)) {
            return {2, 5};
        }

        if ((cube[3][1][0] == c1 && cube[0][1][0] == c2) ||
            (cube[3][1][0] == c2 && cube[0][1][0] == c1)) {
            return {3, 0};
        }
        if ((cube[3][2][1] == c1 && cube[4][0][1] == c2) ||
            (cube[3][2][1] == c2 && cube[4][0][1] == c1)) {
            return {3, 4};
        }
        if ((cube[3][1][2] == c1 && cube[5][1][2] == c2) ||
            (cube[3][1][2] == c2 && cube[5][1][2] == c1)) {
            return {3, 5};
        }

        if ((cube[4][1][0] == c1 && cube[0][0][1] == c2) ||
            (cube[4][1][0] == c2 && cube[0][0][1] == c1)) {
            return {4, 0};
        }
        if ((cube[4][2][1] == c1 && cube[4][0][1] == c2) ||
            (cube[4][2][1] == c2 && cube[4][0][1] == c1)) {
            return {4, 2};
        }
        if ((cube[4][1][2] == c1 && cube[5][0][1] == c2) ||
            (cube[4][1][2] == c2 && cube[5][0][1] == c1)) {
            return {4, 5};
        }
        return {-1, -1};
    }

    tuple<int, int, int> GetCorner(char c1, char c2, char c3) {
        if (equals({cube[1][2][0], cube[0][2][2], cube[2][0][0]}, {c1, c2, c3})) {
            return {1, 0, 2};
        }
        if (equals({cube[2][2][0], cube[0][2][0], cube[3][0][0]}, {c1, c2, c3})) {
            return {2, 0, 3};
        }
        if (equals({cube[3][2][0], cube[0][0][0], cube[4][0][0]}, {c1, c2, c3})) {
            return {3, 0, 4};
        }
        if (equals({cube[4][2][0], cube[0][0][2], cube[1][0][0]}, {c1, c2, c3})) {
            return {4, 0, 1};
        }

        if (equals({cube[1][2][2], cube[5][2][0], cube[2][0][2]}, {c1, c2, c3})) {
            return {1, 5, 2};
        }
        if (equals({cube[2][2][2], cube[5][2][2], cube[3][0][2]}, {c1, c2, c3})) {
            return {2, 5, 3};
        }
        if (equals({cube[3][2][2], cube[5][0][2], cube[4][0][2]}, {c1, c2, c3})) {
            return {3, 5, 4};
        }
        if (equals({cube[4][2][2], cube[5][0][0], cube[1][0][2]}, {c1, c2, c3})) {
            return {4, 5, 1};
        }
        return {-1, -1, -1};
    }

    static bool checkColourCorner(tuple<int, int, int> &t, int e) {
        return get<0>(t) == e || get<1>(t) == e || get<2>(t) == e;
    }

    static bool checkColourPair(pair<int, int> &p, int e) {
        return p.first == e || p.second == e;
    }

    void compileCross() {
        pair<int, int> yb = getPair('Y', 'B');
        if (!((yb.first == 1 && yb.second == 0) || (yb.first == 0 && yb.second == 1))) {
            if (yb.first == 0 || yb.second == 0) {
                if (yb.first == 2 || yb.second == 2) {
                    cube.rRev().rRev().dRev().fRev().fRev();
                } else if (yb.first == 3 || yb.second == 3) {
                    cube.b().b().d().d().f().f();
                } else if (yb.first == 4 || yb.second == 4) {
                    cube.l().l().d().f().f();
                }
            } else if (yb.first == 1 || yb.second == 1) {
                if (yb.first == 4 || yb.second == 4) {
                    cube.f();
                } else if (yb.first == 5 || yb.second == 5) {
                    cube.f().f();
                } else if (yb.first == 2 || yb.second == 2) {
                    cube.fRev();
                }
            } else if (yb.first == 2 || yb.second == 2) {
                if (yb.first == 3 || yb.second == 3) {
                    cube.r().dRev().rRev().f().f();
                } else if (yb.first == 5 || yb.second == 5) {
                    cube.dRev().f().f();
                }
            } else if (yb.first == 3 || yb.second == 3) {
                if (yb.first == 4 || yb.second == 4) {
                    cube.lRev().d().l().f().f();
                } else if (yb.first == 5 || yb.second == 5) {
                    cube.d().d().f().f();
                }
            } else if (yb.first == 4 || yb.second == 4) {
                cube.d().f().f(); // Only 5
            }
        }

        if (cube[0][1][2] == 'B') {
            cube.f().uRev().r().u();
        }

        pair<int, int> ry = getPair('R', 'Y');
        if (!((ry.first == 2 && ry.second == 0) || (ry.first == 0 && ry.second == 2))) {
            if (ry.first == 0 || ry.second == 0) {
                if (ry.first == 1 || ry.second == 1) {
                    cube.f().f().d().r().r();
                } else if (ry.first == 3 || ry.second == 3) {
                    cube.b().b().dRev().r().r();
                } else if (ry.first == 4 || ry.second == 4) {
                    cube.l().l().d().d().r().r();
                }
            } else if (ry.first == 1 || ry.second == 1) {
                if (ry.first == 2 || ry.second == 2) {
                    cube.r();
                } else if (ry.first == 5 || ry.second == 5) {
                    cube.d().r().r();
                } else if (ry.first == 4 || ry.second == 4) {
                    cube.l().d().d().lRev().r().r();
                }
            } else if (ry.first == 2 || ry.second == 2) {
                if (ry.first == 3 || ry.second == 3) {
                    cube.rRev();
                } else if (ry.first == 5 || ry.second == 5) {
                    cube.r().r();
                }
            } else if (ry.first == 3 || ry.second == 3) {
                if (ry.first == 4 || ry.second == 4) {
                    cube.lRev().dRev().dRev().l().r().r();
                } else if (ry.first == 5 || ry.second == 5) {
                    cube.dRev().r().r();
                }
            } else if (ry.first == 4 || ry.second == 4) {
                cube.d().d().r().r(); // Only 5
            }
        }

        if (cube[0][2][1] == 'R') {
            cube.r().uRev().b().u();
        }

        pair<int, int> gy = getPair('G', 'Y');

        if (!((gy.first == 3 && gy.second == 0) || (gy.first == 0 && gy.second == 3))) {
            if (gy.first == 0 || gy.second == 0) {
                if (gy.first == 1 || gy.second == 1) {
                    cube.f().f().d().d().b().b();
                } else if (gy.first == 2 || gy.second == 2) {
                    cube.r().r().d().b().b();
                } else if (gy.first == 4 || gy.second == 4) {
                    cube.l().l().dRev().b().b();
                }
            } else if (gy.first == 1 || gy.second == 1) {
                if (gy.first == 2 || gy.second == 2) {
                    cube.rRev().d().r().b().b();
                } else if (gy.first == 4 || gy.second == 4) {
                    cube.fRev().d().d().f().b().b();
                } else if (gy.first == 5 || gy.second == 5) {
                    cube.d().d().b().b();
                }
            } else if (gy.first == 2 || gy.second == 2) {
                if (gy.first == 3 || gy.second == 3) {
                    cube.b();
                } else if (gy.first == 5 || gy.second == 5) {
                    cube.d().b().b();
                }
            } else if (gy.first == 3 || gy.second == 3) {
                if (gy.first == 4 || gy.second == 4) {
                    cube.bRev();
                } else if (gy.first == 5 || gy.second == 5) {
                    cube.b().b();
                }
            } else if (gy.first == 4 || gy.second == 4) {
                cube.dRev().b().b(); // Only 5
            }
        }

        if (cube[0][1][0] == 'G') {
            cube.b().uRev().l().u();
        }

        pair<int, int> yo = getPair('Y', 'O');

        if (!((yo.first == 4 && yo.second == 0) || (yo.first == 0 && yo.second == 4))) {
            if (yo.first == 0 || yo.second == 0) {
                if (yo.first == 1 || yo.second == 1) {
                    cube.f().f().dRev().l().l();
                } else if (yo.first == 2 || yo.second == 2) {
                    cube.rRev().rRev().dRev().dRev().l().l();
                } else if (yo.first == 3 || yo.second == 3) {
                    cube.b().b().d().l().l();
                }
            } else if (yo.first == 1 || yo.second == 1) {
                if (yo.first == 2 || yo.second == 2) {
                    cube.rRev().dRev().dRev().r().l().l();
                } else if (yo.first == 4 || yo.second == 4) {
                    cube.lRev();
                } else if (yo.first == 5 || yo.second == 5) {
                    cube.dRev().l().l();
                }
            } else if (yo.first == 2 || yo.second == 2) {
                if (yo.first == 3 || yo.second == 3) {
                    cube.bRev().d().b().l().l();
                } else if (yo.first == 5 || yo.second == 5) {
                    cube.d().d().l().l();
                }
            } else if (yo.first == 3 || yo.second == 3) {
                if (yo.first == 4 || yo.second == 4) {
                    cube.l();
                } else if (yo.first == 5 || yo.second == 5) {
                    cube.d().l().l();
                }
            } else if (yo.first == 4 || yo.second == 4) {
                cube.l().l();
            }
        }

        if (cube[0][0][1] == 'O') {
            cube.l().uRev().f().u();
        }
    }

    void compileCorners() {
        auto cbyr = GetCorner('B', 'Y', 'R');

        if (checkColourCorner(cbyr, 1) && checkColourCorner(cbyr, 4) && checkColourCorner(cbyr, 0)) {
            cube.fRev().dRev().f().d().d();
        } else if (checkColourCorner(cbyr, 1) && checkColourCorner(cbyr, 4) && checkColourCorner(cbyr, 5)) {
            cube.d();
        } else if (checkColourCorner(cbyr, 4) && checkColourCorner(cbyr, 0) && checkColourCorner(cbyr, 3)) {
            cube.lRev().dRev().l().dRev();
        } else if (checkColourCorner(cbyr, 4) && checkColourCorner(cbyr, 5) && checkColourCorner(cbyr, 3)) {
            cube.d().d();
        } else if (checkColourCorner(cbyr, 0) && checkColourCorner(cbyr, 2) && checkColourCorner(cbyr, 3)) {
            cube.bRev().dRev().b();
        } else if (checkColourCorner(cbyr, 5) && checkColourCorner(cbyr, 2) && checkColourCorner(cbyr, 3)) {
            cube.dRev();
        }

        while (!(cube[0][2][2] == 'Y' && cube[1][2][0] == 'B' && cube[2][0][0] == 'R')) {
            cube.rRev().dRev().r().d();
        }

        auto cgyr = GetCorner('G', 'Y', 'R');

        if (checkColourCorner(cgyr, 0) && checkColourCorner(cgyr, 1) && checkColourCorner(cgyr, 2)) {
            cube.rRev().dRev().r().d().d();
        } else if (checkColourCorner(cgyr, 5) && checkColourCorner(cgyr, 1) && checkColourCorner(cgyr, 2)) {
            cube.d();
        } else if (checkColourCorner(cgyr, 0) && checkColourCorner(cgyr, 1) && checkColourCorner(cgyr, 4)) {
            cube.fRev().dRev().f().dRev();
        } else if (checkColourCorner(cgyr, 5) && checkColourCorner(cgyr, 1) && checkColourCorner(cgyr, 4)) {
            cube.d().d();
        } else if (checkColourCorner(cgyr, 0) && checkColourCorner(cgyr, 3) && checkColourCorner(cgyr, 4)) {
            cube.lRev().dRev().l();
        } else if (checkColourCorner(cgyr, 5) && checkColourCorner(cgyr, 3) && checkColourCorner(cgyr, 4)) {
            cube.dRev();
        }

        while (!(cube[0][2][0] == 'Y' && cube[2][2][0] == 'R' && cube[3][0][0] == 'G')) {
            cube.bRev().dRev().b().d();
        }

        auto cgyo = GetCorner('G', 'Y', 'O');

        if (checkColourCorner(cgyo, 0) && checkColourCorner(cgyo, 1) && checkColourCorner(cgyo, 2)) {
            cube.rRev().dRev().r().dRev();
        } else if (checkColourCorner(cgyo, 5) && checkColourCorner(cgyo, 1) && checkColourCorner(cgyo, 2)) {
            cube.d().d();
        } else if (checkColourCorner(cgyo, 0) && checkColourCorner(cgyo, 2) && checkColourCorner(cgyo, 3)) {
            cube.bRev().dRev().b().d().d();
        } else if (checkColourCorner(cgyo, 5) && checkColourCorner(cgyo, 2) && checkColourCorner(cgyo, 3)) {
            cube.d();
        } else if (checkColourCorner(cgyo, 1) && checkColourCorner(cgyo, 0) && checkColourCorner(cgyo, 4)) {
            cube.fRev().dRev().f();
        } else if (checkColourCorner(cgyo, 5) && checkColourCorner(cgyo, 1) && checkColourCorner(cgyo, 4)) {
            cube.dRev();
        }

        while (!(cube[0][0][0] == 'Y' && cube[3][2][0] == 'G' && cube[4][0][0] == 'O')) {
            cube.lRev().dRev().l().d();
        }

        auto cbyo = GetCorner('B', 'Y', 'O');

        if (checkColourCorner(cbyo, 0) && checkColourCorner(cbyo, 1) && checkColourCorner(cbyo, 2)) {
            cube.rRev().dRev().r();
        } else if (checkColourCorner(cbyo, 5) && checkColourCorner(cbyo, 1) && checkColourCorner(cbyo, 2)) {
            cube.dRev();
        } else if (checkColourCorner(cbyo, 0) && checkColourCorner(cbyo, 2) && checkColourCorner(cbyo, 3)) {
            cube.bRev().dRev().b().dRev();
        } else if (checkColourCorner(cbyo, 5) && checkColourCorner(cbyo, 2) && checkColourCorner(cbyo, 3)) {
            cube.d().d();
        } else if (checkColourCorner(cbyo, 0) && checkColourCorner(cbyo, 3) && checkColourCorner(cbyo, 4)) {
            cube.fRev().dRev().f().d().d();
        } else if (checkColourCorner(cbyo, 4) && checkColourCorner(cbyo, 5) && checkColourCorner(cbyo, 3)) {
            cube.d();
        }

        while (!(cube[0][0][2] == 'Y' && cube[1][0][0] == 'B' && cube[4][2][0] == 'O')) {
            cube.fRev().dRev().f().d();
        }
    }

    void compileSecondLayer() {
        cube.r().r().m().m().lRev().lRev();

        bool p = true;

        while (p) {
            p = false;

            auto cgr = getPair('G', 'R');
            if (checkColourPair(cgr, 0)) {
                if (checkColourPair(cgr, 3)) {
                    cube.u();
                } else if (checkColourPair(cgr, 4)) {
                    cube.u().u();
                } else if (checkColourPair(cgr, 1)) {
                    cube.uRev();
                }
                if (cube[0][2][1] == 'G') {
                    cube.uRev().fRev().u().f();
                    cube.u().r().uRev().rRev();
                } else {
                    cube.u();
                    cube.u().r().uRev().rRev();
                    cube.uRev().fRev().u().f();
                }
            } else if (checkColourPair(cgr, 4) && checkColourPair(cgr, 1)) {
                cube.u().f().uRev().fRev();
                cube.uRev().lRev().u().l();
                p = true;
            } else if (checkColourPair(cgr, 4) && checkColourPair(cgr, 3)) {
                cube.u().l().uRev().lRev();
                cube.uRev().bRev().u().b();
                p = true;
            } else if (checkColourPair(cgr, 2) && checkColourPair(cgr, 3)) {
                cube.u().b().uRev().bRev();
                cube.uRev().rRev().u().r();
                p = true;
            } else if (checkColourPair(cgr, 1) && checkColourPair(cgr, 2) && cube[1][2][1] == 'R') {
                cube.u().r().uRev().rRev();
                cube.uRev().fRev().u().f();
                p = true;
            }
        }
        p = true;
        while (p) {
            p = false;
            auto crb = getPair('R', 'B');
            if (checkColourPair(crb, 0)) {
                if (checkColourPair(crb, 1)) {
                    cube.u().u();
                } else if (checkColourPair(crb, 2)) {
                    cube.uRev();
                } else if (checkColourPair(crb, 4)) {
                    cube.u();
                }

                if (cube[0][1][0] == 'R') {
                    cube.uRev().rRev().u().r();
                    cube.u().b().uRev().bRev();
                } else {
                    cube.u();
                    cube.u().b().uRev().bRev();
                    cube.uRev().rRev().u().r();
                }
            } else if (checkColourPair(crb, 4) && checkColourPair(crb, 1)) {
                cube.u().f().uRev().fRev();
                cube.uRev().lRev().u().l();
                p = true;
            } else if (checkColourPair(crb, 4) && checkColourPair(crb, 3)) {
                cube.u().l().uRev().lRev();
                cube.uRev().bRev().u().b();
                p = true;
            } else if (checkColourPair(crb, 2) && checkColourPair(crb, 3) && cube[2][2][1] == 'B') {
                cube.u().b().uRev().bRev();
                cube.uRev().rRev().u().r();
                p = true;
            } else if (checkColourPair(crb, 1) && checkColourPair(crb, 2)) {
                cube.u().r().uRev().rRev();
                cube.uRev().fRev().u().f();
                p = true;
            }
        }

        p = true;
        while (p) {
            p = false;
            auto cbo = getPair('B', 'O');
            if (checkColourPair(cbo, 0)) {
                if (checkColourPair(cbo, 1)) {
                    cube.u();
                } else if (checkColourPair(cbo, 2)) {
                    cube.u().u();
                } else if (checkColourPair(cbo, 3)) {
                    cube.uRev();
                }

                if (cube[0][0][1] == 'B') {
                    cube.uRev().bRev().u().b();
                    cube.u().l().uRev().lRev();
                } else {
                    cube.u();
                    cube.u().l().uRev().lRev();
                    cube.uRev().bRev().u().b();
                }
            } else if (checkColourPair(cbo, 4) && checkColourPair(cbo, 1)) {
                cube.u().f().uRev().fRev();
                cube.uRev().lRev().u().l();
                p = true;
            } else if (checkColourPair(cbo, 4) && checkColourPair(cbo, 3) && cube[3][2][1] == 'O') {
                cube.u().l().uRev().lRev();
                cube.uRev().bRev().u().b();
                p = true;
            } else if (checkColourPair(cbo, 2) && checkColourPair(cbo, 3)) {
                cube.u().b().uRev().bRev();
                cube.uRev().rRev().u().r();
                p = true;
            } else if (checkColourPair(cbo, 1) && checkColourPair(cbo, 2)) {
                cube.u().r().uRev().rRev();
                cube.uRev().fRev().u().f();
                p = true;
            }
        }

        p = true;
        while (p) {
            p = false;
            auto cgo = getPair('G', 'O');
            if (checkColourPair(cgo, 0)) {
                if (checkColourPair(cgo, 2)) {
                    cube.u();
                } else if (checkColourPair(cgo, 3)) {
                    cube.u().u();
                } else if (checkColourPair(cgo, 4)) {
                    cube.uRev();
                }

                if (cube[0][1][2] == 'O') {
                    cube.uRev().lRev().u().l();
                    cube.u().f().uRev().fRev();
                } else {
                    cube.u();
                    cube.u().f().uRev().fRev();
                    cube.uRev().lRev().u().l();
                }
            } else if (checkColourPair(cgo, 4) && checkColourPair(cgo, 1) && cube[4][2][1] == 'G') {
                cube.u().f().uRev().fRev();
                cube.uRev().lRev().u().l();
                p = true;
            } else if (checkColourPair(cgo, 4) && checkColourPair(cgo, 3)) {
                cube.u().l().uRev().lRev();
                cube.uRev().bRev().u().b();
                p = true;
            } else if (checkColourPair(cgo, 2) && checkColourPair(cgo, 3)) {
                cube.u().b().uRev().bRev();
                cube.uRev().rRev().u().r();
                p = true;
            } else if (checkColourPair(cgo, 1) && checkColourPair(cgo, 2)) {
                cube.u().r().uRev().rRev();
                cube.uRev().fRev().u().f();
                p = true;
            }
        }
    }

    void compileWhiteWrongCross() {
        while (!(cube[0][1][0] == 'W' &&
                 cube[0][0][1] == 'W' &&
                 cube[0][1][2] == 'W' &&
                 cube[0][2][1] == 'W')) {
            if (cube[0][0][1] == 'W' && cube[0][2][1] == 'W') {
                cube.f().r().u().rRev().uRev().fRev();
            } else if (cube[0][1][0] == 'W' && cube[0][1][2] == 'W') {
                cube.u();
                cube.f().r().u().rRev().uRev().fRev();
            } else if (cube[0][0][1] == 'W' && cube[0][1][0] == 'W') {
                cube.f().r().u().rRev().uRev().fRev();
            } else if (cube[0][1][0] == 'W' && cube[0][2][1] == 'W') {
                cube.uRev();
                cube.f().r().u().rRev().uRev().fRev();
            } else if (cube[0][2][1] == 'W' && cube[0][1][2] == 'W') {
                cube.u().u();
                cube.f().r().u().rRev().uRev().fRev();
            } else if (cube[0][0][1] == 'W' && cube[0][1][2] == 'W') {
                cube.u();
                cube.f().r().u().rRev().uRev().fRev();
            } else {
                cube.f().r().u().rRev().uRev().fRev();
            }
        }
    }

    void makeWhiteCrossRight() {
        int moves = 0;
        int c = 0;
        for (int i = 1; i < 5; i++) {
            if (cube[i][1][1] == cube[i][1][0]) {
                c++;
            }
        }
        while (c < 2 && moves < 10000) {
            cube.u();
            moves++;
            c = 0;
            for (int i = 1; i < 5; i++) {
                if (cube[i][1][1] == cube[i][1][0]) {
                    c++;
                }
            }
        }

        if ((cube[1][1][1] == cube[1][1][0] && cube[3][1][1] == cube[3][1][0])) {
            cube.b().u().bRev().u().b().u().u().bRev();
        } else if (cube[2][1][1] == cube[2][1][0] && cube[4][1][1] == cube[4][1][0]) {
            cube.r().u().rRev().u().r().u().u().rRev();
        }
        moves = 0;
        c = 0;
        for (int i = 1; i < 5; i++) {
            if (cube[i][1][1] == cube[i][1][0]) {
                c++;
            }
        }
        while (c < 2 && moves < 10000) {
            cube.u();
            moves++;
            c = 0;
            for (int i = 1; i < 5; i++) {
                if (cube[i][1][1] == cube[i][1][0]) {
                    c++;
                }
            }
        }

        if (!(cube[1][1][0] == 'G' && cube[2][1][0] == 'R' &&
              cube[3][1][0] == 'B' && cube[4][1][0] == 'O')) {
            if (cube[3][1][0] == 'B' && cube[2][1][0] == 'R') {
                cube.r().u().rRev().u().r().u().u().rRev().u();
            } else if (cube[4][1][0] == 'O' && cube[3][1][0] == 'B') {
                cube.b().u().bRev().u().b().u().u().bRev().u();
            } else if (cube[4][1][0] == 'O' && cube[1][1][0] == 'G') {
                cube.l().u().lRev().u().l().u().u().lRev().u();
            } else if (cube[1][1][0] == 'G' && cube[2][1][0] == 'R') {
                cube.f().u().fRev().u().f().u().u().fRev().u();
            }
        }
    }

    void rotateCorners() {
        auto crbw = GetCorner('R', 'B', 'W');
        auto cgrw = GetCorner('G', 'R', 'W');
        auto cbow = GetCorner('B', 'O', 'W');
        auto cgow = GetCorner('G', 'O', 'W');
        while (!((checkColourCorner(crbw, 2) && checkColourCorner(crbw, 3)) &&
                 (checkColourCorner(cgrw, 2) && checkColourCorner(cgrw, 1)) &&
                 (checkColourCorner(cbow, 3) && checkColourCorner(cbow, 4)) &&
                 (checkColourCorner(cgow, 4) && checkColourCorner(cgow, 1)))) {
            if (!((checkColourCorner(crbw, 2) && checkColourCorner(crbw, 3)) ||
                  (checkColourCorner(cgrw, 2) && checkColourCorner(cgrw, 1)) ||
                  (checkColourCorner(cbow, 3) && checkColourCorner(cbow, 4)) ||
                  (checkColourCorner(cgow, 4) && checkColourCorner(cgow, 1)))) {
                cube.u().r().uRev().lRev().u().rRev().uRev().l();
            }

            if (checkColourCorner(crbw, 2) && checkColourCorner(crbw, 3) &&
                checkColourCorner(cgrw, 4) && checkColourCorner(cgrw, 3) &&
                checkColourCorner(cbow, 4) && checkColourCorner(cbow, 1) &&
                checkColourCorner(cgow, 1) && checkColourCorner(cgow, 2)) {
                cube.uRev().rRev().u().l().uRev().r().u().lRev();
            } else if (checkColourCorner(crbw, 2) && checkColourCorner(crbw, 3) &&
                       checkColourCorner(cgrw, 1) && checkColourCorner(cgrw, 4) &&
                       checkColourCorner(cbow, 1) && checkColourCorner(cbow, 2) &&
                       checkColourCorner(cgow, 3) && checkColourCorner(cgow, 4)) {
                cube.u().b().uRev().fRev().u().bRev().uRev().f();
            } else if (checkColourCorner(crbw, 1) && checkColourCorner(crbw, 4) &&
                       checkColourCorner(cgrw, 2) && checkColourCorner(cgrw, 1) &&
                       checkColourCorner(cbow, 3) && checkColourCorner(cbow, 2) &&
                       checkColourCorner(cgow, 3) && checkColourCorner(cgow, 4)) {
                cube.u().r().uRev().lRev().u().rRev().uRev().l();
            } else if (checkColourCorner(crbw, 3) && checkColourCorner(crbw, 4) &&
                       checkColourCorner(cgrw, 2) && checkColourCorner(cgrw, 1) &&
                       checkColourCorner(cbow, 1) && checkColourCorner(cbow, 4) &&
                       checkColourCorner(cgow, 2) && checkColourCorner(cgow, 3)) {
                cube.uRev().fRev().u().b().uRev().f().u().bRev();
            } else if (checkColourCorner(crbw, 1) && checkColourCorner(crbw, 2) &&
                       checkColourCorner(cgrw, 1) && checkColourCorner(cgrw, 4) &&
                       checkColourCorner(cbow, 3) && checkColourCorner(cbow, 4) &&
                       checkColourCorner(cgow, 2) && checkColourCorner(cgow, 3)) {
                cube.u().l().uRev().rRev().u().lRev().uRev().r();
            } else if (checkColourCorner(crbw, 1) && checkColourCorner(crbw, 4) &&
                       checkColourCorner(cgrw, 2) && checkColourCorner(cgrw, 3) &&
                       checkColourCorner(cbow, 3) && checkColourCorner(cbow, 4) &&
                       checkColourCorner(cgow, 1) && checkColourCorner(cgow, 2)) {
                cube.uRev().bRev().u().f().uRev().b().u().fRev();
            } else if (checkColourCorner(crbw, 1) && checkColourCorner(crbw, 2) &&
                       checkColourCorner(cgrw, 3) && checkColourCorner(cgrw, 4) &&
                       checkColourCorner(cbow, 2) && checkColourCorner(cbow, 3) &&
                       checkColourCorner(cgow, 4) && checkColourCorner(cgow, 1)) {
                cube.u().f().uRev().bRev().u().fRev().uRev().b();
            } else if (checkColourCorner(crbw, 3) && checkColourCorner(crbw, 4) &&
                       checkColourCorner(cgrw, 2) && checkColourCorner(cgrw, 3) &&
                       checkColourCorner(cbow, 1) && checkColourCorner(cbow, 2) &&
                       checkColourCorner(cgow, 4) && checkColourCorner(cgow, 1)) {
                cube.uRev().lRev().u().r().uRev().l().u().rRev();
            }
            crbw = GetCorner('R', 'B', 'W');
            cgrw = GetCorner('G', 'R', 'W');
            cbow = GetCorner('B', 'O', 'W');
            cgow = GetCorner('G', 'O', 'W');
        }
        while (cube[0][2][2] != 'W' || cube[1][2][0] != 'G' || cube[2][0][0] != 'R') {
            cube.rRev().dRev().r().d();
        }
        cube.u();
        while (cube[0][2][2] != 'W' || cube[1][2][0] != 'R' || cube[2][0][0] != 'B') {
            cube.rRev().dRev().r().d();
        }
        cube.u();
        while (cube[0][2][2] != 'W' || cube[1][2][0] != 'B' || cube[2][0][0] != 'O') {
            cube.rRev().dRev().r().d();
        }
        cube.u();
        while (cube[0][2][2] != 'W' || cube[1][2][0] != 'O' || cube[2][0][0] != 'G') {
            cube.rRev().dRev().r().d();
        }
        cube.u();
        cube.r().r().m().m().l().l();
    }

    mt19937 number;
};