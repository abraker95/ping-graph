/*
Module : PING.H
Purpose: Interface for an MFC wrapper class to encapsulate PING
Created: PJN / 10-06-1998

Copyright (c) 1998 - 2016 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

http://www.naughter.com/ping.html
*/


/////////////////////////// Macros / Defines ////////////////////////

#pragma once

#ifndef __PING_H__
#define __PING_H__

#ifndef __ATL_SOCKET__
#pragma message("To avoid this message please put atlsocket.h in your pre compiled header (normally stdafx.h)")
#include <atlsocket.h>
#endif //#ifndef __ATL_SOCKET__

#ifndef IP_EXPORT_INCLUDED
#pragma message("To avoid this message please put IPExport.h in your pre compiled header (normally stdafx.h)")
#include <IPExport.h>
#endif //#ifndef IP_EXPORT_INCLUDED

#ifndef CPING_EXT_CLASS
#define CPING_EXT_CLASS
#endif //#ifndef CPING_EXT_CLASS

#ifndef CPING_EXT_API
#define CPING_EXT_API
#endif //#ifndef CPING_EXT_API

#ifndef _In_
#define _In_
#endif //#ifndef _In_

#ifndef _In_opt_
#define _In_opt_
#endif //#ifndef _In_opt_

#ifndef _Inout_
#define _Inout_
#endif //#ifndef _Inout_

#ifndef _Out_writes_bytes_
#define _Out_writes_bytes_(size)
#endif //#ifdef _Out_writes_bytes_


/////////////////////////// Classes /////////////////////////////////

struct CPING_EXT_CLASS CPingReplyv4
{
//Constructors / Destructors
  CPingReplyv4();

//Methods
  const ICMP_ECHO_REPLY* GetICMP_ECHO_REPLY();

//Member variables
  SOCKADDR_IN         Address;         //The IP address of the replier
  unsigned long       RTT;             //Round Trip time in Milliseconds
  unsigned long       EchoReplyStatus; //here will be status of the last ping if successful
  ATL::CHeapPtr<BYTE> Reply;           //The buffer for the ICMP_ECHO_REPLY / ICMPV6_ECHO_REPLY
};


struct CPING_EXT_CLASS CPingReplyv6
{
  //Constructors / Destructors
  CPingReplyv6();

  //Methods
  const ICMPV6_ECHO_REPLY* GetICMPV6_ECHO_REPLY();

  //Member variables
  SOCKADDR_IN6        Address;         //The IP address of the replier
  unsigned long       RTT;             //Round Trip time in Milliseconds
  unsigned long       EchoReplyStatus; //here will be status of the last ping if successful
  ATL::CHeapPtr<BYTE> Reply;           //The buffer for the ICMP_ECHO_REPLY / ICMPV6_ECHO_REPLY
};


class CPING_EXT_CLASS CPing
{
public:
//Constructors / Destructors
  CPing();
  ~CPing();

//Methods
  BOOL PingUsingICMPv4(_In_ LPCTSTR pszHostName, _Inout_ CPingReplyv4& pr, _In_ UCHAR nTTL = 10, _In_ DWORD dwTimeout = 5000, _In_ WORD wDataSize = 32, _In_ UCHAR nTOS = 0, _In_ BOOL bDontFragment = FALSE, _In_ BOOL bFlagReverse = FALSE, _In_opt_ LPCTSTR pszLocalBoundAddress = NULL) const;
  BOOL PingUsingICMPv6(_In_ LPCTSTR pszHostName, _Inout_ CPingReplyv6& pr, _In_ UCHAR nTTL = 10, _In_ DWORD dwTimeout = 5000, _In_ WORD wDataSize = 32, _In_ UCHAR nTOS = 0, _In_ BOOL bDontFragment = FALSE, _In_ BOOL bFlagReverse = FALSE, _In_opt_ LPCTSTR pszLocalBoundAddress = NULL) const;

protected:
//Function Pointers
  typedef HANDLE (WINAPI ICMPCREATEFILE)(void);
  typedef ICMPCREATEFILE* LPICMPCREATEFILE;
  typedef HANDLE (WINAPI ICMP6CREATEFILE)(void);
  typedef ICMP6CREATEFILE* LPICMP6CREATEFILE;
  typedef BOOL (WINAPI ICMPCLOSEHANDLE)(HANDLE);
  typedef ICMPCLOSEHANDLE* LPICMPCLOSEHANDLE;
  typedef DWORD (WINAPI ICMPSENDECHO)(HANDLE, IPAddr, LPVOID, WORD, IP_OPTION_INFORMATION*, LPVOID, DWORD, DWORD);
  typedef ICMPSENDECHO* LPICMPSENDECHO;
  typedef DWORD (WINAPI ICMP6SENDECHO2)(HANDLE, HANDLE, FARPROC, PVOID, sockaddr_in6*, sockaddr_in6*, LPVOID, WORD, PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD);
  typedef ICMP6SENDECHO2* LPICMP6SENDECHO2;
  typedef DWORD(WINAPI ICMPSENDECHO2EX)(HANDLE, HANDLE, FARPROC, PVOID, IPAddr, IPAddr, LPVOID, WORD, PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD);
  typedef ICMPSENDECHO2EX* LPICMPSENDECHO2EX;

//Member variables
  HMODULE           m_hIcmp;             //HINSTANCE of Iphlapi.DLL or as a fall back ICMP.DLL
  LPICMPCREATEFILE  m_pIcmpCreateFile;
  LPICMP6CREATEFILE m_pIcmp6CreateFile;
  LPICMPSENDECHO    m_pIcmpSendEcho;
  LPICMP6SENDECHO2  m_pIcmp6SendEcho2;
  LPICMPSENDECHO2EX m_pIcmpSendEcho2Ex;
  LPICMPCLOSEHANDLE m_pIcmpCloseHandle;

//Methods
  virtual void FillIcmpData(_Out_writes_bytes_(dwRequestSize) BYTE* pRequestData, _In_ DWORD dwRequestSize) const;
  static HMODULE LoadLibraryFromSystem32(_In_ LPCTSTR lpFileName);
};

#endif //#ifndef __PING_H__
