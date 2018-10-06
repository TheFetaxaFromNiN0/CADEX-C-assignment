#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include "Сircles.h"
#include "Helixes.h"
#include "Ellipses.h"
#include "FigureBase.h"
#include <algorithm>

class FigureBase
{
public:

	virtual std::vector<double> Point() = 0; // возвращает координаты точки по параметру t
	virtual std::vector<double> firstDerivative() = 0; // возвращает первую производную  по параметру t(вектор)
	virtual void ShowCoord() = 0; // показывает координаты точек по данному параметру t
	virtual void ShowDerivative() = 0; // показывает координаты вектора по данному параметру t
	virtual int Flag() = 0; // возвращает флаг, для пометки объекта класса для его определения (является он либо Circles,либо Helixes,либо Ellipses)
	virtual double get_Radius() = 0; // возвращает радис (для Ellepses, радиус большей полуоси)

};

class Сircles :
	public FigureBase
{
private:
	double radius;
	std::vector<double> coordinate;
	std::vector<double> vec;
	double t;

public:
	int flag;
	Сircles(int f)
	{
		radius = (double)((rand() % 100 + 1));
		t = (double)(rand() % 628 / 100);
		flag = f;
	};
	std::vector<double> Point() override
	{
		double x = radius * cos(t);
		coordinate.push_back(x);
		double y = radius * sin(t);
		coordinate.push_back(y);
		double z = 0;
		coordinate.push_back(z);
		return coordinate;

	}

	virtual std::vector<double> firstDerivative() override
	{
		double x = radius * (-sin(t)); // (r*cost)`=r*(-sint)
		vec.push_back(x);
		double y = radius * (cos(t)); // (r*sint)`=r*(cost)
		vec.push_back(y);
		double z = 0; // 0`=0
		vec.push_back(z);
		return vec;
	}

	virtual void ShowCoord() override
	{
		for (double c : coordinate)
		{
			printf("{%f}", c);
		}
		printf("\n");
	}

	virtual void ShowDerivative() override
	{
		for (double c : vec)
		{
			printf("{%f}", c);
		}
		printf("\n");
	}

	virtual int Flag() override
	{
		return flag;
	}

	virtual double get_Radius()
	{
		return radius;
	}
};

class Helixes :
	public FigureBase
{
private:
	double radius;
	double t;
	std::vector<double> coordinate;
	std::vector<double> vec; //
public:
	int flag;
	Helixes(int f)
	{
		radius = (double)((rand() % 100 + 1));
		t = (double)(rand() % 628 / 100);
		flag = f;
	}
	std::vector<double> Point() override
	{
		double x = radius * cos(t);
		coordinate.push_back(x);
		double y = radius * sin(t);
		coordinate.push_back(y);
		double z = t;
		coordinate.push_back(z);
		return coordinate;

	}


	virtual std::vector<double> firstDerivative() override
	{
		double x = radius * (-sin(t)); // (r*cost)`=r*(-sint)
		vec.push_back(x);
		double y = radius * (cos(t)); // (r*sint)`=r*(cost)
		vec.push_back(y);
		double z = t; // t`=1
		vec.push_back(z);
		return vec;
	}

	virtual void ShowCoord() override
	{
		for (double c : coordinate)
		{
			printf("{%f}", c);
		}
		printf("\n");
	}

	virtual void ShowDerivative() override
	{
		for (double c : vec)
		{
			printf("{%f}", c);
		}
		printf("\n");
	}
	virtual int Flag() override
	{
		return flag;
	}

	virtual double get_Radius()
	{
		return radius;
	}
};

class Ellipses :
	public FigureBase
{
private:
	double radiusA;
	double radiusB;
	double t;
	std::vector<double> coordinate; // контейнер для хранение координыт точки
	std::vector<double> vec; // контейнер для хранение вектора производной
public:
	int flag;
	Ellipses(int f)
	{
		radiusA = (double)((rand() % 100 + 2));
		radiusB = (double)((rand() % 100 + 3));
		t = (double)(rand() % 628 / 100);
		flag = f;
	}
	std::vector<double> Point() override
	{
		double x = radiusA * cos(t);
		coordinate.push_back(x);
		double y = radiusB * sin(t);
		coordinate.push_back(y);
		double z = 0;
		coordinate.push_back(z);
		return coordinate;

	}

	virtual std::vector<double> firstDerivative() override
	{
		double x = radiusA * (-sin(t)); // (a*cost)`=a*(-sint)
		vec.push_back(x);
		double y = radiusB * (cos(t)); // (b*sint)`=b*(cost)
		vec.push_back(y);
		double z = 0;
		vec.push_back(z);
		return vec;
	}

	virtual void ShowCoord() override
	{
		for (double c : coordinate)
		{
			printf("{%f}", c);
		}
		printf("\n");

	}

	virtual void ShowDerivative() override
	{
		for (double c : vec)
		{
			printf("{%f}", c);
		}
		printf("\n");
	}

	virtual int Flag() override
	{
		return flag;
	}

	virtual double get_Radius()
	{
		return radiusA;
	}
};

std::vector<FigureBase*> randomFigure(std::vector<FigureBase*>); // заполняет случайным образом контейеекр объектами
std::vector<FigureBase*> chooseCircles(std::vector<FigureBase*>); // заполняет контейнер окружностями из первого контейнера
bool comparator(FigureBase* a, FigureBase* b); // функция для сортировки(используется в функции sort из STL)
double get_SumRadius(std::vector<FigureBase*>); // возращает сумму радиуса для окружности из 2го контейнера


int main()
{

	double sum = 0;
	std::vector<FigureBase*> vec; // контейнер для всех фигур
	std::vector<FigureBase*> vecCircles; // контейнер только для окружностей
	vec = randomFigure(vec);
	printf("\n----------------------------\n");
	vecCircles = chooseCircles(vec);
	printf("\n----------------------------\n");
	for (FigureBase* v2 : vecCircles)
	{
		printf("rad %f  - not sorted\n", v2->get_Radius());
	}
	printf("\n----------------------------\n");
	std::sort(vecCircles.begin(), vecCircles.end(), comparator);
	for (FigureBase* v2 : vecCircles)
	{
		printf("rad %f -sorted\n", v2->get_Radius());
	}

	sum = get_SumRadius(vecCircles);
	printf("\n----------------------------\n");
	printf("%f- sum of radius\n", sum);

}


std::vector<FigureBase*> randomFigure(std::vector<FigureBase*> v)
{
	// Путь создаётся 10 объектов 3х классов случайным образом
	std::vector<int> mask(10);
	for (int i = 0; i < 10; i++)
	{
		mask[i] = rand() % 3;
	}

	for (int m : mask)
	{
		printf("%d ", m);
	}
	printf("\n ");
	for (int i = 0; i < 10; i++)
	{
		if (mask[i] == 0)
		{

			v.emplace_back(new Сircles(0));
		}
		if (mask[i] == 1)
		{

			v.emplace_back(new Ellipses(1));
		}
		if (mask[i] == 2)
		{

			v.emplace_back(new Helixes(2));
		}

	}
	printf("Coordinates :\n");

	for (FigureBase* vec : v)
	{
		vec->Point();
		vec->ShowCoord();
	}
	printf("Vectors of derivative  :\n");
	for (FigureBase* vec : v)
	{
		vec->firstDerivative();
		vec->ShowDerivative();
	}
	return v;

}



std::vector<FigureBase*> chooseCircles(std::vector<FigureBase*> v)
{
	std::vector<FigureBase*> vec;
	for (FigureBase* vector : v)
	{
		if (vector->Flag() == 0)
		{
			vec.push_back(vector);
		}

	}
	printf("Coordinates of circles :\n");
	for (FigureBase* vee : vec)
	{
		vee->ShowCoord();
	}
	return vec;

}

bool comparator(FigureBase* a, FigureBase* b)
{
	return (a->get_Radius() < b->get_Radius());
}

double get_SumRadius(std::vector<FigureBase*> vec)
{
	double sum = 0;
	for (FigureBase* v : vec)
	{
		sum = sum + v->get_Radius();
	}
	return sum;
}


