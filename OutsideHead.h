#pragma once
#ifndef _INC_OUTSIDEHEAD
#define _INC_OUTIDEHEAD

#include "InsideHead.h"
using namespace std;

enum ObjectNumber
{
	Sun, Mercury, Venus, Earth, Moon, Mars, Jupiter, Saturn, SaturnHalo, Background
};
enum LightNumber
{
	useLight0 = GL_LIGHT0, useLight1 = GL_LIGHT1, useLight2 = GL_LIGHT2, useLight3 = GL_LIGHT3,
	useLight4 = GL_LIGHT4, useLight5 = GL_LIGHT5, useLight6 = GL_LIGHT6, useLight7 = GL_LIGHT7,
};
class Sphere
{
public:
	enum Spheretype
	{
		SolidWithTexture, Solid,Wire
	};
	Sphere(double rolate);
	void SphereGetLocation(double *location);
	void SphereLookAt(const double *lookAt);
	void SphereTranslate(const double *vector);
	void SphereRotate(double *rotate);
	void SphereRotate(double angle, double x, double y, double z);
	void SphereChangeColor(const double *color);
	void SphereChangeLineWidth(float width);
	void draw(Spheretype);
	void drawSphere();
	void SphereMaterialAmbient(const float *ambient);
	void SphereMaterialDiffuse(const float *diffuse);
	void SphereMaterialSpecular(const float *specular);
	void SphereMaterialShine(const float lowShine);
	void SphereMatrixRecovery();
private:
	double SphereRolate;//半径
	double SphereLocation[3];//位置
	double SphereColor[3];
	double SphereAlpha = 1.0;//Alpha值
	float SphereLineWidth = 1.0f;
	const int slices = 50;
	const int stacks = 50;
	float SphereAmbient[4];//材料的环境颜色
	float SphereDiffuse[4];//材料的散射颜色
	float SphereSpecular[4];//材料的镜面强度
	float SphereLowShine[1];//材料的反光斑大小 (1-127)
};

class LightingManager
{
	
public:
	LightingManager(LightNumber number);
	void LightBegin();
	void SetLightAmbient(const float *ambient);//设置光的环境强度
	void SetLightModelAmbient(const float *ambient);//设置光的模型的强度
	void SetLightDiffuse(const float *diffuse);//设置光的散射强度
	void SetLightSpecular(const float *speculat);//设置光的镜面强度
	void SetLightPosition(const float *position);
	void SetLightPosition(const float, const float, const float, const float);
	void FlushLightPosition();
	void EnableTwoSideLighting();
	void Disable();
	void Enable();
private:
	LightNumber lightNumber = useLight0;
	static float lightPosition[4];
	float lightAmbient[4];
	float lightDiffuse[4];
	float lightSpecular[4];
};
extern LightingManager Light_0;
extern TimeManager manager;

struct Sun
{
	double selfRotate = 0;
	const double rolate = 200;
	const double rotateStep = 0.08;
	double location[3];
	double rotate[4];
};
struct Mercury
{
	double selfRotateAngle = 0;
	const double selfRotateStep = 0.04;
	double rotateAngle = 0;
	const double rotateStep = 2;
	const double rolate = 50;
	double location[3];
	double selfRotate[4];
	double rotate[4];
};
struct Venus
{
	double selfRotateAngle = 0;
	const double selfRotateStep = 0.02;
	double rotateAngle = 0;
	const double rotateStep = 0.428;
	const double rolate = 80;
	double location[3];
	double selfRotate[4];
	double rotate[4];
};
struct Earth
{
	double selfRotateAngle = 0;
	const double selfRotateStep = 0.5;
	double rotateAngle = 0;
	const double rotateStep = 0.5;
	const double rolate = 100;
	double location[3];
	double selfRotate[4];
	double rotate[4];
};
struct Moon
{
	double selfRotateAngle = 0;
	const double selfRotateStep = 0.05;
	double rotateAngle = 0;
	const double rotateStep = 0.05;
	const double rolate = 20;
	double location[3];
	double selfRotate[4];
	double rotate[4];
};
struct Mars
{
	double selfRotateAngle = 0;
	const double selfRotateStep = 0.5;
	double rotateAngle = 0;
	const double rotateStep = 0.30;
	const double rolate = 30;
	double location[3];
	double selfRotate[4];
	double rotate[4];
};
struct Jupiter
{
	double selfRotateAngle = 0;
	const double selfRotateStep = 1.2;
	double rotateAngle = 0;
	const double rotateStep = 0.15;
	const double rolate = 200;
	double location[3];
	double selfRotate[4];
	double rotate[4];
};
struct Saturn
{
	double selfRotateAngle = 0;
	const double selfRotateStep = 1.2;
	double rotateAngle = 0;
	const double rotateStep = 0.05;
	const double rolate = 175;
	double location[3];
	double selfRotate[4];
	double rotate[4];
};

extern struct Sun theSun;
extern struct Mercury theMercury;
extern struct Venus theVenus;
extern struct Earth theEarth;
extern struct Moon theMoon;
extern struct Mars theMars;
extern struct Jupiter theJupiter;
extern struct Saturn theSaturn;

const int ObjectAmount = 10;
extern unsigned texNumber[ObjectAmount];

const double GolbalTranslate[3] = { 0, 0, GolbalTranslateZ };
void drawHalo(double r1, double r2);
void drawTrack(double rolate);
void specialKeys(int key, int x, int y);
void timeCallBack(int value);
void RenderScene();
void normalKeys(unsigned char key, int x, int y);
void loadTexture(const char *buffer, ObjectNumber number);
void InitalModle();
void drawBackground();
#endif