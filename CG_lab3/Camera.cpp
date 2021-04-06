#include "Camera.h"

Camera::Camera()
{

}
void Camera::PositionCamera(float posX, float posY, float posZ,
	float viewX, float viewY, float viewZ,
	float upX, float upY, float upZ)
{
	//���������� ������� ������
	Vector3f _Position = Vector3f(posX, posY, posZ);
	Vector3f _View = Vector3f(viewX, viewY, viewZ);
	Vector3f _UpVector = Vector3f(upX, upY, upZ);

	Position = _Position;
	View = _View;
	UpVector = _UpVector;
}
void Camera::MoveCamera(float speed)
{
	Vector3f _View = View - Position;	//���������� ����������� �������

	//����������� ������
	Position.x += _View.x * speed;	//�������� ��������� 
	Position.z += _View.z * speed;	//������

	View.x += _View.x * speed;	//�������� ����������� 
	View.z += _View.z * speed;	//������� ������
}
void Camera::RotateView(float angle, float x, float y, float z)
{
	Vector3f _newView;
	Vector3f _View;

	//���������� ����������� �������
	_View = View - Position;

	//���������� ����� � ������� ����������� ����
	float cosA = (float)cos(angle);
	float sinA = (float)sin(angle);

	//����������� ���������� �� �����-�� ����� ��������
	//����� ���������� X ��� ��������� �����
	_newView.x = (cosA + (1 - cosA) * x * x) * _View.x;
	_newView.x += ((1 - cosA) * x * y - z * sinA) * _View.y;
	_newView.x += ((1 - cosA) * x * z + y * sinA) * _View.z;

	//����� ���������� Y ��� ��������� �����
	_newView.y = ((1 - cosA) * x * y + z * sinA) * _View.x;
	_newView.y += (cosA + (1 - cosA) * y * y) * _View.y;
	_newView.y += ((1 - cosA) * y * z - x * sinA) * _View.z;

	//����� ���������� Z ��� ��������� �����
	_newView.z = ((1 - cosA) * x * z - y * sinA) * _View.x;
	_newView.z += ((1 - cosA) * y * z + x * sinA) * _View.y;
	_newView.z += (cosA + (1 - cosA) * z * z) * _View.z;

	//���������� ����� ������ ������
	View.x = Position.x + _newView.x;
	View.y = Position.y + _newView.y;
	View.z = Position.z + _newView.z;
}
void Camera::SetViewByMouse(GLint width, GLint height)
{
	POINT mousePos;		//������� ����

	//��������� ���������� ������ ����
	int middleX = width / 2.0f;
	int middleY = height / 2.0f;

	float angleY = 0.0f;	//����������� ������� �����/����
	float angleZ = 0.0f;	//��������, ����������� ��� �������� �����-������ (�� ��� Y)
	static float currentRotX = 0.0f;

	//�������� ������� ���������� ����
	GetCursorPos(&mousePos);

	//���� ��������� ���� �� ����������
	//������ ������� �� �����
	if (mousePos.x == middleX && mousePos.y == middleY) return;

	//������� ���������� ������� � ����� ����
	SetCursorPos(middleX, middleY);

	//����������, ���� ��� ������� ������
	angleY = (float)((middleX - mousePos.x)) / 1000.0f;
	angleZ = (float)((middleY - mousePos.y)) / 1000.0f;

	static float lastRotX = 0.0f;
	lastRotX = currentRotX;	//��������� ��������� ���� �������� 
							//� ���������� ������ currentRotX

	//���� ������� ������ ������ �������, �������� ���
	//����� ��������� �������� ��������
	if (currentRotX > 1.0f)
	{
		currentRotX = 1.0f;
		if (lastRotX != 1.0f)
		{
			//����� ����� ���, ������ ������� ����� ��������� �������� ����� � ����, ����� 
			//����� ������, ���������������� ������� ������� ������ � 
			//������������� �������
			Vector3f vAxis = Cross(View - Position, UpVector);

			//����������� ���
			vAxis = Normalize(vAxis);

			//������� ������ ������ ����� ��� �� �������� ����
			RotateView(1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}

	//���� ���� ������ -1.0f
	else if (currentRotX < -1.0f)
	{
		currentRotX = -1.0f;
		if (lastRotX != -1.0f)
		{
			//��������� ���
			Vector3f vAxis = Cross(View - Position, UpVector);

			//����������� ���
			vAxis = Normalize(vAxis);

			//�������
			RotateView(-1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}

	//���� � �������� 1.0f -1.0f - ������ �������
	else
	{
		Vector3f vAxis = Cross(View - Position, UpVector);
		vAxis = Normalize(vAxis);
		RotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
	}

	//������ ������� ������ ������ Y-���
	RotateView(angleY, 0, 1, 0);
}
void Camera::RotateAroundPoint(Vector3f _Center, float angle, float x, float y, float z)
{
	Vector3f _NewPosition;

	//������� �����, ������ �������� ����� ��������
	Vector3f vPos = Position - _Center;

	//�������� ����� � ������� ����
	float cosA = (float)cos(angle);
	float sinA = (float)sin(angle);

	//������ �������� X ����� ��������
	_NewPosition.x = (cosA + (1 - cosA) * x * x) * vPos.x;
	_NewPosition.x += ((1 - cosA) * x * y - z * sinA) * vPos.y;
	_NewPosition.x += ((1 - cosA) * x * z + y * sinA) * vPos.z;

	//�������� Y
	_NewPosition.y = ((1 - cosA) * x * y + z * sinA) * vPos.x;
	_NewPosition.y += (cosA + (1 - cosA) * y * y) * vPos.y;
	_NewPosition.y += ((1 - cosA) * y * z - x * sinA) * vPos.z;

	//�������� Z
	_NewPosition.z = ((1 - cosA) * x * z - y * sinA) * vPos.x;
	_NewPosition.z += ((1 - cosA) * y * z + x * sinA) * vPos.y;
	_NewPosition.z += (cosA + (1 - cosA) * z * z) * vPos.z;

	//���������� ����� ������� ������
	Position = _Center + _NewPosition;
}