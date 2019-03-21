#include "InsideHead.h"
#include "OutsideHead.h"
TimeManager::TimeManager()
{
	Time = 10;//default
	Step = 1;
	Value = 0;
}
TimeManager::TimeManager(int time, double step)
{
	Time = time;
	Step = step;
	Value = 0;
}
TimeManager::TimeManager(int time, double step, int value)
{
	Time = time;
	Step = step;
	Value = value;
}
void ChangeSize(int w, int h)
{
	double aspect = double(w) / double(h);
	const double zNear = -(1.0 - GoldenMean)*GolbalTranslateZ;
	const double zFar = -GolbalTranslateZ / (1.0 - GoldenMean);
	//const double ortho[] = { -320, 320, -180, 180, -200, 200 };
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(GolbalFovy, aspect, zNear, zFar);
}
void init()
{
	const float clearColor[] = { 0, 0, 0, 1 };
	glClearColor(0, 0, 0, 1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_RESCALE_NORMAL);
	glEnable(GL_NORMALIZE);//法线的模长取1
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	float light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.5f };//光的环境强度
	float light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };//光的散射强度
	float light_specular[] = { 0.5f, 0.5f, 0.5f, 0.0f };//光的镜面强度
	Light_0.SetLightAmbient(light_ambient);
	Light_0.SetLightDiffuse(light_diffuse);
	Light_0.SetLightSpecular(light_specular);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);//双面光照
	
	loadTexture("Earth.tga", Earth);
	loadTexture("Jupiter.tga", Jupiter);
	loadTexture("Mars.tga", Mars);
	loadTexture("Mercury.tga", Mercury);
	loadTexture("Moon.tga", Moon);	
	loadTexture("Saturn.tga", Saturn);
	loadTexture("Sun.tga", Sun);
	loadTexture("Venus.tga", Venus);
	loadTexture("SaturnHalo.tga", SaturnHalo);
	loadTexture("Background.tga", Background);
	InitalModle();

	printf("\t\t\tMade By 张皓飞\n\t\tPress 'Space' to stop; press 'p' to print screen\n");

}
void loadTexture(const char *buffer, ObjectNumber number)
{
	GLenum eformat;
	int w, h, c;
	glGenTextures(1, &texNumber[number]);
	glBindTexture(GL_TEXTURE_2D, texNumber[number]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	GLbyte *pImange = gltReadTGABits(buffer, &w, &h, &c, &eformat);
	glTexImage2D(GL_TEXTURE_2D, 0, c, w, h, 0, eformat, GL_UNSIGNED_BYTE, pImange);
	free(pImange);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}
void InitalModle()
{
	//sun initial
	theSun.location[0] = 0;
	theSun.location[1] = 0;
	theSun.location[2] = 0;
	theSun.rotate[0] = 0;
	theSun.rotate[1] = 0;
	theSun.rotate[2] = 0;
	theSun.rotate[3] = 1;

	//Mercury initial
	theMercury.location[0] = 300;
	theMercury.location[1] = 0;
	theMercury.location[2] = 0;
	theMercury.rotate[0] = theMercury.rotateAngle;
	theMercury.rotate[1] = 0;
	theMercury.rotate[2] = 0;
	theMercury.rotate[3] = 1;
	theMercury.selfRotate[0] = theMercury.selfRotateAngle;
	theMercury.selfRotate[1] = 0;
	theMercury.selfRotate[2] = 0;
	theMercury.selfRotate[3] = 1;

	//Venus initial
	theVenus.location[0] = 450;
	theVenus.location[1] = 0;
	theVenus.location[2] = 0;
	theVenus.rotate[0] = theVenus.rotateAngle;
	theVenus.rotate[1] = 0;
	theVenus.rotate[2] = 0;
	theVenus.rotate[3] = 1;
	theVenus.selfRotate[0] = theVenus.selfRotateAngle;
	theVenus.selfRotate[1] = 0;
	theVenus.selfRotate[2] = 0;
	theVenus.selfRotate[3] = 1;

	//Earth initial
	theEarth.location[0] = 680;
	theEarth.location[1] = 0;
	theEarth.location[2] = 0;
	theEarth.rotate[0] = theEarth.rotateAngle;
	theEarth.rotate[1] = 0;
	theEarth.rotate[2] = 0;
	theEarth.rotate[3] = 1;
	theEarth.selfRotate[0] = theEarth.selfRotateAngle;
	theEarth.selfRotate[1] = 0;
	theEarth.selfRotate[2] = 0;
	theEarth.selfRotate[3] = 1;

	//Moon initial
	theMoon.location[0] = 140;
	theMoon.location[1] = 0;
	theMoon.location[2] = 0;
	theMoon.rotate[0] = theMoon.rotateAngle;
	theMoon.rotate[1] = 0;
	theMoon.rotate[2] = 0;
	theMoon.rotate[3] = 1;
	theMoon.selfRotate[0] = theMoon.selfRotateAngle;
	theMoon.selfRotate[1] = 0;
	theMoon.selfRotate[2] = 0;
	theMoon.selfRotate[3] = 1;

	//Mars initial
	theMars.location[0] = 900;
	theMars.location[1] = 0;
	theMars.location[2] = 0;
	theMars.rotate[0] = theMars.rotateAngle;
	theMars.rotate[1] = 0;
	theMars.rotate[2] = 0;
	theMars.rotate[3] = 1;
	theMars.selfRotate[0] = theMars.selfRotateAngle;
	theMars.selfRotate[1] = 0;
	theMars.selfRotate[2] = 0;
	theMars.selfRotate[3] = 1;

	//Jupiter initial
	theJupiter.location[0] = 1300;
	theJupiter.location[1] = 0;
	theJupiter.location[2] = 0;
	theJupiter.rotate[0] = theJupiter.rotateAngle;
	theJupiter.rotate[1] = 0;
	theJupiter.rotate[2] = 0;
	theJupiter.rotate[3] = 1;
	theJupiter.selfRotate[0] = theJupiter.selfRotateAngle;
	theJupiter.selfRotate[1] = 0;
	theJupiter.selfRotate[2] = 0;
	theJupiter.selfRotate[3] = 1;

	//Saturn initial
	theSaturn.location[0] = 2000;
	theSaturn.location[1] = 0;
	theSaturn.location[2] = 0;
	theSaturn.rotate[0] = theSaturn.rotateAngle;
	theSaturn.rotate[1] = 0;
	theSaturn.rotate[2] = 0;
	theSaturn.rotate[3] = 1;
	theSaturn.selfRotate[0] = theSaturn.selfRotateAngle;
	theSaturn.selfRotate[1] = 0;
	theSaturn.selfRotate[2] = 0;
	theSaturn.selfRotate[3] = 1;
}