#include "Controls.hpp"

Application *app;

void windowFunc(const char* title) {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow(title);
}

void updateFunc() {
    app->update();
}

void displayFunc() {
    app->display();
    glFlush();
    glutSwapBuffers();
}

void mouseFunc(int button, int state, int x, int y) {
    app->mouse(button, state, x, y);
}

void reshapeFunc(int width, int height) {
    app->resize(width, height);
}

void keyboardFunc(unsigned char key, [[maybe_unused]] int x, [[maybe_unused]] int y) {
    app->controls(key);
}

void motionFunc(int x, int y) {
    app->mouseDrag(x, y);
}

void glutInitialize() {
    windowFunc(app -> printTitle());
    glutReshapeFunc(reshapeFunc);
    glutKeyboardFunc(keyboardFunc);
    glutDisplayFunc(displayFunc);
    glutIdleFunc(updateFunc);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    app -> initGraphics();
}