#pragma once
#include <afx.h>
class CLine :
	public CObject
{
	CPoint m_From, m_To;

public:
	CLine() {};
	CLine(CPoint From, CPoint To) {
		m_From = From;
		m_To = To;
	}

	void Draw(CDC* pDC) {
		pDC->MoveTo(m_From);
		pDC->LineTo(m_To);
	}
};

