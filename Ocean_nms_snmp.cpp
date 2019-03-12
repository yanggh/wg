#include "Ocean_nms_snmp.h"

using namespace mpfmessage;
COceanNmsSnmp::COceanNmsSnmp(void)
{

	Snmp::socket_startup();  // Initialize socket subsystem
	m_ipAddr = (char*)"127.0.0.1:161";
	m_target->set_address(m_ipAddr);
}

COceanNmsSnmp::COceanNmsSnmp(char* szIpAddr)
{
	Snmp::socket_startup();
	m_ipAddr = szIpAddr;
	m_target->set_address(m_ipAddr);
}

COceanNmsSnmp::COceanNmsSnmp(SnmpInfo *pSnmpInfo, char* szIpAddr, const char* szReadCommunity, const char* szWriteCommunity, int nSnmpVersion, int &status_flag, char* szPort /*= "161"*/)
{
	Snmp::socket_startup();
	// 将IP和端口组合为IP：Port格式
	char IpAddr[100] = { 0 };
	strcpy(IpAddr, szIpAddr);
	strcat(IpAddr, ":");
	strcat(IpAddr, szPort);
	m_ipAddr = IpAddr;

	CTarget *pCtarget = new CTarget();
	if(pCtarget == NULL)
	{
		cout << "Error new CTarget: " << endl;
		status_flag = -1;
		return;
	}
	pCtarget->set_address(m_ipAddr);
	pCtarget->set_readcommunity(szReadCommunity);
	pCtarget->set_writecommunity(szWriteCommunity);
	pCtarget->set_timeout(pSnmpInfo->timeout());
	pCtarget->set_retry(pSnmpInfo->retry());
	pCtarget->set_version((snmp_version)nSnmpVersion);
	m_target = pCtarget;

	//m_target.set_address(m_ipAddr);
	//m_target.set_readcommunity( szReadCommunity );
	//m_target.set_writecommunity( szWriteCommunity );
	//m_target.set_version( (snmp_version)nSnmpVersion );
}

COceanNmsSnmp::COceanNmsSnmp(SnmpInfo *pSnmpInfo, SnmpBasePara *pSnmpBasePara, SnmpExtPara *pSnmpExtPara, int nSnmpVersion, int &status_flag)
{
#if 1
	//Snmp::socket_startup();
	// 将IP和端口组合为IP：Port格式
	char IpAddr[100] = { 0 };
	strcpy(IpAddr, pSnmpBasePara->ip_addr().c_str());
	strcat(IpAddr, ":");
	char strPort[10] = { 0 };
	sprintf(strPort, "%d", pSnmpBasePara->port());
	strcat(IpAddr, (const char *)strPort);
	m_ipAddr = IpAddr;

	//---------[ init SnmpV3 ]--------------------------------------------
	//v3MP *v3_MP;

	OctetStr community((const char *)(pSnmpBasePara->read_community().c_str()));    // community name
	OctetStr privPassword((const char *)(pSnmpExtPara->encrypt_password().c_str()));
	OctetStr authPassword((const char *)(pSnmpExtPara->auth_password().c_str()));
	OctetStr securityName((const char *)(pSnmpExtPara->user().c_str()));
	OctetStr contextEngineID((const char *)(pSnmpExtPara->engine_id().c_str()));
	cout << "securityName= " << securityName.get_printable();


	int securityModel = SNMP_SECURITY_MODEL_USM;
	int securityLevel = 0;
	long authProtocol = SNMP_AUTHPROTOCOL_NONE;
	long privProtocol = SNMP_PRIVPROTOCOL_NONE;

	if ((pSnmpExtPara->auth_method() == NONE_AUTH) && (pSnmpExtPara->encryptmethod() == NONE_ENCRYPT))
	{
		securityLevel = SNMP_SECURITY_LEVEL_NOAUTH_NOPRIV;
	}
	else if ((pSnmpExtPara->auth_method() != NONE_AUTH) && (pSnmpExtPara->encryptmethod() == NONE_ENCRYPT))
	{
		securityLevel = SNMP_SECURITY_LEVEL_AUTH_NOPRIV;
	}
	else if ((pSnmpExtPara->auth_method() != NONE_AUTH) && (pSnmpExtPara->encryptmethod() != NONE_ENCRYPT))
	{
		securityLevel = SNMP_SECURITY_LEVEL_AUTH_PRIV;
	}
	else
	{
		printf("ScProtocolGetHandler::snmp_collect securityLevel is error...!");
		status_flag = -1;
		return;
	}

	if (pSnmpExtPara->auth_method() == MD5)
		authProtocol = SNMP_AUTHPROTOCOL_HMACMD5;
	else if (pSnmpExtPara->auth_method() == SHA)
		authProtocol = SNMP_AUTHPROTOCOL_HMACSHA;

	if (pSnmpExtPara->encryptmethod() == AES)
		privProtocol = SNMP_PRIVPROTOCOL_AES128;
	else if (pSnmpExtPara->encryptmethod() == DES)
		privProtocol = SNMP_PRIVPROTOCOL_DES;

	//const char *engineId = "snmpNext";
	const char *filename = "snmpv3_boot_counter";
	unsigned int snmpEngineBoots = 0;
	int status;
	
	status = getBootCounter(filename, pSnmpExtPara->engine_id().c_str(), snmpEngineBoots);
	if ((status != SNMPv3_OK) && (status < SNMPv3_FILEOPEN_ERROR))
	{
		cout << "Error loading snmpEngineBoots counter: " << status << endl;
		status_flag = -1;
		return;
	}

	snmpEngineBoots++;
	status = saveBootCounter(filename, pSnmpExtPara->engine_id().c_str(), snmpEngineBoots);
	if (status != SNMPv3_OK)
	{
		cout << "Error saving snmpEngineBoots counter: " << status << endl;
		status_flag = -1;
		return;
	}

	//snmpEngineBoots++;
	int construct_status;
	//v3_MP = new v3MP(engineId, snmpEngineBoots, construct_status);
	m_v3_MP = new v3MP(pSnmpExtPara->engine_id().c_str(), snmpEngineBoots, construct_status);
	if (construct_status != SNMPv3_MP_OK)
	{
		printf("Error initializing v3MP: %d\n", construct_status);
		status_flag = -1;
		return;
	}

	USM *usm = m_v3_MP->get_usm();
	usm->add_usm_user(securityName,
		authProtocol, privProtocol,
		authPassword, privPassword);

	//--------[ build up SNMP++ object needed ]-------------------------------

	UTarget *pUtarget = new UTarget();
	pUtarget->set_address(m_ipAddr);
	pUtarget->set_version((snmp_version)nSnmpVersion);   // set the SNMP version SNMPV1 or V2 or V3
	pUtarget->set_retry(pSnmpInfo->retry());                              // set the number of auto retries
	pUtarget->set_timeout(pSnmpInfo->timeout());                          // set timeout
	pUtarget->set_security_model(securityModel);
	pUtarget->set_security_name(securityName);
	m_pdu.set_security_level(securityLevel);
	//pdu.set_context_name (contextName);
	m_pdu.set_context_engine_id(contextEngineID);
	m_target = pUtarget;

	//CTarget *pCtarget = new CTarget();
	//pCtarget->set_address(m_ipAddr);
	//pCtarget->set_version((snmp_version)nSnmpVersion);
	//pCtarget->set_retry(pSnmpInfo->retry());
	//pCtarget->set_timeout(pSnmpInfo->timeout());                          // set timeout
	////pCtarget->set_security_model(securityModel);
	////pCtarget->set_security_name(securityName);
	//m_pdu.set_security_level(securityLevel);
	////pdu.set_context_name (contextName);
	//m_pdu.set_context_engine_id(contextEngineID);
	//m_target = pCtarget;
#endif
}


COceanNmsSnmp::~COceanNmsSnmp(void)
{
	//Snmp::socket_cleanup();  // Shut down socket subsystem
	if (m_v3_MP != NULL)
		delete m_v3_MP;
	m_pdu.clear();
	if (m_target != NULL)
		delete m_target;
}

bool COceanNmsSnmp::get_common_dev_res(pCOMDEVRES pcomdevres)
{
	if (!m_ipAddr.valid() || !m_target->valid())
	{
		cout << "Invalid IP or Invalid target" << endl;
		return false;
	}
	int status;
	// 	Snmp snmp(status, 0, (m_ipAddr.get_ip_version() == Address::version_ipv6));
	Snmp snmp(status, 0);
	if (status != SNMP_CLASS_SUCCESS)
	{
		printf("COceanNmsSnmp::get_common_dev_res()： snmp status failed！");
		return false;
	}

	Pdu pdu;
	pdu.set_security_level(m_pdu.get_security_level());
	pdu.set_context_engine_id(m_pdu.get_context_engine_id());
	Vb vb[NUM_OF_CDR];
	vb[0].set_oid(CDR_SYSDESCR);
	vb[1].set_oid(CDR_SYSOBJECTID);
	vb[2].set_oid(CDR_SYSUPTIME);
	vb[3].set_oid(CDR_SYSCONTACT);
	vb[4].set_oid(CDR_SYSNAME);
	vb[5].set_oid(CDR_SYSLOCATION);

	pdu.set_vblist(vb, NUM_OF_CDR);

	status = snmp.get(pdu, *m_target);
	if (status != SNMP_CLASS_SUCCESS)
	{
		printf("COceanNmsSnmp::get_common_dev_res()： snmp get failed！ error msg[%s]", snmp.error_msg(status));
		return false;
	}

	int vbcount = pdu.get_vb_count();
	if (vbcount == NUM_OF_CDR)
	{
		pdu.get_vblist(vb, vbcount);
		for (int i = 0; i<vbcount; i++)
		{
			Oid oid;
			oid = vb[i].get_oid();
			if (oid == Oid(CDR_SYSDESCR))
			{
				char cvalue[256] = { 0 };
				vb[i].get_value(cvalue);
				pcomdevres->strsys_descr = cvalue;
				// 				pcomdevres->strsys_descr = string( vb[i].get_printable_value());
			}
			if (oid == Oid(CDR_SYSOBJECTID))
				pcomdevres->strsys_object_id = string(vb[i].get_printable_value());
			if (oid == Oid(CDR_SYSUPTIME))
				pcomdevres->strsys_up_time = string(vb[i].get_printable_value());
			if (oid == Oid(CDR_SYSCONTACT))
				pcomdevres->strsys_contact = string(vb[i].get_printable_value());
			if (oid == Oid(CDR_SYSNAME))
				pcomdevres->strsys_name = string(vb[i].get_printable_value());
			if (oid == Oid(CDR_SYSLOCATION))
				pcomdevres->strsys_location = string(vb[i].get_printable_value());
		}
	}
	else
		return false;
	pdu.clear();
	return true;
}

bool COceanNmsSnmp::get_host_res(pHOSTRES phostres)
{
	if (!m_ipAddr.valid() || !m_target->valid())
	{
		cout << "Invalid IP or Invalid target" << endl;
		return false;
	}
	int status;
	// 	Snmp snmp(status, 0, (m_ipAddr.get_ip_version() == Address::version_ipv6));
	Snmp snmp(status, 0);
	if (status != SNMP_CLASS_SUCCESS)
	{
		printf("COceanNmsSnmp::get_host_res()： snmp status failed！ error msg[%s]", snmp.error_msg(status));
		return false;
	}
	HOSTPERF hostperf;
	get_host_res_dev_processor(snmp, phostres);
	get_host_res_disk_capacity(snmp, phostres);
	get_host_res_disk_partition(snmp, phostres);
	get_host_res_disk_info(snmp, phostres);
	get_host_perf_storage(snmp, &hostperf);
	phostres->virtual_mm_size = hostperf.nstorage_virtual_memory_size / 1024;

	Pdu pdu;
	Vb vb[NUM_OF_HR];
	vb[0].set_oid(HR_HRSYSTEMDATE);
	vb[1].set_oid(HR_HRSYSTEMUPTIME);
	vb[2].set_oid(HR_HRSYSTEMNUMUSERS);
	vb[3].set_oid(HR_HRSYSTEMPROCESSES);
	vb[4].set_oid(HR_HRMEMORYSIZE);
	//vb[5].set_oid(HR_HRVIRTUALMMSIZE);

	pdu.set_vblist(vb, NUM_OF_HR);

	pdu.set_security_level(m_pdu.get_security_level());
	pdu.set_context_engine_id(m_pdu.get_context_engine_id());

	status = snmp.get(pdu, *m_target);
	if (status != SNMP_CLASS_SUCCESS)
	{
		printf("COceanNmsSnmp::get_host_res()： snmp get failed！ error msg[%s]", snmp.error_msg(status));
		return false;
	}

	int vbcount = pdu.get_vb_count();
	if (vbcount == NUM_OF_HR)
	{
		pdu.get_vblist(vb, vbcount);
		for (int i = 0; i<vbcount; i++)
		{
			Oid oid;
			oid = vb[i].get_oid();
			int n = oid.len();
			if (oid == Oid(HR_HRSYSTEMDATE))
			{
				OctetStr val;
				vb[i].get_value(val);
				char date[128] = { 0 };
				format_date((char*)val.data(), date);
				phostres->strsys_date = date;
			}
			if (oid == Oid(HR_HRSYSTEMUPTIME))
			{
				SmiUINT32 smi = vb[i].get_syntax();
				phostres->strsys_up_time = string(vb[i].get_printable_value());
			}
			if (oid == Oid(HR_HRSYSTEMNUMUSERS))
				phostres->nsys_num_user = atoi(vb[i].get_printable_value());
			if (oid == Oid(HR_HRSYSTEMPROCESSES))
				phostres->nsys_processers = atoi(vb[i].get_printable_value());
			if (oid == Oid(HR_HRMEMORYSIZE))
				phostres->nmemory_size = atoi(vb[i].get_printable_value());
			//if (oid == Oid(HR_HRVIRTUALMMSIZE))
			//	phostres->virtual_mm_size = atoi(vb[i].get_printable_value());
		}
	}
	else
		return false;
	pdu.clear();
	return true;
}
bool COceanNmsSnmp::get_host_res_disk_capacity(Snmp& snmp, pHOSTRES phostres)
{
	Oid oid(HR_HRDISKCAPACITY);
	int status = 0;
	Vb vb;
	vb.set_oid(oid);
	bool btag = true;
	for (; btag;)
	{
		Pdu pdu;
		pdu.set_security_level(m_pdu.get_security_level());
		pdu.set_context_engine_id(m_pdu.get_context_engine_id());
		pdu += vb;
		status = snmp.get_next(pdu, *m_target);
		if (status != SNMP_CLASS_SUCCESS)
		{
			printf("COceanNmsSnmp::get_host_res_disk_capacity(): snmp get_next failed!");
			return false;
		}
		pdu.get_vb(vb, 0);
		Oid oid_item;
		vb.get_oid(oid_item);
		if (oid_item.nCompare(oid_item.len(), oid) == 0)
		{
			printf("COceanNmsSnmp::get_host_res_disk_capacity(): snmp end of mib view!");
			pdu.clear();
			return false;
		}
		if (oid.nCompare(oid.len(), oid_item) == 0)// Table View 操作时，判断下一个oid与当前oid是否相等，如果不等，结束循环。
		{
			oid_item.trim();
			if (oid_item == Oid(HR_HRDISKCAPACITY))
			{
				// 求磁盘容量总和
				phostres->ndisk_capacity += atoi(vb.get_printable_value());
			}
		}
		else
			btag = false;
		pdu.clear();
	}
	return true;
}
/*
bool COceanNmsSnmp::get_host_res_disk_partition(Snmp& snmp, pHOSTRES phostres)
{
	// 
	get_host_res_disk_partition(HR_HRDISKPARTITIONINDEX, snmp, phostres->vecdisk_partition);// 确保为第一个获取的数据
	get_host_res_disk_partition(HR_HRDISKPARTITIONNAME, snmp, phostres->vecdisk_partition);
	get_host_res_disk_partition(HR_HRDISKPARTITIONSIZE, snmp, phostres->vecdisk_partition);
	return true;
}

bool COceanNmsSnmp::get_host_res_disk_partition(char* szoid, Snmp& snmp, vector<DISKPARTITION>& vecdisk_partition)
{
	Oid oid(szoid);
	int status = 0;
	Vb vb;
	vb.set_oid(oid);
	bool btag = true;
	for (int i = 1; btag; ++i)
	{
		//Pdu pdu;
		m_pdu += vb;
		status = snmp.get_next(m_pdu, *m_target);
		if (status != SNMP_CLASS_SUCCESS)
		{
			printf("COceanNmsSnmp::get_host_res_disk_partition()： snmp get_next failed！");
			printf("COceanNmsSnmp::get_host_res_disk_partition()： snmp get_next failed！");
			return false;
		}

		m_pdu.get_vb(vb, 0);
		Oid oid_item;
		vb.get_oid(oid_item);
		if (oid.nCompare(oid.len(), oid_item) == 0)// Table View 操作时，判断下一个oid与当前oid是否相等，如果不等，结束循环。
		{
			oid_item.trim(2);
			DISKPARTITION disk_partition;
			if (oid_item == Oid(HR_HRDISKPARTITIONINDEX)) // 确保为第一个获取的数据
				disk_partition.nindex = atoi(vb.get_printable_value());
			if (oid_item == Oid(HR_HRDISKPARTITIONNAME))
				vecdisk_partition[i - 1].strname = string(vb.get_printable_value());
			if (oid_item == Oid(HR_HRDISKPARTITIONSIZE))
				vecdisk_partition[i - 1].nsize = atoi(vb.get_printable_value());
			if (vecdisk_partition.size() < i) // 确保不能越界
				vecdisk_partition.push_back(disk_partition);
		}
		else
			btag = false;
		m_pdu.clear();
	}
	return true;
}
*/

bool COceanNmsSnmp::get_host_res_disk_partition(Snmp& snmp, pHOSTRES phostres)
{
	// 
	int nFixedDiskBegin = 0;
	int nFixedDiskEnd = 0;

	get_host_res_disk_partition(HP_HRSTORAGETYPE, snmp, phostres->vecdisk_partition, nFixedDiskBegin, nFixedDiskEnd);// 确保为第一个获取的数据
	get_host_res_disk_partition(HP_HRSTORAGEDESC, snmp, phostres->vecdisk_partition, nFixedDiskBegin, nFixedDiskEnd);
	get_host_res_disk_partition(HP_HRSTORAGEUNITS, snmp, phostres->vecdisk_partition, nFixedDiskBegin, nFixedDiskEnd);
	get_host_res_disk_partition(HP_HRSTORAGESIZE, snmp, phostres->vecdisk_partition, nFixedDiskBegin, nFixedDiskEnd);
	get_host_res_disk_partition(HP_HRSTORAGEUSED, snmp, phostres->vecdisk_partition, nFixedDiskBegin, nFixedDiskEnd);
	return true;
}

bool COceanNmsSnmp::get_host_res_disk_partition(string szoid, Snmp& snmp, vector<STORAGEFIXEDDISK>& vecdisk_partition, int& nFixedDiskBegin, int& nFixedDiskEnd)
{
	Oid oid(szoid.c_str());
	int status = 0;
	Vb vb;
	vb.set_oid(oid);
	bool btag = true;
	bool bbegin = true;
	for (int i = 1; btag; ++i)
	{
		Pdu pdu;
		pdu.set_security_level(m_pdu.get_security_level());
		pdu.set_context_engine_id(m_pdu.get_context_engine_id());
		pdu += vb;
		status = snmp.get_next(pdu, *m_target);
		if (status != SNMP_CLASS_SUCCESS)
		{
			printf("COceanNmsSnmp::get_host_res_disk_partition(): snmp get_next failed!");
			return false;
		}

		pdu.get_vb(vb, 0);
		Oid oid_item;
		vb.get_oid(oid_item);
		if (oid_item.nCompare(oid_item.len(), oid) == 0)
		{
			printf("COceanNmsSnmp::get_host_res_disk_partition(): snmp end of mib view!");
			pdu.clear();
			return false;
		}
		if (oid.nCompare(oid.len(), oid_item) == 0)// Table View 操作时，判断下一个oid与当前oid是否相等，如果不等，结束循环。
		{
			oid_item.trim();
			if (oid_item == Oid(HP_HRSTORAGETYPE))// 确保为第一个获取的数据
			{
				if (0 == strcmp(vb.get_printable_value(), "1.3.6.1.2.1.25.2.1.4")) // fixeddisk
				{
					if (bbegin)
					{
						nFixedDiskBegin = i;
						bbegin = false;
					}
					nFixedDiskEnd = i;
					STORAGEFIXEDDISK storagefixdisk;
					storagefixdisk.nstorage_index = i;
					vecdisk_partition.push_back(storagefixdisk);
				}
			}
			if (oid_item == Oid(HP_HRSTORAGESIZE))
			{
				for (int j = 0; j < vecdisk_partition.size(); j++)
				{
					if (i == vecdisk_partition[j].nstorage_index)
					{
						vecdisk_partition[j].nstorage_size = (long long)atoi(vb.get_printable_value())*(long long)vecdisk_partition[j].nstorage_units;
						break;
					}
				}
			}
			if (oid_item == Oid(HP_HRSTORAGEUSED))
			{
				for (int j = 0; j < vecdisk_partition.size(); j++)
				{
					if (i == vecdisk_partition[j].nstorage_index)
					{
						vecdisk_partition[j].nstorage_used = (long long)atoi(vb.get_printable_value()) * vecdisk_partition[j].nstorage_units;
						break;
					}
				}
			}
			if (oid_item == Oid(HP_HRSTORAGEDESC))
			{
				for (int j = 0; j < vecdisk_partition.size(); j++)
				{
					if (i == vecdisk_partition[j].nstorage_index)
					{
						vecdisk_partition[j].strstorage_descr = string(vb.get_printable_value());
						break;
					}
				}
				//if ( i >= nFixedDiskBegin && i <= nFixedDiskEnd )
				//{
				//	phostperf->vecstorage_fixed_disk[i-1].strstorage_descr = string//( vb.get_printable_value() );
				//}
			}
			if (oid_item == Oid(HP_HRSTORAGEUNITS))
			{
				for (int j = 0; j < vecdisk_partition.size(); j++)
				{
					if (i == vecdisk_partition[j].nstorage_index)
					{
						vecdisk_partition[j].nstorage_units = atoi(vb.get_printable_value());
						break;
					}
				}
			}
		}
		else
			btag = false;
		pdu.clear();
	}
	return true;
}

bool COceanNmsSnmp::get_host_res_disk_info(Snmp& snmp, pHOSTRES phostres)
{
	// 
	get_host_res_disk_info(HR_HRDISKREADWRITESTATE, snmp, phostres->vecdisk_storage);
	get_host_res_disk_info(HR_HRDISKMEDIATYPE, snmp, phostres->vecdisk_storage);
	get_host_res_disk_info(HR_HRDISKSTORAGECAPACITY, snmp, phostres->vecdisk_storage);
	return true;
}

bool COceanNmsSnmp::get_host_res_disk_info(string szoid, Snmp& snmp, vector<DISKSTORAGE>& vecdisk_storage)
{
	Oid oid(szoid.c_str());
	int status = 0;
	Vb vb;
	vb.set_oid(oid);
	bool btag = true;
	int temp = 0;
	for (int i = 0, j = 0; btag; i++)
	{
		Pdu pdu;
		pdu.set_security_level(m_pdu.get_security_level());
		pdu.set_context_engine_id(m_pdu.get_context_engine_id());
		pdu += vb;
		status = snmp.get_next(pdu, *m_target);
		if (status != SNMP_CLASS_SUCCESS)
		{
			printf("COceanNmsSnmp::get_host_res_disk_info(): snmp get_next failed!");
			return false;
		}

		pdu.get_vb(vb, 0);
		Oid oid_item;
		vb.get_oid(oid_item);
		
		if (oid_item.nCompare(oid_item.len(), oid) == 0)
		{
			printf("COceanNmsSnmp::get_host_res_disk_info(): snmp end of mib view!");
			pdu.clear();
			return false;
		}
		if (oid.nCompare(oid.len(), oid_item) == 0)// Table View 操作时，判断下一个oid与当前oid是否相等，如果不等，结束循环。
		{
			//oid_item.trim(2);
			//DISKSTORAGE disk_storage;
			vb.set_oid(oid_item);
			//if (oid_item == Oid(HR_HRDISKREADWRITESTATE))
//			if (!strcmp(szoid, HR_HRDISKREADWRITESTATE))
			if (szoid == HR_HRDISKREADWRITESTATE)
			{
				vecdisk_storage.resize(++j);
				//vecdisk_storage[i].disk_access= atoi(vb.get_printable_value());
				temp = atoi(vb.get_printable_value());
				vecdisk_storage[i].disk_access = temp;
			}
//			if (!strcmp(szoid, HR_HRDISKMEDIATYPE))
			if (szoid == HR_HRDISKMEDIATYPE)
			{
				vecdisk_storage[i].media_type = atoi(vb.get_printable_value());
			}
//			if (!strcmp(szoid, HR_HRDISKSTORAGECAPACITY))
			if (szoid == HR_HRDISKSTORAGECAPACITY)
			{
				vecdisk_storage[i].disk_size = atoi(vb.get_printable_value());
			}
		}
		else
			btag = false;
		pdu.clear();
	}
	return true;
}

bool COceanNmsSnmp::get_host_res_dev_processor(Snmp& snmp, pHOSTRES phostres)
{
	int nbegin = 0;
	int nend = 0;
	get_host_res_dev_processor(HR_HRDEVICEPROCESSORTYPE, snmp, phostres, nbegin, nend);// 确保为第一个获取的数据
	get_host_res_dev_processor(HR_HRDEVICEPROCESSORDESCR, snmp, phostres, nbegin, nend);
	get_host_res_dev_processor(HR_HRDEVICEPROCESSORINDEX, snmp, phostres, nbegin, nend);
	get_host_res_dev_processor(HR_HRDEVICEPROCESSORLOAD, snmp, phostres, nbegin, nend);
	return true;
}

bool COceanNmsSnmp::get_host_res_dev_processor(string szoid, Snmp& snmp, pHOSTRES phostres, int& nbegin, int& nend)
{
	Oid oid(szoid.c_str());
	int status = 0;
	Vb vb;
	vb.set_oid(oid);
	bool btag = true;
	bool bbegin = false;
	for (int i = 0; btag; ++i)
	{
		Pdu pdu;
		pdu.set_security_level(m_pdu.get_security_level());
		pdu.set_context_engine_id(m_pdu.get_context_engine_id());
		pdu += vb;
		status = snmp.get_next(pdu, *m_target);
		if (status != SNMP_CLASS_SUCCESS)
		{
			printf("COceanNmsSnmp::get_host_res_dev_processor(): snmp get next failed! error msg[%s]", snmp.error_msg(status));
			return false;
		}
		pdu.get_vb(vb, 0);
		Oid oid_item;
		vb.get_oid(oid_item);
		
		if (oid_item.nCompare(oid_item.len(), oid) == 0)
		{
			printf("COceanNmsSnmp::get_host_res_dev_processor(): snmp end of mib view!");
			pdu.clear();
			return false;
		}
		if (oid.nCompare(oid.len(), oid_item) == 0)// Table View 操作时，判断下一个oid与当前oid是否相等，如果不等，结束循环。
		{
			oid_item.trim();	
			if (oid_item == Oid(HR_HRDEVICEPROCESSORTYPE))// 确保为第一个获取的数据
			{
				if (0 == strcmp(vb.get_printable_value(), "1.3.6.1.2.1.25.3.1.3"))
				{
					if (!bbegin)
					{
						nbegin = i;
						bbegin = true;
					}
					nend = max(i, nend);
				}
			}
			if (oid_item == Oid(HR_HRDEVICEPROCESSORDESCR))
			{
				if (i >= nbegin && i <= nend)
				{
					phostres->vecdev_processor_descr.push_back(vb.get_printable_value());
				}
			}
			if (oid_item == Oid(HR_HRDEVICEPROCESSORINDEX))
			{
				if (i >= nbegin && i <= nend)
				{
					phostres->vecdev_processor_num.push_back(atoi(vb.get_printable_value()));
				}
			}
			if (oid_item == Oid(HR_HRDEVICEPROCESSORLOAD))
			{
				//if (i >= nbegin && i <= nend)
				{
					phostres->vecdev_processor_load.push_back(atoi(vb.get_printable_value()));
				}
			}
		}
		else
			btag = false;
		pdu.clear();
	}
	return true;
}

void COceanNmsSnmp::format_date(const char* szvalue, char* szdate)
{
	if (szvalue == NULL)
	{
		printf("COceanNmsSnmp::format_date(): Incoming data can not be empty!");
		return;
	}

	char buf[256] = { 0 };
	for (int i = 0; i<10; i++)
	{
		buf[i] = 0;
	}
	strcpy(buf, szvalue);
	int year = buf[0] * 256 + 256 + buf[1];
	int month = buf[2];
	int day = buf[3];
	int hour = buf[4];
	int minute = buf[5];
	int second = buf[6];
	int msecond = buf[7];

	sprintf(szdate, "%d-%d-%d %d:%d:%d.%d", year, month, day, hour, minute, second, msecond);
}

bool COceanNmsSnmp::get_interface_res(pIFRES pifres)
{
	if (!m_ipAddr.valid() || !m_target->valid())
	{
		cout << "Invalid IP or Invalid target" << endl;
		return false;
	}
	int status;
	// 	Snmp snmp(status, 0, (m_ipAddr.get_ip_version() == Address::version_ipv6));
	Snmp snmp(status, 0);
	if (status != SNMP_CLASS_SUCCESS)
	{
		printf("COceanNmsSnmp::get_interface_res()： snmp status failed！");
		return false;
	}

	get_interface_res( IFR_IFINDEX,		snmp, pifres->vecifr );// 确保为第一个获取的数据
	if(pifres->vecifr.size() == 0)
	{
		printf("COceanNmsSnmp::get_interface_res get_interface_res_ent_ip IFR_IFINDEX value is NULL!!!");	
	}
	else
	{
		get_interface_res( IFR_IFDESC,		snmp, pifres->vecifr );
		get_interface_res( IFR_IFTYPE,		snmp, pifres->vecifr );
		get_interface_res( IFR_IFPHYSADDRESS, snmp, pifres->vecifr );
		get_interface_res( IFR_IFSPEED,		snmp, pifres->vecifr );
		get_interface_res( IFR_IFMTU,		snmp, pifres->vecifr );
		get_interface_res( IFR_IFADMINSTATUS, snmp, pifres->vecifr );
		get_interface_res( IFR_IFOPERSTATUS, snmp, pifres->vecifr );
		get_interface_res( IFR_IFLASTCHANGE, snmp, pifres->vecifr );
		get_interface_res( IFR_IFALIAS, snmp, pifres->vecifr);
	}

	get_interface_res_ent_ip(IFR_IPADENTIFINDEX, snmp, pifres->vecentip);// 确保为第一个获取的数据
	if(pifres->vecentip.size() == 0)
	{
		printf("COceanNmsSnmp::get_interface_res get_interface_res_ent_ip IFR_IPADENTIFINDEX value is NULL!!!");
	}
	else
	{
		get_interface_res_ent_ip( IFR_IPADENTADDR, snmp, pifres->vecentip );
		get_interface_res_ent_ip( IFR_IPADENTNETMASK, snmp, pifres->vecentip );
	}
	return true;
}

bool COceanNmsSnmp::get_interface_res_ent_ip(string szoid, Snmp& snmp, vector< ENTIP >& vecentip)
{
	Oid oid(szoid.c_str());
	int status = 0;
	Vb vb;
	vb.set_oid(oid);
	bool btag = true;
	printf("get_interface_res_ent_ip vecentip.size:%d\n", (int)(vecentip.size()));
	int i = 0, j = 0;
	for (i, j; btag; i++)
	{
		Pdu pdu;
		pdu.set_security_level(m_pdu.get_security_level());
		pdu.set_context_engine_id(m_pdu.get_context_engine_id());
		pdu += vb;
		status = snmp.get_next(pdu, *m_target);
		if (status != SNMP_CLASS_SUCCESS)
		{
			printf("COceanNmsSnmp::get_interface_res_ent_ip(): snmp get_next failed!");
			return false;
		}

		pdu.get_vb(vb, 0);
		Oid oid_item;
		vb.get_oid(oid_item);
		if (oid_item.nCompare(oid_item.len(), oid) == 0)
		{
			printf("COceanNmsSnmp::get_interface_res_ent_ip(): snmp end of mib view!");
			pdu.clear();
			return false;
		}
		if (oid.nCompare(oid.len(), oid_item) == 0)// Table View 操作时，判断下一个oid与当前oid是否相等，如果不等，结束循环。
		{
			//oid_item.trim( 4 );
			vb.set_oid(oid_item);
			//ENTIP ent_ip;
//			if (!strcmp(szoid, IFR_IPADENTIFINDEX))
			if (szoid == IFR_IPADENTIFINDEX)
			{
				vecentip.resize(++j);
				vecentip[i].nindex = atoi(vb.get_printable_value());;
			}
//			if (!strcmp(szoid, IFR_IPADENTADDR))
			if (szoid == IFR_IPADENTADDR)
			{
				vecentip[i].strent_addr = string(vb.get_printable_value());;
			}
//			if (!strcmp(szoid, IFR_IPADENTNETMASK))
			if (szoid == IFR_IPADENTNETMASK)
			{
				vecentip[i].strent_net_mask = string(vb.get_printable_value());;
			}
		}
		else
			btag = false;
		pdu.clear();
	}
	return true;
}

bool COceanNmsSnmp::get_interface_res(string szoid, Snmp& snmp, vector<IFR>& vecifr)
{
	Oid oid(szoid.c_str());
	int status = 0;
	Vb vb;
	vb.set_oid(oid);
	bool btag = true;
	for (int i = 1; btag; ++i)
	{
		Pdu pdu;
		pdu.set_security_level(m_pdu.get_security_level());
		pdu.set_context_engine_id(m_pdu.get_context_engine_id());
		pdu += vb;
		status = snmp.get_next(pdu, *m_target);
		if (status != SNMP_CLASS_SUCCESS)
		{
			printf("COceanNmsSnmp::get_interface_res(): snmp get_next failed!");
			return false;
		}

		pdu.get_vb(vb, 0);
		Oid oid_item;
		vb.get_oid(oid_item);
		if (oid_item.nCompare(oid_item.len(), oid) == 0)
		{
			printf("COceanNmsSnmp::get_interface_res(): snmp end of mib view!");
			pdu.clear();
			return false;
		}
		if (oid.nCompare(oid.len(), oid_item) == 0)// Table View 操作时，判断下一个oid与当前oid是否相等，如果不等，结束循环。
		{
			oid_item.trim();
			IFR ifr;
			if (oid_item == Oid(IFR_IFINDEX))// 确保为第一个获取的数据
				ifr.nindex = atoi(vb.get_printable_value());
			if (oid_item == Oid(IFR_IFDESC))
			{
				char cvalue[256] = { 0 };
				vb.get_value(cvalue);
				vecifr[i - 1].strdescr = cvalue;
				// 				vecifr[i-1].strdescr = string( vb.get_printable_value() );
			}
			if (oid_item == Oid(IFR_IFTYPE))
				vecifr[i - 1].ntype = atoi(vb.get_printable_value());
			if (oid_item == Oid(IFR_IFPHYSADDRESS))
			{
				char a1[16];
				char a2[16];
				char a3[16];
				char a4[16];
				char a5[16];
				char a6[16];
				char addr[256];
				bzero(addr, 256);
				sscanf(vb.get_printable_value(), "%s %s %s %s %s %s %*s", a1, a2, a3, a4, a5, a6);
				sprintf(addr, "%s %s %s %s %s %s", a1, a2, a3, a4, a5, a6);
				//vecifr[i - 1].strphys_address = string(vb.get_printable_value());
				vecifr[i - 1].strphys_address = string(addr);
			}
			if (oid_item == Oid(IFR_IFSPEED))
				vecifr[i - 1].nspeed = atoi(vb.get_printable_value());
			if (oid_item == Oid(IFR_IFMTU))
				vecifr[i - 1].nmtu = atoi(vb.get_printable_value());
			if (oid_item == Oid(IFR_IFADMINSTATUS))
				vecifr[i - 1].nadmin_status = atoi(vb.get_printable_value());
			if (oid_item == Oid(IFR_IFOPERSTATUS))
				vecifr[i - 1].noper_status = atoi(vb.get_printable_value());
			if (oid_item == Oid(IFR_IFLASTCHANGE))
				vecifr[i - 1].strlast_change = string(vb.get_printable_value());
			if (vecifr.size() == 0 || vecifr.size() < i)// 确保不能越界
				vecifr.push_back(ifr);
		}
		else
			btag = false;
		pdu.clear();
	}
	return true;
}

bool COceanNmsSnmp::get_host_perf(pHOSTPERF phostperf, int flag)
{
	if (!m_ipAddr.valid() || !m_target->valid())
	{
		cout << "Invalid IP or Invalid target" << endl;
		return false;
	}
	int status = 0;
	// 	Snmp snmp(status, 0, (m_ipAddr.get_ip_version() == Address::version_ipv6));
	Snmp snmp(status, 0);
	if (status != SNMP_CLASS_SUCCESS)
	{
		printf("COceanNmsSnmp::get_host_perf()： snmp status failed！");
		return false;
	}
	get_host_perf_processor_load(HP_HRPROCESSORLOAD, snmp, phostperf->vecprocessor_load);
	get_host_perf_storage(snmp, phostperf);
	if(flag != 0)
		get_host_perf_swrun( snmp, phostperf->vecswrun );
	//get_host_perf_installed( snmp, phostperf->vecinstalled );
	return true;
}

bool COceanNmsSnmp::get_host_proc_soft(pHOSTPERF phostperf, int os_flag)
{
	if (!m_ipAddr.valid() || !m_target->valid())
	{
		cout << "Invalid IP or Invalid target" << endl;
		return false;
	}
	int status = 0;
	// 	Snmp snmp(status, 0, (m_ipAddr.get_ip_version() == Address::version_ipv6));
	Snmp snmp(status, 0);
	if (status != SNMP_CLASS_SUCCESS)
	{
		printf("COceanNmsSnmp::get_host_proc_soft() snmp status failed!");
		return false;
	}
	if(os_flag == WINDOWS)
		get_host_perf_swrun(snmp, phostperf->vecswrun);
	get_host_perf_installed(snmp, phostperf->vecinstalled);
	return true;
}

bool COceanNmsSnmp::get_host_perf_installed(Snmp& snmp, vector<INSTALLED>& vecInstalled)
{
	get_host_perf_installed( HP_HRINSTALLEDNAME,snmp, vecInstalled );// 确保为第一个获取的数据
	if(vecInstalled.size() == 0)
	{
		printf("COceanNmsSnmp::get_host_perf_installed HP_HRINSTALLEDNAME value is NULL!!!");	
	}
	else
	{
		get_host_perf_installed( HP_HRINSTALLEDTYPE,snmp, vecInstalled );
		get_host_perf_installed( HP_HRINSTALLEDDATE,snmp, vecInstalled );
	}
	return true;
}

bool COceanNmsSnmp::get_host_perf_installed(string szoid, Snmp& snmp, vector<INSTALLED>& vecInstalled)
{
	Oid oid(szoid.c_str());
	int status = 0;
	Vb vb;
	vb.set_oid(oid);
	bool btag = true;
	for (int i = 1; btag; ++i)
	{
		Pdu pdu;
		pdu.set_security_level(m_pdu.get_security_level());
		pdu.set_context_engine_id(m_pdu.get_context_engine_id());
		pdu += vb;
		status = snmp.get_next(pdu, *m_target);
		if (status != SNMP_CLASS_SUCCESS)
		{
			printf("COceanNmsSnmp::get_host_perf_installed(): snmp get_next failed!");
			return false;
		}

		pdu.get_vb(vb, 0);
		Oid oid_item;
		vb.get_oid(oid_item);
		if (oid_item.nCompare(oid_item.len(), oid) == 0)
		{
			printf("COceanNmsSnmp::get_host_perf_installed(): snmp end of mib view!");
			pdu.clear();
			return false;
		}
		if (oid.nCompare(oid.len(), oid_item) == 0)// Table View 操作时，判断下一个oid与当前oid是否相等，如果不等，结束循环。
		{
			oid_item.trim();
			INSTALLED installed;
			if (oid_item == Oid(HP_HRINSTALLEDNAME))// 确保为第一个获取的数据
				installed.strname = string(vb.get_printable_value());
			if (oid_item == Oid(HP_HRINSTALLEDTYPE))
				vecInstalled[i - 1].ntype = atoi(vb.get_printable_value());
			if (oid_item == Oid(HP_HRINSTALLEDDATE))
			{
				OctetStr val;
				vb.get_value(val);
				char date[128] = { 0 };
				format_date((char*)val.data(), date);
				vecInstalled[i - 1].strdate = date;
			}
			if (vecInstalled.size() < i)// 确保不能越界
				vecInstalled.push_back(installed);
		}
		else
			btag = false;
		pdu.clear();
	}
	return true;
}

bool COceanNmsSnmp::get_host_perf_swrun(Snmp& snmp, vector<SWRUN>& vecswrun)
{
	get_host_perf_swrun( HP_HRSWRUNINDEX,snmp, vecswrun );// 确保为第一个获取的数据
	if(vecswrun.size() == 0)
	{
		printf("COceanNmsSnmp::get_host_perf_swrun HP_HRSWRUNINDEX value is NULL!!!");	
	}
	else
	{
		get_host_perf_swrun( HP_HRSWRUNNAME,snmp, vecswrun );
		get_host_perf_swrun( HP_HRSWRUNPATH,snmp, vecswrun );
		get_host_perf_swrun( HP_HRSWRUNPARA, snmp, vecswrun );
		get_host_perf_swrun( HP_HRSWRUNTYPE,snmp, vecswrun );
		get_host_perf_swrun( HP_HRSWRUNSTATUS,snmp, vecswrun );
		get_host_perf_swrun( HP_HRSWRUNPERFCPU,snmp, vecswrun );
		get_host_perf_swrun( HP_HRSWRUNPERFMEM,snmp, vecswrun );
	}
	return true;
}

bool COceanNmsSnmp::get_host_perf_swrun(string szoid, Snmp& snmp, vector<SWRUN>& vecswrun)
{
	Oid oid(szoid.c_str());
	int status = 0;
	Vb vb;
	vb.set_oid(oid);
	bool btag = true;
	int len = 0;
	len = vecswrun.size();
	for (int i = 1; btag; ++i)
	{
		if(len != 0 && i > len)
			break;
		Pdu pdu;
		pdu.set_security_level(m_pdu.get_security_level());
		pdu.set_context_engine_id(m_pdu.get_context_engine_id());
		pdu += vb;
		status = snmp.get_next(pdu, *m_target);
		if (status != SNMP_CLASS_SUCCESS)
		{
			printf("COceanNmsSnmp::get_host_perf_swrun(): snmp get_next failed!!");
			return false;
		}

		pdu.get_vb(vb, 0);
		Oid oid_item;
		vb.get_oid(oid_item);
		if (oid_item.nCompare(oid_item.len(), oid) == 0)
		{
			printf("COceanNmsSnmp::get_host_perf_swrun(): snmp end of mib view!");
			pdu.clear();
			return false;
		}
		if (oid.nCompare(oid.len(), oid_item) == 0)// Table View 操作时，判断下一个oid与当前oid是否相等，如果不等，结束循环。
		{
			oid_item.trim();
			SWRUN swrun;
			if (oid_item == Oid(HP_HRSWRUNINDEX))// 确保为第一个获取的数据
				swrun.nindex = atoi(vb.get_printable_value());
			if (oid_item == Oid(HP_HRSWRUNNAME))
				vecswrun[i - 1].strname = string(vb.get_printable_value());
			if (oid_item == Oid(HP_HRSWRUNPATH))
				vecswrun[i - 1].strpath = string(vb.get_printable_value());
			if (oid_item == Oid(HP_HRSWRUNPARA))
				vecswrun[i - 1].strpara = string(vb.get_printable_value());
			if (oid_item == Oid(HP_HRSWRUNTYPE))
				vecswrun[i - 1].ntype = atoi(vb.get_printable_value());
			if (oid_item == Oid(HP_HRSWRUNSTATUS))
				vecswrun[i - 1].nstatus = atoi(vb.get_printable_value());
			if (oid_item == Oid(HP_HRSWRUNPERFCPU))
				vecswrun[i - 1].nperfcpu = atoi(vb.get_printable_value());
			if (oid_item == Oid(HP_HRSWRUNPERFMEM))
				vecswrun[i - 1].nperfmem = atoi(vb.get_printable_value());
			if (vecswrun.size() < i)// 确保不能越界
				vecswrun.push_back(swrun);
		}
		else
			btag = false;
		pdu.clear();
	}
	return true;
}

bool COceanNmsSnmp::get_host_perf_storage(Snmp& snmp, pHOSTPERF phostperf)
{
	int nRam = 0;
	int nVirtualMemory = 0;
	int nMemoryBuf = 0; 
	int nCachedMem = 0;
	int nFixedDiskBegin = 0;
	int nFixedDiskEnd = 0;

	get_host_perf_storage(HP_HRSTORAGETYPE, snmp, phostperf, nRam, nVirtualMemory, nMemoryBuf, nCachedMem, nFixedDiskBegin, nFixedDiskEnd);// 确保为第一个获取的数据
	get_host_perf_storage(HP_HRSTORAGEDESC, snmp, phostperf, nRam, nVirtualMemory, nMemoryBuf, nCachedMem, nFixedDiskBegin, nFixedDiskEnd);
	get_host_perf_storage(HP_HRSTORAGEUNITS, snmp, phostperf, nRam, nVirtualMemory, nMemoryBuf, nCachedMem, nFixedDiskBegin, nFixedDiskEnd);
	get_host_perf_storage(HP_HRSTORAGESIZE, snmp, phostperf, nRam, nVirtualMemory, nMemoryBuf, nCachedMem, nFixedDiskBegin, nFixedDiskEnd);
	get_host_perf_storage(HP_HRSTORAGEUSED, snmp, phostperf, nRam, nVirtualMemory, nMemoryBuf, nCachedMem, nFixedDiskBegin, nFixedDiskEnd);

	return true;
}

bool COceanNmsSnmp::get_host_perf_storage(string szoid, Snmp& snmp, pHOSTPERF phostperf, int& nRam, int& nVirtualMemory, int& nMemoryBuf, int& nCachedMem, int& nFixedDiskBegin, int& nFixedDiskEnd)
{
	Oid oid(szoid.c_str());
	int status = 0;
	Vb vb;
	vb.set_oid(oid);
	bool btag = true;
	bool bbegin = true;
	for (int i = 1; btag; ++i)
	{
		Pdu pdu;
		pdu.set_security_level(m_pdu.get_security_level());
		pdu.set_context_engine_id(m_pdu.get_context_engine_id());
		pdu += vb;
		status = snmp.get_next(pdu, *m_target);
		if (status != SNMP_CLASS_SUCCESS)
		{
			printf("COceanNmsSnmp::get_host_perf_storage(): snmp get_next failed!");
			return false;
		}

		pdu.get_vb(vb, 0);
		Oid oid_item;
		vb.get_oid(oid_item);
		if (oid_item.nCompare(oid_item.len(), oid) == 0)
		{
			printf("COceanNmsSnmp::get_host_perf_storage(): snmp end of mib view!");
			pdu.clear();
			return false;
		}
		if (oid.nCompare(oid.len(), oid_item) == 0)// Table View 操作时，判断下一个oid与当前oid是否相等，如果不等，结束循环。
		{
			oid_item.trim();
			if (oid_item == Oid(HP_HRSTORAGETYPE))// 确保为第一个获取的数据
			{
				if (0 == strcmp(vb.get_printable_value(), "1.3.6.1.2.1.25.2.1.4")) // fixeddisk
				{
					if (bbegin)
					{
						nFixedDiskBegin = i;
						bbegin = false;
					}
					nFixedDiskEnd = i;
					STORAGEFIXEDDISK storagefixdisk;
					storagefixdisk.nstorage_index = i;
					phostperf->vecstorage_fixed_disk.push_back(storagefixdisk);
				}
				else if (0 == strcmp(vb.get_printable_value(), "1.3.6.1.2.1.25.2.1.3")) // virtualmemory
				{
					nVirtualMemory = i;
				}
				else if (0 == strcmp(vb.get_printable_value(), "1.3.6.1.2.1.25.2.1.2")) // ram
				{
					nRam = i;
				}
				else if (0 == strcmp(vb.get_printable_value(), "1.3.6.1.2.1.25.2.1.1") && !nMemoryBuf) // memory buffers
				{
					nMemoryBuf = i;
				}
				else if (0 == strcmp(vb.get_printable_value(), "1.3.6.1.2.1.25.2.1.1") && nMemoryBuf && !nCachedMem) // cached memory
				{
					nCachedMem = i;
				}
			}
			if (oid_item == Oid(HP_HRSTORAGESIZE))
			{
				if (i == nRam)
				{
					phostperf->nstorage_ram_size = (long long)atoi(vb.get_printable_value()) * phostperf->nstorage_ram_units;
				}
				else if (i == nVirtualMemory)
				{
					phostperf->nstorage_virtual_memory_size = (long long)atoi(vb.get_printable_value()) * phostperf->nstorage_virtual_memory_units;
				}
				else if (i == nMemoryBuf)
				{
					phostperf->nstorage_memory_buffers_size = (long long)atoi(vb.get_printable_value()) * phostperf->nstorage_memory_buffers_units;
				}
				else if (i == nCachedMem)
				{
					phostperf->nstorage_cached_memory_size = (long long)atoi(vb.get_printable_value()) * phostperf->nstorage_cached_memory_units;
				}
				else
				{
					for (int j = 0; j < phostperf->vecstorage_fixed_disk.size(); j++)
					{
						if (i == phostperf->vecstorage_fixed_disk[j].nstorage_index)
						{
							phostperf->vecstorage_fixed_disk[j].nstorage_size = (long long)atoi(vb.get_printable_value())*(long long)phostperf->vecstorage_fixed_disk[j].nstorage_units;
							break;
						}
					}
				}
			}
			if (oid_item == Oid(HP_HRSTORAGEUSED))
			{
				if (i == nRam)
				{
					phostperf->nstorage_ram_used = (long long)atoi(vb.get_printable_value()) * phostperf->nstorage_ram_units;
				}
				else if (i == nVirtualMemory)
				{
					phostperf->nstorage_virtual_memory_used = (long long)atoi(vb.get_printable_value()) * phostperf->nstorage_virtual_memory_units;
				}
				else if (i == nMemoryBuf)
				{
					phostperf->nstorage_memory_buffers_used = (long long)atoi(vb.get_printable_value()) * phostperf->nstorage_memory_buffers_units;
				}
				else if (i == nCachedMem)
				{
					phostperf->nstorage_cached_memory_used = (long long)atoi(vb.get_printable_value()) * phostperf->nstorage_cached_memory_units;
				}
				else
				{
					for (int j = 0; j < phostperf->vecstorage_fixed_disk.size(); j++)
					{
						if (i == phostperf->vecstorage_fixed_disk[j].nstorage_index)
						{
							phostperf->vecstorage_fixed_disk[j].nstorage_used = (long long)atoi(vb.get_printable_value()) * phostperf->vecstorage_fixed_disk[j].nstorage_units;
							break;
						}
					}
				}
			}
			if (oid_item == Oid(HP_HRSTORAGEDESC))
			{
				for (int j = 0; j < phostperf->vecstorage_fixed_disk.size(); j++)
				{
					if (i == phostperf->vecstorage_fixed_disk[j].nstorage_index)
					{
						phostperf->vecstorage_fixed_disk[j].strstorage_descr = string(vb.get_printable_value());
						break;
					}
				}
				//if ( i >= nFixedDiskBegin && i <= nFixedDiskEnd )
				//{
				//	phostperf->vecstorage_fixed_disk[i-1].strstorage_descr = string//( vb.get_printable_value() );
				//}
			}
			if (oid_item == Oid(HP_HRSTORAGEUNITS))
			{
				if (i == nRam)
				{
					phostperf->nstorage_ram_units = atoi(vb.get_printable_value());
				}
				else if (i == nVirtualMemory)
				{
					phostperf->nstorage_virtual_memory_units = atoi(vb.get_printable_value());
				}
				else if (i == nMemoryBuf)
				{
					phostperf->nstorage_memory_buffers_units = atoi(vb.get_printable_value());
				}
				else if (i == nCachedMem)
				{
					phostperf->nstorage_cached_memory_units = atoi(vb.get_printable_value());
				}
				else
				{
					for (int j = 0; j < phostperf->vecstorage_fixed_disk.size(); j++)
					{
						if (i == phostperf->vecstorage_fixed_disk[j].nstorage_index)
						{
							phostperf->vecstorage_fixed_disk[j].nstorage_units = atoi(vb.get_printable_value());
							break;
						}
					}
				}
			}
		}
		else
			btag = false;
		pdu.clear();
	}
	return true;
}

bool COceanNmsSnmp::get_host_perf_processor_load(string szoid, Snmp& snmp, vector<int>& vecprocessorload)
{
	Oid oid(szoid.c_str());
	int status = 0;
	Vb vb;
	vb.set_oid(oid);
	bool btag = true;
	for (int i = 1; btag; ++i)
	{
		Pdu pdu;
		pdu.set_security_level(m_pdu.get_security_level());
		pdu.set_context_engine_id(m_pdu.get_context_engine_id());
		pdu += vb;
		status = snmp.get_next(pdu, *m_target);
		if (status != SNMP_CLASS_SUCCESS)
		{
			printf("COceanNmsSnmp::get_host_perf_processor_load(): snmp get_next failed!");
			return false;
		}

		pdu.get_vb(vb, 0);
		Oid oid_item;
		vb.get_oid(oid_item);
		if (oid_item.nCompare(oid_item.len(), oid) == 0)
		{
			printf("COceanNmsSnmp::get_host_perf_processor_load(): snmp end of mib view!");
			pdu.clear();
			return false;
		}
		if (oid.nCompare(oid.len(), oid_item) == 0)// Table View 操作时，判断下一个oid与当前oid是否相等，如果不等，结束循环。
		{
			oid_item.trim();
			if (oid_item == Oid(HP_HRPROCESSORLOAD))
				vecprocessorload.push_back(atoi(vb.get_printable_value()));
		}
		else
			btag = false;
		pdu.clear();
	}
	return true;
}

bool COceanNmsSnmp::get_interface_perf(vector<IFPERF>& vecifperf)
{
	if (!m_ipAddr.valid() || !m_target->valid())
	{
		cout << "Invalid IP or Invalid target" << endl;
		return false;
	}
	int status = 0;
	// 	Snmp snmp(status, 0, (m_ipAddr.get_ip_version() == Address::version_ipv6));
	Snmp snmp(status, 0);
	if (status != SNMP_CLASS_SUCCESS)
	{
		printf("COceanNmsSnmp::get_interface_perf()： snmp status failed！");
		return false;
	}
	get_interface_perf( IFP_IFINDEX, snmp, vecifperf );// 确保为第一个获取的数据
	if(vecifperf.size() == 0)
	{
		printf("COceanNmsSnmp::get_interface_perf IFP_IFINDEX value is NULL!!!");	
	}
	else
	{
		get_interface_perf( IFP_IFDESC, snmp, vecifperf );
		get_interface_perf( IFP_IFADMINSTATUS, snmp, vecifperf );
		get_interface_perf( IFP_IFOPERSTATUS, snmp, vecifperf );
		get_interface_perf( IFP_IFSPEED, snmp, vecifperf );
		get_interface_perf( IFP_IFINOCTECTS, snmp, vecifperf );
		get_interface_perf( IFP_IFINERRORS, snmp, vecifperf );
		get_interface_perf( IFP_IFINDISCARDS, snmp, vecifperf );
		get_interface_perf( IFP_IFOUTOCTECTS, snmp, vecifperf );
		get_interface_perf( IFP_IFOUTERRORS, snmp, vecifperf );
		get_interface_perf( IFP_IFOUTDISCARDS, snmp, vecifperf );
	}
	return true;
}

bool COceanNmsSnmp::get_interface_perf(string szoid, Snmp& snmp, vector<IFPERF>& vecifperf)
{
	Oid oid(szoid.c_str());
	int status = 0;
	Vb vb;
	vb.set_oid(oid);
	bool btag = true;
	int len = 0;
	len = vecifperf.size();
        printf("COceanNmsSnmp::get_interface_perf(): vecifperf.size: %d", len);
	for (int i = 1; btag; ++i)
	{
		if(len != 0 && i > len)
			break;
		Pdu pdu;
		pdu.set_security_level(m_pdu.get_security_level());
		pdu.set_context_engine_id(m_pdu.get_context_engine_id());
		pdu += vb;
		status = snmp.get_next(pdu, *m_target);
		if (status != SNMP_CLASS_SUCCESS)
		{
			printf("COceanNmsSnmp::get_interface_perf(): snmp get_next failed!");
			return false;
		}

		pdu.get_vb(vb, 0);
		Oid oid_item;
		vb.get_oid(oid_item);
		if (oid_item.nCompare(oid_item.len(), oid) == 0)
		{
			printf("COceanNmsSnmp::get_interface_perf(): snmp end of mib view!");
			pdu.clear();
			return false;
		}
		if (oid.nCompare(oid.len(), oid_item) == 0)// Table View 操作时，判断下一个oid与当前oid是否相等，如果不等，结束循环。
		{
			oid_item.trim();
			IFPERF ifperf;
			if (oid_item == Oid(IFP_IFINDEX)) // 确保为第一个获取的数据
				ifperf.nindex = atoi(vb.get_printable_value());
			if (oid_item == Oid(IFP_IFDESC))
			{
				char cvalue[256] = { 0 };
				vb.get_value(cvalue);
				vecifperf[i - 1].strdescr = cvalue;
				// 				vecifperf[i-1].strdescr = string( vb.get_printable_value() );
			}
			if (oid_item == Oid(IFP_IFADMINSTATUS))
				vecifperf[i - 1].nadmin_status = atoi(vb.get_printable_value());
			if (oid_item == Oid(IFP_IFOPERSTATUS))
				vecifperf[i - 1].noper_status = atoi(vb.get_printable_value());
			if (oid_item == Oid(IFP_IFSPEED))
				vecifperf[i - 1].nspeed = atoi(vb.get_printable_value());
			if (oid_item == Oid(IFP_IFINOCTECTS))
				vecifperf[i - 1].nin_octects = atoi(vb.get_printable_value());
			if (oid_item == Oid(IFP_IFINERRORS))
				vecifperf[i - 1].nin_errors = atoi(vb.get_printable_value());
			if (oid_item == Oid(IFP_IFINDISCARDS))
				vecifperf[i - 1].nin_discards = atoi(vb.get_printable_value());
			if (oid_item == Oid(IFP_IFOUTOCTECTS))
				vecifperf[i - 1].nout_octects = atoi(vb.get_printable_value());
			if (oid_item == Oid(IFP_IFOUTERRORS))
				vecifperf[i - 1].nout_errors = atoi(vb.get_printable_value());
			if (oid_item == Oid(IFP_IFOUTDISCARDS))
				vecifperf[i - 1].nout_discards = atoi(vb.get_printable_value());
			if (vecifperf.size() == 0 || vecifperf.size() < i)// 确保不能越界
				vecifperf.push_back(ifperf);
		}
		else
			btag = false;
		pdu.clear();
	}
	return true;
}

#if 0
bool COceanNmsSnmp::get_interface_perf(map<int, IFPERF>& mapifperf)
{
	if (!m_ipAddr.valid() || !m_target->valid())
	{
		cout << "Invalid IP or Invalid target" << endl;
		return false;
	}
	int status = 0;
	// 	Snmp snmp(status, 0, (m_ipAddr.get_ip_version() == Address::version_ipv6));
	Snmp snmp(status, 0);
	if (status != SNMP_CLASS_SUCCESS)
	{
		return false;
	}
	get_interface_perf(IFP_IFINDEX, snmp, mapifperf);// 确保为第一个获取的数据
	get_interface_perf(IFP_IFDESC, snmp, mapifperf);
	get_interface_perf(IFP_IFADMINSTATUS, snmp, mapifperf);
	get_interface_perf(IFP_IFOPERSTATUS, snmp, mapifperf);
	get_interface_perf(IFP_IFSPEED, snmp, mapifperf);
	get_interface_perf(IFP_IFINOCTECTS, snmp, mapifperf);
	get_interface_perf(IFP_IFINERRORS, snmp, mapifperf);
	get_interface_perf(IFP_IFINDISCARDS, snmp, mapifperf);
	get_interface_perf(IFP_IFOUTOCTECTS, snmp, mapifperf);
	get_interface_perf(IFP_IFOUTERRORS, snmp, mapifperf);
	get_interface_perf(IFP_IFOUTDISCARDS, snmp, mapifperf);

	return true;
}

bool COceanNmsSnmp::get_interface_perf(char* szoid, Snmp& snmp, map<int, IFPERF>& mapifperf)
{
	Oid oid(szoid);
	int status = 0;
	Vb vb;
	vb.set_oid(oid);
	bool btag = true;
	//IFPERF ifPerf;

	int i = 0, j = 0;
	for (; btag == true;)
	{
		int status;
		Snmp snmp(status);

		Pdu pdu;
		pdu.set_security_level(m_pdu.get_security_level());
		pdu.set_context_engine_id(m_pdu.get_context_engine_id());
		pdu += vb;
		if ((status = snmp.get_next(pdu, *m_target)) == SNMP_CLASS_SUCCESS)
		{
			pdu.get_vb(vb, 0);
			Oid present_oid;           //该表项的Oid
			vb.get_oid(present_oid);
			if (present_oid.nCompare(present_oid.len(), oid) == 0)
			{
				printf("COceanNmsSnmp::get_interface_perf()： snmp end of mib view！");
				printf("COceanNmsSnmp::get_interface_perf()： snmp end of mib view！");
				pdu.clear();
				break;
			}
			//判断是否已越界，如果是则结束循环
			if (oid.nCompare(oid.len(), present_oid) == 0)
			{
				vb.set_oid(present_oid);
				/*
				在这里进行数据处理
				*/

				if (!strcmp(szoid, IFP_IFINDEX))
				{
					mapifperf[i++].nindex = atoi(vb.get_printable_value());
				}
				if (!strcmp(szoid, IFR_IFDESC))
					mapifperf[i++].strdescr = string(vb.get_printable_value());
				if (!strcmp(szoid, IFP_IFADMINSTATUS))
					mapifperf[i++].nadmin_status = atoi(vb.get_printable_value());
				if (!strcmp(szoid, IFP_IFOPERSTATUS))
					mapifperf[i++].noper_status = atoi(vb.get_printable_value());
				if (!strcmp(szoid, IFP_IFSPEED))
					mapifperf[i++].nspeed = atoi(vb.get_printable_value());
				if (!strcmp(szoid, IFP_IFINOCTECTS))
					mapifperf[i++].nin_octects = atoi(vb.get_printable_value());
				if (!strcmp(szoid, IFP_IFINERRORS))
					mapifperf[i++].nin_errors = atoi(vb.get_printable_value());
				if (!strcmp(szoid, IFP_IFINDISCARDS))
					mapifperf[i++].nin_discards = atoi(vb.get_printable_value());
				if (!strcmp(szoid, IFP_IFOUTOCTECTS))
					mapifperf[i++].nout_octects = atoi(vb.get_printable_value());
				if (!strcmp(szoid, IFP_IFOUTERRORS))
					mapifperf[i++].nout_errors = atoi(vb.get_printable_value());
				if (!strcmp(szoid, IFP_IFOUTDISCARDS))
					mapifperf[i++].nout_discards = atoi(vb.get_printable_value());
			}
			else
			{
				btag = false;
			}
		}
		else
		{
			//printf(Poco::format("collect snmp interfaces message table error, %s.", snmp.error_msg(status)));
			cout << snmp.error_msg(status);
			btag = false;
		}
		pdu.clear();
	}
	return true;
}
#endif

bool COceanNmsSnmp::get_room_sensor_res(vector<ROOMSENSORRES>& vecRoomSensorRes)
{
	if (!m_ipAddr.valid() || !m_target->valid())
	{
		cout << "Invalid IP or Invalid target" << endl;
		return false;
	}
	int status;
	// 	Snmp snmp(status, 0, (m_ipAddr.get_ip_version() == Address::version_ipv6));
	Snmp snmp(status, 0);
	if (status != SNMP_CLASS_SUCCESS)
	{
		printf("COceanNmsSnmp::get_room_sensor_res()： snmp status failed！");
		return false;
	}

	get_room_sensor_res(ROOM_SSSERIALNUM, snmp, vecRoomSensorRes);
	if(vecRoomSensorRes.size() == 0)
	{
		printf("COceanNmsSnmp::get_room_sensor_res ROOM_SSSERIALNUM value is NULL!!!");	
	}
	else
	{
		get_room_sensor_res(ROOM_SSNAME, snmp, vecRoomSensorRes);
		get_room_sensor_res(ROOM_SSTYPE, snmp, vecRoomSensorRes);
		get_room_sensor_res(ROOM_SSSUBTYPE, snmp, vecRoomSensorRes);
		get_room_sensor_res(ROOM_SSUNITS, snmp, vecRoomSensorRes);
		get_room_sensor_res(ROOM_ENAVAILABLE, snmp, vecRoomSensorRes);
	}

	return true;
}

bool COceanNmsSnmp::get_room_sensor_res(string szoid, Snmp& snmp, vector<ROOMSENSORRES>& vecRoomSensorRes)
{
	Oid oid(szoid.c_str());
	int status = 0;
	Vb vb;
	vb.set_oid(oid);
	bool btag = true;
	for (int i = 0, j = 0; btag; ++i)
	{
		Pdu pdu;
		pdu.set_security_level(m_pdu.get_security_level());
		pdu.set_context_engine_id(m_pdu.get_context_engine_id());
		pdu += vb;
		status = snmp.get_next(pdu, *m_target);
		if (status != SNMP_CLASS_SUCCESS)
		{
			printf("COceanNmsSnmp::get_room_sensor_res(): snmp get_next failed!");
			return false;
		}

		pdu.get_vb(vb, 0);
		Oid oid_item;
		vb.get_oid(oid_item);
		if (oid_item.nCompare(oid_item.len(), oid) == 0)
		{
			printf("COceanNmsSnmp::get_room_sensor_res(): snmp end of mib view!");
			pdu.clear();
			return false;
		}
		string oid_t = vb.get_printable_oid();
		int n = oid.len();
		if (oid.nCompare(oid.len(), oid_item) == 0)// Table View 操作时，判断下一个oid与当前oid是否相等，如果不等，结束循环。
		{
			vb.set_oid(oid_item);
			ROOMSENSORRES roomSensorRes;
//			if (!strcmp(szoid, ROOM_SSSERIALNUM))
			if (szoid == ROOM_SSSERIALNUM)
			{
				vecRoomSensorRes.resize(++j);
				string indexId = string(vb.get_printable_oid());
				vecRoomSensorRes[i].nsensor_id = i + 1;
				vecRoomSensorRes[i].strsensor_index_value = indexId.substr(30, 5);
				//vecRoomSensorRes[i].nsensor_index_value = atof(indexId.substr(30, 5));
				vecRoomSensorRes[i].nsensor_serial_num = string(vb.get_printable_value());
			}
//			if (!strcmp(szoid, ROOM_SSNAME))
			if (szoid == ROOM_SSNAME)
			{
				if(vecRoomSensorRes.size() == 0)
				{
					printf("COceanNmsSnmp::get_room_sensor_res vecRoomSensorRes.size is 0");
					//return false;
				}
				vecRoomSensorRes[i].strsensor_name = string(vb.get_printable_value());
			}
//			if (!strcmp(szoid, ROOM_SSTYPE))
			if (szoid == ROOM_SSTYPE)
			{
				if(vecRoomSensorRes.size() == 0)
				{
					printf("COceanNmsSnmp::get_room_sensor_res vecRoomSensorRes.size is 0");
					//return false;
				}
				vecRoomSensorRes[i].nsensor_type = atoi(vb.get_printable_value());
			}
//			if (!strcmp(szoid, ROOM_SSSUBTYPE))
			if (szoid == ROOM_SSSUBTYPE)
			{
				if(vecRoomSensorRes.size() == 0)
				{
					printf("COceanNmsSnmp::get_room_sensor_res vecRoomSensorRes.size is 0");
					//return false;
				}
				vecRoomSensorRes[i].nsensor_sub_type = atoi(vb.get_printable_value());
			}
//			if (!strcmp(szoid, ROOM_SSUNITS))
			if (szoid == ROOM_SSUNITS)
			{
				if(vecRoomSensorRes.size() == 0)
				{
					printf("COceanNmsSnmp::get_room_sensor_res vecRoomSensorRes.size is 0");
					//return false;
				}
				vecRoomSensorRes[i].nsensor_units = atoi(vb.get_printable_value());
			}
			if (szoid == ROOM_ENAVAILABLE)
			{
				if(vecRoomSensorRes.size() == 0)
				{
					printf("COceanNmsSnmp::get_room_sensor_res vecRoomSensorRes.size is 0");
					//return false;
				}
				vecRoomSensorRes[i].nsensor_status = atoi(vb.get_printable_value());
			}

			//if (vecifperf.size() == 0 || vecifperf.size() < i)// 确保不能越界
			//	vecifperf.push_back(ifperf);
		}
		else
			btag = false;
		pdu.clear();
	}
	return true;
}

bool COceanNmsSnmp::get_room_environment_para(vector<ROOMENVIRPARA>& vecRoomEnvirPara)
{
	if (!m_ipAddr.valid() || !m_target->valid())
	{
		cout << "Invalid IP or Invalid target" << endl;
		return false;
	}
	int status;
	// 	Snmp snmp(status, 0, (m_ipAddr.get_ip_version() == Address::version_ipv6));
	Snmp snmp(status, 0);
	if (status != SNMP_CLASS_SUCCESS)
	{
		printf("COceanNmsSnmp::get_room_sensor_res()： snmp status failed！");
		return false;
	}

	get_room_environment_para(ROOM_ENAVAILABLE, snmp, vecRoomEnvirPara);
	if(vecRoomEnvirPara.size() == 0)
	{
		printf("COceanNmsSnmp::get_room_environment_para ROOM_ENAVAILABLE value is NULL!!!");	
	}
	else
	{
		get_room_environment_para(ROOM_ENSTATES, snmp, vecRoomEnvirPara);
		get_room_environment_para(ROOM_ENVALUE, snmp, vecRoomEnvirPara);
		get_room_environment_para(ROOM_ENTIMESTAMP, snmp, vecRoomEnvirPara);
	}

	vector<ROOMENVIRPARA> vecRoomIntelEnvirPara;
	get_room_environment_para(ROOM_INTEL_ENAVAILABLE, snmp, vecRoomIntelEnvirPara);
	if (vecRoomIntelEnvirPara.size() == 0)
	{
		printf("COceanNmsSnmp::get_room_sensor_res ROOM_INTEL_ENAVAILABLE value is NULL!!!");
	}
	else
	{
		get_room_environment_para(ROOM_INTEL_ENSTATES, snmp, vecRoomIntelEnvirPara);
		get_room_environment_para(ROOM_INTEL_ENVALUE, snmp, vecRoomIntelEnvirPara);
		get_room_environment_para(ROOM_INTEL_ENTIMESTAMP, snmp, vecRoomIntelEnvirPara);
	}
	vecRoomEnvirPara.insert(vecRoomEnvirPara.begin(), vecRoomIntelEnvirPara.begin(), vecRoomIntelEnvirPara.end());
	
	return true;
}

bool COceanNmsSnmp::get_room_environment_para(string szoid, Snmp& snmp, vector<ROOMENVIRPARA>& vecRoomEnvirPara)
{
	Oid oid(szoid.c_str());
	int status = 0;
	Vb vb;
	vb.set_oid(oid);
	bool btag = true;
	for (int i = 0, j = 0; btag; ++i)
	{
		Pdu pdu;
		pdu.set_security_level(m_pdu.get_security_level());
		pdu.set_context_engine_id(m_pdu.get_context_engine_id());
		pdu += vb;
		status = snmp.get_next(pdu, *m_target);
		if (status != SNMP_CLASS_SUCCESS)
		{
			printf("COceanNmsSnmp::get_room_environment_para(): snmp get_next failed!");
			return false;
		}

		pdu.get_vb(vb, 0);
		Oid oid_item;
		vb.get_oid(oid_item);
		if (oid_item.nCompare(oid_item.len(), oid) == 0)
		{
			printf("COceanNmsSnmp::get_room_environment_para(): snmp end of mib view!");
			pdu.clear();
			return false;
		}
		string oid_t = vb.get_printable_oid();
		int n = oid.len();
		if (oid.nCompare(oid.len(), oid_item) == 0)// Table View 操作时，判断下一个oid与当前oid是否相等，如果不等，结束循环。
		{
			vb.set_oid(oid_item);
			ROOMENVIRPARA roomSensorRes;
			if ( szoid == ROOM_ENAVAILABLE ||  szoid == ROOM_INTEL_ENAVAILABLE)
			{
				vecRoomEnvirPara.resize(++j);
				string indexId = string(vb.get_printable_oid());
				vecRoomEnvirPara[i].strsensor_index_value = indexId.substr(30, 5);
				//vecRoomEnvirPara[i].nsensor_index_value = atof(indexId.substr(30, 5));
				vecRoomEnvirPara[i].nsensor_available = atoi(vb.get_printable_value());
			}
			if ( szoid == ROOM_ENSTATES ||  szoid == ROOM_INTEL_ENSTATES)
			{
				vecRoomEnvirPara[i].nsensor_status = atoi(vb.get_printable_value());
			}
			if ( szoid == ROOM_ENVALUE ||  szoid == ROOM_INTEL_ENVALUE)
			{
				vecRoomEnvirPara[i].nsensor_value = atoi(vb.get_printable_value());
			}
			if ( szoid == ROOM_ENTIMESTAMP ||  szoid == ROOM_INTEL_ENTIMESTAMP)
			{
				vecRoomEnvirPara[i].nsensor_time_stamp = atoi(vb.get_printable_value());
			}
		}
		else
			btag = false;
		pdu.clear();
	}
	return true;
}

bool COceanNmsSnmp::get_room_inlet_sensor_res(vector<ROOMINLETSENSORRES>& vecRoomInletSensorRes)
{
	if (!m_ipAddr.valid() || !m_target->valid())
	{
		cout << "Invalid IP or Invalid target" << endl;
		return false;
	}
	int status;
	// 	Snmp snmp(status, 0, (m_ipAddr.get_ip_version() == Address::version_ipv6));
	Snmp snmp(status, 0);
	if (status != SNMP_CLASS_SUCCESS)
	{
		printf("COceanNmsSnmp::get_room_sensor_res()： snmp status failed！");
		return false;
	}

	get_room_inlet_sensor_res(ROOM_INTEL_SSUNITS, snmp, vecRoomInletSensorRes);

	return true;

}

bool COceanNmsSnmp::get_room_inlet_sensor_res(string szoid, Snmp& snmp, vector<ROOMINLETSENSORRES>& vecRoomInletSensorRes)
{
	Oid oid(szoid.c_str());
	int status = 0;
	Vb vb;
	vb.set_oid(oid);
	bool btag = true;
	for (int i = 0, j = 0; btag; ++i)
	{
		Pdu pdu;
		pdu.set_security_level(m_pdu.get_security_level());
		pdu.set_context_engine_id(m_pdu.get_context_engine_id());
		pdu += vb;
		status = snmp.get_next(pdu, *m_target);
		if (status != SNMP_CLASS_SUCCESS)
		{
			printf("COceanNmsSnmp::get_interface_perf(): snmp get_next failed!");
			return false;
		}

		pdu.get_vb(vb, 0);
		Oid oid_item;
		vb.get_oid(oid_item);
		if (oid_item.nCompare(oid_item.len(), oid) == 0)
		{
			printf("COceanNmsSnmp::get_interface_perf(): snmp end of mib view!");
			pdu.clear();
			return false;
		}
		string oid_t = vb.get_printable_oid();
		int n = oid.len();
		if (oid.nCompare(oid.len(), oid_item) == 0)// Table View 操作时，判断下一个oid与当前oid是否相等，如果不等，结束循环。
		{
			vb.set_oid(oid_item);
			ROOMENVIRPARA roomSensorRes;
			if ( szoid == ROOM_INTEL_SSUNITS)
			{
				vecRoomInletSensorRes.resize(++j);
				//vecRoomInletSensorRes[i].nintel_sensor_id = i + 1;
				string indexId = string(vb.get_printable_oid());
				vecRoomInletSensorRes[i].strinlet_sensor_index_value = indexId.substr(30, 5);
				//vecRoomInletSensorRes[i].nsensor_index_value = atof(indexId.substr(30, 5));
				vecRoomInletSensorRes[i].nimlet_sensor_units = atoi(vb.get_printable_value());
			}
		}
		else
			btag = false;
		pdu.clear();
	}
	return true;
}

bool COceanNmsSnmp::get_room_intel_environment_para(vector<ROOMENVIRPARA>& vecRoomEnvirPara)
{
	if (!m_ipAddr.valid() || !m_target->valid())
	{
		cout << "Invalid IP or Invalid target" << endl;
		return false;
	}
	int status;
	// 	Snmp snmp(status, 0, (m_ipAddr.get_ip_version() == Address::version_ipv6));
	Snmp snmp(status, 0);
	if (status != SNMP_CLASS_SUCCESS)
	{
		printf("COceanNmsSnmp::get_room_sensor_res()： snmp status failed！");
		return false;
	}

	get_room_environment_para(ROOM_INTEL_ENAVAILABLE, snmp, vecRoomEnvirPara);
	if(vecRoomEnvirPara.size() == 0)
	{
		printf("COceanNmsSnmp::get_room_sensor_res ROOM_INTEL_ENAVAILABLE value is NULL!!!");	
	}
	else
	{
		get_room_environment_para(ROOM_INTEL_ENSTATES, snmp, vecRoomEnvirPara);
		get_room_environment_para(ROOM_INTEL_ENVALUE, snmp, vecRoomEnvirPara);
		get_room_environment_para(ROOM_INTEL_ENTIMESTAMP, snmp, vecRoomEnvirPara);
	}

	return true;

}

void  snmp_collect(HOSTPERF& hostperf, MsgGetHostFileSystemListReq *pHostFileSystemReq, SnmpBasePara *pSnmpBasePara, const snmp_version version)
{
	char strPort[10];
	sprintf(strPort, "%d", pSnmpBasePara->port());
	int status_flag = 0;
	COceanNmsSnmp ocean_nms_snmp((SnmpInfo *)&(pHostFileSystemReq->snmp_info()),
			(char *)(pSnmpBasePara->ip_addr().c_str()),
			(const char *)(pSnmpBasePara->read_community().c_str()),
			(const char *)(pSnmpBasePara->write_community().c_str()),
			version,
			status_flag,
			strPort);
	if(status_flag < 0)
	{
		return;
	}

	ocean_nms_snmp.get_host_perf(&hostperf, 1);
}

void snmp_collect(MsgGetHostFileSystemListReq *pHostFileSystemReq, SnmpBasePara *pSnmpBasePara, SnmpExtPara *pSnmpExtPara, MsgGetHostFileSystemListResp *pHostFileSystemResp, const snmp_version version)
{
	char strPort[10];
	sprintf(strPort, "%d", pSnmpBasePara->port());
	int status_flag = 0;
	COceanNmsSnmp ocean_nms_snmp((SnmpInfo *)&(pHostFileSystemReq->snmp_info()), 
		pSnmpBasePara, 
		pSnmpExtPara, 
		version,
		status_flag);
	if(status_flag < 0)
	{
		return;
	}

	HOSTPERF hostperf;
	ocean_nms_snmp.get_host_perf(&hostperf);
}

ostream& operator<<(ostream& out,const STORAGEFIXEDDISK& disk)
{
    out <<	"strstorage_descr = "   <<   disk.strstorage_descr;
	out <<  ", nstorage_index = "     << disk.nstorage_index;
	out <<  ", nstorage_units = "     << disk.nstorage_units;
	out <<  ", nstorage_size = "     << disk.nstorage_size;
	out <<  ", nstorage_used = "    << disk.nstorage_used << endl; 
    return out;
}

ostream& operator<<(ostream& out,const SWRUN& vrun)
{
    out <<	"nindex{0} = "   << vrun.nindex     ;
	out <<  ", strname = "     << vrun.strname  ;
	out <<  ", strpath = "     << vrun.strpath  ;
	out <<  ", strpara = "     << vrun.strpara  ;
	out <<  ", ntype{0} = "    << vrun.ntype    ; 
	out <<  ", nstatus{0} = "  << vrun.nstatus  ; 
	out <<  ", nperfcpu{0} = " << vrun.nperfcpu ;
	out <<  "nperfmem{0} = " << vrun.nperfmem << endl;
 
    return out;
}


