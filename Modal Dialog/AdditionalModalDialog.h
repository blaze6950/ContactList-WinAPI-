#pragma once
#include "header.h"

class CAdditionalModalDialog
{
public:
	CAdditionalModalDialog(void);
	CAdditionalModalDialog(int i);//конструктор для даблклика
	CAdditionalModalDialog(char i);//конструктор для edita
public:
	~CAdditionalModalDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CAdditionalModalDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	TCHAR Name[200], Phone[30], Email[100];
	HWND hName, hPhone, hEmail, hOk, hCancel;
	BOOL DblClk = FALSE, EDIT = FALSE;
};
