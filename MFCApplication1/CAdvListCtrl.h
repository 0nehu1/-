#pragma once
#include <afxcmn.h>
class CAdvListCtrl :
    public CListCtrl
{
    DECLARE_DYNAMIC(CAdvListCtrl)

public:
    CAdvListCtrl();
    virtual ~CAdvListCtrl();

    void AdvComboBox(int nItem, int nCol, CString& lstItems, int nSel);
   

    DECLARE_MESSAGE_MAP()
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLvnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);

    int HitTestEx(CPoint& point, int* nCol) const;
    void SetColumnCombo(int nColumn);

protected:
    DECLARE_MESSAGE_MAP()

    int m_nColumn;
    CComboBox* ShowAdvComboBox(int nItem, int nCol, CStringList& lstItems, int nSel);
};

