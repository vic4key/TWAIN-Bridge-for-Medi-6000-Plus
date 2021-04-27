// Medi-6000.Plus.h : Defines the exported functions for the DLL application.
//

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MEDI6000PLUS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MEDI6000PLUS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef MEDI6000PLUS_EXPORTS
#define MEDI6000PLUS_API __declspec(dllexport)
#else
#define MEDI6000PLUS_API __declspec(dllimport)
#endif

// https://msdn.microsoft.com/en-us/library/aa384187%28v=vs.85%29.aspx?f=255&MSPPError=-2147217396

/*
 * To execute an export function in a DLL.
 * Command : %SystemRoot%\SysWOW64\rundll32.exe <DLL>,<Function> <Arguments>
 * Example : %SystemRoot%\SysWOW64\rundll32.exe Medi-6000.Plus.dll,_fnTWAINSelect@16 0
 * Example : %SystemRoot%\SysWOW64\rundll32.exe Medi-6000.Plus.dll,_fnTWAINAcquire@16 0 Film-Scanner
 */

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * Select Scanner.
 * @param[in] lpszCmdLine The window handle of the application in string.
 */
MEDI6000PLUS_API void CALLBACK fnTWAINSelect(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow);

/**
 * Acquire Image.
 * @param[in] lpszCmdLine The window handle and product name of the application in string.
 */
MEDI6000PLUS_API void CALLBACK fnTWAINAcquire(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow);

#ifdef __cplusplus
}
#endif // __cplusplus