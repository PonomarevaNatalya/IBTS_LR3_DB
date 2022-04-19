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
VirtualStringTree1->NodeDataSize =sizeof(Struct);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   VirtualStringTree1->Clear();
   VirtualStringTree1->BeginUpdate();

		 char* filename = "Databases.db";
		 AnsiString str="Select * from databases ;";
		 sqlite3 *datab;
		 sqlite3_stmt *pStmt;

		 if ( sqlite3_open(filename,&datab))
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

		while (true)
		{
			int resault = (sqlite3_step(pStmt));
			if (resault != SQLITE_ROW) {
			   break;
			}
			PVirtualNode entryNode = VirtualStringTree1->AddChild(VirtualStringTree1->RootNode);
			Struct *nodeData = (Struct*) VirtualStringTree1->GetNodeData(entryNode);
			int col = sqlite3_data_count(pStmt);

			for(int k=0; k<col; k++)
			{
			AnsiString otwet;
			otwet.printf("%s",sqlite3_column_text(pStmt, k));
				  switch (k) {
					case 0:
					  {
						  nodeData->id =otwet.ToInt();;
						  break;
					  }
					case 1:
					  {
						  nodeData->origin = UnicodeString(otwet);
						  break;
					  }
					case 2:
					  {
						  nodeData->name=  UnicodeString(otwet);
						  break;
					  }
					case 3:
					  {
						  nodeData->description= UnicodeString(otwet);
						  break;
					  }
					case 4:
					  {
						  nodeData->estimated_size=otwet.ToInt();
						  break;
					  }

				  }

			}

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
	  Struct *nodeData = (Struct*) VirtualStringTree1->GetNodeData(Node);

	  switch (Column) {
	  case 0:
	  {
		  CellText = (UnicodeString)nodeData->id;
		  break;
	  }
	  case 1:
	  {
		  CellText = nodeData->origin;
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
 Label3->Caption="";
}
//---------------------------------------------------------------------------



void __fastcall TForm1::VirtualStringTree1AddToSelection(TBaseVirtualTree *Sender,
          PVirtualNode Node)
{
if(Node == NULL) return;

		Struct *nodeData = (Struct*) VirtualStringTree1->GetNodeData(Node);
		Label1->Caption=nodeData->name;
		Label2->Caption=nodeData->description;
		Label3->Caption=nodeData->estimated_size;
}
//---------------------------------------------------------------------------


