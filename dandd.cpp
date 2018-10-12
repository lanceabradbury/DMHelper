#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include <wx/choicdlg.h>
#include <wx/numdlg.h>
#include <algorithm>

//compile: g++ dandd.cpp `wx-config --cxxflags --libs` -o dm
class players : public wxPanel
{
public:
	players(wxPanel *parent, wxString player, wxString health, wxString surges);
	
	wxStaticText *name;
    wxStaticText *initiative;
    wxStaticText *health;
    wxStaticText *health_value;
    wxStaticText *bloodied;
    wxStaticText *surges;
    wxStaticText *surges_value;
    wxStaticText *status;
    
    wxButton *damage;
    wxButton *status_effect;
    
    wxBoxSizer *hbox;
    wxBoxSizer *hbox2;
    wxBoxSizer *hbox3;
    wxBoxSizer *vbox;
};

struct initiatives
{
	wxString name;
	int initiative;
};

class init : public wxPanel
{
public:
	init(wxPanel *parent);
	
	wxStaticText *names[11];
	wxStaticText *inits[11];
	
	initiatives ini[11];
	
	int values[11];
    
    wxBoxSizer *hbox;
    wxBoxSizer *hbox2;
    wxBoxSizer *hbox3;
    wxBoxSizer *hbox4;
    wxBoxSizer *hbox5;
    wxBoxSizer *hbox6;
    wxBoxSizer *hbox7;
    wxBoxSizer *hbox8;
    wxBoxSizer *hbox9;
    wxBoxSizer *hbox10;
    wxBoxSizer *hbox11;
    wxBoxSizer *vbox;
};

class monsters : public wxPanel
{
public:
	monsters(wxPanel *parent, wxString type, wxString maxhp);
	void setName(wxString newName);
	void oneDam(wxCommandEvent & event);
	void fiveDam(wxCommandEvent & event);
	void showStatus(wxCommandEvent & event);
	void setNum(int num);
	void reDo();
	
	wxString *localname;
	bool isSetUp;
	int howMany;
	int maxHealth;
	int *healths;
	bool *alive;
	int initiative;
	int effect[9];
	
	wxStaticText *name;
    wxStaticText *health;
    wxStaticText *health_value[9];
    wxStaticText *bloodied[9];
    wxStaticText *status[9];
//	int stats[9][14];

	wxButton *stat_ef;
	wxButton *damage;
	wxButton *show_stat;

	wxBoxSizer *hbox;
	wxBoxSizer *hbox2;
	wxBoxSizer *hbox3;
	wxBoxSizer *hbox4;
	wxBoxSizer *hbox5;
	wxBoxSizer *hbox6;
	wxBoxSizer *hbox7;
	wxBoxSizer *hbox8;
	wxBoxSizer *hbox9;
	wxBoxSizer *hbox10;
	wxBoxSizer *hbox11;
	 
	wxBoxSizer *vbox;
};

class Communicate : public wxFrame
{
public:
    Communicate(const wxString& title);
    void onQuit(wxCommandEvent& event);
    void onSet(wxCommandEvent& event);
    void onSet2(wxCommandEvent& event);
    void onSet3(wxCommandEvent& event);
    void onSet4(wxCommandEvent& event);
    void onSet5(wxCommandEvent& event);
    void setInit(wxCommandEvent& event);

	players *player1;
	players *player2;
	players *player3;
	players *player4;
	players *player5;
	
	monsters *monster1;
	monsters *monster2;
	monsters *monster3;
	monsters *monster4;
	monsters *monster5;
	
	init *inits;
	
    wxPanel *m_parent;

	int *sortedOrder;
	wxString path;
	wxString path2;
	
	wxBoxSizer *hbox;
	wxBoxSizer *hbox2;
	 
	wxBoxSizer *vbox;
	
//	wxComboBox *popup;
	wxMenuBar *menubar;
	wxMenu *file;
	wxMenu *monstera;
	wxMenu *monsterb;
	wxMenu *monsterc;
	wxMenu *monsterd;
	wxMenu *monstere;
};



Communicate::Communicate(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 400))
{
	int ID_SET11 = 100;
	int ID_SET12 = 102;
	int ID_SET13 = 103;
	int ID_SET21 = 110;
	int ID_SET22 = 112;
	int ID_SET23 = 113;
	int ID_SET31 = 120;
	int ID_SET32 = 122;
	int ID_SET33 = 123;
	int ID_SET41 = 130;
	int ID_SET42 = 132;
	int ID_SET43 = 133;
	int ID_SET51 = 140;
	int ID_SET52 = 142;
	int ID_SET53 = 143;
	int ID_INIT = 150;
	menubar = new wxMenuBar;
	file = new wxMenu;
	
	menubar -> Append(file, wxT("&file"));
	SetMenuBar(menubar);
	

	monstera = new wxMenu;
	monstera->Append(ID_SET11, wxT("Set Up"));
	monstera->Append(ID_SET12, wxT("Change Initiative"));
	monstera->Append(ID_SET13, wxT("Status Effect"));
	
	monsterb = new wxMenu;
	monsterb->Append(ID_SET21, wxT("Set Up"));
	monsterb->Append(ID_SET22, wxT("Change Initiative"));
	monsterb->Append(ID_SET23, wxT("Status Effect"));
	
	monsterc = new wxMenu;
	monsterc->Append(ID_SET31, wxT("Set Up"));
	monsterc->Append(ID_SET32, wxT("Change Initiative"));
	monsterc->Append(ID_SET33, wxT("Status Effect"));
	
	monsterd = new wxMenu;
	monsterd->Append(ID_SET41, wxT("Set Up"));
	monsterd->Append(ID_SET42, wxT("Change Initiative"));
	monsterd->Append(ID_SET43, wxT("Status Effect"));
	
	monstere = new wxMenu;
	monstere->Append(ID_SET51, wxT("Set Up"));
	monstere->Append(ID_SET52, wxT("Change Initiative"));
	monstere->Append(ID_SET53, wxT("Status Effect"));

	file->AppendSubMenu(monstera, wxT("Monster A"));
	file->AppendSubMenu(monsterb, wxT("Monster B"));
	file->AppendSubMenu(monsterc, wxT("Monster C"));
	file->AppendSubMenu(monsterd, wxT("Monster D"));
	file->AppendSubMenu(monstere, wxT("Monster E"));
	file->Append(ID_INIT, wxT("Set Initiative"));
	file -> Append(wxID_EXIT, wxT("&Quit"));
	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Communicate::onQuit));
	Connect(ID_INIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Communicate::setInit));
	Connect(ID_SET11, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Communicate::onSet));
	Connect(ID_SET21, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Communicate::onSet2));
	Connect(ID_SET31, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Communicate::onSet3));
	Connect(ID_SET41, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Communicate::onSet4));
	Connect(ID_SET51, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Communicate::onSet5));

	m_parent = new wxPanel(this, wxID_ANY);
	player1 = new players(m_parent, wxT("Varrus"), wxT("80"), wxT("5"));
	player2 = new players(m_parent, wxT("Dannar"), wxT("100"), wxT("8"));
	player3 = new players(m_parent, wxT("Roswyn"), wxT("40"), wxT("3"));
	player4 = new players(m_parent, wxT("Kusha"), wxT("60"), wxT("5"));
	player5 = new players(m_parent, wxT("Tomoros"), wxT("50"), wxT("10"));

	monster1 = new monsters(m_parent, wxT("Monster A"), wxT("150"));
	monster2 = new monsters(m_parent, wxT("Monster B"), wxT("250"));
	monster3 = new monsters(m_parent, wxT("Monster C"), wxT("350"));
	monster4 = new monsters(m_parent, wxT("Monster D"), wxT("450"));
	monster5 = new monsters(m_parent, wxT("Monster E"), wxT("550"));

	inits = new init(m_parent);

	hbox = new wxBoxSizer(wxHORIZONTAL);
	hbox2 = new wxBoxSizer(wxHORIZONTAL);
	 
	vbox = new wxBoxSizer(wxVERTICAL);


	hbox->Add(player1, 1, wxEXPAND | wxALL, 5);
	hbox->Add(player2, 1, wxEXPAND | wxALL, 5);
	hbox->Add(player3, 1, wxEXPAND | wxALL, 5);
	hbox->Add(player4, 1, wxEXPAND | wxALL, 5);
	hbox->Add(player5, 1, wxEXPAND | wxALL, 5);
	hbox->Add(inits, 1, wxEXPAND | wxALL, 5);
	
	hbox2->Add(monster1, 1, wxEXPAND | wxALL, 5);
	hbox2->Add(monster2, 1, wxEXPAND | wxALL, 5);
	hbox2->Add(monster3, 1, wxEXPAND | wxALL, 5);
	hbox2->Add(monster4, 1, wxEXPAND | wxALL, 5);
	hbox2->Add(monster5, 1, wxEXPAND | wxALL, 5);
	
		 
	vbox->Add(hbox, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox2, 1, wxEXPAND | wxALL, 5);

	m_parent->SetSizer(vbox);
	this->Centre();

	Maximize();
}

void Communicate::onSet(wxCommandEvent& event)
{
	wxString input = wxGetTextFromUser(wxT("Monster Name"));
	monster1->setName(input);
	inits->ini[6].name = wxString(input);
	for(int i = 0; i < 9; i++)
	{
		monster1->bloodied[i]->SetLabel(wxT("     "));
	}
	while(inits->ini[6].name.Len() < 8)
	{
		inits->ini[6].name<<wxT(" ");
	}
	inits->names[6]->SetLabel(inits->ini[6].name);
	input = wxGetTextFromUser(wxT("Max Hp"));
	wxString *mx = new wxString(input);
	long temp = 0;
	input.ToLong(&temp);
	monster1->maxHealth = int(temp);
	input = wxGetTextFromUser(wxT("How many?"));
	input.ToLong(&temp);
	monster1->setNum(int(temp));
	for(int i = 0; i < int(temp); i++)
	{
		monster1->health_value[i]->SetLabel(*mx);
	}
	monster1->reDo();
	monster1->isSetUp = true;
}

void Communicate::onSet2(wxCommandEvent& event)
{
	wxString input = wxGetTextFromUser(wxT("Monster Name"));
	monster2->setName(input);
	inits->ini[7].name = wxString(input);
	for(int i = 0; i < 9; i++)
	{
		monster2->bloodied[i]->SetLabel(wxT("     "));
	}
	while(inits->ini[7].name.Len() < 8)
	{
		inits->ini[7].name<<wxT(" ");
	}
	inits->names[7]->SetLabel(inits->ini[7].name);
	input = wxGetTextFromUser(wxT("Max Hp"));
	wxString *mx = new wxString(input);
	long temp = 0;
	input.ToLong(&temp);
	monster2->maxHealth = int(temp);
	input = wxGetTextFromUser(wxT("How many?"));
	input.ToLong(&temp);
	monster2->setNum(int(temp));
	for(int i = 0; i < int(temp); i++)
	{
		monster2->health_value[i]->SetLabel(*mx);
	}
	monster2->reDo();
	monster2->isSetUp = true;
}

void Communicate::onSet3(wxCommandEvent& event)
{
	wxString input = wxGetTextFromUser(wxT("Monster Name"));
	monster3->setName(input);
	inits->ini[8].name = wxString(input);
	for(int i = 0; i < 9; i++)
	{
		monster3->bloodied[i]->SetLabel(wxT("     "));
	}
	while(inits->ini[8].name.Len() < 8)
	{
		inits->ini[8].name<<wxT(" ");
	}
	inits->names[8]->SetLabel(inits->ini[8].name);
	input = wxGetTextFromUser(wxT("Max Hp"));
	wxString *mx = new wxString(input);
	long temp = 0;
	input.ToLong(&temp);
	monster3->maxHealth = int(temp);
	input = wxGetTextFromUser(wxT("How many?"));
	input.ToLong(&temp);
	monster3->setNum(int(temp));
	for(int i = 0; i < int(temp); i++)
	{
		monster3->health_value[i]->SetLabel(*mx);
	}
	monster3->reDo();
	monster3->isSetUp = true;
}

void Communicate::onSet4(wxCommandEvent& event)
{
	wxString input = wxGetTextFromUser(wxT("Monster Name"));
	monster4->setName(input);
	inits->ini[9].name = wxString(input);
	for(int i = 0; i < 9; i++)
	{
		monster4->bloodied[i]->SetLabel(wxT("     "));
	}
	while(inits->ini[9].name.Len() < 8)
	{
		inits->ini[9].name<<wxT(" ");
	}
	inits->names[9]->SetLabel(inits->ini[9].name);
	input = wxGetTextFromUser(wxT("Max Hp"));
	wxString *mx = new wxString(input);
	long temp = 0;
	input.ToLong(&temp);
	monster4->maxHealth = int(temp);
	input = wxGetTextFromUser(wxT("How many?"));
	input.ToLong(&temp);
	monster4->setNum(int(temp));
	for(int i = 0; i < int(temp); i++)
	{
		monster4->health_value[i]->SetLabel(*mx);
	}
	monster4->reDo();
	monster4->isSetUp = true;
}

void Communicate::onSet5(wxCommandEvent& event)
{
	wxString input = wxGetTextFromUser(wxT("Monster Name"));
	monster5->setName(input);
	inits->ini[10].name = wxString(input);
	for(int i = 0; i < 9; i++)
	{
		monster5->bloodied[i]->SetLabel(wxT("     "));
	}
	while(inits->ini[10].name.Len() < 8)
	{
		inits->ini[10].name<<wxT(" ");
	}
	inits->names[10]->SetLabel(inits->ini[10].name);
	input = wxGetTextFromUser(wxT("Max Hp"));
	wxString *mx = new wxString(input);
	long temp = 0;
	input.ToLong(&temp);
	monster5->maxHealth = int(temp);
	input = wxGetTextFromUser(wxT("How many?"));
	input.ToLong(&temp);
	monster5->setNum(int(temp));
	for(int i = 0; i < int(temp); i++)
	{
		monster5->health_value[i]->SetLabel(*mx);
	}
	monster5->reDo();
	monster5->isSetUp = true;
}

void Communicate::setInit(wxCommandEvent& event)
{
	long in = wxGetNumberFromUser(wxT("Initiative"), inits->ini[0].name, wxT("Enter Initiative"), 0, 0, 1000);
	inits->ini[0].initiative = int(in);
	in = wxGetNumberFromUser(wxT("Initiative"), inits->ini[1].name, wxT("Enter Initiative"), 0, 0, 1000);
	inits->ini[1].initiative = int(in);
	in = wxGetNumberFromUser(wxT("Initiative"), inits->ini[2].name, wxT("Enter Initiative"), 0, 0, 1000);
	inits->ini[2].initiative = int(in);
	in = wxGetNumberFromUser(wxT("Initiative"), inits->ini[3].name, wxT("Enter Initiative"), 0, 0, 1000);
	inits->ini[3].initiative = int(in);
	in = wxGetNumberFromUser(wxT("Initiative"), inits->ini[4].name, wxT("Enter Initiative"), 0, 0, 1000);
	inits->ini[4].initiative = int(in);
	in = wxGetNumberFromUser(wxT("Initiative"), inits->ini[5].name, wxT("Enter Initiative"), 0, 0, 1000);
	inits->ini[5].initiative = int(in);
	if(monster1->isSetUp)
	{
		in = wxGetNumberFromUser(wxT("Initiative"), *(monster1->localname), wxT("Enter Initiative"), 0, 0, 1000);
		inits->ini[6].initiative = int(in);
		wxString temp;
		temp<<inits->ini[6].initiative;
		inits->inits[6]->SetLabel(temp);
	}
	if(monster2->isSetUp)
	{
		in = wxGetNumberFromUser(wxT("Initiative"), *(monster2->localname), wxT("Enter Initiative"), 0, 0, 1000);
		inits->ini[7].initiative = int(in);
		wxString temp;
		temp<<inits->ini[7].initiative;
		inits->inits[7]->SetLabel(temp);
	}
	if(monster3->isSetUp)
	{
		in = wxGetNumberFromUser(wxT("Initiative"), *(monster3->localname), wxT("Enter Initiative"), 0, 0, 1000);
		inits->ini[8].initiative = int(in);
		wxString temp;
		temp<<inits->ini[8].initiative;
		inits->inits[8]->SetLabel(temp);
	}
	if(monster4->isSetUp)
	{
		in = wxGetNumberFromUser(wxT("Initiative"), *(monster4->localname), wxT("Enter Initiative"), 0, 0, 1000);
		inits->ini[9].initiative = int(in);
		wxString temp;
		temp<<inits->ini[9].initiative;
		inits->inits[9]->SetLabel(temp);
	}
	if(monster5->isSetUp)
	{
		in = wxGetNumberFromUser(wxT("Initiative"), *(monster5->localname), wxT("Enter Initiative"), 0, 0, 1000);
		inits->ini[10].initiative = int(in);
		wxString temp;
		temp<<inits->ini[10].initiative;
		inits->inits[10]->SetLabel(temp);
	}
	for(int i = 0; i < 6; i++)
	{
		wxString temp;
		temp<<inits->values[i];
		inits->inits[i]->SetLabel(temp);
	}
//	std::sort(inits->ini[0], inits->ini[10]);
	int n = 10;
	bool swapped = true;
	while(swapped)
	{
		swapped = false;
		for(int i = 0; i < 10; i++)
		{
			if(inits->ini[i].initiative < inits->ini[i+1].initiative)
			{
				initiatives temp = inits->ini[i];
				inits->ini[i] = inits->ini[i+1];
				inits->ini[i+1] = temp;
				swapped = true;
			}
		}
		n = n - 1;
	}
	for(int i = 0; i < 10; i++)
	{
		if(inits->ini[i].initiative != -1)
		{
			inits->names[i]->SetLabel(inits->ini[i].name);
			wxString temp;
			temp<<inits->ini[i].initiative;
			inits->inits[i]->SetLabel(temp);
		}
	}
}

void Communicate::onQuit(wxCommandEvent& event)
{
	Close(true);
}

players::players(wxPanel * parent, wxString player, wxString maxhp, wxString numSurges) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(270, 150), wxBORDER_SUNKEN)
{
	hbox = new wxBoxSizer(wxHORIZONTAL);
	hbox2 = new wxBoxSizer(wxHORIZONTAL);
	hbox3 = new wxBoxSizer(wxHORIZONTAL);
	 
	vbox = new wxBoxSizer(wxVERTICAL);

	name = new wxStaticText(this, -1, player);
	health = new wxStaticText(this, -1, wxT("Max Health: "));
	health_value = new wxStaticText(this, -1, maxhp);
	surges = new wxStaticText(this, -1, wxT("Surges Left: "));
	surges_value = new wxStaticText(this, -1, numSurges);
	
	
	hbox->Add(name, 1, wxALL, 5);
//	hbox->AddStretchSpacer();
	hbox2->Add(health, 1, wxALL, 5);
	hbox2->Add(health_value, 1, wxALL, 5);
//	hbox->AddStretchSpacer();
	hbox3->Add(surges, 1, wxALL, 5);
	hbox3->Add(surges_value, 1, wxALL, 5);
	
	vbox->Add(hbox, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox2, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox3, 1, wxEXPAND | wxALL, 5);
	
	this->SetSizer(vbox);
}
const int ID_CH = 300;
const int ID_NEX = 301;
init::init(wxPanel * parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(270, 150), wxBORDER_SUNKEN)
{
	ini[0].name<<wxT("Dannar  ");
	ini[1].name<<wxT("Varrus  ");
	ini[2].name<<wxT("Kusha   ");
	ini[3].name<<wxT("Roswyn  ");
	ini[4].name<<wxT("Tomoros ");
	ini[5].name<<wxT("Nersera ");
	ini[6].name<<wxT("        ");
	ini[7].name<<wxT("        ");
	ini[8].name<<wxT("        ");
	ini[9].name<<wxT("        ");
	ini[10].name<<wxT("        ");
	names[0] = new wxStaticText(this, -1, wxT("Dannar  "));
	names[1] = new wxStaticText(this, -1, wxT("Varrus  "));
	names[2] = new wxStaticText(this, -1, wxT("Kusha   "));
	names[3] = new wxStaticText(this, -1, wxT("Roswyn  "));
	names[4] = new wxStaticText(this, -1, wxT("Tomoros "));
	names[5] = new wxStaticText(this, -1, wxT("Nersera "));
	names[6] = new wxStaticText(this, -1, wxT("        "));
	names[7] = new wxStaticText(this, -1, wxT("        "));
	names[8] = new wxStaticText(this, -1, wxT("        "));
	names[9] = new wxStaticText(this, -1, wxT("        "));
	names[10] = new wxStaticText(this, -1, wxT("        "));
	for(int i = 0; i < 11; i++)
	{
		inits[i] = new wxStaticText(this, -1, wxT(""));
		ini[i].initiative = -1;
	}
	
	
	hbox = new wxBoxSizer(wxHORIZONTAL);
	hbox2 = new wxBoxSizer(wxHORIZONTAL);
	hbox3 = new wxBoxSizer(wxHORIZONTAL);
	hbox4 = new wxBoxSizer(wxHORIZONTAL);
	hbox5 = new wxBoxSizer(wxHORIZONTAL);
	hbox6 = new wxBoxSizer(wxHORIZONTAL);
	hbox7 = new wxBoxSizer(wxHORIZONTAL);
	hbox8 = new wxBoxSizer(wxHORIZONTAL);
	hbox9 = new wxBoxSizer(wxHORIZONTAL);
	hbox10 = new wxBoxSizer(wxHORIZONTAL);
	hbox11 = new wxBoxSizer(wxHORIZONTAL);
	 
	vbox = new wxBoxSizer(wxVERTICAL);
	
	hbox->Add(names[0], 1, wxALL, 5);
	hbox->Add(inits[0], 1, wxALL, 5);

	hbox2->Add(names[1], 1, wxALL, 5);
	hbox2->Add(inits[1], 1, wxALL, 5);
	
	hbox3->Add(names[2], 1, wxALL, 5);
	hbox3->Add(inits[2], 1, wxALL, 5);
	
	hbox4->Add(names[3], 1, wxALL, 5);
	hbox4->Add(inits[3], 1, wxALL, 5);
	
	hbox5->Add(names[4], 1, wxALL, 5);
	hbox5->Add(inits[4], 1, wxALL, 5);
	
	hbox6->Add(names[5], 1, wxALL, 5);
	hbox6->Add(inits[5], 1, wxALL, 5);
	
	hbox7->Add(names[6], 1, wxALL, 5);
	hbox7->Add(inits[6], 1, wxALL, 5);
	
	hbox8->Add(names[7], 1, wxALL, 5);
	hbox8->Add(inits[7], 1, wxALL, 5);
	
	hbox9->Add(names[8], 1, wxALL, 5);
	hbox9->Add(inits[8], 1, wxALL, 5);
	
	hbox10->Add(names[9], 1, wxALL, 5);
	hbox10->Add(inits[9], 1, wxALL, 5);

	hbox11->Add(names[10], 1, wxALL, 5);
	hbox11->Add(inits[10], 1, wxALL, 5);

	
	vbox->Add(hbox, 1, wxALL, 5);
	vbox->Add(hbox2, 1, wxALL, 5);
	vbox->Add(hbox3, 1, wxALL, 5);
	vbox->Add(hbox4, 1, wxALL, 5);
	vbox->Add(hbox5, 1, wxALL, 5);
	vbox->Add(hbox6, 1, wxALL, 5);
	vbox->Add(hbox7, 1, wxALL, 5);
	vbox->Add(hbox8, 1, wxALL, 5);
	vbox->Add(hbox9, 1, wxALL, 5);
	vbox->Add(hbox10, 1, wxALL, 5);
	vbox->Add(hbox11, 1, wxALL, 5);

	
	this->SetSizer(vbox);
}

const int ID_M = 200;
const int ID_FIVE = 201;
const int ID_ONE = 202;
const int ID_STAT = 203;
monsters::monsters(wxPanel * parent, wxString type, wxString maxhp) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(270, 150), wxBORDER_SUNKEN)
{
	howMany = 1;
	setNum(1);
	localname = new wxString(wxT("monster a:"));
	hbox = new wxBoxSizer(wxHORIZONTAL);
	hbox2 = new wxBoxSizer(wxHORIZONTAL);
	hbox3 = new wxBoxSizer(wxHORIZONTAL);
	hbox4 = new wxBoxSizer(wxHORIZONTAL);
	hbox5 = new wxBoxSizer(wxHORIZONTAL);
	hbox6 = new wxBoxSizer(wxHORIZONTAL);
	hbox7 = new wxBoxSizer(wxHORIZONTAL);
	hbox8 = new wxBoxSizer(wxHORIZONTAL);
	hbox9 = new wxBoxSizer(wxHORIZONTAL);
	hbox10 = new wxBoxSizer(wxHORIZONTAL);
	hbox11 = new wxBoxSizer(wxHORIZONTAL);
	 
	vbox = new wxBoxSizer(wxVERTICAL);
	
	name = new wxStaticText(this, -1, type);
	health = new wxStaticText(this, -1, wxT("Health: "));

	for(int i = 0; i < 9; i++)
	{
		wxStaticText *tmp = new wxStaticText(this, -1, wxT(""));
		health_value[i] = tmp;
	}
	
	for(int i = 0; i < 9; i++)
	{
		effect[i] = 0;
	}
	
/*	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 14; j++)
		{
			stats[i][j] = 0;
		}
	}*/
	for(int i = 0; i < 9; i++)
	{
		wxStaticText *tmp = new wxStaticText(this, -1, wxT("              "));
		status[i] = tmp;
//		delete tmp;
		tmp = new wxStaticText(this, -1, wxT("     "));
		bloodied[i] = tmp;
	}

//	edit = new wxButton(this, ID_M, wxT("Edit"));
//	Connect(ID_M, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(monsters::onClick));

	damage = new wxButton(this, ID_ONE, wxT("Damage"));
	stat_ef = new wxButton(this, ID_FIVE, wxT("Apply Stat"));
	show_stat = new wxButton(this, ID_STAT, wxT("Remove Stat"));
	Connect(ID_ONE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(monsters::oneDam));
	Connect(ID_FIVE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(monsters::fiveDam));
	Connect(ID_STAT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(monsters::showStatus));

	hbox->Add(name, 1, wxALL, 5);

	hbox2->Add(health, 1, wxALL, 5);
	hbox2->Add(health_value[0], 1, wxALL, 5);
	hbox2->Add(bloodied[0], 1, wxALL, 5);
	hbox2->Add(status[0], 1, wxALL, 5);

	hbox3->Add(health_value[1], 1, wxALL, 5);
	hbox3->Add(bloodied[1], 1, wxALL, 5);
	hbox3->Add(status[1], 1, wxALL, 5);

	hbox4->Add(health_value[2], 1, wxALL, 5);
	hbox4->Add(bloodied[2], 1, wxALL, 5);
	hbox4->Add(status[2], 1, wxALL, 5);

	hbox5->Add(health_value[3], 1, wxALL, 5);
	hbox5->Add(bloodied[3], 1, wxALL, 5);
	hbox5->Add(status[3], 1, wxALL, 5);

	hbox6->Add(health_value[4], 1, wxALL, 5);
	hbox6->Add(bloodied[4], 1, wxALL, 5);
	hbox6->Add(status[4], 1, wxALL, 5);
	
	hbox7->Add(health_value[5], 1, wxALL, 5);
	hbox7->Add(bloodied[5], 1, wxALL, 5);
	hbox7->Add(status[5], 1, wxALL, 5);
	
	hbox8->Add(health_value[6], 1, wxALL, 5);
	hbox8->Add(bloodied[6], 1, wxALL, 5);
	hbox8->Add(status[6], 1, wxALL, 5);
	
	hbox9->Add(health_value[7], 1, wxALL, 5);
	hbox9->Add(bloodied[7], 1, wxALL, 5);
	hbox9->Add(status[7], 1, wxALL, 5);
	
	hbox10->Add(health_value[8], 1, wxALL, 5);
	hbox10->Add(bloodied[8], 1, wxALL, 5);
	hbox10->Add(status[8], 1, wxALL, 5);

	hbox11->Add(damage, 1, wxALL, 5);
	hbox11->Add(stat_ef, 1, wxALL, 5);
	hbox11->Add(show_stat, 1, wxALL, 5);
	
	vbox->Add(hbox, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox2, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox3, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox4, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox5, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox6, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox7, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox8, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox9, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox10, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox11, 1, wxEXPAND | wxALL, 5);
	
	this->SetSizer(vbox);
	reDo();
}

void monsters::setName(wxString newName)
{
	delete localname;
	localname = new wxString(newName);
	name->SetLabel(*localname);
}


//damage
void monsters::oneDam(wxCommandEvent & event)
{
	wxString choices[howMany];
	for(int i = 1; i <= howMany; i++)
	{
		wxString temp;
		temp << i;
		choices[i - 1] = temp;
	}
	wxArrayInt *selections;
	selections = new wxArrayInt();
	selections->Alloc(howMany);
	long dam = wxGetNumberFromUser(wxT("Amount of Damage"), wxT("prompt"), wxT("Damage"), 0, -1000, 1000);
	int dmg = int(dam);
	if(howMany > 1)
	{
		wxGetMultipleChoices(*selections, wxT("Select Hurt"), wxT("Damage"), howMany, choices);
		for(int i = 0; i < selections->GetCount(); i++)
		{
			switch(selections->Item(i))
			{
				case 0:
				{
					healths[0] -= dmg;
					wxString tmp;
					tmp << healths[0];
					health_value[0]->SetLabel(tmp);
					if(healths[0] <= maxHealth / 2)
					{
						bloodied[0]->SetLabel(wxT("Blood"));
						bloodied[0]->SetForegroundColour((255, 255, 255));
					}
					break;
				}
				case 1:
				{
					wxString tmp;
					healths[1] -= dmg;
					tmp << healths[1];
					health_value[1]->SetLabel(tmp);
					if(healths[1] <= maxHealth / 2)
					{
						bloodied[1]->SetLabel(wxT("Blood"));
						bloodied[1]->SetForegroundColour((255, 255, 255));
					}
					break;
				}
				case 2:
				{
					wxString tmp;
					healths[2] -= dmg;
					tmp << healths[2];
					health_value[2]->SetLabel(tmp);
					if(healths[2] <= maxHealth / 2)
					{
						bloodied[2]->SetLabel(wxT("Blood"));
						bloodied[2]->SetForegroundColour((255, 255, 255));
					}
					break;
				}
				case 3:
				{
					wxString tmp;
					healths[3] -= dmg;
					tmp << healths[3];
					health_value[3]->SetLabel(tmp);
					if(healths[3] <= maxHealth / 2)
					{
						bloodied[3]->SetLabel(wxT("Blood"));
						bloodied[3]->SetForegroundColour((255, 255, 255));
					}
					break;
				}
				case 4:
				{
					wxString tmp;
					healths[4] -= dmg;
					tmp << healths[4];
					health_value[4]->SetLabel(tmp);
					if(healths[4] <= maxHealth / 2)
					{
						bloodied[4]->SetLabel(wxT("Blood"));
						bloodied[4]->SetForegroundColour((255, 255, 255));
					}
					break;
				}
				case 5:
				{
					wxString tmp;
					healths[5] -= dmg;
					tmp << healths[5];
					health_value[5]->SetLabel(tmp);
					if(healths[5] <= maxHealth / 2)
					{
						bloodied[5]->SetLabel(wxT("Blood"));
						bloodied[5]->SetForegroundColour((255, 255, 255));
					}
					break;
				}
				case 6:
				{
					wxString tmp;
					healths[6] -= dmg;
					tmp << healths[6];
					health_value[6]->SetLabel(tmp);
					if(healths[6] <= maxHealth / 2)
					{
						bloodied[6]->SetLabel(wxT("Blood"));
						bloodied[6]->SetForegroundColour((255, 255, 255));
					}
					break;
				}
				case 7:
				{
					wxString tmp;
					healths[7] -= dmg;
					tmp << healths[7];
					health_value[7]->SetLabel(tmp);
					if(healths[7] <= maxHealth / 2)
					{
						bloodied[7]->SetLabel(wxT("Blood"));
						bloodied[7]->SetForegroundColour((255, 255, 255));
					}
					break;
				}
				case 8:
				{
					wxString tmp;
					healths[8] -= dmg;
					tmp << healths[8];
					health_value[8]->SetLabel(tmp);
					if(healths[8] <= maxHealth / 2)
					{
						bloodied[8]->SetLabel(wxT("Blood"));
						bloodied[8]->SetForegroundColour((255, 255, 255));
					}
					break;
				}
				default:
					wxString tmp;
					break;
			}
		}
	}
	else
	{
		healths[0] -= dmg;
		wxString tmp;
		tmp << healths[0];
		health_value[0]->SetLabel(tmp);
		if(healths[0] <= maxHealth / 2)
		{
			bloodied[0]->SetLabel(wxT("Blood"));
			bloodied[0]->SetForegroundColour((255, 255, 255));
		}
	}
}

//status effects
void monsters::fiveDam(wxCommandEvent & event)
{
/*	wxString choices[2];
	choices[0] = wxT("Apply");
	choices[1] = wxT("Remove");
	wxArrayInt *selections;
	selections = new wxArrayInt();
	selections->Alloc(2);
	wxGetMultipleChoices(*selections, wxT("Status Effects"), wxT("Effects"), 2, choices);

/*	choices[2] = wxT("Blinded");
	choices[3] = wxT("Dazed");
	choices[4] = wxT("Deafened");
	choices[5] = wxT("Dominated");
	choices[6] = wxT("Helpless");
	choices[7] = wxT("Immobilized");
	choices[8] = wxT("Marked");
	choices[9] = wxT("Petrified");
	choices[10] = wxT("Prone");
	choices[11] = wxT("Restrained");
	choices[12] = wxT("Slowed");
	choices[13] = wxT("Stunned");
	choices[14] = wxT("Surprised");;
	choices[15] = wxT("Weakened");
	if(selections->Item(0) != 0 && selections->Item(0) != 1)
	{
		while(selections->Item(0) != 0 && selections->Item(0) != 1)
		{
			delete selections;
			selections = new wxArrayInt();
			selections->Alloc(16);
			wxGetMultipleChoices(*selections, wxT("Select Apply or Remove"), wxT("Status Effects"), 16, choices);
		}
	}
	if(selections->Item(0) == 0 && selections->Item(1) == 1)
	{
		delete selections;
			selections = new wxArrayInt();
			selections->Alloc(16);
			wxGetMultipleChoices(*selections, wxT("Select Either Apply or Remove"), wxT("Status Effects"), 16, choices);
	}*/
	wxString choices2[howMany];
	for(int i = 1; i <= howMany; i++)
	{
		wxString temp;
		temp << i;
		choices2[i - 1] = temp;
	}
	wxArrayInt *selections2;
	selections2 = new wxArrayInt();
	selections2->Alloc(howMany);
	if(howMany > 1)
	{
		wxGetMultipleChoices(*selections2, wxT("Select Monsters Affected"), wxT("Affectees"), howMany, choices2);

		for(int i = 0; i < selections2->GetCount(); i++)
		{
			wxString st(wxT("Status Effect"));
			status[selections2->Item(i)]->SetLabel(st);
			effect[selections2->Item(i)] = 1;
		}
	}
	else
	{
		wxString st(wxT("Status Effect"));
		status[0]->SetLabel(st);
		effect[0] = 1;
	}
/*		for(int i = 0; i < selections->GetCount(); i++)
		{
			switch(selections->Item(i))
			{
				case 2:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][0] = 1;
					}
					break;
				case 3:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][1] = 1;
					}
					break;
				case 4:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][2] = 1;
					}
					break;
				case 5:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][3] = 1;
					}
					break;
				case 6:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][4] = 1;
					}
					break;
				case 7:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][5] = 1;
					}
					break;
				case 8:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][6] = 1;
					}
					break;
				case 9:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][7] = 1;
					}
					break;
				case 10:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][8] = 1;
					}
					break;
				case 11:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][9] = 1;
					}
					break;
				case 12:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][10] = 1;
					}
					break;
				case 13:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][11] = 1;
					}
					break;
				case 14:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][12] = 1;
					}
					break;
				case 15:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][13] = 1;
					}
					break;
			}
		}
	}
	else
	{
		
		effect[selections2->Item(i)] = 1;
		/*for(int i = 0; i < selections->GetCount(); i++)
		{
			switch(selections->Item(i))
			{
				case 2:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][0] = 0;
					}
					break;
				case 3:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][1] = 0;
					}
					break;
				case 4:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][2] = 0;
					}
					break;
				case 5:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][3] = 0;
					}
					break;
				case 6:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][4] = 0;
					}
					break;
				case 7:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][5] = 0;
					}
					break;
				case 8:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][6] = 0;
					}
					break;
				case 9:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][7] = 0;
					}
					break;
				case 10:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][8] = 0;
					}
					break;
				case 11:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][9] = 0;
					}
					break;
				case 12:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][10] = 0;
					}
					break;
				case 13:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][11] = 0;
					}
					break;
				case 14:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][12] = 0;
					}
					break;
				case 15:
					for(int j = 0; j < selections2->GetCount(); j++)
					{
						stats[selections2->Item(j)][13] = 0;
					}
					break;
			}
		}*/
/*		for(int i = 0; i < selections2->GetCount(); i++)
		{
			bool hasEffect = false;
			for(int j = 0; j < 14; j++)
			{
				if(stats[selections2->Item(i)][j])
				{
					hasEffect = true;
					break;
				}
			}
			if(!hasEffect)
			{
				wxString st(wxT(""));
				status[selections2->Item(i)]->SetLabel(st);
			}
		}
	}*/
}

void monsters::showStatus(wxCommandEvent & event)
{
	if(howMany > 1)
	{
		wxString choices2[howMany];
		for(int i = 1; i <= howMany; i++)
		{
			wxString temp;
			temp << i;
			choices2[i - 1] = temp;
		}
		wxArrayInt *selections2;
		selections2 = new wxArrayInt();
		selections2->Alloc(howMany);
		wxGetMultipleChoices(*selections2, wxT("Select Monsters Affected"), wxT("Affectees"), howMany, choices2);
		for(int i = 0; i < selections2->GetCount(); i++)
		{
			wxString st(wxT(""));
			status[selections2->Item(i)]->SetLabel(st);
			effect[selections2->Item(i)] = 0;
		}
	}
	else
	{
		wxString st(wxT(""));
		status[0]->SetLabel(st);
		effect[0] = 0;
	}
/*	wxString toPrint;
	for(int i = 0; i < 9; i++)
	{
		bool hasStat = false;
		if(stats[i][0])
		{
			toPrint<<*localname<<(i + 1)<<wxT(": blinded");
			hasStat = true;
		}
		if(stats[i][1])
		{
			if(hasStat)
			{
				toPrint<<wxT(" dazed");
			}
			else
			{
				toPrint<<*localname<<(i + 1)<<wxT(": dazed");
				hasStat = true;
			}
		}
		if(stats[i][2])
		{
			if(hasStat)
			{
				toPrint<<wxT(" deafened");
			}
			else
			{
				toPrint<<*localname<<(i + 1)<<wxT(": deafened");
				hasStat = true;
			}
		}
		if(stats[i][3])
		{
			if(hasStat)
			{
				toPrint<<wxT(" dominated");
			}
			else
			{
				toPrint<<*localname<<(i + 1)<<wxT(": dominated");
				hasStat = true;
			}
		}
		if(stats[i][4])
		{
			if(hasStat)
			{
				toPrint<<wxT(" helpless");
			}
			else
			{
				toPrint<<*localname<<(i + 1)<<wxT(": helpless");
				hasStat = true;
			}
		}
		if(stats[i][5])
		{
			if(hasStat)
			{
				toPrint<<wxT(" immobilized");
			}
			else
			{
				toPrint<<*localname<<(i + 1)<<wxT(": immobilized");
				hasStat = true;
			}
		}
		if(stats[i][6])
		{
			if(hasStat)
			{
				toPrint<<wxT(" marked");
			}
			else
			{
				toPrint<<*localname<<(i + 1)<<wxT(": marked");
				hasStat = true;
			}
		}
		if(stats[i][7])
		{
			if(hasStat)
			{
				toPrint<<wxT(" petrified");
			}
			else
			{
				toPrint<<*localname<<(i + 1)<<wxT(": petrified");
				hasStat = true;
			}
		}
		if(stats[i][8])
		{
			if(hasStat)
			{
				toPrint<<wxT(" prone");
			}
			else
			{
				toPrint<<*localname<<(i + 1)<<wxT(": prone");
				hasStat = true;
			}
		}
		if(stats[i][9])
		{
			if(hasStat)
			{
				toPrint<<wxT(" restrained");
			}
			else
			{
				toPrint<<*localname<<(i + 1)<<wxT(": restrained");
				hasStat = true;
			}
		}
		if(stats[i][10])
		{
			if(hasStat)
			{
				toPrint<<wxT(" slowed");
			}
			else
			{
				toPrint<<*localname<<(i + 1)<<wxT(": slowed");
				hasStat = true;
			}
		}
		if(stats[i][11])
		{
			if(hasStat)
			{
				toPrint<<wxT(" stunned");
			}
			else
			{
				toPrint<<*localname<<(i + 1)<<wxT(": stunned");
				hasStat = true;
			}
		}
		if(stats[i][12])
		{
			if(hasStat)
			{
				toPrint<<wxT(" surprised");
			}
			else
			{
				toPrint<<*localname<<(i + 1)<<wxT(": surprised");
				hasStat = true;
			}
		}
		if(stats[i][13])
		{
			if(hasStat)
			{
				toPrint<<wxT(" weakened");
			}
			else
			{
				toPrint<<*localname<<(i + 1)<<wxT(": weakened");
				hasStat = true;
			}
		}
		toPrint<<wxT("\n");
	}
	wxMessageDialog *dial = new wxMessageDialog(GetParent(), toPrint, wxT("Image Info"), wxOK);
	dial->ShowModal();*/
}

void monsters::setNum(int num)
{
	if(num > 9)
		howMany = 9;
	else
		howMany = num;

	delete healths;
	healths = new int[howMany];
	for(int i = 0; i < howMany; i++)
	{
		healths[i] = maxHealth;
	}
	delete alive;
	alive = new bool[howMany];
	for(int i = 0; i < howMany; i++)
	{
		alive[i] = true;
	}
}

void monsters::reDo()
{
	wxString hp;
	hp<<maxHealth;
	wxString non = wxT("");
	for(int i = 0; i < 9; i++)
	{
		status[i]->SetLabel(wxT("              "));
	}
	for(int i = 0; i < howMany; i++)
	{
		health_value[i]->SetLabel(hp);
	}
	for(int i = howMany; i < 9; i++)
	{
		health_value[i]->SetLabel(non);
	}
}

class MyApp : public wxApp
{
	public:
		virtual bool OnInit();
};

bool MyApp::OnInit()
{
	wxInitAllImageHandlers();
	
    Communicate *communicate = new Communicate(wxT("My Dungeon"));
    communicate->Show(true);

    return true;
}

IMPLEMENT_APP(MyApp)
