#ifndef PROTOCOL_C
#define PROTOCOL_C

#include <stddef.h>
#include <QVector>
#include "protocol.h"

#endif



/*命令参数配置---------------------------------------------------------------------*/
uint8_t  Frame_ID = 0;

//设备信息读取命令
QVector<uint16_t> AT_TypeReq{VR, NI, AP, SH, SL, RI};


//射频参数读取
QVector<uint16_t> AT_ReadID{RI, SH, SL};


//射频发送命令测试
QVector<uint16_t> AT_RfTx{TO, RT, TR};


//射频发送电流测试
QVector<uint16_t> AT_RfTxCurrent{CT};


//射频发送电流测试
QVector<uint16_t> AT_RfRxCurrent{CR};


//GPIO测试
QVector<uint16_t> AT_GPIO{IO};


//晶振测试
QVector<uint16_t>AT_OSC{CO};


//休眠电流测试
QVector<uint16_t>AT_SleepCurrent{CS};

//射频状态初始化
QVector<uint16_t>AT_RfStateInit{RI};





uint8_t  XbeePro_CheckSum(uint8_t length, uint8_t *input);
bool     AT_Com_ReqType(ModuleDeal *module_deal, uint8_t *tx_buf, uint16_t &tx_num);
bool     AT_Com_RfInit(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);
bool     AT_Com_ReadID(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);
bool     AT_Com_RfTx(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);
bool     AT_Com_RfTxCurrent(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);
bool     AT_Com_RfRxCurrent(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);
bool     AT_Com_RfGPIO(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);
bool     AT_Com_RfOSC(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);
bool     AT_Com_RfSleepCurrent(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);
bool     AT_Com_RfStateInit(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num);


void     AT_Com_RspType(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
void     AT_Com_RxAmmeter(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
void     AT_Com_RspRfInit(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
void     AT_Com_RspID(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
uint8_t  AT_Com_RspRfTx(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num, Rf_Rx_Tx_Para &rtx_para);
void     AT_Com_RspRfTxCurrent(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
void     AT_Com_RspRfRxCurrent(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
void     AT_Com_RspRfGPIO(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
void     AT_Com_RspRfOSC(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
void     AT_Com_RspRfSleepCurrent(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);
void     AT_Com_RspRfStateInit(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num);



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



/*获取模块ID------------------------------------------------------------------------------------------------------------*/
bool AT_Com_ReadID(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num)
{
    auto para = module_deal->serialtxrxPara;

    if ((para->tx_num <= MODULE_READ_ID_NUM) && (para->tx_num > 0))
    {
        tx_num = AT_Com_Req(AT_ReadID[MODULE_READ_ID_NUM-para->tx_num], para->frame_id, tx_buf);

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


/*发送测试------------------------------------------------------------------------------------------------------------*/
bool AT_Com_RfTx(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num)
{
    auto para = module_deal->serialtxrxPara;

    if ((para->tx_num <= MODULE_RF_TX_NUM) && (para->tx_num > 0))
    {
        tx_num = AT_Com_Req(AT_RfTx[MODULE_RF_TX_NUM-para->tx_num], para->frame_id, tx_buf);

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


/*发送电流测试-----------------------------------------------------------------------------------------------------*/
bool AT_Com_RfTxCurrent(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num)
{
    auto para = module_deal->serialtxrxPara;

    if ((para->tx_num <= MODULE_CURRENT_TX_NUM) && (para->tx_num > 0))
    {
        tx_num = AT_Com_Req(AT_RfTxCurrent[MODULE_CURRENT_TX_NUM-para->tx_num], para->frame_id, tx_buf);

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


/*接收电流测试-----------------------------------------------------------------------------------------------------*/
bool AT_Com_RfRxCurrent(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num)
{
    auto para = module_deal->serialtxrxPara;

    if ((para->tx_num <= MODULE_CURRENT_RX_NUM) && (para->tx_num > 0))
    {
        tx_num = AT_Com_Req(AT_RfRxCurrent[MODULE_CURRENT_RX_NUM-para->tx_num], para->frame_id, tx_buf);

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


/*GPIO测试-----------------------------------------------------------------------------------------------------*/
bool AT_Com_RfGPIO(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num)
{
    auto para = module_deal->serialtxrxPara;

    if ((para->tx_num <= MODULE_GPIO_NUM) && (para->tx_num > 0))
    {
        tx_num = AT_Com_Req(AT_GPIO[MODULE_GPIO_NUM-para->tx_num], para->frame_id, tx_buf);

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


/*晶振测试-----------------------------------------------------------------------------------------------------*/
bool AT_Com_RfOSC(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num)
{
    auto para = module_deal->serialtxrxPara;

    if ((para->tx_num <= MODULE_OSC_NUM) && (para->tx_num > 0))
    {
        tx_num = AT_Com_Req(AT_OSC[MODULE_OSC_NUM-para->tx_num], para->frame_id, tx_buf);

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


/*休眠电流测试-----------------------------------------------------------------------------------------------------*/
bool AT_Com_RfSleepCurrent(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num)
{
    auto para = module_deal->serialtxrxPara;

    if ((para->tx_num <= MODULE_CURRENT_SLEEP_NUM) && (para->tx_num > 0))
    {
        tx_num = AT_Com_Req(AT_SleepCurrent[MODULE_CURRENT_SLEEP_NUM-para->tx_num], para->frame_id, tx_buf);

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



/*射频状态初始化-----------------------------------------------------------------------------------------------------*/
bool AT_Com_RfStateInit(ModuleDeal *module_deal,  uint8_t *tx_buf, uint16_t &tx_num)
{
    auto para = module_deal->serialtxrxPara;

    if ((para->tx_num <= MODULE_RF_STATE_INIT_NUM) && (para->tx_num > 0))
    {
        tx_num = AT_Com_Req(AT_RfStateInit[MODULE_RF_STATE_INIT_NUM-para->tx_num], para->frame_id, tx_buf);

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
    uint8_t             sum=0;
    uint16_t            AT_Command = 0;
    uint16_t            AT_Length  = 0, length = 0;
    XbeeApi_ATCom_Rsp_t *pXbeeApiAtComRsp;
    XBeeApi_Header_t    *pXbeeApiHeader;

    auto                module = module_deal->moduleWindow;
    QString             temp_str;


     if (((rx_buf[0] == '+') || (rx_buf[0] == '-')) && (rx_num == 17))
     {
         module_deal->serialtxrxPara->tx_count = 0x00;
         module_deal->serialtxrxPara->tx_num= 0x00;

         module->Node_Type = "DA";
         module->Text_Content[0] = "DA";
         module->Text_Content[1] = "Agilent 34401A";
         module->Text_Content[2] = "SCPI Talk Only ASCII";
         module->Text_Content[4] = "000000000000001F";

     }
     else
     {
         pXbeeApiHeader = (XBeeApi_Header_t *)rx_buf;
         length = (pXbeeApiHeader->length_byte_msb << 8) + pXbeeApiHeader->length_byte_lsb;
         if ((rx_buf[0] != 0x7E) || (length >= 255))
         {
            return;
         }

         sum = XbeePro_CheckSum(length, &rx_buf[XBeeApi_Header_Len-1]);
         if (sum != rx_buf[XBeeApi_Header_Len+length-1])
         {
             return;
         }


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
                    module->Node_Type = "DM";
                    module->Text_Content[0] = "DM";
                    module->Text_Content[2] = "NBee N3H Master ";
                }
                else
                {
                    module->Node_Type = "DP";
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

            case RI:                                                //射频初始化
            {
                module_deal->serialtxrxPara->tx_count = 0x00;

                break;
            }
        }
     }
}


void AT_Com_RxAmmeter(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num)
{
     if (((rx_buf[0] == '+') || (rx_buf[0] == '-')) && (rx_num == 17))
     {
         double   ammeter_data = 0;
         uint32_t temp_Integer = 0, temp_decimal = 0, temp_index = 0;
         uint32_t temp_data = 0;
         int8_t  num = 0, data = 0;

         module_deal->serialtxrxPara->tx_count = 0x00;
         module_deal->serialtxrxPara->tx_num= 0x00;

         /*********  +1.01700000E-07 ***************************/
         //整数
         num++;
         for (; num<15; num++)
         {
             if (rx_buf[num] != '.')
             {
                temp_Integer *= 10;
                temp_Integer += (rx_buf[num]-'0');
             }
             else
             {
                 break;
             }
         }


         //小数
         num++;
         for (;num<15; num++)
         {
             if (rx_buf[num] != 'E')
             {
                temp_decimal *= 10;
                temp_decimal += (rx_buf[num]-'0');
             }
             else
             {
                 break;
             }
         }

         //指数
         num += 2;
         for (;num<15; num++)
         {
             if (rx_buf[num] != 'E')
             {
                temp_index *= 10;
                temp_index += rx_buf[num]-'0';
             }
             else
             {
                 break;
             }
         }

         ammeter_data = temp_decimal;
         ammeter_data /= 100000000;
         ammeter_data += temp_Integer;
         for (num=0; num<temp_index; num++)
         {
             if (rx_buf[12] == '+')
             {
                 ammeter_data *= 10;
             }
             else
             {
                 ammeter_data /= 10;
             }
         }

         //转变成mA
         ammeter_data *= 1000;
         module_deal->moduleWindow->Ammeter_Data = ammeter_data;

         //转变成10*uA
         temp_data = (uint32_t)(10000*ammeter_data);
         module_deal->moduleWindow->Ammeter_Text = "";
         data = (temp_data % 10000000)/1000000;
         module_deal->moduleWindow->Ammeter_Text += QString::number(data);
         data = (temp_data % 1000000)/100000;
         module_deal->moduleWindow->Ammeter_Text += QString::number(data);
         data = (temp_data % 100000/10000);
         module_deal->moduleWindow->Ammeter_Text += QString::number(data);

         module_deal->moduleWindow->Ammeter_Text += '.';

         data = (temp_data % 10000)/1000;
         module_deal->moduleWindow->Ammeter_Text += QString::number(data);
         data = (temp_data % 1000)/100;
         module_deal->moduleWindow->Ammeter_Text += QString::number(data);
         data = (temp_data % 100)/10;
         module_deal->moduleWindow->Ammeter_Text += QString::number(data);

         module_deal->moduleWindow->Ammeter_Text += '.';


         data = (temp_data % 10);
         module_deal->moduleWindow->Ammeter_Text += QString::number(data);
     }
}





void AT_Com_RspID(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num)
{
    uint8_t             sum = 0;
    uint16_t            AT_Command = 0;
    uint16_t            AT_Length  = 0, length = 0;
    XbeeApi_ATCom_Rsp_t *pXbeeApiAtComRsp;
    XBeeApi_Header_t    *pXbeeApiHeader;

    auto                module = module_deal->moduleWindow;
    QString             temp_str;


    pXbeeApiHeader = (XBeeApi_Header_t *)rx_buf;
    length = (pXbeeApiHeader->length_byte_msb << 8) + pXbeeApiHeader->length_byte_lsb;
    if ((rx_buf[0] != 0x7E) || (length >= 255))
    {
       return;
    }

    sum = XbeePro_CheckSum(length, &rx_buf[XBeeApi_Header_Len-1]);
    if (sum != rx_buf[XBeeApi_Header_Len+length-1])
    {
        return;
    }

    pXbeeApiAtComRsp  = (XbeeApi_ATCom_Rsp_t *)rx_buf;
    AT_Length         = (pXbeeApiAtComRsp->xbeeapi_header.length_byte_msb << 8)+pXbeeApiAtComRsp->xbeeapi_header.length_byte_lsb;
    AT_Command        = (pXbeeApiAtComRsp->at_command[0] << 8)+pXbeeApiAtComRsp->at_command[1];

    switch(AT_Command)
    {
        case RI:                                                 //射频初始化
        {
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



uint8_t AT_Com_RspRfTx(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num, Rf_Rx_Tx_Para &rtx_para)
{
    uint8_t             sum = 0;
    uint16_t            AT_Command = 0;
    uint16_t            AT_Length  = 0, length = 0;
    XbeeApi_ATCom_Rsp_t *pXbeeApiAtComRsp;
    XBeeApi_Header_t    *pXbeeApiHeader;

    pXbeeApiHeader = (XBeeApi_Header_t *)rx_buf;
    length = (pXbeeApiHeader->length_byte_msb << 8) + pXbeeApiHeader->length_byte_lsb;
    if ((rx_buf[0] != 0x7E) || (length >= 255))
    {
       return 0;
    }

    sum = XbeePro_CheckSum(length, &rx_buf[XBeeApi_Header_Len-1]);
    if (sum != rx_buf[XBeeApi_Header_Len+length-1])
    {
        return 0;
    }

    pXbeeApiAtComRsp  = (XbeeApi_ATCom_Rsp_t *)rx_buf;
    AT_Length         = (pXbeeApiAtComRsp->xbeeapi_header.length_byte_msb << 8)+pXbeeApiAtComRsp->xbeeapi_header.length_byte_lsb;
    AT_Command        = (pXbeeApiAtComRsp->at_command[0] << 8)+pXbeeApiAtComRsp->at_command[1];

    switch(AT_Command)
    {
        case TO:                                                //发送测试接收打开
        {
            module_deal->serialtxrxPara->tx_count = 0;

            return 1;
            break;
        }


        case RT:                                                 //开始发送测试
        {
            rtx_para.tx_num =  rx_buf[XbeeApi_ATCom_Rsp_len];
            rtx_para.tx_num =  (rtx_para.tx_num << 8);
            rtx_para.tx_num += rx_buf[XbeeApi_ATCom_Rsp_len+1];

            module_deal->serialtxrxPara->tx_count = 1;

            return 2;
            break;
        }

        case TF:                                                 //发送测试发送完成
        {
            module_deal->serialtxrxPara->tx_count = 0;

            return 3;
            break;
        }

        case TR:                                                //发送测试结果读取
        {
            rtx_para.rssi   = (int8_t)rx_buf[XbeeApi_ATCom_Rsp_len];
            rtx_para.rx_num =  rx_buf[XbeeApi_ATCom_Rsp_len+1];
            rtx_para.rx_num =  (rtx_para.rx_num << 8);
            rtx_para.rx_num += rx_buf[XbeeApi_ATCom_Rsp_len+2];

            module_deal->serialtxrxPara->tx_count = 0;
            return 4;
            break;
        }

    }

    return 0;
}



void  AT_Com_RspRfTxCurrent(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num)
{
    uint8_t             sum = 0;
    uint16_t            AT_Command = 0;
    uint16_t            AT_Length  = 0, length = 0;
    XbeeApi_ATCom_Rsp_t *pXbeeApiAtComRsp;
    XBeeApi_Header_t    *pXbeeApiHeader;

    pXbeeApiHeader = (XBeeApi_Header_t *)rx_buf;
    length = (pXbeeApiHeader->length_byte_msb << 8) + pXbeeApiHeader->length_byte_lsb;
    if ((rx_buf[0] != 0x7E) || (length >= 255))
    {
       return;
    }

    sum = XbeePro_CheckSum(length, &rx_buf[XBeeApi_Header_Len-1]);
    if (sum != rx_buf[XBeeApi_Header_Len+length-1])
    {
        return;
    }

    pXbeeApiAtComRsp  = (XbeeApi_ATCom_Rsp_t *)rx_buf;
    AT_Length         = (pXbeeApiAtComRsp->xbeeapi_header.length_byte_msb << 8)+pXbeeApiAtComRsp->xbeeapi_header.length_byte_lsb;
    AT_Command        = (pXbeeApiAtComRsp->at_command[0] << 8)+pXbeeApiAtComRsp->at_command[1];

    switch(AT_Command)
    {
        case CT:                                                //发送电流测试应答
        {
            module_deal->serialtxrxPara->tx_count = 0;

            break;
        }
    }
}


void  AT_Com_RspRfRxCurrent(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num)
{
    uint8_t             sum = 0;
    uint16_t            AT_Command = 0;
    uint16_t            AT_Length  = 0, length = 0;
    XbeeApi_ATCom_Rsp_t *pXbeeApiAtComRsp;
    XBeeApi_Header_t    *pXbeeApiHeader;

    pXbeeApiHeader = (XBeeApi_Header_t *)rx_buf;
    length = (pXbeeApiHeader->length_byte_msb << 8) + pXbeeApiHeader->length_byte_lsb;
    if ((rx_buf[0] != 0x7E) || (length >= 255))
    {
       return;
    }

    sum = XbeePro_CheckSum(length, &rx_buf[XBeeApi_Header_Len-1]);
    if (sum != rx_buf[XBeeApi_Header_Len+length-1])
    {
        return;
    }

    pXbeeApiAtComRsp  = (XbeeApi_ATCom_Rsp_t *)rx_buf;
    AT_Length         = (pXbeeApiAtComRsp->xbeeapi_header.length_byte_msb << 8)+pXbeeApiAtComRsp->xbeeapi_header.length_byte_lsb;
    AT_Command        = (pXbeeApiAtComRsp->at_command[0] << 8)+pXbeeApiAtComRsp->at_command[1];

    switch(AT_Command)
    {
        case CR:                                                //接收电流测试应答
        {
            module_deal->serialtxrxPara->tx_count = 0;

            break;
        }
    }
}


void  AT_Com_RspRfGPIO(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num)
{
    uint8_t             sum = 0;
    uint16_t            AT_Command = 0;
    uint16_t            AT_Length  = 0, length = 0;
    XbeeApi_ATCom_Rsp_t *pXbeeApiAtComRsp;
    XBeeApi_Header_t    *pXbeeApiHeader;

    pXbeeApiHeader = (XBeeApi_Header_t *)rx_buf;
    length = (pXbeeApiHeader->length_byte_msb << 8) + pXbeeApiHeader->length_byte_lsb;
    if ((rx_buf[0] != 0x7E) || (length >= 255))
    {
       return;
    }

    sum = XbeePro_CheckSum(length, &rx_buf[XBeeApi_Header_Len-1]);
    if (sum != rx_buf[XBeeApi_Header_Len+length-1])
    {
        return;
    }

    pXbeeApiAtComRsp  = (XbeeApi_ATCom_Rsp_t *)rx_buf;
    AT_Length         = (pXbeeApiAtComRsp->xbeeapi_header.length_byte_msb << 8)+pXbeeApiAtComRsp->xbeeapi_header.length_byte_lsb;
    AT_Command        = (pXbeeApiAtComRsp->at_command[0] << 8)+pXbeeApiAtComRsp->at_command[1];

    switch(AT_Command)
    {
        case IO:                                                //GPIO测试
        {
            module_deal->serialtxrxPara->tx_count = 0;

            break;
        }
    }
}



void  AT_Com_RspRfOSC(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num)
{
    uint8_t             sum = 0;
    uint16_t            AT_Command = 0;
    uint16_t            AT_Length  = 0, length = 0;
    XbeeApi_ATCom_Rsp_t *pXbeeApiAtComRsp;
    XBeeApi_Header_t    *pXbeeApiHeader;

    pXbeeApiHeader = (XBeeApi_Header_t *)rx_buf;
    length = (pXbeeApiHeader->length_byte_msb << 8) + pXbeeApiHeader->length_byte_lsb;
    if ((rx_buf[0] != 0x7E) || (length >= 255))
    {
       return;
    }

    sum = XbeePro_CheckSum(length, &rx_buf[XBeeApi_Header_Len-1]);
    if (sum != rx_buf[XBeeApi_Header_Len+length-1])
    {
        return;
    }

    pXbeeApiAtComRsp  = (XbeeApi_ATCom_Rsp_t *)rx_buf;
    AT_Length         = (pXbeeApiAtComRsp->xbeeapi_header.length_byte_msb << 8)+pXbeeApiAtComRsp->xbeeapi_header.length_byte_lsb;
    AT_Command        = (pXbeeApiAtComRsp->at_command[0] << 8)+pXbeeApiAtComRsp->at_command[1];

    switch(AT_Command)
    {
        case CO:                                                //OSC测试
        {
            module_deal->serialtxrxPara->tx_count = 0;

            break;
        }
    }
}



void  AT_Com_RspRfSleepCurrent(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num)
{
    uint8_t             sum = 0;
    uint16_t            AT_Command = 0;
    uint16_t            AT_Length  = 0, length = 0;
    XbeeApi_ATCom_Rsp_t *pXbeeApiAtComRsp;
    XBeeApi_Header_t    *pXbeeApiHeader;

    pXbeeApiHeader = (XBeeApi_Header_t *)rx_buf;
    length = (pXbeeApiHeader->length_byte_msb << 8) + pXbeeApiHeader->length_byte_lsb;
    if ((rx_buf[0] != 0x7E) || (length >= 255))
    {
       return;
    }

    sum = XbeePro_CheckSum(length, &rx_buf[XBeeApi_Header_Len-1]);
    if (sum != rx_buf[XBeeApi_Header_Len+length-1])
    {
        return;
    }

    pXbeeApiAtComRsp  = (XbeeApi_ATCom_Rsp_t *)rx_buf;
    AT_Length         = (pXbeeApiAtComRsp->xbeeapi_header.length_byte_msb << 8)+pXbeeApiAtComRsp->xbeeapi_header.length_byte_lsb;
    AT_Command        = (pXbeeApiAtComRsp->at_command[0] << 8)+pXbeeApiAtComRsp->at_command[1];

    switch(AT_Command)
    {
        case CS:                                                //休眠电流测试
        {
            module_deal->serialtxrxPara->tx_count = 0;

            break;
        }
    }
}



void  AT_Com_RspRfStateInit(ModuleDeal *module_deal, uint8_t *rx_buf, uint16_t rx_num)
{
    uint8_t             sum = 0;
    uint16_t            AT_Command = 0;
    uint16_t            AT_Length  = 0, length = 0;
    XbeeApi_ATCom_Rsp_t *pXbeeApiAtComRsp;
    XBeeApi_Header_t    *pXbeeApiHeader;

    pXbeeApiHeader = (XBeeApi_Header_t *)rx_buf;
    length = (pXbeeApiHeader->length_byte_msb << 8) + pXbeeApiHeader->length_byte_lsb;
    if ((rx_buf[0] != 0x7E) || (length >= 255))
    {
       return;
    }

    sum = XbeePro_CheckSum(length, &rx_buf[XBeeApi_Header_Len-1]);
    if (sum != rx_buf[XBeeApi_Header_Len+length-1])
    {
        return;
    }

    pXbeeApiAtComRsp  = (XbeeApi_ATCom_Rsp_t *)rx_buf;
    AT_Length         = (pXbeeApiAtComRsp->xbeeapi_header.length_byte_msb << 8)+pXbeeApiAtComRsp->xbeeapi_header.length_byte_lsb;
    AT_Command        = (pXbeeApiAtComRsp->at_command[0] << 8)+pXbeeApiAtComRsp->at_command[1];

    switch(AT_Command)
    {
        case RI:                                                //射频状态初始化
        {
            module_deal->serialtxrxPara->tx_count = 0;

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


























