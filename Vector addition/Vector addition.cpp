// Vector addition.cpp : Defines the entry point for the console application.
//
// This program calculates details about vectors and adds or subtracts them
//
//

#include "stdafx.h"

#define PI 3.141592

class bearing {
public:
	double direction;
	double angleInTriangle;
	std::string strVal;

	void updateStrVal() {

		// TODO: work out direction as a string 
		strVal = "";
		if (direction == -1) {

			strVal = "Zero";

		}

	}

	void calculateAngleInTriangle() {

		do {

			if (direction == -1) {

				angleInTriangle = -1;
				break;
			}

			//straight line
			if (direction == 0 || direction == 90 || direction == 270) {

				angleInTriangle = 0;
				break;
			}

			if (direction < 90) { // 1st quadrant

				angleInTriangle = 90 - direction;
				break;
			}

			if (direction < 180) { // 2nd quadrant

				angleInTriangle = direction - 90;
				break;
			}

			if (direction < 270) { // 3rd quadrant

				angleInTriangle = 90 - (direction - 180);
				break;
			}

			if (direction < 360) { // 4th quadrant

				angleInTriangle = direction - 270;
				break;
			}

			//if angle > 360
			throw "Bad angle in bearing";


		} while (false);

	}

	bearing(double val) {

		while (val >= 360) {

			val -= 360;

		}

		while (val < 0) {

			val += 360;

		}

		direction = val;

		updateStrVal();


		//calculate angle in triangle
		calculateAngleInTriangle();

	}

	bearing() {

		direction = 0;
		strVal = "North";
		angleInTriangle = 0;

	}

	bearing & operator=(double rhs);

};

bearing& bearing::operator=(double rhs)
{
	float temp = rhs;

	//make value good
	while (temp >= 360) {

		temp -= 360;

	}

	while (temp < 0) {

		temp += 360;

	}

	this->direction = temp;
	updateStrVal();
	calculateAngleInTriangle();
	//set string value
	return *this;
}

/*************************************************************************/

class vector {

public:
	

	double magnitude;
	bearing direction; //max 360

	double northMagnitude;
	double eastMagnitude;

	//print details about vector
	void printInfo(int accuracy) {
		std::cout << "Magnitude: " << std::fixed << std::setprecision(accuracy) << magnitude << std::endl;
		std::cout << "Direction: " << std::fixed << std::setprecision(accuracy) << direction.direction << std::endl;
		std::cout << "North Magnitude: " << std::fixed << std::setprecision(accuracy) << northMagnitude << std::endl;
		std::cout << "East Magnitude: " << std::fixed << std::setprecision(accuracy) << eastMagnitude << std::endl;
		std::cout << "Angle to horisontal axis: " << std::fixed << std::setprecision(accuracy) << direction.angleInTriangle << std::endl;
		std::cout << "Angle to vertical axis: " << std::fixed << std::setprecision(accuracy) << 90 - direction.angleInTriangle << std::endl;

		return;
	}

	//constructors

	vector() {

		
		magnitude = 0;
		direction = -1;
		northMagnitude = 0;
		eastMagnitude = 0;
		return;

	}

	

	vector(double newMagnitude, bearing newDirection) {

		

		//add testing to ensure values are good
		magnitude = newMagnitude;
		direction = newDirection;
		
		//calculate components
		do {

			if (direction.angleInTriangle == -1) {

				northMagnitude = 0;
				eastMagnitude = 0;
				break;
			}

			//straight line
			if (direction.direction == 0) {
				
				northMagnitude = magnitude;
				eastMagnitude = 0;
				break;
			}

			if (direction.direction == 90) {

				eastMagnitude = magnitude;
				northMagnitude = 0;
				break;
			}

			if (direction.direction == 180) {

				northMagnitude = -1 * magnitude;
				eastMagnitude = 0;
				break;
			}

			if (direction.direction == 90) {

				eastMagnitude = -1 * magnitude;
				northMagnitude = 0;
				break;
			}

			//not straight line
			if (direction.direction < 90) { // 1st quadrant
				northMagnitude = magnitude * sin(direction.angleInTriangle * (PI / 180));
				eastMagnitude = magnitude * cos(direction.angleInTriangle * (PI / 180));
				break;
			}

			if (direction.direction < 180) { // 2nd quadrant
				northMagnitude = -1 * magnitude * sin(direction.angleInTriangle * (PI / 180));
				eastMagnitude = magnitude * cos(direction.angleInTriangle * (PI / 180));
				break;
			}

			if (direction.direction < 270) { // 3rd quadrant
				northMagnitude = -1 * magnitude * sin(direction.angleInTriangle * (PI / 180));
				eastMagnitude = -1 * magnitude * cos(direction.angleInTriangle * (PI / 180));
				break;
			}

			if (direction.direction < 360) { // 4th quadrant
				northMagnitude = magnitude * sin(direction.angleInTriangle * (PI / 180));
				eastMagnitude = -1 * magnitude * cos(direction.angleInTriangle * (PI / 180));
				break;
			}

		} while (false);
	}

	vector(double newMagnitude) {

		

		//add testing to ensure values are good
		magnitude = newMagnitude;
		direction = 0;

		northMagnitude = magnitude;
		eastMagnitude = 0;

	}

	vector(double northComponent, double eastComponent) {

		

		setUp(northComponent, eastComponent);

	}

	void calculateDirectionString() {

		do {

			if (direction.direction == -1) {
				direction.strVal = "No Direction";
					break;
				}
			if (direction.direction == 0) {
				direction.strVal = "North";
				break;
			}
			if (direction.direction <= 45) {
				std::stringstream ss(direction.direction);
				std::string str;
				ss >> str;
				direction.strVal = (std::string) "North " + str + (std::string) " Degrees East";
				break;
			}
			if (direction.direction < 90) {
				std::stringstream ss(90 - direction.direction);
				std::string str;
				ss >> str;
				direction.strVal = (std::string) "East " + str + (std::string) " Degrees North";
				break;
			}
			if (direction.direction == 90) {
				direction.strVal = "East";
				break;
			}
			if (direction.direction <= 135) {
				std::stringstream ss(direction.direction - 90);
				std::string str;
				ss >> str;
				direction.strVal = (std::string) "East " + str + (std::string) " Degrees South";
				break;
			}
			if (direction.direction < 180) {
				std::stringstream ss(90 - (direction.direction - 90));
				std::string str;
				ss >> str;
				direction.strVal = (std::string) "South " + str + (std::string) " Degrees East";
				break;
			}
			if (direction.direction == 180) {
				direction.strVal = "South";
				break;
			}
			if (direction.direction <= 225) {
				std::stringstream ss(direction.direction - 180);
				std::string str;
				ss >> str;
				direction.strVal = (std::string) "South " + str + (std::string) " Degrees East";
				break;
			}

		} while (false);

	}

	void setUp(double northComponent, double eastComponent) {

		//add testing here to ensure values are good
		northMagnitude = northComponent;
		eastMagnitude = eastComponent;

		//calculate magnitude and direction

		magnitude = sqrt(northMagnitude * northMagnitude + eastMagnitude * eastMagnitude);

		//calculate direction
		do {

			if (northMagnitude == 0) {

				if (eastMagnitude == 0) {

					direction = -1;

				}

			}

			if (northMagnitude > 0 && eastMagnitude > 0) { // 1st quadrant

				direction = 90 - atan(northMagnitude / eastMagnitude) * (180 / PI); //calculate and convert from radians to degrees
				break;
			}

			if (northMagnitude < 0 && eastMagnitude > 0) { // 2nd quadrant

				direction = atan(abs(northMagnitude) / eastMagnitude) * (180 / PI) - 90; //calculate and convert from radians to degrees
				break;
			}

			if (northMagnitude > 0 && eastMagnitude < 0) { // 3rd quadrant

				direction = (90 - atan(northMagnitude / abs(eastMagnitude)) * (180 / PI)) + 180; //calculate and convert from radians to degrees
				break;
			}

			if (northMagnitude < 0 && eastMagnitude < 0) { // 4th quadrant

				direction = atan(abs(northMagnitude) / abs(eastMagnitude)) * (180 / PI) + 270; //calculate and convert from radians to degrees
				break;
			}

		} while (false);


	}

	//operators
	vector& operator+=(const vector& rhs)
	{
		//add vectors

		setUp(this->northMagnitude + rhs.northMagnitude, this->eastMagnitude + rhs.eastMagnitude);

		return *this;
	}

	vector& operator-=(const vector& rhs)
	{
		//subtract vectors
		setUp(this->northMagnitude - rhs.northMagnitude, this->eastMagnitude - rhs.eastMagnitude);
		return *this;
	}



	vector& operator=(vector rhs);

};

inline vector operator+(vector lhs, const vector& rhs)
{
	lhs += rhs;
	return lhs;
}

inline vector operator-(vector lhs, const vector& rhs)
{
	lhs -= rhs;
	return lhs;
}

vector& vector::operator=(vector rhs) {

	this->direction = rhs.direction;
	this->magnitude = rhs.magnitude;
	this->northMagnitude = rhs.magnitude;
	this->eastMagnitude = rhs.eastMagnitude;
	return *this;

}

/*************************************************************************/



int main()
{

	try {

		while (true) {
			int numDP;
			std::cout << "How many decimal places for result? ";
			std::cin >> numDP;
			long long int numV;
			std::cout << "how many vectors? ";
			std::cin >> numV;

			vector ** v = new vector*[numV];
			if (numV < 1) throw "bad value";
			for (int i = 0; i < numV; i++) {

				std::cout << "Setting up vector " << i << std::endl;
				char mode;
				float arg1;
				float arg2;
				std::cout << "1: magnitude and direction \n2: north magnitude and east magnitude" << std::endl;
				std::cin >> mode;
				if (mode == '1') {

					std::cin >> arg1 >> arg2;
					v[i] = new vector(arg1, (bearing)arg2);

				}
				else {
					if (mode == '2') {

						std::cin >> arg1 >> arg2;
						v[i] = new vector(arg1, arg2);

					}
					else {
						throw "bad value";
					}
				}
			}

			vector resultant = *v[0];
			for (int i = 1; i < numV; i++) {
				resultant += *v[i];
			}
			std::cout << "resultant:\n";
			resultant.printInfo(numDP);
			std::cout << "\n\n\n";
		}
	}
	catch(std::exception& e) {

		std::cout << "An error occured. " << e.what() << "\nMost likely causes:" << std::endl;
		std::cout << " - You tried to allocate less than 1 vector" << std::endl;
		std::cout << " - You tried to allocate too many vectors" << std::endl;
		std::cout << " - You gave bad input" << std::endl;

	}
	catch (...) {

		std::cout << "An error occured. \nMost likely causes:" << std::endl;
		std::cout << " - You tried to allocate less than 1 vector" << std::endl;
		std::cout << " - You tried to allocate too many vectors" << std::endl;
		std::cout << " - You gave bad input" << std::endl;

	}

	system("PAUSE");
    return 0;
}

