#include "pch.h"
#include "CInPlaceList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CInPlaceList

CInPlaceList::CInPlaceList(int iItem, int iSubItem, CStringList* plstItems, int nSel)
{
    m_iItem = iItem;
    m_iSubItem = iSubItem;

    m_lstItems.AddTail(plstItems);
    m_nSel = nSel; // 디폴트 아이템 설정
    m_bESC = FALSE;
}


CInPlaceList::~CInPlaceList()
{
}


BOOL CInPlaceList::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

    if (pMsg->message == WM_KEYDOWN)
    {
        if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
        {
            ::TranslateMessage(pMsg);
            ::DispatchMessage(pMsg);
            return TRUE;
        }
    }

    return CComboBox::PreTranslateMessage(pMsg);
}
BEGIN_MESSAGE_MAP(CInPlaceList, CComboBox)
    ON_WM_CREATE()
    ON_WM_KILLFOCUS()
    ON_WM_CHAR()
    ON_WM_NCDESTROY()
    ON_CONTROL_REFLECT(CBN_CLOSEUP, &CInPlaceList::OnCbnCloseup)
END_MESSAGE_MAP()


int CInPlaceList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CComboBox::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  여기에 특수화된 작성 코드를 추가합니다.
    CFont* font = GetParent()->GetFont();
    SetFont(font);

    //콤보 박스에 아이템 설정

    for (POSITION pos = m_lstItems.GetHeadPosition(); pos != NULL; )
    {
        AddString((LPCTSTR)(m_lstItems.GetNext(pos)));
    }

    SetCurSel(m_nSel); // 디폴트 설정
    SetFocus();
    return 0;
}



void CInPlaceList::OnKillFocus(CWnd* pNewWnd)
{
    CComboBox::OnKillFocus(pNewWnd);

    // TODO: 여기에 메시지 처리기 코드를 추가합니다.
    CString str;
    GetWindowText(str);

    LV_DISPINFO dispinfo;
    dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
    dispinfo.hdr.idFrom = GetDlgCtrlID();
    dispinfo.hdr.code = LVN_ENDLABELEDIT;

    dispinfo.item.mask = LVIF_TEXT;
    dispinfo.item.iItem = m_iItem;
    dispinfo.item.iSubItem = m_iSubItem;
    dispinfo.item.pszText = m_bESC ? NULL : LPTSTR((LPCTSTR)str);
    dispinfo.item.cchTextMax = str.GetLength();

    GetParent()->GetParent()->SendMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM)&dispinfo);

    PostMessage(WM_CLOSE);
}



void CInPlaceList::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    if (nChar == VK_ESCAPE || nChar == VK_RETURN)
    {
        if (nChar == VK_ESCAPE)
            m_bESC = TRUE;
        GetParent()->SetFocus();
        return;
    }
    CComboBox::OnChar(nChar, nRepCnt, nFlags);
}



void CInPlaceList::OnNcDestroy()
{
    CComboBox::OnNcDestroy();

    delete this;
    // TODO: 여기에 메시지 처리기 코드를 추가합니다.
}




void CInPlaceList::OnCbnCloseup()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    GetParent()->SetFocus();
}
