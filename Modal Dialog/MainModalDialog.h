#pragma once
#include "header.h"

class CMainModalDialog
{
public:
	CMainModalDialog(void);
public:
	~CMainModalDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CMainModalDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	void Cls_OnTimer(HWND hwnd, UINT id);
	HWND hListBox, hAdd, hEdit, hDelete;
	std::vector<Contact> book;
};
