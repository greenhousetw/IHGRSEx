#include "sqliter.h"


SQLiter::SQLiter(QString dbName):IRepository(dbName)
{
    qDebug() << "Database will be opened:" + dbName;
}

SQLiter::~SQLiter()
{

}

/**
 * @brief SQLiter::OpenDB
 * @return
 */
bool SQLiter::OpenDB()
{
    QStringList tablelist;

    bool result=false;

    this->databaseInstance=QSqlDatabase::addDatabase("QSQLITE");

    this->dbName=QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + QDir::separator() + this->dbName);

    this->databaseInstance.setDatabaseName(this->dbName);

    if(!this->databaseInstance.open())
    {
        qCritical()<<"Sqlite fails to open database:" + this->dbName;
        goto bye;
    }

    qDebug()<<"Open database:" + this->dbName + " successfully";

    tablelist=this->databaseInstance.tables();

    qDebug() << "Table count:" + tablelist.count();

    result=true;

    bye:
    return result;
}

/**
 * @brief SQLiter::ChangeDataBase
 * @param databaseName
 * @return true for successful and false for fail
 */
bool SQLiter::ChangeDataBase(QString databaseName)
{
    bool result=false;

    QString changeMessage="Change is fail";
    qDebug()<<"Change database from " + this->dbName + ", to " + databaseName;

    this->CloseDB();
    this->dbName=databaseName;

    if(this->OpenDB())
    {
        changeMessage="Change is successful";
        result=true;
    }

    qDebug()<<changeMessage;

    return result;
}

/**
 * @brief SQLiter::Execute
 * @param command
 * @return true for all commands get succesul result, otherwise returns false
 */
QMap<QString, QVariant>  SQLiter::ExecuteSQLCommand(QMap<QString, QString> command)
{
    QString message="is fail";

    QSqlQuery sqlExecutor(this->databaseInstance);

    QMap<QString, QVariant> result;

    if(!this->databaseInstance.isOpen())
    {
        qWarning()<<"DataBase:" + this->databaseInstance.databaseName() + " is close";
        goto orz;
    }

    foreach(QString key, command.keys())
    {      
       if(sqlExecutor.exec(command[key]))
       {
           message = command[key] +" is successful";
           qDebug()<<message;
       }
       else
       {
           message=command[key] + " is fail, message=" + sqlExecutor.lastError().databaseText();
           qCritical() << message;
           break;
       }
    }

    result.insert(CommonVariables::SqlSelectSize, QVariant(sqlExecutor.size()));
    result.insert(CommonVariables::SqlNonSelectSize, QVariant(sqlExecutor.numRowsAffected()));

    qDebug()<<message;

    orz:
    return result;
}

/**
 * @brief SQLiter::CloseDB
 * @return true for successful and false for fail
 */
bool SQLiter::CloseDB()
{
    bool result=false;

    this->databaseInstance.close();

    qDebug()<<"Database successfully closed~";

    result=true;

    return result;
}
