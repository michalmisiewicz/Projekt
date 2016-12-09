#include "myglwidget.h"
#include <QtOpenGL>

MyGLWidget::MyGLWidget(QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
}

MyGLWidget::~MyGLWidget()
{
}

void MyGLWidget::initializeGL()
{
	glViewport(0, 0, 768, 768);
	glEnable(GL_TEXTURE_2D);
}

void MyGLWidget::paintGL()
{
	loadTexture();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, texture);
	
	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(-1.0f, -1.0f, 0.0f);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(1.0f, -1.0f, 0.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(1.0f, 1.0f, 0.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-1.0f, 1.0f, 0.0f);  // Top Left Of The Texture and Quad
															  // Back Face
	glEnd();


}

void MyGLWidget::resizeGL(int w, int h)
{
}

int MyGLWidget::loadTexture()
{
	int size = width * 3 * height;
	unsigned char* pixels = new unsigned char[size];
	memset(pixels, 0, size);

	drawCurve(pixels, a, b);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtering

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
	
	return 1;
}

void MyGLWidget::blueButton()
{
	color = 0;
	repaint();
}

void MyGLWidget::greenButton()
{
	color = 1;
	repaint();
}

void MyGLWidget::redButton()
{
	color = 2;
	repaint();
}

void MyGLWidget::setA(int value)
{
	this->a = ((double)value) / 10;
	repaint();
}

void MyGLWidget::drawCurve(unsigned char* tab, double a, double b)
{
	
	for (double i = 0; i < 10; i += 0.0001)
	{
		int x = (sin(a * i) + 1) * 374 + 5;
		int y = (sin(b * i + M_PI / 2) + 1) * 374 + 5;
		*(tab +  y * 3 * this->width + 3 * x + color) = 255;
	}
}