#pragma once

#include "../structs/structs.h"

typedef unsigned short MaterialHandle_t;

struct MaterialVideoMode_t
{
	int m_Width;
	int m_Height;
	int m_Format;
	int m_RefreshRate;
};

struct MaterialSystem_Config_t
{
	MaterialVideoMode_t m_VideoMode;
	float m_fMonitorGamma;
	float m_fGammaTVRangeMin;
	float m_fGammaTVRangeMax;
	float m_fGammaTVExponent;
	bool m_bGammaTVEnabled;
	bool m_bTripleBuffered;
	int m_nAASamples;
	int m_nForceAnisotropicLevel;
	int m_nSkipMipLevels;
	int m_nDxSupportLevel;
	int m_nFlags;
	bool m_bEditMode;
	char m_nProxiesTestMode;
	bool m_bCompressedTextures;
	bool m_bFilterLightmaps;
	bool m_bFilterTextures;
	bool m_bReverseDepth;
	bool m_bBufferPrimitives;
	bool m_bDrawFlat;
	bool m_bMeasureFillRate;
	bool m_bVisualizeFillRate;
	bool m_bNoTransparency;
	bool m_bSoftwareLighting;
	bool m_bAllowCheats;
	char m_nShowMipLevels;
	bool m_bShowLowResImage;
	bool m_bShowNormalMap;
	bool m_bMipMapTextures;
	char m_nFullbright;
	bool m_bFastNoBump;
	bool m_bSuppressRendering;
	bool m_bDrawGray;
	bool m_bShowSpecular;
	bool m_bShowDiffuse;
	int m_nWindowedSizeLimitWidth;
	int m_nWindowedSizeLimitHeight;
	int m_nAAQuality;
	bool m_bShadowDepthTexture;
	bool m_bMotionBlur;
	bool m_bSupportFlashlight;
	bool m_bPaintEnabled;
	char pad[ 0xC ];
};

// KeyValues
class KeyValues
{
public:
	char _pad[0x20]; //csgo, for css its a diff size
};


class IMatRenderContext;
class ITexture;
class IMaterialSystem
{
public:
		VFUNC( 21, OverrideConfig( const MaterialSystem_Config_t& cfg, bool b ), bool( __thiscall* )( void*, const MaterialSystem_Config_t&, bool ) )( cfg, b )
		VFUNC( 36, GetBackBufferFormat(), ImageFormat( __thiscall* )( void* ) )( )
		VFUNC( 84, FindMaterial( const char* name, const char *texgroup, bool complain = true, const char *complainprefix = nullptr ), IMaterial*( __thiscall* )( void*, const char*, const char*, bool, const char* ) )( name, texgroup, complain, complainprefix )
		VFUNC( 86, FirstMaterial(), MaterialHandle_t( __thiscall* )( void* ) )( )
		VFUNC( 87, NextMaterial( MaterialHandle_t h ), MaterialHandle_t( __thiscall* )( void*, MaterialHandle_t ) )( h )
		VFUNC( 88, InvalidMaterial(), MaterialHandle_t( __thiscall* )( void* ) )( )
		VFUNC( 89, GetMaterial( MaterialHandle_t h ), IMaterial* ( __thiscall* )( void*, MaterialHandle_t ) )( h )
		VFUNC( 90, GetNumMaterials(), int( __thiscall* )( void* ) )( )
		VFUNC( 91, FindTexture( const char* name, const char *groupname, bool complain ), ITexture*( __thiscall* )( void*, const char*, const char*, bool ) )( name, groupname, complain )
		VFUNC( 94, BeginRenderTargetAllocation(), void( __thiscall* )( void* ) )( )
		VFUNC( 95, EndRenderTargetAllocation(), void( __thiscall* )( void* ) )( )
		VFUNC( 115, GetRenderContext(), IMatRenderContext*( __thiscall* )( void* ) )( )
		VFUNC( 83, CreateMaterial(const char * pMaterialName, KeyValues* pVMTKeyValues), IMaterial*(__thiscall*)(void*, const char *, KeyValues*)) (pMaterialName, pVMTKeyValues)
};

extern IMaterialSystem* g_pMaterialSystem;

/*
//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
struct studiohdr_t;
struct studiohwdata_t;
struct vcollide_t;
struct virtualmodel_t;
struct vertexFileHeader_t;

namespace OptimizedModel
{
	struct FileHeader_t;
}


//-----------------------------------------------------------------------------
// Reference to a loaded studiomdl 
//-----------------------------------------------------------------------------
typedef unsigned short MDLHandle_t;

enum
{
	MDLHANDLE_INVALID = (MDLHandle_t)~0
};


//-----------------------------------------------------------------------------
// Cache data types
//-----------------------------------------------------------------------------
enum MDLCacheDataType_t
{
	// Callbacks to get called when data is loaded or unloaded for these:
	MDLCACHE_STUDIOHDR = 0,
	MDLCACHE_STUDIOHWDATA,
	MDLCACHE_VCOLLIDE,

	// Callbacks NOT called when data is loaded or unloaded for these:
	MDLCACHE_ANIMBLOCK,
	MDLCACHE_VIRTUALMODEL,
	MDLCACHE_VERTEXES,
	MDLCACHE_DECODEDANIMBLOCK,
};

class IMDLCacheNotify
{
public:
	// Called right after the data is loaded
	virtual void OnDataLoaded(MDLCacheDataType_t type, MDLHandle_t handle) = 0;

	// Called right before the data is unloaded
	virtual void OnDataUnloaded(MDLCacheDataType_t type, MDLHandle_t handle) = 0;
};


//-----------------------------------------------------------------------------
// Flags for flushing 
//-----------------------------------------------------------------------------
enum MDLCacheFlush_t
{
	MDLCACHE_FLUSH_STUDIOHDR = 0x01,
	MDLCACHE_FLUSH_STUDIOHWDATA = 0x02,
	MDLCACHE_FLUSH_VCOLLIDE = 0x04,
	MDLCACHE_FLUSH_ANIMBLOCK = 0x08,
	MDLCACHE_FLUSH_VIRTUALMODEL = 0x10,
	MDLCACHE_FLUSH_AUTOPLAY = 0x20,
	MDLCACHE_FLUSH_VERTEXES = 0x40,

	MDLCACHE_FLUSH_IGNORELOCK = 0x80000000,
	MDLCACHE_FLUSH_ALL = 0xFFFFFFFF
};

/*
#define MDLCACHE_INTERFACE_VERSION_4 "MDLCache004"
namespace MDLCacheV4
{
abstract_class IMDLCache : public IAppSystem
{
public:
	// Used to install callbacks for when data is loaded + unloaded
	virtual void SetCacheNotify( IMDLCacheNotify *pNotify ) = 0;
	// NOTE: This assumes the "GAME" path if you don't use
	// the UNC method of specifying files. This will also increment
	// the reference count of the MDL
	virtual MDLHandle_t FindMDL( const char *pMDLRelativePath ) = 0;
	// Reference counting
	virtual int AddRef( MDLHandle_t handle ) = 0;
	virtual int Release( MDLHandle_t handle ) = 0;
	// Gets at the various data associated with a MDL
	virtual studiohdr_t *GetStudioHdr( MDLHandle_t handle ) = 0;
	virtual studiohwdata_t *GetHardwareData( MDLHandle_t handle ) = 0;
	virtual vcollide_t *GetVCollide( MDLHandle_t handle ) = 0;
	virtual unsigned char *GetAnimBlock( MDLHandle_t handle, int nBlock ) = 0;
	virtual virtualmodel_t *GetVirtualModel( MDLHandle_t handle ) = 0;
	virtual int GetAutoplayList( MDLHandle_t handle, unsigned short **pOut ) = 0;
	virtual vertexFileHeader_t *GetVertexData( MDLHandle_t handle ) = 0;
	// Brings all data associated with an MDL into memory
	virtual void TouchAllData( MDLHandle_t handle ) = 0;
	// Gets/sets user data associated with the MDL
	virtual void SetUserData( MDLHandle_t handle, void* pData ) = 0;
	virtual void *GetUserData( MDLHandle_t handle ) = 0;
	// Is this MDL using the error model?
	virtual bool IsErrorModel( MDLHandle_t handle ) = 0;
	// Flushes the cache, force a full discard
	virtual void Flush( int nFlushFlags = MDLCACHE_FLUSH_ALL ) = 0;
	// Flushes a particular model out of memory
	virtual void Flush( MDLHandle_t handle, int nFlushFlags = MDLCACHE_FLUSH_ALL ) = 0;
	// Returns the name of the model (its relative path)
	virtual const char *GetModelName( MDLHandle_t handle ) = 0;
	// faster access when you already have the studiohdr
	virtual virtualmodel_t *GetVirtualModelFast( const studiohdr_t *pStudioHdr, MDLHandle_t handle ) = 0;
	// all cache entries that subsequently allocated or successfully checked
	// are considered "locked" and will not be freed when additional memory is needed
	virtual void BeginLock() = 0;
	// reset all protected blocks to normal
	virtual void EndLock() = 0;
	// returns a pointer to a counter that is incremented every time the cache has been out of the locked state (EVIL)
	virtual int *GetFrameUnlockCounterPtr()  = 0;
	// Finish all pending async operations
	virtual void FinishPendingLoads() = 0;
};
}
*/
/*


typedef void* (*create_interface_fn)(const char* pName, int* pReturnCode);


//-----------------------------------------------------------------------------
// The main MDL cacher 
//-----------------------------------------------------------------------------


class IMdlCache : public i_app_system
{
public:
	// Used to install callbacks for when data is loaded + unloaded
	// Returns the prior notify
	virtual void SetCacheNotify(IMDLCacheNotify* pNotify) = 0;

	// NOTE: This assumes the "GAME" path if you don't use
	// the UNC method of specifying files. This will also increment
	// the reference count of the MDL
	virtual MDLHandle_t FindMDL(const char* pMDLRelativePath) = 0;

	// Reference counting
	virtual int AddRef(MDLHandle_t handle) = 0;
	virtual int Release(MDLHandle_t handle) = 0;
	virtual int GetRef(MDLHandle_t handle) = 0;

	// Gets at the various data associated with a MDL
	virtual studiohdr_t* GetStudioHdr(MDLHandle_t handle) = 0;
	virtual studiohwdata_t* GetHardwareData(MDLHandle_t handle) = 0;
	virtual vcollide_t* GetVCollide(MDLHandle_t handle) = 0;
	virtual unsigned char* GetAnimBlock(MDLHandle_t handle, int nBlock) = 0;
	virtual virtualmodel_t* GetVirtualModel(MDLHandle_t handle) = 0;
	virtual int GetAutoplayList(MDLHandle_t handle, unsigned short** pOut) = 0;
	virtual vertexFileHeader_t* GetVertexData(MDLHandle_t handle) = 0;

	// Brings all data associated with an MDL into memory
	virtual void TouchAllData(MDLHandle_t handle) = 0;

	// Gets/sets user data associated with the MDL
	virtual void SetUserData(MDLHandle_t handle, void* pData) = 0;
	virtual void* GetUserData(MDLHandle_t handle) = 0;

	// Is this MDL using the error model?
	virtual bool IsErrorModel(MDLHandle_t handle) = 0;

	// Flushes the cache, force a full discard
	virtual void Flush(MDLCacheFlush_t nFlushFlags = MDLCACHE_FLUSH_ALL) = 0;

	// Flushes a particular model out of memory
	virtual void Flush(MDLHandle_t handle, int nFlushFlags = MDLCACHE_FLUSH_ALL) = 0;

	// Returns the name of the model (its relative path)
	virtual const char* GetModelName(MDLHandle_t handle) = 0;

	// faster access when you already have the studiohdr
	virtual virtualmodel_t* GetVirtualModelFast(const studiohdr_t* pStudioHdr, MDLHandle_t handle) = 0;

	// all cache entries that subsequently allocated or successfully checked 
	// are considered "locked" and will not be freed when additional memory is needed
	virtual void BeginLock() = 0;

	// reset all protected blocks to normal
	virtual void EndLock() = 0;

	// returns a pointer to a counter that is incremented every time the cache has been out of the locked state (EVIL)
	virtual int* GetFrameUnlockCounterPtrOLD() = 0;

	// Finish all pending async operations
	virtual void FinishPendingLoads() = 0;

	virtual vcollide_t* GetVCollideEx(MDLHandle_t handle, bool synchronousLoad = true) = 0;
	virtual bool GetVCollideSize(MDLHandle_t handle, int* pVCollideSize) = 0;

	virtual bool GetAsyncLoad(MDLCacheDataType_t type) = 0;
	virtual bool SetAsyncLoad(MDLCacheDataType_t type, bool bAsync) = 0;

	virtual void BeginMapLoad() = 0;
	virtual void EndMapLoad() = 0;
	virtual void MarkAsLoaded(MDLHandle_t handle) = 0;

	virtual void InitPreloadData(bool rebuild) = 0;
	virtual void ShutdownPreloadData() = 0;

	virtual bool IsDataLoaded(MDLHandle_t handle, MDLCacheDataType_t type) = 0;

	virtual int* GetFrameUnlockCounterPtr(MDLCacheDataType_t type) = 0;

	virtual studiohdr_t* LockStudioHdr(MDLHandle_t handle) = 0;
	virtual void UnlockStudioHdr(MDLHandle_t handle) = 0;

	virtual bool PreloadModel(MDLHandle_t handle) = 0;

	// Hammer uses this. If a model has an error loading in GetStudioHdr, then it is flagged
	// as an error model and any further attempts to load it will just get the error model.
	// That is, until you call this function. Then it will load the correct model.
	virtual void ResetErrorModelStatus(MDLHandle_t handle) = 0;

	virtual void MarkFrame() = 0;
};
*/

