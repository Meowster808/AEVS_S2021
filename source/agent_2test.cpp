// Example of an agent making a request to another agent
// agent 002 makes request to 002 upon activation

#include "support/configCosmos.h"
#include "agent/agentclass.h"
#include "support/stringlib.h"

#include <iostream>
#include <string>



// The request function prototype
int32_t hello_agent_002_request_function(string &request, string &response, Agent *cdata);

/// number of requests that have been run since restarting agent
static uint64_t request_counter = 0;

/// ensure only one agent class instance per process
string node_name = "sat_001";
string agent_name = "agent_2test";
string node_agent_name = "["+node_name+":"+agent_name+"]";
static Agent* agent;

/// Program to demonstrate inter-communication between agents
int main(int argc, char **argv)
{
    // construct agent
    cout << node_agent_name <<" starting..."<<endl;
    agent = new Agent(node_name, agent_name, 1.);


    if(agent->last_error() < 0) {
        cout<<"error: unable to start "<<node_agent_name<<" ("<<agent->last_error()<<") "<<cosmos_error_string(agent->last_error())<<endl;
        exit(1);
    } else {
        cout << ""<<node_agent_name<<" started."<<endl;
    }



    // add custom request functions for this agent
    agent->add_request("any_body_out_there", hello_agent_002_request_function, "a request to respond with 'hello'");



    // Start executing the agent
    while(agent->running()) {
        cout<<node_agent_name<<" running..."<<endl;

        // Sleep for 4 sec
        COSMOS_SLEEP(4.);
        // Initiate request to agent_001
        // name of agent target for request
        string agent_target = "agent_1test";


 //       /*
        string req = "Hello Daryll";
        cout<<"  request  = <"<<req<<">"<<endl;
        string res;
        agent->send_request(agent->find_agent(node_name, agent_target, 2.), req, res, 2.);
        cout<<"  response = <"<<res<<">"<<endl;


        req.clear();
        req = "test1";
        cout<<"  request  = <"<<req<<">"<<endl;
        res.clear();
        agent->send_request(agent->find_agent(node_name, agent_target, 2.), req, res, 2.);
        cout<<"  response = <"<<res<<">"<<endl;

        req.clear();
        req = "test2";
        cout<<"  request  = <"<<req<<">"<<endl;
        res.clear();
        agent->send_request(agent->find_agent(node_name, agent_target, 2.), req, res, 2.);
        cout<<"  response = <"<<res<<">"<<endl;

 //       */
          /*
        string req = "get_value \"Longest Ever UTC\" \"Short UTC\"";
        cout<<"  request  = <"<<req<<">"<<endl;
        string res;
        agent->send_request(agent->find_agent(node_name, agent_target, 2.), req, res, 2.);
        cout<<"  response = <"<<res<<">"<<endl;

        req.clear();
        req = "set_value {\"Longest Ever UTC\": 215},{\"user[0].tool\": \"Super Tool!\"}";
        cout<<"  request  = <"<<req<<">"<<endl;
        res.clear();
        agent->send_request(agent->find_agent(node_name, agent_target, 2.), req, res, 2.);
        cout<<"  response = <"<<res<<">"<<endl;

        req.clear();
        req = "get_value \"user\"";
        cout<<"  request  = <"<<req<<">"<<endl;
        res.clear();
        agent->send_request(agent->find_agent(node_name, agent_target, 2.), req, res, 2.);
        cout<<"  response = <"<<res<<">"<<endl;
          */



    }
    return 0;
}

//!
//! \brief The function to handle agent_001's request.
//! \param The response to send back to agent_001.
//! \return int
//!
// JIMNOTE:  Why is Agent part of request function signature?
int32_t hello_agent_002_request_function(string & request, string &response, Agent *a)
{
    // Send response back to agent_001
    response = "hello " + std::to_string(request_counter);

    // agent is set to this pointer?
    //cout << "[" << node_name << ":" << agent_name <<"] received a request from ["<<a->nodeName<<":"<<a->agentName<<"]! Its response is: " << response << endl;
    return 0;
}
