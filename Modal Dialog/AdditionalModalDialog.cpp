#include "AdditionalModalDialog.h"

CAdditionalModalDialog* CAdditionalModalDialog::ptr = NULL;

CAdditionalModalDialog::CAdditionalModalDialog(void)
{
	ptr = this;
}

CAdditionalModalDialog::CAdditionalModalDialog(int i)
{
	ptr = this;
	DblClk = TRUE;
}

CAdditionalModalDialog::CAdditionalModalDialog(char i)
{
	ptr = this;
	EDIT = TRUE;
}

CAdditionalModalDialog::~CAdditionalModalDialog(void)
{

}

void CAdditionalModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL CAdditionalModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	if (!DblClk && !EDIT)
	{
		hName = GetDlgItem(hwnd, IDC_EDIT1);
		hPhone = GetDlgItem(hwnd, IDC_EDIT3);
		hEmail = GetDlgItem(hwnd, IDC_EDIT4);
		hOk = GetDlgItem(hwnd, IDOK);
		hCancel = GetDlgItem(hwnd, IDCANCEL);
		// Переданные от главного диалога данные отображаются на статике
	}
	else if (EDIT)
	{
		hName = GetDlgItem(hwnd, IDC_EDIT1);
		hPhone = GetDlgItem(hwnd, IDC_EDIT3);
		hEmail = GetDlgItem(hwnd, IDC_EDIT4);
		hOk = GetDlgItem(hwnd, IDOK);
		hCancel = GetDlgItem(hwnd, IDCANCEL);
		// Переданные от главного диалога данные отображаются на статике
		SetWindowText(hName, Name);
		SetWindowText(hPhone, Phone);
		SetWindowText(hEmail, Email);
	}
	else{
		hName = GetDlgItem(hwnd, IDC_EDIT1);
		hPhone = GetDlgItem(hwnd, IDC_EDIT3);
		hEmail = GetDlgItem(hwnd, IDC_EDIT4);
		hOk = GetDlgItem(hwnd, IDOK);
		hCancel = GetDlgItem(hwnd, IDCANCEL);
		ShowWindow(hCancel, SW_HIDE);
		// Переданные от главного диалога данные отображаются на статике
		SetWindowText(hName, Name);
		EnableWindow(hName, FALSE);
		SetWindowText(hPhone, Phone);
		EnableWindow(hPhone, FALSE);
		SetWindowText(hEmail, Email);
		EnableWindow(hEmail, FALSE);
	}
	return TRUE;
}


void CAdditionalModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDOK)
	{
		if (SendMessage(hName, EM_LINELENGTH, 0, 0) && SendMessage(hPhone, EM_LINELENGTH, 0, 0) && SendMessage(hEmail, EM_LINELENGTH, 0, 0))
		{
			GetWindowText(hName, Name, 200);
			GetWindowText(hPhone, Phone, 30);
			GetWindowText(hEmail, Email, 100);
			EndDialog(hwnd, IDOK);
		}
		else{
			MessageBox(NULL, TEXT("Fill in all the fields"), TEXT("Error!"), IDOK);
		}
	}
	else if(id == IDCANCEL)
	{
		EndDialog(hwnd, IDCANCEL);
	}
}

BOOL CALLBACK CAdditionalModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
