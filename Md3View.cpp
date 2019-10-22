
// Md3View.cpp: CMd3View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Md3.h"
#endif

#include "Md3Doc.h"
#include "Md3View.h"
#include "CLine.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMd3View

IMPLEMENT_DYNCREATE(CMd3View, CView)

BEGIN_MESSAGE_MAP(CMd3View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SEL_COL, &CMd3View::OnSelCol)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMd3View 생성/소멸

CMd3View::CMd3View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMd3View::~CMd3View()
{
}

BOOL CMd3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMd3View 그리기

void CMd3View::OnDraw(CDC* pDC)
{
	CMd3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int n = pDoc->m_oa.GetSize();
	for (int i = 0; i < n; i++) {
		CLine* p;
		p = (CLine*)pDoc->m_oa[i];
		p->Draw(pDC);
	}
}


// CMd3View 인쇄

BOOL CMd3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMd3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMd3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMd3View 진단

#ifdef _DEBUG
void CMd3View::AssertValid() const
{
	CView::AssertValid();
}

void CMd3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMd3Doc* CMd3View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMd3Doc)));
	return (CMd3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMd3View 메시지 처리기


void CMd3View::OnSelCol()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		col = dlg.GetColor();
	}
}

CPoint pnt;
void CMd3View::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags == MK_LBUTTON) {
		CLine* p = new CLine(pnt, point);
		GetDocument()->m_oa.Add(p);
	}
	pnt = point;

	CView::OnMouseMove(nFlags, point);
}
