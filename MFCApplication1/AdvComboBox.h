#pragma once
#include <afxwin.h>
class AdvComboBox :
    public CComboBox
{
    DECLARE_DYNAMIC(AdvComboBox)

public:
int m_nVK;
    AdvComboBox(int nItem, int nSubItem, CStringList* plstItems, int nSel);

    virtual BOOL PreTranslateMessage(MSG* pMsg);
 

public:

    int         m_nItem;
    int         m_nSubItem;
    CStringList m_lstItems;
    int         m_nSel;
    bool        m_bESC;
public:
    DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//    afx_msg void OnCbnKillfocus();
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnNcDestroy();
    afx_msg void OnCbnCloseup();
};

