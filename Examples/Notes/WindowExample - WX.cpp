#include <wx/notebook.h>
#include <wx/wx.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    wxNotebook* notebook;
};

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("wxWidgets Sample");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200)) {
    notebook = new wxNotebook(this, wxID_ANY);

    // First tab
    wxPanel*    panel1 = new wxPanel(notebook, wxID_ANY);
    wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);

    wxStaticText* nameLabel = new wxStaticText(panel1, wxID_ANY, "Name:");
    wxTextCtrl*   nameText  = new wxTextCtrl(panel1, wxID_ANY);
    sizer1->Add(nameLabel, 0, wxEXPAND | wxALL, 5);
    sizer1->Add(nameText, 0, wxEXPAND | wxALL, 5);

    panel1->SetSizer(sizer1);
    notebook->AddPage(panel1, "Tab 1");

    // Second tab
    wxPanel*    panel2 = new wxPanel(notebook, wxID_ANY);
    wxBoxSizer* sizer2 = new wxBoxSizer(wxVERTICAL);

    wxButton* button = new wxButton(panel2, wxID_ANY, "Click me");
    sizer2->Add(button, 0, wxALIGN_CENTER | wxALL, 5);

    panel2->SetSizer(sizer2);
    notebook->AddPage(panel2, "Tab 2");
}

wxIMPLEMENT_APP(MyApp);
