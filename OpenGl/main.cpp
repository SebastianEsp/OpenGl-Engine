#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>
#include <string>
#include <array>
#include <sstream>

using namespace std;

void sysInfo()
{
	char SysType[13];
	string cpuId;

	__asm
	{
		MOV EAX, 0 //Sets EAX to 0
		CPUID

		MOV EAX, EBX
		MOV SysType[0], al
		MOV SysType[1], ah
		SHR EAX, 16
		MOV SysType[2], al
		MOV SysType[3], ah

		MOV EAX, EDX
		MOV SysType[4], al
		MOV SysType[5], ah
		SHR EAX, 16
		MOV SysType[6], al
		MOV SysType[7], ah

		MOV EAX, ECX
		MOV SysType[8], al
		MOV SysType[9], ah
		SHR EAX, 16
		MOV SysType[10], al
		MOV SysType[11], ah
		MOV SysType[12], 00
	}
	cpuId.assign(SysType, 12);

	cout << "CPU Manufacturer: " << cpuId << "\n\n";

	 int EBXReg;
	 int EDXReg;
	 int ECXReg;

	__asm
	{
		XOR EAX, EAX
		CPUID
		MOV EBXReg, EBX

		XOR EAX, EAX
		CPUID
		MOV EDXReg, EDX

		XOR EAX, EAX
		CPUID
		MOV ECXReg, ECX
	}

	char hexBuffer[9];
	_itoa_s(ECXReg, hexBuffer, 16);

	string hexString = ("Hex: %x\n", hexBuffer);

	string singleHex[9];

	for (size_t i = 0; i < 9; i++)
	{
		stringstream ss;
		ss << hexBuffer[i] << hexBuffer[i + 1];
		string s = ss.str();
		singleHex[i] = s;
		i++;
	}

	cout << hex << "Hex: " << hexBuffer << endl;


	_SYSTEM_INFO sysInfo;
	//GetSystemInfo(&sysInfo);
	GetNativeSystemInfo(&sysInfo);

	string cpuArchitecture = to_string(sysInfo.wProcessorArchitecture);
	string cpuLevel = to_string(sysInfo.wProcessorLevel);
	string cpuRevision = to_string(sysInfo.wProcessorRevision);
	cout << "Processor Architecture: " + cpuArchitecture + "\n";
	cout << "Processor Level: " + cpuLevel + "\n";
	cout << "Processor Revision: " + cpuRevision + "\n\n";
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
	glutCreateWindow("OpenGL Fist Windows");


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