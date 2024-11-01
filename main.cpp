#include <iostream>
#include <cmath>

const double EPSILON_0 = 8.854e-12;
const double MU_0 = 4 * M_PI *1e-7;

class Field
{
	protected:
		double *value;

public:
	Field()
	{
		value = new double [3];
	}

	Field(double x, double y, double z)
	{
		value = new double[3];
	}

	Field(const Field &other)
	{
		value = new double[3];
		for(int i = 0; i < 3; i++)
		{
			value[i] = other.value[i];
		}
	}

	virtual ~Field()
	{
		delete[] value;
	}

	void printMagnitude() const
	{
		std::cout << "Field Components: (" << value[0] << "," << value[1] << "," << value[2] << ")\n";
	}

	friend std::ostream& operator<<(std::ostream &out, const Field &f)
	{
		out << "(" << f.value[0] << "," << f.value[1] << "," << f.value[2] << ")";
		return out;
	}
};

class ElectricField:
public Field
{
	private:
		double calculatedField;

	public:
		ElectricField(double x, double y, double z): Field (x, y, z), calculatedField(0) {}

		void calculateField(double Q, double r)
		{
			calculatedField = Q / (4 * M_PI * r * r * EPSILON_0);
		}

		ElectricField operator+(const ElectricField &other) const
		{
			return ElectricField(value[0] + other.value[0], value[1] + other.value[1], value[2] + other.value[2]);
		}
		
		void printCalculatedField() const
		{
			std::cout << "Calculated Electric Field: " << calculatedField << "N/C\n";
		}
};

class MagneticField:
public Field
{
	private:
		double calculatedField;

	public:
		MagneticField(double x, double y, double z) : Field(x, y, z), calculatedField(0) {}

	void calculateField(double I, double r)
	{
		calculatedField = I * MU_0 / (2 * M_PI * r);
	}

	MagneticField operator+(const MagneticField &other) const
	{
		return MagneticField(value[0] + other.value[0], value[1] + other.value[1], value[2] + other.value[2]);
	}

	void printCalculatedField() const
	{
		std::cout << "Calculated Magnetic Field: " << calculatedField << "T\n";
	}
};

int main()
{
	ElectricField e1(0.0, 1e5, 1e3);
	MagneticField m1(0.0, 0.5, 0.2);

	std::cout << "Electric Field e1: ";
	e1.printMagnitude();
	
	std::cout << "Magnetic Field m1: ";
	m1.printMagnitude();

	double Q = 1e-6;
	double I = 10.0;
	double r = 0.1;

	e1.calculateField(Q, r);
	m1.calculateField(I, r);

	e1.printCalculatedField();
	m1.printCalculatedField();
	
	ElectricField e2(1e3, 2e3, 3e3);
	ElectricField e3 = e1 +e2;
	std::cout << "Resultant Electric Field (e1 +e2): " << e3 << std::endl;

	MagneticField m2(0.3, 0.4, 0.5);
	MagneticField m3 = m1 + m2;
	std::cout << "Resultant Magnetic Field (m1 + m2): " << m3 << std::endl;

	return 0;
}
