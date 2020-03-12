#include "amxxmodule.h"
static const char* empty = "";
static cell AMX_NATIVE_CALL GetEnvironmentVariable(AMX *amx, cell *params){
	enum args_e { arg_null, arg_name, arg_buffer, arg_bufferlength };
	int len, iLen;
	const char *b = MF_GetAmxString(amx, params[arg_name], 0, &len);
	const char *value = secure_getenv(b);
	iLen = value?strlen(value):0;
	len = params[arg_bufferlength];
    return MF_SetAmxStringUTF8Char(amx, params[arg_buffer], iLen?value:empty, iLen, len);
}

static cell AMX_NATIVE_CALL SetEnvironmentVariable(AMX *amx, cell *params){
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

static cell AMX_NATIVE_CALL UnSetEnvironmentVariable(AMX *amx, cell *params){
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
	{"GetEnvironmentVariable", GetEnvironmentVariable},
	{"SetEnvironmentVariable", SetEnvironmentVariable},
	{"UnSetEnvironmentVariable", UnSetEnvironmentVariable},

	{NULL,					NULL}
};

void OnAmxxAttach(){ MF_AddNatives(_Natives); }
