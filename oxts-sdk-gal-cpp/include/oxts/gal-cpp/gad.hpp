#ifndef GAD_HPP
#define GAD_HPP
/*! @file gad.hpp */

#include "oxts/gal-cpp/gad_struct.hpp"
#include "oxts/gal-cpp/oxts_misra.hpp"

namespace OxTS
{
	namespace Gal_Cpp
	{
		typedef GEN_BOOL GenFlag;
		/**
		 * Cpp equivalent class for C struct GEN_3D.
		 *
		 * Provides an interface for concrete data structures used in Gad.
		 */
		class Gen3d /*PRQA S 2213 # Ignore QAC*//*PRQA S 2211 # Ignore QAC*/
		{
		private:
			uint8_t        m_mode;        /** ID */
			uint8_t        m_x_type;      /** Type of value x, e.g. coord system */
			container_double3_t m_x;      /** Values */
			uint8_t        m_v_type;      /** Variance type see GEN_VAR_TYPE */
			container_double6_t m_v;	  /**Vector representation in the given GEN_VAR_TYPE.*/
		public:
			/*! Default Constructor */
			Gen3d();
			/*! Copy constructor */
			Gen3d(const Gen3d& g);
			/** Copy assignment operator. */
			Gen3d& operator=(const Gen3d& g);
#ifdef OXTS_ENABLE_CPP11
			/*! Move constructor. */
			Gen3d(Gen3d&& g);	/*PRQA S 1127 # Assume C++11. */
			/** Move assignment operator. */
			Gen3d& operator=(Gen3d&& g);	/*PRQA S 1127 # Assume C++11. */
#endif
			// Accessor functions 
			/*! Set the struct mode. Typically set to 0.*/
			void SetMode(const uint8_t mode);
			/*! Set the struct mode.*/
			uint8_t GetMode() const;
			/** Set the value type. Index source depends on use of the struct. Sources
			 *  include ::POS_SYS_TYPE, ::VEL_SYS_TYPE, ::SPEED_SYS_TYPE, ::LOC_SYS.
			 */
			void SetValType(const uint8_t x_type);
			/*! Get the value type. See ::GetMode() for indexes */
			uint8_t GetValType() const;

			void SetValX(const double_t x);
			double_t GetValX() const;
			void SetValY(const double_t y);
			double_t GetValY() const;
			void SetValZ(const double_t z);
			double_t GetValZ() const;
			/*! Set the value array. Used to store the aiding data.*/
			void SetVal(const double_t x, const double_t y);
			void SetVal(const double_t x, const double_t y, const double_t z);
			const container_double3_t &GetVal() const;

			uint8_t GetVarType() const;
			void SetVarUpperDiag(const double_t v_00, const double_t v_11, const double_t v_22,
				const double_t v_01, const double_t v_02, const double_t v_12);
			void SetVarDiag(const double_t v_00, const double_t v_11, const double_t v_22);
			void SetVarSingle(const double_t v_0);
			const container_double6_t &GetVar() const;

		};


		/**
		 * Cpp wrapper class for C struct GEN_AIDING_DATA
		 */
		class Gad /*PRQA S 2219 # Ignore QAC*/ /*PRQA S 2213 # Ignore QAC*//*PRQA S 2211 # Ignore QAC*/
		{
		private:
			/** Type of Aiding (position, velocity, ...). For enumerated values see
			 * GEN_TYPE.
			 */
			int8_t        m_type;
			/** Aiding stream ID to identify the source device.
			 *  Values 129-254. Each stream should have a unique ID.
			 */
			uint8_t       m_stream_id;
			/** Sub-struct VALUE. Contains navigation aiding data. */
			Gen3d         m_val_data;
			GenFlag       m_val_valid;
			/** Sub-struct TIME. Contains the time the data was recorded. */
			Gen3d         m_time_data;
			GenFlag       m_time_valid;
			/** Sub-struct LOCATION. Contains lever arm (or alignment) data between the
			 * IMU and aiding source.
			 */
			Gen3d         m_loc_data;
			GenFlag       m_loc_valid;
			// Sub-struct RESERVED
			Gen3d         m_res1_data;
			GenFlag       m_res1_valid;
			// Sub-struct RESERVED
			Gen3d         m_res2_data;
			GenFlag       m_res2_valid;
			/**
			 * Acquisition Time Stamp. The INS will fill in this timestamp upon its
			 * arrival to the INS. Leave blank.
			 */
			uint32_t      m_acq_data;                 // Timestamp from INS. Leave empty.
			GenFlag       m_acq_valid;
		protected:
			// type 
			void SetDataType(const int8_t _type);
			// val
			/** Set Time Valid flag
			 * @param flag boolean to indicate whether time is valid or invalid
			 */
			void SetValValid(const bool flag);
			/** Set Time Valid flag
			* @return flag boolean to indicate whether time validity
			*/
			void SetDataMode(const uint8_t mode);
			void SetDataValType(const uint8_t x_type);
			void SetDataVal(const double_t x_0, const double_t x_1);
			void SetDataVal(const double_t x_0, const double_t x_1, const double_t x_2);
			const container_double3_t&GetDataVal() const;
			void SetDataVarUpperDiag(const double_t v_00, const double_t v_11, const double_t v_22,
				const double_t v_01, const double_t v_02, const double_t v_12);
			void SetDataVarDiag(const double_t v_00, const double_t v_11, const double_t v_22);
			void SetDataVarSingle(const double_t v_0);
			const container_double6_t&GetDataVar() const;
			// loc  
			void SetLocValid(const bool flag);
			void SetLocMode(const uint8_t mode);
			void SetLocValType(const uint8_t x_type);
			void SetLocVal(const double_t x_0, const double_t x_1, const double_t x_2);
			const container_double3_t&GetLocVal() const;
			void SetLocVarUpperDiag(const double_t v_00, const double_t v_11, const double_t v_22,
				const double_t v_01, const double_t v_02, const double_t v_12);
			void SetLocVarDiag(const double_t v_00, const double_t v_11, const double_t v_22);
			void SetLocVarSingle(const double_t v_0);
			const container_double6_t&GetLocVar() const;

		public:
			/*! Default Constructor */
			Gad();
			/*! Constructor */
			Gad(const uint8_t stream_id, const int8_t aiding_type);
			/*! Destructor */
			virtual ~Gad();
			/*! Copy constructor */
			Gad(const Gad& g);
			// Copy assignment operator */
			Gad& operator=(const Gad& g);
#ifdef OXTS_ENABLE_CPP11
			/*! Move constructor */
			Gad(Gad&& g);	/*PRQA S 1127 # Assume C++11 */
			/*! Move assignment operator. */
			Gad& operator=(Gad&& g);	/*PRQA S 1127 # Assume C++11 */
#endif
			// General Accessors
			/** Set Stream ID for this GAD packet */
			void SetStreamId(const uint8_t id);
			/** Get Stream ID for this GAD packet */
			uint8_t GetStreamId() const;

			// Time accessors
			/** Set Time Valid flag
			 * @param flag boolean to indicate whether time is valid or invalid
			 */
			void SetTimeValid(const bool flag);
			/** Set Time Valid flag
			* @return flag boolean to indicate whether time validity
			*/
			const bool GetTimeValid() const;
			/** Set time from an external clock
			 * @param week Week in the external time frame
			 * @param seconds Seconds in the external time frame
			 */
			void SetTimeExternal(const double_t week, const double_t secs);
			/** Get the week in the external time */
			double_t GetTimeExternalWeek() const;
			/** Get the seconds into the week in the external time */
			double_t GetTimeExternalSecondsFromSunday() const;
			const container_double3_t& GetTimeExternal() const;
			/** Set timestamp for this data
			 * @param week GPS Week
			 * @param seconds_from_sunday Seconds from Midnight Sunday (s)
			 */
			void SetTimeGps(const double_t week, const double_t seconds_from_sunday);
			const container_double3_t& GetTimeGps() const;
			/** Get the GPS Week value. Note that this function assumes that
			 *  the time has been set in this format, there is no check. */
			double_t GetTimeGpsWeek() const;
			/** Get the Seconds from Sunday value. Note that this function assumes that
			 *  the time has been set in this format, there is no check. */
			double_t GetTimeGpsSecondsFromSunday() const;
			/** Set a PPS relative timestamp
			 * @param ns Time since PPS timestamp (nanoseconds)
			 */
			 /*Set TAI timestamp in seconds*/
			void SetTimeTAI(const double_t secs);
			/** Get TAI timestamp.  */
			double_t GetTimeTAI() const;

			void SetTimePpsRelative(const double_t ns);
			double_t GetTimePpsRelative() const;
			/**
			 * Set the timestamp type for this data to Latency. The latency is an estimate
			 * of the time taken for the packet to travel from the aiding source to the
			 * INS. Upon arrival the INS will timestamp the data, adjusting for the
			 * latency.
			 * @param ns Latency estimate in (seconds).
			 */
			void SetTimeLatency(const double_t secs);
			/** Get latency estimate.   */
			double_t GetTimeLatency() const;
			/** Set the timestamp as UTC time encoded as the number of seconds from the UNIX epoch.
			*  @param secs Time since unic epoch including leap seconds (seconds).
			*/
			void SetTimeUTCUnix(const double_t secs);
			/** Get unix timestamp.  */
			double_t GetTimeUTCUnix() const;
			/**
			 * Set the timestamp type for this data to void. Data with a void timestamp
			 * will be timestamped by the INS upon receipt.
			 */
			void SetTimeVoid();

			int8_t GetType() const;
			const bool GetValValid() const;
			int8_t  GetDataType() const;
			const bool GetLocValid() const;
			void SetRes1Valid(const bool flag);
			const bool GetRes1Valid() const;
			void SetRes2Valid(const bool flag);
			const bool GetRes2Valid() const;

			const Gen3d& GetTime() const;
			const Gen3d& GetVal() const;
			const Gen3d& GetLoc() const;
			const Gen3d& GetRes1() const;
			const Gen3d& GetRes2() const;

			// Acquisiton time accessors.
			void SetAcqValid(const bool flag);
			const bool GetAcqValid() const;
			/*! Set the acquisition time of the data. Not to be used outside of the INS.*/
			void SetAcqTimestamp(const uint32_t acq_time);
			/*! Get the acquisition time of the data. Not expected to be set outside of the INS.*/
			uint32_t  GetAcqTimestamp() const;

		};

		/**
		 * Generic Aiding position.
		 */
		class GadPosition : public Gad /*PRQA S 1755 # Rule-0_1_5 should not apply as this is to be consumed by 3rd party. */
		{
		private:

		public:
			/**
			 * Constructor
			 *
			 * @param stream_id Stream ID for the position aiding source. Must be unique 129-254.
			 */
			explicit GadPosition(const uint8_t stream_id);
			/**
			 * Set the aiding position in the WGS84 coordinate frame.
			 * @param lat Latitude of the position estimate (deg).
			 * @param lon Longitude of the position estimate (deg).
			 * @param alt Altitude of the position estimate (deg).
			 */
			void SetPosGeodetic(const double_t lat, const double_t lon, const double_t alt);
			/**
			 * Set the aiding position in the user-defined local coordinate frame.
			 * @param x Position in the x axis of the local frame (m).
			 * @param y Position in the y axis of the local frame (m).
			 * @param z Position in the z axis of the local frame (m).
			 */
			void SetPosLocal(const double_t x, const double_t y, const double_t z);
			/**
			 * Get the aiding position.
			 */
			const container_double3_t& GetPos() const;
			/**
			 * Set the variance aiding position in the coordinate frame.
			 * @param var_north Variance of the position estimate (m^2).
			 * @param var_east  Variance of the position estimate (m^2).
			 * @param var_down  Variance of the position estimate (m^2).
			 */
			void SetPosGeodeticVar(const double_t var_north, const double_t var_east, const double_t var_down);
			/**
			 * Set the full covariance matrix of aiding position in the geodetic
			 * coordinate frame. Only six values required due to the symmetry of
			 * covariance matrices. (Indices row major)
			 * @param v_00 Variance of the position estimate (m^2).
			 * @param v_11 Variance of the position estimate (m^2).
			 * @param v_22 Variance of the position estimate (m^2).
			 * @param v_01 Variance of the position estimate (m^2).
			 * @param v_02 Variance of the position estimate (m^2).
			 * @param v_12 Variance of the position estimate (m^2).
			 */
			void SetPosGeodeticVar(
				const double_t v_00, const double_t v_11, const double_t v_22,
				const double_t v_01, const double_t v_02, const double_t v_12
			);
			/**
			 * Set the variance aiding position in the coordinate frame.
			 * @param var_local_x Variance of the position estimate (m^2).
			 * @param var_local_y Variance of the position estimate (m^2).
			 * @param var_local_z Variance of the position estimate (m^2).
			 */
			void SetPosLocalVar(const double_t var_local_x, const double_t var_local_y, const double_t var_local_z);
			/**
			 * Set the full covariance matrix of aiding position in the local
			 * coordinate frame. Only six values required due to the symmetry of
			 * covariance matrices. (Indices row major)
			 * @param v_00 Variance of the position estimate (m^2).
			 * @param v_11 Variance of the position estimate (m^2).
			 * @param v_22 Variance of the position estimate (m^2).
			 * @param v_01 Variance of the position estimate (m^2).
			 * @param v_02 Variance of the position estimate (m^2).
			 * @param v_12 Variance of the position estimate (m^2).
			 */
			void SetPosLocalVar(
				const double_t v_xx, const double_t v_yy, const double_t v_zz,
				const double_t v_xy, const double_t v_xz, const double_t v_yz
			);
			/**
			 * Get the aiding position variance.
			 */
			const container_double6_t& GetPosVar() const;
			/**
			 * Set lever arm from the INS to the aiding source. This lever arm will not be
			 * optimised by the Kalman Filter.
			 *
			 * @param x Offset from INS to aiding source in the x axis of the IMU frame (m).
			 * @param y Offset from INS to aiding source in the y axis of the IMU frame (m).
			 * @param z Offset from INS to aiding source in the z axis of the IMU frame (m).
			 */
			void SetAidingLeverArmFixed(const double_t x, const double_t y, const double_t z);
			const container_double3_t& GetAidingLeverArm() const;
			/**
			 * Set lever arm from the INS to the position aiding source. to be
			 * optimised by the Kalman Filter during navigation.
			 */
			void SetAidingLeverArmOptimising();
			/**
			 * Indicate that lever arm will be configured in the configuration file on
			 * the INS.
			 */
			void SetAidingLeverArmConfig();
			/**
			 * Set the variance (accuracy) of the lever arm measurements from the INS to
			 * the aiding source. Only required for fixed lever-arm.
			 *
			 * @param x Variance on the lever arm from INS to aiding source in the x axis of the IMU frame.
			 * @param y Variance on the lever arm from INS to aiding source in the y axis of the IMU frame.
			 * @param z Variance on the lever arm from INS to aiding source in the z axis of the IMU frame.
			 */
			void SetAidingLeverArmVar(const double_t x, const double_t y, const double_t z);
			const container_double6_t& GetAidingLeverArmVar() const;
		};

		/**
		 * Generic Aiding velocity.
		 */
		class GadVelocity : public Gad /*PRQA S 1755 # Rule-0_1_5 should not apply as this is to be consumed by 3rd party. */
		{
		private:

		public:
			/**
			 * Constructor
			 *
			 * @param stream_id Stream ID for the velocity aiding source. Must be unique 129-254.
			 */
			explicit GadVelocity(const uint8_t stream_id);
			/**
			 * Set the aiding velocity estimate in the local NED coordinate frame.
			 * @param vel_east Velocity estimate in the East direction (m/s).
			 * @param vel_north Velocity estimate in the North direction (m/s).
			 * @param vel_down Velocity estimate in the Down direction (m/s).
			 */
			void SetVelNed(const double_t vel_north, const double_t vel_east, const double_t vel_down);
			/**
			 * Set the aiding velocity estimate in the odometry frame.
			 * @param vel_x Velocity estimate in the x direction (m/s).
			 * @param vel_y Velocity estimate in the y direction (m/s).
			 * @param vel_z Velocity estimate in the z direction (m/s).
			 */
			void SetVelOdom(const double_t vel_x, const double_t vel_y, const double_t vel_z);
			/**
			 * Set the aiding velocity estimate in the user-defined local coordinate frame.
			 * @param vel_local_x Velocity estimate in the x direction (m/s).
			 * @param vel_local_y Velocity estimate in the y direction (m/s).
			 * @param vel_local_z Velocity estimate in the z direction (m/s).
			 */
			void SetVelLocal(const double_t vel_local_x, const double_t vel_local_y, const double_t vel_local_z);
			/**
			 * Get the aiding velocity estimate.
			 */
			const container_double3_t& GetVel() const;
			/**
			 * Set the aiding velocity variance estimate in the local NED coordinate frame.
			 * @param var_north Velocity variance estimate in the North direction (m/s)^2.
			 * @param var_east  Velocity variance estimate in the East direction (m/s)^2.
			 * @param var_down  Velocity variance estimate in the Down direction (m/s)^2.
			 */
			void SetVelNedVar(const double_t var_north, const double_t var_east, const double_t var_down);
			/**
			 * Set the full covariance matrix of aiding velocity in the NED
			 * frame. Only six values required due to the symmetry of
			 * covariance matrices. (Indices row major)
			 * @param v_nn Variance of the position estimate (m/s)^2.
			 * @param v_ee Variance of the position estimate (m/s)^2.
			 * @param v_uu Variance of the position estimate (m/s)^2.
			 * @param v_ne Variance of the position estimate (m/s)^2.
			 * @param v_nu Variance of the position estimate (m/s)^2.
			 * @param v_eu Variance of the position estimate (m/s)^2.
			 */
			void SetVelNedVar(
				const double_t v_nn, const double_t v_ee, const double_t v_dd,
				const double_t v_ne, const double_t v_nd, const double_t v_ed
			);
			/**
			 * Set the aiding velocity variance estimate in the local NED coordinate frame.
			 * @param v_x Velocity variance estimate in the x direction (m/s)^2.
			 * @param v_y Velocity variance estimate in the y direction (m/s)^2.
			 * @param v_z Velocity variance estimate in the z direction (m/s)^2.
			 */
			void SetVelOdomVar(const double_t v_x, const double_t v_y, const double_t v_z);
			/**
			 * Set the full covariance matrix of aiding velocity in the odometry
			 * frame. Only six values required due to the symmetry of
			 * covariance matrices. (Indices row major)
			 * @param v_xx Variance of the position estimate (m/s)^2.
			 * @param v_yy Variance of the position estimate (m/s)^2.
			 * @param v_zz Variance of the position estimate (m/s)^2.
			 * @param v_xy Variance of the position estimate (m/s)^2.
			 * @param v_xz Variance of the position estimate (m/s)^2.
			 * @param v_yz Variance of the position estimate (m/s)^2.
			 */
			void SetVelOdomVar(
				const double_t v_xx, const double_t v_yy, const double_t v_zz,
				const double_t v_xy, const double_t v_xz, const double_t v_yz
			);
			/**
			 * Set the aiding velocity variance estimate in the local NED coordinate frame.
			 * @param v_x Velocity variance estimate in the x direction (m/s)^2.
			 * @param v_y Velocity variance estimate in the y direction (m/s)^2.
			 * @param v_z Velocity variance estimate in the z direction (m/s)^2.
			 */
			void SetVelLocalVar(const double_t v_x, const double_t v_y, const double_t v_z);
			/**
			 * Set the full covariance matrix of aiding velocity in the local
			 * coordinate frame. Only six values required due to the symmetry of
			 * covariance matrices. (Indices row major)
			 * @param v_xx Variance of the position estimate (m^2).
			 * @param v_yy Variance of the position estimate (m^2).
			 * @param v_zz Variance of the position estimate (m^2).
			 * @param v_xy Variance of the position estimate (m^2).
			 * @param v_xz Variance of the position estimate (m^2).
			 * @param v_yz Variance of the position estimate (m^2).
			 */
			void SetVelLocalVar(
				const double_t v_xx, const double_t v_yy, const double_t v_zz,
				const double_t v_xy, const double_t v_xz, const double_t v_yz
			);
			/**
			 * Get the aiding velocity variance estimate.
			 */
			const container_double6_t& GetVelVar() const;
			/**
			 * Set lever arm from the INS to the aiding source. This lever arm will not be
			 * optimised by the Kalman Filter.
			 *
			 * @param x Offset from INS to aiding source in the x axis of the IMU frame (m).
			 * @param y Offset from INS to aiding source in the y axis of the IMU frame (m).
			 * @param z Offset from INS to aiding source in the z axis of the IMU frame (m).
			 */
			void SetAidingLeverArmFixed(const double_t x, const double_t y, const double_t z);
			const container_double3_t& GetAidingLeverArm() const;
			/**
			 * Set lever arm from the INS to the aiding source to be taken from the .gap
			 * file. This lever arm will be optimised by the Kalman Filter during
			 * navigation. Note that if using this, the GNSS antenna lever arm must be set
			 * in mobile.cfg.
			 */
			void SetAidingLeverArmOptimising();
			/**
			 * Indicate that lever arm will be configured in the configuration file on
			 * the INS.
			 * @todo Remove and set this mode to be default
			 */
			void SetAidingLeverArmConfig();
			/**
			 * Set the variance (accuracy) of the lever arm measurements from the INS to
			 * the aiding source.
			 *
			 * @param x Variance on the lever arm from INS to aiding source in the x axis of the IMU frame.
			 * @param y Variance on the lever arm from INS to aiding source in the y axis of the IMU frame.
			 * @param z Variance on the lever arm from INS to aiding source in the z axis of the IMU frame.
			 */
			void SetAidingLeverArmVar(const double_t x, const double_t y, const double_t z);
			const container_double6_t& GetAidingLeverArmVar() const;
		};

		/**
		 * Generic Aiding Wheelspeed (Legacy).
		 */
		class GadWheelSpeed : public Gad /*PRQA S 1755 # Rule-0_1_5 should not apply as this is to be consumed by 3rd party. */
		{
		private:

		public:
			explicit GadWheelSpeed(const uint8_t stream_id);

			/**
			 * Set the forward wheelspeed aiding estimate.
			 *
			 * @param wheelspeed Forward wheelspeed estimate in the vehicle frame (m/s).
			 */
			void SetWheelSpeedFw(const double_t wheelspeed);
			double_t GetWheelSpeedFw() const;
			/**
			 * Set estimated variance on the forward wheelspeed aiding measurement.
			 *
			 * @param v_s Forward wheelspeed estimate in the vehicle frame (units).
			 */
			void SetWheelSpeedFwVar(const double_t v_s);
			double_t GetWheelSpeedFwVar() const;
			/**
			 * Set the pulse count measurement from a wheelspeed encoder.
			 *
			 * @param count Number of pulses recorded during the period.
			 * @param period The period over which the current pulse count was recorded.
			 *
			 * @todo Clarify where the timestamp should correspond to in the period:
			 * start, middle, end.
			 */
			void SetWheelSpeedCount(const double_t count, const double_t period);
			const container_double3_t& GetWheelSpeedCount() const;
			/**
			 * Set the estimated variance on the wheelspeed pulse count.
			 *
			 * @param v_c Estimated variance (pulses).
			 * @todo Clarify units
			 */
			void SetWheelSpeedVar(const double_t v_c);
			double_t GetWheelSpeedVar() const;
			/**
			 * Set lever arm from the INS to the aiding source. This lever arm will not be
			 * optimised by the Kalman Filter.
			 *
			 * @param x Offset from INS to aiding source in the x axis of the IMU frame (m).
			 * @param y Offset from INS to aiding source in the y axis of the IMU frame (m).
			 * @param z Offset from INS to aiding source in the z axis of the IMU frame (m).
			 */
			void SetAidingLeverArmFixed(const double_t x, const double_t y, const double_t z);
			const container_double3_t& GetAidingLeverArm() const;
			/**
			 * Set lever arm from the INS to the aiding source to be taken from the .gap
			 * file. This lever arm will be optimised by the Kalman Filter during
			 * navigation. Note that if using this, the GNSS antenna lever arm must be set
			 * in mobile.cfg.
			 */
			void SetAidingLeverArmOptimising();
			/**
			 * Indicate that lever arm will be configured in the configuration file on
			 * the INS.
			 * @todo Remove and set this mode to be default
			 */
			void SetAidingLeverArmConfig();
			/**
			 * Set the variance (accuracy) of the lever arm measurements from the INS to
			 * the aiding source.
			 *
			 * @param x Variance on the lever arm from INS to aiding source in the x axis of the IMU frame.
			 * @param y Variance on the lever arm from INS to aiding source in the y axis of the IMU frame.
			 * @param z Variance on the lever arm from INS to aiding source in the z axis of the IMU frame.
			 */
			void SetAidingLeverArmVar(const double_t x, const double_t y, const double_t z);
			const container_double6_t& GetAidingLeverArmVar() const;
		};

		/**
		* Generic Aiding speed.
		*/
		class GadSpeed : public Gad /*PRQA S 1755 # Rule-0_1_5 should not apply as this is to be consumed by 3rd party. */
		{
		private:

		public:
			explicit GadSpeed(const uint8_t stream_id);

			/**
			 * Set the forward speed aiding estimate.
			 *
			 * @param speed Forward speed estimate in the vehicle frame (m/s).
			 */
			void SetSpeedFwMs(const double_t speed);
			/**
			 * Set the backward speed aiding estimate.
			 *
			 * @param speed Backward speed estimate in the vehicle frame (m/s).
			 */
			void SetSpeedBwMs(const double_t speed);
			/**
			 * Set an unsigned speed aiding estimate.
			 *
			 * @param speed Unsigned speed estimate in the vehicle frame (m/s).
			 */
			void SetSpeedUnMs(const double_t speed);
			/**
			 * Set the forward pulsed speed aiding estimate.
			 *
			 * @param frequency Pulse frequency in the forward vehicle direction (counts/s).
			 * @param scale_factor Scale factor converting counts to m, e.g. 0.01 for 100 counts/m. (m)
			 * @param(optional) period Time over which the speed measurement is taken (if known) (s).
			 */
			void SetSpeedFwPulsed(const double_t frequency, const double_t scale_factor, const double_t period = 0.0);
			/**
			* Set the backward pulsed speed aiding estimate.
			*
			* @param frequency Pulse frequency in the backward vehicle direction (counts/s).
			* @param scale_factor Scale factor converting counts to m, e.g. 0.01 for 100 counts/m. (m)
			* @param(optional) period Time over which the speed measurement is taken (if known) (s).
			*/
			void SetSpeedBwPulsed(const double_t frequency, const double_t scale_factor, const double_t period = 0.0);
			/**
			 * Set an unsigned pulsed speed aiding estimate.
			 *
			 * @param frequency Unsigned pulse frequency (counts/s).
			 * @param scale_factor Scale factor converting counts to m, e.g. 0.01 for 100 counts/m. (m)
			 * @param(optional) period Time over which the speed measurement is taken (if known) (s).
			 */
			void SetSpeedUnPulsed(const double_t frequency, const double_t scale_factor, const double_t period = 0.0);
			/**
			 * Get the aiding speed estimate.
			 */
			const container_double3_t& GetSpeed() const;
			/**
			 * Set estimated variance on the speed aiding measurement.
			 *
			 * @param v_s Estimated variance on the speed measurement ((m/s)^2).
			 */
			void SetSpeedMsVar(const double_t v_s);
			/**
			 * Set the aiding speed variance estimate including scale factor and period
			 * @param v_s Pulse frequency variance estimate (variance on the measurement) (s^-2).
			 * @param v_sf Scale factor variance estimate (m^-2).
			 */
			void SetSpeedPulsedVar(const double_t v_s, const double_t v_sf);
			/**
			 * Set the aiding speed variance estimate including scale factor and period
			 * @param v_s Pulse frequency variance estimate (variance on the measurement) (s^-2).
			 * @param v_sf Scale factor variance estimate (m^-2).
			 * @param v_p Period variance estimate (s^2).
			 */
			void SetSpeedPulsedVarPeriod(const double_t v_s, const double_t v_sf, const double_t v_p);
			/**
			 * Get the aiding speed variance estimate.
			 */
			const container_double6_t& GetSpeedVar() const;
			/**
			 * Set lever arm from the INS to the aiding source. This lever arm will not be
			 * optimised by the Kalman Filter.
			 *
			 * @param x Offset from INS to aiding source in the x axis of the IMU frame (m).
			 * @param y Offset from INS to aiding source in the y axis of the IMU frame (m).
			 * @param z Offset from INS to aiding source in the z axis of the IMU frame (m).
			 */
			void SetAidingLeverArmFixed(const double_t x, const double_t y, const double_t z);
			const container_double3_t& GetAidingLeverArm() const;
			/**
			 * Indicate that lever arm will be configured in the configuration file on
			 * the INS.
			 * @todo Remove and set this mode to be default
			 */
			void SetAidingLeverArmConfig();
			/**
			 * Set the variance (accuracy) of the lever arm measurements from the INS to
			 * the aiding source.
			 *
			 * @param x Variance on the lever arm from INS to aiding source in the x axis of the IMU frame.
			 * @param y Variance on the lever arm from INS to aiding source in the y axis of the IMU frame.
			 * @param z Variance on the lever arm from INS to aiding source in the z axis of the IMU frame.
			 */
			void SetAidingLeverArmVar(const double_t x, const double_t y, const double_t z);
			const container_double6_t& GetAidingLeverArmVar() const;
		};

		/**
		 * Generic Aiding attitude.
		 */
		class GadAttitude : public Gad /*PRQA S 1755 # Rule-0_1_5 should not apply as this is to be consumed by 3rd party. */
		{
		public:
			/**
			 * Default constructor
			 */
			GadAttitude();
			/** Constructor.
			 *  @param stream_id Stream ID for the attitude aiding source. Must be unique 129-254.
			 */
			explicit GadAttitude(const uint8_t stream_id);
			const container_double3_t& GetAtt() const;
			// val
			/**
			 * Set the aiding attitude measurement relative to the NED coordinate frame.
			 * @param heading
			 * @param pitch
			 * @param roll
			 *
			 * @note All parameters are in degrees. Roll is not yet used!
			 */
			void SetAtt(const double_t heading, const double_t pitch, const double_t roll);
			/**
			* Set the aiding attitude measurement relative to the local coordinate frame.
			* @param heading
			* @param pitch
			* @param roll
			* @note All parameters are in degrees. Roll is not yet used!
			*/
			void SetAttLocal(const double_t heading, const double_t pitch, const double_t roll);
			/**
			 * Set the estimated variance on the aiding attitude measurement.
			 * @param v_h Variance estimate on the heading angle (deg)^2
			 * @param v_p Variance estimate on the pitch angle (deg)^2
			 * @param v_r Variance estimate on the roll angle (deg)^2
			 */
			void SetAttVar(const double_t v_h, const double_t v_p, const double_t v_r);
			const container_double6_t &GetAttVar() const;
			// /**
			//  * Set the angles which specify the rotation required to align the IMU and 
			//  * aiding sensor frames. This alignment will not be optimised by the INS.
			//  * @param x
			//  * @param y
			//  * @param z
			//  */
			void SetAidingAlignmentFixed(const double_t x, const double_t y, const double_t z);
			const container_double3_t& GetAidingAlignment() const;
			/**
			 * Set alignment to be optimised by the INS. The alignment values will be read
			 * from the mobile.att file, so are not set here.
			 */
			void SetAidingAlignmentOptimising();
			/**
			 * Indicate that alignment will be configured in the configuration file on
			 * the INS.
			 */
			void SetAidingAlignmentConfig();
			/**
			 * Set the estimated variance (error) on the alignment angles between the IMU
			 * and aiding sensor frames.
			 * @param x
			 * @param y
			 * @param z
			 */
			void SetAidingAlignmentVar(const double_t x, const double_t y, const double_t z);
			const container_double6_t& GetAidingAlignmentVar() const;
		};

		/**
		 * Generic Aiding Heading.
		 */
		class GadHeading : public Gad /*PRQA S 1755 # Rule-0_1_5 should not apply as this is to be consumed by 3rd party. */
		{
		public:
			/**
			 * Default constructor
			 */
			GadHeading();
			/** Constructor.
			 *  @param stream_id Stream ID for the attitude aiding source. Must be unique 128-254.
			 */
			explicit GadHeading(const uint8_t stream_id);
			double_t GetHeading() const;
			// val
			/**
			 * Set the aiding heading measurement relative to the NED coordinate frame.
			 * @param heading
			 */
			void SetHeading(const double_t heading);

			/**
			 * Set the aiding heading measurement relative to the local coordinate frame.
			 * @param heading
			 */
			void SetHeadingLocal(const double_t heading);
			/**
			 * Set the estimated variance on the aiding attitude measurement.
			 * @param v_h Variance estimate on the heading angle (deg)^2
			 */
			void SetHeadingVar(const double_t v_h);
			double_t GetHeadingVar() const;
			/**
			 * Set the angles which specify the rotation required to align the IMU and
			 * aiding sensor frames. This alignment will not be optimised by the INS.
			 * @param h
			 * @param p
			 * @param r
			 */
			void SetAidingAlignmentFixed(const double_t h, const double_t p, const double_t r);
			const container_double3_t& GetAidingAlignment() const;
			/**
			 * Indicate that alignment will be configured in the configuration file on
			 * the INS.
			 */
			void SetAidingAlignmentConfig();
			/**
			 * Set the estimated variance (error) on the alignment angles between the IMU
			 * and aiding sensor frames.
			 * @param h_v
			 * @param h_p
			 * @param h_r
			 */
			void SetAidingAlignmentVar(const double_t h_v, const double_t p_v, const double_t r_v);
			const container_double6_t& GetAidingAlignmentVar() const;
		};

		/**
		 * (EXPERIMENTAL) Generic Aiding Angular Rate.
		 */
		class GadAngularRate : public Gad
		{
		public:
			/**
			 * Default constructor
			 */
			GadAngularRate();
			/** Constructor.
			 *  @param stream_id Stream ID for the attitude aiding source. Must be unique 128-254.
			 */
			explicit GadAngularRate(uint8_t stream_id);
			const container_double3_t& GetAngularRate() const;
			// val
			/**
			 * Set the angular rate measurement relative to the sensor frame.
			 * @param wx (deg/s)
			 * @param wy (deg/s)
			 * @param wz (deg/s)
			 */
			void SetAngularRate(double_t wx, double_t wy, double_t wz);
			/**
			 * Set the estimated variance on the angular rate measurement.
			 * @param v_wx Variance estimate on the angular rate around the X axis (deg)^2
			 * @param v_wy Variance estimate on the angular rate around the Y axis (deg)^2
			 * @param v_wz Variance estimate on the angular rate around the Z axis (deg)^2
			 */
			void SetAngularRateVar(double_t v_wx, double_t v_wy, double_t v_wz);
			const container_double6_t& GetAngularRateVar() const;
			/**
			 * Set the angles which specify the rotation required to align the IMU and 
			 * aiding sensor frames. This alignment will not be optimised by the INS.
			 * @param h
			 * @param p
			 * @param r
			 */
			void SetAidingAlignmentFixed(double_t h, double_t p, double_t r);
			/** 
			 * Indicate that alignment will be configured in the configuration file on
			 * the INS.
			*/
			void SetAidingAlignmentConfig();
			
			const container_double3_t& GetAidingAlignment() const;
			/**
			 * Set the estimated variance (error) on the alignment angles between the IMU
			 * and aiding sensor frames.
			 * @param v_h
			 * @param v_p
			 * @param v_r
			 */
			void SetAidingAlignmentVar(double_t v_h, double_t v_p, double_t v_r);
			const container_double6_t& GetAidingAlignmentVar() const;
		};

	} // namespace gal_cpp
} // namespace oxts



#endif // GAD_HPP
