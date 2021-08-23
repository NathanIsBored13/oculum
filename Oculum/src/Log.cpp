#include "ocpch.h"
#include "Log.h"

#include <string.h>

namespace Oculum
{
#ifndef OC_DIST
    Log Log::log;

	Log::Log() : clk(std::chrono::steady_clock::now())
	{
		AllocConsole();
		AttachConsole(GetCurrentProcessId());

#pragma warning(push)
#pragma warning(disable: 4996)
		freopen("CON", "w", stdout);
		freopen("CON", "w", stderr);
		freopen("CON", "r", stdin);
#pragma warning (pop)

		OC_INFO("Logger Initialised");
	}

	Log::~Log()
	{

	}

	void Log::Trace(const char* fmt, ...)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		va_list args;
		va_start(args, fmt);
		log.Print(fmt, "TRACE", args);
	}

	void Log::Info(const char* fmt, ...)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		va_list args;
		va_start(args, fmt);
		log.Print(fmt, "INFO ", args);
	}

	void Log::Warn(const char* fmt, ...)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);
		va_list args;
		va_start(args, fmt);
		log.Print(fmt, "WARN ", args);
	}

	void Log::Error(const char* fmt, ...)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		va_list args;
		va_start(args, fmt);
		log.Print(fmt, "ERROR", args);
	}

	void PaddedInsert(char* msg, int start, const char* str, int padlen)
	{
		int len = strlen(str);
		memcpy(msg + start + padlen - len, str, len);
	}

	void Log::Print(const char* fmt, const char* level, va_list args)
	{
		__int64 t_micro = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - clk).count();
		int t_hour = (int)std::floor(t_micro / 3600000000);
		t_micro -= (__int64)t_hour * 3600000000;
		int t_min = (int)std::floor(t_micro / 60000000);
		t_micro -= (__int64)t_min * 60000000;
		int t_sec = (int)(std::floor(t_micro / 1000000));
		t_micro -= (__int64)t_sec * 1000000;
		int t_mili = (int)std::floor(t_micro / 1000);
		t_micro -= (__int64)t_mili * 1000;

		char time_out[] = "[00, 00, 00, 000, 000]";
		PaddedInsert(time_out, 1, std::to_string(t_hour).c_str(), 2);
		PaddedInsert(time_out, 5, std::to_string(t_min).c_str(), 2);
		PaddedInsert(time_out, 9, std::to_string(t_sec).c_str(), 2);
		PaddedInsert(time_out, 13, std::to_string(t_mili).c_str(), 3);
		PaddedInsert(time_out, 18, std::to_string(t_micro).c_str(), 3);
		std::cout << time_out << " " << level << " : ";

		vprintf(fmt, args);
		va_end(args);

		std::cout << std::endl;
	}
#endif
}