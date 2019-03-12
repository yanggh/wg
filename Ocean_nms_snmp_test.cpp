#include "Ocean_nms_snmp.h"
#include <cstdio>

int main(int argc, char** argv)
{
    unsigned char i = 0;
    unsigned char pos = 0;
    while(1)   
    {
        getchar();
 
        MsgGetHostFileSystemListReq a;
        a.set_host_res_id(10);

        SnmpInfo *pSnmp = a.mutable_snmp_info();
        SnmpBasePara *pSnmpBasePara = pSnmp->mutable_base_para();
        pos = i % (argc - 1) + 1;
        i++;
        pSnmpBasePara->set_ip_addr(argv[pos]);
        pSnmpBasePara->set_port(161);
        pSnmpBasePara->set_read_community("public");
        pSnmpBasePara->set_write_community("public");
        pSnmpBasePara->set_version(SNMP_V2);

        pSnmp->set_timeout(30);            

        HOSTPERF hostperf;
        snmp_collect(hostperf, &a, pSnmpBasePara, version2c);

//        hostperf_database(10, string(argv[pos]), hostperf);

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

        vector<float> disk_rate;
        for(auto val : hostperf.vecstorage_fixed_disk)
        {
            float rate = 0;
            if(val.nstorage_size != 0)
            {
                rate = (float)val.nstorage_used / val.nstorage_size * 100;
                disk_rate.push_back(rate);
            }
        }

        for(auto &val : disk_rate)
            printf("=======disk_rate = %f\n", val);

        printf("=======pro_load = %d, phy_mem = %f, vir_mem = %f\n", pro_load, phy_mem, vir_mem);
    }
    return 0; 
}
