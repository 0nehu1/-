#include "pch.h"
#include "CAdvListCtrl.h"

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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (GetFocus() != this) SetFocus();
	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CAdvListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (GetFocus() != this) SetFocus();
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CAdvListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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
					CStringList* lstItems{};
					lstItems->AddTail(L"Item 1");
					lstItems->AddTail(L"Item 2");

					CString strGet = this->GetItemText(nIndex, m_nColumn);
					ShowAdvComboBox(nIndex, m_nColumn, lstItems, 0);
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CListCtrl::OnLButtonUp(nFlags, point);
}


void CAdvListCtrl::OnLvnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO* pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

extern "C" AdvComboBox * CAdvListCtrl::ShowAdvComboBox(int nItem, int nCol, CStringList* lstItems, int nSel)
{
	if (!EnsureVisible(nItem, TRUE)) return NULL;

	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
	int nColumnCount = pHeader->GetItemCount();
	if (nCol >= nColumnCount || GetColumnWidth(nCol) < 10)
		return NULL;

	int offset = 0;
	for (int i = 0; i < nCol; ++i)
	{
		offset += GetColumnWidth(i);
	}

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
	int nHeight = rect.bottom - rect.top;
	rect.bottom += 5 * nHeight;
	if (rect.right > rcClient.right) rect.right = rcClient.right;

	DWORD dwStyle = WS_BORDER | WS_CHILD | WS_VISIBLE |
		CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL;
	//CComboBox* pList = new CAdvComboBox(nItem, nCol, &lstItems, nSel);
	CComboBox* pList = new AdvComboBox( nItem, nCol,  lstItems,  nSel);
	//pList->Create(dwStyle, rect, this, IDC_ADVCOMBO);
	//pList->SetItemHeight(-1, nHeight);
	//pList->SetHorizontalExtent(GetColumnWidth(nCol));

	
	return nullptr;
}

AdvComboBox* ShowAdvComboBox(int nItem, int nCol, CStringList& lstItems, int nSel)
{
	return nullptr;
}
