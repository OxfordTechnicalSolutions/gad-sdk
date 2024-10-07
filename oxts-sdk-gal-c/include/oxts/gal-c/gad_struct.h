//============================================================================================================
//
// The software is protected by copyright of Oxford Technical Solutions.
// Copyright (C) 2020 Oxford Technical Solutions - http://www.oxts.com
//
// Redistribution and use in source and binary forms, with or without modification, are only permitted with
// the specific prior written permission of Oxford Technical Solutions.
//
// LastChangedDate: 2019-10-07 15:14:42 +0100 (Mon, 07 Oct 2019)
// LastChangedRevision: 28566
// LastChangedBy: smccarthy
//
// \file gad_struct.h
//
// \brief Header for gad_struct.c
//  
//============================================================================================================

#ifndef GAD_STRUCT
#define GAD_STRUCT

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "oxts/gal-c/BasicTypes.h"
#include "oxts/gal-c/gad_defines.h"

typedef uint8_t   GEN_BOOL;

//==============================================================================
// \brief Decoder types

#define DECODER_VOID 0U                    /** Not set. */ /*PRQA S 1534 # Macro is intended for external consumption. */
#define DECODER_CSV 1U                     /** Text data. */ /*PRQA S 1534 # Macro is intended for external consumption. */
#define DECODER_BIN 2U                     /** Binary data. */ /*PRQA S 1534 # Macro is intended for external consumption. */


//==============================================================================
// \brief Variance formats

#define GEN_VAR_VOID 0U                   /** Missing. */
#define GEN_VAR_SINGLE 1U                 /** Single variance value. */
#define GEN_VAR_DIAG 2U                   /** Diagonal variance matrix. */
#define GEN_VAR_HMAT 3U                    /** Half-matrix (full co-variance matrix). */

//==============================================================================
// \brief 3-dimensional structure (vector real) with storage for full variance

typedef struct
{
   uint8_t        mode;        /** ID */
   uint8_t        x_type;      /** Type of value x, e.g. coord system */
   double_t       x[3];        /** Values */
   uint8_t        v_type;      /** Variance type see GEN_VAR_TYPE */
   double_t       v[3*(3+1)/2];/** Space for covariance matrix (diag+upper diag) */
} GEN_3D;

//==============================================================================
// \brief Time systems
#define TIME_VOID 0 /*PRQA S 1534 # Macro is intended for external consumption. */
/** Standard GPS time format. */
#define TIME_GPS 1            /*PRQA S 1534 # Macro is intended for external consumption. */
/** Time since PPS. */
#define TIME_PPS_RELATIVE 2   
/** Not a full timestamp, just an estimate of latency. */
#define TIME_EST_LATENCY 3    /*PRQA S 1534 # Macro is intended for external consumption. */
/** This is internal timing for xbns. (DO NOT USE) */
#define TIME_SDN 4            /*PRQA S 1534 # Macro is intended for external consumption. */
/** IN DEVELOPMENT, DO NOT USE */
#define TIME_EXT 5            /*PRQA S 1534 # Macro is intended for external consumption. */
/** Time since unix epoch, including leap seconds. */ 
#define TIME_UNIX_UTC 6       /*PRQA S 1534 # Macro is intended for external consumption. */
// Time in TAI format 
#define TIME_TAI 7            /*PRQA S 1534 # Macro is intended for external consumption. */

//==============================================================================
// \brief Generic Aiding types

#define GEN_VOID 0U 
/** Position 3D. */ 
#define GEN_POS 1U          /*PRQA S 1534 # Macro is intended for external consumption. */
/** Range, 1D value, can contain angle of arrival as additional info. */ 
#define GEN_RANGE 2U        /*PRQA S 1534 # Macro is intended for external consumption. */
/** Velocity 3D. */ 
#define GEN_VEL 3U          /*PRQA S 1534 # Macro is intended for external consumption. */
/** Speed, e.g. wheel speed. */ 
#define GEN_WSPEED 4U        /*PRQA S 1534 # Macro is intended for external consumption. */
/** Attitude. */ 
#define GEN_ATT 5U         /*PRQA S 1534 # Macro is intended for external consumption. */
 /** Heading   note To be merged in GEN_ATT, with ATT specifying in type wherer only heading, or heading+pitch, or heading+pitch+roll are present. */ 
#define GEN_HEADING 6U     /*PRQA S 1534 # Macro is intended for external consumption. */
/** Time trigger, used for indoor segment navigation. */
#define GEN_TIMETRIG 7U    /*PRQA S 1534 # Macro is intended for external consumption. */
/** 1-Dimensional speed in the vehicle frame */
#define GEN_SPEED 8U	/*PRQA S 1534 # Macro is intended for external consumption. */
#define GEN_ANGRATE 9U	/*PRQA S 1534 # Macro is intended for external consumption. */
#define GEN_NUM 10U	/*PRQA S 1534 # Macro is intended for external consumption. */

//==============================================================================
// \brief Position coordinate systems

#define POS_SYS_VOID 0U         /*PRQA S 1534 # Macro is intended for external consumption. */
/** WGS84 - lat/lon/depth */ 
#define POS_SYS_WGS84 1U        /*PRQA S 1534 # Macro is intended for external consumption. */
/** User defined right-handed local coordinate system - x/y/z */
#define POS_SYS_LOCAL 2U        /*PRQA S 1534 # Macro is intended for external consumption. */

//==============================================================================
// \brief Velocity types

#define VEL_SYS_VOID 0U /*PRQA S 1534 # Macro is intended for external consumption. */
 /** North East Down */ 
#define VEL_SYS_NED 1U        /*PRQA S 1534 # Macro is intended for external consumption. */
/** Aiding source frame - x/y/z */
#define VEL_SYS_ODO 2U        /*PRQA S 1534 # Macro is intended for external consumption. */
/** User defined right-handed local coordinate system - x/y/z */
#define VEL_SYS_LOCAL 3U      /*PRQA S 1534 # Macro is intended for external consumption. */

//==============================================================================
// \brief Speed types 

#define SPEED_SYS_VOID 0U /*PRQA S 1534 # Macro is intended for external consumption. */
/** Speed at sensor fixed wrt IMU, signed, +ve forward */
#define SPEED_SYS_FW_VEL 1U    /*PRQA S 1534 # Macro is intended for external consumption. */
/** Speed at sensor fixed wrt IMU, signed, +ve backward */
#define SPEED_SYS_BW_VEL 2U	/*PRQA S 1534 # Macro is intended for external consumption. */
/** Speed at sensor fixed wrt IMU, unsigned */
#define SPEED_SYS_UNSIGNED 3U	/*PRQA S 1534 # Macro is intended for external consumption. */

//==============================================================================
// \brief Attitude types 

#define ATT_SYS_VOID 0U /*PRQA S 1534 # Macro is intended for external consumption. */
/** Attitude measurement given as Heading, Pitch, Roll in the navigation (NED) frame. */
#define ATT_SYS_HPR 1U       /*PRQA S 1534 # Macro is intended for external consumption. */
/** Attitude measurement given as Heading, Pitch, Roll in a static local reference frame. */
#define ATT_SYS_LOCAL 2U     /*PRQA S 1534 # Macro is intended for external consumption. */

//==============================================================================
// \brief Heading types
#define HEA_SYS_VOID  0U /*PRQA S 1534 # Macro is intended for external consumption. */
// Heading measurement in the navigation frame (NED).
#define HEA_SYS_NAV   1U /*PRQA S 1534 # Macro is intended for external consumption. */
// Heading measurement in a local frame.  
#define HEA_SYS_LOCAL 2U /*PRQA S 1534 # Macro is intended for external consumption. */

//==============================================================================
// \brief Angular Rate types
#define ANG_SYS_VOID   0U /*PRQA S 1534 # Macro is intended for external consumption. */
// Angular Rate measurement in the sensor frame (wx, wy, wz).
#define ANG_SYS_SENSOR 1U /*PRQA S 1534 # Macro is intended for external consumption. */

//==============================================================================
// \brief Location types. (lever arm)
/** Lever arm specified explicitly. */ 
#define LOC_FIXED 0U    /*PRQA S 1534 # Macro is intended for external consumption. */
 /** Take lever arm from kalman filter. -- lever arm is specified in the .gap file. */ 
#define LOC_KF 1U       /*PRQA S 1534 # Macro is intended for external consumption. */
/** Take lever arm from a configured lever arm in the config. */ 
#define LOC_CONFIG 2U   /*PRQA S 1534 # Macro is intended for external consumption. */


//==============================================================================
// \brief Generic aiding data structure 
//
// The data is streamed in the sequence of data members
// The dimension of the data is defined by type, if variable, we will need to define a new sub-structure
// The sequence of data items is fixed (e.g. as given in this structure)

typedef struct /*PRQA S 3630 # This is required to be public as it is to be consumed. */
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

//==============================================================================
// \brief Functions to initialise/destroy/copy

// Non-MISRA compliant mode.

//==============================================================================
// \brief Functions to initialise/destroy/copy

/** Sets all the valid flags to 0
   param gad pointer to GEN_AIDING_DATA
   todo make safe to user passing a NULL pointer
*/
extern int32_t reset_genaid_data(GEN_AIDING_DATA* gad);

extern int32_t reset_gen3d(GEN_3D* d); /*PRQA S 0776 # Assume compiler has greater than 6-character limit for identifier uniqueness. */

/** Initialise a block of memory for GEN_AIDING_DATA
   param gad pointer to start of GEN_AIDING_DATA
*/
extern int32_t initialise_genaid(GEN_AIDING_DATA* gad);

/** Copies the data from one pointer to the other. not safe to dst pointer buffer < sizeof(GEN_AIDING_DATA)
   param dst Pointer to the location the data is being copied to
   param src Pointer to the location of the start of the gen_aiding_data struct
*/
extern int32_t genaid_copy(GEN_AIDING_DATA* dst, const GEN_AIDING_DATA* src);

#endif
