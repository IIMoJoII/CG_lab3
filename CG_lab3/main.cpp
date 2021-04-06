#include "header.h"

void Reshape(GLint w, GLint h)
{
	//изменить размеры окна
	width = w;
	height = h;

	//вычислить соотношение между шириной и высотой
	//предотвратить деление на 0
	if (height == 0)
		height = 1;
	float ratio = 1. * width / height;

	//установить матрицу проекции/определяет объем сцены
	glMatrixMode(GL_PROJECTION);

	//загрузить единичную матрицу
	glLoadIdentity();

	//определить окно просмотра
	glViewport(0, 0, width, height);

	//если стоит режим перспективы
	if (perspective)
		gluPerspective(60, ratio, 0.1f, 100.0f);	//использовать перспективную проекциию

	//иначе - ортографическую проекцию
	else
		if (width >= height)
			glOrtho(-mas * ratio, mas * ratio, -mas, mas, -100.0f, 100.0f);
		else
			glOrtho(-mas, mas, -mas / ratio, mas / ratio, -100.0f, 100.0f);

	//возврат к матрице модели
	glMatrixMode(GL_MODELVIEW);
}

void Draw3DSGrid()
{
	glColor3ub(0, 255, 0);
	for (float i = -50; i <= 50; i += 1)
	{
		glBegin(GL_LINES);
		// Ось Х
		glVertex3f(-50, 0, i);
		glVertex3f(50, 0, i);

		// Ось Z
		glVertex3f(i, 0, -50);
		glVertex3f(i, 0, 50);
		glEnd();
	}
}

//отрисовка тиражированной фигуры
void test()
{
	Vector3f normal;
	int nN = 0;

	//НЕ КАРКАСНЫЙ РЕЖИМ
	if (!wireframeModel)
	{
		//НОРМАЛИ НЕ СГЛАЖЕНЫ
		if (!smoothNorm)
		{
			//ТЕКСТУРИРОВАНИЕ ОТКЛЮЧЕНО
			if (!textureMod)
			{
				//устанавливается нормаль для каждой плоскости
				glBegin(GL_TRIANGLES);
				glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
				glColor3ub(0, 255, 0);
				glVertex3f(figure1[0]._1.x, figure1[0]._1.y, figure1[0]._1.z);
				glVertex3f(figure1[0]._2.x, figure1[0]._2.y, figure1[0]._2.z);
				glVertex3f(figure1[0]._3.x, figure1[0]._3.y, figure1[0]._3.z);
				glEnd();

				for (int i = 0; i < figure1.size() - 1; i++)
				{
					glBegin(GL_POLYGON);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;

					glColor3ub(0, 255, 0);
					glVertex3f(figure1[i]._1.x, figure1[i]._1.y, figure1[i]._1.z);
					glVertex3f(figure1[i + 1]._1.x, figure1[i + 1]._1.y, figure1[i + 1]._1.z);
					glVertex3f(figure1[i + 1]._2.x, figure1[i + 1]._2.y, figure1[i + 1]._2.z);
					glVertex3f(figure1[i]._2.x, figure1[i]._2.y, figure1[i]._2.z);
					glEnd();

					glBegin(GL_POLYGON);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;

					glColor3ub(0, 255, 0);
					glVertex3f(figure1[i]._3.x, figure1[i]._3.y, figure1[i]._3.z);
					glVertex3f(figure1[i + 1]._3.x, figure1[i + 1]._3.y, figure1[i + 1]._3.z);
					glVertex3f(figure1[i + 1]._1.x, figure1[i + 1]._1.y, figure1[i + 1]._1.z);
					glVertex3f(figure1[i]._1.x, figure1[i]._1.y, figure1[i]._1.z);
					glEnd();

					glBegin(GL_POLYGON);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;

					glColor3ub(0, 255, 0);
					glVertex3f(figure1[i]._2.x, figure1[i]._2.y, figure1[i]._2.z);
					glVertex3f(figure1[i + 1]._2.x, figure1[i + 1]._2.y, figure1[i + 1]._2.z);
					glVertex3f(figure1[i + 1]._3.x, figure1[i + 1]._3.y, figure1[i + 1]._3.z);
					glVertex3f(figure1[i]._3.x, figure1[i]._3.y, figure1[i]._3.z);
					glEnd();
				}

				int j = figure1.size() - 1;
				glBegin(GL_TRIANGLES);
				glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;

				glColor3ub(0, 255, 0);
				glVertex3f(figure1[j]._1.x, figure1[j]._1.y, figure1[j]._1.z);
				glVertex3f(figure1[j]._2.x, figure1[j]._2.y, figure1[j]._2.z);
				glVertex3f(figure1[j]._3.x, figure1[j]._3.y, figure1[j]._3.z);
				glEnd();
			}

			//ТЕКСТУРИРОВАНИЕ ВКЛЮЧЕНО
			else
			{
				glEnable(GL_TEXTURE_2D);	//разрешить текстурирование
				glBindTexture(GL_TEXTURE_2D, names_tex[0]);	//выбрать текстуру
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	//умножение

				//устанавливается нормаль для каждой плоскости
				//и тестурные координаты
				glBegin(GL_TRIANGLES);
				glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
				glColor3ub(0, 255, 0);
				glTexCoord2f(0, 0); glVertex3f(figure1[0]._1.x, figure1[0]._1.y, figure1[0]._1.z);
				glTexCoord2f(0.5, 1); glVertex3f(figure1[0]._2.x, figure1[0]._2.y, figure1[0]._2.z);
				glTexCoord2f(1, 0); glVertex3f(figure1[0]._3.x, figure1[0]._3.y, figure1[0]._3.z);
				glEnd();

				for (int i = 0; i < figure1.size() - 1; i++)
				{
					glBegin(GL_POLYGON);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;

					glColor3ub(0, 255, 0);
					glTexCoord2f(0, 1); glVertex3f(figure1[i]._1.x, figure1[i]._1.y, figure1[i]._1.z);
					glTexCoord2f(1, 1); glVertex3f(figure1[i + 1]._1.x, figure1[i + 1]._1.y, figure1[i + 1]._1.z);
					glTexCoord2f(1, 0); glVertex3f(figure1[i + 1]._2.x, figure1[i + 1]._2.y, figure1[i + 1]._2.z);
					glTexCoord2f(0, 0); glVertex3f(figure1[i]._2.x, figure1[i]._2.y, figure1[i]._2.z);
					glEnd();

					glBegin(GL_POLYGON);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;

					glColor3ub(0, 255, 0);
					glTexCoord2f(0, 1); glVertex3f(figure1[i]._3.x, figure1[i]._3.y, figure1[i]._3.z);
					glTexCoord2f(1, 1); glVertex3f(figure1[i + 1]._3.x, figure1[i + 1]._3.y, figure1[i + 1]._3.z);
					glTexCoord2f(1, 0); glVertex3f(figure1[i + 1]._1.x, figure1[i + 1]._1.y, figure1[i + 1]._1.z);
					glTexCoord2f(0, 0); glVertex3f(figure1[i]._1.x, figure1[i]._1.y, figure1[i]._1.z);
					glEnd();

					glBegin(GL_POLYGON);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;

					glColor3ub(0, 255, 0);
					glTexCoord2f(0, 1); glVertex3f(figure1[i]._2.x, figure1[i]._2.y, figure1[i]._2.z);
					glTexCoord2f(1, 1); glVertex3f(figure1[i + 1]._2.x, figure1[i + 1]._2.y, figure1[i + 1]._2.z);
					glTexCoord2f(1, 0); glVertex3f(figure1[i + 1]._3.x, figure1[i + 1]._3.y, figure1[i + 1]._3.z);
					glTexCoord2f(0, 0); glVertex3f(figure1[i]._3.x, figure1[i]._3.y, figure1[i]._3.z);
					glEnd();
				}

				int j = figure1.size() - 1;
				glBegin(GL_TRIANGLES);
				glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;

				glColor3ub(0, 255, 0);
				glTexCoord2f(0, 0); glVertex3f(figure1[j]._1.x, figure1[j]._1.y, figure1[j]._1.z);
				glTexCoord2f(0.5, 1); glVertex3f(figure1[j]._2.x, figure1[j]._2.y, figure1[j]._2.z);
				glTexCoord2f(1, 0); glVertex3f(figure1[j]._3.x, figure1[j]._3.y, figure1[j]._3.z);
				glEnd();

				//отключить текстурирование
				glDisable(GL_TEXTURE_2D);
			}
		}

		//НОРМАЛИ СГЛАЖЕНЫ
		else
		{
			//ТЕКСТУРИРОВАНИЕ ОТКЛЮЧЕНО
			if (!textureMod)
			{
				//устанавливается нормаль для каждой вершины
				glBegin(GL_TRIANGLES);
				glColor3ub(0, 255, 0);

				glNormal3f(smoothedNormals[0].x, smoothedNormals[0].y, smoothedNormals[0].z);
				glVertex3f(figure1[0]._1.x, figure1[0]._1.y, figure1[0]._1.z);

				glNormal3f(smoothedNormals[1].x, smoothedNormals[1].y, smoothedNormals[1].z);
				glVertex3f(figure1[0]._2.x, figure1[0]._2.y, figure1[0]._2.z);

				glNormal3f(smoothedNormals[2].x, smoothedNormals[2].y, smoothedNormals[2].z);
				glVertex3f(figure1[0]._3.x, figure1[0]._3.y, figure1[0]._3.z);
				glEnd();

				nN = 0;
				for (int i = 0; i < figure1.size() - 1; i++)
				{
					glBegin(GL_POLYGON);
					glColor3ub(0, 255, 0);

					glNormal3f(smoothedNormals[nN].x, smoothedNormals[nN].y, smoothedNormals[nN].z);
					glVertex3f(figure1[i]._1.x, figure1[i]._1.y, figure1[i]._1.z);

					glNormal3f(smoothedNormals[nN + 3].x, smoothedNormals[nN + 3].y, smoothedNormals[nN + 3].z);
					glVertex3f(figure1[i + 1]._1.x, figure1[i + 1]._1.y, figure1[i + 1]._1.z);

					glNormal3f(smoothedNormals[nN + 4].x, smoothedNormals[nN + 4].y, smoothedNormals[nN + 4].z);
					glVertex3f(figure1[i + 1]._2.x, figure1[i + 1]._2.y, figure1[i + 1]._2.z);

					glNormal3f(smoothedNormals[nN + 1].x, smoothedNormals[nN + 1].y, smoothedNormals[nN + 1].z);
					glVertex3f(figure1[i]._2.x, figure1[i]._2.y, figure1[i]._2.z);
					glEnd();

					glBegin(GL_POLYGON);
					glColor3ub(0, 255, 0);

					glNormal3f(smoothedNormals[nN + 2].x, smoothedNormals[nN + 2].y, smoothedNormals[nN + 2].z);
					glVertex3f(figure1[i]._3.x, figure1[i]._3.y, figure1[i]._3.z);

					glNormal3f(smoothedNormals[nN + 5].x, smoothedNormals[nN + 5].y, smoothedNormals[nN + 5].z);
					glVertex3f(figure1[i + 1]._3.x, figure1[i + 1]._3.y, figure1[i + 1]._3.z);

					glNormal3f(smoothedNormals[nN + 3].x, smoothedNormals[nN + 3].y, smoothedNormals[nN + 3].z);
					glVertex3f(figure1[i + 1]._1.x, figure1[i + 1]._1.y, figure1[i + 1]._1.z);

					glNormal3f(smoothedNormals[nN].x, smoothedNormals[nN].y, smoothedNormals[nN].z);
					glVertex3f(figure1[i]._1.x, figure1[i]._1.y, figure1[i]._1.z);
					glEnd();

					glBegin(GL_POLYGON);
					glColor3ub(0, 255, 0);

					glNormal3f(smoothedNormals[nN + 1].x, smoothedNormals[nN + 1].y, smoothedNormals[nN + 1].z);
					glVertex3f(figure1[i]._2.x, figure1[i]._2.y, figure1[i]._2.z);

					glNormal3f(smoothedNormals[nN + 4].x, smoothedNormals[nN + 4].y, smoothedNormals[nN + 4].z);
					glVertex3f(figure1[i + 1]._2.x, figure1[i + 1]._2.y, figure1[i + 1]._2.z);

					glNormal3f(smoothedNormals[nN + 5].x, smoothedNormals[nN + 5].y, smoothedNormals[nN + 5].z);
					glVertex3f(figure1[i + 1]._3.x, figure1[i + 1]._3.y, figure1[i + 1]._3.z);

					glNormal3f(smoothedNormals[nN + 2].x, smoothedNormals[nN + 2].y, smoothedNormals[nN + 2].z);
					glVertex3f(figure1[i]._3.x, figure1[i]._3.y, figure1[i]._3.z);
					glEnd();

					nN += 3;
				}

				int j = figure1.size() - 1;
				glBegin(GL_TRIANGLES);
				glColor3ub(0, 255, 0);
				glNormal3f(smoothedNormals[nN].x, smoothedNormals[nN].y, smoothedNormals[nN].z);
				glVertex3f(figure1[j]._1.x, figure1[j]._1.y, figure1[j]._1.z);

				glNormal3f(smoothedNormals[nN + 1].x, smoothedNormals[nN + 1].y, smoothedNormals[nN + 1].z);
				glVertex3f(figure1[j]._2.x, figure1[j]._2.y, figure1[j]._2.z);

				glNormal3f(smoothedNormals[nN + 2].x, smoothedNormals[nN + 2].y, smoothedNormals[nN + 2].z);
				glVertex3f(figure1[j]._3.x, figure1[j]._3.y, figure1[j]._3.z);
				glEnd();
			}

			//ТЕКСТУРИРОВАНИЕ ВКЛЮЧЕНО
			else
			{
				glEnable(GL_TEXTURE_2D);	//разрешить текстурирование
				glBindTexture(GL_TEXTURE_2D, names_tex[0]);	//выбрать текстуру
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	//умножение

				//устанавливается нормаль для каждой вершины
				//и текстурные коорднаты
				glBegin(GL_TRIANGLES);
				glColor3ub(0, 255, 0);

				glNormal3f(smoothedNormals[0].x, smoothedNormals[0].y, smoothedNormals[0].z);
				glTexCoord2f(0, 0); glVertex3f(figure1[0]._1.x, figure1[0]._1.y, figure1[0]._1.z);

				glNormal3f(smoothedNormals[1].x, smoothedNormals[1].y, smoothedNormals[1].z);
				glTexCoord2f(0.5, 1); glVertex3f(figure1[0]._2.x, figure1[0]._2.y, figure1[0]._2.z);

				glNormal3f(smoothedNormals[2].x, smoothedNormals[2].y, smoothedNormals[2].z);
				glTexCoord2f(1, 0); glVertex3f(figure1[0]._3.x, figure1[0]._3.y, figure1[0]._3.z);
				glEnd();

				nN = 0;
				for (int i = 0; i < figure1.size() - 1; i++)
				{
					glBegin(GL_POLYGON);
					glColor3ub(0, 255, 0);

					glNormal3f(smoothedNormals[nN].x, smoothedNormals[nN].y, smoothedNormals[nN].z);
					glTexCoord2f(0, 1); glVertex3f(figure1[i]._1.x, figure1[i]._1.y, figure1[i]._1.z);

					glNormal3f(smoothedNormals[nN + 3].x, smoothedNormals[nN + 3].y, smoothedNormals[nN + 3].z);
					glTexCoord2f(1, 1); glVertex3f(figure1[i + 1]._1.x, figure1[i + 1]._1.y, figure1[i + 1]._1.z);

					glNormal3f(smoothedNormals[nN + 4].x, smoothedNormals[nN + 4].y, smoothedNormals[nN + 4].z);
					glTexCoord2f(1, 0); glVertex3f(figure1[i + 1]._2.x, figure1[i + 1]._2.y, figure1[i + 1]._2.z);

					glNormal3f(smoothedNormals[nN + 1].x, smoothedNormals[nN + 1].y, smoothedNormals[nN + 1].z);
					glTexCoord2f(0, 0); glVertex3f(figure1[i]._2.x, figure1[i]._2.y, figure1[i]._2.z);
					glEnd();

					glBegin(GL_POLYGON);
					glColor3ub(0, 255, 0);

					glNormal3f(smoothedNormals[nN + 2].x, smoothedNormals[nN + 2].y, smoothedNormals[nN + 2].z);
					glTexCoord2f(0, 1); glVertex3f(figure1[i]._3.x, figure1[i]._3.y, figure1[i]._3.z);

					glNormal3f(smoothedNormals[nN + 5].x, smoothedNormals[nN + 5].y, smoothedNormals[nN + 5].z);
					glTexCoord2f(1, 1); glVertex3f(figure1[i + 1]._3.x, figure1[i + 1]._3.y, figure1[i + 1]._3.z);

					glNormal3f(smoothedNormals[nN + 3].x, smoothedNormals[nN + 3].y, smoothedNormals[nN + 3].z);
					glTexCoord2f(1, 0); glVertex3f(figure1[i + 1]._1.x, figure1[i + 1]._1.y, figure1[i + 1]._1.z);

					glNormal3f(smoothedNormals[nN].x, smoothedNormals[nN].y, smoothedNormals[nN].z);
					glTexCoord2f(0, 0); glVertex3f(figure1[i]._1.x, figure1[i]._1.y, figure1[i]._1.z);
					glEnd();

					glBegin(GL_POLYGON);
					glColor3ub(0, 255, 0);

					glNormal3f(smoothedNormals[nN + 1].x, smoothedNormals[nN + 1].y, smoothedNormals[nN + 1].z);
					glTexCoord2f(0, 1); glVertex3f(figure1[i]._2.x, figure1[i]._2.y, figure1[i]._2.z);

					glNormal3f(smoothedNormals[nN + 4].x, smoothedNormals[nN + 4].y, smoothedNormals[nN + 4].z);
					glTexCoord2f(1, 1); glVertex3f(figure1[i + 1]._2.x, figure1[i + 1]._2.y, figure1[i + 1]._2.z);

					glNormal3f(smoothedNormals[nN + 5].x, smoothedNormals[nN + 5].y, smoothedNormals[nN + 5].z);
					glTexCoord2f(1, 0); glVertex3f(figure1[i + 1]._3.x, figure1[i + 1]._3.y, figure1[i + 1]._3.z);

					glNormal3f(smoothedNormals[nN + 2].x, smoothedNormals[nN + 2].y, smoothedNormals[nN + 2].z);
					glTexCoord2f(0, 0); glVertex3f(figure1[i]._3.x, figure1[i]._3.y, figure1[i]._3.z);
					glEnd();
				}

				int j = figure1.size() - 1;
				glBegin(GL_TRIANGLES);
				glColor3ub(0, 255, 0);

				glNormal3f(smoothedNormals[nN].x, smoothedNormals[nN].y, smoothedNormals[nN].z);
				glTexCoord2f(0, 0); glVertex3f(figure1[j]._1.x, figure1[j]._1.y, figure1[j]._1.z);

				glNormal3f(smoothedNormals[nN + 1].x, smoothedNormals[nN + 1].y, smoothedNormals[nN + 1].z);
				glTexCoord2f(0.5, 1); glVertex3f(figure1[j]._2.x, figure1[j]._2.y, figure1[j]._2.z);

				glNormal3f(smoothedNormals[nN + 2].x, smoothedNormals[nN + 2].y, smoothedNormals[nN + 2].z);
				glTexCoord2f(1, 0); glVertex3f(figure1[j]._3.x, figure1[j]._3.y, figure1[j]._3.z);
				glEnd();

				//отключить текстурирование
				glDisable(GL_TEXTURE_2D);
			}
		}
	}

	//КАРКАСНЫЙ РЕЖИМ
	else
	{
		glBegin(GL_LINE_STRIP);
		glColor3ub(255, 0, 0);
		for (int i = 0; i < figure1.size(); i++)
			glVertex3f(figure1[i]._1.x, figure1[i]._1.y, figure1[i]._1.z);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3ub(255, 0, 0);
		for (int i = 0; i < figure1.size(); i++)
			glVertex3f(figure1[i]._2.x, figure1[i]._2.y, figure1[i]._2.z);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3ub(255, 0, 0);
		for (int i = 0; i < figure1.size(); i++)
			glVertex3f(figure1[i]._3.x, figure1[i]._3.y, figure1[i]._3.z);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3ub(255, 0, 0);
		for (int i = 0; i < path.size(); i++)
			glVertex3f(path[i].x, path[i].y, path[i].z);
		glEnd();

		for (int i = 0; i < figure1.size(); i++)
		{
			glBegin(GL_LINE_LOOP);
			glColor3ub(255, 0, 0);
			glVertex3f(figure1[i]._1.x, figure1[i]._1.y, figure1[i]._1.z);
			glVertex3f(figure1[i]._2.x, figure1[i]._2.y, figure1[i]._2.z);
			glVertex3f(figure1[i]._3.x, figure1[i]._3.y, figure1[i]._3.z);
			glEnd();
		}
	}

	//ПОКАЗ НОРМАЛЕЙ
	if (showNormal)
	{
		//НОРМАЛИ НЕ СГЛАЖЕНЫ
		if (!smoothNorm)
		{
			glBegin(GL_LINE_STRIP);
			glColor3ub(0, 255, 255);
			glVertex3f(figure1[0]._1.x, figure1[0]._1.y, figure1[0]._1.z);
			glVertex3f(figure1[0]._1.x + normals[0].x, figure1[0]._1.y + normals[0].y, figure1[0]._1.z + normals[0].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
			glColor3ub(0, 255, 255);
			glVertex3f(figure1[0]._2.x, figure1[0]._2.y, figure1[0]._2.z);
			glVertex3f(figure1[0]._2.x + normals[0].x, figure1[0]._2.y + normals[0].y, figure1[0]._2.z + normals[0].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
			glColor3ub(0, 255, 255);
			glVertex3f(figure1[0]._3.x, figure1[0]._3.y, figure1[0]._3.z);
			glVertex3f(figure1[0]._3.x + normals[0].x, figure1[0]._3.y + normals[0].y, figure1[0]._3.z + normals[0].z);
			glEnd();

			nN = 1;
			for (int i = 0; i < figure1.size() - 1; i++)
			{
				glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure1[i]._1.x, figure1[i]._1.y, figure1[i]._1.z);
				glVertex3f(figure1[i]._1.x + normals[nN].x, figure1[i]._1.y + normals[nN].y, figure1[i]._1.z + normals[nN].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure1[i + 1]._1.x, figure1[i + 1]._1.y, figure1[i + 1]._1.z);
				glVertex3f(figure1[i + 1]._1.x + normals[nN].x, figure1[i + 1]._1.y + normals[nN].y, figure1[i + 1]._1.z + normals[nN].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure1[i + 1]._2.x, figure1[i + 1]._2.y, figure1[i + 1]._2.z);
				glVertex3f(figure1[i + 1]._2.x + normals[nN].x, figure1[i + 1]._2.y + normals[nN].y, figure1[i + 1]._2.z + normals[nN].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure1[i]._2.x, figure1[i]._2.y, figure1[i]._2.z);
				glVertex3f(figure1[i]._2.x + normals[nN].x, figure1[i]._2.y + normals[nN].y, figure1[i]._2.z + normals[nN].z);
				glEnd();

				nN++;

				glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure1[i]._3.x, figure1[i]._3.y, figure1[i]._3.z);
				glVertex3f(figure1[i]._3.x + normals[nN].x, figure1[i]._3.y + normals[nN].y, figure1[i]._3.z + normals[nN].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure1[i + 1]._3.x, figure1[i + 1]._3.y, figure1[i + 1]._3.z);
				glVertex3f(figure1[i + 1]._3.x + normals[nN].x, figure1[i + 1]._3.y + normals[nN].y, figure1[i + 1]._3.z + normals[nN].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure1[i + 1]._1.x, figure1[i + 1]._1.y, figure1[i + 1]._1.z);
				glVertex3f(figure1[i + 1]._1.x + normals[nN].x, figure1[i + 1]._1.y + normals[nN].y, figure1[i + 1]._1.z + normals[nN].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure1[i]._1.x, figure1[i]._1.y, figure1[i]._1.z);
				glVertex3f(figure1[i]._1.x + normals[nN].x, figure1[i]._1.y + normals[nN].y, figure1[i]._1.z + normals[nN].z);
				glEnd();

				nN++;

				glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure1[i]._2.x, figure1[i]._2.y, figure1[i]._2.z);
				glVertex3f(figure1[i]._2.x + normals[nN].x, figure1[i]._2.y + normals[nN].y, figure1[i]._2.z + normals[nN].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure1[i + 1]._2.x, figure1[i + 1]._2.y, figure1[i + 1]._2.z);
				glVertex3f(figure1[i + 1]._2.x + normals[nN].x, figure1[i + 1]._2.y + normals[nN].y, figure1[i + 1]._2.z + normals[nN].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure1[i + 1]._3.x, figure1[i + 1]._3.y, figure1[i + 1]._3.z);
				glVertex3f(figure1[i + 1]._3.x + normals[nN].x, figure1[i + 1]._3.y + normals[nN].y, figure1[i + 1]._3.z + normals[nN].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure1[i]._3.x, figure1[i]._3.y, figure1[i]._3.z);
				glVertex3f(figure1[i]._3.x + normals[nN].x, figure1[i]._3.y + normals[nN].y, figure1[i]._3.z + normals[nN].z);
				glEnd();

				nN++;
			}

			int j = figure1.size() - 1;
			glBegin(GL_LINE_STRIP);
			glColor3ub(0, 255, 255);
			glVertex3f(figure1[j]._1.x, figure1[j]._1.y, figure1[j]._1.z);
			glVertex3f(figure1[j]._1.x + normals[nN].x, figure1[j]._1.y + normals[nN].y, figure1[j]._1.z + normals[nN].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
			glColor3ub(0, 255, 255);
			glVertex3f(figure1[j]._2.x, figure1[j]._2.y, figure1[j]._2.z);
			glVertex3f(figure1[j]._2.x + normals[nN].x, figure1[j]._2.y + normals[nN].y, figure1[j]._2.z + normals[nN].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
			glColor3ub(0, 255, 255);
			glVertex3f(figure1[j]._3.x, figure1[j]._3.y, figure1[j]._3.z);
			glVertex3f(figure1[j]._3.x + normals[nN].x, figure1[j]._3.y + normals[nN].y, figure1[j]._3.z + normals[nN].z);
			glEnd();

		}

		//НОРМАЛИ СГЛАЖЕНЫ
		else
		{
			nN = 0;
			for (int i = 0; i < figure1.size(); i++)
			{
				glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure1[i]._1.x, figure1[i]._1.y, figure1[i]._1.z);
				glVertex3f(figure1[i]._1.x + smoothedNormals[nN].x, figure1[i]._1.y + smoothedNormals[nN].y, figure1[i]._1.z + smoothedNormals[nN].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure1[i]._2.x, figure1[i]._2.y, figure1[i]._2.z);
				glVertex3f(figure1[i]._2.x + smoothedNormals[nN + 1].x, figure1[i]._2.y + smoothedNormals[nN + 1].y, figure1[i]._2.z + smoothedNormals[nN + 1].z);
				glEnd();

				glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure1[i]._3.x, figure1[i]._3.y, figure1[i]._3.z);
				glVertex3f(figure1[i]._3.x + smoothedNormals[nN + 2].x, figure1[i]._3.y + smoothedNormals[nN + 2].y, figure1[i]._3.z + smoothedNormals[nN + 2].z);
				glEnd();
				nN += 3;
			}
		}
	}
}

//установка освещения
void Shine_a_Light()
{
	GLfloat ambience[4] = { 0.1f, 0.1f, 0.1f, 1.0 };	//Цвет мирового света
	GLfloat material_diffuse[] = { 0.15, 0.15, 0.15, 1 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glEnable(GL_COLOR_MATERIAL);
	if (light_sample == 1)
	{
		//направленный источник света
		//находится в бесконечности и свет от него распространяется в заданном направлении
		GLfloat light0_diffuse[] = { 0.4, 0.7, 0.2 };
		GLfloat light0_direction[] = { -1.0, 4.0, -1.0, 0.0 };
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambience);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
	}
	if (light_sample == 2)
	{
		//точечный источник света
		//убывание интенсивности с расстоянием
		//отключено (по умолчанию)
		GLfloat light1_diffuse[] = { 0.4, 0.7, 0.2 };
		GLfloat light1_position[] = { -5.0, 8.0, -4.0, 1.0 };
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambience);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	}
	if (light_sample == 3)
	{
		//точечный источник света
		//убывание интенсивности с расстоянием
		GLfloat light2_diffuse[] = { 0.4, 0.7, 0.2 };
		GLfloat light2_position[] = { -5.0, 8.0, -4.0, 1.0 };
		glEnable(GL_LIGHT2);
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambience);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
		glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0);
		glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.04);
		glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.04);
	}
	if (light_sample == 4)
	{
		//прожектор
		//убывание интенсивности с расстоянием
		//отключено (по умолчанию)
		GLfloat light3_diffuse[] = { 0.4, 0.7, 0.2 };
		GLfloat light3_position[] = { -5.0, 8.0, -3.0, 1.0 };
		GLfloat light3_spot_direction[] = { 1.0, -1.0, -1.0 };
		glEnable(GL_LIGHT3);
		glLightfv(GL_LIGHT3, GL_AMBIENT, ambience);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
		glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
		glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 50);
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3_spot_direction);
	}
	if (light_sample == 5)
	{
		//прожектор
		//включен рассчет убывания интенсивности для прожектора
		GLfloat light4_diffuse[] = { 0.4, 0.7, 0.2 };
		GLfloat light4_position[] = { -5.0, 8.0, -3.0, 1.0 };
		GLfloat light4_spot_direction[] = { 1.0, -1.0, -1.0 };
		glEnable(GL_LIGHT4);
		glLightfv(GL_LIGHT4, GL_AMBIENT, ambience);
		glLightfv(GL_LIGHT4, GL_DIFFUSE, light4_diffuse);
		glLightfv(GL_LIGHT4, GL_POSITION, light4_position);
		glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 50);
		glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, light4_spot_direction);
		glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 15.0);
	}
}

void Display(void)
{
	//очистка буфера цвета и глубины
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//включить буфер глубины
	glEnable(GL_DEPTH_TEST);

	if (g_bLight)
		glEnable(GL_LIGHTING);	//включить свет
	else
		glDisable(GL_LIGHTING); //выключить свет	

	 //обнуление трансформации
	glLoadIdentity();

	//установить вид камеры
	gluLookAt(camera1.Position.x, camera1.Position.y, camera1.Position.z,
		camera1.View.x, camera1.View.y, camera1.View.z,
		camera1.UpVector.x, camera1.UpVector.y, camera1.UpVector.z);

	//устаносить освещение
	Shine_a_Light();

	//нарисовать сетку
	if (showGrid)
		Draw3DSGrid();

	//нарисовать тиражированную фигуру
	test();

	//переместиться в точку взгляда
	glTranslatef(camera1.View.x, 0, camera1.View.z);

	//отключить все источники
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);

	//сменить буфер
	glutSwapBuffers();
}

void Process_Mouse_Move(int x, int y)
{
	if (rot)
		camera1.SetViewByMouse(width, height);
}
void Process_Normal_Keys(unsigned char key, int x, int y)
{
	//приближение/отдаление в ортографической проекции
	if (key == '+')
	{
		if (mas > 0.1 && !perspective)
		{
			mas -= 0.05;
			Reshape(width, height);
		}
	}

	if (key == '-' && !perspective)
	{
		if (mas < 10)
		{
			mas += 0.05;
			Reshape(width, height);
		}
	}

	//включение/выключение вращения камеры мышью
	if (key == 'q' || key == 'Q')
	{
		rot = !rot;
		ShowCursor(!rot);
	}

	//переключение между режимами перспективной и ортографической проекции
	if (key == 'p' || key == 'P')
	{
		perspective = !perspective;
		Reshape(width, height);
	}

	//включение/выключение каркасного режима
	if (key == 'm' || key == 'M')
	{
		wireframeModel = !wireframeModel;
		if (wireframeModel)
			g_bLight = false;
		else
			g_bLight = true;
	}

	//включение/выключение отображения нормалей
	if (key == 'n' || key == 'N')
	{
		showNormal = !showNormal;
	}

	//включение/выключение сглаженных нормалей
	if (key == 'b' || key == 'B')
	{
		smoothNorm = !smoothNorm;
	}

	//включение/выключение показа сетки
	if (key == 'g' || key == 'G')
	{
		showGrid = !showGrid;
	}

	//включение/выключение света
	if (key == 'l' || key == 'L')
	{
		g_bLight = !g_bLight;
	}

	//включение/выключение текстуры
	if (key == 't' || key == 'T')
	{
		textureMod = !textureMod;
	}

	//движение камеры
	if (key == 'w' || key == 'W')
	{
		camera1.MoveCamera(kSpeed);
	}
	if (key == 's' || key == 'S')
	{
		camera1.MoveCamera(-kSpeed);
	}
	if (key == 'a' || key == 'A')
	{
		camera1.RotateAroundPoint(camera1.View, -kSpeed * 2.0f, 0.0f, 1.0f, 0.0f);
	}
	if (key == 'd' || key == 'D')
	{
		camera1.RotateAroundPoint(camera1.View, kSpeed * 2.0f, 0.0f, 1.0f, 0.0f);
	}

	if (key == '1')
		light_sample = 1;
	if (key == '2')
		light_sample = 2;
	if (key == '3')
		light_sample = 3;
	if (key == '4')
		light_sample = 4;
	if (key == '5')
		light_sample = 5;
}
void Process_Special_Keys(int key, int x, int y)
{
	//движение камеры
	if (key == GLUT_KEY_UP)
	{
		camera1.MoveCamera(kSpeed);
	}

	if (key == GLUT_KEY_DOWN)
	{
		camera1.MoveCamera(-kSpeed);
	}

	if (key == GLUT_KEY_LEFT)
	{
		camera1.RotateAroundPoint(camera1.View, -kSpeed * 2.0f, 0.0f, 1.0f, 0.0f);
	}

	if (key == GLUT_KEY_RIGHT)
	{
		camera1.RotateAroundPoint(camera1.View, kSpeed * 2.0f, 0.0f, 1.0f, 0.0f);
	}
	glutPostRedisplay();
}

void Initialize()
{
	Shine_a_Light();	//установить освещение
	camera1.PositionCamera(-18.0f, 0.5f, -3.0f, -12.0f, 0.5f, -3.0f, 0.0f, 1.0f, 0.0f);	//установить начальную позицию камеры
	makeDuplication();	//рассчитать координаты тиражированной фигуры
	calcNormals();		//вычислить нормали
	smoothNormals();	//вычислить сглаженные нормали
	loadTexture();		//загрузить текстуру
}

int main(int argc, char* argv[])
{
	width = 500;
	height = 500;
	glutInit(&argc, argv);

	//включить буфер глубины/двойную буферизацию
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow("CG_L3 triangles ('o')/");
	Initialize();								//начальные установки

	glutKeyboardFunc(Process_Normal_Keys);		//обработка клавиш с кодами ascii
	glutSpecialFunc(Process_Special_Keys);		//обработка не-ascii клавиш

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);

	glutIdleFunc(Display);
	glutPassiveMotionFunc(Process_Mouse_Move);

	glutMainLoop();
}