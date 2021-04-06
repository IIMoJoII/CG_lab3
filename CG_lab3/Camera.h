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
	Vector3f Position;	//������� ������/��������� ����� �����������/
	Vector3f View;		//����������� ����������
	Vector3f UpVector;	//������ �������� �����

	Camera();	//�����������
	void PositionCamera(float posX, float posY, float posZ,
		float viewX, float viewY, float viewZ,
		float upX, float upY, float upZ);	//��������� ������� ������

	void SetViewByMouse(GLint width, GLint height);			//��������� ���� � ������� ����
	void MoveCamera(float speed);							//������������ ������ ������/�����
	void RotateView(float angle, float x, float y, float z);	//�������� ������ ������ �������� ���
	void RotateAroundPoint(Vector3f vCenter, float angle, float x, float y, float z);//�������� ������ ������ �����������
};
