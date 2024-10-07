#include "oxts/gal-cpp/gad.hpp"

namespace OxTS
{
	namespace Gal_Cpp
	{
		//==============================================================================
		// Gen3d

		Gen3d::Gen3d() :
			m_mode(0U),
			m_x_type(0U),
			m_v_type(0U),
			m_x(),
			m_v()
		{
			for (size_t i = 0U; i < 3U; ++i)
			{
				m_x[i] = 0.0;
			}
		}

		/** Copy constructor. */
		Gen3d::Gen3d(const Gen3d& g) :
			m_mode(g.m_mode),
			m_x_type(g.m_x_type),
			m_v_type(g.m_v_type),
			m_x(g.m_x),
			m_v(g.m_v)
		{

		}

		/** Copy assignment operator. */
		Gen3d& Gen3d::operator=(const Gen3d& g)
		{
			if (this != &g)
			{
				m_mode = g.m_mode;
				m_x_type = g.m_x_type;
				m_x = g.m_x;
				m_v_type = g.m_v_type;
				m_v = g.m_v;
			}
			return *this;
		}

#ifdef OXTS_ENABLE_CPP11
		/** Move constructor. */
		Gen3d::Gen3d(Gen3d&& g) :	/*PRQA S 1127 # Assume C++11. */
			m_mode(std::move(g.m_mode)),
			m_x_type(std::move(g.m_x_type)),
			m_x(std::move(g.m_x)),
			m_v_type(std::move(g.m_v_type)),
			m_v(std::move(g.m_v))
		{

		}

		/** Move assignment operator. */
		Gen3d& Gen3d::operator=(Gen3d&& g)	/*PRQA S 1127 # Assume C++11. */
		{
			if (this != &g)
			{
				m_mode = std::move(g.m_mode);
				m_x_type = std::move(g.m_x_type);
				m_x = std::move(g.m_x);
				m_v_type = std::move(g.m_v_type);
				m_v = std::move(g.m_v);
			}
			return *this;
		}
#endif

		uint8_t  Gen3d::GetVarType() const { return m_v_type; }

		void Gen3d::SetMode(const uint8_t mode) { m_mode = mode; }
		uint8_t Gen3d::GetMode() const { return m_mode; }

		void Gen3d::SetValType(const uint8_t x_type) { m_x_type = x_type; }
		uint8_t Gen3d::GetValType() const { return m_x_type; }

		void Gen3d::SetValX(const double_t x)
		{
			m_x[0U] = x; 
		}
		double_t Gen3d::GetValX() const { return (m_x.size() > 0U) ? m_x[0U] : 0.0; }
		void Gen3d::SetValY(const double_t y)
		{
			m_x[1U] = y;
		}
		double_t Gen3d::GetValY() const { return (m_x.size() > 1U) ? m_x[1U] : 0.0; }
		void Gen3d::SetValZ(const double_t z)
		{
			m_x[2U] = z;
		}
		double_t Gen3d::GetValZ() const { return (m_x.size() > 2U) ? m_x[2U] : 0.0; }

		void Gen3d::SetVal(const double_t x, const double_t y, const double_t z)
		{
			SetValX(x);
			SetValY(y);
			SetValZ(z);
		}
		void Gen3d::SetVal(const double_t x, const double_t y)
		{
			SetValX(x);
			SetValY(y);
		}
		const container_double3_t& Gen3d::GetVal() const
		{
			return m_x;
		}

		void Gen3d::SetVarUpperDiag(const double_t v_00, const double_t v_11, const double_t v_22,
			const double_t v_01, const double_t v_02, const double_t v_12)
		{
#ifdef OXTS_ENABLE_CPP11
			m_v_type = static_cast<uint8_t>(GEN_VAR_TYPE::GEN_VAR_HMAT);
#else
			m_v_type = static_cast<uint8_t>(GEN_VAR_HMAT);
#endif
			m_v[0U] = v_00;
			m_v[1U] = v_11;
			m_v[2U] = v_22;
			m_v[3U] = v_01;
			m_v[4U] = v_02;
			m_v[5U] = v_12;
		}

		void Gen3d::SetVarDiag(const double_t v_00, const double_t v_11, const double_t v_22)
		{
#ifdef OXTS_ENABLE_CPP11
			m_v_type = static_cast<uint8_t>(GEN_VAR_TYPE::GEN_VAR_DIAG);
#else
			m_v_type = static_cast<uint8_t>(GEN_VAR_DIAG);
#endif
			m_v[0U] = v_00;
			m_v[1U] = v_11;
			m_v[2U] = v_22;
		}

		void Gen3d::SetVarSingle(const double_t v_0)
		{
#ifdef OXTS_ENABLE_CPP11
			m_v_type = static_cast<uint8_t>(GEN_VAR_TYPE::GEN_VAR_SINGLE);
#else
			m_v_type = static_cast<uint8_t>(GEN_VAR_SINGLE);
#endif
			m_v[0U] = v_0;
		}

		const container_double6_t& Gen3d::GetVar() const
		{
			return m_v;
		}


		//==============================================================================
		// Gad superclass
		const uint8_t DEFAULT_STREAM_ID = 128U;
		// Default Constructor
		Gad::Gad() :
			m_stream_id(DEFAULT_STREAM_ID),
#ifdef OXTS_ENABLE_CPP11
			m_type(static_cast<int8_t>(GEN_TYPE::GEN_VOID)),
#else
			m_type(static_cast<int8_t>(GEN_VOID)),
#endif
			m_val_data(),
			m_val_valid(false),
			m_time_data(),
			m_time_valid(false),
			m_loc_data(),
			m_loc_valid(false),
			m_res1_data(),
			m_res1_valid(false),
			m_res2_data(),
			m_res2_valid(false),
			m_acq_data(),
			m_acq_valid(false)
		{}
		// Constructor
		Gad::Gad(const uint8_t stream_id, const int8_t aiding_type) :
			m_stream_id(stream_id),
			m_type(aiding_type),
			m_val_data(),
			m_val_valid(false),
			m_time_data(),
			m_time_valid(false),
			m_loc_data(),
			m_loc_valid(false),
			m_res1_data(),
			m_res1_valid(false),
			m_res2_data(),
			m_res2_valid(false),
			m_acq_data(),
			m_acq_valid(false)
		{}

		Gad::~Gad()
		{

		}

		Gad::Gad(const Gad& g) :
			m_type(g.m_type),
			m_stream_id(g.m_stream_id),
			m_val_data(g.m_val_data),
			m_val_valid(g.m_val_valid),
			m_time_data(g.m_time_data),
			m_time_valid(g.m_time_valid),
			m_loc_data(g.m_loc_data),
			m_loc_valid(g.m_loc_valid),
			m_res1_data(g.m_res1_data),
			m_res1_valid(g.m_res1_valid),
			m_res2_data(g.m_res2_data),
			m_res2_valid(g.m_res2_valid),
			m_acq_data(g.m_acq_data),
			m_acq_valid(g.m_acq_valid)
		{

		}

		Gad& Gad::operator=(const Gad& g)
		{
			if (this != &g)
			{
				m_type = g.m_type;
				m_stream_id = g.m_stream_id;
				m_val_data = g.m_val_data;
				m_val_valid = g.m_val_valid;
				m_time_data = g.m_time_data;
				m_time_valid = g.m_time_valid;
				m_loc_data = g.m_loc_data;
				m_loc_valid = g.m_loc_valid;
				m_res1_data = g.m_res1_data;
				m_res1_valid = g.m_res1_valid;
				m_res2_data = g.m_res2_data;
				m_res2_valid = g.m_res2_valid;
				m_acq_data = g.m_acq_data;
				m_acq_valid = g.m_acq_valid;
			}
			return *this;
		}

#ifdef OXTS_ENABLE_CPP11
		/** Move constructor. */
		Gad::Gad(Gad&& g) :m_type(g.m_type),	/*PRQA S 1127 # Assume C++11. */
			m_stream_id(std::move(g.m_stream_id)),
			m_val_data(std::move(g.m_val_data)),
			m_val_valid(std::move(g.m_val_valid)),
			m_time_data(std::move(g.m_time_data)),
			m_time_valid(std::move(g.m_time_valid)),
			m_loc_data(std::move(g.m_loc_data)),
			m_loc_valid(std::move(g.m_loc_valid)),
			m_res1_data(std::move(g.m_res1_data)),
			m_res1_valid(std::move(g.m_res1_valid)),
			m_res2_data(std::move(g.m_res2_data)),
			m_res2_valid(std::move(g.m_res2_valid)),
			m_acq_data(std::move(g.m_acq_data)),
			m_acq_valid(std::move(g.m_acq_valid))
		{

		}

		/** Move assignment operator. */
		Gad& Gad::operator=(Gad&& g)	/*PRQA S 1127 # Assume C++11. */
		{
			if (this != &g)
			{
				m_type = std::move(g.m_type);
				m_stream_id = std::move(g.m_stream_id);
				m_val_data = std::move(g.m_val_data);
				m_val_valid = std::move(g.m_val_valid);
				m_time_data = std::move(g.m_time_data);
				m_time_valid = std::move(g.m_time_valid);
				m_loc_data = std::move(g.m_loc_data);
				m_loc_valid = std::move(g.m_loc_valid);
				m_res1_data = std::move(g.m_res1_data);
				m_res1_valid = std::move(g.m_res1_valid);
				m_res2_data = std::move(g.m_res2_data);
				m_res2_valid = std::move(g.m_res2_valid);
				m_acq_data = std::move(g.m_acq_data);
				m_acq_valid = std::move(g.m_acq_valid);
			}
			return *this;
		}
#endif

		// streamId
		void Gad::SetStreamId(const uint8_t id) { m_stream_id = id; }
		uint8_t  Gad::GetStreamId() const { return m_stream_id; }
		// type 
		void Gad::SetDataType(const int8_t _type) { m_type = _type; }
		int8_t  Gad::GetDataType() const { return m_type; }
		// val
		void Gad::SetValValid(const bool flag) { m_val_valid = flag; }
		const bool Gad::GetValValid() const { return m_val_valid; }

		void Gad::SetDataMode(const uint8_t mode) { m_val_data.SetMode(mode); }
		void Gad::SetDataValType(const uint8_t x_type) { m_val_data.SetValType(x_type); }
		void Gad::SetDataVal(const double_t x_0, const double_t x_1, const double_t x_2)
		{
			SetValValid(true);
			m_val_data.SetVal(x_0, x_1, x_2);
		}
		void Gad::SetDataVal(const double_t x_0, const double_t x_1)
		{
			SetValValid(true);
			m_val_data.SetVal(x_0, x_1);
		}

		const container_double3_t& Gad::GetDataVal() const
		{
			return m_val_data.GetVal();
		}

		void Gad::SetDataVarUpperDiag(const double_t v_00, const double_t v_11, const double_t v_22,
			const double_t v_01, const double_t v_02, const double_t v_12)
		{
			m_val_data.SetVarUpperDiag(v_00, v_11, v_22, v_01, v_02, v_12);
		}

		void Gad::SetDataVarDiag(const double_t v_00, const double_t v_11, const double_t v_22)
		{
			m_val_data.SetVarDiag(v_00, v_11, v_22);
		}

		void Gad::SetDataVarSingle(const double_t v_0)
		{
			m_val_data.SetVarSingle(v_0);
		}

		const container_double6_t& Gad::GetDataVar() const
		{
			return m_val_data.GetVar();
		}

		// time
		void Gad::SetTimeValid(const bool flag) { m_time_valid = flag; }
		const bool Gad::GetTimeValid() const { return m_time_valid; }
		//
		void Gad::SetTimeExternal(const double_t week, const double_t secs)
		{
			SetTimeValid(true);
			m_time_data.SetMode(0U);
#ifdef OXTS_ENABLE_CPP11
			m_time_data.SetValType(static_cast<uint8_t>(TIME_SYS::TIME_EXT));
#else
			m_time_data.SetValType(static_cast<uint8_t>(TIME_EXT));
#endif
			m_time_data.SetVal(week, secs);
		}
		double_t Gad::GetTimeExternalWeek() const { return m_time_data.GetValX(); }
		double_t Gad::GetTimeExternalSecondsFromSunday() const { return m_time_data.GetValY(); }
		const container_double3_t& Gad::GetTimeExternal() const
		{
			return m_time_data.GetVal();
		}
		// GPS
		void Gad::SetTimeGps(const double_t week, const double_t seconds_from_sunday)
		{
			SetTimeValid(true);
			m_time_data.SetMode(0U);
#ifdef OXTS_ENABLE_CPP11
			m_time_data.SetValType(static_cast<uint8_t>(TIME_SYS::TIME_GPS));
#else
			m_time_data.SetValType(static_cast<uint8_t>(TIME_GPS));
#endif
			m_time_data.SetVal(week, seconds_from_sunday);
		}
		const container_double3_t& Gad::GetTimeGps() const
		{
			return m_time_data.GetVal();
		}
		double_t Gad::GetTimeGpsWeek() const { return m_time_data.GetValX(); }
		double_t Gad::GetTimeGpsSecondsFromSunday() const { return m_time_data.GetValY(); }

		// TAI
		void Gad::SetTimeTAI(const double_t secs)
		{
			SetTimeValid(true);
			m_time_data.SetMode(0U);
#ifdef OXTS_ENABLE_CPP11
			m_time_data.SetValType(static_cast<uint8_t>(TIME_SYS::TIME_TAI));
#else
			m_time_data.SetValType(static_cast<uint8_t>(TIME_TAI));
#endif
			m_time_data.SetVal(secs, 0.0, 0.0);
		}
		double_t Gad::GetTimeTAI() const { return m_time_data.GetValX(); }

		// PPS
		void Gad::SetTimePpsRelative(const double_t ns)
		{
			SetTimeValid(true);
			m_time_data.SetMode(0U);
#ifdef OXTS_ENABLE_CPP11
			m_time_data.SetValType(static_cast<uint8_t>(TIME_SYS::TIME_PPS_RELATIVE));
#else
			m_time_data.SetValType(static_cast<uint8_t>(TIME_PPS_RELATIVE));
#endif
			m_time_data.SetVal(0.0, 0.0, ns);
		}
		double_t Gad::GetTimePpsRelative() const { return m_time_data.GetValZ(); }
		// Latency
		void   Gad::SetTimeLatency(const double_t secs)
		{
			SetTimeValid(true);
			m_time_data.SetMode(0U);
#ifdef OXTS_ENABLE_CPP11
			m_time_data.SetValType(static_cast<uint8_t>(TIME_SYS::TIME_EST_LATENCY));
#else
			m_time_data.SetValType(static_cast<uint8_t>(TIME_EST_LATENCY));
#endif
			m_time_data.SetVal(0.0, secs, 0.0);
		}
		double_t Gad::GetTimeLatency() const { return m_time_data.GetValY(); }
		// UTC - Unix
		void Gad::SetTimeUTCUnix(const double_t secs)
		{
			SetTimeValid(true);
			m_time_data.SetMode(0U);
#ifdef OXTS_ENABLE_CPP11
			m_time_data.SetValType(static_cast<uint8_t>(TIME_SYS::TIME_UNIX_UTC));
#else
			m_time_data.SetValType(static_cast<uint8_t>(TIME_UNIX_UTC));
#endif
			m_time_data.SetVal(secs, 0.0, 0.0);
		}
		double_t Gad::GetTimeUTCUnix() const { return m_time_data.GetValX(); }
		// Void
		void   Gad::SetTimeVoid()
		{
			SetTimeValid(true);
			m_time_data.SetMode(0U);
#ifdef OXTS_ENABLE_CPP11
			m_time_data.SetValType(static_cast<uint8_t>(TIME_SYS::TIME_VOID));
#else
			m_time_data.SetValType(static_cast<uint8_t>(TIME_VOID));
#endif
		}

		// loc  
		void Gad::SetLocValid(const bool flag) { m_loc_valid = flag; }
		const bool Gad::GetLocValid() const { return m_loc_valid; }

		void Gad::SetLocMode(const uint8_t mode) { m_loc_data.SetMode(mode); }
		void Gad::SetLocValType(const uint8_t x_type) { m_loc_data.SetValType(x_type); }
		void Gad::SetLocVal(const double_t x_0, const double_t x_1, const double_t x_2)
		{
			SetLocValid(true);
			m_loc_data.SetVal(x_0, x_1, x_2);
		}
		const container_double3_t& Gad::GetLocVal() const
		{
			return m_loc_data.GetVal();
		}
		void Gad::SetLocVarUpperDiag(const double_t v_00, const double_t v_11, const double_t v_22,
			const double_t v_01, const double_t v_02, const double_t v_12)
		{
			m_loc_data.SetVarUpperDiag(v_00, v_11, v_22, v_01, v_02, v_12);
		}
		void Gad::SetLocVarDiag(const double_t v_00, const double_t v_11, const double_t v_22)
		{
			m_loc_data.SetVarDiag(v_00, v_11, v_22);
		}
		void Gad::SetLocVarSingle(const double_t v_0)
		{
			m_loc_data.SetVarSingle(v_0);
		}
		const container_double6_t& Gad::GetLocVar() const
		{
			return m_loc_data.GetVar();
		}

		void Gad::SetRes1Valid(const bool flag) { m_res1_valid = flag; }
		const bool Gad::GetRes1Valid() const { return m_res1_valid; }
		void Gad::SetRes2Valid(const bool flag) { m_res2_valid = flag; }
		const bool Gad::GetRes2Valid() const { return m_res2_valid; }
		void Gad::SetAcqValid(const bool flag) { m_acq_valid = flag; }
		const bool Gad::GetAcqValid() const { return m_acq_valid; }
		int8_t Gad::GetType() const { return m_type; }

		const Gen3d& Gad::GetTime() const { return m_time_data; }
		const Gen3d& Gad::GetVal() const { return m_val_data; }
		const Gen3d& Gad::GetLoc() const { return m_loc_data; }
		const Gen3d& Gad::GetRes1() const { return m_res1_data; }
		const Gen3d& Gad::GetRes2() const { return m_res2_data; }

		void Gad::SetAcqTimestamp(const uint32_t acq_time)
		{
			m_acq_data = acq_time;
			m_acq_valid = 1;
		}
		uint32_t Gad::GetAcqTimestamp() const
		{
			return m_acq_data;
		}

		//==============================================================================
		// GadPosition

		GadPosition::GadPosition(const uint8_t stream_id) : 
#ifdef OXTS_ENABLE_CPP11
			Gad(stream_id, static_cast<int8_t>(GEN_TYPE::GEN_POS)) 
#else
			Gad(stream_id, static_cast<int8_t>(GEN_POS)) 
#endif
		{

		}

		void GadPosition::SetPosGeodetic(const double_t lat, const double_t lon, const double_t alt)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(POS_SYS_TYPE::POS_SYS_WGS84));
#else
			SetDataValType(static_cast<uint8_t>(POS_SYS_WGS84));
#endif
			SetDataVal(lat, lon, alt);
		}

		void GadPosition::SetPosLocal(const double_t x, const double_t y, const double_t z)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(POS_SYS_TYPE::POS_SYS_LOCAL));
#else
			SetDataValType(static_cast<uint8_t>(POS_SYS_LOCAL));
#endif
			SetDataVal(x, y, z);
		}

		const container_double3_t& GadPosition::GetPos() const
		{
			return GetDataVal();
		}

		void GadPosition::SetPosGeodeticVar(const double_t var_north, const double_t var_east, const double_t var_down)
		{
			SetDataVarDiag(var_north, var_east, var_down);
		}

		void GadPosition::SetPosGeodeticVar(
			const double_t v_00, const double_t v_11, const double_t v_22,
			const double_t v_01, const double_t v_02, const double_t v_12
		) {
			SetDataVarUpperDiag(v_00, v_11, v_22, v_01, v_02, v_12);
		}

		void GadPosition::SetPosLocalVar(const double_t var_local_x, const double_t var_local_y, const double_t var_local_z)
		{
			SetDataVarDiag(var_local_x, var_local_y, var_local_z);
		}

		void GadPosition::SetPosLocalVar(
			const double_t v_xx, const double_t v_yy, const double_t v_zz,
			const double_t v_xy, const double_t v_xz, const double_t v_yz
		) {
			SetDataVarUpperDiag(v_xx, v_yy, v_zz, v_xy, v_xz, v_yz);
		}

		const container_double6_t& GadPosition::GetPosVar() const
		{
			return GetDataVar();
		}

		void GadPosition::SetAidingLeverArmFixed(const double_t x, const double_t y, const double_t z)
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_FIXED));
#else
			SetLocMode(static_cast<uint8_t>(LOC_FIXED));
#endif
			SetLocVal(x, y, z);
		}

		const container_double3_t& GadPosition::GetAidingLeverArm() const
		{
			return GetLocVal();
		}

		void GadPosition::SetAidingLeverArmOptimising()
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_KF));
#else
			SetLocMode(static_cast<uint8_t>(LOC_KF));
#endif
			SetLocVal(0.0, 0.0, 0.0);
		}

		void GadPosition::SetAidingLeverArmConfig()
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_CONFIG));
#else
			SetLocMode(static_cast<uint8_t>(LOC_CONFIG));
#endif
			SetLocVal(0.0, 0.0, 0.0);
		}

		void GadPosition::SetAidingLeverArmVar(const double_t x, const double_t y, const double_t z)
		{
			SetLocVarDiag(x, y, z);
		}

		const container_double6_t& GadPosition::GetAidingLeverArmVar() const
		{
			return GetLocVar();
		}

		//==============================================================================
		// GadVelocity
		GadVelocity::GadVelocity(const uint8_t stream_id) : 
#ifdef OXTS_ENABLE_CPP11
			Gad(stream_id, static_cast<int8_t>(GEN_TYPE::GEN_VEL)) 
#else
			Gad(stream_id, static_cast<int8_t>(GEN_VEL)) 
#endif
		{

		}

		// val
		void GadVelocity::SetVelNed(const double_t vel_north, const double_t vel_east, const double_t vel_down)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(VEL_SYS_TYPE::VEL_SYS_NED));
#else
			SetDataValType(static_cast<uint8_t>(VEL_SYS_NED));
#endif
			SetDataVal(vel_north, vel_east, vel_down);
		}

		void GadVelocity::SetVelOdom(const double_t vel_x, const double_t vel_y, const double_t vel_z)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(VEL_SYS_TYPE::VEL_SYS_ODO));
#else
			SetDataValType(static_cast<uint8_t>(VEL_SYS_ODO));
#endif
			SetDataVal(vel_x, vel_y, vel_z);
		}

		void GadVelocity::SetVelLocal(const double_t vel_local_x, const double_t vel_local_y, const double_t vel_local_z)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(VEL_SYS_TYPE::VEL_SYS_LOCAL));
#else
			SetDataValType(static_cast<uint8_t>(VEL_SYS_LOCAL));
#endif
			SetDataVal(vel_local_x, vel_local_y, vel_local_z);
		}

		const container_double3_t& GadVelocity::GetVel() const
		{
			return GetDataVal();
		}

		void GadVelocity::SetVelNedVar(const double_t var_north, const double_t var_east, const double_t var_down)
		{
			SetDataVarDiag(var_north, var_east, var_down);
		}

		void GadVelocity::SetVelNedVar(
			const double_t v_nn, const double_t v_ee, const double_t v_dd,
			const double_t v_ne, const double_t v_nd, const double_t v_ed
		) {
			SetDataVarUpperDiag(v_nn, v_ee, v_dd, v_ne, v_nd, v_ed);
		}

		void GadVelocity::SetVelOdomVar(const double_t v_x, const double_t v_y, const double_t v_z)
		{
			SetDataVarDiag(v_x, v_y, v_z);
		}

		void GadVelocity::SetVelOdomVar(
			const double_t v_xx, const double_t v_yy, const double_t v_zz,
			const double_t v_xy, const double_t v_xz, const double_t v_yz
		) {
			SetDataVarUpperDiag(v_xx, v_yy, v_zz, v_xy, v_xz, v_yz);
		}

		void GadVelocity::SetVelLocalVar(const double_t v_x, const double_t v_y, const double_t v_z)
		{
			SetDataVarDiag(v_x, v_y, v_z);
		}

		void GadVelocity::SetVelLocalVar(
			const double_t v_xx, const double_t v_yy, const double_t v_zz,
			const double_t v_xy, const double_t v_xz, const double_t v_yz
		) {
			SetDataVarUpperDiag(v_xx, v_yy, v_zz, v_xy, v_xz, v_yz);
		}

		const container_double6_t& GadVelocity::GetVelVar() const
		{
			return GetDataVar();
		}

		// loc 
		void GadVelocity::SetAidingLeverArmFixed(const double_t x, const double_t y, const double_t z)
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_FIXED));
#else
			SetLocMode(static_cast<uint8_t>(LOC_FIXED));
#endif
			SetLocVal(x, y, z);
		}

		const container_double3_t& GadVelocity::GetAidingLeverArm() const
		{
			return GetLocVal();
		}

		void GadVelocity::SetAidingLeverArmConfig()
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_CONFIG));
#else
			SetLocMode(static_cast<uint8_t>(LOC_CONFIG));
#endif
			SetLocVal(0.0, 0.0, 0.0);
		}
		void GadVelocity::SetAidingLeverArmOptimising()
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_KF));
#else
			SetLocMode(static_cast<uint8_t>(LOC_KF));
#endif
			SetLocVal(0.0, 0.0, 0.0);
		}
		void GadVelocity::SetAidingLeverArmVar(const double_t x, const double_t y, const double_t z)
		{
			SetLocVarDiag(x, y, z);
		}

		const container_double6_t& GadVelocity::GetAidingLeverArmVar() const
		{
			return GetLocVar();
		}
		//==============================================================================
		// GadWheelSpeed
		GadWheelSpeed::GadWheelSpeed(const uint8_t stream_id) :
#ifdef OXTS_ENABLE_CPP11
			Gad(stream_id, static_cast<int8_t>(GEN_TYPE::GEN_WSPEED))
#else
			Gad(stream_id, static_cast<int8_t>(GEN_WSPEED))
#endif
		{

		}

		// val
		void GadWheelSpeed::SetWheelSpeedFw(const double_t wheelspeed)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(SPEED_SYS_TYPE::SPEED_SYS_FW_VEL));
#else
			SetDataValType(static_cast<uint8_t>(SPEED_SYS_FW_VEL));
#endif
			SetDataVal(wheelspeed, 1.0, 0.0);
		}

		double_t GadWheelSpeed::GetWheelSpeedFw() const
		{
			double_t ret_val = 0.0;
			const container_double3_t& val = GetDataVal();
			if (val.size() > 0U)
			{
				ret_val = val[0U];
			}
			return ret_val;
		}

		void GadWheelSpeed::SetWheelSpeedFwVar(const double_t v_s)
		{
			SetDataVarSingle(v_s);
		}

		double_t GadWheelSpeed::GetWheelSpeedFwVar() const
		{
			double_t ret_val = 0.0;
			const container_double6_t& var = GetDataVar();
			if (var.size() > 0U)
			{
				ret_val = var[0U];
			}
			return ret_val;
		}

		void GadWheelSpeed::SetWheelSpeedCount(const double_t count, const double_t period)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(SPEED_SYS_TYPE::SPEED_SYS_FW_VEL));
#else
			SetDataValType(static_cast<uint8_t>(SPEED_SYS_FW_VEL));
#endif
			SetDataVal(count, period, 0.0);
		}

		const container_double3_t& GadWheelSpeed::GetWheelSpeedCount() const
		{
			return GetDataVal();
		}

		void GadWheelSpeed::SetWheelSpeedVar(const double_t v_c)
		{
			SetDataVarSingle(v_c);
		}

		double_t GadWheelSpeed::GetWheelSpeedVar() const
		{
			double_t ret_val = 0.0;
			const container_double6_t& var = GetDataVar();
			if (var.size() > 0U)
			{
				ret_val = var[0U];
			}
			return ret_val;
		}

		// loc 
		void GadWheelSpeed::SetAidingLeverArmFixed(const double_t x, const double_t y, const double_t z)
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_FIXED));
#else
			SetLocMode(static_cast<uint8_t>(LOC_FIXED));
#endif
			SetLocVal(x, y, z);
		}
		const container_double3_t& GadWheelSpeed::GetAidingLeverArm() const
		{
			return GetLocVal();
		}

		void GadWheelSpeed::SetAidingLeverArmConfig()
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_CONFIG));
#else
			SetLocMode(static_cast<uint8_t>(LOC_CONFIG));
#endif
			SetLocVal(0.0, 0.0, 0.0);
		}

		void GadWheelSpeed::SetAidingLeverArmOptimising()
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_KF));
#else
			SetLocMode(static_cast<uint8_t>(LOC_KF));
#endif
			SetLocVal(0.0, 0.0, 0.0);
		}

		void GadWheelSpeed::SetAidingLeverArmVar(const double_t x, const double_t y, const double_t z)
		{
			SetLocVarDiag(x, y, z);
		}

		const container_double6_t& GadWheelSpeed::GetAidingLeverArmVar() const
		{
			return GetLocVar();
		}
		//==============================================================================
		// GadSpeed
		GadSpeed::GadSpeed(const uint8_t stream_id) :
#ifdef OXTS_ENABLE_CPP11
			Gad(stream_id, static_cast<int8_t>(GEN_TYPE::GEN_SPEED))
#else
			Gad(stream_id, static_cast<int8_t>(GEN_SPEED))
#endif
		{

		}
		// val
		void GadSpeed::SetSpeedFwMs(const double_t speed)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(SPEED_SYS_TYPE::SPEED_SYS_FW_VEL));
#else
			SetDataValType(static_cast<uint8_t>(SPEED_SYS_FW_VEL));
#endif
			SetDataVal(speed, 1.0, 1.0);
		}
		void GadSpeed::SetSpeedBwMs(const double_t speed)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(SPEED_SYS_TYPE::SPEED_SYS_BW_VEL));
#else
			SetDataValType(static_cast<uint8_t>(SPEED_SYS_BW_VEL));
#endif
			SetDataVal(speed, 1.0, 1.0);
		}

		void GadSpeed::SetSpeedUnMs(const double_t speed)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(SPEED_SYS_TYPE::SPEED_SYS_UNSIGNED));
#else
			SetDataValType(static_cast<uint8_t>(SPEED_SYS_UNSIGNED));
#endif
			SetDataVal(speed, 1.0, 1.0);
		}

		void GadSpeed::SetSpeedFwPulsed(const double_t frequency, const double_t scale_factor, const double_t period)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(SPEED_SYS_TYPE::SPEED_SYS_FW_VEL));
#else
			SetDataValType(static_cast<uint8_t>(SPEED_SYS_FW_VEL));
#endif
			SetDataVal(frequency, scale_factor, period);
		}

		void GadSpeed::SetSpeedBwPulsed(const double_t frequency, const double_t scale_factor, const double_t period)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(SPEED_SYS_TYPE::SPEED_SYS_BW_VEL));
#else
			SetDataValType(static_cast<uint8_t>(SPEED_SYS_BW_VEL));
#endif
			SetDataVal(frequency, scale_factor, period);
		}

		void GadSpeed::SetSpeedUnPulsed(const double_t frequency, const double_t scale_factor, const double_t period)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(SPEED_SYS_TYPE::SPEED_SYS_UNSIGNED));
#else
			SetDataValType(static_cast<uint8_t>(SPEED_SYS_UNSIGNED));
#endif
			SetDataVal(frequency, scale_factor, period);
		}

		const container_double3_t& GadSpeed::GetSpeed() const
		{
			return GetDataVal();
		}

		// var
		void GadSpeed::SetSpeedMsVar(const double_t v_s)
		{
			SetDataVarSingle(v_s);
		}

		void GadSpeed::SetSpeedPulsedVar(const double_t v_s, const double_t v_sf)
		{
			SetDataVarDiag(v_s, v_sf, 0.0);
		}

		void GadSpeed::SetSpeedPulsedVarPeriod(const double_t v_s, const double_t v_sf, const double_t v_p)
		{
			SetDataVarDiag(v_s, v_sf, v_p);
		}

		const container_double6_t& GadSpeed::GetSpeedVar() const
		{
			return GetDataVar();
		}

		// loc
		void GadSpeed::SetAidingLeverArmFixed(const double_t x, const double_t y, const double_t z)
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_FIXED));
#else
			SetLocMode(static_cast<uint8_t>(LOC_FIXED));
#endif
			SetLocVal(x, y, z);
		}

		void GadSpeed::SetAidingLeverArmConfig()
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_CONFIG));
#else
			SetLocMode(static_cast<uint8_t>(LOC_CONFIG));
#endif
			SetLocVal(0.0, 0.0, 0.0);
		}
		const container_double3_t& GadSpeed::GetAidingLeverArm() const
		{
			return GetLocVal();
		}
		void GadSpeed::SetAidingLeverArmVar(const double_t x, const double_t y, const double_t z)
		{
			SetLocVarDiag(x, y, z);
		}
		const container_double6_t& GadSpeed::GetAidingLeverArmVar() const
		{
			return GetLocVar();
		}

		//==============================================================================
		// GadAttitude
		GadAttitude::GadAttitude() : 
#ifdef OXTS_ENABLE_CPP11
			Gad(DEFAULT_STREAM_ID, static_cast<int8_t>(GEN_TYPE::GEN_ATT)) 
#else
			Gad(DEFAULT_STREAM_ID, static_cast<int8_t>(GEN_ATT)) 
#endif
		{

		}

		GadAttitude::GadAttitude(const uint8_t stream_id) : 
#ifdef OXTS_ENABLE_CPP11
			Gad(stream_id, static_cast<int8_t>(GEN_TYPE::GEN_ATT)) 
#else
			Gad(stream_id, static_cast<int8_t>(GEN_ATT)) 
#endif
		{

		}

		// val
		void GadAttitude::SetAtt(const double_t heading, const double_t pitch, const double_t roll)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(ATT_SYS_TYPE::ATT_SYS_HPR));
#else
			SetDataValType(static_cast<uint8_t>(ATT_SYS_HPR));
#endif
			SetDataVal(heading, pitch, roll);
		}

		void GadAttitude::SetAttLocal(const double_t heading, const double_t pitch, const double_t roll)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(ATT_SYS_TYPE::ATT_SYS_LOCAL));
#else
			SetDataValType(static_cast<uint8_t>(ATT_SYS_LOCAL));
#endif
			SetDataVal(heading, pitch, roll);
		}

		const container_double3_t& GadAttitude::GetAtt() const
		{
			return GetDataVal();
		}

		void GadAttitude::SetAttVar(const double_t v_h, const double_t v_p, const double_t v_r)
		{
			SetDataVarDiag(v_h, v_p, v_r);
		}

		const container_double6_t& GadAttitude::GetAttVar() const
		{
			return GetDataVar();
		}
		// loc 
		const container_double3_t& GadAttitude::GetAidingAlignment() const
		{
			return GetLocVal();
		}

		void GadAttitude::SetAidingAlignmentFixed(const double_t x, const double_t y, const double_t z)
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_FIXED));
#else
			SetLocMode(static_cast<uint8_t>(LOC_FIXED));
#endif
			SetLocVal(x, y, z);
		}

		void GadAttitude::SetAidingAlignmentOptimising()
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_KF));
#else
			SetLocMode(static_cast<uint8_t>(LOC_KF));
#endif
			SetLocVal(0.0, 0.0, 0.0);
		}

		void GadAttitude::SetAidingAlignmentConfig()
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_CONFIG));
#else
			SetLocMode(static_cast<uint8_t>(LOC_CONFIG));
#endif
			SetLocVal(0.0, 0.0, 0.0);
		}

		// In here was orignally SetData rather than SetLoc
		void GadAttitude::SetAidingAlignmentVar(const double_t x, const double_t y, const double_t z)
		{
			SetLocVarDiag(x, y, z);
		}

		const container_double6_t& GadAttitude::GetAidingAlignmentVar() const
		{
			return GetLocVar();
		}

		//==============================================================================
		// GadHeading
		GadHeading::GadHeading() : 
#ifdef OXTS_ENABLE_CPP11
			Gad(DEFAULT_STREAM_ID, static_cast<int8_t>(GEN_TYPE::GEN_HEADING)) 
#else
			Gad(DEFAULT_STREAM_ID, static_cast<int8_t>(GEN_HEADING)) 
#endif
		{

		}

		GadHeading::GadHeading(const uint8_t stream_id) : 
#ifdef OXTS_ENABLE_CPP11
			Gad(stream_id, static_cast<int8_t>(GEN_TYPE::GEN_HEADING)) 
#else
			Gad(stream_id, static_cast<int8_t>(GEN_HEADING)) 
#endif
		{

		}

		// val
		void GadHeading::SetHeading(const double_t heading)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(HEA_SYS_TYPE::HEA_SYS_NAV));
#else
			SetDataValType(static_cast<uint8_t>(HEA_SYS_NAV));
#endif
			SetDataVal(heading, 0.0, 0.0);
		}
		void GadHeading::SetHeadingLocal(const double_t heading)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(HEA_SYS_TYPE::HEA_SYS_LOCAL));
#else
			SetDataValType(static_cast<uint8_t>(HEA_SYS_LOCAL));
#endif
			SetDataVal(heading, 0.0, 0.0);
		}

		double_t GadHeading::GetHeading() const
		{
			double_t ret_val = 0.0;
			const container_double3_t& val = GetDataVal();
			if (val.size() > 0U)
			{
				ret_val = val[0U];
			}
			return ret_val;
		}

		void GadHeading::SetHeadingVar(const double_t v_h)
		{
			SetDataVarSingle(v_h);
		}

		double_t GadHeading::GetHeadingVar() const
		{
			double_t ret_val = 0.0;
			const container_double6_t& var = GetDataVar();
			if (var.size() > 0U)
			{
				ret_val = var[0U];
			}
			return ret_val;
		}
		// loc 
		const container_double3_t& GadHeading::GetAidingAlignment() const
		{
			return GetLocVal();
		}

		void GadHeading::SetAidingAlignmentFixed(const double_t h, const double_t p, const double_t r)
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_FIXED));
#else
			SetLocMode(static_cast<uint8_t>(LOC_FIXED));
#endif
			SetLocVal(h, p, r);
		}

		void GadHeading::SetAidingAlignmentConfig()
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_CONFIG));
#else
			SetLocMode(static_cast<uint8_t>(LOC_CONFIG));
#endif
			SetLocVal(0.0, 0.0, 0.0);
		}


		void GadHeading::SetAidingAlignmentVar(const double_t h_v, const double_t p_v, const double_t r_v)
		{
			SetLocVarDiag(h_v, p_v, r_v);
		}

		const container_double6_t& GadHeading::GetAidingAlignmentVar() const
		{
			return GetLocVar();
		}

		//==============================================================================
		// GadAngularRate
		GadAngularRate::GadAngularRate() : 
#ifdef OXTS_ENABLE_CPP11
			Gad(DEFAULT_STREAM_ID, static_cast<int8_t>(GEN_TYPE::GEN_ANGRATE)) 
#else
			Gad(DEFAULT_STREAM_ID, static_cast<int8_t>(GEN_ANGRATE)) 
#endif
		{

		}

		GadAngularRate::GadAngularRate(const uint8_t stream_id) : 
#ifdef OXTS_ENABLE_CPP11
			Gad(stream_id, static_cast<int8_t>(GEN_TYPE::GEN_ANGRATE)) 
#else
			Gad(stream_id, static_cast<int8_t>(GEN_ANGRATE)) 
#endif
		{

		}

		// val
		void GadAngularRate::SetAngularRate(double_t wx, double_t wy, double_t wz)
		{
			SetDataMode(0U);
#ifdef OXTS_ENABLE_CPP11
			SetDataValType(static_cast<uint8_t>(ANG_SYS_TYPE::ANG_SYS_SENSOR));
#else
			SetDataValType(static_cast<uint8_t>(ANG_SYS_SENSOR));
#endif
			SetDataVal(wx, wy, wz);
		}

		const container_double3_t& GadAngularRate::GetAngularRate() const
		{
			return GetDataVal();
		}

		void GadAngularRate::SetAngularRateVar(double_t v_wx, double_t v_wy, double_t v_wz)
		{
			SetDataVarDiag(v_wx, v_wy, v_wz);
		}

		const container_double6_t& GadAngularRate::GetAngularRateVar() const
		{
			return GetDataVar();
		}
		// loc 
		const container_double3_t& GadAngularRate::GetAidingAlignment() const
		{
			return GetLocVal();
		}

		void GadAngularRate::SetAidingAlignmentFixed(double_t h, double_t p, double_t r)
		{
			SetLocMode(LOC_SYS::LOC_FIXED);
			SetLocVal(h, p, r);
		}

		void GadAngularRate::SetAidingAlignmentConfig()
		{
#ifdef OXTS_ENABLE_CPP11
			SetLocMode(static_cast<uint8_t>(LOC_SYS::LOC_CONFIG));
#else
			SetLocMode(static_cast<uint8_t>(LOC_CONFIG));
#endif
			SetLocVal(0.0, 0.0, 0.0);
		}

		void GadAngularRate::SetAidingAlignmentVar(double_t v_h, double_t v_p, double_t v_r)
		{
			SetLocVarDiag(v_h, v_p, v_r);
		}

		const container_double6_t& GadAngularRate::GetAidingAlignmentVar() const
		{
			return GetLocVar();
		}
	} // namespace Gal_Cpp
} // namespace OxTS
