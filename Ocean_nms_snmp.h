#ifndef _OCEAN_NMS_SNMP_H_
#define _OCEAN_NMS_SNMP_H_

//snmp++Э���
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
	/*! Ĭ�Ϲ��캯��
	*
	*
	*
	*
	*/
	COceanNmsSnmp(void);
	/*! ��������
	*
	*
	*
	*
	*/
	virtual ~COceanNmsSnmp(void);

	/*! ���캯��
	* pszIP Ŀ��IP��ַ�� ��ʽΪIP:PORT����PORTΪĬ�ϵ�161ʱ����ʡ�Բ�д���������
	*
	*
	*
	*/
	COceanNmsSnmp(char* pszIp);
	/*! ���캯��
	* pszIp Ŀ��IP��ַ�������˿�
	* szReadCommunity
	* szWriteCommunity
	* nSnmpVersion snmp�汾
	* szProt Ĭ��Ϊ161
	*/
	COceanNmsSnmp(SnmpInfo *pSnmpInfo, char* pszIp, const char* szReadCommunity, const char* szWriteCommunity, int nSnmpVersion, int &status_flag, char* szPort = "161");

	COceanNmsSnmp(SnmpInfo *pSnmpInfo, SnmpBasePara *pSnmpBasePara, SnmpExtPara *pSnmpExtPara, int nSnmpVersion, int &status_flag);

	/*! ��ȡͨ���豸��Դ�ӿ�
	* pcomdevres ͨ���豸��Դ�ṹ���������
	* �ɹ�����true��ʧ�ܷ���false
	*/
	bool	get_common_dev_res(pCOMDEVRES pcomdevres);
	/*! ��ȡ������Դ�ӿ�
	* phostres ������Դ�ṹ���������
	* �ɹ�����true��ʧ�ܷ���false
	*
	*
	*/
	bool	get_host_res(pHOSTRES phostres);
	/*! ��ȡ�ӿ���Դ�ӿ�
	* pifres �ӿ���Դ�ṹ���������
	* �ɹ�����true��ʧ�ܷ���false
	*
	*
	*/
	bool	get_interface_res(pIFRES pifres);
	/*! ��ȡ�������ܽӿ�
	* phostperf �������ܽṹ���������
	* �ɹ�����true��ʧ�ܷ���false
	*
	*
	*/
	bool	get_host_perf(pHOSTPERF phostperf, int flag = 0);
	/*! ��ȡ�������̺�����ӿ�
	* phostperf �������ܽṹ���������
	* �ɹ�����true��ʧ�ܷ���false
	*
	*
	*/
	bool get_host_proc_soft(pHOSTPERF phostperf, int os_flag);
	/*! ��ȡ�ӿ����ܽӿ�
	* vecifperf �ӿ����ܽṹ���������
	* �ɹ�����true��ʧ�ܷ���false
	*
	*
	*/
	bool	get_interface_perf(vector<IFPERF>& vecifperf);
	bool get_interface_perf(map<int, IFPERF>& mapifperf);

	bool get_room_sensor_res(vector<ROOMSENSORRES>& vecRoomSensorRes);
	/*! ��ȡ������������
	* proomsensorres�������������ṹ,�������
	* �ɹ�����true��ʧ�ܷ���false
	*/
	bool get_room_environment_para(vector<ROOMENVIRPARA>& vecRoomEnvirPara);

	bool get_room_inlet_sensor_res(vector<ROOMINLETSENSORRES>& vecRoomInletSensorRes);

	bool get_room_intel_environment_para(vector<ROOMENVIRPARA>& vecRoomEnvirPara);

protected:
	UdpAddress	m_ipAddr;
	SnmpTarget  *m_target = NULL;
	Pdu m_pdu;
	v3MP *m_v3_MP = NULL;
	/*! ����oid��ȡ��Ӧ�Ľӿ����ܲ���
	* szoid �ӿ�oid
	* snmp snmp����
	* vecifperf  �õ��Ľӿ����ܲ��� �����������
	* �ɹ�����true��ʧ�ܷ���false
	*/
	virtual bool get_interface_perf(string szoid, Snmp& snmp, vector<IFPERF>& vecifperf);
	bool get_interface_perf(string szoid, Snmp& snmp, map<int, IFPERF>& mapifperf);
	/*! ��ȡ������Դ��CPU�ͺţ�CPU����б�
	* szoid CPU�ͺŻ�CPU����б�oid
	* snmp snmp����
	* phostres ������Դ
	* nbegin ����hrDeviceType�õ��Ŀ�ʼ����
	* nend ����hrDeviceType�õ��Ľ�������
	* �ɹ�����true��ʧ�ܷ���false
	*/
	virtual bool get_host_res_dev_processor(string szoid, Snmp& snmp, pHOSTRES phostres, int& nbegin, int& nend);
	/*! ��ȡ������Դ��CPU�ͺţ�CPU����б�
	* snmp snmp����
	* phostres ������Դ
	* �ɹ�����true��ʧ�ܷ���false
	*
	*/
	bool get_host_res_dev_processor(Snmp& snmp, pHOSTRES phostres);
	/*! ��ȡ������Դ�Ĵ����ܿռ�
	* snmp snmp����
	* phostres ������Դ
	*
	* �ɹ�����true��ʧ�ܷ���false
	*/
	virtual bool get_host_res_disk_capacity(Snmp& snmp, pHOSTRES phostres);
	/*! ��ȡ������Դ�Ĵ��̷����б����
	* snmp snmp����
	* phostres ������Դ
	*
	* �ɹ�����true��ʧ�ܷ���false
	*/
	bool get_host_res_disk_partition(Snmp& snmp, pHOSTRES phostres);
	/*! ��ȡ������Դ�Ĵ��̷����б�
	* szoid �����������������ƣ�������С��oid
	* snmp snmp����
	* vecdisk_partition ���̷����б�����
	* �ɹ�����true��ʧ�ܷ���false
	*/
	//bool get_host_res_disk_partition(string szoid, Snmp& snmp, vector<DISKPARTITION>& vecdisk_partition);
	virtual bool get_host_res_disk_partition(string szoid, Snmp& snmp, vector<STORAGEFIXEDDISK>& vecdisk_partition, int& nFixedDiskBegin, int& nFixedDiskEnd);
	/*! ��ȡ������Դ�Ĵ��̻�����Ϣ����
	* snmp snmp����
	* phostres ������Դ
	*
	* �ɹ�����true��ʧ�ܷ���false
	*/
	bool get_host_res_disk_info(Snmp& snmp, pHOSTRES phostres);
	/*! ��ȡ������Դ�Ļ�����Ϣ
	* szoid ������Ϣoid
	* snmp snmp����
	* vecdisk_partition ���̷����б�����
	* �ɹ�����true��ʧ�ܷ���false
	*/
	virtual bool get_host_res_disk_info(string szoid, Snmp& snmp, vector<DISKSTORAGE>& vecdisk_storage);
	/*! ��ȡ�ӿ���Դ
	* szoid �ӿ����ݶ�Ӧ��oid
	* snmp snmp����
	* vecifr �ӿ���Դ����
	* �ɹ�����true��ʧ�ܷ���false
	*/
	virtual bool get_interface_res(string szoid, Snmp& snmp, vector<IFR>& vecifr);
	/*! ��ȡ�ӿ���Դ��IP����
	* szoid �ӿ�ip��ַ���ӿ�ip�����oid
	* snmp snmp����
	* vecentip �ӿ�IP����
	* �ɹ�����true��ʧ�ܷ���false
	*/
	virtual bool get_interface_res_ent_ip(string szoid, Snmp& snmp, vector< ENTIP >& vecentip);
	/*! ��ȡ�������ܵ�CPU����
	* szoid ���ض�Ӧ��oid
	* snmp snmp����
	* vecprocessorload CPU��������
	* �ɹ�����true��ʧ�ܷ���false
	*/
	virtual bool get_host_perf_processor_load(string szoid, Snmp& snmp, vector<int>& vecprocessorload);
	/*!��ȡ�������ܵ������ڴ��С�������ڴ���ʹ�ã������ڴ��С�������ڴ���ʹ�ã����̷�������
	* snmp snmp����
	* phostperf ������������
	*
	* �ɹ�����true��ʧ�ܷ���false
	*/
	bool get_host_perf_storage(Snmp& snmp, pHOSTPERF phostperf);

	/*!����hrStorageType��ȡ�������ܵ������ڴ��С�������ڴ���ʹ�ã������ڴ��С�������ڴ���ʹ�ã����̷�������
	* szoid hrStorageType��hrStorageDescr��hrStorageSize�� hrStorageUsed��Ӧ��oid
	* snmp snmp����
	* phostperf ������������
	* nRam ����hrStorageType�ĵ��������ڴ����ڵ�����
	* nVirtualMemory ����hrStorageType�õ��������ڴ����ڵ�����
	* nFixedDiskBegin ����hrStorageType�õ��Ĵ��̷�����ʼ������
	* nFixedDiskend ����hrStorageType�õ��Ĵ��̷�������������
	* �ɹ�����true��ʧ�ܷ���false
	*/
	virtual bool get_host_perf_storage(string szoid, Snmp& snmp, pHOSTPERF phostperf, int& nRam, int& nVirtualMemory, int &nMemoryBuf, int &nCachedMem, int& nFixedDiskBegin, int& nFixedDiskEnd);
	/*! ��ȡ�������ܵĽ��������б�����
	* snmp snmp����
	* vecswrun ���������б�����
	*
	* �ɹ�����true��ʧ�ܷ���false
	*/
	bool get_host_perf_swrun(Snmp& snmp, vector<SWRUN>& vecswrun);
	/*! ���ݽ������ܵĲ���oid�õ���Ӧ����
	* szoid �������ܵĲ���oid
	* snmp snmp����
	* vecswrun ���������б�����
	* �ɹ�����true��ʧ�ܷ���false
	*/
	bool get_host_perf_swrun(string szoid, Snmp& snmp, vector<SWRUN>& vecswrun);
	/*! ��ȡ�������ܵ��Ѱ�װ����б�����
	* snmp snmp����
	* vecInstalled �Ѱ�װ�������
	* �ɹ�����true��ʧ�ܷ���false
	*/
	bool get_host_perf_installed(Snmp& snmp, vector<INSTALLED>& vecInstalled);
	/*! �����Ѱ�װ�����Ӧoid��ȡ����
	* szoid �Ѱ�װ������ݵ�oid
	* snmp snmp����
	* vecInstalled �Ѱ�װ�������
	* �ɹ�����true��ʧ�ܷ���false
	*/
	bool get_host_perf_installed(string szoid, Snmp& snmp, vector<INSTALLED>& vecInstalled);

	/*! ���ڴ�����������ݸ�ʽ��Ϊ 2015-3-25 12:12:12.000����ʽ
	* szvalue �������ݣ��������
	* szdate ��ʽ����Ľ���� �������
	*
	*
	*/

	bool get_room_sensor_res(string szoid, Snmp& snmp, vector<ROOMSENSORRES>& vecRoomSensorRes);
	/*! ��ȡ������������
	* szoid �����������ݶ�Ӧ��oid
	* snmp snmp����
	* proomsensorres �������������ṹ
	* �ɹ�����true��ʧ�ܷ���false
	*/
	bool get_room_environment_para(string szoid, Snmp& snmp, vector<ROOMENVIRPARA>& vecRoomEnvirPara);
	/*! ���ڴ�����������ݸ�ʽ��Ϊ 2015-3-25 12:12:12.000����ʽ
	* szvalue �������ݣ��������
	* szdate ��ʽ����Ľ���� �������
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
