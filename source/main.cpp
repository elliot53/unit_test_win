#include "entry.hpp"

int main(int argc, char* argv[])
{
    std::cerr << "unit test win begin..." << std::endl;
    zjy::Message msg(argc, argv);

    std::map<std::string, std::function<int(zjy::Message&)>> cmd_map = 
    {
        {"--network-unit", zjy::network_unit}
    };

    auto it = cmd_map.find(msg.msg_pool.at(1));
    if (it != cmd_map.end())
    {   
        it->second(msg);
    }
    else 
    {
        std::cerr << "invalid cmd: " << msg.msg_pool.at(1) << "\n";
    }

    std::cerr << "unit test win end..." << std::endl;
    return 1;
}