#ifndef _DATA_STRUCT_DEF_H_
#define _DATA_STRUCT_DEF_H_

#define MAX_LENGTH 256

#include <string>
#include <vector>
using namespace std;

typedef struct inproc
{
	string inproc_name;
	int inproc_id;
} INPROC;

// **通用设备资源**
typedef struct tagCOMDEVRES
{
	bool bdev_status;
	string strdev_serial;
	string strdev_type;
	string strsys_descr;
	string strsys_object_id;
	string strsys_up_time;
	int  nlast_syn_time{0};
	string strsys_contact;
	string strsys_name;
	string strsys_location;

//	tagCOMDEVRES()
//		:nlast_syn_time(0){}

} COMDEVRES, *pCOMDEVRES;


// **主机资源**
// 磁盘分区列表
typedef struct tagSTORAGEFIXEDDISK
{
	string strstorage_descr;
	int nstorage_index{0};
	int nstorage_units{0};
	long long nstorage_size{0};
	long long nstorage_used{0};

//	tagSTORAGEFIXEDDISK() :nstorage_size(0)
//		, nstorage_index(0)
//		, nstorage_units(0)
//		, nstorage_used(0){}

} STORAGEFIXEDDISK, *pSTORAGEFIXEDDISK;

// 磁盘存储信息
typedef struct tagDISKSTORAGE
{
	int disk_access{0};
	int media_type{2};
	int disk_size{0};

//	tagDISKSTORAGE()
//		:disk_access(0)
//		, media_type(2)
//		, disk_size(0){}
} DISKSTORAGE, *pDISKSTORAGE;

typedef struct tagHOSTRES
{
	string strsys_date;
	string strsys_up_time;
	int nsys_num_user{0};
	int nsys_processers{0};
	vector<string> vecdev_processor_descr;
	vector<int> vecdev_processor_num;
	vector<int> vecdev_processor_load;
	int nmemory_size{0};
	int virtual_mm_size;
	int ndisk_capacity{0};
	vector<STORAGEFIXEDDISK> vecdisk_partition;
	vector<DISKSTORAGE> vecdisk_storage;

//	tagHOSTRES()
//		:nsys_num_user(0)
//		,nsys_processers(0)
//		,nmemory_size(0)
//		,ndisk_capacity(0)
//	{}

} HOSTRES, *pHOSTRES;

// **接口资源**
typedef struct tagIFR
{
	int nindex{0};
	string strdescr;
	int ntype{0};
	string strphys_address;
	int nspeed{0};
	int nmtu{0};
	int nadmin_status{0};
	int noper_status{0};
	string strlast_change;
	string stralias;

//	tagIFR():nindex(0)
//		,ntype(0)
//		,nspeed(0)
//		,nmtu(0)
//		,nadmin_status(0)
//		,noper_status(0)
//	{}
} IFR, *pIFR;

typedef struct tagENTIP
{
	int nindex;
	string strent_addr;
	string strent_net_mask;
} ENTIP, *pENTIP;

typedef struct tagIFRES
{
	vector< IFR > vecifr;
	vector< ENTIP > vecentip;
} IFRES, *pIFRES;

// **主机性能**

//  进程性能列表
typedef struct tagSWRUN
{
	int nindex{0};
	string strname;
	string strpath;
	string strpara;
	int ntype{0};
	int nstatus{0};
	int nperfcpu{0};
	int nperfmem{0};

//	tagSWRUN():nindex(0)
//		,ntype(0)
//		,nstatus(0)
//		,nperfcpu(0)
//		,nperfmem(0){}
//
} SWRUN, *pSWRUN;

// **已安装软件列表**
typedef struct tagINSTALLED
{
	string strname;
	int ntype{0};
	string strdate;

//	tagINSTALLED():ntype(0){}

} INSTALLED, *pINSTALLED;

typedef struct tagHOSTPERF
{
	vector<int> vecprocessor_load;
	long long nstorage_ram_size{0};
	long long nstorage_ram_used{0};
	long long nstorage_virtual_memory_size{0};
	long long nstorage_virtual_memory_used{0};
	long long nstorage_memory_buffers_size;
	long long nstorage_memory_buffers_used;
	long long nstorage_cached_memory_size{0};
	long long nstorage_cached_memory_used{0};

	long long nstorage_ram_units{0};
	long long nstorage_virtual_memory_units{0};
	long long nstorage_memory_buffers_units{0};
	long long nstorage_cached_memory_units{0};
	vector<STORAGEFIXEDDISK> vecstorage_fixed_disk;
	vector<int> vecstorage_disk_units;
	vector<SWRUN> vecswrun;
	vector<INSTALLED> vecinstalled;

//	tagHOSTPERF():nstorage_ram_size(0)
//		,nstorage_ram_used(0)
//		,nstorage_virtual_memory_size(0)
//		, nstorage_virtual_memory_used(0)
//		, nstorage_ram_units(0)
//		, nstorage_virtual_memory_units(0){}
} HOSTPERF, *pHOSTPERF;


// **接口性能**
typedef struct tagIFPERF
{
	uint32_t nindex{0};
	string strdescr;
	int nadmin_status{0};
	int noper_status{0};
	int nspeed{0};
	int nin_octects{0};
	int nin_errors{0};
	int nin_discards{0};
	int nout_octects{0};
	int nout_errors{0};
	int nout_discards{0};

//	tagIFPERF(): nindex(0)
//		,nadmin_status(0)
//		,noper_status(0)
//		,nspeed(0)
//		,nin_octects(0)
//		,nin_errors(0)
//		,nin_discards(0)
//		,nout_octects(0)
//		,nout_errors(0)
//		,nout_discards(0){}

} IFPERF, *pIFPERF;

typedef struct tagROOMSENSORRES
{
	string nsensor_serial_num;
	string strsensor_name;
	int nsensor_type{0};
	int nsensor_sub_type{0};
	int nsensor_units{0};
	int nsensor_status{0};
	int nsensor_id{0};
	string strsensor_index_value;

//	tagROOMSENSORRES() :nsensor_type(0)
//		, nsensor_sub_type(0)
//		, nsensor_units(0)
//		, nsensor_status(0)
//		, nsensor_id(0){}

} ROOMSENSORRES, *pROOMSENSORRES;

typedef struct tagROOMENVIRPARA
{
	string strsensor_index_value;
	int nsensor_available{0};
	int nsensor_status{0};
	int nsensor_value{0};
	int nsensor_time_stamp{0};

//	tagROOMENVIRPARA() :nsensor_available(0)
//		, nsensor_status(0)
//		, nsensor_value(0)
//		, nsensor_time_stamp(0){}

} ROOMENVIRPARA, *pROOMENVIRPARA;

typedef struct tagROOMINLETSENSORRES
{
	//int nintel_sensor_id;
	string strinlet_sensor_index_value;
	int nimlet_sensor_units{0};

//	tagROOMINLETSENSORRES() :nimlet_sensor_units(0)
//		//		, nintel_sensor_id(0)
//	{}

} ROOMINLETSENSORRES, *pROOMINLETSENSORRES;

#endif
