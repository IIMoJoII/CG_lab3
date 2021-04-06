#pragma once

#include<math.h>

//���������� �������/��������� ���������/ ������/!!!!/ ������� �������

class Vector3f
{
public:
	float x, y, z;

	Vector3f() {};							//����������� �� ���������
	Vector3f(float _x, float _y, float _z)	//�����������
	{
		x = _x;
		y = _y;
		z = _z;
	}

	//��������������� ��������� +
	Vector3f operator + (Vector3f _Vector)
	{
		return Vector3f(_Vector.x + x, _Vector.y + y, _Vector.z + z);
	}
	//��������������� ��������� -
	Vector3f operator - (Vector3f _Vector)
	{
		return Vector3f(x - _Vector.x, y - _Vector.y, z - _Vector.z);
	}

	//��������������� ��������� *
	Vector3f operator * (float num)
	{
		return Vector3f(x * num, y * num, z * num);
	}

	//��������������� ��������� /
	Vector3f operator / (float num)
	{
		return Vector3f(x / num, y / num, z / num);
	}
};

//���������� ������� ���� ��������
Vector3f Cross(Vector3f _Vec1, Vector3f _Vec2);

//���������� ����� �������
float Norm(Vector3f _Vec);

//������������ �������
Vector3f Normalize(Vector3f _Vec);

//���������� ���������� ������������
float scalar(Vector3f _Vec1, Vector3f _Vec2);

//������ ����� ����� �������
Vector3f Vector(Vector3f _Point1, Vector3f _Point2);

//���������� ������� ��������
Vector3f Normal(Vector3f _1, Vector3f _2, Vector3f _3);
