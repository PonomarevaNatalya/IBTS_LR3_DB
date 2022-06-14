//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "sqlite3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
VirtualStringTree1->NodeDataSize =sizeof(Struct);  // задаем размер-структуру
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   VirtualStringTree1->Clear();
   VirtualStringTree1->BeginUpdate();

		 char* filename = "load_statistics.db";
		 AnsiString str="Select * from load_statistics ;";
		 sqlite3 *datab;
		 sqlite3_stmt *pStmt;
		 //const char *errmsg;

		if (sqlite3_open(filename,&datab))
			{
		ShowMessage("Can't open database: " + (String)sqlite3_errmsg(datab));
		sqlite3_close(datab);
		return;
			}
		if (sqlite3_prepare_v2(datab, str.c_str(), -1, &pStmt, NULL))
		{
			sqlite3_finalize(pStmt);
			sqlite3_close(datab);
		}

		while (sqlite3_step(pStmt) == SQLITE_ROW)
		{
			PVirtualNode entryNode = VirtualStringTree1->AddChild(VirtualStringTree1->RootNode);
			Struct *nodeData = (Struct*) VirtualStringTree1->GetNodeData(entryNode);

			nodeData->top_level_hostname =(char *)sqlite3_column_text(pStmt, 0);
			nodeData->resource_hostname =(char *)sqlite3_column_text(pStmt, 1);
			nodeData->resource_url_hash=(char *)sqlite3_column_text(pStmt, 2);
			nodeData->resource_type=StrToInt((char *)sqlite3_column_text(pStmt, 3));
			nodeData->last_update=(char *)sqlite3_column_text(pStmt, 4);
		 }



	sqlite3_finalize(pStmt);
	sqlite3_close(datab);
 VirtualStringTree1->EndUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
if(Node == NULL) return;
	  Struct *nodeData = (Struct*) VirtualStringTree1->GetNodeData(Node);  // было в лекции, преобразует в норм текст

	  switch (Column) {
	  case 0:
	  {
		  CellText =nodeData->top_level_hostname;
		  break;
	  }
	  case 1:
	  {
		  CellText =nodeData->resource_hostname;
		  break;
	  }
	  case 2:
	  {
		  CellText = nodeData->resource_type;
		  break;
	  }

	 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
 VirtualStringTree1->Clear();
 Label1->Caption="";
 Label2->Caption="";
 }
//---------------------------------------------------------------------------



void __fastcall TForm1::VirtualStringTree1AddToSelection(TBaseVirtualTree *Sender,
		  PVirtualNode Node)
{
if(Node == NULL) return;

		Struct *nodeData = (Struct*) VirtualStringTree1->GetNodeData(Node);
		Label1->Caption=nodeData->resource_url_hash;
		Label2->Caption=nodeData->last_update;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender)
{
 sqlite3* datab;
   char* filename="load_statistics.db";
   PVirtualNode choiseStr=VirtualStringTree1->GetFirstSelected(); // берем то, что выделено
   if(choiseStr==NULL) return;

Struct *nodeData=(Struct*)VirtualStringTree1->GetNodeData(choiseStr);
AnsiString str="Delete from load_statistics where last_update = "+nodeData->last_update+" ;";

   sqlite3_stmt *pStmt;
   char* errmsg;

if(sqlite3_open( filename,&datab ))
{
	sqlite3_close(datab);
}

int result=sqlite3_prepare_v2(datab,str.c_str(),-1,&pStmt,NULL);
if(result!=SQLITE_OK)
{
	errmsg=(char*)sqlite3_errmsg(datab);
	sqlite3_close(datab);
	return;
}

result=sqlite3_step(pStmt);
if(result!=SQLITE_DONE)
{
	sqlite3_finalize(pStmt);
	sqlite3_close(datab);
	return;
}
sqlite3_finalize(pStmt);
sqlite3_close(datab);
Button1Click(Sender);
Label1->Caption="";
Label2->Caption="";

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
    sqlite3* datab;
   char* filename="load_statistics.db";
   AnsiString str="Delete from load_statistics ;";
   sqlite3_stmt *pStmt;
   char* errmsg;

if(sqlite3_open( filename,&datab ))
{
	sqlite3_close(datab);
}

int result=sqlite3_prepare_v2(datab,str.c_str(),-1,&pStmt,NULL);
if(result!=SQLITE_OK)
{
	errmsg=(char*)sqlite3_errmsg(datab);
	sqlite3_close(datab);
	return;
}

result=sqlite3_step(pStmt);
if(result!=SQLITE_DONE)
{
	sqlite3_finalize(pStmt);
	sqlite3_close(datab);
	return;
}
	sqlite3_finalize(pStmt);
	sqlite3_close(datab);
	Button1Click(Sender);
	Label1->Caption="";
	Label2->Caption="";
}
//---------------------------------------------------------------------------

