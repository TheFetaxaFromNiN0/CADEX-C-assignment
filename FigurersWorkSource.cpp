#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include "Сircles.h"
#include "Helixes.h"
#include "Ellipses.h"
#include "FigureBase.h"
#include <algorithm>
#include <memory>

class FigureBase
{
public:

	virtual std::vector<double> Point(double t) = 0; // возвращает координаты точки по параметру t
	virtual std::vector<double> firstDerivative(double t) = 0; // возвращает первую производную  по параметру t(вектор)
	virtual int Flag() = 0;
	virtual double get_Radius() = 0; // возвращает радис (для Ellepses, радиус большей полуоси)

};


class Сircles :
	public FigureBase
{
private:
	double radius;

public:
	Сircles()
	{
		radius = (double)((rand() % 100 + 1));

	};
	virtual std::vector<double> Point(double t) override
	{
		std::vector<double> coordinate;
		double x = radius * cos(t);
		coordinate.push_back(x);
		double y = radius * sin(t);
		coordinate.push_back(y);
		double z = 0;
		coordinate.push_back(z);
		return coordinate;

	}

	virtual std::vector<double> firstDerivative(double t) override
	{
		std::vector<double> vec;
		double x = radius * (-sin(t)); // (r*cost)`=r*(-sint)
		vec.push_back(x);
		double y = radius * (cos(t)); // (r*sint)`=r*(cost)
		vec.push_back(y);
		double z = 0; // 0`=0
		vec.push_back(z);
		return vec;
	}



	virtual double get_Radius()
	{
		return radius;
	}

	virtual int Flag() override
	{
		return 0;
	}
};
class Helixes :
	public FigureBase
{
private:
	double radius;
public:
	Helixes()
	{
		radius = (double)((rand() % 100 + 1));
	}
	virtual std::vector<double> Point(double t) override
	{
		std::vector<double> coordinate;
		double x = radius * cos(t);
		coordinate.push_back(x);
		double y = radius * sin(t);
		coordinate.push_back(y);
		double z = t;
		coordinate.push_back(z);
		return coordinate;

	}


	virtual std::vector<double> firstDerivative(double t) override
	{
		std::vector<double> vec;
		double x = radius * (-sin(t)); // (r*cost)`=r*(-sint)
		vec.push_back(x);
		double y = radius * (cos(t)); // (r*sint)`=r*(cost)
		vec.push_back(y);
		double z = t; // t`=1
		vec.push_back(z);
		return vec;
	}



	virtual double get_Radius()
	{
		return radius;
	}
	virtual int Flag() override
	{
		return 2;
	}
};



class Ellipses :
	public FigureBase
{
private:
	double radiusA;
	double radiusB;
	std::vector<double> coordinate;
public:
	Ellipses()
	{
		radiusA = (double)((rand() % 100 + 2));
		radiusB = (double)((rand() % 100 + 3));
	}
	std::vector<double> Point(double t) override
	{
		std::vector<double> coordinate;
		double x = radiusA * cos(t);
		coordinate.push_back(x);
		double y = radiusB * sin(t);
		coordinate.push_back(y);
		double z = 0;
		coordinate.push_back(z);
		return coordinate;

	}

	virtual std::vector<double> firstDerivative(double t) override
	{
		std::vector<double> vec;
		double x = radiusA * (-sin(t)); // (a*cost)`=a*(-sint)
		vec.push_back(x);
		double y = radiusB * (cos(t)); // (b*sint)`=b*(cost)
		vec.push_back(y);
		double z = 0;
		vec.push_back(z);
		return vec;
	}



	virtual double get_Radius()
	{
		return radiusA;
	}

	virtual int Flag() override
	{
		return 1;
	}
};


std::vector<std::shared_ptr <FigureBase>> randomFigure(std::vector<std::shared_ptr <FigureBase>>); // заполняет случайным образом контейеекр объектами
std::vector<std::shared_ptr <FigureBase>>  chooseCircles(std::vector<std::shared_ptr <FigureBase>>); // заполняет контейнер окружностями из первого контейнера
bool comparator(std::shared_ptr <FigureBase> a, std::shared_ptr <FigureBase> b); // функция для сортировки(используется в функции sort из STL)
double get_SumRadius(std::vector<std::shared_ptr <FigureBase>>); // возращает сумму радиуса для окружности из 2го контейнера
void ShowCordinate(std::vector<double>);


int main()
{

	double sum = 0;
	double t;
	std::vector<std::shared_ptr <FigureBase>> vec; // контейнер для всех фигур
	std::vector<std::shared_ptr <FigureBase>>  vecCircles;// контейнер только для окружностей
	vec = randomFigure(vec);
	printf("Coordinates:\n");
	for (std::shared_ptr <FigureBase> v : vec)
	{
		t = (double)(rand() % 628 / 100);
		printf("t=%f \n", t);
		ShowCordinate(v->Point(t));
		printf("-coordinate\n");
		ShowCordinate(v->firstDerivative(t));
		printf("-coordinateDerivative");
		printf("\n");
	}
	printf("\n----------------------------\n");
	vecCircles = chooseCircles(vec);
	printf("\n----------------------------\n");
	for (std::shared_ptr <FigureBase> v2 : vecCircles)
	{
		printf("rad %f  - not sorted\n", v2->get_Radius());
	}
	printf("\n----------------------------\n");
	std::sort(vecCircles.begin(), vecCircles.end(), comparator);
	for (std::shared_ptr <FigureBase> v2 : vecCircles)
	{
		printf("rad %f -sorted\n", v2->get_Radius());
	}

	sum = get_SumRadius(vecCircles);
	printf("\n----------------------------\n");
	printf("%f- sum of radius\n", sum);

}


std::vector<std::shared_ptr <FigureBase>> randomFigure(std::vector<std::shared_ptr <FigureBase>> v)
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

			v.emplace_back(std::make_shared<Сircles>());
		}
		if (mask[i] == 1)
		{

			v.emplace_back(std::make_shared<Ellipses>());
		}
		if (mask[i] == 2)
		{

			v.emplace_back(std::make_shared<Helixes>());
		}

	}
	return v;

}



std::vector<std::shared_ptr <FigureBase>>  chooseCircles(std::vector<std::shared_ptr <FigureBase>>  v)
{
	std::vector<std::shared_ptr <FigureBase>>  vec;
	for (std::shared_ptr <FigureBase> vector : v)
	{
		if (vector->Flag() == 0)
		{
			vec.push_back(vector);
		}

	}
	return vec;

}
void ShowCordinate(std::vector<double> coor)
{
	for (double c : coor)
	{
		printf("{%f}", c);
	}
}




bool comparator(std::shared_ptr <FigureBase> a, std::shared_ptr <FigureBase> b)
{
	return (a->get_Radius() < b->get_Radius());
}

double get_SumRadius(std::vector<std::shared_ptr <FigureBase>> vec)
{
	double sum = 0;
	for (std::shared_ptr <FigureBase> v : vec)
	{
		sum = sum + v->get_Radius();
	}
	return sum;
}





