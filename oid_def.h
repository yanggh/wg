// OID����
#ifndef _OID_DEF_H_
#define _OID_DEF_H_

// **ͨ���豸��Դ**
#define NUM_OF_CDR		6

#define CDR_DEVSTATUS	""	// �豸״̬
#define CDR_DEVSERIAL	""	// �豸�ͺ�
#define CDR_DEVTYPE		""	// �豸����
#define CDR_SYSDESCR	"1.3.6.1.2.1.1.1.0"	// ϵͳ����
#define CDR_SYSOBJECTID "1.3.6.1.2.1.1.2.0"	// sysOID
#define CDR_SYSUPTIME	"1.3.6.1.2.1.1.3.0"	// ϵͳ����ʱ��
#define CDR_LASTSYNTIME	""	// ���ͬ��ʱ��
#define CDR_SYSCONTACT	"1.3.6.1.2.1.1.4.0"	// ��ϵ��
#define CDR_SYSNAME		"1.3.6.1.2.1.1.5.0"	// ϵͳ����
#define CDR_SYSLOCATION	"1.3.6.1.2.1.1.6.0"	// λ��
	//
	//
// **������Դ**
#define NUM_OF_HR	5

#define HR_HRSYSTEMDATE				"1.3.6.1.2.1.25.1.2.0"	    // ϵͳʱ��
#define HR_HRSYSTEMUPTIME			"1.3.6.1.2.1.25.1.1.0"	    // ϵͳ����ʱ��
#define HR_HRSYSTEMNUMUSERS			"1.3.6.1.2.1.25.1.5.0"	    // ϵͳ��¼�û���
#define	HR_HRSYSTEMPROCESSES		"1.3.6.1.2.1.25.1.6.0"	    // ϵͳ��ǰ������
#define	HR_HRDEVICEPROCESSORDESCR	"1.3.6.1.2.1.25.3.2.1.3"	// CPU�ͺ�
#define	HR_HRDEVICEPROCESSORTYPE	"1.3.6.1.2.1.25.3.2.1.2"	// �豸����
#define	HR_HRDEVICEPROCESSORINDEX	"1.3.6.1.2.1.25.3.2.1.1"	// CPU����б�
#define HR_HRDEVICEPROCESSORLOAD    "1.3.6.1.2.1.25.3.3.1.2"    // CPU��ǰ����
#define HR_HRMEMORYSIZE				"1.3.6.1.2.1.25.2.2.0"	    // �������ڴ�
#define HR_HRVIRTUALMMSIZE          "1.3.6.1.4.1.2021.4.3.0"    // �������ڴ�
#define HR_HRDISKCAPACITY			"1.3.6.1.2.1.25.3.6.1.4"	// �����ܿռ�
#define HR_HRDISKPARTITION			"1.3.6.1.2.1.25.3.7"	    // ���̷����б�
#define HR_HRDISKPARTITIONINDEX		"1.3.6.1.2.1.25.3.7.1.1"	// ���̷����б�����
#define HR_HRDISKPARTITIONNAME		"1.3.6.1.2.1.25.3.7.1.2"	// ���̷����б�����
#define HR_HRDISKPARTITIONSIZE		"1.3.6.1.2.1.25.3.7.1.4"	// ���̷����б��С
#define HR_HRDISKREADWRITESTATE     "1.3.6.1.2.1.25.3.6.1.1"    // ���̶�д״̬
#define HR_HRDISKMEDIATYPE          "1.3.6.1.2.1.25.3.6.1.2"    // ���̽�������
#define HR_HRDISKSTORAGECAPACITY    "1.3.6.1.2.1.25.3.6.1.4"    // ���̴洢�ռ�
	//
	//
	//
// **�ӿ���Դ**
#define IFR_IFINDEX			"1.3.6.1.2.1.2.2.1.1"	// �ӿ�����
#define IFR_IFDESC			"1.3.6.1.2.1.2.2.1.2"	// �ӿ�����
#define IFR_IFTYPE			"1.3.6.1.2.1.2.2.1.3"	// �ӿ�����
#define IFR_IFPHYSADDRESS	"1.3.6.1.2.1.2.2.1.6"	// MAC��ַ
#define IFR_IFSPEED			"1.3.6.1.2.1.2.2.1.5"	// �ӿڴ���
#define IFR_IFMTU			"1.3.6.1.2.1.2.2.1.4"	// MTU
#define IFR_IFADMINSTATUS	"1.3.6.1.2.1.2.2.1.7"	// ����״̬
#define IFR_IFOPERSTATUS	"1.3.6.1.2.1.2.2.1.8"	// ����״̬
#define IFR_IFLASTCHANGE	"1.3.6.1.2.1.2.2.1.9"	// ������ʱ��
#define IFR_IPADENTIFINDEX  "1.3.6.1.2.1.4.20.1.2"
#define IFR_IPADENTADDR		"1.3.6.1.2.1.4.20.1.1"	// �ӿ�IP��ַ
#define IFR_IPADENTNETMASK	"1.3.6.1.2.1.4.20.1.3"	// �ӿ�IP����
#define IFR_IFALIAS         "1.3.6.1.2.1.31.1.1.1.18" //�ӿڱ���
//
// **��������**
#define HP_HRPROCESSORLOAD				"1.3.6.1.2.1.25.3.3.1.2"	// CPU����
#define HP_HRSTORAGERAMSIZE				"1.3.6.1.2.1.25.2.3.1.5"	// �����ڴ��С
#define HP_HRSTORAGERAMUSED				"1.3.6.1.2.1.25.2.3.1.6"	// �����ڴ���ʹ��
#define HP_HRSTORAGEVIRTUALMEMORYSIZE	"1.3.6.1.2.1.25.2.3.1.5"	// �����ڴ��С
#define HP_HRSTORAGEVIRTUALMEMORYUSED	"1.3.6.1.2.1.25.2.3.1.6"	// �����ڴ���ʹ��
#define HP_HRSTORAGEFIXEDDISK			"1.3.6.1.2.1.25.2.3.1"		// ���̷���ʹ��
// ϵͳ�洢
#define HP_HRSTORAGETYPE				"1.3.6.1.2.1.25.2.3.1.2"	// ����
#define HP_HRSTORAGEDESC				"1.3.6.1.2.1.25.2.3.1.3"
#define HP_HRSTORAGEUNITS               "1.3.6.1.2.1.25.2.3.1.4"    // �洢��λ
#define HP_HRSTORAGESIZE				"1.3.6.1.2.1.25.2.3.1.5"	// ��С 
#define HP_HRSTORAGEUSED				"1.3.6.1.2.1.25.2.3.1.6"	// ����
// �����б�
#define HP_HRSWRUNINDEX					"1.3.6.1.2.1.25.4.2.1.1"	// ȡ����ID(hrSWRunEntry.hrSWEunIndex)
#define HP_HRSWRUNNAME					"1.3.6.1.2.1.25.4.2.1.2"	// ������(hrSWRunEntry.hrSWRunName)
#define HP_HRSWRUNPATH					"1.3.6.1.2.1.25.4.2.1.4"	// ·����hrSWRunEntry.hrSWRunPath��
#define HP_HRSWRUNPARA                  "1.3.6.1.2.1.25.4.2.1.5"   // ������hrSWRunEntry.hrSWRunParameters��
#define HP_HRSWRUNTYPE					"1.3.6.1.2.1.25.4.2.1.6"	// �������ͣ�hrSWRunEntry.hrSWRunType��
#define HP_HRSWRUNSTATUS				"1.3.6.1.2.1.25.4.2.1.7"	// ����״̬��hrSWRunEntry.hrSWRunStatus��
#define HP_HRSWRUNPERFCPU				"1.3.6.1.2.1.25.5.1.1.1"	// ���̵�ǰռ��CPU��hrSWRunPerfEntry.hrSWRunPerfCPU��
#define HP_HRSWRUNPERFMEM				"1.3.6.1.2.1.25.5.1.1.2"	// ���̵�ǰռ���ڴ棨hrSWRunPerfEntry.hrSWRunPerfMem��.
// �Ѱ�װ����б�
#define HP_HRINSTALLEDNAME				"1.3.6.1.2.1.25.6.3.1.2"	// �������
#define HP_HRINSTALLEDTYPE				"1.3.6.1.2.1.25.6.3.1.4"	// ����
#define HP_HRINSTALLEDDATE				"1.3.6.1.2.1.25.6.3.1.5"	// ��װʱ��
//
//
//
// **v1�ӿ�����**
#define IFP_IFINDEX			"1.3.6.1.2.1.2.2.1.1"	// �ӿ�����
#define IFP_IFDESC			"1.3.6.1.2.1.2.2.1.2"	// �ӿ�����
#define IFP_IFADMINSTATUS	"1.3.6.1.2.1.2.2.1.7"	// ����״̬
#define IFP_IFOPERSTATUS	"1.3.6.1.2.1.2.2.1.8"	// ����״̬
#define IFP_IFSPEED			"1.3.6.1.2.1.2.2.1.5"	// �ӿڴ���
#define IFP_IFINOCTECTS		"1.3.6.1.2.1.2.2.1.10"	// �����ֽ���
#define IFP_IFINERRORS		"1.3.6.1.2.1.2.2.1.14"	// �������������
#define IFP_IFINDISCARDS	"1.3.6.1.2.1.2.2.1.13"	// ��������������
#define IFP_IFOUTOCTECTS	"1.3.6.1.2.1.2.2.1.16"	// �����ֽ���
#define IFP_IFOUTERRORS		"1.3.6.1.2.1.2.2.1.20"	// �������������
#define IFP_IFOUTDISCARDS	"1.3.6.1.2.1.2.2.1.19"	// ��������������
//
//

// **v2c�ӿ�����**
#define IFHC_IFDESC		        "1.3.6.1.2.1.31.1.1.1.1"	// �ӿ�����
#define IFHC_IFSPEED			"1.3.6.1.2.1.31.1.1.1.15"	// �ӿڴ���
#define IFHC_IFINOCTECTS		"1.3.6.1.2.1.31.1.1.1.6"	// �����ֽ���
#define IFHC_IFOUTOCTECTS	    "1.3.6.1.2.1.31.1.1.1.10"	// �����ֽ���

//**������������Դ**
#define ROOM_SSSERIALNUM        "1.3.6.1.4.1.13742.6.3.6.3.1.3"   //���������к�
#define ROOM_SSNAME             "1.3.6.1.4.1.13742.6.3.6.3.1.4"   //����������
#define ROOM_SSTYPE             "1.3.6.1.4.1.13742.6.3.6.3.1.2"   //����������
#define ROOM_SSSUBTYPE          "1.3.6.1.4.1.13742.6.3.6.3.1.10"  //������������
#define ROOM_SSUNITS            "1.3.6.1.4.1.13742.6.3.6.3.1.16"  //���ݵ�λ
#define ROOM_SSSTATES           ""  //������״̬
#define ROOM_SSID               ".1.3.6.1.4.1.13742.6.3.6.3.1.1"  //������ID
#define ROOM_SSINDEXVALUE       ""  //����ֵ

//**������������**
#define ROOM_ENINDEXVALUE       "1.3.6.1.4.1.13742.6.5.5.3.1"     //����������ֵ
#define ROOM_ENAVAILABLE        "1.3.6.1.4.1.13742.6.5.5.3.1.2"   //������������
#define ROOM_ENSTATES           "1.3.6.1.4.1.13742.6.5.5.3.1.3"   //������״̬
#define ROOM_ENVALUE            "1.3.6.1.4.1.13742.6.5.5.3.1.4"   //������ֵ
#define ROOM_ENTIMESTAMP        "1.3.6.1.4.1.13742.6.5.5.3.1.5"   //ʱ���

//**intel sensor resources**
#define ROOM_INTEL_SSINDEXVALUE   ""  //����ֵ
#define ROOM_INTEL_SSUNITS        "1.3.6.1.4.1.13742.6.3.3.4.1.6"  //���ݵ�λ

//**room intel sensor parameter**
#define ROOM_INTEL_ENINDEXVALUE   ""  //����ֵ
#define ROOM_INTEL_ENAVAILABLE    "1.3.6.1.4.1.13742.6.5.2.3.1.2"  //intel sensor available
#define ROOM_INTEL_ENSTATES       "1.3.6.1.4.1.13742.6.5.2.3.1.3"  //intel sensor state
#define ROOM_INTEL_ENVALUE        "1.3.6.1.4.1.13742.6.5.2.3.1.4"  //intel sensor value
#define ROOM_INTEL_ENTIMESTAMP    "1.3.6.1.4.1.13742.6.5.2.3.1.5"  //intel sensor timestamp

#endif
