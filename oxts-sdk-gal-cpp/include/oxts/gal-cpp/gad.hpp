#ifndef GAD_HPP
#define GAD_HPP
/*! @file gad.hpp */

#include <vector>

#include "oxts/gal-c/gad_struct.h"

namespace OxTS
{
	using GenFlag = GEN_BOOL;
	/**
	 * Cpp wrapper class for C struct GEN_3D.
	 *
	 * Provides an interface for concrete data structures used in Gad.
	 */
	class Gen3d : public GEN_3D
	{
	public:
		/*! Default Constructor */
		Gen3d();
		/*! Destructor */
		~Gen3d() = default;
		/*! Copy constructor */
		explicit Gen3d(const GEN_3D& g);

		/*! Implicit conversion from Gen3d to GEN_3D* */
		explicit operator ::GEN_3D* () { return this; }
		/*! Implicit const conversion from Gen3d to GEN_3D* */
		explicit operator const ::GEN_3D* () const { return this; }


		GEN_3D getCStruct() const;

		// Accessor functions 
		/*! Set the struct mode. Typically set to 0.*/
		void SetMode(int mode);
		/*! Set the struct mode.*/
		int GetMode() const;
		/** Set the value type. Index source depends on use of the struct. Sources
		 *  include ::POS_SYS_TYPE, ::VEL_SYS_TYPE, ::SPEED_SYS_TYPE, ::LOC_SYS.
		 */
		void SetValType(int x_type);
		/*! Get the value type. See ::GetMode() for indexes */
		int GetValType() const;

		void SetValX(double x);
		double GetValX() const;
		void SetValY(double y);
		double GetValY() const;
		void SetValZ(double z);
		double GetValZ() const;
		/*! Set the value array. Used to store the aiding data.*/
		void SetVal(double x, double y, double z);
		std::vector<double> GetVal() const;

		int GetVarType() const;
		void SetVarUpperDiag(double v_00, double v_11, double v_22,
			double v_01, double v_02, double v_12);
		void SetVarDiag(double v_00, double v_11, double v_22);
		void SetVarSingle(double v_0);
		std::vector<double> GetVar() const;

	};


	/**
	 * Cpp wrapper class for C struct GEN_AIDING_DATA
	 */
	class Gad
	{
	private:
		/** Type of Aiding (position, velocity, ...). For enumerated values see
		 * GEN_TYPE.
		 */
		int8_t        type = { 0 };
		/** Aiding stream ID to identify the source device.
		 *  Values 128-254. Each stream should have a unique ID.
		 */
		uint8_t       stream_id = { 0 };
		/** Sub-struct VALUE. Contains navigation aiding data. */
		Gen3d         val;
		GenFlag       val_valid = { 0 };
		/** Sub-struct TIME. Contains the time the data was recorded. */
		Gen3d         time;
		GenFlag       time_valid = { 0 };
		/** Sub-struct LOCATION. Contains lever arm (or alignment) data between the
		 * IMU and aiding source.
		 */
		Gen3d         loc;
		GenFlag       loc_valid = { 0 };
		// Sub-struct RESERVED
		Gen3d         res1;
		GenFlag       res1_valid = { 0 };
		// Sub-struct RESERVED
		Gen3d         res2;
		GenFlag       res2_valid = { 0 };
		/**
		 * Acquisition Time Stamp. The INS will fill in this timestamp upon its
		 * arrival to the INS. Leave blank.
		 */
		uint32_t      acq = { 0 };                 // Timestamp from INS. Leave empty.
		GenFlag       acq_valid = { 0 };
	protected:
		// type 
		void SetDataType(int type);
		int  GetDataType() const;
		// val
		/** Set Time Valid flag
		 * @param flag boolean to indicate whether time is valid or invalid
		 */
		void SetValValid(bool flag);
		/** Set Time Valid flag
		* @return flag boolean to indicate whether time validity
		*/
		bool GetValValid() const;
		void SetDataMode(int mode);
		void SetDataValType(int x_type);
		void SetDataVal(double x_0, double x_1, double x_2);
		std::vector<double> GetDataVal() const;
		void SetDataVarUpperDiag(double v_00, double v_11, double v_22,
			double v_01, double v_02, double v_12);
		void SetDataVarDiag(double v_0, double v_1, double v_2);
		void SetDataVarSingle(double v_0);
		std::vector<double> GetDataVar() const;
		// loc  
		void SetLocValid(bool flag);
		bool GetLocValid() const;
		void SetLocMode(int mode);
		void SetLocValType(int x_type);
		void SetLocVal(double x_0, double x_1, double x_2);
		std::vector<double> GetLocVal() const;
		void SetLocVarUpperDiag(double v_00, double v_11, double v_22,
			double v_01, double v_02, double v_12);
		void SetLocVarDiag(double v_00, double v_11, double v_22);
		void SetLocVarSingle(double v_0);
		std::vector<double> GetLocVar() const;

	public:
		/*! Default Constructor */
		Gad();
		/*! Constructor */
		Gad(uint8_t stream_id, int8_t aiding_type);
		/*! Destructor */
		virtual ~Gad();
		/*! Copy constructor */
		Gad(const Gad& g);
		/*! Copy constructor to allow direct copy to C struct. */
		explicit Gad(const GEN_AIDING_DATA& g);
		// Copy assignment operator Gad -> Gad */
		Gad& operator=(const Gad& g);
		// Copy data from Gad to an instance of the C struct GEN_AIDING_DATA
		GEN_AIDING_DATA  getCStruct();
		/** Copy assignment operator GEN_AIDING_DATA -> Gad   */
		Gad& operator=(const GEN_AIDING_DATA& g);

		// General Accessors
		/** Set Stream ID for this GAD packet */
		void SetStreamId(int id);
		/** Get Stream ID for this GAD packet */
		int GetStreamId() const;

		// Time accessors
		/** Set Time Valid flag
		 * @param flag boolean to indicate whether time is valid or invalid
		 */
		void SetTimeValid(bool flag);
		/** Set Time Valid flag
		* @return flag boolean to indicate whether time validity
		*/
		bool GetTimeValid() const;
		/** Set time from an external clock
		 * @param week Week in the external time frame
		 * @param seconds Seconds in the external time frame
		 */
		void SetTimeExternal(double week, double secs);
		/** Get the week in the external time */
		double GetTimeExternalWeek() const;
		/** Get the seconds into the week in the external time */
		double GetTimeExternalSecondsFromSunday() const;
		std::vector<double> GetTimeExternal() const;
		/** Set timestamp for this data
		 * @param week GPS Week
		 * @param seconds_from_sunday Seconds from Midnight Sunday (s)
		 */
		void SetTimeGps(double week, double seconds_from_sunday);
		std::vector<double> GetTimeGps() const;
		/** Get the GPS Week value. Note that this function assumes that
		 *  the time has been set in this format, there is no check. */
		double GetTimeGpsWeek() const;
		/** Get the Seconds from Sunday value. Note that this function assumes that
		 *  the time has been set in this format, there is no check. */
		double GetTimeGpsSecondsFromSunday() const;
		/** Set a PPS relative timestamp
		 * @param ns Time since PPS timestamp (nanoseconds)
		 */
		/*Set TAI timestamp in seconds*/
		void SetTimeTAI(double secs);
		/** Get TAI timestamp.  */
		double GetTimeTAI() const;

		void SetTimePpsRelative(double ns);
		double GetTimePpsRelative() const;
		/**
		 * Set the timestamp type for this data to Latency. The latency is an estimate
		 * of the time taken for the packet to travel from the aiding source to the
		 * INS. Upon arrival the INS will timestamp the data, adjusting for the
		 * latency.
		 * @param ns Latency estimate in (nanoseconds).
		 */
		void SetTimeLatency(double ns);
		/** Get latency estimate.   */
		double GetTimeLatency() const;
		/** Set the timestamp as UTC time encoded as the number of seconds from the UNIX epoch.
		*  @param secs Time since unic epoch including leap seconds (seconds).
		*/
		void SetTimeUTCUnix(double secs);
		/** Get unix timestamp.  */
		double GetTimeUTCUnix() const;
		/**
		 * Set the timestamp type for this data to void. Data with a void timestamp
		 * will be timestamped by the INS upon receipt.
		 */
		void SetTimeVoid();

		void SetRes1Valid(bool flag);
		bool GetRes1Valid() const;
		void SetRes2Valid(bool flag);
		bool GetRes2Valid() const;

		// Acquisiton time accessors.
		void SetAcqValid(bool flag);
		bool GetAcqValid() const;
		/*! Set the acquisition time of the data. Not to be used outside of the INS.*/
		void SetAcqTimestamp(uint32_t acq_time);
		/*! Get the acquisition time of the data. Not expected to be set outside of the INS.*/
		uint32_t  GetAcqTimestamp() const;

	};

	/**
	 * Generic Aiding position.
	 */
	class GadPosition : public Gad
	{
	private:

	public:
		/**
		 * Constructor
		 *
		 * @param stream_id Stream ID for the position aiding source. Must be unique 128-254.
		 */
		explicit GadPosition(uint8_t stream_id);
		/**
		 * Set the aiding position in the WGS84 coordinate frame.
		 * @param lat Latitude of the position estimate (deg).
		 * @param lon Longitude of the position estimate (deg).
		 * @param alt Altitude of the position estimate (deg).
		 */
		void SetPosGeodetic(double lat, double lon, double alt);
		/**
		 * Set the aiding position in the user-defined local coordinate frame.
		 * @param x Position in the x axis of the local frame (m).
		 * @param y Position in the y axis of the local frame (m).
		 * @param z Position in the z axis of the local frame (m).
		 */
		void SetPosLocal(double x, double y, double z);
		/**
		 * Get the aiding position.
		 */
		std::vector<double> GetPos() const;
		/**
		 * Set the variance aiding position in the coordinate frame.
		 * @param v_n Variance of the position estimate (m^2).
		 * @param v_e Variance of the position estimate (m^2).
		 * @param v_d Variance of the position estimate (m^2).
		 */
		void SetPosGeodeticVar(double v_n, double v_e, double v_d);
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
			double v_00, double v_11, double v_22,
			double v_01, double v_02, double v_12
		);
		/**
		 * Set the variance aiding position in the coordinate frame.
		 * @param v_x Variance of the position estimate (m^2).
		 * @param v_y Variance of the position estimate (m^2).
		 * @param v_z Variance of the position estimate (m^2).
		 */
		void SetPosLocalVar(double v_x, double v_y, double v_z);
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
			double v_00, double v_11, double v_22,
			double v_01, double v_02, double v_12
		);
		/**
		 * Get the aiding position variance.
		 */
		std::vector<double> GetPosVar() const;
		/**
		 * Set lever arm from the INS to the aiding source. This lever arm will not be
		 * optimised by the Kalman Filter.
		 *
		 * @param x Offset from INS to aiding source in the x axis of the IMU frame (m).
		 * @param y Offset from INS to aiding source in the y axis of the IMU frame (m).
		 * @param z Offset from INS to aiding source in the z axis of the IMU frame (m).
		 */
		void SetAidingLeverArmFixed(double x, double y, double z);
		std::vector<double> GetAidingLeverArm() const;
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
		void SetAidingLeverArmVar(double x, double y, double z);
		/**
		 * Set the variance (accuracy) of the lever arm measurements from the INS to
		 * the aiding source, including off-diagonal terms. Only required for fixed lever-arm.
		 *
		 * @param v_xx Variance on the lever arm from INS to aiding source in the x axis of the IMU frame.
		 * @param v_yy Variance on the lever arm from INS to aiding source in the x axis of the IMU frame.
		 * @param v_zz Variance on the lever arm from INS to aiding source in the x axis of the IMU frame.
		 * @param v_xy Covariance on the lever arm from INS to aiding source between the x and y axes of the IMU frame.
		 * @param v_xz Covariance on the lever arm from INS to aiding source between the x and z axes of the IMU frame.
		 * @param v_yz Covariance on the lever arm from INS to aiding source between the y and z axes of the IMU frame.
		 */
		void SetAidingLeverArmVarUpperDiag(
			double v_xx, double v_yy, double v_zz,
			double v_xy, double v_xz, double v_yz);
		
		std::vector<double> GetAidingLeverArmVar() const;
	};

	/**
	 * Generic Aiding velocity.
	 */
	class GadVelocity : public Gad
	{
	private:

	public:
		/**
		 * Constructor
		 *
		 * @param stream_id Stream ID for the velocity aiding source. Must be unique 128-254.
		 */
		explicit GadVelocity(uint8_t stream_id);
		/**
		 * Set the aiding velocity estimate in the local NED coordinate frame.
		 * @param v_e Velocity estimate in the East direction (m/s).
		 * @param v_n Velocity estimate in the North direction (m/s).
		 * @param v_d Velocity estimate in the Down direction (m/s).
		 */
		void SetVelNed(double v_n, double v_e, double v_d);
		/**
		 * Set the aiding velocity estimate in the odometry frame.
		 * @param v_x Velocity estimate in the x direction (m/s).
		 * @param v_y Velocity estimate in the y direction (m/s).
		 * @param v_z Velocity estimate in the z direction (m/s).
		 */
		void SetVelOdom(double v_x, double v_y, double v_z);
		/**
		 * Set the aiding velocity estimate in the user-defined local coordinate frame.
		 * @param v_x Velocity estimate in the x direction (m/s).
		 * @param v_y Velocity estimate in the y direction (m/s).
		 * @param v_z Velocity estimate in the z direction (m/s).
		 */
		void SetVelLocal(double v_x, double v_y, double v_z);
		/**
		 * Get the aiding velocity estimate.
		 */
		std::vector<double> GetVel() const;
		/**
		 * Set the aiding velocity variance estimate in the local NED coordinate frame.
		 * @param v_n Velocity variance estimate in the North direction (m/s)^2.
		 * @param v_e Velocity variance estimate in the East direction (m/s)^2.
		 * @param v_u Velocity variance estimate in the Up direction (m/s)^2.
		 */
		void SetVelNedVar(double v_n, double v_e, double v_d);
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
			double v_nn, double v_ee, double v_dd,
			double v_ne, double v_nd, double v_ed
		);
		/**
		 * Set the aiding velocity variance estimate in the local NED coordinate frame.
		 * @param v_x Velocity variance estimate in the x direction (m/s)^2.
		 * @param v_y Velocity variance estimate in the y direction (m/s)^2.
		 * @param v_z Velocity variance estimate in the z direction (m/s)^2.
		 */
		void SetVelOdomVar(double v_x, double v_y, double v_z);
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
			double v_xx, double v_yy, double v_zz,
			double v_xy, double v_xz, double v_yz
		);
		/**
		 * Set the aiding velocity variance estimate in the local NED coordinate frame.
		 * @param v_x Velocity variance estimate in the x direction (m/s)^2.
		 * @param v_y Velocity variance estimate in the y direction (m/s)^2.
		 * @param v_z Velocity variance estimate in the z direction (m/s)^2.
		 */
		void SetVelLocalVar(double v_x, double v_y, double v_z);
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
			double v_xx, double v_yy, double v_zz,
			double v_xy, double v_xz, double v_yz
		);
		/**
		 * Get the aiding velocity variance estimate.
		 */
		std::vector<double> GetVelVar() const;
		/**
		 * Set lever arm from the INS to the aiding source. This lever arm will not be
		 * optimised by the Kalman Filter.
		 *
		 * @param x Offset from INS to aiding source in the x axis of the IMU frame (m).
		 * @param y Offset from INS to aiding source in the y axis of the IMU frame (m).
		 * @param z Offset from INS to aiding source in the z axis of the IMU frame (m).
		 */
		void SetAidingLeverArmFixed(double x, double y, double z);
		std::vector<double> GetAidingLeverArm() const;
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
		void SetAidingLeverArmVar(double x, double y, double z);
		std::vector<double> GetAidingLeverArmVar() const;
	};

	/**
	 * Generic Aiding speed.
	 */
	class GadSpeed : public Gad
	{
	private:

	public:
		explicit GadSpeed(uint8_t stream_id);

		/**
		 * Set the forward speed aiding estimate.
		 *
		 * @param speed Forward speed estimate in the vehicle frame (m/s).
		 */
		void SetSpeedFw(double speed);
		double GetSpeedFw() const;
		/**
		 * Set estimated variance on the forward speed aiding measurement.
		 *
		 * @param v_s Forward speed estimate in the vehicle frame (units).
		 */
		void SetSpeedFwVar(double v_s);
		double GetSpeedFwVar() const;
		/**
		 * Set the pulse count measurement from a wheelspeed encoder.
		 *
		 * @param count Number of pulses recorded during the period.
		 * @param period The period over which the current pulse count was recorded.
		 *
		 * @todo Clarify where the timestamp should correspond to in the period:
		 * start, middle, end.
		 */
		void SetWheelspeedCount(double count, double period);
		std::vector<double> GetWheelspeedCount() const;
		/**
		 * Set the estimated variance on the wheelspeed pulse count.
		 *
		 * @param v_c Estimated variance (pulses).
		 * @todo Clarify units
		 */
		void SetWheelspeedVar(double v_c);
		double GetWheelspeedVar() const;
		/**
		 * Set lever arm from the INS to the aiding source. This lever arm will not be
		 * optimised by the Kalman Filter.
		 *
		 * @param x Offset from INS to aiding source in the x axis of the IMU frame (m).
		 * @param y Offset from INS to aiding source in the y axis of the IMU frame (m).
		 * @param z Offset from INS to aiding source in the z axis of the IMU frame (m).
		 */
		void SetAidingLeverArmFixed(double x, double y, double z);
		std::vector<double> GetAidingLeverArm() const;
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
		void SetAidingLeverArmVar(double x, double y, double z);
		std::vector<double> GetAidingLeverArmVar() const;
	};

	/**
	 * Generic Aiding attitude.
	 */
	class GadAttitude : public Gad
	{
	public:
		/**
		 * Default constructor
		 */
		GadAttitude();
		/** Constructor.
		 *  @param stream_id Stream ID for the attitude aiding source. Must be unique 128-254.
		 */
		explicit GadAttitude(uint8_t stream_id);
		std::vector<double> GetAtt() const;
		// val
		/**
		 * Set the aiding attitude measurement relative to the NED coordinate frame.
		 * @param heading (deg)
		 * @param pitch   (deg)
		 * @param roll    (deg)
		 *
		 * @note Roll is not yet used
		 */
		void SetAtt(double heading, double pitch, double roll);
		/**
		* Set the aiding attitude measurement relative to the local coordinate frame. 
		* @param heading (deg)
		* @param pitch   (deg)
		* @param roll    (deg)
		* @note Roll is not yet used!
		*/
		void SetAttLocal(double heading, double pitch, double roll);
		/**
		 * Set the estimated variance on the aiding attitude measurement.
		 * @param v_h Variance estimate on the heading angle (deg)^2
		 * @param v_p Variance estimate on the pitch angle (deg)^2
		 * @param v_r Variance estimate on the roll angle (deg)^2
		 */
		void SetAttVar(double v_h, double v_p, double v_r);
		std::vector<double> GetAttVar() const;
		// /**
		//  * Set the angles which specify the rotation required to align the IMU and 
		//  * aiding sensor frames. This alignment will not be optimised by the INS.
		//  * @param x
		//  * @param y
		//  * @param z
		//  */
		void SetAidingAlignmentFixed(double x, double y, double z);
		std::vector<double> GetAidingAlignment() const;
		/**
		 * Set alignment to be optimised by the INS. The alignment values will be read
		 * from the mobile.att file, so are not set here.
		 */
		void SetAidingAlignmentOptimising();
		/**
		 * Set the estimated variance (error) on the alignment angles between the IMU
		 * and aiding sensor frames.
		 * @param x
		 * @param y
		 * @param z
		 */
		void SetAidingAlignmentVar(double x, double y, double z);
		std::vector<double> GetAidingAlignmentVar() const;
	};

	/**
	 * Generic Aiding Heading.
	 */
	class GadHeading : public Gad
	{
	public:
		/**
		 * Default constructor
		 */
		GadHeading();
		/** Constructor.
		 *  @param stream_id Stream ID for the attitude aiding source. Must be unique 128-254.
		 */
		explicit GadHeading(uint8_t stream_id);
		double GetHeading() const;
		// val
		/**
		 * Set the aiding heading measurement relative to the NED coordinate frame.
		 * @param heading (deg)
		 */
		void SetHeading(double heading);

		/**
		 * Set the aiding heading measurement relative to the local coordinate frame.
		 * @param heading (deg)
		 */
		void SetHeadingLocal(double heading);
		/**
		 * Set the estimated variance on the aiding attitude measurement.
		 * @param v_h Variance estimate on the heading angle (deg)^2
		 */
		void SetHeadingVar(double v_h);
		double GetHeadingVar() const;
		/**
		 * Set the angles which specify the rotation required to align the IMU and 
		 * aiding sensor frames. This alignment will not be optimised by the INS.
		 * @param h
		 * @param p
		 * @param r
		 */
		void SetAidingAlignmentFixed(double h, double p, double r);
		std::vector<double> GetAidingAlignment() const;
		/**
		 * Set the estimated variance (error) on the alignment angles between the IMU
		 * and aiding sensor frames.
		 * @param h_v
		 * @param h_p
		 * @param h_r
		 */
		void SetAidingAlignmentVar(double h_v, double p_v, double r_v);
		std::vector<double> GetAidingAlignmentVar() const;
	};

} // namespace OxTS



#endif // GAD_HPP
