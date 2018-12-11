#pragma once
#include <wx/wx.h>

class LightsPanel :
	public wxPanel
{
public:
	LightsPanel(wxPanel *parent, int id, unsigned char* aPattern, int width, int height);
	~LightsPanel();

	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);

	wxPanel *m_parent;
	unsigned char* pattern;

};

