#pragma once

#ifndef IVDebugOverlay_h

#define IVDebugOverlay_h

class OverlayText_t;

class IVDebugOverlay
{
public:
	virtual void            AddEntityTextOverlay( int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char *format, ... ) = 0;
	virtual void            AddBoxOverlay( const Vector& origin, const Vector& mins, const Vector& max, QAngle const& orientation, int r, int g, int b, int a, float duration ) = 0;
	virtual void            AddSphereOverlay( const Vector& vOrigin, float flRadius, int nTheta, int nPhi, int r, int g, int b, int a, float flDuration ) = 0;
	virtual void            AddTriangleOverlay( const Vector& p1, const Vector& p2, const Vector& p3, int r, int g, int b, int a, bool noDepthTest, float duration ) = 0;
	virtual void            AddLineOverlay( const Vector& origin, const Vector& dest, int r, int g, int b, bool noDepthTest, float duration ) = 0;
	virtual void            AddTextOverlay( const Vector& origin, float duration, const char *format, ... ) = 0;
	virtual void            AddTextOverlay( const Vector& origin, int line_offset, float duration, const char *format, ... ) = 0;
	virtual void            AddScreenTextOverlay( float flXPos, float flYPos, float flDuration, int r, int g, int b, int a, const char *text ) = 0;
	virtual void            AddSweptBoxOverlay( const Vector& start, const Vector& end, const Vector& mins, const Vector& max, const QAngle & angles, int r, int g, int b, int a, float flDuration ) = 0;
	virtual void            AddGridOverlay( const Vector& origin ) = 0;
	virtual void            AddCoordFrameOverlay( const matrix3x4_t& frame, float flScale, int vColorTable[ 3 ][ 3 ] = NULL ) = 0;
	virtual int             ScreenPosition( const Vector& point, Vector& screen ) = 0;
	virtual int             ScreenPosition( float flXPos, float flYPos, Vector& screen ) = 0;
	virtual OverlayText_t*  GetFirst( void ) = 0;
	virtual OverlayText_t*  GetNext( OverlayText_t *current ) = 0;
	virtual void            ClearDeadOverlays( void ) = 0;
	virtual void            ClearAllOverlays( void ) = 0;
	virtual void            AddTextOverlayRGB( const Vector& origin, int line_offset, float duration, float r, float g, float b, float alpha, const char *format, ... ) = 0;
	virtual void            AddTextOverlayRGB( const Vector& origin, int line_offset, float duration, int r, int g, int b, int a, const char *format, ... ) = 0;
	virtual void            AddLineOverlayAlpha( const Vector& origin, const Vector& dest, int r, int g, int b, int a, bool noDepthTest, float duration ) = 0;
	virtual void            AddBoxOverlay2( const Vector& origin, const Vector& mins, const Vector& max, QAngle const& orientation, const uint8_t* faceColor, const uint8_t* edgeColor, float duration ) = 0;
	virtual void			AddLineOverlay( const Vector& origin, const Vector& dest, int r, int g, int b, int a, float, float ) = 0;
	virtual void            PurgeTextOverlays() = 0;
	VFUNC( 23, AddCapsuleOverlay( Vector& mins, Vector& maxs, float radius, int r, int g, int b, int a, float duration ), void( __thiscall* )( void*, Vector&, Vector&, float&, int, int, int, int, float ) )( mins, maxs, radius, r, g, b, a, duration )
	VFUNC( 24, AddCapsuleOverlayVisible( Vector& mins, Vector& maxs, float radius, int r, int g, int b, int a, float duration ), void( __thiscall* )( void*, Vector&, Vector&, float&, int, int, int, int, float ) )( mins, maxs, radius, r, g, b, a, duration )

	bool WorldToScreen(const Vector& in, Vector& out) {
		using original_fn = int(__thiscall*)(IVDebugOverlay*, const Vector&, Vector&);
		int return_value = (*(original_fn**)this)[13](this, in, out);
		return static_cast<bool>(return_value != 1);
	}
};

#endif // !IVDebugOverlay_h