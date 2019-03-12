#include "Ocean_nms_DB.h"
#include "Poco/Util/Application.h"
#include "Poco/Data/Session.h"

using namespace Poco::Data;
using namespace Poco::Data::Keywords;
using Poco::Util::Application;

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/JSONException.h"

using namespace Poco::Dynamic;
using namespace Poco;

std::vector<std::pair<int, std::string>>  YGH{

    //mysql数据库当前总连接数  A
    std::make_pair<int, std::string>(107, "max_used_connections"),

#if 0
    //mysql数据库平均每秒钟的输入\输出流量 X
    std::make_pair<int, std::string>(106, "UPTIME"),
    std::make_pair<int, std::string>(108, "BYTES_RECEIVED"),
    std::make_pair<int, std::string>(109, "BYTES_SENT"),

    //// QPS/TPS X
    std::make_pair<int, std::string>(109, "UPTIME"),
    std::make_pair<int, std::string>(110, "QUESTIONS"),
    std::make_pair<int, std::string>(111, "COM_INSERT"),
    std::make_pair<int, std::string>(112, "COM_UPDATE"),
    std::make_pair<int, std::string>(113, "COM_SELECT"),
    std::make_pair<int, std::string>(114, "COM_DELETE"),
    std::make_pair<int, std::string>(115, "COM_COMMIT"),
    std::make_pair<int, std::string>(116, "COM_ROLLBACK"),

    ///InnoDB缓冲池的读命中率、利用率以及缓冲池脏块的百分率 X
    std::make_pair<int, std::string>(117, "INNODB_BUFFER_POOL_READS"),
    std::make_pair<int, std::string>(118, "INNODB_BUFFER_POOL_READ_REQUESTS"),
    std::make_pair<int, std::string>(119, "INNODB_BUFFER_POOL_PAGES_FREE"),
    std::make_pair<int, std::string>(120, "INNODB_BUFFER_POOL_PAGES_TOTAL"),
    std::make_pair<int, std::string>(121, "INNODB_BUFFER_POOL_PAGES_DIRTY"),

    ///InnoDB缓冲池的读命中率、利用率以及缓冲池脏块的百分率 X
    std::make_pair<int, std::string>(122, "KEY_READS"),
    std::make_pair<int, std::string>(123, "KEY_READ_REQUESTS"),
    std::make_pair<int, std::string>(124, "KEY_WRITES"),
    std::make_pair<int, std::string>(125, "KEY_WRITE_REQUESTS"),
    std::make_pair<int, std::string>(126, "KEY_BLOCKS_USED"),
    std::make_pair<int, std::string>(127, "KEY_BLOCKS_UNUSED"),
#endif
    // InnoDB每秒钟的读取和写入次数 A
    std::make_pair<int, std::string>(116, "INNODB_DATA_READS"),
    std::make_pair<int, std::string>(117, "INNODB_DATA_WRITES"),

    //执行语句时在硬盘上自动创建的临时表的数量 A
    std::make_pair<int, std::string>(125, "CREATED_TMP_DISK_TABLES"),

    //MyISAM平均每秒的读写次数 A
    std::make_pair<int, std::string>(121, "KEY_READ_REQUESTS"),
    std::make_pair<int, std::string>(122, "KEY_WRITE_REQUESTS"),
    std::make_pair<int, std::string>(123, "KEY_READS"),
    std::make_pair<int, std::string>(124, "KEY_WRITES"),
#if 0
    //数据库每秒语句执行次数的监控，所涉及到的语句包括Insert、Delete、Insert_Select、Replace、Replace_Select、Select六种 X
    std::make_pair<int, std::string>(135, "UPTIME"),
    std::make_pair<int, std::string>(136, "COM_INSERT"),
    std::make_pair<int, std::string>(137, "COM_SELECT"),
    std::make_pair<int, std::string>(138, "COM_DELETE"),
    std::make_pair<int, std::string>(139, "COM_REPLACE"),
    std::make_pair<int, std::string>(140, "COM_REPLACE_SELECT"),
    std::make_pair<int, std::string>(141, "COM_INSERT_SELECT"),
#endif

    //InnoDB每秒钟操作数据行数的统计，根据操作的不同，分为平均每秒向日志文件的物理写次数、平均每秒从InnoDB表“删除/更新/读取/插入”的行数等五种类型 A
    std::make_pair<int, std::string>(132, "INNODB_ROWS_DELETED"),
    std::make_pair<int, std::string>(133, "INNODB_ROWS_UPDATED"),
    std::make_pair<int, std::string>(135, "INNODB_ROWS_INSERTED"),
    std::make_pair<int, std::string>(134, "INNODB_ROWS_READ")
};

OceanNmsMySql::OceanNmsMySql(){
   MySQL::Connector::registerConnector();
   Application::instance().logger().information("registerConnector");
}

OceanNmsMySql::OceanNmsMySql(const std::string szServer, const std::string szUID, const std::string szPWD, const std::string szPort)
:m_strServer{szServer}, 
m_strUID{szUID}, 
m_strPWD{szPWD}, 
m_strPort{szPort}
{
    MySQL::Connector::registerConnector();
    Application::instance().logger().information("registerConnector");
}

OceanNmsMySql::~OceanNmsMySql()
{
    MySQL::Connector::unregisterConnector();
    Application::instance().logger().information("unregisterConnector");
}

void OceanNmsMySql::ConnectDB()
{
    try
    {
        std::string dbConnString = 
        "host=" + m_strServer + ";port=" + m_strPort + ";"
        "user=" + m_strUID + ";password=" + m_strPWD + ";"
        "db=nms;compress=true;auto-reconnect=true";

        Application::instance().logger().information("dbConnString = " + dbConnString);
        m_pSession = new Session(MySQL::Connector::KEY, dbConnString);
        *m_pSession << "set global show_compatibility_56=on", now;
    }
   	catch (ConnectionFailedException& ex)
	{
        Application::instance().logger().error(ex.displayText());
	}
}

int OceanNmsMySql::get_level(int warn_id, const float value)
{
    /* 获取告警级别 */
    size_t level = 0;
    std::string sql = Application::instance().config().getString("th_sql");

    std::string json;
    *m_pSession << sql, into(json), use(warn_id), now;

    JSON::Parser parser;
    Dynamic::Var result;

    result = parser.parse(json);
    JSON::Array::Ptr pArry = result.extract<Poco::JSON::Array::Ptr>();
    int value_l = pArry->getObject(0)->get("value").convert<int>();
    int value_m = pArry->getObject(1)->get("value").convert<int>();
    int value_h = pArry->getObject(2)->get("value").convert<int>();

    if(value > value_h) 
    level = pArry->getObject(2)->get("level").convert<int>();
    else if(value > value_m)
    level = pArry->getObject(1)->get("level").convert<int>();
    else if(value > value_l) 
    level = pArry->getObject(0)->get("level").convert<int>();

    Application::instance().logger().information("json = " + json);
    Application::instance().logger().information("value_l = " + std::to_string(value_l));
    Application::instance().logger().information("value_m = " + std::to_string(value_m));
    Application::instance().logger().information("value_h = " + std::to_string(value_h));

    return level;
}

std::string OceanNmsMySql::get_type(const int &warn_id)
{
    std::string  type;
    if(warn_id >= 101 && warn_id <= 104)
        type = Application::instance().config().getString("host_type");
    else
        type = Application::instance().config().getString("mysql_type");
    return std::move(type);
}

std::string OceanNmsMySql::get_para(const std::string& ip, const float & value)
{
    std::string  para = Application::instance().config().getString("para");
    /* json 字符串 */
    char para_json[1024];
    snprintf(para_json, 1024, para.c_str(), ip.c_str(), value);
    std::string para_ = std::string(para_json);
    Application::instance().logger().information("para_json = "  + para_ + ", value = " + std::to_string(value));

    return std::move(para_);

}

int OceanNmsMySql::get_dev_id(std::string ip)
{
    /* 获取设备ID */
    int  dev_id=0;
    std::string  dev_id_sql = Application::instance().config().getString("dev_id_sql");
    *m_pSession << dev_id_sql, into(dev_id), use(ip), now;
    Application::instance().logger().information("dev_id_sql = " + dev_id_sql + ", dev_id is " + std::to_string(dev_id));

    return dev_id;
}

std::string OceanNmsMySql::get_locat(const int& dev_id)
{
    std::string  locat = Application::instance().config().getString("locat");
    /* json 字符串 */
    char locat_json[1024];
    snprintf(locat_json, 1024, locat.c_str(), dev_id);
    std::string locat_ = std::string(locat_json);
    Application::instance().logger().information("locat_json = " + locat_);

    return std::move(locat_);
}

void OceanNmsMySql::get_warn_name(std::string ip, int warn_id, const float& value)
{
    /* 获取设备warn_name */
    std::string  warn_name;
    std::string  dev_warn_name_sql = Application::instance().config().getString("dev_warn_name_sql");
    *m_pSession << dev_warn_name_sql, into(warn_name), use(warn_id), now;
  
    /* 获取 type */ 
    std::string type = get_type(warn_id);

    /* 获取level */
    int  level = get_level(warn_id, value);
    
    if(level == 0)
        return;
    /* 获取status */
    static std::string  status = Application::instance().config().getString("status");

    /* 获取para_ */
    std::string para_ = get_para(ip, value);

    /* 获取locat */
    int dev_id = get_dev_id(ip);
    std::string  locat_ = get_locat(dev_id);

    /* 获取detail */
    char detail_[1024];
    snprintf(detail_, 1024, (warn_name + "%0.2f" + Application::instance().config().getString("detail")).c_str(), value);
    std::string detail = std::string(detail_);

    /* 获取时间 */
    Poco::Timestamp  now_time;
    time_t tt = now_time.epochTime();

    /* 获取restore */
    static std::string  restore= Application::instance().config().getString("restore");
    /* 获取reason */
    std::string reason = warn_name + Application::instance().config().getString("reason");
    /* 获取advice */
    static std::string  advice = Application::instance().config().getString("advice");
    /* 获取comment */
    static std::string  comment = Application::instance().config().getString("comment");
    /* 插入语句 */
    static std::string  host_sql = Application::instance().config().getString("host_sql");

    Application::instance().logger().information("warn_id = " + std::to_string(warn_id) + ", warn_name = " + warn_name + ", type = " + type + ", level = " + std::to_string(level) + ", status = " + status + ", para = " + para_ + ", soure = " + ip + ", locat = " + locat_ + ", detail = " + detail + ", tt = " + std::to_string(tt) + /*", restore = " + restore + */", reason = " + reason + ", advice = " + advice + ", comment = " + comment);

    *m_pSession << host_sql, 
    use(warn_id), 
    use(warn_name), 
    use(type), 
    use(level), 
    use(status), 
    use(para_), 
    use(ip), 
    use(locat_), 
    use(detail), 
    use(tt), 
//    use(restore), 
    use(reason), 
    use(advice), 
    use(comment), 
    now;
}

void OceanNmsMySql::Matchine()
{
    std::string  ip = "172.20.48.225";
    for(int i = 101; i < 138; i++)
    if(i != 105)  
    {
        std::cout << "==================== " << i << std::endl;
        get_warn_name(ip, i, rand()%100); 
        std::cout << "==================== " << i << std::endl;
    }
    
    test1(ip);
}

void OceanNmsMySql::test()
{
    std::string sql = Application::instance().config().getString("mysql_dev_sql");

    char sql_str[1024];

    //磁盘空间/数据库占用空间，单位MB
    int m_nDBDataSize;
    std::string mysql_disk_sql = Application::instance().config().getString("mysql_disk_sql");
    std::string mysql_disk_id = Application::instance().config().getString("mysql_disk_id");
    *m_pSession << mysql_disk_sql, into(m_nDBDataSize), now;
    get_warn_name(m_strServer, std::stoi(mysql_disk_id), m_nDBDataSize);
    int value;
    for(auto &val : YGH) 
    {
        bzero(sql_str, 1024);
        snprintf(sql_str, 1024, sql.c_str(), val.second.c_str());
        *m_pSession << sql_str, into(value), now;
        get_warn_name(m_strServer, val.first, value); 
    } 
}

void OceanNmsMySql::test1(const std::string& ip)
{
    std::string snmp_ip = Application::instance().config().getString("snmp_ip");
    std::string snmp_port = Application::instance().config().getString("snmp_port");
    std::string snmp_r_community = Application::instance().config().getString("snmp_r_community");
    std::string snmp_w_community = Application::instance().config().getString("snmp_w_community");
    std::string snmp_timeout = Application::instance().config().getString("snmp_timeout");

    while(1)   
    {
        sleep(5);
 
        MsgGetHostFileSystemListReq a;
        a.set_host_res_id(10);

        SnmpInfo *pSnmp = a.mutable_snmp_info();
        SnmpBasePara *pSnmpBasePara = pSnmp->mutable_base_para();
        pSnmpBasePara->set_ip_addr(snmp_ip);
        pSnmpBasePara->set_port(std::atoi(snmp_port.c_str()));
        pSnmpBasePara->set_read_community(snmp_r_community);
        pSnmpBasePara->set_write_community(snmp_w_community);
        pSnmpBasePara->set_version(SNMP_V2);

        pSnmp->set_timeout(std::atoi(snmp_timeout.c_str()));            

        HOSTPERF hostperf;
        snmp_collect(hostperf, &a, pSnmpBasePara, version2c);

        int   pro_load = 0;
        for(auto val : hostperf.vecprocessor_load)
        {
            pro_load += val;
        }

        float phy_mem = 0;
        if(hostperf.nstorage_ram_size != 0)
        {
            phy_mem = (float)hostperf.nstorage_ram_used / hostperf.nstorage_ram_size * 100;
        }

        float vir_mem = 0;
        if(hostperf.nstorage_virtual_memory_size != 0)
        {
            vir_mem = (float)hostperf.nstorage_virtual_memory_used /hostperf.nstorage_virtual_memory_size * 100;
        }

        float  nstorage_sum = 0;
        float  nstorage_used = 0;
        for(auto val : hostperf.vecstorage_fixed_disk)
        {
            if(val.nstorage_size != 0)
            {
                nstorage_used += (float)val.nstorage_used;
                nstorage_sum  += (float)val.nstorage_size;
            }
        }

        float  nstorage_rate =  nstorage_used / nstorage_sum * 100;
        printf("=======disk_rate = %f\n", nstorage_rate);

        printf("=======pro_load = %d, phy_mem = %f, vir_mem = %f, nstorage_rate = %f\n", pro_load, phy_mem, vir_mem, nstorage_rate);
        get_warn_name(ip, HOST_CPU_ID, pro_load);
        get_warn_name(ip, HOST_MEM_ID, phy_mem);
        get_warn_name(ip, HOST_VMEM_ID, vir_mem);
        get_warn_name(ip, HOST_DISK_ID, nstorage_rate);
    }
}
