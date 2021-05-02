#include "support/configCosmos.h"
#include "support/elapsedtime.h"
#include "support/timeutils.h"
#include "agent/agentclass.h"

#include <iostream>
#include <string>



// The request function prototype
int32_t sample_agent_request_function(string &request, string &response, Agent *cdata);
static uint64_t request_counter = 10000;


/// ensure the Agent constructor creates only one instance per process
static Agent *agent;
string node_name = "sat_001";
string agent_name = "agent_1test";
string node_agent_name = "["+node_name+":"+agent_name+"]";

int main(int argc, char **argv)
{
    // construct agent
    cout << node_agent_name << " starting..."<<endl;
    agent = new Agent(node_name, agent_name, 1.);

    // exit with error if unable to start agent

    if(agent->last_error() < 0) {
        cout<<"error: unable to start "<<node_agent_name<<" ("<<agent->last_error()<<") "<<cosmos_error_string(agent->last_error())<<endl;
        exit(1);

    } else {
        cout << node_agent_name << " started."<<endl;
    }

    // add custom request functions for this agent
    string request_name = "identify_yourself";
    agent->add_request(request_name, sample_agent_request_function, "\n\t\trequest to support the reporting of identification");

    // try to locate a specific agent (agent_002)
    string agent_target = "agent_2test"; // The name of the agent this agent will send requests to
    beatstruc agent_target_heartbeat = agent->find_agent(node_name, agent_target, 2.);
    //cout<<"["<<node_name<<":"<<agent_name<<"] looking for ["<<node_name<<":"<<agent_target<<"]..."<<endl;

    if(agent->debug_level>1)	{
        cout<<"A agent "<<agent_target<<" beatstruc:"<<endl;
        cout<<agent_target_heartbeat;
    }

    string response; // Variable to store agent_002's response
/*
    //Start executing the agent
    agent->cinfo->add_name("Short UTC", &agent->cinfo->node.loc.utc, "double");
    //agent->cinfo->add_name("Longest Ever UTC", &agent->cinfo->node.loc.utc, "double");
    //agent->cinfo->set_value<double>("Short UTC", 213.0);
*/

    while (agent->running()) {

        cout<<"["<<node_name<<":"<<agent_name<<"] running..."<<endl;
        // Sleep for 5 sec

        COSMOS_SLEEP(5.);
    }
    return 0;
}



int32_t sample_agent_request_function(string & request, string &response, Agent *)
{
    // Send response back to agent_002

    response = "I am the one they call [sat_001:agent_001]";

/*      JIMNOTE: there is a actually a bug with the string request variable supplied...
 *      it is not passed properly to the user's request function after multiple different
 *      requests have been made.  the request is parsed properly, i.e. this function is still
 *      called, but the request string contains overflow characters from previous requests
 *      beyond the null character.  somewhere a string.resize() call is missing.
 *
 *      HACKY FIX: mixing char[] within a string only prints correctly if cast as c_str(),
 *      so do that for now.
 */
    cout << "[" << node_name << ":" << agent_name << "]"<<" received <"<<request.c_str()<<"> request!"<<endl;
    cout << "[" << node_name << ":" << agent_name << "] transmit <"<<request.c_str()<<"> response:\n    TX: \"" << response << "\" ("<<response.size()<<" bytes)"<<endl;

    // Increment counter of how many requests were run
    request_counter--;

    return 0;
}
