#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>
#include <string>
#include <array>
#include <sstream>

using namespace std;

string getCpuManufacturerAsHex(int reg);

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

	string EBXHex = getCpuManufacturerAsHex(EBXReg);
	string EDXHex = getCpuManufacturerAsHex(EDXReg);
	string ECXHex = getCpuManufacturerAsHex(ECXReg);

	cout << "EBX Reg: " << EBXHex << endl << "EDX Reg: " << EDXHex << endl << "ECX Reg: " << ECXHex << endl << endl;

	_SYSTEM_INFO sysInfo;
	//GetSystemInfo(&sysInfo);
	GetNativeSystemInfo(&sysInfo);

	string cpuArchitecture = to_string(sysInfo.wProcessorArchitecture);
	string cpuLevel = to_string(sysInfo.wProcessorLevel);
	string cpuRevision = to_string(sysInfo.wProcessorRevision);
	cout << "Processor Architecture: " << cpuArchitecture << endl;
	cout << "Processor Level: " << cpuLevel << endl;
	cout << "Processor Revision: " << cpuRevision << endl << endl;
}

string getCpuManufacturerAsHex(int reg)
{
	int i = 0;
	char hexBuffer[9];
	_itoa_s(reg, hexBuffer, 16);

	string hexString = ("Hex: %x\n", hexBuffer);

	stringstream ss;

	for (; i < 8; i++)
	{
		ss << hexBuffer[i] << hexBuffer[i + 1];
		i++;
	}

	string s = ss.str();

	return s;
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