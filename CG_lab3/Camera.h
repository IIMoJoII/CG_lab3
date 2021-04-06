#pragma once

#include <math.h>
#include <windows.h>
#include "GL/glut.h"
#include <vector>
#include <gl\gl.h>
#include "Normal.h"


class Camera
{
public:
	Vector3f Position;	//позиция камеры/положение точки наблюдателя/
	Vector3f View;		//направление наблюдения
	Vector3f UpVector;	//вектор поворота сцены

	Camera();	//конструктор
	void PositionCamera(float posX, float posY, float posZ,
		float viewX, float viewY, float viewZ,
		float upX, float upY, float upZ);	//установка позиции камеры

	void SetViewByMouse(GLint width, GLint height);			//установка вида с помощью мыши
	void MoveCamera(float speed);							//передвижение камеры вперед/назад
	void RotateView(float angle, float x, float y, float z);	//вращение камеры вокруг заданной оси
	void RotateAroundPoint(Vector3f vCenter, float angle, float x, float y, float z);//вращение камеры вокруг наблюдателя
};
