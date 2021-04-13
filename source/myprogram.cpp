#include "agent/agentclass.h"
#include "support/configCosmos.h"
#include "agent/agentclass.h"
#include "device/serial/serialclass.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    Agent *agent;
    string nodename = "node_name_here";
    string agentname = "agent_name_here";

    agent = new Agent(nodename, agentname);
    string agent_name_here_soh = "{\"data_name_here\"}";
    agent->set_sohstring(agent_name_here_soh.c_str());

    while(agent->running())
    {
        std::cout << "Hello World!";
        return 0;
    }
}
