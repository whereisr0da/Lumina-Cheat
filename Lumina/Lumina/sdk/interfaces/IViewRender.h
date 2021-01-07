#pragma once

class IViewRender
{
public:
	virtual void		Init( void ) = 0;

	// Clear any systems between levels
	virtual void		LevelInit( void ) = 0;
	virtual void		LevelShutdown( void ) = 0;

	// Shutdown
	virtual void		Shutdown( void ) = 0;

	// RENDERING
	// Called right before simulation. It must setup the view model origins and angles here so 
	// the correct attachment points can be used during simulation.	
	virtual void		OnRenderStart() = 0;

	// Called to render the entire scene
	virtual	void		Render( void *rect ) = 0;

	// Called to render just a particular setup ( for timerefresh and envmap creation )
	virtual void		RenderView( const CViewSetup &view, int nClearFlags, int whatToDraw ) = 0;

	// What are we currently rendering? Returns a combination of DF_ flags.
	virtual int GetDrawFlags() = 0;

	// MISC
	// Start and stop pitch drifting logic
	virtual void		StartPitchDrift( void ) = 0;
	virtual void		StopPitchDrift( void ) = 0;
};

extern IViewRender* g_pViewRender;