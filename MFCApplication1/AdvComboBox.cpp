#include "pch.h"
#include "AdvComboBox.h"

IMPLEMENT_DYNAMIC(AdvComboBox, CComboBox)

AdvComboBox::AdvComboBox(int nItem, int nSubItem, CStringList * plstItems, int nSel)
	: m_nItem(nItem)
	, m_nSubItem(nSubItem)
	, m_nSel(nSel)
	, m_bESC(false)
{
	m_lstItems.AddTail(plstItems);
}



BEGIN_MESSAGE_MAP(AdvComboBox, CComboBox)
	ON_WM_CREATE()
	ON_WM_KILLFOCUS()
	ON_WM_CHAR()
	ON_WM_NCDESTROY()
	ON_CONTROL_REFLECT(CBN_CLOSEUP, &AdvComboBox::OnCbnCloseup)
END_MESSAGE_MAP()



BOOL AdvComboBox::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		// Enter Key
		if (pMsg->wParam == VK_RETURN ||
			pMsg->wParam == VK_ESCAPE ||
			pMsg->wParam == VK_TAB)
		{
			m_nVK = pMsg->wParam;
			::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
		}
	}

	return CComboBox::PreTranslateMessage(pMsg);
}



int AdvComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	CFont* pFont = GetParent()->GetFont();
	SetFont(pFont);

	for (POSITION pos = m_lstItems.GetHeadPosition(); pos != NULL;)
	{
		AddString((LPCTSTR)(m_lstItems.GetNext(pos)));
	}
	SetCurSel(m_nSel);
	SetFocus();

	return 0;
}


void AdvComboBox::OnKillFocus(CWnd* pNewWnd)
{
	CComboBox::OnKillFocus(pNewWnd);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CString strTemp;
	GetWindowText(strTemp);

	LV_DISPINFO dispinfo;
	dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
	dispinfo.hdr.idFrom = GetDlgCtrlID();
	//dispinfo.hdr.code = LVN_ENDLABELEDIT;

	dispinfo.item.mask = LVIF_TEXT;
	dispinfo.item.iItem = m_nItem;
	dispinfo.item.iSubItem = m_nSubItem;
	dispinfo.item.pszText = m_bESC ? NULL : LPTSTR((LPCTSTR)strTemp);
	dispinfo.item.cchTextMax = strTemp.GetLength();

	GetParent()->GetParent()->SendMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM)&dispinfo);

	PostMessage(WM_CLOSE);
}


void AdvComboBox::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (nChar == VK_ESCAPE || nChar == VK_RETURN)
	{
		if (nChar == VK_ESCAPE)
		{
			m_bESC = true;
		}
		GetParent()->SetFocus();
		return;
	}

	CComboBox::OnChar(nChar, nRepCnt, nFlags);
}


void AdvComboBox::OnNcDestroy()
{
	CComboBox::OnNcDestroy();

	delete this;
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void AdvComboBox::OnCbnCloseup()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GetParent()->SetFocus();
}
