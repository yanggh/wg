#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/Application.h"
#include "Ocean_nms_DB.h"

#include <iostream>
using namespace Poco::Util;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::Util::Application;

class CMpfTestServer: public ServerApplication
{
public:
    CMpfTestServer()
    {
    }

    ~CMpfTestServer()
    {
    }

protected:
    void initialize(Application& self)
    {
        ServerApplication::initialize(self);
        logger().information("initialize");
    }

    void uninitialize()
    {
        logger().information("uninitialize");
        ServerApplication::uninitialize();
    }

    void defineOptions(OptionSet& options)
    {
        logger().information("defineOptions");
        ServerApplication::defineOptions(options);

        options.addOption(
            Option("help", "h", "display help information on command line arguments")
            .required(false)
            .repeatable(false)
            .callback(OptionCallback<CMpfTestServer>(this, &CMpfTestServer::handleHelp)));

        options.addOption(
            Option("config-file", "f", "load configuration data from a file")
                .required(false)
                .repeatable(true)
                .argument("file")
                .callback(OptionCallback<CMpfTestServer>(this, &CMpfTestServer::handleConfig)));
    }

    void handleHelp(const std::string& name, const std::string& value)
    {
        logger().information("handleHelp");
        _helpRequested = true;
        displayHelp();
        stopOptionsProcessing();
    }
    
    void handleConfig(const std::string& name, const std::string& value)
    {
        logger().information("handleConfig");
        loadConfiguration(value);

       std::string szServer = config().getString("Server", "127.0.0.1");
       std::string szUID = config().getString("UID", "root");
       std::string szPWD = config().getString("PWD", "123456");
       std::string szPort = config().getString("Port", "3306");

       msql = new OceanNmsMySql(szServer, szUID,  szPWD, szPort);
    }

    void displayHelp()
    {
        HelpFormatter helpFormatter(options());
        helpFormatter.format(std::cout);
    }

    int main(const std::vector<std::string>& args)
    {
        if(!msql)
        {
            msql = new OceanNmsMySql();
        }
        msql->ConnectDB();
        msql->Matchine();
        return 0;
    }
private:
    bool _helpRequested;
    Poco::SharedPtr<OceanNmsMySql> msql;
};

POCO_SERVER_MAIN(CMpfTestServer)
