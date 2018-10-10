#ifndef PROTOCOL_C
#define PROTOCOL_C

#include <stddef.h>
#include <QVector>
#include "protocol.h"

#endif



/*命令参数配置---------------------------------------------------------------------*/
uint8_t  Frame_ID = 0;

//设备信息读取命令
QVector<uint16_t> AT_TypeReq{VR, NI, AP, SH, SL};

//射频参数读取命令
QVector<uint16_t> AT_ReadID{SH, SL};

//射频发送命令测试
QVector<uint16_t> AT_RfTx(10, RT);





uint8_t  XbeePro_CheckSum(uint8_t length, uint8_t *input);
bool     AT_Com_ReqType(ModuleDeal *module_deal, uint8_t *tx_buf, uint16_t &tx_num);

void     AT_Com_RspType(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);





/*AT请求指令-------------------------------------------------------------------------------------------------------------*/
uint16_t AT_Com_Req(uint16_t command, uint8_t frame_id, uint8_t *tx_buf)
{
    if (tx_buf != NULL)
    {
        XbeeApi_ATCom_t     *pXbeeApiAtCom;

        pXbeeApiAtCom = (XbeeApi_ATCom_t *)tx_buf;
        pXbeeApiAtCom->xbeeapi_header.start_byte      = API_START_DATA;
        pXbeeApiAtCom->xbeeapi_header.length_byte_msb = (((XbeeApi_ATCom_len-3) >> 8) & 0xFF);
        pXbeeApiAtCom->xbeeapi_header.length_byte_lsb = (((XbeeApi_ATCom_len-3) >> 0) & 0xFF);
        pXbeeApiAtCom->xbeeapi_header.frame_type      = API_AT_COM;

        pXbeeApiAtCom->frame_id                       = frame_id;
        pXbeeApiAtCom->at_command[0]                  = ((command >> 8) & 0xFF);
        pXbeeApiAtCom->at_command[1]                  = ((command >> 0) & 0xFF);

        tx_buf[XbeeApi_ATCom_len] = XbeePro_CheckSum((XbeeApi_ATCom_len-3), tx_buf+(XBeeApi_Header_Len-1));

        return (XbeeApi_ATCom_len+1);
    }
    else
    {
        return 0;
    }
}


/*设备类型信息请求处理------------------------------------------------------------------------------------------------------*/
bool AT_Com_ReqType(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num)
{
    auto para = module_deal->serialtxrxPara;

    if ((para->tx_num <= MODULE_TYPE_REQ_NUM) && (para->tx_num > 0))
    {
        tx_num = AT_Com_Req(AT_TypeReq[MODULE_TYPE_REQ_NUM-para->tx_num], para->frame_id, tx_buf);

        para->frame_id++;
        para->frame_id = (para->frame_id) ? (para->frame_id) : (1);

        para->tx_num--;
        para->search_count++;

        return true;
    }
    else
    {
        return false;
    }
}







void AT_Com_RspType(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num)
{
    uint16_t            AT_Command = 0;
    uint16_t            AT_Length  = 0;
    XbeeApi_ATCom_Rsp_t *pXbeeApiAtComRsp;

    auto                module = module_deal->moduleWindow;
    QString             temp_str;


    pXbeeApiAtComRsp  = (XbeeApi_ATCom_Rsp_t *)rx_buf;
    AT_Length         = (pXbeeApiAtComRsp->xbeeapi_header.length_byte_msb << 8)+pXbeeApiAtComRsp->xbeeapi_header.length_byte_lsb;
    AT_Command        = (pXbeeApiAtComRsp->at_command[0] << 8)+pXbeeApiAtComRsp->at_command[1];

    switch(AT_Command)
    {
        case VR:                                                 //节点类型
        {
            AT_Length = (rx_num - XbeeApi_ATCom_Rsp_len - 1);
            for (int i=0; i<AT_Length; i++)
            {
                temp_str += QString::number(rx_buf[XbeeApi_ATCom_Rsp_len+i] & 0xFF, 16).toUpper();
            }

            if (temp_str == "21A7")
            {
                module->Text_Content[0] = "DM";
                module->Text_Content[2] = "NBee N3H Master ";
            }
            else
            {
                module->Text_Content[0] = "DP";
                module->Text_Content[2] = "NBee N3H Slave ";
            }
            module_deal->serialtxrxPara->tx_count = 0x00;

            break;
        }

        case NI:                                                 //节点标识
        {
            AT_Length = (rx_num - XbeeApi_ATCom_Rsp_len - 1);
            for (int i=0; i<AT_Length; i++)
            {
                temp_str += rx_buf[XbeeApi_ATCom_Rsp_len+i];
            }

            module->Text_Content[1] = temp_str;
            module_deal->serialtxrxPara->tx_count = 0x00;

            break;
        }

        case AP:                                                 //通信模式
        {
            AT_Length = (rx_num - XbeeApi_ATCom_Rsp_len - 1);

            temp_str = QString::number(rx_buf[XbeeApi_ATCom_Rsp_len]);

            if (temp_str == "1")
            {
               module->Text_Content[2] += "API";
            }
            else
            {
               module->Text_Content[2] += "AT";
            }
            module_deal->serialtxrxPara->tx_count = 0x00;

            break;
        }

        case SH:                                                 //源64位地址高
        {

            AT_Length = (rx_num - XbeeApi_ATCom_Rsp_len - 1);
            for (int i=0; i<AT_Length; i++)
            {
                if(rx_buf[XbeeApi_ATCom_Rsp_len+i] < 16)
                {
                    temp_str += "0";
                }
                temp_str += QString::number(rx_buf[XbeeApi_ATCom_Rsp_len+i] & 0xFF, 16).toUpper();
            }


            module->Text_Content[4] = temp_str;
            module_deal->serialtxrxPara->tx_count = 0x00;

            break;
        }

        case SL:                                                 //源64位地址低
        {
            AT_Length = (rx_num - XbeeApi_ATCom_Rsp_len - 1);
            for (int i=0; i<AT_Length; i++)
            {
                if(rx_buf[XbeeApi_ATCom_Rsp_len+i] < 16)
                {
                    temp_str += "0";
                }
                temp_str += QString::number(rx_buf[XbeeApi_ATCom_Rsp_len+i] & 0xFF, 16).toUpper();
            }
            module->Text_Content[4] += temp_str;
            module_deal->serialtxrxPara->tx_count = 0x00;

            break;
        }
    }
}



















/*---------------------------------Xbee校验-----------------------------------*/
uint8_t XbeePro_CheckSum(uint8_t length, uint8_t *input)
{
    uint8_t i = 0;
    uint8_t sum = 0;

    for (i=0; i<length; i++)
    {
        sum += input[i];
    }

    sum = 0xFF-sum;

    return sum;
}


























