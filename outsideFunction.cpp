#include "InsideHead.h"
#include "OutsideHead.h"

const double XX = 1;
const double ZZ = 0.5;
const double lookAt[] = { XX, 0, -ZZ, 0, 0, 0, ZZ, 0, XX };
void timeCallBack(int value)
{
	glutPostRedisplay();
	if (value == start)
	{
		theSun.selfRotate += theSun.rotateStep;
		theSun.rotate[0] = theSun.selfRotate;

		theMercury.rotateAngle += theMercury.rotateStep;
		theMercury.selfRotateAngle += theMercury.selfRotateStep;
		theMercury.rotate[0] = theMercury.rotateAngle;
		theMercury.selfRotate[0] = theMercury.selfRotateAngle;

		theVenus.rotateAngle += theVenus.rotateStep;
		theVenus.selfRotateAngle += theVenus.selfRotateStep;
		theVenus.rotate[0] = theVenus.rotateAngle;
		theVenus.selfRotate[0] = theVenus.selfRotateAngle;

		theEarth.rotateAngle += theEarth.rotateStep;
		theEarth.selfRotateAngle += theEarth.selfRotateStep;
		theEarth.rotate[0] = theEarth.rotateAngle;
		theEarth.selfRotate[0] = theEarth.selfRotateAngle;

		theMoon.rotateAngle += theMoon.rotateStep;
		theMoon.selfRotateAngle += theMoon.selfRotateStep;
		theMoon.rotate[0] = theMoon.rotateAngle;
		theMoon.selfRotate[0] = theMoon.selfRotateAngle;

		theMars.rotateAngle += theMars.rotateStep;
		theMars.selfRotateAngle += theMars.selfRotateStep;
		theMars.rotate[0] = theMars.rotateAngle;
		theMars.selfRotate[0] = theMars.selfRotateAngle;

		theJupiter.rotateAngle += theJupiter.rotateStep;
		theJupiter.selfRotateAngle += theJupiter.selfRotateStep;
		theJupiter.rotate[0] = theJupiter.rotateAngle;
		theJupiter.selfRotate[0] = theJupiter.selfRotateAngle;

		theSaturn.rotateAngle += theSaturn.rotateStep;
		theSaturn.selfRotateAngle += theSaturn.selfRotateStep;
		theSaturn.rotate[0] = theSaturn.rotateAngle;
		theSaturn.selfRotate[0] = theSaturn.selfRotateAngle;
	}
	if (theSun.selfRotate >= 360)
		theSun.selfRotate = 0;

	if (theMercury.rotateAngle >= 360)
		theMercury.rotateAngle = 0;
	if (theMercury.selfRotateAngle >= 360)
		theMercury.selfRotateAngle = 0;

	if (theVenus.rotateAngle >= 360)
		theVenus.rotateAngle = 0;
	if (theVenus.selfRotateAngle >= 360)
		theVenus.selfRotateAngle = 0;

	if (theEarth.rotateAngle >= 360)
		theEarth.rotateAngle = 0;
	if (theEarth.selfRotateAngle >= 360)
		theEarth.selfRotateAngle = 0;

	if (theMoon.rotateAngle >= 360)
		theMoon.rotateAngle = 0;
	if (theMoon.selfRotateAngle >= 360)
		theMoon.selfRotateAngle = 0;

	if (theMars.rotateAngle >= 360)
		theMars.rotateAngle = 0;
	if (theMars.selfRotateAngle >= 360)
		theMars.selfRotateAngle = 0;

	if (theJupiter.rotateAngle >= 360)
		theJupiter.rotateAngle = 0;
	if (theJupiter.selfRotateAngle >= 360)
		theJupiter.selfRotateAngle = 0;

	if (theSaturn.rotateAngle >= 360)
		theSaturn.rotateAngle = 0;
	if (theSaturn.selfRotateAngle >= 360)
		theSaturn.selfRotateAngle = 0;

	glutTimerFunc(manager.Time, timeCallBack, manager.Value);
}
void specialKeys(int key, int x, int y)
{
	
}
void normalKeys(unsigned char key, int x, int y)
{
	if (key == 'q')
		exit(EXIT_SUCCESS);
	if (key == VK_ESCAPE)
		exit(EXIT_SUCCESS);
	static int count = 0;
	if (key == ' '&&count == 0)
	{
		manager.Value = stop;
		count = 1;
	}
	else if (key == ' '&&count == 1)
	{
		manager.Value = start;
		count = 0;
	}
	static int i = 0;
	char buffer[100];
	if (key == 'p')
	{
		sprintf(buffer, "data\\zhf%d.tga", ++i);
		gltGrabScreenTGA(buffer);
	}
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, texNumber[Background]);
	drawBackground();
	//开启光照0
	Light_0.SetLightPosition(0, 0, 0, 1);
	Light_0.Enable();
	Light_0.LightBegin();
	glPushMatrix();
	glLoadIdentity();
	glTranslated(0, 0, GolbalTranslateZ);
	Light_0.FlushLightPosition();
	gluLookAt(XX, 0, ZZ, 0, 0, 0, -ZZ, 0, XX);
	Light_0.FlushLightPosition();
	glPopMatrix();
	//draw the track
	drawTrack(theMercury.location[0]);
	drawTrack(theVenus.location[0]);
	drawTrack(theEarth.location[0]);
	drawTrack(theMars.location[0]);
	drawTrack(theJupiter.location[0]);
	drawTrack(theSaturn.location[0]);
	
	//draw the sun
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, texNumber[Sun]);
	Sphere sun(theSun.rolate);
	glLoadIdentity();
	sun.SphereTranslate(GolbalTranslate);//golbal translate
	sun.SphereLookAt(lookAt);
	sun.SphereTranslate(theSun.location);//set location
	sun.SphereRotate(theSun.rotate);//自转
	sun.draw(sun.SolidWithTexture);
	sun.SphereMatrixRecovery();

	glEnable(GL_LIGHTING);

	//draw the Mercury
	glBindTexture(GL_TEXTURE_2D, texNumber[Mercury]);
	Sphere mercury(theMercury.rolate);
	const float mercuryAmbient[4] = { 0.5, 0.5, 0.5, 1 };
	mercury.SphereMaterialAmbient(mercuryAmbient);
	glLoadIdentity();
	mercury.SphereTranslate(GolbalTranslate);//golbal translate
	mercury.SphereLookAt(lookAt);
	mercury.SphereRotate(theMercury.rotate);//公转
	mercury.SphereTranslate(theMercury.location);//set location
	mercury.SphereRotate(theMercury.selfRotate);//自转
	mercury.draw(mercury.SolidWithTexture);
	mercury.SphereMatrixRecovery();

	//draw the Venus
	glBindTexture(GL_TEXTURE_2D, texNumber[Venus]);
	Sphere venus(theVenus.rolate);
	const float venusAmbient[4] = { 0.5, 0.5, 0.5, 1 };
	venus.SphereMaterialAmbient(venusAmbient);
	glLoadIdentity();
	venus.SphereTranslate(GolbalTranslate);//golbal translate
	venus.SphereLookAt(lookAt);
	venus.SphereRotate(theVenus.rotate);//公转
	venus.SphereTranslate(theVenus.location);//set location
	venus.SphereRotate(theVenus.selfRotate);//自转
	venus.draw(mercury.SolidWithTexture);
	venus.SphereMatrixRecovery();

	//draw the Earth
	glBindTexture(GL_TEXTURE_2D, texNumber[Earth]);
	Sphere earth(theEarth.rolate);
	const float earthAmbient[4] = { 0.8, 0.8, 0.8, 1 };
	earth.SphereMaterialAmbient(earthAmbient);
	glLoadIdentity();
	earth.SphereTranslate(GolbalTranslate);//golbal translate
	earth.SphereLookAt(lookAt);
	earth.SphereRotate(theEarth.rotate);//公转
	earth.SphereTranslate(theEarth.location);//set location
	earth.SphereRotate(theEarth.selfRotate);//自转
	earth.draw(earth.SolidWithTexture);

	//draw the Moon
	glBindTexture(GL_TEXTURE_2D, texNumber[Moon]);
	Sphere moon(theMoon.rolate);
	const float moonAmbient[4] = { 0.6, 0.6, 0.6, 1 };
	moon.SphereMaterialAmbient(moonAmbient);
	moon.SphereRotate(theMoon.rotate);//公转
	moon.SphereTranslate(theMoon.location);//set location
	moon.SphereRotate(theMoon.selfRotate);//自转
	moon.draw(moon.SolidWithTexture);
	moon.SphereMatrixRecovery();
	earth.SphereMatrixRecovery();

	//draw the Mars
	glBindTexture(GL_TEXTURE_2D, texNumber[Mars]);
	Sphere mars(theMars.rolate);
	const float marsAmbient[4] = { 0.8, 0.8, 0.8, 1 };
	mars.SphereMaterialAmbient(marsAmbient);
	glLoadIdentity();
	mars.SphereTranslate(GolbalTranslate);//golbal translate
	mars.SphereLookAt(lookAt);
	mars.SphereRotate(theMars.rotate);//公转
	mars.SphereTranslate(theMars.location);//set location
	mars.SphereRotate(theMars.selfRotate);//自转
	mars.draw(mercury.SolidWithTexture);
	mars.SphereMatrixRecovery();

	//draw the Jupiter
	glBindTexture(GL_TEXTURE_2D, texNumber[Jupiter]);
	Sphere jupiter(theJupiter.rolate);
	const float jupiterAmbient[4] = { 0.6, 0.6, 0.6, 1 };
	jupiter.SphereMaterialAmbient(jupiterAmbient);
	glLoadIdentity();
	jupiter.SphereTranslate(GolbalTranslate);//golbal translate
	jupiter.SphereLookAt(lookAt);
	jupiter.SphereRotate(theJupiter.rotate);//公转
	jupiter.SphereTranslate(theJupiter.location);//set location
	jupiter.SphereRotate(theJupiter.selfRotate);//自转
	jupiter.draw(jupiter.SolidWithTexture);
	jupiter.SphereMatrixRecovery();

	//draw the Saturn
	Sphere saturn(theSaturn.rolate);
	const float saturnAmbient[4] = { 0.6, 0.6, 0.6, 1 };
	saturn.SphereMaterialAmbient(saturnAmbient);
	glLoadIdentity();
	saturn.SphereTranslate(GolbalTranslate);//golbal translate
	saturn.SphereLookAt(lookAt);
	saturn.SphereRotate(theSaturn.rotate);//公转
	saturn.SphereTranslate(theSaturn.location);//set location

	glBindTexture(GL_TEXTURE_2D, texNumber[SaturnHalo]);
	drawHalo(180, 400);

	saturn.SphereRotate(theSaturn.selfRotate);//自转
	glBindTexture(GL_TEXTURE_2D, texNumber[Saturn]);
	saturn.draw(saturn.SolidWithTexture);
	saturn.SphereMatrixRecovery();
	
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();
}
void drawHalo(double r1, double r2)
{
	const double precision = 50;
	double rMin = min(r1, r2);
	double rMax = max(r1, r2);
	double Pi = 3.14159265358979;
	glDisable(GL_CULL_FACE);
	glColor3d(1, 1, 1);
	glPushMatrix();
	glRotated(-5, 0, 0, 1);
	glBegin(GL_QUAD_STRIP);	
	for (double i = 0; i < 2 * Pi + 0.001*Pi; i += 2 * Pi / precision)
	{
		glTexCoord2d(i / Pi, 1);
		glVertex3d(rMin*cos(i), rMin*sin(i), 0);

		glTexCoord2d(i / Pi, 0);
		glVertex3d(rMax*cos(i), rMax*sin(i), 0);
	}
	glEnd();
	glPopMatrix();
	glEnable(GL_CULL_FACE);
}
void drawTrack(double rolate)
{
	const double Pi = 3.14159265358979;
	const double Floor = 2 * Pi + 0.01*Pi;
	const double Precision = 50;
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LINE_STIPPLE);
	glPushMatrix();
	glTranslated(0, 0, GolbalTranslateZ);
	gluLookAt(XX, 0, -ZZ, 0, 0, 0, ZZ, 0, XX);
	glLineStipple(0, 0x0003);
	glBegin(GL_LINE_LOOP);
	for (double i = 0; i < Floor; i += 2 * Pi / Precision)
		glVertex2d(rolate*cos(i), rolate*sin(i));
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();
}
void drawBackground()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glPushMatrix();
	glLoadIdentity();
	glTranslated(0, 0, GolbalTranslateZ);
	gluLookAt(XX, 0, ZZ, 0, 0, 0, -ZZ, 0, XX);
	glColor3d(1, 1, 1);
	double z = 2500;
	//celing
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0);
	glVertex3d(-z, -z, z);

	glTexCoord2d(0, 1);
	glVertex3d(z, -z, z);

	glTexCoord2d(1, 1);
	glVertex3d(z, z, z);

	glTexCoord2d(1, 0);
	glVertex3d(-z, z, z);
	glEnd();
	//ground
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0);
	glVertex3d(-z, -z, -z);

	glTexCoord2d(1, 0);
	glVertex3d(z, -z, -z);

	glTexCoord2d(1, 1);
	glVertex3d(z, z, -z);

	glTexCoord2d(0, 1);
	glVertex3d(-z, z, -z);
	glEnd();
	//left side
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0);
	glVertex3d(-z, -z, -z);

	glTexCoord2d(1, 0);
	glVertex3d(-z, -z, z);

	glTexCoord2d(1, 1);
	glVertex3d(z, -z, z);

	glTexCoord2d(0, 1);
	glVertex3d(z, -z, -z);
	glEnd();
	//back side
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0);
	glVertex3d(-z, -z, -z);

	glTexCoord2d(1, 0);
	glVertex3d(-z, -z, z);

	glTexCoord2d(1, 1);
	glVertex3d(-z, z, z);

	glTexCoord2d(0, 1);
	glVertex3d(-z, z, -z);
	glEnd();
	//right side
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0);
	glVertex3d(-z, z, -z);

	glTexCoord2d(1, 0);
	glVertex3d(-z, z, z);

	glTexCoord2d(1, 1);
	glVertex3d(z, z, z);

	glTexCoord2d(0, 1);
	glVertex3d(z, z, -z);
	glEnd();
	
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glPopMatrix();
}