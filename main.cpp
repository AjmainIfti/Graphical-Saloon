#include <stdio.h>
#include<windows.h>
#include<map>
#include <GL/glut.h>
#include<iostream>
#include<math.h>
using namespace std;
void myMouse(int b, int s, int x1, int y1);
void myMouseMove(int x1, int y1);
GLfloat UpwardsScrollVelocity = -10.0;
float view = 10.0;
char quote[6][80];
int numberOfQuotes = 0;
bool done = false;
void timeTick(void);
void welcome(void);
void drawMenuBackground(void);
void RenderToDisplay();
void myDisplayFunction(void);
void drawInstructions(void);
void drawCredits(void);
void border(void);
void drawblank1();
void dress(void);
void myDisplay(void);
void myInit(void);
void DrawRazor();
void mouse(int mouse, int state, int a, int b);
void Face(void);
void keyboardown(unsigned char key, int x1, int y1);
void keyboardMenu(unsigned char key, int x1, int y1);
void keyboardown1(unsigned char key, int x1, int y1);
void hair(void);
void reshape(int w, int h);
void leap(void);
void collar(void);
int move_unit = 10;
bool move_razor = false;
void drawblank();
bool isInsideHair(int px, int py);
bool isInsideSkin(int px, int py);
bool isInsideBeardRegion(int px, int py);
void DrawScissor();
void razorholder(void);
void myDisplayFunc();
int winner(char a);
static int x = 400, double_shave = 0, y = 200, i = 0, m = 410, n = 110;
int blank[100000][2], count1[10000];
bool razor = false;
bool scissor = false;
static int dollar = 500;
int play();
std::map < std::pair<int, int>, int > Scores, dollarsdeduct, dollarsadd;
std::map<std::pair<int, int>, int >::iterator res;
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Start");
	glutDisplayFunc(myDisplayFunc);
	myInit();
	glutKeyboardFunc(keyboardMenu);
	glutMainLoop();
	cout << dollarsdeduct.size() * 5 << endl;
	return 0;
}
void myDisplayFunc() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPointSize(20.0);
	drawMenuBackground();
	welcome();
	drawInstructions();
	drawCredits();
	border();

	if (razor == true || scissor == true) {
		play();
		glutPostRedisplay();
	}

	glFlush();


}
int play() {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Graphical Saloon");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMouseFunc(myMouse);

	if (razor == true)
		glutKeyboardFunc(keyboardown);
	else if (scissor == true)
		glutKeyboardFunc(keyboardown1);
	glutPassiveMotionFunc(myMouseMove);

	glutMainLoop();
	return 0;
}
void myDisplay(void) {
	if (razor == true)
	{
		glClearColor(0.42f, 0.55f, 0.48f, 1.0f);
	}
	else if (scissor == true)
	{
		glClearColor(0.62f, 0.36f, 0.24f, 1.0f);
	}
	else
	{
		glClearColor(0.055f, 0.070f, 0.110f, 1.0f);
	}

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	razorholder();
	dress();
	hair();
	Face();
	if (done == true) {
		winner('1');
	}
	if (razor == true)
		drawblank();
	else if (scissor == true)
		drawblank1();

	DrawRazor();
	DrawScissor();
	leap();
	int i = dollarsadd.size() * 10 - dollarsdeduct.size() * 5 + 50;
	char buffer[10];
	_itoa_s(i, buffer, 10);

	float scoreScale = 0.3f;
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(2.0f);
	glPushMatrix();
	glTranslatef(20.0f, 400.0f, 0.0f);
	glScalef(scoreScale, scoreScale, 1.0f);
	for (int k = 0; buffer[k] != '\0'; k++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, buffer[k]);
	}
	glPopMatrix();
	glLineWidth(1.0f);

	glFlush();
}
void dress(void) {
	glColor3f(0, 0, 0.18);
	glBegin(GL_POLYGON);
	int r = 100, xc = 225, yc = 30;
	int P = 1 - r;
	int x1 = 0;
	int y1 = r;
	while (x1 <= y1) {
		if (P<0) {
			x1 = x1 + 1;
			P = P + (2 * x1) + 1;
		}
		else {
			x1 = x1 + 1;
			y1 = y1 - 1;
			P = P + (2 * x1) - (2 * y1) + 1;
		}
		glVertex2i(xc + x1, yc + y1);
		glVertex2i(xc + y1, yc + x1);
		glVertex2i(xc - y1, yc + x1);
		glVertex2i(xc - x1, yc + y1);
		glVertex2i(xc - x1, yc - y1);
		glVertex2i(xc - y1, yc - x1);
		glVertex2i(xc + y1, yc - x1);
		glVertex2i(xc + x1, yc - y1);
	}
	glEnd();
}
void leap(void) {
	int rx = 40, ry = 20;
	int xc = 230, yc = 180;
	int x1 = 0, y1 = ry;
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	int p = (ry*ry) - (rx*rx*ry) + ((rx*rx) / 4);
	while ((2 * x1*ry*ry)<(2 * y1*rx*rx)) {
		glVertex2i(xc + x1, yc - y1);
		glVertex2i(xc - x1, yc - y1);
		if (p<0) {
			x1 = x1 + 1;
			p = p + (2 * ry*ry*x1) + (ry*ry);
		}
		else {
			x1 = x1 + 1;
			y1 = y1 - 1;
			p = p + (2 * ry*ry*x1 + ry*ry) - (2 * rx*rx*y1);
		}
	}
	p = ((float)x1 + 0.5)*((float)x1 + 0.5)*ry*ry + (y1 - 1)*(y1 - 1)*rx*rx - rx*rx*ry*ry;
	while (y1>0) {
		glVertex2i(xc + x1, yc - y1);
		glVertex2i(xc - x1, yc - y1);
		if (p>0) {
			y1 = y1 - 1;
			p = p - (2 * rx*rx*y1) + (rx*rx);
		}
		else {
			y1 = y1 - 1;
			x1 = x1 + 1;
			p = p + (2 * ry*ry*x1) - (2 * rx*rx*y1) - (rx*rx);
		}
	}
	glEnd();

}
void hair(void) {
	glColor3f(.5, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(150, 100);
	glVertex2i(300, 100);
	glVertex2i(330, 150);
	glVertex2i(350, 245);
	glVertex2i(352, 325);
	glVertex2i(375, 410);
	glVertex2i(374, 430);
	glVertex2i(350, 450);
	glVertex2i(330, 460);
	glVertex2i(230, 430);
	glVertex2i(140, 400);
	glVertex2i(115, 370);
	glVertex2i(98, 353);
	glVertex2i(100, 335);
	glVertex2i(130, 160);
	glVertex2i(140, 150);
	glVertex2i(150, 100);
	glEnd();
}
void Face(void) {
	glColor3f(1.0, 0.84, 0.76);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(140, 200);
	glVertex2i(325, 200);
	glVertex2i(330, 310);
	glVertex2i(325, 340);
	glVertex2i(175, 380);
	glVertex2i(140, 350);
	glEnd();
	glColor3f(1.0, 0.68, 0.53);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(230, 210);
	glVertex2i(250, 240);
	glVertex2i(210, 240);
	glVertex2i(220, 225);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	int r = 25, xc = 180, yc = 290;
	int P = 1 - r;
	int x1 = 0;
	int y1 = r;
	while (x1 <= y1) {
		if (P<0) {
			x1 = x1 + 1;
			P = P + (2 * x1) + 1;
		}
		else {
			x1 = x1 + 1;
			y1 = y1 - 1;
			P = P + (2 * x1) - (2 * y1) + 1;
		}
		glVertex2i(xc + x1, yc + y1);
		glVertex2i(xc + y1, yc + x1);
		glVertex2i(xc - y1, yc + x1);
		glVertex2i(xc - x1, yc + y1);
		glVertex2i(xc - x1, yc - y1);
		glVertex2i(xc - y1, yc - x1);
		glVertex2i(xc + y1, yc - x1);
		glVertex2i(xc + x1, yc - y1);
	}
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	r = 25, xc = 280, yc = 290;
	P = 1 - r;
	x1 = 0;
	y1 = r;
	while (x1 <= y1) {
		if (P<0) {
			x1 = x1 + 1;
			P = P + (2 * x1) + 1;
		}
		else {
			x1 = x1 + 1;
			y1 = y1 - 1;
			P = P + (2 * x1) - (2 * y1) + 1;
		}
		glVertex2i(xc + x1, yc + y1);
		glVertex2i(xc + y1, yc + x1);
		glVertex2i(xc - y1, yc + x1);
		glVertex2i(xc - x1, yc + y1);
		glVertex2i(xc - x1, yc - y1);
		glVertex2i(xc - y1, yc - x1);
		glVertex2i(xc + y1, yc - x1);
		glVertex2i(xc + x1, yc - y1);
	}
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	r = 7, xc = 280, yc = 290;
	P = 1 - r;
	x1 = 0;
	y1 = r;
	while (x1 <= y1) {
		if (P<0) {
			x1 = x1 + 1;
			P = P + (2 * x1) + 1;
		}
		else {
			x1 = x1 + 1;
			y1 = y1 - 1;
			P = P + (2 * x1) - (2 * y1) + 1;
		}
		glVertex2i(xc + x1, yc + y1);
		glVertex2i(xc + y1, yc + x1);
		glVertex2i(xc - y1, yc + x1);
		glVertex2i(xc - x1, yc + y1);
		glVertex2i(xc - x1, yc - y1);
		glVertex2i(xc - y1, yc - x1);
		glVertex2i(xc + y1, yc - x1);
		glVertex2i(xc + x1, yc - y1);
	}
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	r = 7, xc = 180, yc = 290;
	P = 1 - r;
	x1 = 0;
	y1 = r;
	while (x1 <= y1) {
		if (P<0) {
			x1 = x1 + 1;
			P = P + (2 * x1) + 1;
		}
		else {
			x1 = x1 + 1;
			y1 = y1 - 1;
			P = P + (2 * x1) - (2 * y1) + 1;
		}
		glVertex2i(xc + x1, yc + y1);
		glVertex2i(xc + y1, yc + x1);
		glVertex2i(xc - y1, yc + x1);
		glVertex2i(xc - x1, yc + y1);
		glVertex2i(xc - x1, yc - y1);
		glVertex2i(xc - y1, yc - x1);
		glVertex2i(xc + y1, yc - x1);
		glVertex2i(xc + x1, yc - y1);
	}
	glEnd();

	int rx = 30, ry = 15;
	xc = 180, yc = 320;
	x1 = 0, y1 = ry;
	glColor3f(0.5, 0.0, 0.0);
	glBegin(GL_POINTS);
	int p = (ry*ry) - (rx*rx*ry) + ((rx*rx) / 4);
	while ((2 * x1*ry*ry)<(2 * y1*rx*rx)) {

		glVertex2i(xc - x1, yc + y1);
		glVertex2i(xc + x1, yc + y1);

		if (p<0) {
			x1 = x1 + 1;
			p = p + (2 * ry*ry*x1) + (ry*ry);
		}
		else {
			x1 = x1 + 1;
			y1 = y1 - 1;
			p = p + (2 * ry*ry*x1 + ry*ry) - (2 * rx*rx*y1);
		}
	}
	p = ((float)x1 + 0.5)*((float)x1 + 0.5)*ry*ry + (y1 - 1)*(y1 - 1)*rx*rx - rx*rx*ry*ry;
	while (y1>0) {

		glVertex2i(xc - x1, yc + y1);
		glVertex2i(xc + x1, yc + y1);

		if (p>0) {
			y1 = y1 - 1;
			p = p - (2 * rx*rx*y1) + (rx*rx);
		}
		else {
			y1 = y1 - 1;
			x1 = x1 + 1;
			p = p + (2 * ry*ry*x1) - (2 * rx*rx*y1) - (rx*rx);
		}
	}
	glEnd();

	rx = 30, ry = 15;
	xc = 280, yc = 320;
	x1 = 0, y1 = ry;
	glColor3f(0.5, 0.0, 0.0);
	glBegin(GL_POINTS);
	p = (ry*ry) - (rx*rx*ry) + ((rx*rx) / 4);
	while ((2 * x1*ry*ry)<(2 * y1*rx*rx)) {

		glVertex2i(xc - x1, yc + y1);
		glVertex2i(xc + x1, yc + y1);

		if (p<0) {
			x1 = x1 + 1;
			p = p + (2 * ry*ry*x1) + (ry*ry);
		}
		else {
			x1 = x1 + 1;
			y1 = y1 - 1;
			p = p + (2 * ry*ry*x1 + ry*ry) - (2 * rx*rx*y1);
		}
	}
	p = ((float)x1 + 0.5)*((float)x1 + 0.5)*ry*ry + (y1 - 1)*(y1 - 1)*rx*rx - rx*rx*ry*ry;
	while (y1>0) {

		glVertex2i(xc - x1, yc + y1);
		glVertex2i(xc + x1, yc + y1);

		if (p>0) {
			y1 = y1 - 1;
			p = p - (2 * rx*rx*y1) + (rx*rx);
		}
		else {
			y1 = y1 - 1;
			x1 = x1 + 1;
			p = p + (2 * ry*ry*x1) - (2 * rx*rx*y1) - (rx*rx);
		}
	}
	glEnd();
}
void razorholder(void) {
	int m0 = 410, n0 = 110;
	glColor3f(0.75, 0.75, 0.75);
	glBegin(GL_POLYGON);
	glVertex2i(m0 - 11, n0 + 2);
	glVertex2i(m0 + 24, n0 + 45);
	glVertex2i(m0 - 16, n0 + 5);
	glVertex2i(m0 - 11, n0 + 2);
	glEnd();
	glColor3f(0.75, 0.75, 0.75);
	glBegin(GL_POLYGON);
	glVertex2i(m0, n0);
	glVertex2i(m0 + 14, n0 + 65);
	glVertex2i(m0 - 6, n0);
	glVertex2i(m0, n0);
	glEnd();
	glColor3f(.5, .5, 0.75);
	glBegin(GL_POLYGON);
	glVertex2i(388, 110);
	glVertex2i(435, 110);
	glVertex2i(435, 180);
	glVertex2i(388, 180);
	glEnd();
	glColor3f(1, .5, 0.75);
	glBegin(GL_POLYGON);
	glVertex2i(388, 180);
	glVertex2i(435, 180);
	glVertex2i(435, 230);
	glVertex2i(388, 230);
	glEnd();
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(388, 230);
	glVertex2i(411, 240);
	glEnd();
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(435, 230);
	glVertex2i(411, 240);
	glEnd();
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex2i(411, 240);
	glEnd();

	glColor3f(0.75, 0.75, 0.75);
	int x0 = 400, y0 = 200;
	glBegin(GL_POLYGON);
	glVertex2i(x0, y0);
	glVertex2i(x0 + 20, y0 + 20);
	glVertex2i(x0 + 15, y0 + 25);
	glVertex2i(x0 - 5, y0 + 5);
	glEnd();
	glColor3f(0.75, 0.75, 0.75);
	glBegin(GL_POLYGON);
	glVertex2i(x0 + 3, y0 - 3);
	glVertex2i(x0 + 23, y0 + 17);
	glVertex2i(x0 + 20, y0 + 20);
	glVertex2i(x0, y0);
	glEnd();
	glColor3f(0.75, 0.75, 0.75);
	glBegin(GL_POLYGON);
	glVertex2i(x0 + 25, y0 - 15);
	glVertex2i(x0 + 30, y0 - 12);
	glVertex2i(x0 + 11, y0 + 15);
	glVertex2i(x0 + 6, y0 + 13);
	glEnd();

}
void DrawRazor() {


	glColor3f(0.4, 0, 1.2);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x + 20, y + 20);
	glVertex2i(x + 15, y + 25);
	glVertex2i(x - 5, y + 5);
	glEnd();
	glColor3f(1.0, 0, 1.2);
	glBegin(GL_POLYGON);
	glVertex2i(x + 3, y - 3);
	glVertex2i(x + 23, y + 17);
	glVertex2i(x + 20, y + 20);
	glVertex2i(x, y);
	glEnd();
	glColor3f(0.4, 0, 1.2);
	glBegin(GL_POLYGON);
	glVertex2i(x + 25, y - 15);
	glVertex2i(x + 30, y - 12);
	glVertex2i(x + 11, y + 15);
	glVertex2i(x + 6, y + 13);
	glEnd();

}
void DrawScissor() {

	glColor3f(1.0, 0, 1.2);
	glBegin(GL_POLYGON);
	glVertex2i(m - 11, n + 2);
	glVertex2i(m + 24, n + 45);
	glVertex2i(m - 16, n + 5);
	glVertex2i(m - 11, n + 2);

	glEnd();

	glColor3f(0.4, 0.2, 1.8);
	glBegin(GL_POLYGON);
	glVertex2i(m, n);
	glVertex2i(m + 14, n + 65);
	glVertex2i(m - 6, n);
	glVertex2i(m, n);

	glEnd();
}
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 1.0, 3200);
	glMatrixMode(GL_MODELVIEW);
}
bool isInsideHair(int px, int py) {
	static const int hairX[] = { 150, 300, 330, 350, 352, 375, 374, 350, 330, 230, 140, 115, 98, 100, 130, 140 };
	static const int hairY[] = { 100, 100, 150, 245, 325, 410, 430, 450, 460, 430, 400, 370, 353, 335, 160, 150 };
	const int n = 16;
	bool inside = false;
	int j = n - 1;
	for (int k = 0; k < n; k++) {
		if (((hairY[k] > py) != (hairY[j] > py)) &&
			(px < (hairX[j] - hairX[k]) * (float)(py - hairY[k]) / (float)(hairY[j] - hairY[k]) + hairX[k])) {
			inside = !inside;
		}
		j = k;
	}
	return inside;
}
bool isInsideSkin(int px, int py) {
	static const int faceX[] = { 140, 325, 330, 325, 175, 140 };
	static const int faceY[] = { 200, 200, 310, 340, 380, 350 };
	const int n = 6;
	bool inside = false;
	int j = n - 1;
	for (int k = 0; k < n; k++) {
		if (((faceY[k] > py) != (faceY[j] > py)) &&
			(px < (faceX[j] - faceX[k]) * (float)(py - faceY[k]) / (float)(faceY[j] - faceY[k]) + faceX[k])) {
			inside = !inside;
		}
		j = k;
	}
	return inside;
}
bool isInsideBeardRegion(int px, int py) {
	if (py < 100 || py > 200) {
		return false;
	}

	static const int leftX[] = { 150, 140, 130, 100 };
	static const int leftY[] = { 100, 150, 160, 335 };
	static const int rightX[] = { 300, 330, 350 };
	static const int rightY[] = { 100, 150, 245 };

	float xMin = (float)leftX[0];
	for (int k = 0; k < 3; k++) {
		if (py >= leftY[k] && py <= leftY[k + 1]) {
			float t = (float)(py - leftY[k]) / (float)(leftY[k + 1] - leftY[k]);
			xMin = leftX[k] + t * (leftX[k + 1] - leftX[k]);
			break;
		}
	}

	float xMax = (float)rightX[0];
	for (int k = 0; k < 2; k++) {
		if (py >= rightY[k] && py <= rightY[k + 1]) {
			float t = (float)(py - rightY[k]) / (float)(rightY[k + 1] - rightY[k]);
			xMax = rightX[k] + t * (rightX[k + 1] - rightX[k]);
			break;
		}
	}

	return (px >= xMin && px <= xMax);
}
void drawblank() {
	int c = i;

	for (int j = 0; j<c; j++) {

		int a = blank[j][0], b = blank[j][1];


		if (!isInsideBeardRegion(a, b)) {
			continue;
		}

		glColor3f(1.0, 0.84, 0.76);
		glBegin(GL_POLYGON);
		glVertex2i(a, b);
		glVertex2i(a + 10, b);
		glVertex2i(a + 10, b + 10);
		glVertex2i(a, b + 10);
		glEnd();
		if (count1[j] >= 1) {
			glColor3f(1, 0, 0);
			glBegin(GL_POINTS);
			glVertex2i(a + 2, b + 2);
			glVertex2i(a + 5, b + 4);
			glEnd();
			dollarsdeduct.insert(make_pair(make_pair(a, b), 5));

		}
		else {
			dollarsadd.insert(make_pair(make_pair(a, b), 5));

		}
	}
}
void drawblank1() {
	int c = i;

	for (int j = 0; j<c; j++) {

		int a = blank[j][0], b = blank[j][1];

		if ((a >= 150 && a <= 210 && b >= 305 && b <= 335) ||
			(a >= 250 && a <= 310 && b >= 305 && b <= 335)) {
			dollarsdeduct.insert(make_pair(make_pair(a, b), 5));
		}

		if (!isInsideHair(a, b) || isInsideSkin(a, b)) {
			continue;
		}

		glColor3f(1.0, 0.84, 0.76);
		glBegin(GL_POLYGON);
		glVertex2i(a, b);
		glVertex2i(a + 10, b);
		glVertex2i(a + 10, b + 10);
		glVertex2i(a, b + 10);
		glEnd();

		dollarsadd.insert(make_pair(make_pair(a, b), 5));
	}
}
void keyboardown(unsigned char key, int x1, int y1) {
	if (key == 'd') {
		x += move_unit;
		if (x >= 500)
			x = 0;
		glutPostRedisplay();
	}
	else if (key == 'a') {
		x -= move_unit;
		if (x <= 0)
			x = 500;
		glutPostRedisplay();
	}
	else if (key == 'w') {
		y += move_unit;
		if (y >= 500)
			y = 0;
		glutPostRedisplay();
	}

	else if (key == 's') {
		y -= move_unit;
		if (y <= 0)
			y = 500;
		glutPostRedisplay();
	}
	else if (key == 'g') {
		blank[i][0] = x + 7.5;
		blank[i][1] = y + 12.5;
		res = Scores.find(make_pair(blank[i][0], blank[i][1]));
		if (res == Scores.end()) {
			Scores.insert(make_pair(make_pair(blank[i][0], blank[i][1]), count1[i]));
			i++;
		}
		else {
			count1[i]++;
			Scores[make_pair(blank[i][0], blank[i][1])] = count1[i];
		}
		glutPostRedisplay();
	}
	else if (key == 'q') {
		done = true;
		glutPostRedisplay();
	}


}
void keyboardMenu(unsigned char key, int x1, int y1) {
	if (key == 's' || key == 'S') {
		razor = true;
		glutPostRedisplay();
	}
	else if (key == 'h' || key == 'H') {
		scissor = true;
		glutPostRedisplay();
	}
}
void keyboardown1(unsigned char key, int x1, int y1) {


	if (key == 'd') {
		m += move_unit;
		if (m >= 500)
			m = 0;
		glutPostRedisplay();
	}
	else if (key == 'a') {
		m -= move_unit;
		if (m <= 0)
			m = 500;
		glutPostRedisplay();
	}
	else if (key == 'w') {
		n += move_unit;
		if (n >= 500)
			n = 0;
		glutPostRedisplay();
	}

	else if (key == 's') {
		n -= move_unit;
		if (n <= 0)
			n = 500;
		glutPostRedisplay();
	}
	else if (key == 'g') {
		blank[i][0] = m + 7.5;
		blank[i][1] = n + 12.5;
		res = Scores.find(make_pair(blank[i][0], blank[i][1]));
		if (res == Scores.end()) {
			Scores.insert(make_pair(make_pair(blank[i][0], blank[i][1]), count1[i]));
			i++;
		}
		else {
			count1[i]++;
			Scores[make_pair(blank[i][0], blank[i][1])] = count1[i];
		}
		glutPostRedisplay();
	}
	else if (key == 'q') {
		done = true;
		glutPostRedisplay();
	}

}
void RenderToDisplay() {
	int l, lenghOfQuote, i;

	glTranslatef(0.0, -100, UpwardsScrollVelocity);
	glRotatef(-20, 1.0, 0.0, 0.0);
	glScalef(0.1, 0.1, 0.1);



	for (l = 0; l<numberOfQuotes; l++)
	{
		lenghOfQuote = (int)strlen(quote[l]);
		glPushMatrix();
		glTranslatef(-(lenghOfQuote * 37), -(l * 200), 0.0);
		for (i = 0; i < lenghOfQuote; i++)
		{
			glColor3f((UpwardsScrollVelocity / 10) + 300 + (l * 10), (UpwardsScrollVelocity / 10) + 300 + (l * 10), 0.0);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);


		}
		glPopMatrix();
	}

}
void myDisplayFunction(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 30.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	RenderToDisplay();
	glutSwapBuffers();
}
void drawMenuBackground(void) {
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	glColor3f(0.98f, 0.89f, 0.68f); glVertex2i(0, 512);
	glColor3f(0.98f, 0.89f, 0.68f); glVertex2i(500, 512);
	glColor3f(0.40f, 0.13f, 0.10f); glVertex2i(500, 0);
	glColor3f(0.40f, 0.13f, 0.10f); glVertex2i(0, 0);
	glEnd();
	glShadeModel(GL_FLAT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	int cx = 250, cy = 390;
	for (int k = 6; k >= 1; k--) {
		float alpha = 0.05f * (7 - k);
		glColor4f(1.0f, 0.96f, 0.80f, alpha);
		int rx = 34 * k, ry = 16 * k;
		glBegin(GL_POLYGON);
		for (int a = 0; a < 360; a += 10) {
			float rad = a * 3.14159265f / 180.0f;
			glVertex2f(cx + rx * cosf(rad), cy + ry * sinf(rad));
		}
		glEnd();
	}
	glDisable(GL_BLEND);
}
void welcome(void) {

	const char* text = "Welcome to Graphical Saloon";
	float maxTextWidth = 440.0f;

	float totalWidth = 0.0f;
	for (const char* p = text; *p != '\0'; p++) {
		totalWidth += glutStrokeWidth(GLUT_STROKE_ROMAN, *p);
	}
	float scale = maxTextWidth / totalWidth;
	float scaledWidth = totalWidth * scale;
	float startX = (500.0f - scaledWidth) / 2.0f;
	float startY = 350.0f;

	glColor3f(0.25f, 0.05f, 0.03f);
	glLineWidth(3.5f);
	glPushMatrix();
	glTranslatef(startX, startY, 0.0f);
	glScalef(scale, scale, 1.0f);
	for (const char* p = text; *p != '\0'; p++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	}
	glPopMatrix();
	glLineWidth(1.0f);
}
void drawInstructions(void) {
	const char* text = "Press H for Haircutting  or  Press S for Shaving";
	float maxTextWidth = 400.0f;

	float totalWidth = 0.0f;
	for (const char* p = text; *p != '\0'; p++) {
		totalWidth += glutStrokeWidth(GLUT_STROKE_ROMAN, *p);
	}
	float scale = maxTextWidth / totalWidth;
	float scaledWidth = totalWidth * scale;
	float startX = (500.0f - scaledWidth) / 2.0f;
	float startY = 240.0f;

	glColor3f(0.25f, 0.05f, 0.03f);
	glLineWidth(3.0f);
	glPushMatrix();
	glTranslatef(startX, startY, 0.0f);
	glScalef(scale, scale, 1.0f);
	for (const char* p = text; *p != '\0'; p++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	}
	glPopMatrix();
	glLineWidth(1.0f);
}
void drawCredits(void) {
	static const char* lines[4] = {
		"A simple graphics project by",
		"Ajmain Iktidar Rahman (233005912)",
		"Tahiat Farhana Subha (233032412)",
		"Mohammad Zaied (233006512)"
	};
	const int numLines = 4;
	float maxTextWidth = 290.0f;
	float lineSpacing = 26.0f;
	float startY = 175.0f;


	float widths[numLines];
	float maxWidth = 0.0f;
	for (int lineIdx = 0; lineIdx < numLines; lineIdx++) {
		float w = 0.0f;
		for (const char* p = lines[lineIdx]; *p != '\0'; p++) {
			w += glutStrokeWidth(GLUT_STROKE_ROMAN, *p);
		}
		widths[lineIdx] = w;
		if (w > maxWidth) maxWidth = w;
	}
	float scale = maxTextWidth / maxWidth;

	glColor3f(0.30f, 0.15f, 0.08f);
	glLineWidth(3.0f);

	for (int lineIdx = 0; lineIdx < numLines; lineIdx++) {
		float scaledWidth = widths[lineIdx] * scale;
		float startX = (500.0f - scaledWidth) / 2.0f;
		float lineY = startY - lineIdx * lineSpacing;

		glPushMatrix();
		glTranslatef(startX, lineY, 0.0f);
		glScalef(scale, scale, 1.0f);
		for (const char* p = lines[lineIdx]; *p != '\0'; p++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
		}
		glPopMatrix();
	}
	glLineWidth(1.0f);
}
void border(void) {

	glBegin(GL_POLYGON);
	glColor3f(0.72, 0.55, 0.15);

	glVertex2i(0, 75);
	glVertex2i(512, 75);
	glVertex2i(512, 80);
	glVertex2i(0, 80);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.72, 0.55, 0.15);
	glVertex2i(0, 445);
	glVertex2i(512, 445);
	glVertex2i(512, 450);
	glVertex2i(0, 450);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.72, 0.55, 0.15);
	glVertex2i(10, 75);
	glVertex2i(15, 75);
	glVertex2i(15, 450);
	glVertex2i(10, 450);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.72, 0.55, 0.15);
	glVertex2i(485, 75);
	glVertex2i(490, 75);
	glVertex2i(490, 450);
	glVertex2i(485, 450);
	glEnd();
}
void myInit(void) {

	glClearColor(0.055f, 0.070f, 0.110f, 1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 512.0);
}
int winner(char a) {
	strcpy_s(quote[0], "Customer");

	strcpy_s(quote[1], "Is ");
	if (dollarsadd.size()>dollarsdeduct.size() && razor == true && dollarsadd.size() >= 40) {
		strcpy_s(quote[2], ":) ");
		strcpy_s(quote[3], "happy ");

	}

	else if (dollar>dollar - dollarsdeduct.size() * 5 && scissor == true) {
		strcpy_s(quote[2], ":) ");
		strcpy_s(quote[3], "happy ");
	}
	else {
		strcpy_s(quote[2], ":(");
		strcpy_s(quote[3], "sad ");
	}
	numberOfQuotes = 5;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Game Result");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glLineWidth(3);

	glutDisplayFunc(myDisplayFunction);
	glutReshapeFunc(reshape);
	glutIdleFunc(timeTick);
	glutMainLoop();

	return 0;
}
void timeTick(void) {
	if (UpwardsScrollVelocity< -600)
		view -= 0.000011;
	if (view < 0) { view = 20; UpwardsScrollVelocity = -10.0; }

	UpwardsScrollVelocity -= 0.1;
	glutPostRedisplay();

}
void myMouse(int b, int s, int x1, int y1) {
	if (s == GLUT_DOWN) {


		if (b == GLUT_LEFT_BUTTON&&razor == true) {
			blank[i][0] = x + 7.5;
			blank[i][1] = y + 12.5;
			res = Scores.find(make_pair(blank[i][0], blank[i][1]));
			if (res == Scores.end()) {
				Scores.insert(make_pair(make_pair(blank[i][0], blank[i][1]), count1[i]));
				i++;
			}
			else {
				count1[i]++;
				Scores[make_pair(blank[i][0], blank[i][1])] = count1[i];
			}

		}
		else if (b == GLUT_LEFT_BUTTON&&scissor == true) {
			blank[i][0] = m + 7.5;
			blank[i][1] = n + 12.5;
			res = Scores.find(make_pair(blank[i][0], blank[i][1]));
			if (res == Scores.end()) {
				Scores.insert(make_pair(make_pair(blank[i][0], blank[i][1]), count1[i]));
				i++;
			}
			else {
				count1[i]++;
				Scores[make_pair(blank[i][0], blank[i][1])] = count1[i];
			}

		}
	}

}

int mouseChange = 3;
int tempY = 0;
int tempX = 0;
void myMouseMove(int x1, int y1)
{
	int winW = glutGet(GLUT_WINDOW_WIDTH);
	int winH = glutGet(GLUT_WINDOW_HEIGHT);
	if (winW <= 0) winW = 1366;
	if (winH <= 0) winH = 768;

	const float orthoWidth = 500.0f;
	const float orthoHeight = 512.0f;

	float scaledX = (x1 / (float)winW) * orthoWidth;
	float scaledY = orthoHeight - (y1 / (float)winH) * orthoHeight;

	if (razor == true) {
		x = (int)scaledX;
		y = (int)scaledY;
	}
	else if (scissor == true)
	{
		m = (int)scaledX;
		n = (int)scaledY;
	}

	glutPostRedisplay();
}
