/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 vistart
 * @license https://vistart.me/license/
*/
#pragma once
#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>
#include <iomanip>
using namespace std;
class Point
{
public:
	Point() = default;
	~Point() = default;
	double X() const noexcept;
	virtual Point& X(double const) noexcept;
	double Y() const noexcept;
	virtual Point& Y(double const) noexcept;
	double Z() const noexcept;
	virtual Point& Z(double const) noexcept;
	unsigned char R() const;
	virtual Point& R(unsigned char const);
	unsigned char G() const;
	virtual Point& G(unsigned char const);
	unsigned char B() const;
	virtual Point& B(unsigned char const);
	double NX() const;
	virtual Point& NX(double const);
	double NY() const;
	virtual Point& NY(double const);
	double NZ() const;
	virtual Point& NZ(double const);
	unsigned char ALPHA() const;
	virtual Point& ALPHA(unsigned char const);
	double CONFIDENCE() const;
	virtual Point& CONFIDENCE(double const);
	double INTENSITY() const;
	virtual Point& INTENSITY(double const);
	virtual bool operator==(Point const&) const;
	virtual bool operator!=(Point const&) const;
	virtual bool operator<(Point const&) const;
	virtual bool operator>(Point const&) const;
	enum class Coordination { X, Y, Z };
	virtual bool is_less_than(Point const&, Coordination const&) const;
	virtual bool is_equal_to(Point const&, Coordination const&) const;
	virtual bool is_greater_than(Point const&, Coordination const&) const;
	virtual bool is_equal_or_less_than(Point const&, Coordination const&) const;
	virtual bool is_equal_or_greater_than(Point const&, Coordination const&) const;
	bool has_RGB = false;
	bool has_normal = false;
	bool has_alpha = false;
	bool has_confidence = false;
	bool has_intensity = false;
	void offset(double const, double const, double const);
	double offset_of(double const, Coordination const&) const;
	friend ostream& operator<<(ostream& stream, Point const& point)
	{
		stream << "(" << setprecision(10) << point.__X << "," << setprecision(10) << point.__Y << "," << setprecision(10) << point.__Z << ")";
		return stream;
	}
protected:
	double __X = 0;
	double __Y = 0;
	double __Z = 0;
	unsigned char __R = 0;
	unsigned char __G = 0;
	unsigned char __B = 0;
	double __NX = 0;
	double __NY = 0;
	double __NZ = 0;
	unsigned char __ALPHA = 255;
	double __CONFIDENCE = 1;
	double __INTENSITY = 0.5;
	void set_all_properties(double const, double const, double const,
						    unsigned char const, unsigned char const, unsigned char const,
							double const, double const, double const,
							unsigned char const, double const, double const);
private:
	const char* coord_no_out_of_range_message = "The coordination system code is out of range.";
};

#endif
