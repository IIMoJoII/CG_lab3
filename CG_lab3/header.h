#pragma once

#define _USE_MATH_DEFINES 
#include <math.h>
#include <windows.h>
#include "GL/glut.h"
#include "gl/glaux.h"
#include <vector>
#include <gl\gl.h>
#include <stdio.h>
#include "Camera.h"

#pragma comment(lib,"GLAUX.LIB")

#define kSpeed  0.03f	//скорость перемещения камеры

using namespace std;

float angle = 60;		//угол в перспективной проекции
float mas = 10;			//множитель в ортографической проекции
GLint width, height;	//ширина и высота окна
Camera camera1;			//камера
bool rot = false;			//включить вращение камеры с помощью мыши
bool perspective = true;	//включить перспективную проекцию
bool wireframeModel = false;//каркасный режим
bool showNormal = false;	//отображение нормалей
bool smoothNorm = false;	//сгладить нормали
bool showGrid = true;		//отображение сетки
bool g_bLight = true;		//включить освещение
bool textureMod = false;	//отображение текстуры
int light_sample = 1;		//текущий источник света

float TMatrix[4][4];	//матрица сдвига
float RMatrix[4][4];	//матрица поворота
float SMatrix[4][4];	//матрица масштаба

unsigned int names_tex[10];	//имена текстур

//структура для хранения треугольника
struct triangle
{
	Vector3f _1;
	Vector3f _2;
	Vector3f _3;
};

vector <float> percent;				//вектор процентных положений сечений тиражирования
vector <Vector3f> normals;			//вектор нормалей/содержит нормаль каждого полигона/
vector <Vector3f> smoothedNormals;	//вектор сглаженных нормалей/содержит нормаль к каждой вершине
vector <Vector3f> path;		//траектория тиражирования
vector <Vector3f> scales;	//масштабирование каждого сечения
vector <triangle> figure1;	//набор сечений треугольника
triangle templateTriangle;	//шаблон треугольника

//умножение координаты на указанную матрицу
Vector3f multCoord(float _matrix[4][4], Vector3f _vec)
{
	float vec[4] = { _vec.x, _vec.y, _vec.z, 1.0f };
	float resVec[4];

	for (int i = 0; i < 4; i++)
	{
		double s = 0;
		for (int j = 0; j < 4; j++)
			s += _matrix[i][j] * vec[j];
		resVec[i] = s;
	}
	return Vector3f::Vector3f(resVec[0], resVec[1], resVec[2]);
}

//определить матрицу сдвига
void makeTranslateMatrix(float dx, float dy, float dz)
{
	TMatrix[0][0] = 1; TMatrix[0][1] = 0;
	TMatrix[0][2] = 0; TMatrix[0][3] = dx;
	TMatrix[1][0] = 0; TMatrix[1][1] = 1;
	TMatrix[1][2] = 0; TMatrix[1][3] = dy;
	TMatrix[2][0] = 0; TMatrix[2][1] = 0;
	TMatrix[2][2] = 1; TMatrix[2][3] = dz;
	TMatrix[3][0] = 0; TMatrix[3][1] = 0;
	TMatrix[3][2] = 0; TMatrix[3][3] = 1;
}

//определить матрицу поворота/относительно произвольной оси/
void makeRotateMatrix(float angle, Vector3f Axis)
{
	float c = (float)cos(angle * M_PI / 180.0);
	float s = (float)sin(angle * M_PI / 180.0);
	Vector3f Os = Normalize(Axis);

	RMatrix[0][0] = c + (1 - c) * Os.x * Os.x;
	RMatrix[0][1] = (1 - c) * Os.x * Os.y - s * Os.z;
	RMatrix[0][2] = (1 - c) * Os.x * Os.z + s * Os.y;
	RMatrix[0][3] = 0;
	RMatrix[1][0] = (1 - c) * Os.x * Os.y + s * Os.z;
	RMatrix[1][1] = c + (1 - c) * Os.y * Os.y;
	RMatrix[1][2] = (1 - c) * Os.z * Os.y - s * Os.x;
	RMatrix[1][3] = 0;
	RMatrix[2][0] = (1 - c) * Os.x * Os.z - s * Os.y;
	RMatrix[2][1] = (1 - c) * Os.z * Os.y + s * Os.x;
	RMatrix[2][2] = c + (1 - c) * Os.z * Os.z;
	RMatrix[2][3] = 0;
	RMatrix[3][0] = 0;
	RMatrix[3][1] = 0;
	RMatrix[3][2] = 0;
	RMatrix[3][3] = 1;
}

//определить матрицу масштаба
void makeScaleMatrix(float sx, float sy, float sz)
{
	SMatrix[0][0] = sx; SMatrix[0][1] = 0;
	SMatrix[0][2] = 0; SMatrix[0][3] = 0;
	SMatrix[1][0] = 0; SMatrix[1][1] = sy;
	SMatrix[1][2] = 0; SMatrix[1][3] = 0;
	SMatrix[2][0] = 0; SMatrix[2][1] = 0;
	SMatrix[2][2] = sz; SMatrix[2][3] = 0;
	SMatrix[3][0] = 0; SMatrix[3][1] = 0;
	SMatrix[3][2] = 0; SMatrix[3][3] = 1;
}

//трансформация нового треугольника
triangle transform(int num, float angle, Vector3f Axis, Vector3f shift)
{
	triangle _triangle;
	_triangle._1 = templateTriangle._1;
	_triangle._2 = templateTriangle._2;
	_triangle._3 = templateTriangle._3;

	//если угол не равен нулю - повернуть треугольник
	if (angle != 0)
	{
		makeRotateMatrix(angle, Axis);
		_triangle._1 = multCoord(RMatrix, _triangle._1);
		_triangle._2 = multCoord(RMatrix, _triangle._2);
		_triangle._3 = multCoord(RMatrix, _triangle._3);
	}

	//масштабируем треугольник
	makeScaleMatrix(scales[num].x, scales[num].y, scales[num].z);
	_triangle._1 = multCoord(SMatrix, _triangle._1);
	_triangle._2 = multCoord(SMatrix, _triangle._2);
	_triangle._3 = multCoord(SMatrix, _triangle._3);

	//сдвинуть треугольник
	makeTranslateMatrix(shift.x, shift.y, shift.z);
	_triangle._1 = multCoord(TMatrix, _triangle._1);
	_triangle._2 = multCoord(TMatrix, _triangle._2);
	_triangle._3 = multCoord(TMatrix, _triangle._3);

	return _triangle;
}

//тиражировать фигуру
void makeDuplication()
{
	FILE* in1;
	FILE* in2;
	FILE* in3;

	in1 = fopen("triangle.txt", "r");
	in2 = fopen("trajectory.txt", "r");
	in3 = fopen("percent.txt", "r");

	//считать координаты шаблонного треугольника
	fscanf(in1, "%f%f%f", &templateTriangle._1.x, &templateTriangle._1.y, &templateTriangle._1.z);
	fscanf(in1, "%f%f%f", &templateTriangle._2.x, &templateTriangle._2.y, &templateTriangle._2.z);
	fscanf(in1, "%f%f%f", &templateTriangle._3.x, &templateTriangle._3.y, &templateTriangle._3.z);

	Vector3f coord;
	Vector3f scale;
	float ang;

	//считать координаты траектории
	while (!feof(in2))
	{
		fscanf(in2, "%f%f%f", &coord.x, &coord.y, &coord.z);
		path.push_back(coord);
	}

	float per;
	while (!feof(in3))
	{
		fscanf(in3, "%f", &per);
		fscanf(in3, "%f%f%f", &scale.x, &scale.y, &scale.z);
		percent.push_back(per);
		scales.push_back(scale);
	}
	fclose(in1);
	fclose(in2);
	fclose(in3);

	Vector3f Axis;	//ось поворота
	//предыдущее направление - нормаль шаблонного треугольника
	Vector3f predPath = Normal(templateTriangle._1, templateTriangle._2, templateTriangle._3);
	Vector3f curPath;	//текущее направление
	triangle _triangle;

	int i;
	float pathLength = 0;	//длина пути

	//вычисление длины пути
	for (i = 0; i < path.size() - 1; i++)
	{
		curPath = path[i + 1] - path[i];
		pathLength += Norm(curPath);
	}

	for (i = 0; i < percent.size(); i++)
	{
		//расстояние до точки тиражирования
		float pointDistance = (pathLength * percent[i]) / 100.;

		//поиск отрезка траектории, которому принадлежит точка тиражирования
		int j;
		Vector3f curPathLength;	//текущее направление вектора траектории
		float curLength = 0;	//текущая длина пути
		float predLength = 0;	//предыдущая длина пути
		bool found = false;		//найден отрезок траектории

		int numPath;	//индекс начала отрезка траектории

		//если это последнее сечение
		if (i == percent.size() - 1)
			numPath = path.size() - 2;
		else
		{
			for (j = 0; j < path.size() - 1, !found; j++)
			{
				curPathLength = path[j + 1] - path[j];
				curLength += Norm(curPathLength);

				//если точка тиражирования пренадлежит текущему отрезку
				if (pointDistance >= predLength && pointDistance <= curLength)
					found = true;
				else
					predLength = curLength;
			}

			numPath = j - 1;
		}
		//вычислить текущее направление
		curPath = path[numPath + 1] - path[numPath];

		//величина сдвига от начала отрезка, которому принадлежит точка тиражирования
		float localPath = pointDistance - predLength;
		if (i == percent.size() - 1)
			localPath = Norm(curPath);
		float normCurPath = Norm(curPath);

		//вычисление координат сдвига
		Vector3f shift = Vector3f(path[numPath].x + (localPath * curPath.x) / normCurPath,
			path[numPath].y + (localPath * curPath.y) / normCurPath,
			path[numPath].z + (localPath * curPath.z) / normCurPath);

		//вычислить скалярное произведение
		float scal = scalar(curPath, predPath);

		//вычислить ось
		Axis = Cross(curPath, predPath);

		//вычислить угол поворота
		ang = acos(scal / (Norm(curPath) * Norm(predPath))) * 180.0 / M_PI;

		//в зависимости от знака скалярного произведения изменить угол
		if (scal < 0)
			ang = 180 - ang;
		else
			ang = -(180 + ang);
		if (ang == 180) ang = 0;

		//определить координаты нового треугольника
		_triangle = transform(i, ang, Axis, shift);

		//добавить треугольник в вектор
		figure1.push_back(_triangle);
	}
}

//вычисление нормалей к плоскостям
void calcNormals()
{
	Vector3f normal;
	//отдельно вычисляются нормали к первому треугольнику
	normal = Normal(figure1[0]._1, figure1[0]._2, figure1[0]._3);
	normals.push_back(normal);

	for (int i = 0; i < figure1.size() - 1; i++)
	{
		normal = Normal(figure1[i]._2, figure1[i]._1, figure1[i + 1]._1);
		normals.push_back(normal);

		normal = Normal(figure1[i]._1, figure1[i]._3, figure1[i + 1]._3);
		normals.push_back(normal);

		normal = Normal(figure1[i]._3, figure1[i]._2, figure1[i + 1]._2);
		normals.push_back(normal);
	}

	//и к последнему
	int j = figure1.size() - 1;
	normal = Normal(figure1[j]._1, figure1[j]._3, figure1[j]._2);
	normals.push_back(normal);
}

//вычисление сглаженных нормалей
void smoothNormals()
{
	Vector3f _smoothNormal;

	_smoothNormal = (normals[0] + normals[1] + normals[2]) / 3.0;
	smoothedNormals.push_back(_smoothNormal);

	_smoothNormal = (normals[0] + normals[1] + normals[3]) / 3.0;
	smoothedNormals.push_back(_smoothNormal);

	_smoothNormal = (normals[0] + normals[2] + normals[3]) / 3.0;
	smoothedNormals.push_back(_smoothNormal);

	int nN = 1;
	for (int i = 1; i < figure1.size() - 1; i++)
	{
		_smoothNormal = (normals[nN] + normals[nN + 1] + normals[nN + 3] + normals[nN + 4]) / 4.0;
		smoothedNormals.push_back(_smoothNormal);

		_smoothNormal = (normals[nN] + normals[nN + 2] + normals[nN + 3] + normals[nN + 5]) / 4.0;
		smoothedNormals.push_back(_smoothNormal);

		_smoothNormal = (normals[nN + 1] + normals[nN + 2] + normals[nN + 4] + normals[nN + 5]) / 4.0;
		smoothedNormals.push_back(_smoothNormal);
		nN += 3;
	}
	int j = normals.size() - 1;
	_smoothNormal = (normals[j] + normals[j - 2] + normals[j - 3]) / 3.0;
	smoothedNormals.push_back(_smoothNormal);

	_smoothNormal = (normals[j] + normals[j - 1] + normals[j - 3]) / 3.0;
	smoothedNormals.push_back(_smoothNormal);

	_smoothNormal = (normals[j] + normals[j - 1] + normals[j - 2]) / 3.0;
	smoothedNormals.push_back(_smoothNormal);
}

void loadTexture()//загрузка текстуры
{


}




