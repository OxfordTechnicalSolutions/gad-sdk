#include "oxts/gal-cpp/gad.hpp"

using std::vector;

namespace OxTS
{
	//==============================================================================
	// Gen3d

	Gen3d::Gen3d() : GEN_3D()
	{
		SetMode(0);
		SetValType(0);
		SetVal(0.0, 0.0, 0.0);
		SetVarUpperDiag(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	}

	Gen3d::Gen3d(const GEN_3D& g) : GEN_3D()
	{
		SetMode(g.mode);
		SetValType(g.x_type);
		SetVal(g.x[0], g.x[1], g.x[2]);
		v_type = g.v_type;
		switch (g.v_type)
		{
		case GEN_VAR_TYPE::GEN_VAR_HMAT:
			SetVarUpperDiag(g.v[0], g.v[1], g.v[2], g.v[3], g.v[4], g.v[5]);
			break;
		case GEN_VAR_TYPE::GEN_VAR_DIAG:
			SetVarDiag(g.v[0], g.v[1], g.v[2]);
			break;
		case GEN_VAR_TYPE::GEN_VAR_SINGLE:
			SetVarSingle(g.v[0]);
			break;
		default:
			break;
		}
	}

	int  Gen3d::GetVarType() const { return static_cast<int>(v_type); }

	GEN_3D Gen3d::getCStruct() const
	{
		GEN_3D g;
		g.mode = GetMode();
		g.v_type = GetValType();
		g.x[0] = GetValX();
		g.x[1] = GetValY();
		g.x[2] = GetValZ();
		g.v_type = GetVarType();
		std::vector<double> cov = GetVar();
		for (int i = 0; i < cov.size(); ++i)
		{
			g.v[i] = cov.at(i);
		}

		return g;
	}

	void Gen3d::SetMode(int mode) { this->mode = mode; }
	int Gen3d::GetMode() const { return mode; }

	void Gen3d::SetValType(int x_type) { this->x_type = x_type; }
	int Gen3d::GetValType() const { return x_type; }

	void Gen3d::SetValX(double x) { this->x[0] = x; }
	double Gen3d::GetValX() const { return x[0]; }
	void Gen3d::SetValY(double y) { x[1] = y; }
	double Gen3d::GetValY() const { return x[1]; }
	void Gen3d::SetValZ(double z) { x[2] = z; }
	double Gen3d::GetValZ() const { return x[2]; }

	void Gen3d::SetVal(double x, double y, double z)
	{
		SetValX(x);
		SetValY(y);
		SetValZ(z);
	}
	std::vector<double> Gen3d::GetVal() const
	{
		return std::vector<double> {GetValX(), GetValY(), GetValZ()};
	}

	void Gen3d::SetVarUpperDiag(double v_00, double v_11, double v_22,
		double v_01, double v_02, double v_12)
	{
		v_type = GEN_VAR_TYPE::GEN_VAR_HMAT;
		v[0] = v_00;
		v[1] = v_11;
		v[2] = v_22;
		v[3] = v_01;
		v[4] = v_02;
		v[5] = v_12;
	}

	void Gen3d::SetVarDiag(double v_00, double v_11, double v_22)
	{
		v_type = GEN_VAR_TYPE::GEN_VAR_DIAG;
		v[0] = v_00;
		v[1] = v_11;
		v[2] = v_22;
		v[3] = 0.0;
		v[4] = 0.0;
		v[5] = 0.0;
	}

	void Gen3d::SetVarSingle(double v_0)
	{
		v_type = GEN_VAR_TYPE::GEN_VAR_SINGLE;
		v[0] = v_0;
		v[1] = 0.0;
		v[2] = 0.0;
		v[3] = 0.0;
		v[4] = 0.0;
		v[5] = 0.0;
	}

	std::vector<double> Gen3d::GetVar() const
	{
		std::vector<double> cov;
		int length = 0;

		switch (v_type)
		{
		case GEN_VAR_TYPE::GEN_VAR_HMAT:
			length = 6;
			break;
		case GEN_VAR_TYPE::GEN_VAR_DIAG:
			length = 3;
			break;
		case GEN_VAR_TYPE::GEN_VAR_SINGLE:
			length = 1;
			break;
		}

		for (int i = 0; i < length; ++i) {
			cov.push_back(v[i]);
		}

		return cov;
	}


	//==============================================================================
	// Gad superclass
	const int DEFAULT_STREAM_ID = 128;
	// Default Constructor
	Gad::Gad() :
		stream_id(DEFAULT_STREAM_ID),
		type(GEN_TYPE::GEN_VOID)
	{}
	// Constructor
	Gad::Gad(uint8_t stream_id, int8_t aiding_type) :
		stream_id(stream_id),
		type(aiding_type)
	{}

	Gad::~Gad() = default;
	Gad::Gad(const Gad& g) = default;
	Gad& Gad::operator=(const Gad& g) = default;

	Gad::Gad(const GEN_AIDING_DATA& g)
	{
		//call assignment operator
		*this = g;
	}

	Gad& Gad::operator=(const GEN_AIDING_DATA& g)
	{
		SetDataType(g.type);
		SetStreamId(g.stream_id);
		val = Gen3d(g.val);
		val_valid = g.val_valid;
		time = Gen3d(g.time);
		time_valid = g.time_valid;
		loc = Gen3d(g.loc);
		loc_valid = g.loc_valid;
		res1 = Gen3d(g.res1);
		res1_valid = g.res1_valid;
		res2 = Gen3d(g.res2);
		res2_valid = g.res2_valid;
		acq = g.acq;
		acq_valid = g.acq_valid;
		return *this;
	}

	GEN_AIDING_DATA Gad::getCStruct()
	{
		GEN_AIDING_DATA g;
		g.type = GetDataType();
		g.stream_id = GetStreamId();
		g.val = GEN_3D(val);
		g.val_valid = val_valid;
		g.time = GEN_3D(time);
		g.time_valid = time_valid;
		g.loc = GEN_3D(loc);
		g.loc_valid = loc_valid;
		g.res1 = GEN_3D(res1);
		g.res1_valid = res1_valid;
		g.res2 = GEN_3D(res2);
		g.res2_valid = res2_valid;
		g.acq = acq;
		g.acq_valid = acq_valid;

		return g;
	}


	// streamId
	void Gad::SetStreamId(int id) { stream_id = id; }
	int  Gad::GetStreamId() const { return stream_id; }
	// type 
	void Gad::SetDataType(int type) { this->type = type; }
	int  Gad::GetDataType() const { return type; }
	// val
	void Gad::SetValValid(bool flag) { val_valid = flag; }
	bool Gad::GetValValid() const { return val_valid; }

	void Gad::SetDataMode(int mode) { val.SetMode(mode); }
	void Gad::SetDataValType(int x_type) { val.SetValType(x_type); }
	void Gad::SetDataVal(double x_0, double x_1, double x_2)
	{
		SetValValid(true);
		val.SetVal(x_0, x_1, x_2);
	}

	std::vector<double> Gad::GetDataVal() const
	{
		return val.GetVal();
	}

	void Gad::SetDataVarUpperDiag(double v_00, double v_11, double v_22,
		double v_01, double v_02, double v_12)
	{
		val.SetVarUpperDiag(v_00, v_11, v_22, v_01, v_02, v_12);
	}

	void Gad::SetDataVarDiag(double v_00, double v_11, double v_22)
	{
		val.SetVarDiag(v_00, v_11, v_22);
	}

	void Gad::SetDataVarSingle(double v_0)
	{
		val.SetVarSingle(v_0);
	}

	std::vector<double> Gad::GetDataVar() const
	{
		return val.GetVar();
	}

	// time
	void Gad::SetTimeValid(bool flag) { time_valid = flag; }
	bool Gad::GetTimeValid() const { return time_valid; }
	//
	void Gad::SetTimeExternal(double week, double secs)
	{
		SetTimeValid(true);
		time.SetMode(0);
		time.SetValType(TIME_SYS::TIME_EXT);
		time.SetVal(week, secs, 0.0);
	}
	double Gad::GetTimeExternalWeek() const { return time.GetValX(); }
	double Gad::GetTimeExternalSecondsFromSunday() const { return time.GetValY(); }
	std::vector<double> Gad::GetTimeExternal() const
	{
		return std::vector<double>{GetTimeExternalWeek(), GetTimeExternalSecondsFromSunday()};
	}
	// GPS
	void Gad::SetTimeGps(double week, double seconds_from_sunday)
	{
		SetTimeValid(true);
		time.SetMode(0);
		time.SetValType(TIME_SYS::TIME_GPS);
		time.SetVal(week, seconds_from_sunday, 0);
	}
	std::vector<double> Gad::GetTimeGps() const
	{
		return std::vector<double>{GetTimeGpsWeek(), GetTimeGpsSecondsFromSunday()};
	}
	double Gad::GetTimeGpsWeek() const { return time.GetValX(); }
	double Gad::GetTimeGpsSecondsFromSunday() const { return time.GetValY(); }

	// TAI
	void Gad::SetTimeTAI(double secs)
	{
		SetTimeValid(true);
		time.SetMode(0);
		time.SetValType(TIME_SYS::TIME_TAI);
		time.SetVal(secs, 0.0, 0.0);
	}
	double Gad::GetTimeTAI() const { return time.GetValX(); }

	// PPS
	void Gad::SetTimePpsRelative(double ns)
	{
		SetTimeValid(true);
		time.SetMode(0);
		time.SetValType(TIME_SYS::TIME_PPS_RELATIVE);
		time.SetVal(0.0, 0.0, ns);
	}
	double Gad::GetTimePpsRelative() const { return time.GetValZ(); }
	// Latency
	void   Gad::SetTimeLatency(double ns)
	{
		SetTimeValid(true);
		time.SetMode(0);
		time.SetValType(TIME_SYS::TIME_EST_LATENCY);
		time.SetVal(0.0, ns, 0.0);
	}
	double Gad::GetTimeLatency() const { return time.GetValY(); }
	// UTC - Unix
	void Gad::SetTimeUTCUnix(double secs)
	{
		SetTimeValid(true);
		time.SetMode(0);
		time.SetValType(TIME_SYS::TIME_UNIX_UTC);
		time.SetVal(secs, 0.0, 0.0);
	}
	double Gad::GetTimeUTCUnix() const { return time.GetValX(); }
	// Void
	void   Gad::SetTimeVoid()
	{
		SetTimeValid(true);
		time.SetMode(0);
		time.SetValType(TIME_SYS::TIME_VOID);
	}

	// loc  
	void Gad::SetLocValid(bool flag) { loc_valid = flag; }
	bool Gad::GetLocValid() const { return loc_valid; }

	void Gad::SetLocMode(int mode) { loc.SetMode(mode); }
	void Gad::SetLocValType(int x_type) { loc.SetValType(x_type); }
	void Gad::SetLocVal(double x_0, double x_11, double x_22)
	{
		SetLocValid(true);
		loc.SetVal(x_0, x_11, x_22);
	}
	std::vector<double> Gad::GetLocVal() const
	{
		return loc.GetVal();
	}
	void Gad::SetLocVarUpperDiag(double v_00, double v_11, double v_22,
		double v_01, double v_02, double v_12)
	{
		loc.SetVarUpperDiag(v_00, v_11, v_22, v_01, v_02, v_12);
	}
	void Gad::SetLocVarDiag(double v_00, double v_11, double v_22)
	{
		loc.SetVarDiag(v_00, v_11, v_22);
	}
	void Gad::SetLocVarSingle(double v_0)
	{
		loc.SetVarSingle(v_0);
	}
	std::vector<double> Gad::GetLocVar() const
	{
		return loc.GetVar();
	}

	void Gad::SetRes1Valid(bool flag) { res1_valid = flag; }
	bool Gad::GetRes1Valid() const { return res1_valid; }
	void Gad::SetRes2Valid(bool flag) { res2_valid = flag; }
	bool Gad::GetRes2Valid() const { return res2_valid; }
	void Gad::SetAcqValid(bool flag) { acq_valid = flag; }
	bool Gad::GetAcqValid() const { return acq_valid; }

	void Gad::SetAcqTimestamp(uint32_t acq_time)
	{
		acq = acq_time;
		acq_valid = 1;
	}
	uint32_t Gad::GetAcqTimestamp() const
	{
		return acq;
	}

	//==============================================================================
	// GadPosition

	GadPosition::GadPosition(uint8_t stream_id) : Gad(stream_id, GEN_TYPE::GEN_POS) {}

	void GadPosition::SetPosGeodetic(double lat, double lon, double alt)
	{
		SetDataMode(0);
		SetDataValType(POS_SYS_TYPE::POS_SYS_WGS84);
		SetDataVal(lat, lon, alt);
	}

	void GadPosition::SetPosLocal(double x, double y, double z)
	{
		SetDataMode(0);
		SetDataValType(POS_SYS_TYPE::POS_SYS_LOCAL);
		SetDataVal(x, y, z);
	}

	std::vector<double> GadPosition::GetPos() const
	{
		return GetDataVal();
	}

	void GadPosition::SetPosGeodeticVar(double v_n, double v_e, double v_d)
	{
		SetDataVarDiag(v_n, v_e, v_d);
	}

	void GadPosition::SetPosGeodeticVar(
		double v_00, double v_11, double v_22,
		double v_01, double v_02, double v_12
	) {
		SetDataVarUpperDiag(v_00, v_11, v_22, v_01, v_02, v_12);
	}

	void GadPosition::SetPosLocalVar(double v_x, double v_y, double v_z)
	{
		SetDataVarDiag(v_x, v_y, v_z);
	}

	void GadPosition::SetPosLocalVar(
		double v_xx, double v_yy, double v_zz,
		double v_xy, double v_xz, double v_yz
	) {
		SetDataVarUpperDiag(v_xx, v_yy, v_zz, v_xy, v_xz, v_yz);
	}

	std::vector<double> GadPosition::GetPosVar() const
	{
		return GetDataVar();
	}

	void GadPosition::SetAidingLeverArmFixed(double x, double y, double z)
	{
		SetLocMode(LOC_SYS::LOC_FIXED);
		SetLocVal(x, y, z);
	}

	std::vector<double> GadPosition::GetAidingLeverArm() const
	{
		return GetLocVal();
	}

	void GadPosition::SetAidingLeverArmOptimising()
	{
		SetLocMode(LOC_SYS::LOC_KF);
		SetLocVal(0.0, 0.0, 0.0);
	}

	void GadPosition::SetAidingLeverArmConfig()
	{
		SetLocMode(LOC_SYS::LOC_CONFIG);
		SetLocVal(0.0, 0.0, 0.0);
	}

	void GadPosition::SetAidingLeverArmVar(double x, double y, double z)
	{
		SetLocVarDiag(x, y, z);
	}

	void GadPosition::SetAidingLeverArmVarUpperDiag(
		double v_xx, double v_yy, double v_zz,
		double v_xy, double v_xz, double v_yz)
	{
		SetLocVarUpperDiag(v_xx, v_yy, v_zz, v_xy, v_xz, v_yz);
	}

	std::vector<double> GadPosition::GetAidingLeverArmVar() const
	{
		return GetLocVar();
	}

	//==============================================================================
	// GadVelocity
	GadVelocity::GadVelocity(uint8_t stream_id) : Gad(stream_id, GEN_TYPE::GEN_VEL) {}

	// val
	void GadVelocity::SetVelNed(double v_n, double v_e, double v_d)
	{
		SetDataMode(0);
		SetDataValType(VEL_SYS_TYPE::VEL_SYS_NED);
		SetDataVal(v_n, v_e, v_d);
	}

	void GadVelocity::SetVelOdom(double v_x, double v_y, double v_z)
	{
		SetDataMode(0);
		SetDataValType(VEL_SYS_TYPE::VEL_SYS_ODO);
		SetDataVal(v_x, v_y, v_z);
	}

	void GadVelocity::SetVelLocal(double v_x, double v_y, double v_z)
	{
		SetDataMode(0);
		SetDataValType(VEL_SYS_TYPE::VEL_SYS_LOCAL);
		SetDataVal(v_x, v_y, v_z);
	}

	std::vector<double> GadVelocity::GetVel() const
	{
		return GetDataVal();
	}

	void GadVelocity::SetVelNedVar(double v_n, double v_e, double v_d)
	{
		SetDataVarDiag(v_n, v_e, v_d);
	}

	void GadVelocity::SetVelNedVar(
		double v_nn, double v_ee, double v_dd,
		double v_ne, double v_nd, double v_ed
	){
		SetDataVarUpperDiag(v_nn, v_ee, v_dd, v_ne, v_nd, v_ed);
	}

	void GadVelocity::SetVelOdomVar(double v_x, double v_y, double v_z)
	{
		SetDataVarDiag(v_x, v_y, v_z);
	}

	void GadVelocity::SetVelOdomVar(
		double v_xx, double v_yy, double v_zz,
		double v_xy, double v_xz, double v_yz
	) {
		SetDataVarUpperDiag(v_xx, v_yy, v_zz, v_xy, v_xz, v_yz);
	}

	void GadVelocity::SetVelLocalVar(double v_x, double v_y, double v_z)
	{
		SetDataVarDiag(v_x, v_y, v_z);
	}

	void GadVelocity::SetVelLocalVar(
		double v_xx, double v_yy, double v_zz,
		double v_xy, double v_xz, double v_yz
	) {
		SetDataVarUpperDiag(v_xx, v_yy, v_zz, v_xy, v_xz, v_yz);
	}

	std::vector<double> GadVelocity::GetVelVar() const
	{
		return GetDataVar();
	}

	// loc 
	void GadVelocity::SetAidingLeverArmFixed(double x, double y, double z)
	{
		SetLocMode(LOC_SYS::LOC_FIXED);
		SetLocVal(x, y, z);
	}

	std::vector<double> GadVelocity::GetAidingLeverArm() const
	{
		return GetLocVal();
	}

	void GadVelocity::SetAidingLeverArmConfig()
	{
		SetLocMode(LOC_SYS::LOC_CONFIG);
		SetLocVal(0.0, 0.0, 0.0);
	}
	void GadVelocity::SetAidingLeverArmOptimising()
	{
		SetLocMode(LOC_SYS::LOC_KF);
		SetLocVal(0.0, 0.0, 0.0);
	}
	void GadVelocity::SetAidingLeverArmVar(double x, double y, double z)
	{
		SetLocVarDiag(x, y, z);
	}

	std::vector<double> GadVelocity::GetAidingLeverArmVar() const
	{
		return GetLocVar();
	}
	//==============================================================================
	// GadSpeed
	GadSpeed::GadSpeed(uint8_t stream_id) : Gad(stream_id, GEN_TYPE::GEN_SPEED) {}

	// val
	void GadSpeed::SetSpeedFw(double speed)
	{
		SetDataMode(0);
		SetDataValType(SPEED_SYS_TYPE::SPEED_SYS_FW_VEL);
		SetDataVal(speed, 1.0, 0.0);
	}

	double GadSpeed::GetSpeedFw() const
	{
		return GetDataVal()[0];
	}

	void GadSpeed::SetSpeedFwVar(double v_s)
	{
		SetDataVarSingle(v_s);
	}

	double GadSpeed::GetSpeedFwVar() const
	{
		return GetDataVar()[0];
	}

	void GadSpeed::SetWheelspeedCount(double count, double period)
	{
		SetDataMode(0);
		SetDataValType(SPEED_SYS_TYPE::SPEED_SYS_FW_VEL);
		SetDataVal(count, period, 0.0);
	}

	std::vector<double> GadSpeed::GetWheelspeedCount() const
	{
		return std::vector<double>{GetDataVal()[0], GetDataVal()[1]};
	}

	void GadSpeed::SetWheelspeedVar(double v_c)
	{
		SetDataVarSingle(v_c);
	}

	double GadSpeed::GetWheelspeedVar() const
	{
		return GetDataVar()[0];
	}

	// loc 
	void GadSpeed::SetAidingLeverArmFixed(double x, double y, double z)
	{
		SetLocMode(LOC_SYS::LOC_FIXED);
		SetLocVal(x, y, z);
	}

	void GadSpeed::SetAidingLeverArmConfig()
	{
		SetLocMode(LOC_SYS::LOC_CONFIG);
		SetLocVal(0.0, 0.0, 0.0);
	}

	void GadSpeed::SetAidingLeverArmOptimising()
	{
		SetLocMode(LOC_SYS::LOC_KF);
		SetLocVal(0.0, 0.0, 0.0);
	}

	std::vector<double> GadSpeed::GetAidingLeverArm() const
	{
		return GetLocVal();
	}
	void GadSpeed::SetAidingLeverArmVar(double x, double y, double z)
	{
		SetLocVarDiag(x, y, z);
	}

	std::vector<double> GadSpeed::GetAidingLeverArmVar() const
	{
		return GetLocVar();
	}
	//==============================================================================
	// GadAttitude
	GadAttitude::GadAttitude() : Gad(DEFAULT_STREAM_ID, GEN_TYPE::GEN_ATT) {}

	GadAttitude::GadAttitude(uint8_t stream_id) : Gad(stream_id, GEN_TYPE::GEN_ATT) {}

	// val
	void GadAttitude::SetAtt(double heading, double pitch, double roll)
	{
		SetDataMode(0);
		SetDataValType(ATT_SYS_TYPE::ATT_SYS_HPR);
		SetDataVal(heading, pitch, roll);
	}
	
	void GadAttitude::SetAttLocal(double heading, double pitch, double roll)
	{
		SetDataMode(0);
		SetDataValType(ATT_SYS_TYPE::ATT_SYS_LOCAL);
		SetDataVal(heading,pitch,roll); 
	}

	std::vector<double> GadAttitude::GetAtt() const
	{
		return GetDataVal();
	}

	void GadAttitude::SetAttVar(double v_h, double v_p, double v_r)
	{
		SetDataVarDiag(v_h, v_p, v_r);
	}

	std::vector<double> GadAttitude::GetAttVar() const
	{
		return GetDataVar();
	}
	// loc 
	std::vector<double> GadAttitude::GetAidingAlignment() const
	{
		return GetLocVal();
	}

	void GadAttitude::SetAidingAlignmentFixed(double h, double p, double r)
	{
	   SetLocMode(LOC_SYS::LOC_FIXED);
	   SetLocVal(h,p,r);
	}

	void GadAttitude::SetAidingAlignmentOptimising()
	{
		SetLocMode(LOC_SYS::LOC_KF);
		SetLocVal(0.0, 0.0, 0.0);
	}

	// In here was orignally SetData rather than SetLoc
	void GadAttitude::SetAidingAlignmentVar(double h_v, double p_v, double r_v)
	{
		SetLocVarDiag(h_v, p_v, r_v);
	}

	std::vector<double> GadAttitude::GetAidingAlignmentVar() const
	{
		return GetLocVar();
	}

	//==============================================================================
	// GadHeading
	GadHeading::GadHeading() : Gad(DEFAULT_STREAM_ID, GEN_TYPE::GEN_HEADING) {}

	GadHeading::GadHeading(uint8_t stream_id) : Gad(stream_id, GEN_TYPE::GEN_HEADING) {}

	// val
	void GadHeading::SetHeading(double heading)
	{
		SetDataMode(0);
		SetDataValType(HEA_SYS_TYPE::HEA_SYS_NAV);
		SetDataVal(heading, 0.0, 0.0);
	}
	void GadHeading::SetHeadingLocal(double heading)
	{
		SetDataMode(0);
		SetDataValType(HEA_SYS_TYPE::HEA_SYS_LOCAL);
		SetDataVal(heading, 0.0, 0.0);
	}

	double GadHeading::GetHeading() const
	{
		return GetDataVal()[0];
	}

	void GadHeading::SetHeadingVar(double v_h)
	{
		SetDataVarSingle(v_h);
	}

	double GadHeading::GetHeadingVar() const
	{
		return GetDataVar()[0];
	}
	// loc 
	std::vector<double> GadHeading::GetAidingAlignment() const
	{
		return GetLocVal();
	}

	void GadHeading::SetAidingAlignmentFixed(double h, double p, double r)
	{
	  this->SetLocMode(LOC_SYS::LOC_FIXED);
	  this->SetLocVal(h, p, r);
	}

	void GadHeading::SetAidingAlignmentVar(double h_v, double p_v, double r_v)
	{
		SetLocVarDiag(h_v, p_v, r_v);
	}

	std::vector<double> GadHeading::GetAidingAlignmentVar() const
	{
		return GetLocVar();
	}

} // namespace OxTS
