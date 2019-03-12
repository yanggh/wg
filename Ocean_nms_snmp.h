#ifndef _OCEAN_NMS_SNMP_H_
#define _OCEAN_NMS_SNMP_H_

//snmp++协议库
#include <string>
#include <map>

#include "snmp_pp/snmp_pp.h"
#include "devcollector_msg.pb.h"
#include "msg_common.pb.h"

#include "oid_def.h"
#include "struct_def.h"

using namespace std;
using namespace Snmp_pp;
using namespace mpfmessage;

class COceanNmsSnmp
{
public:
	/*! 默认构造函数
	*
	*
	*
	*
	*/
	COceanNmsSnmp(void);
	/*! 析构函数
	*
	*
	*
	*
	*/
	virtual ~COceanNmsSnmp(void);

	/*! 构造函数
	* pszIP 目的IP地址， 形式为IP:PORT。当PORT为默认的161时，可省略不写。输入参数
	*
	*
	*
	*/
	COceanNmsSnmp(char* pszIp);
	/*! 构造函数
	* pszIp 目的IP地址，不带端口
	* szReadCommunity
	* szWriteCommunity
	* nSnmpVersion snmp版本
	* szProt 默认为161
	*/
	COceanNmsSnmp(SnmpInfo *pSnmpInfo, char* pszIp, const char* szReadCommunity, const char* szWriteCommunity, int nSnmpVersion, int &status_flag, char* szPort = "161");

	COceanNmsSnmp(SnmpInfo *pSnmpInfo, SnmpBasePara *pSnmpBasePara, SnmpExtPara *pSnmpExtPara, int nSnmpVersion, int &status_flag);

	/*! 获取通用设备资源接口
	* pcomdevres 通用设备资源结构。输出参数
	* 成功返回true，失败返回false
	*/
	bool	get_common_dev_res(pCOMDEVRES pcomdevres);
	/*! 获取主机资源接口
	* phostres 主机资源结构，输出参数
	* 成功返回true，失败返回false
	*
	*
	*/
	bool	get_host_res(pHOSTRES phostres);
	/*! 获取接口资源接口
	* pifres 接口资源结构，输出参数
	* 成功返回true，失败返回false
	*
	*
	*/
	bool	get_interface_res(pIFRES pifres);
	/*! 获取主机性能接口
	* phostperf 主机性能结构，输出参数
	* 成功返回true，失败返回false
	*
	*
	*/
	bool	get_host_perf(pHOSTPERF phostperf, int flag = 0);
	/*! 获取主机进程和软件接口
	* phostperf 主机性能结构，输出参数
	* 成功返回true，失败返回false
	*
	*
	*/
	bool get_host_proc_soft(pHOSTPERF phostperf, int os_flag);
	/*! 获取接口性能接口
	* vecifperf 接口性能结构，输出参数
	* 成功返回true，失败返回false
	*
	*
	*/
	bool	get_interface_perf(vector<IFPERF>& vecifperf);
	bool get_interface_perf(map<int, IFPERF>& mapifperf);

	bool get_room_sensor_res(vector<ROOMSENSORRES>& vecRoomSensorRes);
	/*! 获取机房环境参数
	* proomsensorres机房环境参数结构,输出参数
	* 成功返回true，失败返回false
	*/
	bool get_room_environment_para(vector<ROOMENVIRPARA>& vecRoomEnvirPara);

	bool get_room_inlet_sensor_res(vector<ROOMINLETSENSORRES>& vecRoomInletSensorRes);

	bool get_room_intel_environment_para(vector<ROOMENVIRPARA>& vecRoomEnvirPara);

protected:
	UdpAddress	m_ipAddr;
	SnmpTarget  *m_target = NULL;
	Pdu m_pdu;
	v3MP *m_v3_MP = NULL;
	/*! 根据oid获取对应的接口性能参数
	* szoid 接口oid
	* snmp snmp对象
	* vecifperf  得到的接口性能参数 输入输出参数
	* 成功返回true，失败返回false
	*/
	virtual bool get_interface_perf(string szoid, Snmp& snmp, vector<IFPERF>& vecifperf);
	bool get_interface_perf(string szoid, Snmp& snmp, map<int, IFPERF>& mapifperf);
	/*! 获取主机资源中CPU型号，CPU编号列表
	* szoid CPU型号或CPU编号列表oid
	* snmp snmp对象
	* phostres 主机资源
	* nbegin 根据hrDeviceType得到的开始索引
	* nend 根据hrDeviceType得到的结束索引
	* 成功返回true，失败返回false
	*/
	virtual bool get_host_res_dev_processor(string szoid, Snmp& snmp, pHOSTRES phostres, int& nbegin, int& nend);
	/*! 获取主机资源中CPU型号，CPU编号列表
	* snmp snmp对象
	* phostres 主机资源
	* 成功返回true，失败返回false
	*
	*/
	bool get_host_res_dev_processor(Snmp& snmp, pHOSTRES phostres);
	/*! 获取主机资源的磁盘总空间
	* snmp snmp对象
	* phostres 主机资源
	*
	* 成功返回true，失败返回false
	*/
	virtual bool get_host_res_disk_capacity(Snmp& snmp, pHOSTRES phostres);
	/*! 获取主机资源的磁盘分区列表参数
	* snmp snmp对象
	* phostres 主机资源
	*
	* 成功返回true，失败返回false
	*/
	bool get_host_res_disk_partition(Snmp& snmp, pHOSTRES phostres);
	/*! 获取主机资源的磁盘分区列表
	* szoid 分区索引，分区名称，分区大小的oid
	* snmp snmp对象
	* vecdisk_partition 磁盘分区列表数据
	* 成功返回true，失败返回false
	*/
	//bool get_host_res_disk_partition(string szoid, Snmp& snmp, vector<DISKPARTITION>& vecdisk_partition);
	virtual bool get_host_res_disk_partition(string szoid, Snmp& snmp, vector<STORAGEFIXEDDISK>& vecdisk_partition, int& nFixedDiskBegin, int& nFixedDiskEnd);
	/*! 获取主机资源的磁盘基本信息参数
	* snmp snmp对象
	* phostres 主机资源
	*
	* 成功返回true，失败返回false
	*/
	bool get_host_res_disk_info(Snmp& snmp, pHOSTRES phostres);
	/*! 获取主机资源的基本信息
	* szoid 磁盘信息oid
	* snmp snmp对象
	* vecdisk_partition 磁盘分区列表数据
	* 成功返回true，失败返回false
	*/
	virtual bool get_host_res_disk_info(string szoid, Snmp& snmp, vector<DISKSTORAGE>& vecdisk_storage);
	/*! 获取接口资源
	* szoid 接口数据对应的oid
	* snmp snmp对象
	* vecifr 接口资源数据
	* 成功返回true，失败返回false
	*/
	virtual bool get_interface_res(string szoid, Snmp& snmp, vector<IFR>& vecifr);
	/*! 获取接口资源的IP数据
	* szoid 接口ip地址，接口ip掩码的oid
	* snmp snmp对象
	* vecentip 接口IP数据
	* 成功返回true，失败返回false
	*/
	virtual bool get_interface_res_ent_ip(string szoid, Snmp& snmp, vector< ENTIP >& vecentip);
	/*! 获取主机性能的CPU负载
	* szoid 负载对应的oid
	* snmp snmp对象
	* vecprocessorload CPU负载数据
	* 成功返回true，失败返回false
	*/
	virtual bool get_host_perf_processor_load(string szoid, Snmp& snmp, vector<int>& vecprocessorload);
	/*!获取主机性能的虚拟内存大小，虚拟内存已使用，物理内存大小，物理内存已使用，磁盘分区数据
	* snmp snmp对象
	* phostperf 主机性能数据
	*
	* 成功返回true，失败返回false
	*/
	bool get_host_perf_storage(Snmp& snmp, pHOSTPERF phostperf);

	/*!根据hrStorageType获取主机性能的虚拟内存大小，虚拟内存已使用，物理内存大小，物理内存已使用，磁盘分区数据
	* szoid hrStorageType，hrStorageDescr，hrStorageSize， hrStorageUsed对应的oid
	* snmp snmp对象
	* phostperf 主机性能数据
	* nRam 根据hrStorageType的到的物理内存所在的索引
	* nVirtualMemory 根据hrStorageType得到的虚拟内存所在的索引
	* nFixedDiskBegin 根据hrStorageType得到的磁盘分区开始的索引
	* nFixedDiskend 根据hrStorageType得到的磁盘分区结束的索引
	* 成功返回true，失败返回false
	*/
	virtual bool get_host_perf_storage(string szoid, Snmp& snmp, pHOSTPERF phostperf, int& nRam, int& nVirtualMemory, int &nMemoryBuf, int &nCachedMem, int& nFixedDiskBegin, int& nFixedDiskEnd);
	/*! 获取主机性能的进程性能列表数据
	* snmp snmp对象
	* vecswrun 进程性能列表数据
	*
	* 成功返回true，失败返回false
	*/
	bool get_host_perf_swrun(Snmp& snmp, vector<SWRUN>& vecswrun);
	/*! 根据进程性能的参数oid得到对应数据
	* szoid 进程性能的参数oid
	* snmp snmp对象
	* vecswrun 进程性能列表数据
	* 成功返回true，失败返回false
	*/
	bool get_host_perf_swrun(string szoid, Snmp& snmp, vector<SWRUN>& vecswrun);
	/*! 获取主机性能的已安装软件列表数据
	* snmp snmp对象
	* vecInstalled 已安装软件数据
	* 成功返回true，失败返回false
	*/
	bool get_host_perf_installed(Snmp& snmp, vector<INSTALLED>& vecInstalled);
	/*! 根据已安装软件对应oid获取数据
	* szoid 已安装软件数据的oid
	* snmp snmp对象
	* vecInstalled 已安装软件数据
	* 成功返回true，失败返回false
	*/
	bool get_host_perf_installed(string szoid, Snmp& snmp, vector<INSTALLED>& vecInstalled);

	/*! 将内存里的日期数据格式化为 2015-3-25 12:12:12.000的形式
	* szvalue 日期数据，输入参数
	* szdate 格式化后的结果， 输出参数
	*
	*
	*/

	bool get_room_sensor_res(string szoid, Snmp& snmp, vector<ROOMSENSORRES>& vecRoomSensorRes);
	/*! 获取机房环境参数
	* szoid 机房环境数据对应的oid
	* snmp snmp对象
	* proomsensorres 机房环境参数结构
	* 成功返回true，失败返回false
	*/
	bool get_room_environment_para(string szoid, Snmp& snmp, vector<ROOMENVIRPARA>& vecRoomEnvirPara);
	/*! 将内存里的日期数据格式化为 2015-3-25 12:12:12.000的形式
	* szvalue 日期数据，输入参数
	* szdate 格式化后的结果， 输出参数
	*
	*
	*/

	bool get_room_inlet_sensor_res(string szoid, Snmp& snmp, vector<ROOMINLETSENSORRES>& vecRoomInletSensorRes);

	void format_date(const char* szvalue, char* szdate);
};

void  snmp_collect(HOSTPERF& hostperf, MsgGetHostFileSystemListReq *pHostFileSystemReq, SnmpBasePara *pSnmpBasePara, const snmp_version version);
void snmp_collect(MsgGetHostFileSystemListReq *pHostFileSystemReq, SnmpBasePara *pSnmpBasePara, SnmpExtPara *pSnmpExtPara, MsgGetHostFileSystemListResp *pHostFileSystemResp, const snmp_version version);
ostream& operator<<(ostream& out,const SWRUN& vrun);


#endif
