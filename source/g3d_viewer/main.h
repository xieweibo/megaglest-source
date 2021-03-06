// ==============================================================
// This file is part of MegaGlest (www.glest.org)
//
// Copyright (C) 2011 - by Mark Vejvoda <mark_vejvoda@hotmail.com>
//
//	You can redistribute this code and/or modify it under
//	the terms of the GNU General Public License as published
//	by the Free Software Foundation; either version 2 of the
//	License, or (at your option) any later version
// ==============================================================

#ifndef _SHADER_G3DVIEWER_MAIN_H_
#define _SHADER_G3DVIEWER_MAIN_H_

#ifdef WIN32
    #include <winsock2.h>
    #include <winsock.h>
#endif

#include <string>
#include <GL/glew.h>
#include <wx/wx.h>
#include <wx/glcanvas.h>
//#include <wx/clrpicker.h>
#include <wx/colordlg.h>

#include "renderer.h"
#include "util.h"
#include "particle_type.h"
#include "unit_particle_type.h"

using std::string;
using namespace Glest::Game;

namespace Shared{ namespace G3dViewer{

class GlCanvas;

// ===============================
// 	class MainWindow
// ===============================

class MainWindow: public wxFrame{
private:
	DECLARE_EVENT_TABLE()

public:
	static const string versionString;
	static const string winHeader;

	enum MenuId{
		miFileLoad,
		miFileLoadParticleXML,
		miFileLoadProjectileParticleXML,
		miFileLoadSplashParticleXML,
		miFileClearAll,
		miFileToggleScreenshotTransparent,
		miFileSaveScreenshot,
		miModeWireframe,
		miModeNormals,
		miModeGrid,
		miSpeedSlower,
		miSpeedFaster,
		miRestart,
		miChangeBackgroundColor,
		miColorRed,
		miColorBlue,
		miColorGreen,
		miColorYellow,
		miColorWhite,
		miColorCyan,
		miColorOrange,
		miColorMagenta
	};

private:
	GlCanvas *glCanvas;
	Renderer *renderer;

	wxTimer *timer;

	wxMenuBar *menu;
	wxMenu *menuFile;
	wxMenu *menuMode;
	wxMenu *menuSpeed;
	wxMenu *menuCustomColor;
	wxFileDialog *fileDialog;

	wxColourDialog *colorPicker;

	Model *model;

	std::pair<string,vector<string> > unitPath;
	std::vector<string> modelPathList;
	std::vector<string> particlePathList;
	std::vector<string> particleProjectilePathList;
	std::vector<string> particleSplashPathList; // as above

	bool resetAnimation;
	float resetAnim;
	int resetParticleLoopStart;

	float speed;
	float anim;
	float lastanim;
	int particleLoopStart;
	float rotX, rotY, zoom;
	float backBrightness, gridBrightness, lightBrightness;
	int lastX, lastY;
	Renderer::PlayerColor playerColor;
	bool initTextureManager;

	std::vector<UnitParticleSystemType *> unitParticleSystemTypes;
	std::vector<UnitParticleSystem *> unitParticleSystems;

	std::vector<ParticleSystemTypeProjectile *> projectileParticleSystemTypes;
	std::vector<ProjectileParticleSystem *> projectileParticleSystems;
	std::vector<ParticleSystemTypeSplash *> splashParticleSystemTypes; // as above
	std::vector<SplashParticleSystem *> splashParticleSystems;
	string statusbarText;

	bool isControlKeyPressed;

	string appPath;

	bool startupSettingsInited;

	void initGlCanvas();
	void loadUnit(string path, string skillName);
	void loadModel(string path);
	void loadParticle(string path);
	void loadProjectileParticle(string path);
	void loadSplashParticle(string path);

	void saveScreenshot();

public:
	MainWindow(	std::pair<string,vector<string> > unitToLoad,
				const string modelPath,const string particlePath,
				const string projectileParticlePath,const string splashParticlePath,
				float defaultAnimation,int defaultParticleLoopStart,
				float defaultZoom,float defaultXRot, float defaultYRot,
				string appPath);
	~MainWindow();
	void init();

	void Notify();

	void onPaint(wxPaintEvent &event);
	void onClose(wxCloseEvent &event);
	void onMenuFileLoad(wxCommandEvent &event);
	void onMenuFileLoadParticleXML(wxCommandEvent &event);
	void onMenuFileLoadProjectileParticleXML(wxCommandEvent &event);
	void onMenuFileLoadSplashParticleXML(wxCommandEvent &event);
	void onMenuFileClearAll(wxCommandEvent &event);
	void onMenumFileToggleScreenshotTransparent(wxCommandEvent &event);
	void onMenuFileSaveScreenshot(wxCommandEvent &event);
	void onMenuFileExit(wxCommandEvent &event);
	void onMenuModeNormals(wxCommandEvent &event);
	void onMenuModeWireframe(wxCommandEvent &event);
	void onMenuModeGrid(wxCommandEvent &event);
	void onMenuSpeedSlower(wxCommandEvent &event);
	void onMenuSpeedFaster(wxCommandEvent &event);
	void onMenuRestart(wxCommandEvent &event);
	void OnChangeColor(wxCommandEvent &event);
	void onMenuColorRed(wxCommandEvent &event);
	void onMenuColorBlue(wxCommandEvent &event);
	void onMenuColorGreen(wxCommandEvent &event);
	void onMenuColorYellow(wxCommandEvent &event);
	void onMenuColorWhite(wxCommandEvent &event);
	void onMenuColorCyan(wxCommandEvent &event);
	void onMenuColorOrange(wxCommandEvent &event);
	void onMenuColorMagenta(wxCommandEvent &event);
	void onMouseWheelDown(wxMouseEvent &event);
	void onMouseWheelUp(wxMouseEvent &event);
	void onMouseMove(wxMouseEvent &event);
	void onTimer(wxTimerEvent &event);

	void onKeyDown(wxKeyEvent &e);

	string getModelInfo();

	void setupTimer();
	void setupStartupSettings();
};

// =====================================================
//	class GlCanvas
// =====================================================

class GlCanvas: public wxGLCanvas {
private:
	DECLARE_EVENT_TABLE()

public:
	GlCanvas(MainWindow *mainWindow, int *args);
	~GlCanvas();

	void onMouseWheel(wxMouseEvent &event);
	void onMouseMove(wxMouseEvent &event);
	void onPaint(wxPaintEvent &event);
	void onKeyDown(wxKeyEvent &event);
	void OnSize(wxSizeEvent&);
	void setCurrentGLContext();

	wxGLContext * getCtx() { return context; }
private:
	MainWindow *mainWindow;
	wxGLContext *context;
};


// ===============================
// 	class App
// ===============================

class App: public wxApp{
private:
	MainWindow *mainWindow;

public:
	App() : wxApp() {
		mainWindow = NULL;
	}
	virtual ~App() {}
	virtual bool OnInit();
	virtual int MainLoop();
	virtual int OnExit();
};

}}//end namespace

DECLARE_APP(Shared::G3dViewer::App)

#endif
