#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>
#include <QString>
#include "leftwindow.h"



/*AT指令功能码定义------------------------------------------------------------*/
#define         CONVERSION(a, b)                        (b +(a << 8))
//地址命令
#define         DH                                      CONVERSION('D', 'H')    //目的地址高32位
#define         DL                                      CONVERSION('D', 'L')    //目的地址低32位
#define         MY                                      CONVERSION('M', 'Y')    //16位网络地址
#define         MP                                      CONVERSION('M', 'P')    //16位父节点地址
#define         NC                                      CONVERSION('N', 'C')    //查看还可加入子节点个数
#define         SH                                      CONVERSION('S', 'H')    //读取独立64位地址高32位
#define         SL                                      CONVERSION('S', 'L')    //读取独立64位地址低32位
#define         NI                                      CONVERSION('N', 'I')    //读取节点描述
#define         SE                                      CONVERSION('S', 'E')    //设置AT命令模式下发送数据源endpoint值
#define         DE                                      CONVERSION('D', 'E')    //设置AT命令模式下发送数据目的endpoint值
#define         CI                                      CONVERSION('C', 'I')    //设置AT命令下簇ID
#define         NP                                      CONVERSION('N', 'P')    //payload字节84不加密，加密62
#define         DD                                      CONVERSION('D', 'D')    //设备类型标识
//网络命令
#define         CH                                      CONVERSION('C', 'H')    //当前使用信道
#define         DA                                      CONVERSION('D', 'A')    //强制节点离网  +
#define         ID                                      CONVERSION('I', 'D')    //扩展64位地址
#define         OP                                      CONVERSION('O', 'P')    //对扩展64位地址操作
#define         NH                                      CONVERSION('N', 'H')    //单播数据发送超时时间（NH*50）+100ms
#define         BH                                      CONVERSION('B', 'H')    //广播数据可跳级数
#define         OI                                      CONVERSION('O', 'I')    //获取网络PANID
#define         NT                                      CONVERSION('N', 'T')    //节点发现应答超时时间设置？？
#define         NO                                      CONVERSION('N', 'O')    //节点发现操作模式？？
#define         SC                                      CONVERSION('S', 'C')    //扫描信道
#define         CR                                      CONVERSION('C', 'R')    //设置PANID冲突检测阀值到达这个阀值PANID改变
#define         SD                                      CONVERSION('S', 'D')    //信道扫描周期
#define         ZS                                      CONVERSION('Z', 'S')    //协议栈版本：0~2
#define         NJ                                      CONVERSION('N', 'J')    //COOR组网后允许节点加入时间
#define         JV                                      CONVERSION('J', 'V')    //通道验证？？
#define         NW                                      CONVERSION('N', 'W')    //网络看门狗，协调器使用
#define         JN                                      CONVERSION('J', 'N')    //节点加入通知
#define         AR                                      CONVERSION('A', 'R')    //Many-To-One广播时间
#define         DJ                                      CONVERSION('D', 'J')    //节点禁止加入
#define         II                                      CONVERSION('I', 'I')    //重新入网，重新生成PANID
//安全命令
#define         EE                                      CONVERSION('E', 'E')    //加密使能
#define         EO                                      CONVERSION('E', 'O')    //加密模式
#define         NK                                      CONVERSION('N', 'K')    //网络层密钥
#define         KY                                      CONVERSION('K', 'Y')    //应用层密钥
//无线接口命令
#define         PL                                      CONVERSION('P', 'L')    //射频发送功率
#define         PM                                      CONVERSION('P', 'M')    //射频发送模式
#define         DB                                      CONVERSION('D', 'B')    //接受信号强度
#define         PP                                      CONVERSION('P', 'P')    //dbM值读取
//串口接口命令
#define         AP                                      CONVERSION('A', 'P')    //API使能
#define         AO                                      CONVERSION('A', 'O')    //API模式
#define         BD                                      CONVERSION('B', 'D')    //串口波特率
#define         NB                                      CONVERSION('N', 'B')    //串口校验位
#define         SB                                      CONVERSION('S', 'B')    //串口停止位
#define         RO                                      CONVERSION('R', 'O')
#define         D7                                      CONVERSION('D', '7')
#define         D6                                      CONVERSION('D', '6')
//I/O命令
#define         IR                                      CONVERSION('I', 'R')
#define         IC                                      CONVERSION('I', 'C')
#define         P0                                      CONVERSION('P', '0')
#define         P1                                      CONVERSION('P', '1')
#define         P2                                      CONVERSION('P', '2')
#define         P3                                      CONVERSION('P', '3')
#define         D0                                      CONVERSION('D', '0')
#define         D1                                      CONVERSION('D', '1')
#define         D2                                      CONVERSION('D', '2')
#define         D3                                      CONVERSION('D', '3')
#define         D4                                      CONVERSION('D', '4')
#define         D5                                      CONVERSION('D', '5')
#define         D8                                      CONVERSION('D', '8')
#define         LT                                      CONVERSION('L', 'T')
#define         PR                                      CONVERSION('P', 'R')
#define         RP                                      CONVERSION('R', 'P')
#define         DO                                      CONVERSION('D', 'O')
#define         YV                                      CONVERSION('%', 'V')
#define         VJ                                      CONVERSION('V', '+')
#define         TP                                      CONVERSION('T', 'P')
//诊断命令
#define         VR                                      CONVERSION('V', 'R')    //固件版本读取
#define         HV                                      CONVERSION('H', 'V')    //硬件版本读取
#define         AI                                      CONVERSION('A', 'I')    //网络状态指示
//AT 操作命令
#define         MT                                      CONVERSION('C', 'T')
#define         CN                                      CONVERSION('C', 'N')
#define         GT                                      CONVERSION('G', 'T')
#define         CC                                      CONVERSION('C', 'C')
//休眠命令
#define         SM                                      CONVERSION('S', 'M')    //休眠模式
#define         SN                                      CONVERSION('S', 'N')    //休眠周期
#define         SP                                      CONVERSION('S', 'P')    //设置休眠周期
#define         ST                                      CONVERSION('S', 'T')    //进入休眠前延时时间长度
#define         SO                                      CONVERSION('S', 'O')    //设置休眠操作
#define         WH                                      CONVERSION('W', 'H')
#define         SI                                      CONVERSION('S', 'I')
#define         PO                                      CONVERSION('P', 'O')    //保持和休眠周期一样
//执行命令
#define         AC                                      CONVERSION('A', 'C')    //应用修改
#define         WR                                      CONVERSION('W', 'R')    //参数保存
#define         RE                                      CONVERSION('R', 'E')    //参数恢复默认值
#define         FR                                      CONVERSION('F', 'R')    //软件复位
#define         NR                                      CONVERSION('N', 'R')    //网络复位
#define         CB                                      CONVERSION('C', 'B')
#define         ND                                      CONVERSION('N', 'D')
#define         DN                                      CONVERSION('D', 'N')
#define         IS                                      CONVERSION('I', 'S')

//射频测试
#define         RT                                      CONVERSION('R', 'T')    //射频发送测试
#define         RR                                      CONVERSION('R', 'R')    //射频接收测试


#define API_START_DATA                                  0x7E                    //起始数据
#define API_FRAME_ID                                    0x00                    //默认FRAME_ID
#define DEVICE_TYPE_ID_R                                0xBC000001              //为路由器
#define DEVICE_TYPE_ID_E                                0xBC000002              //为终端



/*XBee-Cluster定义------------------------------------------------------------*/
#define  REMOTE_COM_REQ_ZCL                             0x0021                  //针对0x17远程命令请求
#define  REMOTE_COM_RES_ZCL                             0x00A1                  //针对0x97远程命令请求应答
#define  ZIGBEE_TRA_REQ_ZCL                             0x0011                  //针对数据请求
#define  JOINING_ARNOUNCE_ZCL                           0x0013                  //节点上线告知
#define  ZIGBEE_ND_COM_ZCL                              0x0015

/*XBee-Profile定义------------------------------------------------------------*/
#define  ZDO_PROFILE_ID                                 0x0000                  //ZDO profile
#define  AT_PROFILE_ID                                  0xC105                  //对应0x17 0x97 0x10



/*0x8A节点状态定义------------------------------------------------------------*/
#define Modem_Status_Hard_Reset                         0x00                    //硬件复位
#define Modem_Status_Wdg_Reset                          0x01                    //看门狗复位
#define Modem_Status_Join_Net                           0x02                    //加入网络
#define Modem_Status_Disassociated                      0x03                    //断开连接
#define Modem_Status_Coor_Started                       0x06                    //协调器开启
#define Modem_Status_Security_Updated                   0x07                    //加密更新



/*XBee-API命令功能码----------------------------------------------------------*/
#define  API_AT_COM                                     0x08	                //API AT命令
#define  API_AT_COM_QUEUE                               0x09	                //API  AT命令模块参数设置，该参数并不立即生效,直到发送"AT COM(0x08)"或者AC命令
#define	 API_ZIGBEE_TRA_REQ                             0x10	                //API 数据发送
#define  API_EX_ADDR_ZIGBEE_COM                         0x11                    //发送数据允许应用层添加Point，profile ID cluster ID等
#define	 API_REMOTE_COM_REQ                             0x17	                //远程节点参数设置
#define	 API_CREATE_SOURCE_ROUTE                        0x21 	                //创建路由路径
#define  API_AT_COM_RESPONSE                            0x88	                //API AT命令应答
#define	 API_MODEM_STATUS                               0x8A	                //无线模块特定状态
#define  API_ZIGBEE_TRA_STATUS	                        0x8B	                //API 数据发送状态返回
#define  API_ZIGBEE_REC_PACKET                          0x90	                //API 数据接收
#define  API_ZIGBEE_EX_RX_INDICATOR                     0x91	                //接收数据(其中AO=1否则为//普通接收包0x90)
#define	 API_ZIGBEE_IO_DATA_SAMP                        0x92 	                //模块收到远程IO采样帧
#define  API_XBEE_SENSOR_READ                           0x94	                //模块收到传感器信息(A0=0)
#define  API_NODE_IDENTIFICATION                        0x95	                //节点发送标识信息给协调器 (AO=0)
#define  API_REMOTE_COM_RES                             0x97	                //远程节点参数设置应答
#define  API_OVER_AIR_UPDATE                            0xA0                    //空中无线升级
#define  API_ROUTE_RECORD_INDICATOR                     0xA1 	                //路由应答
#define  API_MANY_TO_ONE                                0xA3                    //多对一路由


/*AT命令应答状态定义----------------------------------------------------------*/
#define  AT_ACK_SUCCESS                                 0x00                    //成功
#define  AT_ACK_ERROR                                   0x01                    //错误
#define  AT_ACK_NO_CMD                                  0x02                    //错误功能码
#define  AT_ACK_NO_PARA                                 0x03                    //错误参数
#define  AT_ACK_TX_FAILE                                0x04                    //发送错误




/*对应功能码结构体定义--------------------------------------------------------*/
#pragma pack(1)
typedef struct                                                                  //XBeeApi帧头
{
    uint8_t start_byte;
    uint8_t length_byte_msb;
    uint8_t length_byte_lsb;
    uint8_t frame_type;
}XBeeApi_Header_t;
#pragma pack()


//功能码-0x08
#pragma pack(1)                                                                 //XBeeApi AT命令帧 0x08 参数立即生效
typedef struct
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t frame_id;
    uint8_t at_command[2];
}XbeeApi_ATCom_t;
#pragma pack()


//功能码-0x09
#pragma pack(1)
typedef struct                                                                  //XbeeApi AT命令帧 0x09 参数不立即生效
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t frame_id;
    uint8_t at_command[2];
    uint8_t parameter_value[1];
}XbeeApi_ATComQueue_t;
#pragma pack()


//功能码-0x10
#pragma pack(1)                                                                 //XbeeApi 数据发送0x10
typedef struct
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t frame_id;
    uint8_t dest_64_address[8];
    uint8_t dest_16_address[2];
    uint8_t broadcast_radius;
    uint8_t options;
    uint8_t rf_data[1];
}XbeeApi_Tra_Req_t;
#pragma pack()


//功能码-0x11
#pragma pack(1)                                                                 //XbeeApi 发送数据允许应用程添加端口等0x11
typedef struct
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t frame_id;
    uint8_t dest_64_address[8];
    uint8_t dest_16_address[2];
    uint8_t source_endpoint;
    uint8_t dest_endpoint;
    uint8_t cluster_id[2];
    uint8_t profile_id[2];
    uint8_t broadcast_radius;
    uint8_t transmit_options;
    uint8_t rf_data[1];
}XbeeApi_Ex_Tra_Req_t;
#pragma pack()


//功能码-0x17
#pragma pack(1)                                                                 //XbeeApi 发送远程命令帧 0x17
typedef struct
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t frame_id;
    uint8_t dest_64_address[8];
    uint8_t dest_16_address[2];
    uint8_t remote_cmd_opt;
    uint8_t at_command[2];
    uint8_t parameter_value[1];
}XbeeApi_Remote_Com_Req_t;
#pragma pack()

//远程命令设置请求无线接收到空中数据帧格式
#pragma pack(1)
typedef struct
{
    uint8_t unknow[2];
    uint8_t remote_cmd;                                                         //Bit0:Disable ACK; BIT1:Apply Changes; BIT6:Extened timeout
    uint8_t frame_id;
    uint8_t src_64_address[8];
    uint8_t src_16_address[2];
    uint8_t at_command[2];
    uint8_t parameter_value[1];
}XbeeApi_Remote_Com_Req_Data_t;
#pragma pack()




//功能码-0x21
#pragma pack(1)                                                                 //XbeeApi 创建源路由 0x21
typedef struct
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t frame_id;
    uint8_t dest_64_address[8];
    uint8_t dest_16_address[2];
    uint8_t route_cmd_opt;
    uint8_t nums_address;
    uint8_t address[1];
}XbeeApi_Create_Src_Route_t;
#pragma pack()


//功能码-0x88
#pragma pack(1)                                                                 //XbeeApi AT命令应答  0x88
typedef struct
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t frame_id;
    uint8_t at_command[2];
    uint8_t command_status;
}XbeeApi_ATCom_Rsp_t;
#pragma pack()


//功能码-0x8A
#pragma pack(1)                                                                 //XbeeApi 节点状态0x8A
typedef struct
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t status;
}XbeeApi_Modem_Status_t;
#pragma pack()


//功能码-0x8B
#pragma pack(1)
typedef struct                                                                  //XbeeApi 数据发送状态0x8B
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t frame_id;
    uint8_t dest_16_address[2];
    uint8_t tra_retry_count;
    uint8_t delivery_status;
    uint8_t discovery_status;
}XbeeApi_Tra_Status_t;
#pragma pack()


//功能码-0x90
#pragma pack(1)                                                                 //XbeeApi 接收到数据0x90
typedef struct
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t source_64_address[8];
    uint8_t source_16_address[2];
    uint8_t receive_options;
    uint8_t received_data[1];
}XbeeApi_Rec_Packet_t;
#pragma pack()


//功能码-0x91
#pragma pack(1)                                                                 //XbeeApi 接收到数据0x91
typedef struct
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t source_64_address[8];
    uint8_t source_16_address[2];
    uint8_t source_endpoint;
    uint8_t dest_endpoint;
    uint8_t cluster_id[2];
    uint8_t profile_id[2];
    uint8_t receive_options;
    uint8_t received_data[1];
}XbeeApi_Ex_Rec_Packet_t;
#pragma pack()


//功能码-0x92
#pragma pack(1)                                                                 //XbeeApi IO采集接收显示 0x92
typedef struct
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t source_64_address[8];
    uint8_t source_16_address[2];
    uint8_t receive_opt;
    uint8_t nums_samples;
    uint8_t digital_channel_mask[2];
    uint8_t analog_channel_mask;
    uint8_t digital_sample[2];
    uint8_t analog_sample[2];
}XbeeApi_IOData_Sample_Rx_t;
#pragma pack()


//功能码-0x94
#pragma pack(1)                                                                 //XbeeApi 传感器值读取 0x94
typedef struct
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t source_64_address[8];
    uint8_t source_16_address[2];
    uint8_t receive_opt;
    uint8_t wire_sensors;
    uint8_t ad_values[8];
    uint8_t temperature_values[2];
}XbeeApi_Sensor_Read_Indicator_t;
#pragma pack()


//功能码-0x95
#pragma pack(1)                                                                 //XbeeApi 节点识别读取 0x95
typedef struct
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t source_64_address[8];
    uint8_t source_16_address[2];
    uint8_t receive_opt;
    uint8_t set_16_address[2];
    uint8_t set_64_address[8];
    uint8_t ni_string[2];
    uint8_t parent_16_address[2];
    uint8_t device_type;
    uint8_t source_event;
    uint8_t profile_id[2];
    uint8_t manufacturer_id[2];
}XbeeApi_Node_Identification_t;
#pragma pack()


//功能码-0x97
#pragma pack(1)                                                                 //XbeeApi 收到远程模块设置命令0x97
typedef struct
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t frame_id;
    uint8_t source_64_address[8];
    uint8_t source_16_address[2];
    uint8_t at_com[2];
    uint8_t com_status;
    uint8_t com_paratmeter[1];
}XbeeApi_Remote_Com_Res_t;
#pragma pack()

//远程命令设置请求应答空中数据帧格式
#pragma pack(1)
typedef struct
{
    uint8_t frame_id;
    uint8_t at_command[2];
    uint8_t cmd_status;        //0:OK; 1:ERROR; 2:Invail Command; 3:Invail Paramter; 4:Remote Command error
}XbeeApi_Remote_Com_Req_Ack_t;
#pragma pack()


//功能码-0xA0
#pragma pack(1)                                                                 //XbeeApi OTA固件更新 0xA0
typedef struct
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t source_64_address[8];
    uint8_t source_16_address[2];
    uint8_t receive_opt;
    uint8_t bootloader_mess;
    uint8_t block_num;
    uint8_t dst_64_address[8];
}XbeeApi_OTA_Update_t;
#pragma pack()


//功能码-0xA1
#pragma pack(1)                                                                 //XbeeApi 路由记录 0xA1
typedef struct
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t source_64_address[8];
    uint8_t source_16_address[2];
    uint8_t receive_opt;
    uint8_t num_address;
    uint8_t address[1];
}XbeeApi_Route_Record_t;
#pragma pack()


//功能码-0xA3
#pragma pack(1)                                                                 //XbeeApi 多对一路由请求 0xA3
typedef struct
{
    XBeeApi_Header_t xbeeapi_header;
    uint8_t source_64_address[8];
    uint8_t source_16_address[2];
}XbeeApi_Many_One_Route_t;
#pragma pack()




//无线协议接收结构体定义处理
//#pragma pack(1)
//typedef struct
//{
//    EmberNodeId              sender;
//    EmberEUI64               senderEui64;
//    EmberIncomingMessageType type;
//    EmberApsFrame            *apsFrame;
//    uint16_t                 messageLength;
//    uint8_t                  *messageContents;
//}Rf_Protocol_t;
//#pragma pack()

/*AT命令相关操作定义-----------------------------------------------------------*/
#define AT_COM_READ_LEN                     0x04                                   //AT命令读取帧长度



/*结构体长度定义--------------------------------------------------------------*/
#define XBeeApi_Header_Len                 sizeof(XBeeApi_Header_t)                //头长度
#define XbeeApi_ATCom_len                  sizeof(XbeeApi_ATCom_t)                 //功能码0x08
#define XbeeApi_ATComQueue_len             sizeof(XbeeApi_ATComQueue_t)            //功能码0x09
#define XbeeApi_Tra_Req_len                sizeof(XbeeApi_Tra_Req_t)               //功能码0x10
#define XbeeApi_Ex_Tra_Req_len             sizeof(XbeeApi_Ex_Tra_Req_t)            //功能码0x11
#define XbeeApi_Remote_Com_Req_len         sizeof(XbeeApi_Remote_Com_Req_t)        //功能码0x17
#define XbeeApi_Create_Src_Route_len       sizeof(XbeeApi_Create_Src_Route_t)      //功能码0x21
#define XbeeApi_ATCom_Rsp_len              sizeof(XbeeApi_ATCom_Rsp_t)             //功能码0x88
#define XbeeApi_Modem_Status_len           sizeof(XbeeApi_Modem_Status_t)          //功能码0x8A
#define XbeeApi_Tra_Status_len             sizeof(XbeeApi_Tra_Status_t)            //功能码0x8B
#define XbeeApi_Rec_Packet_len             sizeof(XbeeApi_Rec_Packet_t)            //功能码0x90
#define XbeeApi_Ex_Rec_Packet_len          sizeof(XbeeApi_Ex_Rec_Packet_t)         //功能码0x91
#define XbeeApi_IOData_Sample_Rx_len       sizeof(XbeeApi_IOData_Sample_Rx_t)      //功能码0x92
#define XbeeApi_Sensor_Read_Indicator_len  sizeof(XbeeApi_Sensor_Read_Indicator_t) //功能码0x94
#define XbeeApi_Node_Identification_len    sizeof(XbeeApi_Node_Identification_t)   //功能码0x95
#define XbeeApi_Remote_Com_Res_len         sizeof(XbeeApi_Remote_Com_Res_t)        //功能码0x97
#define XbeeApi_OTA_Update_len             sizeof(XbeeApi_OTA_Update_t)            //功能码0xA0
#define XbeeApi_Route_Record_len           sizeof(XbeeApi_Route_Record_t)          //功能码0xA1
#define XbeeApi_Many_One_Route_len         sizeof(XbeeApi_Many_One_Route_t)        //功能码0xA3





/*用户变量定义---------------------------------------------------------------------------------*/
#define MODULE_REQ_NULL                   0xFF                                    //无命令发送
#define MODULE_TYPE_REQ_FUN               0x01                                    //设备信息类型请求
#define MODULE_RADIO_TEST_FUN             0x02                                    //射频参数测试



#define MODULE_TYPE_REQ_NUM               5
#define MODULE_TYPE_REQ_INTERVAL          3000




#endif // PROTOCOL_H
























