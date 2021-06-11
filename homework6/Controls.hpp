#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>
#include "Interface.hpp"
#include "Algorithm.hpp"

using namespace std;

class Controls : public Application {

private:
    Cubic &cube;
    Algorithm &solveAlgorithm;
public:

    explicit Controls(Algorithm &w) : solveAlgorithm(w), cube(w.getCube()) {}

    void render(bool wired) {
        Application::renderText(10, 10, "Cube", GLUT_BITMAP_TIMES_ROMAN_10);
        for (int k = 0; k < 6; k++) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (wired) {
                        glColor3f(0.0, 0.0, 0.0);
                        glLineWidth(3.0);
                    } else {
                        switch (cube[k][i][j]) {
                            case 'R' :
                                glColor3f(1.0, 0.0, 0.0);
                                break;
                            case 'G':
                                glColor3f(0.0, 1.0, 0.0);
                                break;
                            case 'B':
                                glColor3f(0.0, 0.0, 1.0);
                                break;
                            case 'Y':
                                glColor3f(1.0, 1.0, 0.0);
                                break;
                            case 'W':
                                glColor3f(1.0, 1.0, 1.0);
                                break;
                            case 'O':
                                glColor3f(1.0, 0.65, 0.0);
                                break;
                        }
                    }
                    glBegin(GL_QUADS);

                    switch (k) {
                        case 0:
                            glVertex3f(-30.0 + 20 * i, 30.0, -30.0 + 20 * j);
                            glVertex3f(-30.0 + 20 * i, 30.0, -10.0 + 20 * j);
                            glVertex3f(-10.0 + 20 * i, 30.0, -10.0 + 20 * j);
                            glVertex3f(-10.0 + 20 * i, 30.0, -30.0 + 20 * j);
                            break;
                        case 1:
                            glVertex3f(-30.0 + 20 * i, -30.0 + 20 * (2 - j), 30.0);
                            glVertex3f(-10.0 + 20 * i, -30.0 + 20 * (2 - j), 30.0);
                            glVertex3f(-10.0 + 20 * i, -10.0 + 20 * (2 - j), 30.0);
                            glVertex3f(-30.0 + 20 * i, -10.0 + 20 * (2 - j), 30.0);
                            break;
                        case 2:
                            glVertex3f(30.0, -30.0 + 20 * (2 - j), -30.0 + 20 * (2 - i));
                            glVertex3f(30.0, -10.0 + 20 * (2 - j), -30.0 + 20 * (2 - i));
                            glVertex3f(30.0, -10.0 + 20 * (2 - j), -10.0 + 20 * (2 - i));
                            glVertex3f(30.0, -30.0 + 20 * (2 - j), -10.0 + 20 * (2 - i));
                            break;
                        case 3:
                            glVertex3f(-30.0 + 20 * (2 - i), -30.0 + 20 * (2 - j), -30.0);
                            glVertex3f(-30.0 + 20 * (2 - i), -10.0 + 20 * (2 - j), -30.0);
                            glVertex3f(-10.0 + 20 * (2 - i), -10.0 + 20 * (2 - j), -30.0);
                            glVertex3f(-10.0 + 20 * (2 - i), -30.0 + 20 * (2 - j), -30.0);
                            break;
                        case 4:
                            glVertex3f(-30.0, -30.0 + 20 * (2 - j), -30.0 + 20 * i);
                            glVertex3f(-30.0, -30.0 + 20 * (2 - j), -10.0 + 20 * i);
                            glVertex3f(-30.0, -10.0 + 20 * (2 - j), -10.0 + 20 * i);
                            glVertex3f(-30.0, -10.0 + 20 * (2 - j), -30.0 + 20 * i);
                            break;
                        case 5:
                            glVertex3f(-30.0 + 20 * i, -30.0, -30.0 + 20 * (2 - j));
                            glVertex3f(-10.0 + 20 * i, -30.0, -30.0 + 20 * (2 - j));
                            glVertex3f(-10.0 + 20 * i, -30.0, -10.0 + 20 * (2 - j));
                            glVertex3f(-30.0 + 20 * i, -30.0, -10.0 + 20 * (2 - j));
                            break;
                        default: {
                        }
                    }
                    glEnd();
                }
            }
        }
    }

    void controls(unsigned char case_) override {
        vector<string> str;
        switch (case_) {
            case 'w':
                solveAlgorithm.getCube().u();
                solveAlgorithm.status();
                break;
            case 'W':
                solveAlgorithm.getCube().uRev();
                solveAlgorithm.status();
                break;
            case 'd':
                solveAlgorithm.getCube().r();
                solveAlgorithm.status();
                break;
            case 'D':
                solveAlgorithm.getCube().rRev();
                solveAlgorithm.status();
                break;
            case 'a':
                solveAlgorithm.getCube().l();
                solveAlgorithm.status();
                break;
            case 'A':
                solveAlgorithm.getCube().lRev();
                solveAlgorithm.status();
                break;
            case 's':
                solveAlgorithm.getCube().fRev();
                solveAlgorithm.status();
                break;
            case 'S':
                solveAlgorithm.getCube().f();
                solveAlgorithm.status();
                break;
            case 'x':
                solveAlgorithm.getCube().d();
                solveAlgorithm.status();
                break;
            case 'X':
                solveAlgorithm.getCube().dRev();
                solveAlgorithm.status();
                break;
            case 'f':
                solveAlgorithm.getCube().b();
                solveAlgorithm.status();
                break;
            case 'F':
                solveAlgorithm.getCube().bRev();
                solveAlgorithm.status();
                break;
            case 'M':
                str = solveAlgorithm.mixCube(20);
                for (const string &s : str) {
                    cout << s << " ";
                }
                cout << endl;
                break;
            case 'm':
                str = solveAlgorithm.mixCube(10);
                for (const string &s : str) {
                    cout << s << " ";
                }
                cout << endl;
                break;
            case 'r':
                if (solveAlgorithm.isSolved())
                    cout << "Cube is solved" << endl;
                else if (solveAlgorithm.comleteCube()) {
                    cout << "Solving steps: ";
                    for (const auto &c : solveAlgorithm.getCube().result) {
                        cout << " " << c;
                    }
                    cout << " solved" << endl;
                } else {
                    cout << "Invalid cube." << endl;
                }
                break;
            case 'i': {
                solveAlgorithm.getCube().m();
                solveAlgorithm.status();
                break;
            }
            case 'q': {
                glutLeaveMainLoop();
            }
            default: {
            }
        }

        Application::controls(case_);
        Controls::display();
    }

    void display() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f(0.0, 1.0, 0.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_LINE);
        Controls::render(false);
        glColor3f(0.0, 0.0, 0.0);
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_NONE);
        Controls::render(true);
        Application::update();
    }

    const char *printTitle() override {
        return "Application";
    }
};