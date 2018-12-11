#include "LightsPanel.h"

#define LUC_NUM_CHANNELS	9

// light positions (x, y)
//  	0		1	2	3		4
//  0				O
//  
//  1				O
//  2	O		O	O	O		O
//  3				O
//  
//  4				O
const wxPoint lightPos[LUC_NUM_CHANNELS] = { 
	wxPoint(2, 2),		// halogen bulb
	wxPoint(2, 0), wxPoint(0, 2), wxPoint(2, 4), wxPoint(4, 2),		// outer ring
	wxPoint(2, 1), wxPoint(1, 2), wxPoint(2, 3), wxPoint(3, 2)		// inner ring
};

LightsPanel::LightsPanel(wxPanel *parent, int id, unsigned char* aPattern, int width, int height)
	: wxPanel(parent, id, wxPoint(-1, -1), wxSize(width, height))
{
	m_parent = parent;
	pattern = aPattern;

	Connect(wxEVT_PAINT, wxPaintEventHandler(LightsPanel::OnPaint));
	Connect(wxEVT_SIZE, wxSizeEventHandler(LightsPanel::OnSize));
}


LightsPanel::~LightsPanel()
{
}

void LightsPanel::OnPaint(wxPaintEvent & event)
{
	wxFont font(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
		wxFONTWEIGHT_NORMAL, false, wxT("Courier 10 Pitch"));

	wxPaintDC dc(this);
	dc.SetFont(font);
	wxSize size = GetSize();
	size.DecBy(1, 1);
	int widthUnit = size.GetWidth() / 10;
	int xPositions[5] = { widthUnit, widthUnit * 3, widthUnit * 5, widthUnit * 7, widthUnit * 9};
	int heightUnit = size.GetHeight() / 10;
	int yPositions[5] = { heightUnit, heightUnit * 3, heightUnit * 5, heightUnit * 7, heightUnit * 9 };

	// draw background
	wxColor colBackground = wxColor(100, 100, 100);
	dc.SetBrush(wxBrush(colBackground));
	dc.DrawEllipse(wxPoint(0, 0), size);

	// draw lights
	wxColor colDefault = wxColor(255, 255, 255);
	dc.SetBrush(wxBrush(colDefault));
	for (int i = 0; i < LUC_NUM_CHANNELS; i++) {
		int size = (i == 0 ? 80 : 20);
		// channel 0 is yellow, other channels are white
		wxColor color(pattern[i], pattern[i], (i == 0 ? 0 : pattern[i]));
		dc.SetBrush(wxBrush(color));
		dc.DrawEllipse(xPositions[lightPos[i].x] - size / 2, yPositions[lightPos[i].y] - size / 2, size, size);
	}
	

//	dc.DrawText(wxT("Lucinda"), 10, 10);
}

void LightsPanel::OnSize(wxSizeEvent& event)
{
	Refresh();
}