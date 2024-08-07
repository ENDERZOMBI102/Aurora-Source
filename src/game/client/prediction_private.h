//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $Log: $
//
// $NoKeywords: $
//=============================================================================//
#pragma once


// point on plane side epsilon
#define ON_EPSILON 0.1

#define MAX_FORWARD 6

// Use smoothing if error is > this
#define MIN_CORRECTION_DISTANCE 0.25f

// Complain if error is > this and we have cl_showerror set
#define MIN_PREDICTION_EPSILON 0.5f

// Above this is assumed to be a teleport, don't smooth, etc.
#define MAX_PREDICTION_ERROR 64.0f
