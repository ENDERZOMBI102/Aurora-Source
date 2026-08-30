/***
*
//========= Copyright Valve Corporation, All rights reserved. ============//
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
****/
#pragma once
#include <cstdio>
#include "mathlib/vector.h"
#include "studio.h"
#include "tier0/basetypes.h"
#include "tier1/utlsymbol.h"
#include "tier1/utlvector.h"

struct LodScriptData_t;

#define IDSTUDIOHEADER ( ( 'T' << 24 ) + ( 'S' << 16 ) + ( 'D' << 8 ) + 'I' )
// little-endian "IDST"
#define IDSTUDIOANIMGROUPHEADER ( ( 'G' << 24 ) + ( 'A' << 16 ) + ( 'D' << 8 ) + 'I' )
// little-endian "IDAG"


#define STUDIO_QUADRATIC_MOTION 0x00002000

#define MAXSTUDIOANIMFRAMES 2000 // max frames per animation
#define MAXSTUDIOSEQUENCES 1524 // total sequences
#define MAXSTUDIOSRCBONES 512 // bones allowed at source movement
#define MAXSTUDIOBONEWEIGHTS 3
#define MAXSTUDIONAME 128


char outname[ 1024 ];
int numdirs;
char cddir[ 32 ][ MAX_PATH ];
char fullpath[ 1024 ];

float g_defaultscale;
float g_currentscale;
RadianEuler g_defaultrotation;


char defaulttexture[ 16 ][ MAX_PATH ];
char sourcetexture[ 16 ][ MAX_PATH ];

int numrep;

int flip_triangles;
float normal_blend;


void* kalloc( int num, int size );

struct s_trianglevert_t {
	int vertindex;
	int normindex; // index into normal array
	int s, t;
	float u, v;
};

struct s_boneweight_t {
	int numbones;

	int bone[ MAXSTUDIOBONEWEIGHTS ];
	float weight[ MAXSTUDIOBONEWEIGHTS ];
};


struct s_vertexinfo_t {
	// wtf is this doing here?
	int material;

	int firstref;
	int lastref;

	int flexmask;
	int numflex;
	int flexoffset;
};

struct s_tmpface_t {
	int material;
	unsigned long a, b, c;
	unsigned long ta, tb, tc;
	unsigned long na, nb, nc;
};

struct s_face_t {
	unsigned long a, b, c;
};

struct s_node_t {
	char name[ MAXSTUDIONAME ];
	int parent;
};


struct s_bone_t {
	Vector pos;
	RadianEuler rot;
};

struct s_texture_t {
	char name[ MAX_PATH ];
	int flags;
	int parent;
	int material;
	float width;
	float height;
	float dPdu;
	float dPdv;
};
s_texture_t g_texture[ MAXSTUDIOSKINS ];
int g_numtextures;
int g_material[ MAXSTUDIOSKINS ]; // link into texture array
int g_nummaterials;

float g_gamma;
int g_numskinref;
int g_numskinfamilies;
int g_skinref[ 256 ][ MAXSTUDIOSKINS ]; // [skin][skinref], returns texture index
int g_numtexturegroups;
int g_numtexturelayers[ 32 ];
int g_numtexturereps[ 32 ];
int g_texturegroup[ 32 ][ 32 ][ 32 ];

struct s_mesh_t {
	int numvertices;
	int vertexoffset;

	int numfaces;
	int faceoffset;
};


struct s_vertanim_t {
	int vertex;
	float speed;
	float side;
	Vector pos;
	Vector normal;
};

// processed aggregate lod pools
struct s_loddata_t {
	int numvertices;
	s_boneweight_t* globalBoneweight;
	s_vertexinfo_t* vertexInfo;
	Vector* vertex;
	Vector* normal;
	Vector4D* tangentS;
	Vector2D* texcoord;

	int numfaces;
	s_face_t* face;

	s_mesh_t mesh[ MAXSTUDIOSKINS ];

	// remaps verts from an lod's source mesh to this all-lod processed aggregate pool
	int* pMeshVertIndexMaps[ MAX_NUM_LODS ];
};

// raw off-disk source files.  Raw data should be not processed.
struct s_source_t {
	char filename[ MAX_PATH ];
	int time; // time stamp

	bool isActiveModel;

	// local skeleton hierarchy
	int numbones;
	s_node_t localBone[ MAXSTUDIOSRCBONES ];
	matrix3x4_t boneToPose[ MAXSTUDIOSRCBONES ]; // converts bone local data into initial pose data

	// bone remapping
	int boneflags[ MAXSTUDIOSRCBONES ]; // attachment, vertex, etc flags for this bone
	int boneref[ MAXSTUDIOSRCBONES ]; // flags for this and child bones
	int boneLocalToGlobal[ MAXSTUDIOSRCBONES ]; // bonemap : local bone to world bone mapping
	int boneGlobalToLocal[ MAXSTUDIOSRCBONES ]; // boneimap : world bone to local bone mapping

	int texmap[ MAXSTUDIOSKINS * 4 ]; // map local MAX materials to unique textures

	// per material mesh
	int nummeshes;
	int meshindex[ MAXSTUDIOSKINS ]; // mesh to skin index
	s_mesh_t mesh[ MAXSTUDIOSKINS ];

	// model global copy of vertices
	int numvertices;
	s_boneweight_t* localBoneweight; // vertex info about local bone weighting
	s_boneweight_t* globalBoneweight; // vertex info about global bone weighting
	s_vertexinfo_t* vertexInfo; // generic vertex info
	Vector* vertex;
	Vector* normal;
	Vector4D* tangentS;
	Vector2D* texcoord;

	int numfaces;
	s_face_t* face; // vertex indexs per face

	// raw skeletal animation
	int numframes;
	int startframe;
	int endframe;
	s_bone_t* rawanim[ MAXSTUDIOANIMFRAMES ]; // [frame][bones];

	// vertex animation
	int* vanim_mapcount; // local verts map to N target verts
	int** vanim_map; // local vertices to target vertices mapping list
	int* vanim_flag; // local vert does animate

	int numvanims[ MAXSTUDIOANIMFRAMES ];
	s_vertanim_t* vanim[ MAXSTUDIOANIMFRAMES ]; // [frame][vertex]

	// processed aggregate lod data
	s_loddata_t* pLodData;
};


int g_numsources;
s_source_t* g_source[ MAXSTUDIOSEQUENCES ];

int is_v1support;

int g_numverts;
Vector g_vertex[ MAXSTUDIOVERTS ];
s_boneweight_t g_bone[ MAXSTUDIOVERTS ];

int g_numnormals;
Vector g_normal[ MAXSTUDIOVERTS ];

int g_numtexcoords;
Vector2D g_texcoord[ MAXSTUDIOVERTS ];

int g_numfaces;
s_tmpface_t g_face[ MAXSTUDIOTRIANGLES ];
s_face_t g_src_uface[ MAXSTUDIOTRIANGLES ]; // max res unified faces

struct v_unify_t {
	int refcount;
	int lastref;
	int firstref;
	int v;
	int m;
	int n;
	int t;
	v_unify_t* next;
};

v_unify_t* v_list[ MAXSTUDIOVERTS ];
v_unify_t v_listdata[ MAXSTUDIOVERTS ];
int numvlist;

int SortAndBalanceBones( int iCount, int iMaxCount, int bones[], float weights[] );
void Grab_Vertexanimation( s_source_t* psource );
extern void BuildIndividualMeshes( s_source_t* psource );
