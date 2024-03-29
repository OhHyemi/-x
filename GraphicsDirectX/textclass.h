#pragma once
#ifndef _TEXTCLASS_H_
#define _TEXTCLASS_H_
#define SENTENCECOUNT 5
#define UICOUNT 7
///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "fontclass.h"
#include "fontshaderclass.h"
////////////////////////////////////////////////////////////////////////////////
// Class name: TextClass
////////////////////////////////////////////////////////////////////////////////

class TextClass
{
private:
	struct SentenceType
	{
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		float red, green, blue;
	};
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};
public:
	TextClass();
	TextClass(const TextClass&);
	~TextClass();
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, HWND, int, int, D3DXMATRIX, int, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX);
	//bool SetMousePosition(int, int, ID3D11DeviceContext*);
	bool ShowScreenSize(int, int, ID3D11DeviceContext*);
	bool ShowPolygonCount(ID3D11DeviceContext*);
	bool SetFps(int, ID3D11DeviceContext*);
	bool SetCpu(int, ID3D11DeviceContext*);
	bool ShowModelCount(ID3D11DeviceContext*);
	bool ShowGotCarrot(int, ID3D11DeviceContext*);
private:
	bool InitializeSentence(SentenceType**, int, ID3D11Device*);
	bool UpdateSentence(SentenceType*, char*, int, int, float, float, float, ID3D11DeviceContext*);
	void ReleaseSentence(SentenceType**);
	bool RenderSentence(ID3D11DeviceContext*, SentenceType*, D3DXMATRIX, D3DXMATRIX);
	

private:
	FontClass* m_Font;
	FontShaderClass* m_FontShader;
	int m_screenWidth, m_screenHeight;
	D3DXMATRIX m_baseViewMatrix;
	SentenceType* m_sentence[SENTENCECOUNT];
	SentenceType* u_sentence[UICOUNT];
	
	int mouseX;
	int mouseY;

	int modelCount;
	int polygonCount;
	
};
#endif