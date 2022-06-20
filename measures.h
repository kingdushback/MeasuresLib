#pragma once
#include <string>
#include <map>
#include <exception>
#include <iostream>
#include <vector>

typedef long double ld;
typedef long long ll;

std::map<std::string, ld> prefixes =
{
	{ "da", 10 },
	{ "ga", 100 },
	{ "k", 1000 },
	{ "M", 1000000},
	{ "G", 1000000000},
	{ "T", 1000000000000},
	{ "P", 1000000000000000},
	{ "E", 1000000000000000000},
	{ "Z", 1e21},
	{ "Y", 1e24},
	{ "d", 1 / 10},
	{ "c", 1 / 100},
	{ "m", 1 / 1000},
	{ std::string({(char)230}), 1 / 1000000},
	{ "n", 1 / 1000000000},
	{ "p", 1 / 1000000000000},
	{ "f", 1 / 1000000000000000},
	{ "a", 1 / 1000000000000000000},
	{ "z", 1e-21},
	{ "y", 1e-24}
};

struct TypeReadException : std::exception
{
	const char* what() const throw () {
		return "Incorrect type read";
	}
};

struct NoDefaultNameException : std::exception
{
	NoDefaultNameException(int l, int m, int t)
	{
		this->l = l, this->m = m, this->t = t;
	}
	int l, m, t;
	const char* what() const throw () {
		return ("Unknown measurment: no default name for m^" + std::to_string(l) + " * g^" + std::to_string(m) + " * s^" + std::to_string(t)).c_str();
	}
};

template <int l, int m, int t>
class Measure_t
{
public:
	ld value;

	Measure_t() 
	{
		value = 0;
	}

	Measure_t(ld val) 
	{
		value = val;
	}

	Measure_t<l, m, t> operator+(const Measure_t<l, m, t> mes) const
	{
		return Measure_t<l, m, t>(value + mes.value);
	}

	Measure_t<l, m, t> operator-(const Measure_t<l, m, t> mes) const
	{
		return Measure_t<l, m, t>(value - mes.value);
	}

	template <int l1, int m1, int t1>
	Measure_t<l + l1, m + m1, t + t1> operator*(const Measure_t<l1, m1, t1> mes) const
	{
		return Measure_t<l + l1, m + m1, t + t1>(value * mes.value);
	}

	template <int l1, int m1, int t1>
	Measure_t<l - l1, m - m1, t - t1> operator/(const Measure_t<l1, m1, t1> mes) const
	{
		return Measure_t<l - l1, m - m1, t - t1>(value / mes.value);
	}

	Measure_t<l, m, t> operator*(const ld s) const
	{
		return Measure_t<l, m, t>(value * ld);
	}

	Measure_t<l, m, t> operator/(const ld s) const
	{
		return Measure_t<l, m, t>(value / ld);
	}

	Measure_t<l, m, t> operator*=(const ld s)
	{
		value *= s;
		return *this;
	}

	Measure_t<l, m, t> operator/=(const ld s)
	{
		value /= s;
		return *this;
	}

	Measure_t<l, m, t> operator+=(const Measure_t<l, m, t> mes)
	{
		value += mes.value;
		return *this;
	}

	Measure_t<l, m, t> operator-=(const Measure_t<l, m, t> mes)
	{
		value -= mes.value;
		return *this;
	}

	void printCustom(std::string measure, int len, int mass, int time, ld conversionCoeff = 1, std::ostream& out = std::cout)
	{
		bool first = true;
		out << value * conversionCoeff << " ";
		if (measure != "")
		{
			first = false;
			out << measure;
		}
		len = l - len;
		mass = m - mass;
		time = t - time;
		if (len != 0)
		{
			if (!first)
			{
				out << " * ";
			}
			else
			{
				first = false;
			}
			out << "m";
			if (len != 1)
			{
				out << "^" << len;
			}
		}
		if (mass != 0)
		{
			if (!first)
			{
				out << " * ";
			}
			else
			{
				first = false;
			}
			out << "g";
			if (mass != 1)
			{
				out << "^" << mass;
			}
		}
		if (time != 0)
		{
			if (!first)
			{
				out << " * ";
			}
			else
			{
				first = false;
			}
			out << "s";
			if (time != 1)
			{
				out << "^" << time;
			}
		}
	}

	void print(std::ostream &out = std::cout) const
	{
		bool first = true;
		out << value << " ";
		if (l != 0)
		{
			if (!first)
			{
				out << " * ";
			}
			else
			{
				first = false;
			}
			out << "m";
			if (l != 1)
			{
				out << "^" << l;
			}
		}
		if (m != 0)
		{
			if (!first)
			{
				out << " * ";
			}
			else
			{
				first = false;
			}
			out << "g";
			if (m != 1)
			{
				out << "^" << m;
			}
		}
		if (t != 0)
		{
			if (!first)
			{
				out << " * ";
			}
			else
			{
				first = false;
			}
			out << "s";
			if (t != 1)
			{
				out << "^" << t;
			}
		}
	}

	constexpr static int getL()
	{
		return l;
	}

	constexpr static int getM()
	{
		return m;
	}

	constexpr static int getT()
	{
		return t;
	}

private:
	void readScal(std::istream &in = std::cin)
	{
		in >> value;
	}

	void readM(std::istream &in = std::cin)
	{
		in >> value;
		std::string mes;
		ld coeff = 1;
		in >> mes;
		if (mes[mes.size() - 1] == 't')
		{
			coeff = 1000;
		}
		else if (mes[mes.size() - 1] != 'g')
		{
			throw TypeReadException();
		}
		mes.pop_back();
		if (mes != "")
		{
			if (prefixes.find(mes) == prefixes.end())
			{
				throw TypeReadException();
			}
			coeff *= prefixes[mes];
		}
		value *= coeff;
	}

	void readSI(std::vector<std::string> measures, std::istream &in = std::cin)
	{
		in >> value;
		std::string mes, measure = "";
		ld coeff = 1;
		in >> mes;
		bool isCorrect = false;
		int num = -1;
		for (int i = 0; i < measures.size(); ++i)
		{
			measure = measures[i];
			if (mes.size() >= measure.size() && std::string(mes.end() - measure.size(), mes.end()) == mes)
			{
				isCorrect = true;
				break;
			}
		}
		for (int i = 0; i < measure.size(); ++i)
		{
			mes.pop_back();
		}
		if (mes != "")
		{
			if (prefixes.find(mes) == prefixes.end())
			{
				throw TypeReadException();
			}
			coeff *= prefixes[mes];
		}
		value *= coeff;
	}
public:

	void read(std::istream &in = std::cin, std::string measure = "", ld conversionCoeff = 1, bool isCustom = false) // if called for scalar reads next double from stream(custom measure overrides), otherwise reads next double and string from stream. isCustom exists to allow reading of custom measures with no symbol and coef = 1
	{
		if (measure != "")
		{
			std::string mes;
			in >> value >> mes;
			value *= conversionCoeff;
			if (mes != measure)
			{
				throw TypeReadException();
			}
		}
		else if (conversionCoeff != 1 || isCustom)
		{
			in >> value;
			value *= conversionCoeff;
		}
		else
		{
			if (l = 0 && m == 0 && t == 0)
			{
				readScal(in);
			}
			else if (l = 1 && m == 0 && t == 0)
			{
				readSI({"m"}, in);
			}
			else if (l = 0 && m == 1 && t == 0)
			{
				readM(in);
			}
			else if (l = 0 && m == 0 && t == 1)
			{
				readSI({"s"}, in);
			}
			else if (l = 0 && m == 0 && t == -1)
			{
				readSI({ "Hz", "Bq"}, in);
			}
			else if (l = 1 && m == 1 && t == -2)
			{
				readSI({ "N" }, in);
			}
			else if (l = 2 && m == 1 && t == -2)
			{
				readSI({ "J" }, in);
			}
			else if (l = 2 && m == 1 && t == -3)
			{
				readSI({ "W" }, in);
			}
			else if (l = -1 && m == 1 && t == -2)
			{
				readSI({ "Pa" }, in);
			}
			else if (l = 2 && m == 0 && t == -2)
			{
				readSI({ "Gy", "Sv"}, in);
			}
			else
			{
				throw NoDefaultNameException(l, m, t);
			}
		}
	}
};

typedef Measure_t<0, 0, 0> scalar;

typedef Measure_t<1, 0, 0> meter;
typedef Measure_t<0, 1, 0> gramm;
typedef Measure_t<0, 0, 1> second;

typedef Measure_t<0, 0, -1> Hz;
typedef Measure_t<1, 1, -2> mN; //milinuton was used due to nuton beeng measured in kg * m / s^2 and kg not beeng base measurement of system
typedef Measure_t<2, 1, -2> mJ; //milijoule was used due to joule beeng measured in kg * m^2 / s^2 and kg not beeng base measurement of system
typedef Measure_t<2, 1, -3> mW; //miliwatt was used due to watt beeng measured in kg * m^2 / s^3 and kg not beeng base measurement of system
typedef Measure_t<-1, 1, -2> mPa; //milipascal was used due to pascal beeng measured in kg / (m * s^2) and kg not beeng base measurement of system

typedef Measure_t<2, 0, -2> Gy; //gray
typedef Measure_t<2, 0, -2> Sv; //sievert