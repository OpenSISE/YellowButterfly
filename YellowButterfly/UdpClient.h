#pragma once
class UdpClient
{
public:
	SOCKET* cSocket, *iSocket;
	sockaddr_in Localaddr, Remoteaddr, addr4999, addr3848;
	int AddrSize = sizeof(Remoteaddr);
	int n = sizeof(Remoteaddr), Pack_len = 0, TempLen = 0;
	char buf[1024], RecvBuf[1024], iRecvBuf[1024], rMsg[1024];
	char ServerIp[16];
	char *pBuf;
public:
	UdpClient(SOCKET*);
	~UdpClient();
	void CreateClient();
	void CloseClient();
	BOOL BindPort();
	void BasListend();
	BOOL InitInfoSock(SOCKET*);
	void Initialize();
	CString RecvData();
	void SendLoginPack(UCHAR mac[6], char username[32], char passwd[32], char localIp[16], char service[32], unsigned char ipType, char version[16]);
	void SendLogoutPack();  //char session[128], char localip[16], UCHAR mac[6], unsigned long keepId
	void UnpackLogin(char *pack, int len);
	void UnpackLogout(char *pack, int len);
	void UnpackHeart(char *pack, int len);
	void UnpackBreak(char *pack, int len);
	void SendHeartPack();
	void Listen();
	void Listen4999();
	void MakeHeartPack(unsigned int);
	void CleanData();
	void SetServer(CString);
};


void HeadPack(char *ptr, int headtype, int total_len);
void AddPack(char **pack, int packtype, int Contentlen, void *PackData, int &totallen);
BOOL  encrypt(unsigned char *data, int datalen);
BOOL  decrypt(unsigned char *data, int datalen);
void SendLoginPack(UCHAR mac[6], char username[32], char passwd[32], char localIp[16], char service[32], unsigned char ipType, char version[16]);
void SendFreeData(int socket, char * buf, int len, char * ip, int port);
BOOL CheckHeadPack(char *pack, int len);
BOOL SkipPack(char **pack, int &Templen);