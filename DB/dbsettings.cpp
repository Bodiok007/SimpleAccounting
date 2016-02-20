#include "dbsettings.h"

DBSettings::DBSettings()
{
    m_pSettingsFile = new QFile("dbSettings/settings.txt");

    createMassivePointersToSettings();

    readSettings();
}


// create an array of pointers to configuration
// for comfortably read data from file in one cycle
void DBSettings::createMassivePointersToSettings()
{
    settings[0] = &m_databaseName;
    settings[1] = &m_userName;
    settings[2] = &m_password;
    settings[3] = &m_hostName;
}


bool DBSettings::readSettings()
{
    if (!m_pSettingsFile->open(QIODevice::ReadOnly
                               | QIODevice::Text)) {
        errorOpenMessage("reading");

        return false;
    }

    QTextStream in(m_pSettingsFile);

    QStringList parameterList;

    QString line = "";

    // set settings from file
    for (int setting = 0; setting < NUM_SETTINGS; ++setting) {
        if (!in.atEnd()) {
            line = in.readLine();
            parameterList = line.split(":");
            *settings[setting] = parameterList.at(1);
        }
    }

    m_pSettingsFile->close();

    return true;
}


void DBSettings::writeSettings(QString databaseName,
                               QString userName,
                               QString password,
                               QString hostName)
{
    if (!m_pSettingsFile->open(QIODevice::WriteOnly
                               | QIODevice::Text)) {
        errorOpenMessage("writing");

        return;
    }

    QTextStream out(m_pSettingsFile);
    out << "databaseName:" << databaseName << "\n";
    out << "userName:" << userName << "\n";
    out << "password:" << password << "\n";
    out << "hostName:" << hostName;

    m_pSettingsFile->close();

    setDatabaseName(databaseName);
    setUserName(userName);
    setPassword(password);
    setHostName(hostName);
}


// error message if can`t open file for [action]
void DBSettings::errorOpenMessage(QString action)
{
    QMessageBox msgBox;
    msgBox.setText("Can`t open file "
                   + QDir::currentPath()
                   + QDir::separator()
                   + m_pSettingsFile->fileName()
                   + " for "
                   + action);
    msgBox.exec();
}


QString DBSettings::getHostName() const
{
    return m_hostName;
}


void DBSettings::setHostName(const QString &value)
{
    m_hostName = value;
}


QString DBSettings::getDatabaseName() const
{
    return m_databaseName;
}


void DBSettings::setDatabaseName(const QString &value)
{
    m_databaseName = value;
}


QString DBSettings::getUserName() const
{
    return m_userName;
}


void DBSettings::setUserName(const QString &value)
{
    m_userName = value;
}


QString DBSettings::getPassword() const
{
    return m_password;
}


void DBSettings::setPassword(const QString &value)
{
    m_password = value;
}


DBSettings::~DBSettings()
{
    delete m_pSettingsFile;
}

