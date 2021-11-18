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
    m_nSel = nSel; // ����Ʈ ������ ����
    m_bESC = FALSE;
}


CInPlaceList::~CInPlaceList()
{
}


BOOL CInPlaceList::PreTranslateMessage(MSG* pMsg)
{
    // TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

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

    // TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
    CFont* font = GetParent()->GetFont();
    SetFont(font);

    //�޺� �ڽ��� ������ ����

    for (POSITION pos = m_lstItems.GetHeadPosition(); pos != NULL; )
    {
        AddString((LPCTSTR)(m_lstItems.GetNext(pos)));
    }

    SetCurSel(m_nSel); // ����Ʈ ����
    SetFocus();
    return 0;
}



void CInPlaceList::OnKillFocus(CWnd* pNewWnd)
{
    CComboBox::OnKillFocus(pNewWnd);

    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
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
    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}




void CInPlaceList::OnCbnCloseup()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    GetParent()->SetFocus();
}
