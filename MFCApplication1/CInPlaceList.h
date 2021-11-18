#pragma once
#include <afxwin.h>
class CInPlaceList :
    public CComboBox
{
private:
    int         m_iItem;
    int         m_iSubItem;
    CStringList m_lstItems;
    int         m_nSel;
    BOOL        m_bESC;

public:
    CInPlaceList(int iItem, int iSubItem, CStringList* plstItems, int nSel);

public:
    virtual ~CInPlaceList();

    // Generated message map functions
protected:
   

public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnNcDestroy();
    afx_msg void OnCbnCloseup();
};

