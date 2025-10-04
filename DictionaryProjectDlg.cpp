
// DictionaryProjectDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "DictionaryProject.h"
#include "DictionaryProjectDlg.h"
#include "afxdialogex.h"

#include <string>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


extern std::vector<std::vector<std::wstring>> mywtextvector;
int wylosowanaglobalna;
int language = 0;


void pokaz_wektor2D(std::vector<std::vector<std::wstring>> tabl)
{
	
	for (auto rzad : tabl)
	{
		
		for (auto elem : rzad)
			AfxMessageBox(elem.c_str());

	}
	int sz = tabl.size();
	AfxMessageBox(sz);
}


CDictionaryProjectDlg::CDictionaryProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DICTIONARYPROJECT_DIALOG, pParent)
	, Russian(_T(""))
	, English(_T(""))
	, Polish(_T(""))
	, Sentence(_T(""))
	, Words(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	srand(time(NULL));				 // inicjowanie losowania musi byc w jakiejs funkcji bo poza funkcja wyrzuci error przy kompilacji
}

void CDictionaryProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Russian);
	DDX_Text(pDX, IDC_EDIT2, English);
	DDX_Text(pDX, IDC_EDIT3, Polish);
	DDX_Text(pDX, IDC_EDIT4, Sentence);
	DDX_Text(pDX, IDC_EDIT5, Words);
	CFont* m_pFont = new CFont();
	m_pFont->CreatePointFont(250, _T("Arial"));
	GetDlgItem(IDC_EDIT1)->SetFont(m_pFont, TRUE);  // USTAWIA FONT WIEKSZY DLA PIERWSZEGO OKNA EDIT
	GetDlgItem(IDC_EDIT2)->SetFont(m_pFont, TRUE);  // USTAWIA FONT WIEKSZY DLA DRUGIEGO OKNA EDIT2
	GetDlgItem(IDC_EDIT3)->SetFont(m_pFont, TRUE);  // USTAWIA FONT WIEKSZY DLA DRUGIEGO OKNA EDIT2
	GetDlgItem(IDC_EDIT4)->SetFont(m_pFont, TRUE);  // USTAWIA FONT WIEKSZY DLA DRUGIEGO OKNA EDIT2
	GetDlgItem(IDC_EDIT5)->SetFont(m_pFont, TRUE);  // USTAWIA FONT WIEKSZY DLA DRUGIEGO OKNA EDIT2
}

BEGIN_MESSAGE_MAP(CDictionaryProjectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDictionaryProjectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDictionaryProjectDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDictionaryProjectDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDictionaryProjectDlg message handlers

BOOL CDictionaryProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	SetIcon(hIcon, TRUE);
		return TRUE;  // return TRUE  unless you set the focus to a control
}

	// TODO: Add extra initialization here

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDictionaryProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDictionaryProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int wylosuj()
{
	return (rand() % mywtextvector.size()); // funkcja licz slowa zwraca wartosc o 1 wieksza od liczby slow dzieki ostatnie slowo "koniec" nigdy nie zostanie wyswietlone i po to ono tu jest uwaga! JESZCZE TRZEBA BYLO DODAC TUTAJ + 1 bo indeksowanie tablic zaczyna sie od 0 czyli razem musi byæ +2
}

void CDictionaryProjectDlg::OnBnClickedButton1()
{
	//pokaz_wektor2D(mywtextvector);
	Russian = "";
	English = "";
	Polish = "";
	Sentence = "";
	if (mywtextvector.size())
	{
		wylosowanaglobalna = wylosuj();
		switch (language)
		{
		case 0:
			Russian = mywtextvector[wylosowanaglobalna][0].c_str();
			break;
		case 1:
			English = mywtextvector[wylosowanaglobalna][1].c_str();
			break;
		case 2:
			Polish = mywtextvector[wylosowanaglobalna][2].c_str();
			break;
		default:
			break;
		}
		Words = mywtextvector.size();
		UpdateData(false);
		Russian = mywtextvector[wylosowanaglobalna][0].c_str();	// cztery linijki potrzebne aby zapisac tekst do pol przed wykasowaniem row w vektorze
		English = mywtextvector[wylosowanaglobalna][1].c_str();
		Polish = mywtextvector[wylosowanaglobalna][2].c_str();
		Sentence = mywtextvector[wylosowanaglobalna][3].c_str();

		mywtextvector.erase(mywtextvector.begin() + wylosowanaglobalna);
	}
	else
	{
		AfxMessageBox(_T("THE END!!!"));
		exit(1);
	}
}


void CDictionaryProjectDlg::OnBnClickedButton2()
{
	UpdateData(false);
}


void CDictionaryProjectDlg::OnBnClickedButton3()
{
	language = (language + 1) % 3;
}

