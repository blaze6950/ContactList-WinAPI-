#include "MainModalDialog.h"
#include "AdditionalModalDialog.h"

CMainModalDialog* CMainModalDialog::ptr = NULL;

CMainModalDialog::CMainModalDialog(void)
{
	ptr = this;
}

CMainModalDialog::~CMainModalDialog(void)
{

}

void CMainModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL CMainModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hListBox = GetDlgItem(hwnd, IDC_LIST1);
	hAdd = GetDlgItem(hwnd, IDC_BUTTON1);
	hEdit = GetDlgItem(hwnd, IDC_BUTTON3);
	hDelete = GetDlgItem(hwnd, IDC_BUTTON4);
	return TRUE;
}

void CMainModalDialog::Cls_OnTimer(HWND hwnd, UINT id)
{
	if (SendMessage(hListBox, LB_GETCOUNT, 0, 0))
	{
		EnableWindow(hEdit, TRUE);
		EnableWindow(hDelete, TRUE);
	}
	else{
		EnableWindow(hEdit, FALSE);
		EnableWindow(hDelete, FALSE);
	}
}

void CMainModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_BUTTON1)
	{
		SetTimer(hwnd, 1, 1000, NULL);
		CAdditionalModalDialog dlg;
		// передача данных через public-поле класса CAdditionalModalDialog дополнительного диалога
		INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, CAdditionalModalDialog::DlgProc);
		if(result == IDOK)
		{
			Contact newCont;
			_tcscpy_s(newCont.Name, dlg.Name); _tcscpy_s(newCont.Phone, dlg.Phone); _tcscpy_s(newCont.Email, dlg.Email);
			book.push_back(newCont);
			int index1 = book.size();
			index1--;
			// Переданные от дополнительного диалога данные отображаются на статике
			int index = SendMessage(hListBox, LB_ADDSTRING, 0, LPARAM(dlg.Name));
			SendMessage(hListBox, LB_SETITEMDATA, index, LPARAM(index1));
		}
	}
	else if (id == IDC_BUTTON4)
	{
		if (SendMessage(hListBox, LB_GETCURSEL, 0, 0) != LB_ERR)
		{
			int asd = 0;
			for (auto it = book.begin(); 1; it++, asd++)
			{
				if (asd == int(SendMessage(hListBox, LB_GETCURSEL, 0, 0)))
				{
					book.erase(it);
					break;
				}
			}
			SendMessage(hListBox, LB_DELETESTRING, SendMessage(hListBox, LB_GETCURSEL, 0, 0), 0);
		}
		else{
			MessageBox(hwnd, TEXT("Choose one contact!"), TEXT("Error"), MB_OK);
		}
	}
	else if (id == IDC_BUTTON3)
	{
		if (SendMessage(hListBox, LB_GETCURSEL, 0, 0) != LB_ERR)
		{
			CAdditionalModalDialog dlg('d');
			SendMessage(hListBox, LB_GETTEXT, SendMessage(hListBox, LB_GETCURSEL, 0, 0), LPARAM(dlg.Name));
			LRESULT newCont = SendMessage(hListBox, LB_GETITEMDATA, SendMessage(hListBox, LB_GETCURSEL, 0, 0), 0);
			SendMessage(hListBox, LB_DELETESTRING, SendMessage(hListBox, LB_GETCURSEL, 0, 0), 0);
			_tcscpy(dlg.Email, book.at(newCont).Email);
			_tcscpy(dlg.Phone, book.at(newCont).Phone);
			INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, CAdditionalModalDialog::DlgProc);
			if (result == IDOK)
			{
				_tcscpy(book.at(newCont).Email, dlg.Email);
				_tcscpy(book.at(newCont).Phone, dlg.Phone);
				_tcscpy(book.at(newCont).Name, dlg.Name);
				int index = SendMessage(hListBox, LB_ADDSTRING, 0, LPARAM(dlg.Name));
				SendMessage(hListBox, LB_SETITEMDATA, index, LPARAM(newCont));
			}
			else{
				_tcscpy(book.at(newCont).Email, dlg.Email);
				_tcscpy(book.at(newCont).Phone, dlg.Phone);
				_tcscpy(book.at(newCont).Name, dlg.Name);
				int index = SendMessage(hListBox, LB_ADDSTRING, 0, LPARAM(dlg.Name));
				SendMessage(hListBox, LB_SETITEMDATA, index, LPARAM(newCont));
			}
		}
		else{
			MessageBox(hwnd, TEXT("Choose one contact!"), TEXT("Error"), MB_OK);
		}
	}
	else if (codeNotify == LBN_DBLCLK)
	{
		CAdditionalModalDialog dlg(1);
		SendMessage(hListBox, LB_GETTEXT, SendMessage(hListBox, LB_GETCURSEL, 0, 0), LPARAM(dlg.Name));
		LRESULT newCont = SendMessage(hListBox, LB_GETITEMDATA, SendMessage(hListBox, LB_GETCURSEL, 0, 0), 0);
		//SendMessage(hListBox, LB_DELETESTRING, SendMessage(hListBox, LB_GETCURSEL, 0, 0), 0);
		_tcscpy(dlg.Email, book.at(newCont).Email);
		_tcscpy(dlg.Phone, book.at(newCont).Phone);
		INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, CAdditionalModalDialog::DlgProc);
	}
}

BOOL CALLBACK CMainModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_TIMER, ptr->Cls_OnTimer);
	}
	return FALSE;
}
