//#include <stdio.h>
//#include <Process.h>
//#include <QCoreApplication>
//#include <QEvent>
#include <QFile>
#include <QTextStream>
#include <QReadWriteLock>
#include <QDateTime>
#include "win_qextserialport.h"
//#include "xmlprocessor.h"
#define MAX_BUFFSIZE 2048
char g_buffer[MAX_BUFFSIZE];

/*!
\fn Win_QextSerialPort::Win_QextSerialPort()
Default constructor.  Note that the name of the device used by a Win_QextSerialPort constructed
with this constructor will be determined by #defined constants, or lack thereof - the default
behavior is the same as _TTY_LINUX_.  Possible naming conventions and their associated constants
are:

\verbatim

Constant         Used By         Naming Convention
----------       -------------   ------------------------
_TTY_WIN_        Windows         COM1, COM2
_TTY_IRIX_       SGI/IRIX        /dev/ttyf1, /dev/ttyf2
_TTY_HPUX_       HP-UX           /dev/tty1p0, /dev/tty2p0
_TTY_SUN_        SunOS/Solaris   /dev/ttya, /dev/ttyb
_TTY_DIGITAL_    Digital UNIX    /dev/tty01, /dev/tty02
_TTY_FREEBSD_    FreeBSD         /dev/ttyd0, /dev/ttyd1
_TTY_LINUX_      Linux           /dev/ttyS0, /dev/ttyS1
<none>           Linux           /dev/ttyS0, /dev/ttyS1
\endverbatim

This constructor associates the object with the first port on the system, e.g. COM1 for Windows
platforms.  See the other constructor if you need a port other than the first.
*/
int m_table1ON;
int m_table1OFF;
int m_table2ON;
int m_table2OFF;
int m_vFan1,m_vFan2;
int m_iFan1,m_iFan2;
//QTimer *m_tTimer;
char gcHead303;
char gcAddress303[3];
char gcCommand303[5];
char gcHead353;
char gcAddress353[3];
char gcCommand353[5];
char gcHead354;
char gcAddress354[3];
char gcCommand354[5];
char gcHead355;
char gcAddress355[3];
char gcCommand355[5];
char gcHead356;
char gcAddress356[3];
char gcCommand356[5];
int m_defTemperatureType;
int m_defLutronType;
int gTimer=0;
bool isRun;
bool gterminate;
static enum
{
        START,
        ADDRESS,
        COMMAND,
        CHECKSUM,
        END
} deliverState;


#define MaxCmd 52
char BossWinCommand[MaxCmd][4][10]=
{
        {"001","#","0","GET_T"},
        {"C001","#","0","GET_TC"},
        {"F001","#","0","GET_TF"},
        {"002","#","1","GET_H"},
        {"003","#","2","GET_B2"},
        {"005","#","3","GET_T"},
        {"006","#","4","GET_T"},
        {"007","#","5","GET_T"},
        {"008","#","6","GET_T"},
        {"009","#","7","GET_T"},
        {"011","#","C0TC","GET_T2C"},
        {"012","#","C0TC","GET_T2F"},
        {"013","#","C0H","GET_H2"},
        {"301","#","A001","GET_R"},
        {"302","#","A000","GET_R"},
        {"303","#","100","GET_S"},
        {"304","#","0","GET_S"},
        {"305","#","20","GET_S"},
        {"306","#","40","GET_S"},
        {"307","#","60","GET_S"},
        {"308","#","80","GET_S"},
        {"309","#","100","GET_S"},
        {"310","#","0","GET_S"},

        {"311","#","200","GET_I"},
        {"312","#","40","GET_I"},
        {"313","#","100","GET_I"},
        {"314","#","130","GET_I"},
        {"315","#","150","GET_I"},
        {"316","#","180","GET_I"},
        {"317","#","200","GET_I"},
        {"318","#","40","GET_I"},

        {"323","#","Q01001","GET_R"},
        {"324","#","Q01001","GET_R"},
        {"325","#","Q01001","GET_R"},
        {"326","#","Q01001","GET_R"},
        {"327","#","Q01001","GET_R"},
        {"351","#","A001","GET_R"},
        {"352","#","A000","GET_R"},
        {"357","#","A501","GET_R"},
        {"358","#","A500","GET_R"},
        {"359","#","A601","GET_R"},
        {"360","#","A600","GET_R"},
        {"361","#","A701","GET_R"},
        {"362","#","A700","GET_R"},
        {"451","#","B401","GET_R"},
        {"452","#","B400","GET_R"},
        {"453","#","B501","GET_R"},
        {"454","#","B500","GET_R"},
        {"455","#","B601","GET_R"},
        {"456","#","B600","GET_R"},
        {"457","#","B701","GET_R"},
        {"458","#","B700","GET_R"}
};
stBOSSWIN bwBosswin[MaxCmd];


#define FAILURE -1
#define USER1_STX0 'Q'
#define USER1_STX1 'C'
#define USER1_STX2 'R'
#define USER1_STX3 'S'
#define USER1_ETX0 '*'


QFile LogFile;
#define SHOW1 TRUE  //->data
#define SHOW2 TRUE  //<-data
#define SHOW3 TRUE  //data->
#define SHOW4 TRUE  //data<-
/**
****************************************************************************************************************
@ description:將data寫入log檔
@ param:char* string: 欲寫入的資料
@ author: Yu-Hua Tseng
@ date: 2010.05.22
@ version: 1.0
@ Histroy: Initial version.
****************************************************************************************************************
*/
void To_Log_File(char* string)
{
    QDateTime DT;

    QTextStream out(&LogFile);

    out <<"["<<DT.currentDateTime().toString("yyyy.MM.dd hh:mm:ss").toLocal8Bit().data()<< "]"<<":"<<string<<"\n";

//   qDebug("%s",string);
}

/**
****************************************************************************************************************
@ description:初始化log檔 (QFile)
@ author: Yu-Hua Tseng
@ date: 2010.05.23
@ version: 1.0
@ Histroy: Initial version.
2010.06.04: 修正log檔存放路徑
****************************************************************************************************************
*/
void Initial_Log_File()
{

    LogFile.setFileName("Log_GreenUI.txt");

    if(!LogFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        To_Log_File((char*)"Open or create GreenLog Fail\n");

        return;
    }

    To_Log_File((char*)"**********************************Log Start**********************************\n");

}

Win_QextSerialPort::Win_QextSerialPort():
    QextSerialBase()
{
    Win_Handle=INVALID_HANDLE_VALUE;
    init();
}

/*!Win_QextSerialPort::Win_QextSerialPort(const Win_QextSerialPort&)
Copy constructor.
*/
Win_QextSerialPort::Win_QextSerialPort(const Win_QextSerialPort& s):
    QextSerialBase(s.port)
{
    Win_Handle=INVALID_HANDLE_VALUE;
    _queryMode = s._queryMode;
    _bytesToWrite = s._bytesToWrite;
    bytesToWriteLock = new QReadWriteLock;
    overlapThread = new Win_QextSerialThread(this);
    setOpenMode(s.openMode());
    lastErr=s.lastErr;
    port = s.port;
    Settings.FlowControl=s.Settings.FlowControl;
    Settings.Parity=s.Settings.Parity;
    Settings.DataBits=s.Settings.DataBits;
    Settings.StopBits=s.Settings.StopBits;
    Settings.BaudRate=s.Settings.BaudRate;
    Win_Handle=s.Win_Handle;
    memcpy(&Win_CommConfig, &s.Win_CommConfig, sizeof(COMMCONFIG));
    memcpy(&Win_CommTimeouts, &s.Win_CommTimeouts, sizeof(COMMTIMEOUTS));
    if (s.overlapThread->isRunning())
        overlapThread->start();
}

/*!
\fn Win_QextSerialPort::Win_QextSerialPort(const QString & name)
Constructs a serial port attached to the port specified by devName.
devName is the name of the device, which is windowsystem-specific,
e.g."COM2" or "/dev/ttyS0".
*/
Win_QextSerialPort::Win_QextSerialPort(const QString & name, QextSerialBase::QueryMode mode):
    QextSerialBase(name)
{
    Win_Handle=INVALID_HANDLE_VALUE;
    setQueryMode(mode);
    init();
}

/*!
\fn Win_QextSerialPort::Win_QextSerialPort(const PortSettings& settings)
Constructs a port with default name and specified settings.
*/
Win_QextSerialPort::Win_QextSerialPort(const PortSettings& settings, QextSerialBase::QueryMode mode)
{
    Win_Handle=INVALID_HANDLE_VALUE;
    setBaudRate(settings.BaudRate);
    setDataBits(settings.DataBits);
    setStopBits(settings.StopBits);
    setParity(settings.Parity);
    setFlowControl(settings.FlowControl);
    setTimeout(settings.Timeout_Millisec);
    setQueryMode(mode);
    init();
}

/*!
\fn Win_QextSerialPort::Win_QextSerialPort(const QString & name, const PortSettings& settings)
Constructs a port with specified name and settings.
*/
Win_QextSerialPort::Win_QextSerialPort(const QString & name, const PortSettings& settings, QextSerialBase::QueryMode mode)
{
    Win_Handle=INVALID_HANDLE_VALUE;
    setPortName(name);
    setBaudRate(settings.BaudRate);
    setDataBits(settings.DataBits);
    setStopBits(settings.StopBits);
    setParity(settings.Parity);
    setFlowControl(settings.FlowControl);
    setTimeout(settings.Timeout_Millisec);
    setQueryMode(mode);
    init();
}

void Win_QextSerialPort::init()
{
    int l;
    for(l=0; l<MaxCmd; l++)
    {
        bwBosswin[l].isUse=false;
    }
    _bytesToWrite = 0;
    m_defTemperatureType=0;
        m_defLutronType=2;
    overlapThread = new Win_QextSerialThread(this);
    bytesToWriteLock = new QReadWriteLock;
    m_table1ON=0;
    m_table1OFF=0;
    m_table2ON=0;
    m_table2OFF=0;
    m_vFan1=0;
    m_vFan2=0;
    m_iFan1=0;
    m_iFan2=0;
    Initial_Log_File();

}

/*!
\fn Win_QextSerialPort::~Win_QextSerialPort()
Standard destructor.
*/
Win_QextSerialPort::~Win_QextSerialPort()
{
    if (isOpen())
    {
        close();
    }
    delete overlapThread;
    delete bytesToWriteLock;
    To_Log_File((char*)"**********************************Log End**********************************\n");
    LogFile.close();
}

/*!
\fn Win_QextSerialPort& Win_QextSerialPort::operator=(const Win_QextSerialPort& s)
overrides the = operator
*/
Win_QextSerialPort& Win_QextSerialPort::operator=(const Win_QextSerialPort& s)
{
    setOpenMode(s.openMode());
    _queryMode = s._queryMode;
    _bytesToWrite = s._bytesToWrite;
    bytesToWriteLock = new QReadWriteLock;
    overlapThread = new Win_QextSerialThread(this);
    lastErr=s.lastErr;
    port = s.port;
    Settings.FlowControl=s.Settings.FlowControl;
    Settings.Parity=s.Settings.Parity;
        Settings.DataBits=s.Settings.DataBits;
    Settings.StopBits=s.Settings.StopBits;
    Settings.BaudRate=s.Settings.BaudRate;
    Win_Handle=s.Win_Handle;
    memcpy(&Win_CommConfig, &s.Win_CommConfig, sizeof(COMMCONFIG));
    memcpy(&Win_CommTimeouts, &s.Win_CommTimeouts, sizeof(COMMTIMEOUTS));
    if (s.overlapThread->isRunning())
        overlapThread->start();
    return *this;
}


/*!
\fn bool Win_QextSerialPort::open(OpenMode mode)
Opens a serial port.  Note that this function does not specify which device to open.  If you need
to open a device by name, see Win_QextSerialPort::open(const char*).  This function has no effect
if the port associated with the class is already open.  The port is also configured to the current
settings, as stored in the Settings structure.
*/
bool Win_QextSerialPort::open(OpenMode mode)
{
    unsigned long confSize = sizeof(COMMCONFIG);
    Win_CommConfig.dwSize = confSize;
    DWORD dwFlagsAndAttributes = 0;


        LOCK_MUTEX();
    if (mode == QIODevice::NotOpen)
        return isOpen();
    if (!isOpen())
    {

        Win_Handle=CreateFileA(port.toLatin1(), GENERIC_READ|GENERIC_WRITE,
                               FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, dwFlagsAndAttributes, NULL);
        if (Win_Handle!=INVALID_HANDLE_VALUE)
        {
            m_bufferlength=0;
            /*configure port settings*/
            GetCommConfig(Win_Handle, &Win_CommConfig, &confSize);
            GetCommState(Win_Handle, &(Win_CommConfig.dcb));

            /*set up parameters*/
            Win_CommConfig.dcb.fBinary=TRUE;
            Win_CommConfig.dcb.fInX=FALSE;
            Win_CommConfig.dcb.fOutX=FALSE;
            Win_CommConfig.dcb.fAbortOnError=FALSE;
            Win_CommConfig.dcb.fNull=FALSE;
            setBaudRate(Settings.BaudRate);
            setDataBits(Settings.DataBits);
            setStopBits(Settings.StopBits);
            setParity(Settings.Parity);
            setFlowControl(Settings.FlowControl);
            setTimeout(Settings.Timeout_Millisec);
            SetCommConfig(Win_Handle, &Win_CommConfig, sizeof(COMMCONFIG));
            overlapThread->start();
            QIODevice::open(mode);
        }
    }
    else
    {
        UNLOCK_MUTEX();
        return false;
    }
        UNLOCK_MUTEX();
    return isOpen();
}

/*!
\fn void Win_QextSerialPort::close()
Closes a serial port.  This function has no effect if the serial port associated with the class
is not currently open.
*/
void Win_QextSerialPort::close()
{
    LOCK_MUTEX();
    if (isOpen())
    {
        flush();
        if (overlapThread->isRunning())
        {
            overlapThread->stop();
            while(isRun)
            {
                Sleep(1000);
            }
        }
        if (CloseHandle(Win_Handle))
            Win_Handle = INVALID_HANDLE_VALUE;
        _bytesToWrite = 0;
        QIODevice::close();
    }

        UNLOCK_MUTEX();
}

/*!
\fn void Win_QextSerialPort::flush()
Flushes all pending I/O to the serial port.  This function has no effect if the serial port
associated with the class is not currently open.
*/
void Win_QextSerialPort::flush()
{
        LOCK_MUTEX();
    if (isOpen())
    {
        FlushFileBuffers(Win_Handle);
    }
        UNLOCK_MUTEX();
}

/*!
\fn qint64 Win_QextSerialPort::size() const
This function will return the number of bytes waiting in the receive queue of the serial port.
It is included primarily to provide a complete QIODevice interface, and will not record errors
in the lastErr member (because it is const).  This function is also not thread-safe - in
multithreading situations, use Win_QextSerialPort::bytesAvailable() instead.
*/
qint64 Win_QextSerialPort::sizeSukon() const
{
    int availBytes;
    COMSTAT Win_ComStat;
    DWORD Win_ErrorMask=0;
    ClearCommError(Win_Handle, &Win_ErrorMask, &Win_ComStat);
    availBytes = Win_ComStat.cbInQue;
    return (qint64)availBytes;
}

qint64 Win_QextSerialPort::size() const
{

    return m_bufferlength;
}


qint64 Win_QextSerialPort::bytesAvailable()
{
        LOCK_MUTEX();
    if (isOpen())
    {
        return m_bufferlength;
    }
        UNLOCK_MUTEX();
    return 0;
}

/*!
\fn void Win_QextSerialPort::translateError(ulong error)
Translates a system-specific error code to a QextSerialPort error code.  Used internally.
*/
void Win_QextSerialPort::translateError(ulong error)
{
    if (error&CE_BREAK)
    {
        lastErr=E_BREAK_CONDITION;
    }
    else if (error&CE_FRAME)
    {
        lastErr=E_FRAMING_ERROR;
    }
    else if (error&CE_IOE)
    {
        lastErr=E_IO_ERROR;
    }
    else if (error&CE_MODE)
    {
        lastErr=E_INVALID_FD;
    }
    else if (error&CE_OVERRUN)
    {
        lastErr=E_BUFFER_OVERRUN;
    }
    else if (error&CE_RXPARITY)
    {
        lastErr=E_RECEIVE_PARITY_ERROR;
    }
    else if (error&CE_RXOVER)
    {
        lastErr=E_RECEIVE_OVERFLOW;
    }
    else if (error&CE_TXFULL)
    {
        lastErr=E_TRANSMIT_OVERFLOW;
    }
}

/*!
\fn qint64 Win_QextSerialPort::readData(char *data, qint64 maxSize)
Reads a block of data from the serial port.  This function will read at most maxlen bytes from
the serial port and place them in the buffer pointed to by data.  Return value is the number of
bytes actually read, or -1 on error.

\warning before calling this function ensure that serial port associated with this class
is currently open (use isOpen() function to check if port is open).
*/



qint64 Win_QextSerialPort::readData(char *data, qint64 maxSize)
{
    DWORD retVal=0;

    if(!data)
    {
        lastErr = E_READ_FAILED;
        retVal = (DWORD)-1;
        return (qint64)retVal;
    }
    else
    {
        qint64 realReadSize;
        char tempbuffer[MAX_BUFFSIZE];
        if(maxSize > m_bufferlength) realReadSize = m_bufferlength;
        else realReadSize = maxSize;
                LOCK_MUTEX();
        memcpy(data,g_buffer,realReadSize);
        m_bufferlength-=realReadSize;
        if(m_bufferlength>0)
        {
            memcpy(tempbuffer,g_buffer+realReadSize,m_bufferlength);
            memcpy(g_buffer,tempbuffer,m_bufferlength);
        }
        retVal = (DWORD)realReadSize;
                UNLOCK_MUTEX();
    }
    return (qint64)retVal;
}

/*!
\fn qint64 Win_QextSerialPort::writeData(const char *data, qint64 maxSize)
Writes a block of data to the serial port.  This function will write len bytes
from the buffer pointed to by data to the serial port.  Return value is the number
of bytes actually written, or -1 on error.

\warning before calling this function ensure that serial port associated with this class
is currently open (use isOpen() function to check if port is open).
*/

bool Win_QextSerialPort::doSendCommand(char * cHead,char *cAddress,char *cCommand)
{
    bool bReturn=TRUE;
    DWORD dataSize=0,dwSend;

    char cSendData[128];
    int j,datalen;
    char cChecksum[3];
    unsigned char cCheckCal=0;
    sprintf(cSendData,"%s%s%s",cHead,cAddress,cCommand);
    datalen=strlen(cSendData);
    for(j=0; j<datalen; j++)
        cCheckCal+=cSendData[j];

    sprintf(cChecksum,"%.2X",cCheckCal);
//  strcat(cSendData,cChecksum);
    strcat(cSendData,"\r");
    dataSize+=datalen+1;

#ifdef SHOW3
    char szCmd[128];
    sprintf(szCmd,"%s ->",cSendData);
    To_Log_File(szCmd);
#endif
    if (!WriteFile(Win_Handle, (void*)cSendData, (DWORD)dataSize, & dwSend, NULL))
    {
        lastErr = E_WRITE_FAILED;
        bReturn=false;
    }
    Sleep(200);

    return bReturn;
}

bool Win_QextSerialPort::doRecReturn(char cHead,char *cAddress,char *cCommand)
{
    DWORD dataSize=0,dwSend;
    char szRead[128];

    size_t j;
    bool bReturn=TRUE;
    char cChecksum[3];
    unsigned char cCheckCal=0;



    dataSize=sizeSukon();
    if(dataSize>0)
    {

        if(dataSize>(128-1)) dataSize=128-1;
        ReadFile(Win_Handle, (void*)(szRead), (DWORD)dataSize, & dwSend, NULL);
        szRead[dwSend]=0;
#ifdef SHOW4
        char szCmd[128];
        sprintf(szCmd,"%s <-",szRead);
        To_Log_File(szCmd);
#endif
        if(NULL!=strstr(szRead,">"))
        {
            sprintf(szRead,"%c%s%sSC",cHead,cAddress,cCommand);
        }
        else
            bReturn=false;
    }
    else
        bReturn=false;
    if(!bReturn)
        sprintf(szRead,"%c%s%sSF",cHead,cAddress,cCommand);
    cCheckCal=0;
    for(j=0; j<strlen(szRead); j++)
        cCheckCal+=szRead[j];
    sprintf(cChecksum,"%.2X",cCheckCal);
    strcat(szRead,cChecksum);
    strcat(szRead,"*");
#ifdef SHOW2
    char szCmd[128];
    sprintf(szCmd,"<- %s",szRead);
    To_Log_File(szCmd);
#endif
    memcpy(g_buffer+m_bufferlength,szRead,strlen(szRead));
    m_bufferlength+=strlen(szRead);


    return bReturn;
}

bool Win_QextSerialPort::doRecReturnNULL(void)
{
    char szRead[128];
    DWORD dataSize=0,dwSend;
    bool bReturn=TRUE;

    dataSize=sizeSukon();
    if(dataSize>0)
    {
        if(dataSize>(128-1)) dataSize=128-1;
        ReadFile(Win_Handle, (void*)(szRead), (DWORD)dataSize, & dwSend, NULL);
        szRead[dwSend]=0;
#ifdef SHOW4
        char szCmd[128];
        sprintf(szCmd,"%s <-",szRead);
        To_Log_File(szCmd);
#endif
    }
    else
        bReturn=false;

    return bReturn;
}

bool Win_QextSerialPort::doRecReturnX(char cHead,char *cAddress,char *cCommand,int iTure)
{
    char szRead[128];
    bool bReturn=TRUE;
    char cChecksum[3];
    unsigned char cCheckCal=0;

    size_t j;

    if(iTure)
    {
        sprintf(szRead,"%c%s%sSC",cHead,cAddress,cCommand);
    }
    else
        sprintf(szRead,"%c%s%sSF",cHead,cAddress,cCommand);
    cCheckCal=0;
    for(j=0; j<strlen(szRead); j++)
        cCheckCal+=szRead[j];
    sprintf(cChecksum,"%.2X",cCheckCal);
    strcat(szRead,cChecksum);
    strcat(szRead,"*");
#ifdef SHOW2
    char szCmd[128];
    sprintf(szCmd,"<- %s",szRead);
    To_Log_File(szCmd);
#endif
    memcpy(g_buffer+m_bufferlength,szRead,strlen(szRead));
    m_bufferlength+=strlen(szRead);

    return bReturn;
}
bool Win_QextSerialPort::doRecReturnSS(char cHead,char *cAddress,char *cCommand)
{
    bool bReturn=TRUE;
    char cChecksum[3];
    size_t j;
    char szRead[128];
    unsigned char cCheckCal=0;

    sprintf(szRead,"%c%s%sSS",cHead,cAddress,cCommand);
    cCheckCal=0;
    for(j=0; j<strlen(szRead); j++)
        cCheckCal+=szRead[j];
    sprintf(cChecksum,"%.2X",cCheckCal);
    strcat(szRead,cChecksum);
    strcat(szRead,"*");
#ifdef SHOW2
    char szCmd[128];
    sprintf(szCmd,"<- %s",szRead);
    To_Log_File(szCmd);
#endif
    memcpy(g_buffer+m_bufferlength,szRead,strlen(szRead));
    m_bufferlength+=strlen(szRead);

    return bReturn;
}

bool Win_QextSerialPort::doRecReturn851(char cHead,char *cAddress,int val03,int val04,int val05)
{
    bool bReturn=TRUE;
    char cChecksum[3];
    size_t j;
    char szRead[128];
    unsigned char cCheckCal=0;

    sprintf(szRead,"%c%s",cHead,cAddress);
    if(val03==0) strcat(szRead,"304");
        else if(val03==100) strcat(szRead,"303");
        else if(val03==80) strcat(szRead,"308");
        else if(val03==60) strcat(szRead,"307");
        else if(val03==40) strcat(szRead,"306");
        else if(val03==20) strcat(szRead,"305");
    if(0==(val04&0x1)) strcat(szRead,"353");
    else strcat(szRead,"354");
    if(0==(val04&0x4)) strcat(szRead,"355");
    else strcat(szRead,"356");

    if(val05&0x01) strcat(szRead,"351");
    else strcat(szRead,"352");
    if(val05&0x10) strcat(szRead,"357");
    else strcat(szRead,"358");
    if(val05&0x20) strcat(szRead,"357");
    else strcat(szRead,"360");
    if(val05&0x40) strcat(szRead,"361");
    else strcat(szRead,"362");

    if((val05&0x100)&&(val05&0x200)&&(val05&0x400)&&(val05&0x800)) strcat(szRead,"401");
    else if((val05&0x100)&&(val05&0x200)) strcat(szRead,"402");
    else if((val05&0x400)&&(val05&0x800)) strcat(szRead,"403");
    else if((val05&0x100)&&(val05&0x400)) strcat(szRead,"404");
    else if((val05&0x200)&&(val05&0x800)) strcat(szRead,"405");
    else strcat(szRead,"406");

    if(val05&0x1000) strcat(szRead,"451");
    else strcat(szRead,"452");
    if(val05&0x2000) strcat(szRead,"453");
    else strcat(szRead,"454");
    if(val05&0x4000) strcat(szRead,"455");
    else strcat(szRead,"456");
    if(val05&0x8000) strcat(szRead,"457");
    else strcat(szRead,"458");

    if(m_defTemperatureType==0) strcat(szRead,"901");
    else strcat(szRead,"902");

    if(m_defLutronType==0) strcat(szRead,"903");
    else if(m_defLutronType==1) strcat(szRead,"904");
    else strcat(szRead,"905");
    cCheckCal=0;
    for(j=0; j<strlen(szRead); j++)
        cCheckCal+=szRead[j];
    sprintf(cChecksum,"%.2X",cCheckCal);
    strcat(szRead,cChecksum);
    strcat(szRead,"*");
#ifdef SHOW2
    char szCmd[128];
    sprintf(szCmd,"<- %s",szRead);
    To_Log_File(szCmd);
#endif
    memcpy(g_buffer+m_bufferlength,szRead,strlen(szRead));
    m_bufferlength+=strlen(szRead);

    return bReturn;
}

bool Win_QextSerialPort::doRecReturn852(char cHead,char *cAddress,int val03,int val04,int val05)
{
    bool bReturn=TRUE;
    char cChecksum[3];
    size_t j;
    char szRead[128];
    unsigned char cCheckCal=0;

    sprintf(szRead,"%c%s",cHead,cAddress);
    if(val03==40) strcat(szRead,"312");
        else if(val03==200) strcat(szRead,"311");
        else if(val03==100) strcat(szRead,"313");
        else if(val03==130) strcat(szRead,"314");
        else if(val03==150) strcat(szRead,"315");
        else if(val03==180) strcat(szRead,"316");
    if(0==(val04&0x1)) strcat(szRead,"353");
    else strcat(szRead,"354");
    if(0==(val04&0x4)) strcat(szRead,"355");
    else strcat(szRead,"356");

    if(val05&0x01) strcat(szRead,"351");
    else strcat(szRead,"352");
    if(val05&0x10) strcat(szRead,"357");
    else strcat(szRead,"358");
    if(val05&0x20) strcat(szRead,"357");
    else strcat(szRead,"360");
    if(val05&0x40) strcat(szRead,"361");
    else strcat(szRead,"362");

    if((val05&0x100)&&(val05&0x200)&&(val05&0x400)&&(val05&0x800)) strcat(szRead,"401");
    else if((val05&0x100)&&(val05&0x200)) strcat(szRead,"402");
    else if((val05&0x400)&&(val05&0x800)) strcat(szRead,"403");
    else if((val05&0x100)&&(val05&0x400)) strcat(szRead,"404");
    else if((val05&0x200)&&(val05&0x800)) strcat(szRead,"405");
    else strcat(szRead,"406");

    if(val05&0x1000) strcat(szRead,"451");
    else strcat(szRead,"452");
    if(val05&0x2000) strcat(szRead,"453");
    else strcat(szRead,"454");
    if(val05&0x4000) strcat(szRead,"455");
    else strcat(szRead,"456");
    if(val05&0x8000) strcat(szRead,"457");
    else strcat(szRead,"458");

    if(m_defTemperatureType==0) strcat(szRead,"901");
    else strcat(szRead,"902");

    if(m_defLutronType==0) strcat(szRead,"903");
    else if(m_defLutronType==1) strcat(szRead,"904");
    else strcat(szRead,"905");
    cCheckCal=0;
    for(j=0; j<strlen(szRead); j++)
        cCheckCal+=szRead[j];
    sprintf(cChecksum,"%.2X",cCheckCal);
    strcat(szRead,cChecksum);
    strcat(szRead,"*");
#ifdef SHOW2
    char szCmd[128];
    sprintf(szCmd,"<- %s",szRead);
    To_Log_File(szCmd);
#endif
    memcpy(g_buffer+m_bufferlength,szRead,strlen(szRead));
    m_bufferlength+=strlen(szRead);

    return bReturn;
}
bool Win_QextSerialPort::doRecTemperature(char cHead,char *cAddress,int iType)
{
    DWORD dataSize=0,dwSend;

    bool bReturn=TRUE;
    char cChecksum[3];
    unsigned char cCheckCal=0;


    dataSize=sizeSukon();
    if(dataSize>0)
    {
        char szRead[128];
        char cPN;
        char cCF;
        size_t j;
        float fRead;
        if(dataSize>(128-1)) dataSize=128-1;
        ReadFile(Win_Handle, (void*)(szRead), (DWORD)dataSize, & dwSend, NULL);
        szRead[dwSend]=0;
#ifdef SHOW4
        char szCmd[128];
        sprintf(szCmd,"%s <-",szRead);
        To_Log_File(szCmd);
#endif


        sscanf(szRead,">%f\r",&fRead);
        if((3!=iType)&&(4!=iType))
        {
            fRead-=4;
            fRead*=31.25;
            fRead-=100;
        }
        if(fRead>0)
            cPN='P';
        else
        {
            cPN='N';
            fRead*=-1;
        }
        if(((0==m_defTemperatureType)&&(0==iType))||(1==iType)||(3==iType))
            cCF='C';
        else
        {
            cCF='F';
            fRead*=9;
            fRead/=5;
            fRead+=32;
        }
        if((3!=iType)&&(4!=iType))
        {
            sprintf(szRead,"%c%s%c%c%d",cHead,cAddress,cCF,cPN,(int)fRead);
        }
        else
        {
            sprintf(szRead,"%c%s%c%c%.1f",cHead,cAddress,cCF,cPN,fRead);
        }
        cCheckCal=0;
        for(j=0; j<strlen(szRead); j++)
            cCheckCal+=szRead[j];
        sprintf(cChecksum,"%.2X",cCheckCal);
        strcat(szRead,cChecksum);
        strcat(szRead,"*");
#ifdef SHOW2
        char szCmdx[128];
        sprintf(szCmdx,"<- %s",szRead);
        To_Log_File(szCmdx);
#endif
        memcpy(g_buffer+m_bufferlength,szRead,strlen(szRead));
        m_bufferlength+=strlen(szRead);
    }
    else
        bReturn=false;

    return bReturn;
}

bool Win_QextSerialPort::doRecHumidity(char cHead,char *cAddress ,int iType)
{
    DWORD dataSize=0,dwSend;
    bool bReturn=TRUE;
    char cChecksum[3];
    unsigned char cCheckCal=0;

    dataSize=sizeSukon();
    if(dataSize>0)
    {
        char szRead[128];
        char cPN;
        size_t j;
        float fRead;
        if(dataSize>(128-1)) dataSize=128-1;
        ReadFile(Win_Handle, (void*)(szRead), (DWORD)dataSize, & dwSend, NULL);
        szRead[dwSend]=0;
#ifdef SHOW4
        char szCmd[128];
        sprintf(szCmd,"%s <-",szRead);
        To_Log_File(szCmd);
#endif
        sscanf(szRead,">%f\r",&fRead);
        if(0 == iType)
        {
            fRead-=5.6;
            fRead*=6.25;
            fRead+=10;
        }
        cPN='H';
        if(0 == iType)
        {
            sprintf(szRead,"%c%s%c%d",cHead,cAddress,cPN,(int)fRead);
        }
        else
        {
            sprintf(szRead,"%c%s%c%.1f",cHead,cAddress,cPN,fRead);
        }
        cCheckCal=0;
        for(j=0; j<strlen(szRead); j++)
            cCheckCal+=szRead[j];
        sprintf(cChecksum,"%.2X",cCheckCal);
        strcat(szRead,cChecksum);
        strcat(szRead,"*");
#ifdef SHOW2
        char szCmdx[128];
        sprintf(szCmdx,"<- %s",szRead);
        To_Log_File(szCmdx);
#endif
        memcpy(g_buffer+m_bufferlength,szRead,strlen(szRead));
        m_bufferlength+=strlen(szRead);
    }
    else
        bReturn=false;

    return bReturn;
}

bool Win_QextSerialPort::doRecIlluminance(char cHead,char *cAddress)
{
    DWORD dataSize=0,dwSend;
    bool bReturn=TRUE;
    char cChecksum[3];
    unsigned char cCheckCal=0;

    dataSize=sizeSukon();
    if(dataSize>0)
    {
        char szRead[128];

        char cPN=0;
        size_t j;
        float fRead;
        if(dataSize>(128-1)) dataSize=128-1;
        ReadFile(Win_Handle, (void*)(szRead), (DWORD)dataSize, & dwSend, NULL);
        szRead[dwSend]=0;
#ifdef SHOW4
        char szCmd[128];
        sprintf(szCmd,"%s <-",szRead);
        To_Log_File(szCmd);
#endif
        sscanf(szRead,">%f\r",&fRead);
        if(0==m_defLutronType)
        {
            fRead-=4;
            fRead*=125;
            cPN='A';
        }
        else if(1==m_defLutronType)
        {
            fRead-=5.6;
            fRead*=1250;
            fRead+=2000;
            cPN='B';
        }
        else if(2==m_defLutronType)
        {
            fRead-=10.6;
            fRead*=3125;
            fRead+=20000;
                        cPN='D';
        }

        sprintf(szRead,"%c%s%c%d",cHead,cAddress,cPN,(int)fRead);
        cCheckCal=0;
        for(j=0; j<strlen(szRead); j++)
            cCheckCal+=szRead[j];
        sprintf(cChecksum,"%.2X",cCheckCal);
        strcat(szRead,cChecksum);
        strcat(szRead,"*");
#ifdef SHOW2
        char szCmdx[128];
        sprintf(szCmdx,"<- %s",szRead);
        To_Log_File(szCmdx);
#endif
        memcpy(g_buffer+m_bufferlength,szRead,strlen(szRead));
        m_bufferlength+=strlen(szRead);
    }
    else
        bReturn=false;

    return bReturn;
}

int Win_QextSerialPort::doRecReturnVIN(void)
{
    DWORD dataSize=0,dwSend;
    float fReturn=0;
        int bReturn=0;

    dataSize=sizeSukon();
   //     dataSize=10;
    if(dataSize>0)
    {
        char szRead[128];
        if(dataSize>(128-1)) dataSize=128-1;
        ReadFile(Win_Handle, (void*)(szRead), (DWORD)dataSize, & dwSend, NULL);
        szRead[dwSend]=0;
      //          strcpy(szRead,"!03+03.300\r");
#ifdef SHOW4
        char szCmd[128];
        sprintf(szCmd,"%s <-",szRead);
        To_Log_File(szCmd);
#endif
        sscanf(szRead,"!03+%f\r",&fReturn);
        fReturn*=10;
        bReturn=(int)fReturn;
    }

    return bReturn;
}

int Win_QextSerialPort::doRecReturnGIN(void)
{
    DWORD dataSize=0,dwSend;
    int bReturn=0xffff;

    dataSize=sizeSukon();
    if(dataSize>0)
    {
        char szRead[128];
        if(dataSize>(128-1)) dataSize=128-1;
        ReadFile(Win_Handle, (void*)(szRead), (DWORD)dataSize, & dwSend, NULL);
        szRead[dwSend]=0;
#ifdef SHOW4
        char szCmd[128];
        sprintf(szCmd,"%s <-",szRead);
        To_Log_File(szCmd);
#endif
        sscanf(szRead,">%x\r",&bReturn);
    }

    return bReturn;
}


void Win_QextSerialPort::StartStop(void)
{
    int l,i;
    if(m_vFan1!=m_vFan2)
    {
        char cCommand[128];
        if(m_vFan1>m_vFan2)
        {
            m_vFan2++;
        }
        else if(m_vFan1<m_vFan2)
        {
            m_vFan2--;
        }
        sprintf(cCommand,"0+%02d.%01d00",m_vFan2/10,m_vFan2-(m_vFan2/10*10));
        doSendCommand((char*)"#",gcAddress303,cCommand);

        if(m_vFan1==m_vFan2)
            doRecReturn(gcHead303,gcAddress303,gcCommand303);
        else
            doRecReturnNULL();
    }

    for(i=0; i<MaxCmd; i++)
    {
        if(true==bwBosswin[i].isUse)
        {
                char cHead;
                char cAddress[3];
                char cCommand[5];
                cHead=bwBosswin[i].Head;
                strcpy(cAddress,bwBosswin[i].Address);
                strcpy(cCommand,bwBosswin[i].Command);
                for(l=0; l<MaxCmd; l++)
                {

                    if(0==strcmp(BossWinCommand[l][0],cCommand))
                    {

                        if(0==strcmp(BossWinCommand[l][3],"GET_S"))
                        {
                            sscanf(BossWinCommand[l][2],"%d",&m_vFan1);

                            if(m_vFan1!=m_vFan2)
                            {
        #ifdef SHOW1
                                char szCmd[128];
                                sprintf(szCmd,"start: %c%s%s",cHead,cAddress,cCommand);
                                To_Log_File(szCmd);
        #endif
                                gcHead303=cHead;
                                strcpy(gcAddress303,cAddress);
                                strcpy(gcCommand303,cCommand);
                            }
                            else
                            {
        #ifdef SHOW1
                                char szCmd[128];
                                sprintf(szCmd,"same: %c%s%s",cHead,cAddress,cCommand);
                                To_Log_File(szCmd);
        #endif
                                doRecReturnX(cHead,cAddress,cCommand,1);
                            }
                        }
                        else if(0==strcmp(BossWinCommand[l][3],"GET_I"))
                        {
                            sscanf(BossWinCommand[l][2],"%d",&m_iFan1);

                            if(m_iFan1!=m_iFan2)
                            {
        #ifdef SHOW1
                                char szCmd[128];
                                sprintf(szCmd,"start: %c%s%s",cHead,cAddress,cCommand);
                                To_Log_File(szCmd);
        #endif
                                gcHead303=cHead;
                                strcpy(gcAddress303,cAddress);
                                strcpy(gcCommand303,cCommand);
                            }
                            else
                            {
        #ifdef SHOW1
                                char szCmd[128];
                                sprintf(szCmd,"same: %c%s%s",cHead,cAddress,cCommand);
                                To_Log_File(szCmd);
        #endif
                                doRecReturnX(cHead,cAddress,cCommand,1);
                            }
                        }
                        else
                        {
                            if(! doSendCommand(BossWinCommand[l][1],cAddress,BossWinCommand[l][2]))
                                doRecReturnX(cHead,cAddress,cCommand,0);
                            if(0==strcmp(BossWinCommand[l][3],"GET_R"))
                                doRecReturn(cHead,cAddress,cCommand);
                            else if(0==strcmp(BossWinCommand[l][3],"GET_T"))
                                doRecTemperature(cHead,cAddress,0);
                            else if(0==strcmp(BossWinCommand[l][3],"GET_TC"))
                                doRecTemperature(cHead,cAddress,1);
                            else if(0==strcmp(BossWinCommand[l][3],"GET_TF"))
                                doRecTemperature(cHead,cAddress,2);
                            else if(0==strcmp(BossWinCommand[l][3],"GET_T2C"))
                                doRecTemperature(cHead,cAddress,3);
                            else if(0==strcmp(BossWinCommand[l][3],"GET_T2F"))
                                doRecTemperature(cHead,cAddress,4);
                            else if(0==strcmp(BossWinCommand[l][3],"GET_H"))
                                doRecHumidity(cHead,cAddress,0);
                            else if(0==strcmp(BossWinCommand[l][3],"GET_H2"))
                                doRecHumidity(cHead,cAddress,1);
                            else if(0==strcmp(BossWinCommand[l][3],"GET_B2"))
                                doRecIlluminance(cHead,cAddress);
                         }
                         break;
                    }
                }
                if(MaxCmd==l)
                {
                        if(0==strcmp("010",cCommand))
                        {
                                doSendCommand((char*)"#",cAddress,(char*)"4");
                                doRecTemperature(cHead,cAddress,0);
                                doSendCommand((char*)"#",cAddress,(char*)"5");
                                doRecTemperature(cHead,cAddress,0);
                                doSendCommand((char*)"#",cAddress,(char*)"6");
                                doRecTemperature(cHead,cAddress,0);
                                doSendCommand((char*)"#",cAddress,(char*)"7");
                                doRecTemperature(cHead,cAddress,0);

                        }
                        else if(0==strcmp("014",cCommand))
                        {
                                doSendCommand((char*)"#",cAddress,(char*)"C0TC");
                                doRecTemperature(cHead,cAddress,3);

                                doSendCommand((char*)"#",cAddress,(char*)"C0H");
                                doRecHumidity(cHead,cAddress,1);
                        }
                        else if(0==strcmp("015",cCommand))
                        {
                                doSendCommand((char*)"#",cAddress,(char*)"C0TC");
                                doRecTemperature(cHead,cAddress,4);

                                doSendCommand((char*)"#",cAddress,(char*)"C0H");
                                doRecHumidity(cHead,cAddress,1);
                        }
                        else if(0==strcmp("004",cCommand))
                        {

                                doSendCommand((char*)"#",cAddress,(char*)"0");
                                doRecTemperature(cHead,cAddress,0);
                                doSendCommand((char*)"#",cAddress,(char*)"1");
                                doRecHumidity(cHead,cAddress,0);
                                doSendCommand((char*)"#",cAddress,(char*)"2");
                                doRecIlluminance(cHead,cAddress);

                        }
                        else if(0==strcmp("353",cCommand))
                        {

                                if(m_table1ON)
                                {
                                        m_table1ON=0;
                                        doSendCommand((char*)"#",cAddress,(char*)"A100");
                                }
                                if(m_table1OFF)
                                {
                                        m_table1OFF=0;
                                        doSendCommand((char*)"#",cAddress,(char*)"A200");
                                }
                                doSendCommand((char*)"#",cAddress,(char*)"A101");

                                m_table1ON=1;
                                gcHead353=cHead;
                                strcpy(gcAddress353,cAddress);
                                strcpy(gcCommand353,cCommand);
                                doRecReturnNULL();

                        }
                        else if(0==strcmp("354",cCommand))
                        {

                                if(m_table1ON)
                                {
                                        m_table1ON=0;
                                        doSendCommand((char*)"#",cAddress,(char*)"A100");
                                }
                                if(m_table1OFF)
                                {
                                        m_table1OFF=0;
                                        doSendCommand((char*)"#",cAddress,(char*)"A200");
                                }
                                doSendCommand((char*)"#",cAddress,(char*)"A201");
                                m_table1OFF=1;
                                gcHead354=cHead;
                                strcpy(gcAddress354,cAddress);
                                strcpy(gcCommand354,cCommand);
                                doRecReturnNULL();

                        }
                        else if(0==strcmp("355",cCommand))
                        {
                                if(m_table2ON)
                                {
                                        m_table2ON=0;
                                        doSendCommand((char*)"#",cAddress,(char*)"A300");
                                }
                                if(m_table2OFF)
                                {
                                        m_table2OFF=0;
                                        doSendCommand((char*)"#",cAddress,(char*)"A400");
                                }
                                doSendCommand((char*)"#",cAddress,(char*)"A301");
                                m_table2ON=1;
                                gcHead355=cHead;
                                strcpy(gcAddress355,cAddress);
                                strcpy(gcCommand355,cCommand);
                                doRecReturnNULL();

                        }
                        else if(0==strcmp("356",cCommand))
                        {
                                if(m_table2ON)
                                {
                                        m_table2ON=0;
                                        doSendCommand((char*)"#",cAddress,(char*)"A300");
                                }
                                if(m_table2OFF)
                                {
                                        m_table2OFF=0;
                                        doSendCommand((char*)"#",cAddress,(char*)"A400");
                                }
                                doSendCommand((char*)"#",cAddress,(char*)"A401");
                                m_table2OFF=1;
                                gcHead356=cHead;
                                strcpy(gcAddress356,cAddress);
                                strcpy(gcCommand356,cCommand);
                                doRecReturnNULL();
                        }
                        else if(0==strcmp("401",cCommand))
                        {

                                doSendCommand((char*)"#",cAddress,(char*)"B001");
                                doSendCommand((char*)"#",cAddress,(char*)"B101");
                                doSendCommand((char*)"#",cAddress,(char*)"B201");
                                doSendCommand((char*)"#",cAddress,(char*)"B301");
                                doRecReturn(cHead,cAddress,cCommand);

                        }
                        else if(0==strcmp("402",cCommand))
                        {

                                doSendCommand((char*)"#",cAddress,(char*)"B001");
                                doSendCommand((char*)"#",cAddress,(char*)"B101");
                                doSendCommand((char*)"#",cAddress,(char*)"B200");
                                doSendCommand((char*)"#",cAddress,(char*)"B300");
                                doRecReturn(cHead,cAddress,cCommand);

                        }
                        else if(0==strcmp("403",cCommand))
                        {
                                doSendCommand((char*)"#",cAddress,(char*)"B000");
                                doSendCommand((char*)"#",cAddress,(char*)"B100");
                                doSendCommand((char*)"#",cAddress,(char*)"B201");
                                doSendCommand((char*)"#",cAddress,(char*)"B301");
                                doRecReturn(cHead,cAddress,cCommand);
                        }
                        else if(0==strcmp("404",cCommand))
                        {
                                doSendCommand((char*)"#",cAddress,(char*)"B001");
                                doSendCommand((char*)"#",cAddress,(char*)"B100");
                                doSendCommand((char*)"#",cAddress,(char*)"B201");
                                doSendCommand((char*)"#",cAddress,(char*)"B300");
                                doRecReturn(cHead,cAddress,cCommand);
                        }
                        else if(0==strcmp("405",cCommand))
                        {
                                doSendCommand((char*)"#",cAddress,(char*)"B000");
                                doSendCommand((char*)"#",cAddress,(char*)"B101");
                                doSendCommand((char*)"#",cAddress,(char*)"B200");
                                doSendCommand((char*)"#",cAddress,(char*)"B301");
                                doRecReturn(cHead,cAddress,cCommand);
                        }
                        else if(0==strcmp("406",cCommand))
                        {
                                doSendCommand((char*)"#",cAddress,(char*)"B000");
                                doSendCommand((char*)"#",cAddress,(char*)"B100");
                                doSendCommand((char*)"#",cAddress,(char*)"B200");
                                doSendCommand((char*)"#",cAddress,(char*)"B300");
                                doRecReturn(cHead,cAddress,cCommand);
                        }
                        else if(0==strcmp("901",cCommand))
                        {
                                m_defTemperatureType=0;
                                doRecReturnSS(cHead,cAddress,cCommand);
                        }
                        else if(0==strcmp("902",cCommand))
                        {
                                m_defTemperatureType=1;
                                doRecReturnSS(cHead,cAddress,cCommand);
                        }
                        else if(0==strcmp("903",cCommand))
                        {
                                m_defLutronType=0;
                                doRecReturnSS(cHead,cAddress,cCommand);
                        }
                        else if(0==strcmp("904",cCommand))
                        {
                                m_defLutronType=1;
                                doRecReturnSS(cHead,cAddress,cCommand);
                        }
                        else if(0==strcmp("905",cCommand))
                        {
                                m_defLutronType=2;
                                doRecReturnSS(cHead,cAddress,cCommand);
                        }
                        else if(0==strcmp("851",cCommand))
                        {
                                int iReturnValA05,iReturnValA04,iReturnValA03;
                                doSendCommand((char*)"$",(char*)"03",(char*)"80");
                                iReturnValA03=doRecReturnVIN();
                                m_vFan2=iReturnValA03;
                                strcpy(gcAddress303,"03");
                                doSendCommand((char*)"@",(char*)"04",(char*)"");
                                iReturnValA04=doRecReturnGIN();
                                doSendCommand((char*)"@",(char*)"05",(char*)"");
                                iReturnValA05=doRecReturnGIN();
                                doRecReturn851(cHead,cAddress,m_vFan1,iReturnValA04,iReturnValA05);
                        }
                        else if(0==strcmp("852",cCommand))
                        {
                                int iReturnValA05,iReturnValA04,iReturnValA03;
                                doSendCommand((char*)"$",(char*)"03",(char*)"80");
                                iReturnValA03=doRecReturnVIN();
                                m_iFan2=iReturnValA03;
                                strcpy(gcAddress303,"03");
                                doSendCommand((char*)"@",(char*)"04",(char*)"");
                                iReturnValA04=doRecReturnGIN();
                                doSendCommand((char*)"@",(char*)"05",(char*)"");
                                iReturnValA05=doRecReturnGIN();
                                doRecReturn852(cHead,cAddress,m_iFan1,iReturnValA04,iReturnValA05);
                        }
                }
#ifdef SHOW1
                char szCmd[128];
                sprintf(szCmd,"cmd: %s is end at %d",cCommand,i);
                To_Log_File(szCmd);
#endif
                bwBosswin[i].isUse=false;
        }
    }
    gTimer++;
    if(gTimer<3)
    {
        return;
    }
    if(m_iFan1!=m_iFan2)
    {
        char cCommand[128];
        if(m_iFan1>m_iFan2)
        {
            m_iFan2+=5;
        }
        else if(m_iFan1<m_iFan2)
        {
            m_iFan2-=5;
        }
        sprintf(cCommand,"0+%02d.%01d00",m_iFan2/10,m_iFan2-(m_iFan2/10*10));
        doSendCommand((char*)"#",gcAddress303,cCommand);

        if(m_iFan1==m_iFan2)
            doRecReturn(gcHead303,gcAddress303,gcCommand303);
        else
            doRecReturnNULL();
    }
    if(gTimer<7)
    {
        return;
    }
    gTimer=0;
    if(m_table1ON)
    {
        m_table1ON++;
//       LOCK_MUTEX();
        if(m_table1ON==3)
        {

            doSendCommand((char*)"#",gcAddress353,(char*)"A100");
            doRecReturnNULL();

        }
        if(m_table1ON>30)
        {

            doRecReturnX(gcHead353,gcAddress353,gcCommand353,0);
            doSendCommand((char*)"#",gcAddress353,(char*)"A100");
            doRecReturnNULL();

            m_table1ON=0;
        }
        else
        {

            doSendCommand((char*)"@",(char*)"04",(char*)"");

            if(0==(doRecReturnGIN()&0x1))
            {
                doRecReturnX(gcHead353,gcAddress353,gcCommand353,1);
                doSendCommand((char*)"#",gcAddress353,(char*)"A100");
                doRecReturnNULL();
                m_table1ON=0;
            }

        }
//       UNLOCK_MUTEX();
    }
    if(m_table1OFF)
    {
        m_table1OFF++;
//        LOCK_MUTEX();
        if(m_table1OFF==3)
        {
            doSendCommand((char*)"#",gcAddress354,(char*)"A200");
            doRecReturnNULL();
        }
        if(m_table1OFF>30)
        {
            doRecReturnX(gcHead354,gcAddress354,gcCommand354,0);
            doSendCommand((char*)"#",gcAddress354,(char*)"A200");
            doRecReturnNULL();
            m_table1OFF=0;
        }
        else
        {
            doSendCommand((char*)"@",(char*)"04",(char*)"");

            if(0==(doRecReturnGIN()&0x2))
            {
                doRecReturnX(gcHead354,gcAddress354,gcCommand354,1);
                doSendCommand((char*)"#",gcAddress354,(char*)"A200");
                doRecReturnNULL();
                m_table1OFF=0;
            }
        }
                //      UNLOCK_MUTEX();
    }
    if(m_table2ON)
    {
        //
        m_table2ON++;
                //    LOCK_MUTEX();
        if(m_table2ON==3)
        {
            doSendCommand((char*)"#",gcAddress355,(char*)"A300");
            doRecReturnNULL();
        }
        if(m_table2ON>30)
        {
            doRecReturnX(gcHead355,gcAddress355,gcCommand355,0);
            doSendCommand((char*)"#",gcAddress355,(char*)"A300");
            doRecReturnNULL();
            m_table2ON=0;
        }
        else
        {
            doSendCommand((char*)"@",(char*)"04",(char*)"");

            if(0==(doRecReturnGIN()&0x4))
            {
                doRecReturnX(gcHead355,gcAddress355,gcCommand355,1);
                doSendCommand((char*)"#",gcAddress355,(char*)"A300");
                doRecReturnNULL();
                m_table2ON=0;
            }
        }
                //    UNLOCK_MUTEX();
    }
    if(m_table2OFF)
    {
        m_table2OFF++;
                //    LOCK_MUTEX();
        if(m_table2OFF==3)
        {
            doSendCommand((char*)"#",gcAddress356,(char*)"A400");
            doRecReturnNULL();
        }
        if(m_table2OFF>30)
        {
            doRecReturnX(gcHead356,gcAddress356,gcCommand356,0);
            doSendCommand((char*)"#",gcAddress356,(char*)"A400");
            doRecReturnNULL();
            m_table2OFF=0;
        }
        else
        {
            doSendCommand((char*)"@",(char*)"04",(char*)"");

            if(0==(doRecReturnGIN()&0x8))
            {
                doRecReturnX(gcHead356,gcAddress356,gcCommand356,1);
                doSendCommand((char*)"#",gcAddress356,(char*)"A400");
                doRecReturnNULL();
                m_table2OFF=0;
            }
        }
                //     UNLOCK_MUTEX();
    }


}



qint64 Win_QextSerialPort::writeData(const char *data, qint64 maxSize)
{
    DWORD retVal;

    int i;
    INT32 retStatus=1;
    char cHead=0;
    char cAddress[3];
    char cCommand[5];
    char cChecksum[3];
    static unsigned short tempByteCount;

    deliverState=START;
    retVal=0;

    for(i=0; i<maxSize; i++)
    {
#ifdef SHOW1
              //      char szCmd[128];
              ////      sprintf(szCmd,"i:%d deliverState:%d char:%c maxSize:%d",i,deliverState,data[i],maxSize);
              //      To_Log_File(szCmd);
#endif
        switch(deliverState)
        {
            case START:
        //    To_Log_File("step1");
                if((data[i] == USER1_STX0)||(data[i] == USER1_STX1)||(data[i] == USER1_STX2)||(data[i] == USER1_STX3))
                {
               //     To_Log_File("step2");
                    cHead=data[i];
                    deliverState = ADDRESS;
                    tempByteCount=0;
               //     To_Log_File("step21");
                }
                else
                {
                  //  To_Log_File("step3");

                    retStatus = FAILURE;
                }
                break;

            case ADDRESS:
                //To_Log_File("step4");

                if(USER1_ETX0 == data[i])
                {
                //    To_Log_File("step5");

                    deliverState = START;
                    break;
                }
               // To_Log_File("step6");

                cAddress[tempByteCount]=data[i];
                if(++tempByteCount == 2)
                {
                    cAddress[tempByteCount]=0;
                    deliverState = COMMAND;
                    tempByteCount = 0;
                }
                break;
            case COMMAND:
                if(USER1_ETX0 == data[i])
                {
                    deliverState = START;
                    break;
                }
                cCommand[tempByteCount]=data[i];
                tempByteCount++;
                if(((tempByteCount == 3)&&('C'!=cCommand[0])&&('F'!=cCommand[0]))||(tempByteCount == 4))
                {
                    cCommand[tempByteCount]=0;
                    deliverState = CHECKSUM;
                    tempByteCount = 0;
                }

                break;
            case CHECKSUM:
                if(USER1_ETX0 == data[i])
                {
                    deliverState = START;
                    break;
                }
                cChecksum[tempByteCount]=data[i];
                if(++tempByteCount == 2)
                {
                    cChecksum[tempByteCount]=0;
                    deliverState = END;
                    tempByteCount = 0;
                }
                break;
            case END:
                if(USER1_ETX0 == data[i])
                {

                    unsigned char cCheckCal=0;
                    unsigned int iChecksumVal;
                    int l;

                    cCheckCal+=cHead;
                    cCheckCal+=cAddress[0];
                    cCheckCal+=cAddress[1];
                    cCheckCal+=cCommand[0];
                    cCheckCal+=cCommand[1];
                    cCheckCal+=cCommand[2];
                    sscanf(cChecksum,"%x",&iChecksumVal);
                    if(cCheckCal != (unsigned char)iChecksumVal)
                    {
//                        retStatus = FAILURE;
//                        break;
                    }
#ifdef SHOW1
                    char szCmd[128];
                    sprintf(szCmd,"-> %c%s%s%s*",cHead,cAddress,cCommand,cChecksum);
                    To_Log_File(szCmd);
#endif
                                        for(l=0; l<MaxCmd; l++)
                                        {
                                            if(!bwBosswin[l].isUse)
                                            {
#ifdef SHOW1
                char szCmd[128];
                sprintf(szCmd,"cmd: %s is start at %d",cCommand,l);
                To_Log_File(szCmd);
#endif
                                                LOCK_MUTEX();
                                                bwBosswin[l].Head=cHead;
                                                strcpy(bwBosswin[l].Address,cAddress);
                                                strcpy(bwBosswin[l].Command,cCommand);
                                                bwBosswin[l].isUse=true;
                                                UNLOCK_MUTEX();
                                                break;
                                            }
                                        }
                                        if(MaxCmd==l)
                                        {
#ifdef SHOW1
                                            char szCmd[128];
                                            sprintf(szCmd,"buffer full!");
                                            To_Log_File(szCmd);
#endif
                                        }


                    deliverState = START;
                                        retVal+=(6+strlen(cCommand)); //9 or 10
                }
                else
                    retStatus = FAILURE;
                break;
            default:
             //   To_Log_File("step9");
                //PRINTF("#! INVALID INTERNAL ERROR IN user1_Deliver");
                break;
        }
        //To_Log_File("stepx1");
        if(retStatus == FAILURE)
        {
       //     To_Log_File("stepx2");
            deliverState = START;
            //PRINTF(" Error in parsing the buffer received from IoStream");
            break;
        }
       // To_Log_File("stepx3");
    }

    return (qint64)retVal;
}

/*!
\fn void Win_QextSerialPort::ungetChar(char c)
This function is included to implement the full QIODevice interface, and currently has no
purpose within this class.  This function is meaningless on an unbuffered device and currently
only prints a warning message to that effect.
*/
void Win_QextSerialPort::ungetChar(char c)
{

    /*meaningless on unbuffered sequential device - return error and print a warning*/
    TTY_WARNING("Win_QextSerialPort: ungetChar() called on an unbuffered sequential device - operation is meaningless");
}

/*!
\fn void Win_QextSerialPort::setFlowControl(FlowType flow)
Sets the flow control used by the port.  Possible values of flow are:
\verbatim
    FLOW_OFF            No flow control
    FLOW_HARDWARE       Hardware (RTS/CTS) flow control
    FLOW_XONXOFF        Software (XON/XOFF) flow control
\endverbatim
*/
void Win_QextSerialPort::setFlowControl(FlowType flow)
{
        LOCK_MUTEX();
    if (Settings.FlowControl!=flow)
    {
        Settings.FlowControl=flow;
    }
//   if (isOpen())
    {
        switch(flow)
        {

                /*no flow control*/
            case FLOW_OFF:
                Win_CommConfig.dcb.fOutxCtsFlow=FALSE;
                Win_CommConfig.dcb.fRtsControl=RTS_CONTROL_DISABLE;
                Win_CommConfig.dcb.fInX=FALSE;
                Win_CommConfig.dcb.fOutX=FALSE;
                SetCommConfig(Win_Handle, &Win_CommConfig, sizeof(COMMCONFIG));
                break;

                /*software (XON/XOFF) flow control*/
            case FLOW_XONXOFF:
                Win_CommConfig.dcb.fOutxCtsFlow=FALSE;
                Win_CommConfig.dcb.fRtsControl=RTS_CONTROL_DISABLE;
                Win_CommConfig.dcb.fInX=TRUE;
                Win_CommConfig.dcb.fOutX=TRUE;
                SetCommConfig(Win_Handle, &Win_CommConfig, sizeof(COMMCONFIG));
                break;

            case FLOW_HARDWARE:
                Win_CommConfig.dcb.fOutxCtsFlow=TRUE;
                Win_CommConfig.dcb.fRtsControl=RTS_CONTROL_HANDSHAKE;
                Win_CommConfig.dcb.fInX=FALSE;
                Win_CommConfig.dcb.fOutX=FALSE;
                SetCommConfig(Win_Handle, &Win_CommConfig, sizeof(COMMCONFIG));
                break;
        }
    }
        UNLOCK_MUTEX();
}

/*!
\fn void Win_QextSerialPort::setParity(ParityType parity)
Sets the parity associated with the serial port.  The possible values of parity are:
\verbatim
    PAR_SPACE       Space Parity
    PAR_MARK        Mark Parity
    PAR_NONE        No Parity
    PAR_EVEN        Even Parity
    PAR_ODD         Odd Parity
\endverbatim
*/
void Win_QextSerialPort::setParity(ParityType parity)
{
        LOCK_MUTEX();
    if (Settings.Parity!=parity)
    {
        Settings.Parity=parity;
    }
    //  if (isOpen())
    {
        Win_CommConfig.dcb.Parity=(unsigned char)parity;
        switch (parity)
        {

                /*space parity*/
            case PAR_SPACE:
                if (Settings.DataBits==DATA_8)
                {
                    TTY_PORTABILITY_WARNING("Win_QextSerialPort Portability Warning: Space parity with 8 data bits is not supported by POSIX systems.");
                }
                Win_CommConfig.dcb.fParity=TRUE;
                break;

                /*mark parity - WINDOWS ONLY*/
            case PAR_MARK:
                TTY_PORTABILITY_WARNING("Win_QextSerialPort Portability Warning:  Mark parity is not supported by POSIX systems");
                Win_CommConfig.dcb.fParity=TRUE;
                break;

                /*no parity*/
            case PAR_NONE:
                Win_CommConfig.dcb.fParity=FALSE;
                break;

                /*even parity*/
            case PAR_EVEN:
                Win_CommConfig.dcb.fParity=TRUE;
                break;

                /*odd parity*/
            case PAR_ODD:
                Win_CommConfig.dcb.fParity=TRUE;
                break;
        }
        SetCommConfig(Win_Handle, &Win_CommConfig, sizeof(COMMCONFIG));
    }
        UNLOCK_MUTEX();
}

/*!
\fn void Win_QextSerialPort::setDataBits(DataBitsType dataBits)
Sets the number of data bits used by the serial port.  Possible values of dataBits are:
\verbatim
    DATA_5      5 data bits
    DATA_6      6 data bits
    DATA_7      7 data bits
    DATA_8      8 data bits
\endverbatim

\note
This function is subject to the following restrictions:
\par
    5 data bits cannot be used with 2 stop bits.
\par
    1.5 stop bits can only be used with 5 data bits.
\par
    8 data bits cannot be used with space parity on POSIX systems.

*/
void Win_QextSerialPort::setDataBits(DataBitsType dataBits)
{
        LOCK_MUTEX();
    if (Settings.DataBits!=dataBits)
    {
        if ((Settings.StopBits==STOP_2 && dataBits==DATA_5) ||
                (Settings.StopBits==STOP_1_5 && dataBits!=DATA_5))
        {
        }
        else
        {
            Settings.DataBits=dataBits;
        }
    }
//   if (isOpen())
    {
        switch(dataBits)
        {

                /*5 data bits*/
            case DATA_5:
                if (Settings.StopBits==STOP_2)
                {
                    TTY_WARNING("Win_QextSerialPort: 5 Data bits cannot be used with 2 stop bits.");
                }
                else
                {
                    Win_CommConfig.dcb.ByteSize=5;
                    SetCommConfig(Win_Handle, &Win_CommConfig, sizeof(COMMCONFIG));
                }
                break;

                /*6 data bits*/
            case DATA_6:
                if (Settings.StopBits==STOP_1_5)
                {
                    TTY_WARNING("Win_QextSerialPort: 6 Data bits cannot be used with 1.5 stop bits.");
                }
                else
                {
                    Win_CommConfig.dcb.ByteSize=6;
                    SetCommConfig(Win_Handle, &Win_CommConfig, sizeof(COMMCONFIG));
                }
                break;

                /*7 data bits*/
            case DATA_7:
                if (Settings.StopBits==STOP_1_5)
                {
                    TTY_WARNING("Win_QextSerialPort: 7 Data bits cannot be used with 1.5 stop bits.");
                }
                else
                {
                    Win_CommConfig.dcb.ByteSize=7;
                    SetCommConfig(Win_Handle, &Win_CommConfig, sizeof(COMMCONFIG));
                }
                break;

                /*8 data bits*/
            case DATA_8:
                if (Settings.StopBits==STOP_1_5)
                {
                    TTY_WARNING("Win_QextSerialPort: 8 Data bits cannot be used with 1.5 stop bits.");
                }
                else
                {
                    Win_CommConfig.dcb.ByteSize=8;
                    SetCommConfig(Win_Handle, &Win_CommConfig, sizeof(COMMCONFIG));
                }
                break;
        }
    }
        UNLOCK_MUTEX();
}

/*!
\fn void Win_QextSerialPort::setStopBits(StopBitsType stopBits)
Sets the number of stop bits used by the serial port.  Possible values of stopBits are:
\verbatim
    STOP_1      1 stop bit
    STOP_1_5    1.5 stop bits
    STOP_2      2 stop bits
\endverbatim

\note
This function is subject to the following restrictions:
\par
    2 stop bits cannot be used with 5 data bits.
\par
    1.5 stop bits cannot be used with 6 or more data bits.
\par
    POSIX does not support 1.5 stop bits.
*/
void Win_QextSerialPort::setStopBits(StopBitsType stopBits)
{
        LOCK_MUTEX();
    if (Settings.StopBits!=stopBits)
    {
        if ((Settings.DataBits==DATA_5 && stopBits==STOP_2) ||
                (stopBits==STOP_1_5 && Settings.DataBits!=DATA_5))
        {
        }
        else
        {
            Settings.StopBits=stopBits;
        }
    }
//   if (isOpen())
    {
        switch (stopBits)
        {

                /*one stop bit*/
            case STOP_1:
                Win_CommConfig.dcb.StopBits=ONESTOPBIT;
                SetCommConfig(Win_Handle, &Win_CommConfig, sizeof(COMMCONFIG));
                break;

                /*1.5 stop bits*/
            case STOP_1_5:
                TTY_PORTABILITY_WARNING("Win_QextSerialPort Portability Warning: 1.5 stop bit operation is not supported by POSIX.");
                if (Settings.DataBits!=DATA_5)
                {
                    TTY_WARNING("Win_QextSerialPort: 1.5 stop bits can only be used with 5 data bits");
                }
                else
                {
                    Win_CommConfig.dcb.StopBits=ONE5STOPBITS;
                    SetCommConfig(Win_Handle, &Win_CommConfig, sizeof(COMMCONFIG));
                }
                break;

                /*two stop bits*/
            case STOP_2:
                if (Settings.DataBits==DATA_5)
                {
                    TTY_WARNING("Win_QextSerialPort: 2 stop bits cannot be used with 5 data bits");
                }
                else
                {
                    Win_CommConfig.dcb.StopBits=TWOSTOPBITS;
                    SetCommConfig(Win_Handle, &Win_CommConfig, sizeof(COMMCONFIG));
                }
                break;
        }
    }
        UNLOCK_MUTEX();
}

/*!
\fn void Win_QextSerialPort::setBaudRate(BaudRateType baudRate)
Sets the baud rate of the serial port.  Note that not all rates are applicable on
all platforms.  The following table shows translations of the various baud rate
constants on Windows(including NT/2000) and POSIX platforms.  Speeds marked with an *
are speeds that are usable on both Windows and POSIX.
\verbatim

  RATE          Windows Speed   POSIX Speed
  -----------   -------------   -----------
   BAUD50                 110          50
   BAUD75                 110          75
  *BAUD110                110         110
   BAUD134                110         134.5
   BAUD150                110         150
   BAUD200                110         200
  *BAUD300                300         300
  *BAUD600                600         600
  *BAUD1200              1200        1200
   BAUD1800              1200        1800
  *BAUD2400              2400        2400
  *BAUD4800              4800        4800
  *BAUD9600              9600        9600
   BAUD14400            14400        9600
  *BAUD19200            19200       19200
  *BAUD38400            38400       38400
   BAUD56000            56000       38400
  *BAUD57600            57600       57600
   BAUD76800            57600       76800
  *BAUD115200          115200      115200
   BAUD128000          128000      115200
   BAUD256000          256000      115200
\endverbatim
*/
void Win_QextSerialPort::setBaudRate(BaudRateType baudRate)
{
        LOCK_MUTEX();
    if (Settings.BaudRate!=baudRate)
    {
        switch (baudRate)
        {
            case BAUD50:
            case BAUD75:
            case BAUD134:
            case BAUD150:
            case BAUD200:
                Settings.BaudRate=BAUD110;
                break;

            case BAUD1800:
                Settings.BaudRate=BAUD1200;
                break;

            case BAUD76800:
                Settings.BaudRate=BAUD57600;
                break;

            default:
                Settings.BaudRate=baudRate;
                break;
        }
    }
    //  if (isOpen())
    {
        switch (baudRate)
        {

                /*50 baud*/
            case BAUD50:
                TTY_WARNING("Win_QextSerialPort: Windows does not support 50 baud operation.  Switching to 110 baud.");
                Win_CommConfig.dcb.BaudRate=CBR_110;
                break;

                /*75 baud*/
            case BAUD75:
                TTY_WARNING("Win_QextSerialPort: Windows does not support 75 baud operation.  Switching to 110 baud.");
                Win_CommConfig.dcb.BaudRate=CBR_110;
                break;

                /*110 baud*/
            case BAUD110:
                Win_CommConfig.dcb.BaudRate=CBR_110;
                break;

                /*134.5 baud*/
            case BAUD134:
                TTY_WARNING("Win_QextSerialPort: Windows does not support 134.5 baud operation.  Switching to 110 baud.");
                Win_CommConfig.dcb.BaudRate=CBR_110;
                break;

                /*150 baud*/
            case BAUD150:
                TTY_WARNING("Win_QextSerialPort: Windows does not support 150 baud operation.  Switching to 110 baud.");
                Win_CommConfig.dcb.BaudRate=CBR_110;
                break;

                /*200 baud*/
            case BAUD200:
                TTY_WARNING("Win_QextSerialPort: Windows does not support 200 baud operation.  Switching to 110 baud.");
                Win_CommConfig.dcb.BaudRate=CBR_110;
                break;

                /*300 baud*/
            case BAUD300:
                Win_CommConfig.dcb.BaudRate=CBR_300;
                break;

                /*600 baud*/
            case BAUD600:
                Win_CommConfig.dcb.BaudRate=CBR_600;
                break;

                /*1200 baud*/
            case BAUD1200:
                Win_CommConfig.dcb.BaudRate=CBR_1200;
                break;

                /*1800 baud*/
            case BAUD1800:
                TTY_WARNING("Win_QextSerialPort: Windows does not support 1800 baud operation.  Switching to 1200 baud.");
                Win_CommConfig.dcb.BaudRate=CBR_1200;
                break;

                /*2400 baud*/
            case BAUD2400:
                Win_CommConfig.dcb.BaudRate=CBR_2400;
                break;

                /*4800 baud*/
            case BAUD4800:
                Win_CommConfig.dcb.BaudRate=CBR_4800;
                break;

                /*9600 baud*/
            case BAUD9600:
                Win_CommConfig.dcb.BaudRate=CBR_9600;
                break;

                /*14400 baud*/
            case BAUD14400:
                TTY_PORTABILITY_WARNING("Win_QextSerialPort Portability Warning: POSIX does not support 14400 baud operation.");
                Win_CommConfig.dcb.BaudRate=CBR_14400;
                break;

                /*19200 baud*/
            case BAUD19200:
                Win_CommConfig.dcb.BaudRate=CBR_19200;
                break;

                /*38400 baud*/
            case BAUD38400:
                Win_CommConfig.dcb.BaudRate=CBR_38400;
                break;

                /*56000 baud*/
            case BAUD56000:
                TTY_PORTABILITY_WARNING("Win_QextSerialPort Portability Warning: POSIX does not support 56000 baud operation.");
                Win_CommConfig.dcb.BaudRate=CBR_56000;
                break;

                /*57600 baud*/
            case BAUD57600:
                Win_CommConfig.dcb.BaudRate=CBR_57600;
                break;

                /*76800 baud*/
            case BAUD76800:
                TTY_WARNING("Win_QextSerialPort: Windows does not support 76800 baud operation.  Switching to 57600 baud.");
                Win_CommConfig.dcb.BaudRate=CBR_57600;
                break;

                /*115200 baud*/
            case BAUD115200:
                Win_CommConfig.dcb.BaudRate=CBR_115200;
                break;

                /*128000 baud*/
            case BAUD128000:
                TTY_PORTABILITY_WARNING("Win_QextSerialPort Portability Warning: POSIX does not support 128000 baud operation.");
                Win_CommConfig.dcb.BaudRate=CBR_128000;
                break;

                /*256000 baud*/
            case BAUD256000:
                TTY_PORTABILITY_WARNING("Win_QextSerialPort Portability Warning: POSIX does not support 256000 baud operation.");
                Win_CommConfig.dcb.BaudRate=CBR_256000;
                break;
        }
        SetCommConfig(Win_Handle, &Win_CommConfig, sizeof(COMMCONFIG));
    }
        UNLOCK_MUTEX();
}

/*!
\fn void Win_QextSerialPort::setDtr(bool set)
Sets DTR line to the requested state (high by default).  This function will have no effect if
the port associated with the class is not currently open.
*/
void Win_QextSerialPort::setDtr(bool set)
{
        LOCK_MUTEX();
//    if (isOpen())
    {
        if (set)
        {
            EscapeCommFunction(Win_Handle, SETDTR);
        }
        else
        {
            EscapeCommFunction(Win_Handle, CLRDTR);
        }
    }
        UNLOCK_MUTEX();
}

/*!
\fn void Win_QextSerialPort::setRts(bool set)
Sets RTS line to the requested state (high by default).  This function will have no effect if
the port associated with the class is not currently open.
*/
void Win_QextSerialPort::setRts(bool set)
{
        LOCK_MUTEX();
    //  if (isOpen())
    {
        if (set)
        {
            EscapeCommFunction(Win_Handle, SETRTS);
        }
        else
        {
            EscapeCommFunction(Win_Handle, CLRRTS);
        }
    }
        UNLOCK_MUTEX();
}

/*!
\fn ulong Win_QextSerialPort::lineStatus(void)
returns the line status as stored by the port function.  This function will retrieve the states
of the following lines: DCD, CTS, DSR, and RI.  On POSIX systems, the following additional lines
can be monitored: DTR, RTS, Secondary TXD, and Secondary RXD.  The value returned is an unsigned
long with specific bits indicating which lines are high.  The following constants should be used
to examine the states of individual lines:

\verbatim
Mask        Line
------      ----
LS_CTS      CTS
LS_DSR      DSR
LS_DCD      DCD
LS_RI       RI
\endverbatim

This function will return 0 if the port associated with the class is not currently open.
*/
ulong Win_QextSerialPort::lineStatus(void)
{
    unsigned long Status=0, Temp=0;
        LOCK_MUTEX();
//   if (isOpen())
    {
        GetCommModemStatus(Win_Handle, &Temp);
        if (Temp&MS_CTS_ON)
        {
            Status|=LS_CTS;
        }
        if (Temp&MS_DSR_ON)
        {
            Status|=LS_DSR;
        }
        if (Temp&MS_RING_ON)
        {
            Status|=LS_RI;
        }
        if (Temp&MS_RLSD_ON)
        {
            Status|=LS_DCD;
        }
    }
        UNLOCK_MUTEX();
    return Status;
}

bool Win_QextSerialPort::waitForReadyRead(int msecs)
{
    //@todo implement
    return false;
}

qint64 Win_QextSerialPort::bytesToWrite() const
{
    return _bytesToWrite;
}



/*!
\fn void Win_QextSerialPort::setTimeout(ulong millisec);
Sets the read and write timeouts for the port to millisec milliseconds.
Setting 0 for both sec and millisec indicates that timeouts are not used for read nor
write operations. Setting -1 indicates that read and write should return immediately.

\note this function does nothing in event driven mode.
*/
void Win_QextSerialPort::setTimeout(long millisec)
{
        LOCK_MUTEX();
    Settings.Timeout_Millisec = millisec;

    if (millisec == -1)
    {
        Win_CommTimeouts.ReadIntervalTimeout = MAXDWORD;
        Win_CommTimeouts.ReadTotalTimeoutConstant = 0;
    }
    else
    {
        Win_CommTimeouts.ReadIntervalTimeout = millisec;
        Win_CommTimeouts.ReadTotalTimeoutConstant = millisec;
    }
    Win_CommTimeouts.ReadTotalTimeoutMultiplier = 0;
    Win_CommTimeouts.WriteTotalTimeoutMultiplier = millisec;
    Win_CommTimeouts.WriteTotalTimeoutConstant = 0;

    SetCommTimeouts(Win_Handle, &Win_CommTimeouts);

        UNLOCK_MUTEX();
}

Win_QextSerialThread::Win_QextSerialThread(Win_QextSerialPort * qesp):
    QThread()
{
    this->qesp = qesp;
    gterminate = false;
}
void Win_QextSerialThread::stop()
{
    gterminate = true;
}
void Win_QextSerialThread::run()
{
    isRun=true;
    gterminate = false;
    while(!gterminate)
    {
       QThread::msleep(300);
       qesp->StartStop();
    }
    isRun=false;
}
