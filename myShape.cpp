#include "OutsideHead.h"

Sphere::Sphere(double rolate)
{
	for (int i = 0; i < 3; i++)
	{
		SphereColor[i] = 1.0;
		SphereAmbient[i] = 0.1f;
		SphereDiffuse[i] = 1.0;
		SphereSpecular[i] = 0.5;
		SphereLocation[i] = 0;
	}
	SphereAmbient[3] = 1.0;
	SphereDiffuse[3] = 1.0;
	SphereSpecular[3] = 1.0;
	SphereLowShine[0] = { 50 };
	SphereRolate = rolate;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
}
void Sphere::drawSphere()
{
	const double Pi = 3.14159265358979;
	int precise = max(stacks, slices);

	double theta1 = 0.0;
	double theta2 = 0.0;
	double theta3 = 0.0;

	double ex = 0.0f;
	double ey = 0.0f;
	double ez = 0.0f;

	double px = 0.0f;
	double py = 0.0f;
	double pz = 0.0f;

	glRotated(-90, 1, 0, 0);
	for (int i = 0; i < precise / 2; i++)
	{
		theta1 = i * 2 * Pi / precise - Pi / 2;
		theta2 = (i + 1) * 2 * Pi / precise - Pi / 2;
		glBegin(GL_TRIANGLE_STRIP);
		{
			for (int j = 0; j <= precise; j++)
			{
				theta3 = j * 2 * Pi / precise;

				ex = cos(theta2) * cos(theta3);
				ey = sin(theta2);
				ez = cos(theta2) * sin(theta3);
				px = SphereLocation[0] + SphereRolate * ex;
				py = SphereLocation[1] + SphereRolate * ey;
				pz = SphereLocation[2] + SphereRolate * ez;

				glNormal3d(ex, ey, ez);
				glTexCoord2d(-(j / (double)precise), 2 * (i + 1) / (double)precise);
				glVertex3d(px, py, pz);

				ex = cos(theta1) * cos(theta3);
				ey = sin(theta1);
				ez = cos(theta1) * sin(theta3);
				px = SphereLocation[0] + SphereRolate * ex;
				py = SphereLocation[1] + SphereRolate * ey;
				pz = SphereLocation[2] + SphereRolate * ez;

				glNormal3d(ex, ey, ez);
				glTexCoord2d(-(j / (double)precise), 2 * i / (double)precise);
				glVertex3d(px, py, pz);
			}
		}
		glEnd();
	}
	glRotated(90, 1, 0, 0);
}
void Sphere::SphereLookAt(const double *lookAt)
{
	gluLookAt(lookAt[0], lookAt[1], lookAt[2], lookAt[3], lookAt[4], lookAt[5], lookAt[6], lookAt[7], lookAt[8]);
}
void Sphere::SphereTranslate(const double *vector)
{
	glTranslated(vector[0], vector[1], vector[2]);
}
void Sphere::SphereRotate(double *rotate)
{
	glRotated(rotate[0], rotate[1], rotate[2], rotate[3]);
}
void Sphere::SphereRotate(double angle, double x, double y, double z)
{
	glRotated(angle, x, y, z);
}
void Sphere::SphereChangeColor(const double *color)
{
	for (int i = 0; i < 3; i++)
		SphereColor[i] = color[i];
}
void Sphere::SphereChangeLineWidth(float width)
{
	SphereLineWidth = width;
}
void Sphere::draw(Spheretype type)
{
	glColor3dv(SphereColor);
	glLineWidth(SphereLineWidth);	
	glMaterialfv(GL_FRONT, GL_AMBIENT, SphereAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, SphereDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, SphereSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, SphereLowShine);
	switch (type)
	{
	case Solid:	glutSolidSphere(SphereRolate, slices, stacks);
		break;
	case Wire:	glutWireSphere(SphereRolate, slices, stacks);
		break;
	case SolidWithTexture:drawSphere();
	}
}
void Sphere::SphereMaterialAmbient(const float *ambient)
{
	for (int i = 0; i < 4; i++)
	{
		SphereAmbient[i] = ambient[i];
	}
}
void Sphere::SphereMaterialDiffuse(const float *diffuse)
{
	for (int i = 0; i < 4; i++)
	{
		SphereDiffuse[i] = diffuse[i];
	}
}
void Sphere::SphereMaterialSpecular(const float *specular)
{
	for (int i = 0; i < 4; i++)
	{
		SphereSpecular[i] = specular[i];
	}
}
void Sphere::SphereMaterialShine(const float lowShine)
{
	SphereLowShine[0] = lowShine;
}
void Sphere::SphereMatrixRecovery()
{
	glPopMatrix();
}

LightingManager::LightingManager(LightNumber number)
{
	glEnable(GL_LIGHTING);
	lightNumber = number;
	for (int i = 0; i < 4; i++)
	{
		lightPosition[i] = 0;
		lightAmbient[i] = 0;
		lightDiffuse[i] = 1;
		lightSpecular[i] = 0;
	}
}
void LightingManager::SetLightAmbient(const float *ambient)
{
	for (int i = 0; i < 4; i++)
		lightAmbient[i] = ambient[i];
}
void LightingManager::SetLightModelAmbient(const float *ambient)
{
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
}
void LightingManager::SetLightDiffuse(const float *diffuse)
{
	for (int i = 0; i < 4; i++)
		lightDiffuse[i] = diffuse[i];
}
void LightingManager::SetLightSpecular(const float *speculat)
{
	for (int i = 0; i < 4; i++)
		lightSpecular[i] = speculat[i];
}
void LightingManager::SetLightPosition(const float *position)
{
	for (int i = 0; i < 4; i++)
		lightPosition[i] = position[i];
}
void LightingManager::SetLightPosition(const float x, const float y, const float z, const float value)
{
	lightPosition[0] = x;
	lightPosition[1] = y;
	lightPosition[2] = z;
	lightPosition[3] = value;
}
void LightingManager::FlushLightPosition()
{
	glLightfv(lightNumber, GL_POSITION, lightPosition);
}
void LightingManager::LightBegin()
{
	glLightfv(lightNumber, GL_AMBIENT, lightAmbient);
	glLightfv(lightNumber, GL_DIFFUSE, lightDiffuse);
	glLightfv(lightNumber, GL_SPECULAR, lightSpecular);
	glLightfv(lightNumber, GL_POSITION, lightPosition);
}
void LightingManager::EnableTwoSideLighting()
{
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}
void LightingManager::Disable()
{
	glDisable(lightNumber);
}
void LightingManager::Enable()
{
	glEnable(GL_LIGHTING);
	glEnable(lightNumber);
}
