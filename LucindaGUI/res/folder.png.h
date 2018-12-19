#ifndef FOLDER_PNG_H
#define FOLDER_PNG_H

#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

static const unsigned char folder_png[] =
{
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 
	0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 
	0x00, 0x00, 0x00, 0x10, 0x08, 0x06, 0x00, 0x00, 0x00, 0x1F, 
	0xF3, 0xFF, 0x61, 0x00, 0x00, 0x00, 0x04, 0x67, 0x41, 0x4D, 
	0x41, 0x00, 0x00, 0xAF, 0xC8, 0x37, 0x05, 0x8A, 0xE9, 0x00, 
	0x00, 0x00, 0x19, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6F, 0x66, 
	0x74, 0x77, 0x61, 0x72, 0x65, 0x00, 0x41, 0x64, 0x6F, 0x62, 
	0x65, 0x20, 0x49, 0x6D, 0x61, 0x67, 0x65, 0x52, 0x65, 0x61, 
	0x64, 0x79, 0x71, 0xC9, 0x65, 0x3C, 0x00, 0x00, 0x01, 0xAB, 
	0x49, 0x44, 0x41, 0x54, 0x38, 0xCB, 0xC5, 0x93, 0xBB, 0x8A, 
	0x14, 0x41, 0x14, 0x86, 0xBF, 0xEA, 0xED, 0x19, 0x5B, 0xB1, 
	0x87, 0x05, 0x45, 0x74, 0x51, 0x04, 0x13, 0x67, 0x37, 0x77, 
	0x41, 0xD8, 0x4C, 0x43, 0x13, 0x9F, 0xC0, 0xC4, 0x57, 0x10, 
	0x03, 0x41, 0x30, 0xD4, 0x17, 0xD0, 0xCC, 0xC0, 0xCC, 0x50, 
	0x30, 0x13, 0x31, 0xF0, 0x01, 0x16, 0xCD, 0x14, 0x37, 0x70, 
	0x11, 0xDD, 0xF5, 0x32, 0x3D, 0xD7, 0xED, 0xAE, 0xAE, 0x3A, 
	0xBF, 0x41, 0xB7, 0x33, 0x63, 0x62, 0x32, 0x81, 0x27, 0xA9, 
	0xE2, 0x70, 0xFE, 0xEF, 0xDC, 0xAA, 0x9C, 0x24, 0x56, 0xB1, 
	0x84, 0x15, 0x6D, 0x65, 0x40, 0x0A, 0xF0, 0xE1, 0xE5, 0x95, 
	0xDD, 0xAC, 0xB7, 0xB5, 0xE5, 0xDC, 0x32, 0x4F, 0x54, 0xE3, 
	0x4F, 0xFB, 0x31, 0x14, 0x57, 0x81, 0xEA, 0x2F, 0x95, 0x03, 
	0x60, 0x7A, 0xF9, 0xC6, 0xFB, 0x90, 0x02, 0x38, 0x25, 0xFD, 
	0x0B, 0x3B, 0x4F, 0x3B, 0xCE, 0x39, 0x50, 0x23, 0xC6, 0x39, 
	0x42, 0xF9, 0xE3, 0xD2, 0xC1, 0xEE, 0x83, 0x7D, 0xB5, 0x5E, 
	0x80, 0xB5, 0x6E, 0x4F, 0x8A, 0xF5, 0xE1, 0xE4, 0xEB, 0xEB, 
	0x3B, 0xC0, 0xF3, 0x14, 0x80, 0xA0, 0x12, 0xF3, 0xC7, 0xAA, 
	0x6F, 0x8F, 0x89, 0x7E, 0x0D, 0x92, 0x1E, 0xCE, 0xE5, 0x64, 
	0x1B, 0xD7, 0xD8, 0xD8, 0x7E, 0xD8, 0x45, 0x02, 0x0C, 0x64, 
	0x80, 0x70, 0xC9, 0xC9, 0xB3, 0x1F, 0x5F, 0xEC, 0xDC, 0x5F, 
	0x00, 0x6A, 0x97, 0xC8, 0x3C, 0xD1, 0x77, 0x91, 0x09, 0x3B, 
	0xFA, 0x4C, 0x3D, 0x3D, 0x60, 0x72, 0xF8, 0x86, 0x4E, 0x76, 
	0x0E, 0x54, 0x83, 0x79, 0xA4, 0x00, 0x04, 0xF2, 0xFE, 0xDD, 
	0x2E, 0xB2, 0x8B, 0xF3, 0x19, 0xE0, 0x94, 0x59, 0x38, 0xC2, 
	0xCF, 0x40, 0x7E, 0x4A, 0x3D, 0x1E, 0x91, 0xF7, 0x6F, 0x91, 
	0x9D, 0xDA, 0x6C, 0x1B, 0xFE, 0x53, 0x81, 0x9A, 0x0A, 0xD2, 
	0x75, 0x88, 0x49, 0xBA, 0x00, 0xD4, 0x09, 0xE9, 0xF1, 0x33, 
	0xAC, 0x6F, 0xDE, 0x9E, 0x07, 0x0A, 0xC3, 0xFC, 0x17, 0x42, 
	0xF1, 0x0A, 0xC5, 0x21, 0x0A, 0x43, 0x14, 0x46, 0x28, 0x4E, 
	0xC8, 0xCE, 0xDF, 0x83, 0x4A, 0x2C, 0x01, 0x24, 0xC5, 0x12, 
	0x9B, 0xBD, 0x6B, 0x82, 0xE3, 0x18, 0x85, 0x02, 0xAB, 0x07, 
	0x28, 0x0E, 0x21, 0x14, 0xAD, 0x7F, 0x84, 0xE2, 0x14, 0x54, 
	0x41, 0xBD, 0xB4, 0x46, 0x2A, 0x24, 0x0B, 0x58, 0xFD, 0xBD, 
	0xC9, 0x14, 0x87, 0x28, 0x14, 0xED, 0x7D, 0xD0, 0x66, 0x1E, 
	0xCD, 0x01, 0x52, 0x98, 0x2F, 0xB6, 0x01, 0x78, 0xC9, 0x11, 
	0x51, 0xF8, 0xD5, 0x0A, 0x8B, 0x45, 0xD9, 0x71, 0x88, 0xC2, 
	0x78, 0x21, 0xB6, 0xB2, 0x69, 0x33, 0x2C, 0x01, 0xE4, 0x6D, 
	0x10, 0x66, 0x3F, 0x4F, 0xD4, 0x93, 0x6E, 0x8E, 0xE5, 0x89, 
	0xD4, 0x01, 0xCB, 0x41, 0xA7, 0x51, 0xAC, 0x00, 0x8F, 0x92, 
	0xE6, 0x74, 0x49, 0x24, 0x96, 0xA5, 0xE4, 0xAD, 0x5A, 0x00, 
	0xCA, 0xEA, 0xD1, 0xDE, 0x93, 0x9B, 0xDB, 0x88, 0xEB, 0x38, 
	0xF2, 0x7F, 0xBE, 0x5D, 0x01, 0xEE, 0xAD, 0xC7, 0xF4, 0xAC, 
	0x59, 0xE0, 0xFF, 0xFE, 0x8D, 0xBF, 0x01, 0xBE, 0x88, 0x1F, 
	0x7F, 0xE1, 0xDB, 0x9A, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x49, 
	0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82, 
};

wxBitmap& folder_png_to_wx_bitmap()
{
	static wxMemoryInputStream memIStream( folder_png, sizeof( folder_png ) );
	static wxImage image( memIStream, wxBITMAP_TYPE_PNG );
	static wxBitmap bmp( image );
	return bmp;
}


#endif //FOLDER_PNG_H
