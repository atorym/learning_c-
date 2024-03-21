/*
Тест

Точка в геометрии — это позиция в пространстве. Мы можем определить точку в 3D-пространстве
как набор координат x, y и z. Например, Point(0.0, 1.0, 2.0) будет точкой в координатном
пространстве x = 0.0, y = 1.0 и z = 2.0.

Вектор в физике — это величина, которая имеет длину и направление (но не положение). Мы можем
определить вектор в 3D-пространстве через значения x, y и z, представляющие направление вектора
вдоль осей x, y и z. Например, Vector(1.0, 0.0, 0.0) будет вектором, представляющим направление
только вдоль положительной оси x длиной 1.0.

Вектор может применятся к точке для перемещения точки на новую позицию. Это делается путем
добавления направления вектора к позиции точки. Например, Point(0.0, 1.0, 2.0) + Vector(0.0, 2.0, 0.0)
даст точку (0.0, 3.0, 2.0).

Точки и векторы часто используются в компьютерной графике (точка для представления вершин фигуры,
а векторы — для перемещения фигуры).

a) Сделайте класс Point3D дружественным классу Vector3D и реализуйте метод moveByVector() в классе Point3D.
b) Вместо того, чтобы класс Point3D был дружественным классу Vector3D, сделайте метод
Point3D::moveByVector() дружественным классу Vector3D.
c) Переделайте свой ответ из задания b, используя 5 отдельных файлов: Point3D.h, Point3D.cpp,
Vector3D.h, Vector3D.cpp и main.cpp.
*/

#include <iostream>

class Vector3D;

class Point3D {
private:
 double m_x, m_y, m_z;

public:
 Point3D(double x = 0.0, double y = 0.0, double z = 0.0)
     : m_x(x)
     , m_y(y)
     , m_z(z) {
 }

 void print() {
   std::cout << "Point(" << m_x << " , " << m_y << " , " << m_z << ")\n";
 }

 void moveByVector(const Vector3D& v);
};

class Vector3D {
private:
 double m_x, m_y, m_z;

public:
 Vector3D(double x = 0.0, double y = 0.0, double z = 0.0)
     : m_x(x)
     , m_y(y)
     , m_z(z) {}

 void print() {
   std::cout << "Vector(" << m_x << " , " << m_y << " , " << m_z << ")\n";
 }

 friend void Point3D::moveByVector(const Vector3D& v);
};


void Point3D::moveByVector(const Vector3D& v) {
 m_x += v.m_x;
 m_y += v.m_y;
 m_z += v.m_z;
}


int main() {

 Point3D p(3.0, 4.0, 5.0);
 Vector3D v(3.0, 3.0, -2.0);
 p.print();
 p.moveByVector(v);
 p.print();

 return EXIT_SUCCESS;
}