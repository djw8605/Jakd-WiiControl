#ifndef EVENTS_H_
#define EVENTS_H_

/* To handle the window size changing */
void reshape(int w, int h);

/* To handle mouse events */
void mouse(int button, int state, int x, int y);

/* Keyboard events */
void keyboard(unsigned char key, int x, int y);

/* Special keyboard events */
void specialKeyboard(int key, int x, int y);



#endif /*EVENTS_H_*/
