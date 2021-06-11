#include <GL/glut.h>
#include "Initialize.hpp"

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    Cubic cubic;
    Algorithm worker(cubic);
    app = new Controls(worker);
    glutInitialize();
    cout << "conrols:" << endl;
    cout << "turn up side clockwise - w" << endl;
    cout << "turn up side counter-clockwise - shift + w" << endl;
    cout << "turn front side clockwise - s" << endl;
    cout << "turn front side counter-clockwise - shift + s" << endl;
    cout << "turn right side clockwise - d" << endl;
    cout << "turn right side counter-clockwise - shift + d" << endl;
    cout << "turn left side clockwise - a" << endl;
    cout << "turn left side counter-clockwise - shift + a" << endl;
    cout << "turn down side clockwise - x" << endl;
    cout << "turn down side counter-clockwise - shift + x" << endl;
    cout << "turn back side clockwise - f" << endl;
    cout << "turn back side counter-clockwise - shift + f" << endl;
    cout << "mixCube cube - m" << endl;
    cout << "solve cube - r" << endl;
    cout << "quit - q" << endl;
    glutMainLoop();
    app->deinit();
}
