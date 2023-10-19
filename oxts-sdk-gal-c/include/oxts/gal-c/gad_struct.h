//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2020 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! $LastChangedDate: 2019-10-07 15:14:42 +0100 (Mon, 07 Oct 2019) $
//! $LastChangedRevision: 28566 $
//! $LastChangedBy: smccarthy $
//!
//! \file gad_struct.h
//!
//! \brief Header for gad_struct.c
//!  
//============================================================================================================

#ifndef GAD_STRUCT
#define GAD_STRUCT

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "oxts/core/BasicTypes.h"
#include "oxts/core/errors.h"
#include "oxts/gal-c/gad_defines.h"

typedef uint8_t   GEN_BOOL;

//==============================================================================
//! \brief Decoder types

typedef enum
{
   DECODER_VOID,                    /** Not set. */
   DECODER_CSV,                     /** Text data. */
   DECODER_BIN                      /** Binary data. */
} DECODER_TYPE;


//==============================================================================
//! \brief Variance formats

typedef enum
{
   GEN_VAR_VOID,                   /** Missing. */
   GEN_VAR_SINGLE,                 /** Single variance value. */
   GEN_VAR_DIAG,                   /** Diagonal variance matrix. */
   GEN_VAR_HMAT                    /** Half-matrix (full co-variance matrix). */
} GEN_VAR_TYPE;

//==============================================================================
//! \brief 3-dimensional structure (vector real) with storage for full variance

typedef struct
{
   uint8_t        mode;        /** ID */
   uint8_t        x_type;      /** Type of value x, e.g. coord system */
   real64_t       x[3];        /** Values */
   uint8_t        v_type;      /** Variance type see GEN_VAR_TYPE */
   real64_t       v[3*(3+1)/2];/** Space for covariance matrix (diag+upper diag) */
} GEN_3D;

//==============================================================================
//! \brief Time systems
typedef enum
{
   TIME_VOID,
   TIME_GPS,            /** Standard GPS time format. */
   TIME_PPS_RELATIVE,   /** Time since PPS. */
   TIME_EST_LATENCY,    /** Not a full timestamp, just an estimate of latency. */
   TIME_SDN,            /** This is internal timing for xbns. (DO NOT USE) */
   TIME_EXT,            /** IN DEVELOPMENT, DO NOT USE */
   TIME_UNIX_UTC,       /** Time since unix epoch, including leap seconds. */
   TIME_TAI             // Time in TAI format
}TIME_SYS;

//==============================================================================
//! \brief Generic Aiding types

typedef enum
{
   GEN_VOID,
   GEN_POS,          /** Position 3D. */
   GEN_RANGE,        /** Range, 1D value, can contain angle of arrival as additional info. */
   GEN_VEL,          /** Velocity 3D. */
   GEN_SPEED,        /** Speed, e.g. wheel speed. */
   GEN_ATT,          /** Attitude. */
   GEN_HEADING,      /** Heading   @note To be merged in GEN_ATT, with ATT specifying in type wherer only heading, or heading+pitch, or heading+pitch+roll are present. */
   GEN_TIMETRIG,     /** Time trigger, used for indoor segment navigation. */
   GEN_ANGULAR,      /** Angular Rate. */
   GEN_NUM
} GEN_TYPE;

//==============================================================================
//! \brief Position coordinate systems

typedef enum
{
   POS_SYS_VOID,         
   POS_SYS_WGS84,        /** WGS84 - lat/lon/depth */
   POS_SYS_LOCAL,        /** User defined right-handed local coordinate system - x/y/z */
} POS_SYS_TYPE;


//==============================================================================
//! \brief Velocity types

typedef enum
{
   VEL_SYS_VOID,
   VEL_SYS_NED,             /** North East Down */
   VEL_SYS_ODO,             /** Aiding source frame - x/y/z */
   VEL_SYS_LOCAL            /** User defined right-handed local coordinate system - x/y/z */
} VEL_SYS_TYPE;

//==============================================================================
//! \brief Speed types 

typedef enum
{
   SPEED_SYS_VOID,
   SPEED_SYS_FW_VEL,        /** Speed at sensor fixed wrt IMU, speed angle wrt IMU given. */
} SPEED_SYS_TYPE;
//==============================================================================
//! \brief Attitude types 

typedef enum
{
   ATT_SYS_VOID,
   ATT_SYS_HPR,      /** Attitude measurement given as Heading, Pitch, Roll in the navigation (NED) frame. */
   ATT_SYS_LOCAL,    /** Attitude measurement given as Heading, Pitch, Roll in a static local reference frame. */
} ATT_SYS_TYPE;

//============================================================================================================
//! \brief Heading types
typedef enum
{
   HEA_SYS_VOID,
   HEA_SYS_NAV,        // Heading measurement in the navigation frame (NED).
   HEA_SYS_LOCAL       // Heading measurement in a local frame. 
} HEA_SYS_TYPE;

//==============================================================================
//! \brief Angular Rate types
typedef enum
{
   ANG_SYS_VOID = 0,    
   ANG_SYS_DEFAULT = 1  /** Angular rate update in a rigidly-mounted sensor frame. */
} ANG_SYS_TYPE;

//==============================================================================
//! \brief Location types. (lever arm)
typedef enum
{
   LOC_FIXED = 0,    /** Lever arm specified explicitly. */
   LOC_KF = 1,       /** Take lever arm from kalman filter. -- lever arm is specified in the .gap file. */
   LOC_CONFIG = 2    /** Take lever arm from a configured lever arm in the config. */
}LOC_SYS;


//==============================================================================
//! \brief Generic aiding data structure 
//!
//! The data is streamed in the sequence of data members
//! The dimension of the data is defined by type, if variable, we will need to define a new sub-structure
//! The sequence of data items is fixed (e.g. as given in this structure)

typedef struct
{
   /** Aiding type. Enumerated by GEN_TYPE */
   int8_t         type;

   /** Stream ID. Identifies the source device. */
   uint8_t        stream_id;

   /** Sub-struct VALUE. Contains aiding data */
   GEN_3D         val;
   GEN_BOOL       val_valid;

   /** Sub-struct TIME. Contains time information. */
   GEN_3D         time;
   GEN_BOOL       time_valid;

   /** Sub-struct LOCATION. Contains lever arm / alignment between aiding
    *  source and IMU. */ 
   GEN_3D         loc;
   GEN_BOOL       loc_valid;

   /** Sub-struct RESERVED for future use. */
   GEN_3D         res1;
   GEN_BOOL       res1_valid;          

   /** Sub-struct RESERVED for future use.*/
   GEN_3D         res2;
   GEN_BOOL       res2_valid;          

   /** Acquisition Time Stamp. Field used by INS upon acquisition, not needed by 
    *  users. */ 
   uint32_t       acq;
   GEN_BOOL       acq_valid;

} GEN_AIDING_DATA;



#ifdef __cplusplus
extern "C"
{
#endif

//==============================================================================
//! \brief Functions to initialise/destroy/copy

/** Sets all the valid flags to 0
   @param gad pointer to GEN_AIDING_DATA
   @todo make safe to user passing a NULL pointer
*/
int reset_genaid_data(GEN_AIDING_DATA* gad);


int reset_gen3d(GEN_3D* d);

/** Initialise a block of memory for GEN_AIDING_DATA
   @param gad pointer to the a pointer to start of GEN_AIDING_DATA
*/
int initialise_genaid(void** gad);


/** Frees generic aiding resource
 * @param gad pointer to the a pointer to start of GEN_AIDING_DATA
 * @param free_base
*/
int kill_genaid(void** gad, int free_base);


/** Copies the data from one pointer to the other. not safe to dst pointer buffer < sizeof(GEN_AIDING_DATA)
   @param dst Pointer to the location the data is being copied to
   @param src Pointer to the location of the start of the gen_aiding_data struct
*/
int genaid_copy(void* dst, void* src);

#ifdef __cplusplus
}
#endif

#endif
