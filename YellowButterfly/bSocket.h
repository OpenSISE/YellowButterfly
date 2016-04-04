#pragma once 

/*
*define some Amtium's const data
*/


////////////////////////////////
extern const int Pack_Head_Len = 18;
////////////////////////////////
extern const unsigned int Type_UserName = 0x01;        //username
extern const unsigned int Type_Password = 0x02;        //password
extern const unsigned int Type_LoginFlag = 0x03;
extern const unsigned int Type_Mac = 0x07;             //mac
extern const unsigned int Type_Random = 0x08;           //Random number?
extern const unsigned int Type_Ip = 0x09;              //user localhost ip
extern const unsigned int Type_Service = 0x0A;         //Connect Service?
extern const unsigned int Type_Server_Msg = 0x0B;
extern const unsigned int Type_IpType = 0x0E;          //Is dhcp?
extern const unsigned int Type_ClientVersion = 0x1F;   //Client Version
extern const unsigned int Type_Identity = 0x14;        //Keep id?
extern const unsigned int Type_Break_Reason = 0x24;
////////////////////////////////// what the fuck?
extern const unsigned int Type_Block1 = 0x2A;
extern const unsigned int Type_Block2 = 0x2B;
extern const unsigned int Type_Block3 = 0x2C;
extern const unsigned int Type_Block4 = 0x2D;
extern const unsigned int Type_Block5 = 0x2E;
extern const unsigned int Type_Block6 = 0x2F;
/////////////////////////////////
extern const unsigned int Action_Login = 0x01;	        // Login
extern const unsigned int Action_Login_Reply = 0x02;
extern const unsigned int Action_HeartBeat = 0x03;	        // Heart
extern const unsigned int Action_Heart_Reply = 0x04;	        // Heart_reply
extern const unsigned int Action_Logout = 0x05;	        // logout
extern const unsigned int Action_Logout_Reply = 0x06;      //logout pack reply
extern const unsigned int Action_Breaked = 0x09;           //disconnect
extern const unsigned int Action_Confirm = 0x0A;
extern const unsigned int Action_Confirm_Replt = 0x0B;
////////////////////////////////

extern const unsigned int Action_ReLogin = 0x401;          //Auto Relogin
//extern unsigned char RandomNum[64] = {0};


