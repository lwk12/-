// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Train.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog


CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON13, OnButton13)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

void CMainDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
	EndDialog(TRUE);
	
}

BOOL CMainDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_list.InsertColumn(0,"车次号",LVCFMT_CENTER,100);
	m_list.InsertColumn(1,"起点",LVCFMT_CENTER,100);
	m_list.InsertColumn(2,"终点",LVCFMT_CENTER,100);
	m_list.InsertColumn(3,"发车时间",LVCFMT_CENTER,100);
	m_list.InsertColumn(4,"座位数",LVCFMT_CENTER,100);
	m_list.InsertColumn(5,"购票",LVCFMT_CENTER,100);

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	show();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CMainDlg::show()
{
	int num = read();
	m_list.DeleteAllItems();
	for(int i =0;i<num;i++)
	{
		m_list.InsertItem(i,0);
		CString str;
		m_list.SetItemText(i,0,train[i].id);
		m_list.SetItemText(i,1,train[i].begin);
		m_list.SetItemText(i,2,train[i].end);
		m_list.SetItemText(i,3,train[i].date);
		str.Format("%d",train[i].number);
		m_list.SetItemText(i,4,str);
		str.Format("%d",train[i].buy);
		m_list.SetItemText(i,5,str);
	}
}

int CMainDlg::read()
{
	int i=0;
	ifstream file;
	file.open("train.txt",ios::in);
	while(!file.eof())
	{
		file>>train[i].id>>train[i].begin>>train[i].end>>train[i].date>>train[i].number>>train[i].buy;
		i++;
	}
	i--;
	return i;
}

void CMainDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CString id,begin,end,date,number;
	GetDlgItem(IDC_EDIT1)->GetWindowText(id);
	GetDlgItem(IDC_EDIT2)->GetWindowText(begin);
	GetDlgItem(IDC_EDIT3)->GetWindowText(end);
	GetDlgItem(IDC_EDIT4)->GetWindowText(date);
	GetDlgItem(IDC_EDIT5)->GetWindowText(number);
	if(id==""||begin==""||end==""||date==""||number=="")
	{
		MessageBox("车次信息请完善");
		return;
	}
	int num = read();
	for(int i =0;i<num;i++)
	{
		if(strcmp(id,train[i].id)==0)
		{
			MessageBox("车次信息已存在，不能再添加了");
			return;
		}
	}

	ofstream file;
	file.open("train.txt",ios::app);
	file<<id.GetBuffer(0)<<"   "<<begin.GetBuffer(0)<<"   "<<end.GetBuffer(0)<<"  "<<date.GetBuffer(0)<<"    "<<atoi(number)<<"   "<<0<<endl;
	file.close();

	MessageBox("添加成功");
	show();
	
}

void CMainDlg::OnButton5() 
{
	int mark = m_list.GetSelectionMark();
	if(mark == -1)
	{
		MessageBox("请先选择需要删除的信息");
		return;
	}
	CString id = m_list.GetItemText(mark,0);

	int num = read();
	ofstream outfile;
	outfile.open("train.txt",ios::ate);
	for(int i=0;i<num;i++)
	{
		if(strcmp(id,train[i].id)==0)
		{
			continue;
		}
		outfile<<train[i].id<<"  "<<train[i].begin<<" "<<train[i].end<<"  "<<train[i].date<<"  "<<train[i].number<<"  "<<train[i].buy<<endl;
	}
	outfile.close();
	MessageBox("删除成功");
	show();	
}

void CMainDlg::OnButton6() 
{
	// TODO: Add your control notification handler code her
	CString id,begin;
	GetDlgItem(IDC_EDIT1)->GetWindowText(id);
	GetDlgItem(IDC_EDIT2)->GetWindowText(begin);
	if(id==""&&begin=="")
	{
		show();
		return ;
	}
	if(id!="")
	{
		m_list.DeleteAllItems();
		int a=0;
		for(int i =0;i<read();i++)
		{
			if(strcmp(id,train[i].id)==0)
			{
				m_list.InsertItem(a,0);
				CString str;
				m_list.SetItemText(a,0,train[i].id);
				m_list.SetItemText(a,1,train[i].begin);
				m_list.SetItemText(a,2,train[i].end);
				m_list.SetItemText(a,3,train[i].date);
				str.Format("%d",train[i].number);
				m_list.SetItemText(a,4,str);
				str.Format("%d",train[i].buy);
				m_list.SetItemText(a,5,str);
				a++;
			}
		}
		return;
	}

	if(begin!="")
	{
		m_list.DeleteAllItems();
		int a=0;
		for(int i =0;i<read();i++)
		{
			if(strcmp(begin,train[i].begin)==0)
			{
				m_list.InsertItem(a,0);
				CString str;
				m_list.SetItemText(a,0,train[i].id);
				m_list.SetItemText(a,1,train[i].begin);
				m_list.SetItemText(a,2,train[i].end);
				m_list.SetItemText(a,3,train[i].date);
				str.Format("%d",train[i].number);
				m_list.SetItemText(a,4,str);
				str.Format("%d",train[i].buy);
				m_list.SetItemText(a,5,str);
				a++;
			}
		}
		return;
	}



	
}

void CMainDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CString id,begin,end,date,number;
	GetDlgItem(IDC_EDIT1)->GetWindowText(id);
	GetDlgItem(IDC_EDIT2)->GetWindowText(begin);
	GetDlgItem(IDC_EDIT3)->GetWindowText(end);
	GetDlgItem(IDC_EDIT4)->GetWindowText(date);
	GetDlgItem(IDC_EDIT5)->GetWindowText(number);
	if(id==""||begin==""||end==""||date==""||number=="")
	{
		MessageBox("车次信息请完善");
		return;
	}

	int num = read();

	ofstream outfile;
	outfile.open("train.txt",ios::ate);
	for(int i=0;i<num;i++)
	{
		if(strcmp(id,train[i].id)==0)
		{
			strcpy(train[i].begin,begin);
			strcpy(train[i].end,end);
			strcpy(train[i].date,date);
			train[i].number=atoi(number);
		}
		outfile<<train[i].id<<"  "<<train[i].begin<<" "<<train[i].end<<"  "<<train[i].date<<"  "<<train[i].number<<"  "<<train[i].buy<<endl;
	}
	outfile.close();

	MessageBox("修改成功");
	show();
	
}

void CMainDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here

	int mark =m_list.GetSelectionMark();
	if(mark==-1)
	{
		MessageBox("请选择购买的车次");
		return;
	}
	CString id = m_list.GetItemText(mark,0);

	int num = read();

	ofstream outfile;
	outfile.open("train.txt",ios::ate);
	for(int i=0;i<num;i++)
	{
		if(strcmp(id,train[i].id)==0)
		{
			train[i].buy++;
		}
		outfile<<train[i].id<<"  "<<train[i].begin<<" "<<train[i].end<<"  "<<train[i].date<<"  "<<train[i].number<<"  "<<train[i].buy<<endl;
	}
	outfile.close();

	MessageBox("购票成功");
	show();
	
}

void CMainDlg::OnButton9() 
{
	int mark =m_list.GetSelectionMark();
	if(mark==-1)
	{
		MessageBox("请选择退票的车次");
		return;
	}
	CString id = m_list.GetItemText(mark,0);

	int num = read();
	mark =-1;
	ofstream outfile;
	outfile.open("train.txt",ios::ate);
	for(int i=0;i<num;i++)
	{
		if(strcmp(id,train[i].id)==0&&train[i].buy>0)
		{
			mark=0;
			train[i].buy--;
		}
		outfile<<train[i].id<<"  "<<train[i].begin<<" "<<train[i].end<<"  "<<train[i].date<<"  "<<train[i].number<<"  "<<train[i].buy<<endl;
	}
	outfile.close();

	if(mark ==-1)
	{
		MessageBox("退票失败");
		return;
	}

	MessageBox("退票成功");
	show();	
}

void CMainDlg::OnButton10() 
{
	// TODO: Add your control notification handler code here

	int mark =m_list.GetSelectionMark();
	if(mark==-1)
	{
		MessageBox("请选择退票的车次");
		return;
	}
	CString id = m_list.GetItemText(mark,0);

	int num = read();
	mark =-1;
	for(int i=0;i<num;i++)
	{
		if(strcmp(id,train[i].id)==0)
		{
			CString content;
			content.Format("购票数量:%d",train[i].buy);
			MessageBox(content);
			return;
		}
	}

	
}

void CMainDlg::OnButton11() 
{
	// TODO: Add your control notification handler code here
	
	int mark =m_list.GetSelectionMark();
	if(mark==-1)
	{
		MessageBox("请选择退票的车次");
		return;
	}
	CString id = m_list.GetItemText(mark,0);

	int num = read();
	mark =-1;
	for(int i=0;i<num;i++)
	{
		if(strcmp(id,train[i].id)==0)
		{
			CString content;
			content.Format("余票数量:%d",train[i].number-train[i].buy);
			MessageBox(content);
			return;
		}
	}
}

void CMainDlg::OnButton12() 
{
	// TODO: Add your control notification handler code here
	show();
	
}

void CMainDlg::OnButton13() 
{
	// TODO: Add your control notification handler code here
	MessageBox("导出成功");
	
}
