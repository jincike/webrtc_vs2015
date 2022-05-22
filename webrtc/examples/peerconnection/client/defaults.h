/*
 *  Copyright 2011 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_EXAMPLES_PEERCONNECTION_CLIENT_DEFAULTS_H_
#define WEBRTC_EXAMPLES_PEERCONNECTION_CLIENT_DEFAULTS_H_
#pragma once

#include <stdint.h>

#include <string>
#include <vector>

//hujianhua
#define JANUS_FLAG                         1

extern const char kAudioLabel[];
extern const char kVideoLabel[];
extern const char kStreamLabel[];
extern const uint16_t kDefaultServerPort;

//保存一个网络连接信息
struct NetWorkConection
{
	int index{};			//该连接在MIB_IFTABLE中的索引
	std::string description;		//网络描述（获取自GetAdapterInfo）
	std::string description_2;	//网络描述（获取自GetIfTable）
	unsigned int in_bytes;	//初始时已接收字节数
	unsigned int out_bytes;	//初始时已发送字节数
	std::string ip_address;	//IP地址
	std::string subnet_mask;	//子网掩码
	std::string default_gateway;	//默认网关
};

std::string GetEnvVarOrDefault(const char* env_var_name,
                               const char* default_value);
std::string GetPeerConnectionString();
std::string GetDefaultServerName();
std::string GetPeerName();

void GetLocalHostIp(std::vector<NetWorkConection>& netConnections);
#endif  // WEBRTC_EXAMPLES_PEERCONNECTION_CLIENT_DEFAULTS_H_
