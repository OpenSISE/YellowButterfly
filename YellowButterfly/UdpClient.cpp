#include "stdafx.h"
#include "UdpClient.h"
#include "bSocket.h"
#include "YellowButterfly.h"
#include "md5.h"
#include "ShowTip.h"
//////////////////This is a ClientSocket class////
unsigned char RandomNum[64] = { 0 };
unsigned char SessionId[64] = { 0 };
unsigned long HeartRandom = 0x1000000;
UdpClient::UdpClient(SOCKET *socket)
{
	memset(this->RecvBuf, 0, sizeof(this->RecvBuf));
	memset(this->iRecvBuf, 0, sizeof(this->iRecvBuf));
	this->cSocket = socket;
	this->CreateClient();
}

UdpClient::~UdpClient()
{
	::closesocket(*(this->cSocket));
	::closesocket(*(this->iSocket));
}

void UdpClient::Initialize()
{
	SOCKET SearchSock = ::socket(AF_INET, SOCK_DGRAM, NULL);
	char buf[100] = {0};
	strcpy(buf, "info sock ini");
	::SendFreeData(SearchSock, buf, strlen(buf), "1.1.1.8", 3850);
}

void UdpClient::CreateClient()
{
	*(this->cSocket) = ::socket(AF_INET, SOCK_DGRAM, NULL);
	Localaddr.sin_family = AF_INET;
	Localaddr.sin_port = htons(3848);
	Localaddr.sin_addr.s_addr = ADDR_ANY;


}

void UdpClient::SetServer(CString serverIp)
{
	memset(this->ServerIp, 0, sizeof(this->ServerIp));
	memcpy(this->ServerIp,serverIp.GetBuffer(), serverIp.GetLength());
}

void UdpClient::CloseClient()
{
	//::closesocket(*(this->cSocket));
	//::closesocket(*(this->iSocket));
}

BOOL UdpClient::BindPort()
{
	if (::bind(*(this->cSocket), (sockaddr*)&(this->Localaddr), sizeof(this->Localaddr)) == SOCKET_ERROR)
	{
		return FALSE;
	}
	else{
		return TRUE;
	}
}

BOOL UdpClient::InitInfoSock(SOCKET *isocket)
{
	this->iSocket = isocket;
	*(this->iSocket) = ::socket(AF_INET, SOCK_DGRAM, NULL);
	addr4999.sin_family = AF_INET;
	addr4999.sin_port = htons(4999);
	addr4999.sin_addr.s_addr = ADDR_ANY;
	if (::bind(*(this->iSocket), (sockaddr*)&(this->addr4999), sizeof(this->addr4999)) == SOCKET_ERROR)
	{
		return FALSE;
	}
	else{
		return TRUE;
	}
}

CString UdpClient::RecvData()
{
	CString Msg;
	if (::recvfrom(*(this->cSocket), this->RecvBuf, sizeof(this->RecvBuf), 0, (sockaddr*)&(this->Remoteaddr), &this->AddrSize) > 0)
	{
		if (strcmp(inet_ntoa(this->Remoteaddr.sin_addr), "172.16.1.180") != 0){ return "Hi Kid!"; }
		Msg.Format("%s", this->RecvBuf);

	}
	return Msg;
}



//void UdpClient::SetListenFlas(BOOL flag)
//{
//	//this->ListenFlag = FALSE;
//}

void UdpClient::Listen()
{
	  BOOL IpLegal = FALSE;
	  memset(this->RecvBuf, 0, sizeof(this->RecvBuf));
	  int PackLen = ::recvfrom(*(this->cSocket), this->RecvBuf, sizeof(this->RecvBuf), 0, (sockaddr*)&(this->Remoteaddr), &this->AddrSize);
	  if (strcmp(inet_ntoa(this->Remoteaddr.sin_addr), this->ServerIp) == 0)
	  {
		  IpLegal = TRUE;
		  IsConnectingFlag = TRUE;
	  }
	  if (PackLen> 18 && IpLegal)
	  {
	    this->CleanData();
		char RecvRandom[1024] = { 0 };
		decrypt((unsigned char *)RecvBuf, PackLen);
		unsigned char temp,* pStr;
		pStr = (unsigned char *)RecvBuf;
		int NowLen = 0;
		temp = pStr[0];
		switch (temp)
		{
		case Action_Login_Reply:
			this->UnpackLogin(RecvBuf, PackLen);
			return;
		case Action_Heart_Reply:
			this->UnpackHeart(RecvBuf, PackLen);
			return;
		case Action_Logout_Reply:
			this->UnpackLogout(RecvBuf, PackLen);
			return;
		default:
			return;
		}
	  }
	  return;	
}
void UdpClient::Listen4999()
{
	BOOL iIpLegal = FALSE;
	memset(this->iRecvBuf, 0, sizeof(this->iRecvBuf));
	int iPackLen = ::recvfrom(*(this->iSocket), this->iRecvBuf, sizeof(this->iRecvBuf), 0, (sockaddr*)&(this->Remoteaddr), &this->AddrSize);
	if (strcmp(inet_ntoa(this->Remoteaddr.sin_addr), this->ServerIp) == 0)
	{
		iIpLegal = TRUE;
		//IsConnectingFlag = TRUE;
	}
	if (iPackLen>18 && iIpLegal)
	{
		decrypt((unsigned char *)iRecvBuf, strlen(iRecvBuf));
		unsigned char temp, *pStr;
		pStr = (unsigned char *)iRecvBuf;
		temp = pStr[0];
		switch (temp)
		{
		case Action_Breaked:
			UnpackBreak(iRecvBuf, iPackLen);return;
		}
	}
}
void UdpClient::UnpackLogin(char *pack, int len)    //char session[128],char localip[16],UCHAR mac[6],unsigned long keepId
{
	memset(rMsg,0,sizeof(rMsg));
	unsigned char tmpe;char *pStr;
	pStr = pack;
	int NowLen = 0;
	::CheckHeadPack(pack,len);
	this->TempLen = len;
	pStr += Pack_Head_Len;
	this->TempLen -= Pack_Head_Len;
	CString ss;
	while (TempLen > 3)
	{
	tmpe = pStr[0];
	switch (tmpe)
	 {
	case  Type_LoginFlag:
		LoginReplyFlag = *(pStr+2);
		SkipPack(&pStr, TempLen);
		break;
	case Type_Random:
		NowLen = *(pStr + 1);
		memcpy(RandomNum, pStr + 2, NowLen);
		pStr += (NowLen + 2);
		TempLen -= (NowLen + 2);
		break;
	 case Type_Server_Msg: //reply
		 NowLen = (UCHAR)*(pStr + 1);
		 memcpy(rMsg, pStr + 2, NowLen);
		 pStr += (NowLen + 2);
		 TempLen -= (NowLen + 2);
		 break;
	 case  Type_Identity:
		 NowLen = (UCHAR)*(pStr + 1);
		 memcpy(SessionId, pStr + 2, NowLen);
		 pStr += (NowLen + 2);
		 TempLen -= (NowLen + 2);	 
		 break;
	 default:
		 SkipPack(&pStr, TempLen);
		break;
	 }
	}
	HWND hwnd = ::FindWindow("YellowButterfly",NULL);
	PostMessage(hwnd, WM_NOTIFYMSG, (WPARAM)rMsg, NULL);
}

void UdpClient::UnpackBreak(char *pack, int len)
{
	BOOL BreakLegal = FALSE,Reasonlegal = FALSE;
	unsigned char temp; char *pStr,reason=0;
	pStr = pack;
	int NowLen = 0,ReasonFlags=0;
	::CheckHeadPack(pack, len);
	this->TempLen = len;
	pStr += Pack_Head_Len;
	this->TempLen -= Pack_Head_Len;
	while (TempLen > 1)
	{
		temp = pStr[0];
		switch (temp)
		{
		case Type_Random:
			NowLen = *(pStr + 1);
			if (memcmp(RandomNum, pStr + 2, NowLen) == 0)
			{
				BreakLegal = TRUE;
			}
			pStr += (NowLen + 2);
			TempLen -= (NowLen + 2);
			break;
		case Type_Break_Reason:
			Reasonlegal = TRUE;
			NowLen = *(pStr + 1);
			memcpy(&ReasonFlags, pStr + 2, NowLen);
		    SkipPack(&pStr, TempLen);
			break;
		default:
			SkipPack(&pStr, TempLen);
			break;
		}
	}
	if (BreakLegal && Reasonlegal)  // && Reasonlegal
	{
		char rTips[128] = {0};
		switch (ReasonFlags)
		{
		case 0:
			memcpy(rTips, "下线提示: \r\nIDLE超时, 被服务器踢下线!\r\n是否重新登陆？", strlen("下线提示: \r\nIDLE超时, 被服务器踢下线!\r\n是否重新登陆？")); break; // "下线提示: \r\nIDLE超时,被服务器踢下线!\r\n是否重新登陆？"; 
		case 2:
			memcpy(rTips, "下线提示: \r\n您的流量已用完,被服务器踢下线!\r\n是否重新登陆？", strlen("下线提示: \r\n您的流量已用完,被服务器踢下线!\r\n是否重新登陆？")); break;  //  "下线提示: \r\n您的流量已用完,被服务器踢下线!\r\n是否重新登陆？";
		case 3:
			memcpy(rTips, "下线提示: \r\n您的时长已用完,被服务器踢下线!\r\n是否重新登陆？", strlen("下线提示: \r\n您的时长已用完,被服务器踢下线!\r\n是否重新登陆？")); break;// "下线提示: \r\n您的时长已用完,被服务器踢下线!\r\n是否重新登陆？"; break;
		case 4:
			break;
		default:
			memcpy(rTips, "下线提示: \r\n您的帐号已在其他地方登录!\r\n是否重新登陆？", strlen("下线提示: \r\n您的帐号已在其他地方登录!\r\n是否重新登陆？")); break;// "下线提示: \r\n您的帐号已在其他地方登录!\r\n是否重新登陆？"; break;
			break;
		}
		// "下线提示:";
		unsigned int Action = Action_Breaked;
		if (ReLoginFlags){ Action = Action_ReLogin; }
		LoginReplyFlag = 0;
		HWND hwnd = ::FindWindow("YellowButterfly", NULL);	
		PostMessage(hwnd, WM_NOTIFYMSG, (WPARAM)rTips, Action);
	}
	else if (BreakLegal && !Reasonlegal)
	{
		char *rTips = "下线提示: \r\n你被服务器踢下线了!\r\n是否重新登陆？";
		// "下线提示:";
		unsigned int Action = Action_Breaked;
		if (ReLoginFlags){ Action = Action_ReLogin; }
		LoginReplyFlag = 0;
		HWND hwnd = ::FindWindow("YellowButterfly", NULL);	
		PostMessage(hwnd, WM_NOTIFYMSG, (WPARAM)rTips, Action);
	}
}

void UdpClient::UnpackLogout(char *pack, int len)
{
	unsigned char temp; char *pStr;
	pStr = pack;
	int NowLen = 0;
	::CheckHeadPack(pack, len);
	this->TempLen = len;
	pStr += Pack_Head_Len;
	this->TempLen -= Pack_Head_Len;
	while (TempLen > 3)
	{
		temp = pStr[0];
		switch (temp)
		{
		case Type_Random:
			NowLen = *(pStr + 1);
			if (memcmp(RandomNum, pStr + 2, NowLen) == 0)
			{
				char *rTips = "下线提示: \r\n下线成功，您的蝴蝶帐号已正常下线！";
				// "下线提示:";
				LoginReplyFlag = 0;
				HWND hwnd = ::FindWindow("YellowButterfly", NULL);
				PostMessage(hwnd, WM_NOTIFYMSG, (WPARAM)rTips, NULL);
			};
			pStr += (NowLen + 6);
			TempLen -= (NowLen + 6);
			break;
		default:
			SkipPack(&pStr, TempLen);
			break;
		}
	}

}

void UdpClient::UnpackHeart(char *pack, int len)
{
	memset(rMsg, 0, sizeof(rMsg));
	unsigned char tmpe; char *pStr;
	pStr = pack;
	int NowLen = 0;
	::CheckHeadPack(pack, len);
	this->TempLen = len;
	pStr += Pack_Head_Len;
	this->TempLen -= Pack_Head_Len;
	while (TempLen > 3)
	{
		tmpe = pStr[0];
		switch (tmpe)
		{
		case Type_Random:
			NowLen = *(pStr + 1);
			memcpy(RandomNum, pStr + 2, NowLen);
			pStr += (NowLen + 2);
			TempLen -= (NowLen + 2);
			break;
		case Type_Identity: //reply
			NowLen = (UCHAR)*(pStr + 1);
			memcpy(SessionId, pStr + 2, NowLen);
			pStr += (NowLen + 2);
			TempLen -= (NowLen + 2);
			break;
		default:
			SkipPack(&pStr, TempLen);
			break;
		}
	}
	HeartRandom += 3;
}

void UdpClient::CleanData()
{
	this->Pack_len = 0;
	memset(this->buf, 0, sizeof(this->buf));
	this->pBuf = this->buf;
	this->pBuf += Pack_Head_Len;
	this->Pack_len += Pack_Head_Len;
}

void UdpClient::SendLoginPack(UCHAR mac[6], char username[32], char passwd[32], char localIp[16], char service[32], unsigned char ipType, char version[16])
{

	this->CleanData();

	//the sequence of pack structure is that: head(include 16 bytes of md5code) + mac + username + password + ip +service + iptype +version 
	//mac
	AddPack(&(this->pBuf), Type_Mac, strlen((char *)mac), (char *)mac, this->Pack_len);//(char *)
	//username
	AddPack(&(this->pBuf), Type_UserName, strlen(username), username, this->Pack_len);
	//password
	AddPack(&(this->pBuf), Type_Password, strlen(passwd), passwd, this->Pack_len);
	//ip
	AddPack(&(this->pBuf), Type_Ip, strlen(localIp), localIp, this->Pack_len);
	//service
	AddPack(&(this->pBuf), Type_Service, strlen(service), service, this->Pack_len);
	//ipType hava a little difference	
	*this->pBuf = 14;
	*(this->pBuf + 1) = 3;
	(this->pBuf += 2);
	*this->pBuf = ipType;
	this->pBuf++;
	this->Pack_len += 3;
	//ClientVersion 
	AddPack(&(this->pBuf), Type_ClientVersion, strlen(version), version, this->Pack_len);
	//Head
	HeadPack(this->buf, Action_Login, this->Pack_len);
	//encrypt
	encrypt((UCHAR *)buf, this->Pack_len);
	::SendFreeData(*(this->cSocket), buf, Pack_len, this->ServerIp, 3848);
}
void UdpClient::SendHeartPack()
{
	this->MakeHeartPack(Action_HeartBeat);
}

void UdpClient::MakeHeartPack(unsigned int ActionType)        //好像心跳包和下线包构造一样....
{
	unsigned long tmpRandom=ntohl(HeartRandom);
	this->CleanData();
	//random
	AddPack(&(this->pBuf), Type_Random, strlen((char *)RandomNum), (char *)RandomNum, this->Pack_len);
	//ip
	AddPack(&(this->pBuf), Type_Ip,LoginService.LocalIp.GetLength(), LoginService.LocalIp.GetBuffer(), this->Pack_len);
	//mac
	AddPack(&(this->pBuf), Type_Mac, strlen((char *)LoginService.Mac), (char *)LoginService.Mac, this->Pack_len);
	//keep Random
	AddPack(&(this->pBuf), Type_Identity, sizeof(HeartRandom), &tmpRandom, this->Pack_len);
	//block1
	tmpRandom = 0;
	AddPack(&(this->pBuf), Type_Block1, sizeof(HeartRandom), &tmpRandom, this->Pack_len);
	//block2
	AddPack(&(this->pBuf), Type_Block2, sizeof(HeartRandom), &tmpRandom, this->Pack_len);
	//block3
	AddPack(&(this->pBuf), Type_Block3, sizeof(HeartRandom), &tmpRandom, this->Pack_len);
	//block4
	AddPack(&(this->pBuf), Type_Block4, sizeof(HeartRandom), &tmpRandom, this->Pack_len);
	//block5
	AddPack(&(this->pBuf), Type_Block5, sizeof(HeartRandom), &tmpRandom, this->Pack_len);
	//block6
	AddPack(&(this->pBuf), Type_Block6, sizeof(HeartRandom), &tmpRandom, this->Pack_len);
	//Head
	HeadPack(this->buf, ActionType, this->Pack_len);
	//encrypt
	encrypt((UCHAR *)buf, this->Pack_len);
	::SendFreeData(*(this->cSocket), buf, Pack_len, this->ServerIp, 3848);

}

void UdpClient::SendLogoutPack() 
{
	this->MakeHeartPack(Action_Logout);
}










void SendFreeData(int socket, char * buf, int len, char * ip, int port)
{
	struct	sockaddr_in addr;
	int addrlen = sizeof(struct sockaddr_in);

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);

	sendto(socket, buf, len, 0, (struct sockaddr *)&addr, addrlen);
}







void HeadPack(char *pack, int headtype, int totallen)
{

	unsigned char szDigest[16];
	unsigned char * buf;
	buf = (unsigned char *)pack;
	*pack = headtype;
	*(pack + 1) = totallen;
	pack += 2;
	MD5Digest(buf, totallen, szDigest);
	memcpy(pack, szDigest, 16);

}

void AddPack(char **pack, int packtype, int Contentlen, void *PackData, int &totallen)
{
	char * buf;
	buf = *pack;
	*buf = packtype;
	*(buf + 1) = Contentlen + 2;
	buf += 2;
	memcpy(buf, PackData, Contentlen);
	*pack += Contentlen + 2;
	totallen += Contentlen + 2;

}

BOOL CheckHeadPack(char *pack, int len)
{
	char *pPack;
	unsigned char buf[1500];
	char md5[16];
	unsigned char szDigest[16];

	if (pack != NULL)
	{
		memset(buf, 0, sizeof(buf));
		memcpy(buf, pack, len);
		pPack = pack;
		pPack += 2;
		memcpy(md5, pPack, 16);
		memset(buf + 2, 0, 16);
		MD5Digest(buf, len, szDigest);
		if (memcmp(szDigest, md5, 16) == 0)
			return  true;
	}

	return false;
}

BOOL SkipPack(char **pack, int &curlen)
{
	char *ptr = *pack;
	int tmpchar;
	tmpchar = (UCHAR)*(ptr+1);
	if (curlen<tmpchar)
		return false;
	if (tmpchar <= 2)
		return false;
	*pack += tmpchar;
	curlen -= tmpchar;
	return true;
}

BOOL  encrypt(unsigned char *data, int datalen)
{
	int	i;
	unsigned char	encode;
	if (datalen <= 0 || data == NULL) return 0;
	for (i = 0; i < datalen; i++)
	{
		encode = ((data[i] & 0x01) << 7) |
			((data[i] & 0x02) >> 1) |
			((data[i] & 0x04) << 2) |
			((data[i] & 0x08) << 2) |
			((data[i] & 0x10) << 2) |
			((data[i] & 0x20) >> 2) |
			((data[i] & 0x40) >> 4) |
			((data[i] & 0x80) >> 6);
		data[i] = encode;
	}
	return TRUE;
}


BOOL  decrypt(unsigned char *data, int datalen)
{
	unsigned char	decode;
	int	i;
	if (datalen <= 0 || data == NULL) return 0;
	for (i = 0; i < datalen; i++)
	{
		decode = ((data[i] & 0x01) << 1) |
			((data[i] & 0x02) << 6) |
			((data[i] & 0x04) << 4) |
			((data[i] & 0x08) << 2) |
			((data[i] & 0x10) >> 2) |
			((data[i] & 0x20) >> 2) |
			((data[i] & 0x40) >> 2) |
			((data[i] & 0x80) >> 7);
		data[i] = decode;
	}
	return TRUE;
}