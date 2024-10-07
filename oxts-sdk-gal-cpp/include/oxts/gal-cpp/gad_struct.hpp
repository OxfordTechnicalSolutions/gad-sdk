//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2020 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//!
//! \brief C++ version of gad_struct.h
//!  
//============================================================================================================

#ifndef GAD_STRUCT_HPP
#define GAD_STRUCT_HPP

#include <cstdint>
#include <cstring>
#include <cstdlib>
#include "oxts/gal-cpp/oxts_misra.hpp"

namespace OxTS
{
    namespace Gal_Cpp
    {
        typedef bool   GEN_BOOL;

        //==============================================================================
        //! \brief Encoder types

        ENUM ENCODER_TYPE	/*PRQA S 1120 # Assume C++11*/
        {
            ENCODER_VOID,                    /** Not set. */
            ENCODER_CSV,                     /** Text data. */
            ENCODER_BIN                      /** Binary data. */
        };

        //==============================================================================
        //! \brief Output types.
        
        ENUM OUTPUT_TYPE /*PRQA S 1120 # Assume C++11*/
        {
            OUTPUT_VOID,                    /** Not set. */
            OUTPUT_UDP,                     /** Output via UDP. */
            OUTPUT_FILE                     /** Output to file. */
        };


        //==============================================================================
        //! \brief Variance formats

        ENUM GEN_VAR_TYPE /*PRQA S 1120 # Assume C++11*/
        {
            GEN_VAR_VOID,                   /** Missing. */
            GEN_VAR_SINGLE,                 /** Single variance value. */
            GEN_VAR_DIAG,                   /** Diagonal variance matrix. */
            GEN_VAR_HMAT                    /** Half-matrix (full co-variance matrix). */
        };

        //==============================================================================
        //! \brief Time systems
        ENUM TIME_SYS /*PRQA S 1120 # Assume C++11*/
        {
            TIME_VOID,
            TIME_GPS,            /** Standard GPS time format. */
            TIME_PPS_RELATIVE,   /** Time since PPS. */
            TIME_EST_LATENCY,    /** Not a full timestamp, just an estimate of latency. */
            TIME_SDN,            /** This is internal timing for xbns. (DO NOT USE) */
            TIME_EXT,            /** IN DEVELOPMENT, DO NOT USE */
            TIME_UNIX_UTC,       /** Time since unix epoch, including leap seconds. */
            TIME_TAI             // Time in TAI format
        };

        //==============================================================================
        //! \brief Generic Aiding types

        ENUM GEN_TYPE /*PRQA S 1120 # Assume C++11*/
        {
            GEN_VOID,
            GEN_POS,          /** Position 3D. */
            GEN_RANGE,        /** Range, 1D value, can contain angle of arrival as additional info. */
            GEN_VEL,          /** Velocity 3D. */
            GEN_WSPEED,        /** Wheel Speed */
            GEN_ATT,          /** Attitude. */
            GEN_HEADING,      /** Heading   @note To be merged in GEN_ATT, with ATT specifying in type wherer only heading, or heading+pitch, or heading+pitch+roll are present. */
            GEN_TIMETRIG,     /** Time trigger, used for indoor segment navigation. */
            GEN_SPEED,        /** Wheel Speed */
            GEN_ANGRATE,      /** Angular rate measurement */
            GEN_NUM
        };

        //==============================================================================
        //! \brief Position coordinate systems

        ENUM POS_SYS_TYPE /*PRQA S 1120 # Assume C++11*/
        {
            POS_SYS_VOID,
            POS_SYS_WGS84,        /** WGS84 - lat/lon/depth */
            POS_SYS_LOCAL         /** User defined right-handed local coordinate system - x/y/z */
        };


        //==============================================================================
        //! \brief Velocity types

        ENUM VEL_SYS_TYPE /*PRQA S 1120 # Assume C++11*/
        {
            VEL_SYS_VOID,
            VEL_SYS_NED,             /** North East Down */
            VEL_SYS_ODO,             /** Aiding source frame - x/y/z */
            VEL_SYS_LOCAL            /** User defined right-handed local coordinate system - x/y/z */
        };

        //==============================================================================
        //! \brief Speed types 

        ENUM SPEED_SYS_TYPE /*PRQA S 1120 # Assume C++11*/
        {
            SPEED_SYS_VOID,
            SPEED_SYS_FW_VEL,         /** Forward speed at sensor fixed wrt IMU, speed angle wrt IMU given. */
            SPEED_SYS_BW_VEL,         /** Backwards speed at sensor fixed wrt IMU, speed angle wrt IMU given. */
            SPEED_SYS_UNSIGNED        /** unsigned speed at sensor fixed wrt IMU, speed angle wrt IMU given. */
        };
        //==============================================================================
        //! \brief Attitude types 

        ENUM ATT_SYS_TYPE /*PRQA S 1120 # Assume C++11*/
        {
            ATT_SYS_VOID,
            ATT_SYS_HPR,      /** Attitude measurement given as Heading, Pitch, Roll in the navigation (NED) frame. */
            ATT_SYS_LOCAL     /** Attitude measurement given as Heading, Pitch, Roll in a static local reference frame. */
        };

        //============================================================================================================
        //! \brief Heading types
        ENUM HEA_SYS_TYPE /*PRQA S 1120 # Assume C++11*/
        {
            HEA_SYS_VOID,
            HEA_SYS_NAV,        // Heading measurement in the navigation frame (NED).
            HEA_SYS_LOCAL       // Heading measurement in a local frame. 
        };

        //============================================================================================================
        //! \brief Angular Rate types
        ENUM ANG_SYS_TYPE /*PRQA S 1120 # Assume C++11*/
        {
            ANG_SYS_VOID,
            ANG_SYS_SENSOR        // Angular Rate measurement in the sensor frame (wx, wy, wz | deg/s).
        };

        //==============================================================================
        //! \brief Location types. (lever arm)
        ENUM LOC_SYS /*PRQA S 1120 # Assume C++11*/
        {
            LOC_FIXED = 0,    /** Lever arm specified explicitly. */
            LOC_KF = 1,       /** Take lever arm from kalman filter. -- lever arm is specified in the .gap file. */
            LOC_CONFIG = 2    /** Take lever arm from a configured lever arm in the config. */
        };
    }
}

#endif
