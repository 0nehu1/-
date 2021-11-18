#include "pch.h"
#include "CAdvListCtrl.h"
#include "resource.h"
#include "CInPlaceList.h"

IMPLEMENT_DYNAMIC(CAdvListCtrl, CListCtrl)

BEGIN_MESSAGE_MAP(CAdvListCtrl, CListCtrl)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, &CAdvListCtrl::OnLvnEndlabeledit)
	
END_MESSAGE_MAP()



CAdvListCtrl::CAdvListCtrl()
{
	m_nColumn = -1;
}





void CAdvListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (GetFocus() != this) SetFocus();
	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CAdvListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (GetFocus() != this) SetFocus();
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CAdvListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	int nIndex;
	CListCtrl::OnLButtonDown(nFlags, point);

	int nColumn;
	if ((nIndex = HitTestEx(point, &nColumn)) != -1)
	{
		UINT flag = LVIS_FOCUSED;
		if ((GetItemState(nIndex, flag) & flag) == flag && m_nColumn == nColumn)
		{
				if (!(GetWindowLong(m_hWnd, GWL_STYLE) & LVS_EDITLABELS))
				{ 
					CStringList lstItems{};
					lstItems.AddTail(L"Item 1");
					lstItems.AddTail(L"Item 2");

					CString strGet = this->GetItemText(nIndex, m_nColumn);
					ShowInPlaceList(nIndex, m_nColumn, lstItems, 0);
					SetItemState(nIndex, LVIS_SELECTED, LVIS_SELECTED);
				}	
		}
		else
		{
			SetItemState(nIndex, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		}
	}
}


void CAdvListCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CListCtrl::OnLButtonUp(nFlags, point);
}


void CAdvListCtrl::OnLvnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO* pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	LVITEMW* pItem = &pDispInfo->item;

	if (pItem->pszText != NULL)
	{
		SetItemText(pItem->iItem, pItem->iSubItem, pItem->pszText);
	}
	*pResult = 0;
}


int CAdvListCtrl::HitTestEx(CPoint& point, int* nCol) const
{
	return 0;
}

void CAdvListCtrl::SetColumnCombo(int nColumn)
{
	m_nColumn = nColumn;
}

extern "C" CComboBox * CAdvListCtrl::ShowInPlaceList(int nItem, int nCol,
	CStringList& lstItems, int nSel)
{
	if (!EnsureVisible(nItem, TRUE)) return NULL;

	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
	int nColumnCount = pHeader->GetItemCount();
	if (nCol >= nColumnCount || GetColumnWidth(nCol) < 10)
		return NULL;

	int offset = 0;
	for (int i = 0; i < nCol; i++)
		offset += GetColumnWidth(i);

	CRect rect;
	GetItemRect(nItem, &rect, LVIR_BOUNDS);

	CRect rcClient;
	GetClientRect(&rcClient);
	if (offset + rect.left < 0 || offset + rect.left > rcClient.right)
	{
		CSize size;
		size.cx = offset + rect.left;
		size.cy = 0;
		Scroll(size);
		rect.left -= size.cx;
	}

	rect.left += offset + 4;
	rect.right = rect.left + GetColumnWidth(nCol) - 3;
	int height = rect.bottom - rect.top;
	rect.bottom += 5 * height;
	if (rect.right > rcClient.right) rect.right = rcClient.right;

	// �޺� �ڽ��� ��Ÿ�� ����
	DWORD dwStyle = WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL |
		CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL;
	//CInPlaceList �� CComboBox�� ��ӹ޾� ���� ������ Ŭ����
	CComboBox* pList = new CInPlaceList(nItem/*�������ε���*/, nCol/*�÷�*/, &lstItems/*�޺� �ڽ��� �� �����۸���Ʈ*/, nSel/*����Ʈ ������ �ε���*/);
	pList->Create(dwStyle, rect, this, GetDlgCtrlID());
	pList->SetItemHeight(-1, height);
	pList->SetHorizontalExtent(GetColumnWidth(nCol));

	return pList;
}
