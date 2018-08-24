#pragma once
#include <windows.h>
#include <windowsX.h>
#include <tchar.h>
#include "resource.h"
#include <vector>

struct Contact
{
	TCHAR Name[200];
	TCHAR Phone[30];
	TCHAR Email[100];
};