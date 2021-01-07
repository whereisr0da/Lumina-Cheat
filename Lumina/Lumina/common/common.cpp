#include "../common/includes.h"

#include "common.h"

#include <fstream>

namespace common {

	bool active = true;
	bool unload = false;

	float hitmarkerTime = 0;
	int   hitmarkerDamage = 0;

	HMODULE currentModule = NULL;
	HMODULE engineModule = NULL;
	HMODULE clientModule = NULL;
	HMODULE materialsystemModule = NULL;
	HMODULE vguimatsurfaceModule = NULL;
	HMODULE vstdlibModule = NULL;
	HMODULE soundsystemModule = NULL;
	HMODULE vgui2Module = NULL;
	HMODULE datacacheModule = NULL;
	HMODULE dx9apiModule = NULL;
	HMODULE inputSysModule = NULL;
	HMODULE localizeModule = NULL;
	HMODULE steamApiModule = NULL;
	HMODULE studiorenderModule = NULL;

	std::string luminaPath = XorStr("C:\\Lumina\\");

	void ps(std::string message)
	{
#ifdef _DEBUG

		time_t rawtime;
		char buffer[80];
		char bufferLog[80];
		char printedString[150];

		time(&rawtime);

		strftime(buffer, sizeof(buffer), XorStr("%H:%M:%S"), localtime(&rawtime));

		strftime(bufferLog, sizeof(bufferLog), XorStr("%d.%m.%Y"), localtime(&rawtime));

		sprintf(printedString, XorStr("[%s] %s\r\n"), buffer, message.c_str());

#endif

#ifdef FULL_DEBUG

		std::ofstream logFile;

		std::string logFileNAme = "C:\\Lumina\\log.";

		logFileNAme += bufferLog;
		logFileNAme += ".txt";

		logFile.open(logFileNAme.c_str(), std::ios_base::app);

		std::string ff = printedString;

		logFile << ff.substr(0, ff.length() - 2);
		logFile << "\n";
#endif

#ifdef _DEBUG
		printf(printedString);
#endif

	}

	void pf(std::string fmt, ...) {

#ifdef _DEBUG

			int size = ((int)fmt.size()) * 2 + 50;
			std::string str;
			va_list ap;
			while (1) {
				str.resize(size);
				va_start(ap, fmt);
				int n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
				va_end(ap);
				if (n > -1 && n < size) {
					str.resize(n);
					goto fine;
				}
				if (n > -1)
					size = n + 1;
				else
					size *= 2;
			}

		fine:

			time_t rawtime;
			char buffer[80];
			char bufferLog[80];
			char printedString[150];

			time(&rawtime);

			strftime(buffer, sizeof(buffer), XorStr("%H:%M:%S"), localtime(&rawtime));

			strftime(bufferLog, sizeof(bufferLog), XorStr("%d.%m.%Y"), localtime(&rawtime));

			sprintf(printedString, XorStr("[%s] %s\r\n"), buffer, str.c_str());
#endif

#ifdef FULL_DEBUG

			std::ofstream logFile;

			std::string logFileNAme = "C:\\Lumina\\log.";

			logFileNAme += bufferLog;
			logFileNAme += ".txt";

			logFile.open(logFileNAme.c_str(), std::ios_base::app);

			std::string ff = printedString;

			logFile << ff.substr(0,ff.length()-2);
			logFile << "\n";
#endif

#ifdef _DEBUG
			printf(printedString);
#endif
	}

	void exit() {

#ifdef _DEBUG
		ps("common::exit : exit");
#endif

		FreeLibraryAndExitThread(common::currentModule, 0);

		active = false;
	}
}