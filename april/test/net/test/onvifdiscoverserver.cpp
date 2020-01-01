/*
 @written by Li,Yangang @2019.4
*/
#include<iostream>
#include"datagramsocket.h"
#include"april_uuid.h"

using namespace std;
using namespace April::net;

int main(int argc, char** argv)
{

  // cout<<argv[1]<<" "<<argv[2]<<endl;
   DatagramSocket  ds;
  
  
   bool ret = ds.bind_v4("", 3702, true, true);
   ds.joinMulticastGroup("239.255.255.250", argv[1]);
   

   if ( ret == false )
   {
       cout<<"socket bind failed!"<<endl;
   }

   AprilUUID id_addr;
   while(1)
   {
       //uSleep(200*1000);
       char buf[2048]={ 0 };
       NetAddr addr;
       int ret_recv = ds.recvFrom(buf, 2048, addr);
       if (ret_recv > 0)
       {

           cout<<"data from"<<addr.IP()<<addr.Port()<<endl;
           cout<<buf<<endl;

           DatagramSocket  ds_c;
           bool ret1 = ds_c.bind_v4(argv[1], 3702, true, true);

           if(ret1)
           {
               AprilUUID id_msg;
               AprilUUID id_Rel;
               

               std::string strResp = "<?xml version=\"1.0\" encoding=\"utf-8\">";
               strResp += "<s:Envelope xmlns:sc=\"http://www.w3.org/2003/05/soap-encoding\" ";
               strResp += "xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" ";
               strResp += "xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" ";
               strResp += "xmlns:d=\"http://schemas.xmlsoap.org/ws/2005/04/discovery\" ";
               strResp += "xmlns:dn=\"http://www.onvif.org/ver10/network/wsdl\" ";
               strResp += "xmlns:tds=\"http://www.onvif.org/ver10/device/wsdl\">";
               strResp += "<s:Header><a:MessageID>uuid:";
               strResp += id_msg.get(); 
               strResp += "</a:MessageID>";
               strResp += "<a:To>urn:schemas-xmlsoap-org:ws:2005:04:discovery</a:To>";
               strResp += "<a:Action>http://schemas.xmlsoap.org/ws/2005/04/discovery/ProbeMatches</a:Action>";
               strResp += "<a:RelatesTo>uuid:"; 
               strResp += id_Rel.get(); 
               strResp += "</a:RelatesTo>";
               strResp += "</s:Header><s:Body><d:ProbeMatches><d:ProbeMatch>";
               strResp += "<a:EndpointReference><a:Address>uuid:";
               strResp +=  id_addr.get();
               strResp +=  "</a:Address></a:EndpointReference>";
               strResp += "<d:Types>dn:NetworkVideoTransmitter tds:Device</d:Types>";
               strResp += "<d:Scopes>onvif://www.onvif.org/location/country/china ";
               strResp += "onvif://www.onvif.org/name/Honeywell ";
               strResp += "onvif://www.onvif.org/hardware/HFD6GR2 ";
               strResp += "onvif://www.onvif.org/Profile/Streaming ";
               strResp += "onvif://www.onvif.org/type/Network_Video_Transmitter "; 
               strResp += "onvif://www.onvif.org/MAC/";
               strResp +=  argv[2];
               strResp +=  " </d:Scopes>";
               strResp += "<d:XAddrs>http://";
               strResp +=  argv[1];
               strResp += "/onvif/device_service</d:XAddrs>";
               strResp += "<d:MetadataVersion>1</d:MetadataVersion>";
               strResp += "</d:ProbeMatch></d:ProbeMatches></s:Body></s:Envelope>";

               ds_c.sendTo((char*)strResp.c_str(), strResp.length(), addr);
               
           }
       }
   }
}