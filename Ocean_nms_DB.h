#ifndef __ABCDE__
#define __ABCDE__
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/Utility.h"
#include "Ocean_nms_snmp.h"
#include <cstdio>

#include <iostream>
#include <string>
#include <vector>
enum  warn_id
{
    HOST_CPU_ID =101, //CPU负载
    HOST_MEM_ID =102, //物理内存占用率
    HOST_VMEM_ID =103, //虚拟内存占用率
    HOST_DISK_ID =104, //硬盘占用率

    MYSQL_DISK_ID =106 //mysql数据库占用磁盘空间
//    MYSQL_ =107, //mysql数据库当前总连接数
//    MYSQL_ =108, //mysql数据库平均每秒钟的输入流量
//    MYSQL_ =109, //mysql数据库平均每秒钟的输出流量

//    MYSQL_ =110, //mysql MyISAM引擎每秒SQL语句执行次数
//    MYSQL_ =111, //mysql InnoDB引擎每秒SQL语句执行次数
//    MYSQL_ =112, //mysql平均每秒SQL语句事务处理数
//    MYSQL_ =113, //mysql InnoDB缓冲池的读命中率
//    MYSQL_ =114, //mysql InnoDB缓冲池的利用率
//    MYSQL_ =115, //mysql InnoDB缓冲池脏块的百分率

//    MYSQL_ =116, //mysql InnoDB每秒钟的读取次数
//    MYSQL_ =117, //mysql InnoDB每秒钟的写入次数

//    MYSQL_ =118, //mysql MyISAM缓冲池的读命中率
//    MYSQL_ =119, //mysql MyISAM缓冲池的写命中率
//    MYSQL_ =120, //mysql MyISAM缓冲池的利用率

//    MYSQL_ =121, //mysql MyISAM平均每秒钟从缓冲池中的读取次数
//    MYSQL_ =122, //mysql MyISAM平均每秒钟从缓冲池中的写入次数
//    MYSQL_ =123, //mysql MyISAM平均每秒钟从硬盘上读取的次数
//    MYSQL_ =124, //mysql MyISAM平均每秒钟从硬盘上写入的次数

//    MYSQL_ =125, //mysql执行语句时在硬盘上自动创建的临时表的数量

//    MYSQL_ =126, //mysql数据库每秒Insert语句执行次数
//    MYSQL_ =127, //mysql数据库每秒Delete语句执行次数
//    MYSQL_ =128, //mysql数据库每秒Insert_Select语句执行次数
//    MYSQL_ =129, //mysql数据库每秒Replace语句执行次数
//    MYSQL_ =130, //mysql数据库每秒Replace_Select语句执行次数
//    MYSQL_ =131, //mysql数据库每秒Select语句执行次数

//    MYSQL_ =132, //mysql平均每秒从InnoDB表删除的行数
//    MYSQL_ =133, //mysql平均每秒从InnoDB表更新的行数
//    MYSQL_ =134, //mysql平均每秒从InnoDB表读取的行数
//    MYSQL_ =135, //mysql平均每秒从InnoDB表插入的行数

//    MYSQL_ =136, //mysql数据库cpu占用率
//    MYSQL_ =137, //mysql数据库内存占用率
};

class OceanNmsMySql
{
public: 
    OceanNmsMySql();
    OceanNmsMySql(const std::string szServer, const std::string szUID, const std::string szPWD, const std::string szPort);
    ~OceanNmsMySql();

    void ConnectDB();
    void Matchine();
private:

    int get_level(int warn_id, const float value );
    std::string get_type(const int &warn_id);
    std::string get_para(const std::string& ip, const float & value);
    int get_dev_id(std::string ip);
    std::string get_locat(const int& dev_id);
    void get_warn_name(std::string ip, int warn_id, const float& value);
    void test();
    void test1(const std::string& ip);

    // 数据库服务地址（IP或者主机名）
    std::string m_strServer{"127.0.0.1"};
    // 登录用户名
    std::string m_strUID{"root"};
    // 登录密码
    std::string m_strPWD{"123456"};
    // 数据库服务端口
    std::string m_strPort{"3306"};
    // 数据库连接对象
    Poco::SharedPtr<Poco::Data::Session> m_pSession;
};
#endif
