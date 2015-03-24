#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>
#include <string>
#include <array>
#include <sstream>

using namespace std;

string getCpuManufacturerAsHex(int reg);
string hexToAscii(string hex);

void sysInfo()
{
	//Holds the decimal value of the EBX, EDX and ECX registers.
	 int EBXReg;
	 int EDXReg;
	 int ECXReg;

	__asm // zero out EAX and call the CPUID instruction. Then move EBX, EDX and ECX into their respective variables.
	{
		XOR EAX, EAX
		CPUID
		
		MOV EBXReg, EBX
		MOV EDXReg, EDX
		MOV ECXReg, ECX
	}

	string EBXHex = getCpuManufacturerAsHex(EBXReg);
	string EDXHex = getCpuManufacturerAsHex(EDXReg);
	string ECXHex = getCpuManufacturerAsHex(ECXReg);

	string EBXAscii = hexToAscii(EBXHex);
	string EDXAscii = hexToAscii(EDXHex);
	string ECXAscii = hexToAscii(ECXHex);

	cout << "EBX Reg: " << EBXHex << " --> " << EBXAscii << endl;
	cout << "EDX Reg: " << EDXHex << " --> " << EDXAscii << endl;
	cout << "ECX Reg: " << ECXHex << " --> " << ECXAscii << endl << endl;

	string CpuManufacturer = ECXAscii + EDXAscii + EBXAscii;
	reverse(CpuManufacturer.begin(), CpuManufacturer.end());

	cout << "Cpu manufacturer: " << CpuManufacturer << endl << endl;
}

// Takes an integer and converts it to base 16, aka hexidecimal... then return it.
string getCpuManufacturerAsHex(int reg)
{
	int i = 0;
	char hexBuffer[9];
	_itoa_s(reg, hexBuffer, 16);

	stringstream ss;

	for (; i < 8; i++)
	{
		ss << hexBuffer[i] << hexBuffer[i + 1];
		i++;
	}

	string s = ss.str();

	return s;
}

//Convert a hex value to the equivalent Ascii string
string hexToAscii(string hex)
{
	int len = hex.length();
	std::string newString;
	for (int i = 0; i< len; i += 2)
	{
		string byte = hex.substr(i, 2);
		char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
		newString.push_back(chr);
	}

	return newString;
}

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears the depth and color buffers.
	glClearColor(1.0, 0.0, 0.0, 1.0); //Clears the windows with the specified color. Color order is red, green, blue, alpha.

	glutSwapBuffers(); //Swaps between front- and backbuffer, also called double buffering.
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv); //Initialize the GLUT library
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL");


	sysInfo();

	glewInit(); //Initialize the GLEW library
	if (glewIsSupported("GL_VERSION_4_0"))
	{
		cout << "GLEW Version is 4.0\n";
	}
	else
	{
		cout << "GLEW Version 4.0 is not supported\n";
	}

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}