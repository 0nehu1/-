
// MFCApplication1.h: PROJECT_NAME 애플리케이션에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.

enum _enumCONTROLTYPE
{
	_CT_CButton
};
// CMFCApplication1App:
// 이 클래스의 구현에 대해서는 MFCApplication1.cpp을(를) 참조하세요.
//

class CMFCApplication1App : public CWinApp
{
public:
	CMFCApplication1App();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
public:

	CWnd* _SetItemControl(int nRow,
		int nCol,
		_enumCONTROLTYPE enumControlType,
		DWORD dwStyle = 0,
		LPCTSTR lpszText = NULL,
		UINT uID = 0,
		int nWidth = CW_USEDEFAULT,
		int nHeight = CW_USEDEFAULT,
		CFont* pFont = NULL)
	{
	
		// create new control.
		CWnd* pWnd;
		dwStyle |= WS_VISIBLE;
		CRect rcControl(0, 0, CW_USEDEFAULT, CW_USEDEFAULT);

	

		switch (enumControlType)
		{
	
		case _CT_CButton: // 클릭되어서 default button이 됐을 때, 이를 나타내는 rectangle이 button둘레에 그려진다.이 rectangel이 scroll할 때 잔상으로 남게 된다.
						  // 생성시에는 transparent 속성이 없음에도 불구하고
						  // redraw할 때 transparent 된다.
						  // 따라서, text와 겹칠 때 잔상이 남는다.
			pWnd = new CButton();
			((CButton*)pWnd)->Create(_T(""), dwStyle, rcControl, pWnd, 0);
			break;
		}
	}
};

extern CMFCApplication1App theApp;
