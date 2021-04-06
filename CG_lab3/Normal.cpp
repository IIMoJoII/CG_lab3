#include "Normal.h"

//¬ычисление нормали двух векторов
Vector3f Cross(Vector3f _Vec1, Vector3f _Vec2)
{
	Vector3f _Normal;

	//вычисление векторного произведени€
	_Normal.x = ((_Vec1.y * _Vec2.z) - (_Vec1.z * _Vec2.y));
	_Normal.y = ((_Vec1.z * _Vec2.x) - (_Vec1.x * _Vec2.z));
	_Normal.z = ((_Vec1.x * _Vec2.y) - (_Vec1.y * _Vec2.x));

	return _Normal;
}

//¬ычисление нормы вектора
float Norm(Vector3f _Vec)
{
	return (float)sqrt((_Vec.x * _Vec.x) + (_Vec.y * _Vec.y) + (_Vec.z * _Vec.z));
}

//Ќормализаци€ вектора
Vector3f Normalize(Vector3f _Vec)
{
	//¬ычислить норму вектора
	float norm = Norm(_Vec);

	//нормализовать вектор
	_Vec = _Vec / norm;

	return _Vec;
}

//¬ычисление скал€рного произведени€
float scalar(Vector3f _Vec1, Vector3f _Vec2)
{
	return _Vec1.x * _Vec2.x + _Vec1.y * _Vec2.y + _Vec1.z * _Vec2.z;
}

//¬ектор между двум€ точками
Vector3f Vector(Vector3f _Point1, Vector3f _Point2)
{
	Vector3f _Vector;

	_Vector.x = _Point1.x - _Point2.x;
	_Vector.y = _Point1.y - _Point2.y;
	_Vector.z = _Point1.z - _Point2.z;
	return _Vector;
}

//¬ычисление нормали полигона
Vector3f Normal(Vector3f _1, Vector3f _2, Vector3f _3)
{
	Vector3f _Vector1 = Vector(_3, _2);
	Vector3f _Vector2 = Vector(_2, _1);
	Vector3f _Normal = Cross(_Vector1, _Vector2);
	_Normal = Normalize(_Normal);
	return _Normal;
}