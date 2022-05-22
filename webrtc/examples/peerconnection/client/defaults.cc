/*
 *  Copyright 2012 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "webrtc/examples/peerconnection/client/defaults.h"

#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#include <winsock2.h>
#include <Iphlpapi.h>
#else
#include <unistd.h>
#endif

#include "webrtc/base/arraysize.h"

const char kAudioLabel[] = "audio_label";
const char kVideoLabel[] = "video_label";
const char kStreamLabel[] = "stream_label";
const uint16_t kDefaultServerPort = 8888;

std::string GetEnvVarOrDefault(const char* env_var_name,
                               const char* default_value) {
  std::string value;
  const char* env_var = getenv(env_var_name);
  if (env_var)
    value = env_var;

  if (value.empty())
    value = default_value;

  return value;
}

std::string GetPeerConnectionString() {
  return GetEnvVarOrDefault("WEBRTC_CONNECT", "stun:stun.l.google.com:19302");
}
 
void GetLocalHostIp(std::vector<NetWorkConection>& netConnections) {
	PIP_ADAPTER_INFO pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[sizeof(IP_ADAPTER_INFO)];		//PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);		//�õ��ṹ���С,����GetAdaptersInfo����
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);	//����GetAdaptersInfo����,���pIpAdapterInfoָ�����;����stSize��������һ��������Ҳ��һ�������

	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//����������ص���ERROR_BUFFER_OVERFLOW
		//��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
		//��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������
		delete[](BYTE*)pIpAdapterInfo;	//�ͷ�ԭ�����ڴ�ռ�
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];	//���������ڴ�ռ������洢����������Ϣ
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);		//�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
	}
	PIP_ADAPTER_INFO pIpAdapterInfoHead = pIpAdapterInfo;	//����pIpAdapterInfo�����е�һ��Ԫ�صĵ�ַ

	if (ERROR_SUCCESS == nRel)
	{
		while (pIpAdapterInfo)
		{
			NetWorkConection connection;
			connection.description = pIpAdapterInfo->Description;
			connection.ip_address =  pIpAdapterInfo->IpAddressList.IpAddress.String;;
			connection.subnet_mask = pIpAdapterInfo->IpAddressList.IpMask.String;
			connection.default_gateway = pIpAdapterInfo->GatewayList.IpAddress.String;

			netConnections.push_back(connection);
			pIpAdapterInfo = pIpAdapterInfo->Next;
	}
}
	//�ͷ��ڴ�ռ�
	if (pIpAdapterInfoHead)
	{
		delete[](BYTE*)pIpAdapterInfoHead;
	}
	return;
}
std::string GetDefaultServerName() {
#if JANUS_FLAG
	std::vector<NetWorkConection> netConnections;
	GetLocalHostIp(netConnections);
	std::string firstIpDefault = netConnections.at(0).ip_address;
  return GetEnvVarOrDefault("WEBRTC_SERVER", firstIpDefault.c_str());
#else
  return GetEnvVarOrDefault("WEBRTC_SERVER", "localhost");
#endif
}

std::string GetPeerName() {
  char computer_name[256];
  std::string ret(GetEnvVarOrDefault("USERNAME", "user"));
  ret += '@';
  if (gethostname(computer_name, arraysize(computer_name)) == 0) {
    ret += computer_name;
  } else {
    ret += "host";
  }
  return ret;
}
