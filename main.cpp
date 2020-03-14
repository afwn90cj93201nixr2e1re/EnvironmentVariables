#include "FIX_NO_USE_META.h"
#include "osDep.h"
#include "amxxmodule.h"
#ifdef _WIN32
	#include <windows.h>
	int unsetenv(const char* name);
	int setenv(const char* name, const char* value, int overwrite);
#endif
static const char* empty = "";
static cell AMX_NATIVE_CALL NGetEnvironmentVariable(AMX *amx, cell *params){
	enum args_e { arg_null, arg_name, arg_buffer, arg_bufferlength };
	int len, iLen;
	const char *b = MF_GetAmxString(amx, params[arg_name], 0, &len);
	len = params[arg_bufferlength];
	const char* value
#ifdef _WIN32
	= getenv(b);
#else
	= secure_getenv(b);
#endif
	iLen = value ? strlen(value) : 0;
	return MF_SetAmxStringUTF8Char(amx, params[arg_buffer], iLen ? value : empty, iLen, len);
}

static cell AMX_NATIVE_CALL NSetEnvironmentVariable(AMX *amx, cell *params){
	enum args_e { arg_null, arg_name, arg_value, arg_replace, arg_errno };
	int len;
	const char *n = MF_GetAmxString(amx, params[arg_name], 0, &len);
	const char *v = MF_GetAmxString(amx, params[arg_value], 1, &len);
	/* printf("Num %d|%d\n",(*params / sizeof(cell)), params[arg_errno]); */
	bool flag_replace  = params[arg_replace] != 0;
	auto ret = setenv(n,v,flag_replace);
	cell *cErrno = MF_GetAmxAddr(amx, params[arg_errno]);
	*cErrno = ret?errno:0;
	return (cell)ret;
}

static cell AMX_NATIVE_CALL NUnSetEnvironmentVariable(AMX *amx, cell *params){
	enum args_e { arg_null, arg_name, arg_errno };
	int len;
	const char *n = MF_GetAmxString(amx, params[arg_name], 0, &len);
	auto ret = unsetenv(n);
	cell *cErrno = MF_GetAmxAddr(amx, params[arg_errno]);
	*cErrno = ret?errno:0;
	return (cell)ret;
}

/* native int GetEnvironmentVariable(const char[] szName, char[] szBuffer, int iBufferLength, bool &bExists = false); */
AMX_NATIVE_INFO _Natives[] = {
	{"GetEnvironmentVariable", NGetEnvironmentVariable},
	{"SetEnvironmentVariable", NSetEnvironmentVariable},
	{"UnSetEnvironmentVariable", NUnSetEnvironmentVariable},

	{NULL,					NULL}
};

void OnAmxxAttach(){ MF_AddNatives(_Natives); }

#ifdef _WIN32
	int setenv(const char* name, const char* value, int overwrite) {
		if (!overwrite && getenv(name) != nullptr) return 0;
		if (*value != '\0') { auto e = _putenv_s(name, value); if (e != 0) { errno = e; return -1; } return 0;}
		if (_putenv_s(name, "  ") != 0) { errno = EINVAL; return -1; }
		*getenv(name) = '\0'; *(getenv(name) + 1) = '=';
		if (_wenviron != nullptr) {
			wchar_t buf[_MAX_ENV + 1];size_t len;
			if (mbstowcs_s(&len, buf, _MAX_ENV + 1, name, _MAX_ENV) != 0) {errno = EINVAL;return -1;}
			*_wgetenv(buf) = u'\0'; *(_wgetenv(buf) + 1) = u'=';
		}
		if (!SetEnvironmentVariableA(name, value)) { errno = EINVAL; return -1; }
		return 0;
	}

	int unsetenv(const char* name) {
		if (_putenv_s(name, "") != 0)return -1;
		return 0;
	}
#endif