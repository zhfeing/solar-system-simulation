#include "InsideHead.h"
#include "OutsideHead.h"
float LightingManager::lightPosition[4];
TimeManager manager(15, 1);
LightingManager Light_0(useLight0);
struct Sun theSun;
struct Mercury theMercury;
struct Venus theVenus;
struct Earth theEarth;
struct Moon theMoon;
struct Mars theMars;
struct Jupiter theJupiter;
struct Saturn theSaturn;
unsigned texNumber[ObjectAmount];

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1600, 900);
	glutInitWindowPosition(160, 90);
	glutCreateWindow("ZHF");
	
	init();
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
		
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(normalKeys);

	glutTimerFunc(manager.Time, timeCallBack, manager.Value);
	glutMainLoop();
	return 0;
}