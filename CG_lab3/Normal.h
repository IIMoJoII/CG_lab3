#pragma once

#include<math.h>

//ВЫЧИСЛЕНИЕ НОРМАЛИ/ОТРИСОВКА ПОЛИГОНОВ/ ПРОТИВ/!!!!/ ЧАСОВОЙ СТРЕЛКИ

class Vector3f
{
public:
	float x, y, z;

	Vector3f() {};							//конструктор по умолчанию
	Vector3f(float _x, float _y, float _z)	//конструктор
	{
		x = _x;
		y = _y;
		z = _z;
	}

	//Переопределение оператора +
	Vector3f operator + (Vector3f _Vector)
	{
		return Vector3f(_Vector.x + x, _Vector.y + y, _Vector.z + z);
	}
	//Переопределение оператора -
	Vector3f operator - (Vector3f _Vector)
	{
		return Vector3f(x - _Vector.x, y - _Vector.y, z - _Vector.z);
	}

	//Переопределение оператора *
	Vector3f operator * (float num)
	{
		return Vector3f(x * num, y * num, z * num);
	}

	//Переопределение оператора /
	Vector3f operator / (float num)
	{
		return Vector3f(x / num, y / num, z / num);
	}
};

//Вычисление нормали двух векторов
Vector3f Cross(Vector3f _Vec1, Vector3f _Vec2);

//Вычисление нормы вектора
float Norm(Vector3f _Vec);

//Нормализация вектора
Vector3f Normalize(Vector3f _Vec);

//Вычисление скалярного произведения
float scalar(Vector3f _Vec1, Vector3f _Vec2);

//Вектор между двумя точками
Vector3f Vector(Vector3f _Point1, Vector3f _Point2);

//Вычисление нормали полигона
Vector3f Normal(Vector3f _1, Vector3f _2, Vector3f _3);
