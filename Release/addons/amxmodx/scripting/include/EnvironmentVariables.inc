#if defined _environment_variables
	#endinput
#endif

#define _environment_variables

#if !defined EINVAL
#define EINVAL 22 // Invalid argument
#endif

#if !defined ENOMEM
#define ENOMEM 12 // Not enough space/cannot allocate memory
#endif

#if AMXX_VERSION_NUM >= 175
	#pragma reqlib environmentvariables
	#if !defined AMXMODX_NOAUTOLOAD
		#pragma loadlib environmentvariables
	#endif
#else
	#pragma library environmentvariables
#endif

/**
* Retrieves the environment variable value.
*
* @param name			Client index, or 0 to retrieve the server hostname
* @param buffer			Buffer to copy name to
* @param buffLength		Maximum buffer size
*
* @return         		Number of cells written to buffer
*/
native GetEnvironmentVariable(const name[], const buffer[], const buffLength);

/**
* Errors:
* 	@EINVAL - name is NULL, points to a string of length 0, or contains an '=' character.
* 	@ENOMEM - Insufficient memory to add a new variable to the environment
*/

/**
* Adds the variable 'name' to the environment with the value 'value',
* if 'name' does not already exist.  If 'name' does exist in the environment,
* then its value is changed to 'value' if 'overwrite' is nonzero; if 'overwrite' is zero, 
* then the value of 'name' is not changed (and returns a success status).
*
* @param name			Environment name
* @param value			Value to set
* @param owerwrite		Overwrite flag
* @param _error			Set an error code here if anything goes wrong
*
* @return          		0 on success, or -1 on error
*/
native SetEnvironmentVariable(const name[], const value[], const bool:overwrite, &_error = 0);

/**
* Deletes the variable 'name' from the environment.
* If 'name' does not exist in the environment, then the
* function succeeds, and the environment is unchanged.
*
* @param name			Environment name
* @param _error			Set an error code here if anything goes wrong
*
* @return          		0 on success, or -1 on error.
*/
native UnSetEnvironmentVariable(const name[], &_error = 0);