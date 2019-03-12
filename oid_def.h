// OID定义
#ifndef _OID_DEF_H_
#define _OID_DEF_H_

// **通用设备资源**
#define NUM_OF_CDR		6

#define CDR_DEVSTATUS	""	// 设备状态
#define CDR_DEVSERIAL	""	// 设备型号
#define CDR_DEVTYPE		""	// 设备类型
#define CDR_SYSDESCR	"1.3.6.1.2.1.1.1.0"	// 系统描述
#define CDR_SYSOBJECTID "1.3.6.1.2.1.1.2.0"	// sysOID
#define CDR_SYSUPTIME	"1.3.6.1.2.1.1.3.0"	// 系统启动时间
#define CDR_LASTSYNTIME	""	// 最后同步时间
#define CDR_SYSCONTACT	"1.3.6.1.2.1.1.4.0"	// 联系人
#define CDR_SYSNAME		"1.3.6.1.2.1.1.5.0"	// 系统名字
#define CDR_SYSLOCATION	"1.3.6.1.2.1.1.6.0"	// 位置
	//
	//
// **主机资源**
#define NUM_OF_HR	5

#define HR_HRSYSTEMDATE				"1.3.6.1.2.1.25.1.2.0"	    // 系统时间
#define HR_HRSYSTEMUPTIME			"1.3.6.1.2.1.25.1.1.0"	    // 系统运行时间
#define HR_HRSYSTEMNUMUSERS			"1.3.6.1.2.1.25.1.5.0"	    // 系统登录用户数
#define	HR_HRSYSTEMPROCESSES		"1.3.6.1.2.1.25.1.6.0"	    // 系统当前进程数
#define	HR_HRDEVICEPROCESSORDESCR	"1.3.6.1.2.1.25.3.2.1.3"	// CPU型号
#define	HR_HRDEVICEPROCESSORTYPE	"1.3.6.1.2.1.25.3.2.1.2"	// 设备类型
#define	HR_HRDEVICEPROCESSORINDEX	"1.3.6.1.2.1.25.3.2.1.1"	// CPU编号列表
#define HR_HRDEVICEPROCESSORLOAD    "1.3.6.1.2.1.25.3.3.1.2"    // CPU当前负载
#define HR_HRMEMORYSIZE				"1.3.6.1.2.1.25.2.2.0"	    // 总物理内存
#define HR_HRVIRTUALMMSIZE          "1.3.6.1.4.1.2021.4.3.0"    // 总虚拟内存
#define HR_HRDISKCAPACITY			"1.3.6.1.2.1.25.3.6.1.4"	// 磁盘总空间
#define HR_HRDISKPARTITION			"1.3.6.1.2.1.25.3.7"	    // 磁盘分区列表
#define HR_HRDISKPARTITIONINDEX		"1.3.6.1.2.1.25.3.7.1.1"	// 磁盘分区列表索引
#define HR_HRDISKPARTITIONNAME		"1.3.6.1.2.1.25.3.7.1.2"	// 磁盘分区列表名称
#define HR_HRDISKPARTITIONSIZE		"1.3.6.1.2.1.25.3.7.1.4"	// 磁盘分区列表大小
#define HR_HRDISKREADWRITESTATE     "1.3.6.1.2.1.25.3.6.1.1"    // 磁盘读写状态
#define HR_HRDISKMEDIATYPE          "1.3.6.1.2.1.25.3.6.1.2"    // 磁盘介质类型
#define HR_HRDISKSTORAGECAPACITY    "1.3.6.1.2.1.25.3.6.1.4"    // 磁盘存储空间
	//
	//
	//
// **接口资源**
#define IFR_IFINDEX			"1.3.6.1.2.1.2.2.1.1"	// 接口索引
#define IFR_IFDESC			"1.3.6.1.2.1.2.2.1.2"	// 接口描述
#define IFR_IFTYPE			"1.3.6.1.2.1.2.2.1.3"	// 接口类型
#define IFR_IFPHYSADDRESS	"1.3.6.1.2.1.2.2.1.6"	// MAC地址
#define IFR_IFSPEED			"1.3.6.1.2.1.2.2.1.5"	// 接口带宽
#define IFR_IFMTU			"1.3.6.1.2.1.2.2.1.4"	// MTU
#define IFR_IFADMINSTATUS	"1.3.6.1.2.1.2.2.1.7"	// 管理状态
#define IFR_IFOPERSTATUS	"1.3.6.1.2.1.2.2.1.8"	// 运行状态
#define IFR_IFLASTCHANGE	"1.3.6.1.2.1.2.2.1.9"	// 最后更新时间
#define IFR_IPADENTIFINDEX  "1.3.6.1.2.1.4.20.1.2"
#define IFR_IPADENTADDR		"1.3.6.1.2.1.4.20.1.1"	// 接口IP地址
#define IFR_IPADENTNETMASK	"1.3.6.1.2.1.4.20.1.3"	// 接口IP掩码
#define IFR_IFALIAS         "1.3.6.1.2.1.31.1.1.1.18" //接口别名
//
// **主机性能**
#define HP_HRPROCESSORLOAD				"1.3.6.1.2.1.25.3.3.1.2"	// CPU负载
#define HP_HRSTORAGERAMSIZE				"1.3.6.1.2.1.25.2.3.1.5"	// 物理内存大小
#define HP_HRSTORAGERAMUSED				"1.3.6.1.2.1.25.2.3.1.6"	// 物理内存已使用
#define HP_HRSTORAGEVIRTUALMEMORYSIZE	"1.3.6.1.2.1.25.2.3.1.5"	// 虚拟内存大小
#define HP_HRSTORAGEVIRTUALMEMORYUSED	"1.3.6.1.2.1.25.2.3.1.6"	// 虚拟内存已使用
#define HP_HRSTORAGEFIXEDDISK			"1.3.6.1.2.1.25.2.3.1"		// 磁盘分区使用
// 系统存储
#define HP_HRSTORAGETYPE				"1.3.6.1.2.1.25.2.3.1.2"	// 类型
#define HP_HRSTORAGEDESC				"1.3.6.1.2.1.25.2.3.1.3"
#define HP_HRSTORAGEUNITS               "1.3.6.1.2.1.25.2.3.1.4"    // 存储单位
#define HP_HRSTORAGESIZE				"1.3.6.1.2.1.25.2.3.1.5"	// 大小 
#define HP_HRSTORAGEUSED				"1.3.6.1.2.1.25.2.3.1.6"	// 已用
// 进程列表
#define HP_HRSWRUNINDEX					"1.3.6.1.2.1.25.4.2.1.1"	// 取进程ID(hrSWRunEntry.hrSWEunIndex)
#define HP_HRSWRUNNAME					"1.3.6.1.2.1.25.4.2.1.2"	// 进程名(hrSWRunEntry.hrSWRunName)
#define HP_HRSWRUNPATH					"1.3.6.1.2.1.25.4.2.1.4"	// 路径（hrSWRunEntry.hrSWRunPath）
#define HP_HRSWRUNPARA                  "1.3.6.1.2.1.25.4.2.1.5"   // 参数（hrSWRunEntry.hrSWRunParameters）
#define HP_HRSWRUNTYPE					"1.3.6.1.2.1.25.4.2.1.6"	// 进程类型（hrSWRunEntry.hrSWRunType）
#define HP_HRSWRUNSTATUS				"1.3.6.1.2.1.25.4.2.1.7"	// 进程状态（hrSWRunEntry.hrSWRunStatus）
#define HP_HRSWRUNPERFCPU				"1.3.6.1.2.1.25.5.1.1.1"	// 进程当前占用CPU（hrSWRunPerfEntry.hrSWRunPerfCPU）
#define HP_HRSWRUNPERFMEM				"1.3.6.1.2.1.25.5.1.1.2"	// 进程当前占用内存（hrSWRunPerfEntry.hrSWRunPerfMem）.
// 已安装软件列表
#define HP_HRINSTALLEDNAME				"1.3.6.1.2.1.25.6.3.1.2"	// 软件名字
#define HP_HRINSTALLEDTYPE				"1.3.6.1.2.1.25.6.3.1.4"	// 类型
#define HP_HRINSTALLEDDATE				"1.3.6.1.2.1.25.6.3.1.5"	// 安装时间
//
//
//
// **v1接口性能**
#define IFP_IFINDEX			"1.3.6.1.2.1.2.2.1.1"	// 接口索引
#define IFP_IFDESC			"1.3.6.1.2.1.2.2.1.2"	// 接口描述
#define IFP_IFADMINSTATUS	"1.3.6.1.2.1.2.2.1.7"	// 管理状态
#define IFP_IFOPERSTATUS	"1.3.6.1.2.1.2.2.1.8"	// 运行状态
#define IFP_IFSPEED			"1.3.6.1.2.1.2.2.1.5"	// 接口带宽
#define IFP_IFINOCTECTS		"1.3.6.1.2.1.2.2.1.10"	// 接收字节数
#define IFP_IFINERRORS		"1.3.6.1.2.1.2.2.1.14"	// 入流量错误包数
#define IFP_IFINDISCARDS	"1.3.6.1.2.1.2.2.1.13"	// 入流量包丢弃数
#define IFP_IFOUTOCTECTS	"1.3.6.1.2.1.2.2.1.16"	// 发送字节数
#define IFP_IFOUTERRORS		"1.3.6.1.2.1.2.2.1.20"	// 出流量错误包数
#define IFP_IFOUTDISCARDS	"1.3.6.1.2.1.2.2.1.19"	// 出流量包丢弃数
//
//

// **v2c接口性能**
#define IFHC_IFDESC		        "1.3.6.1.2.1.31.1.1.1.1"	// 接口描述
#define IFHC_IFSPEED			"1.3.6.1.2.1.31.1.1.1.15"	// 接口带宽
#define IFHC_IFINOCTECTS		"1.3.6.1.2.1.31.1.1.1.6"	// 接收字节数
#define IFHC_IFOUTOCTECTS	    "1.3.6.1.2.1.31.1.1.1.10"	// 发送字节数

//**机房传感器资源**
#define ROOM_SSSERIALNUM        "1.3.6.1.4.1.13742.6.3.6.3.1.3"   //传感器序列号
#define ROOM_SSNAME             "1.3.6.1.4.1.13742.6.3.6.3.1.4"   //传感器名字
#define ROOM_SSTYPE             "1.3.6.1.4.1.13742.6.3.6.3.1.2"   //传感器类型
#define ROOM_SSSUBTYPE          "1.3.6.1.4.1.13742.6.3.6.3.1.10"  //传感器子类型
#define ROOM_SSUNITS            "1.3.6.1.4.1.13742.6.3.6.3.1.16"  //数据单位
#define ROOM_SSSTATES           ""  //传感器状态
#define ROOM_SSID               ".1.3.6.1.4.1.13742.6.3.6.3.1.1"  //传感器ID
#define ROOM_SSINDEXVALUE       ""  //索引值

//**机房环境参数**
#define ROOM_ENINDEXVALUE       "1.3.6.1.4.1.13742.6.5.5.3.1"     //传感器索引值
#define ROOM_ENAVAILABLE        "1.3.6.1.4.1.13742.6.5.5.3.1.2"   //传感器可用性
#define ROOM_ENSTATES           "1.3.6.1.4.1.13742.6.5.5.3.1.3"   //传感器状态
#define ROOM_ENVALUE            "1.3.6.1.4.1.13742.6.5.5.3.1.4"   //传感器值
#define ROOM_ENTIMESTAMP        "1.3.6.1.4.1.13742.6.5.5.3.1.5"   //时间戳

//**intel sensor resources**
#define ROOM_INTEL_SSINDEXVALUE   ""  //索引值
#define ROOM_INTEL_SSUNITS        "1.3.6.1.4.1.13742.6.3.3.4.1.6"  //数据单位

//**room intel sensor parameter**
#define ROOM_INTEL_ENINDEXVALUE   ""  //索引值
#define ROOM_INTEL_ENAVAILABLE    "1.3.6.1.4.1.13742.6.5.2.3.1.2"  //intel sensor available
#define ROOM_INTEL_ENSTATES       "1.3.6.1.4.1.13742.6.5.2.3.1.3"  //intel sensor state
#define ROOM_INTEL_ENVALUE        "1.3.6.1.4.1.13742.6.5.2.3.1.4"  //intel sensor value
#define ROOM_INTEL_ENTIMESTAMP    "1.3.6.1.4.1.13742.6.5.2.3.1.5"  //intel sensor timestamp

#endif
