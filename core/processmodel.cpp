#include "processmodel.h"
#include "processmanager.h"

ProcessModel::ProcessModel(QProcess *process, QObject *parent)
    : QObject {parent}, m_process(process)
{
    connect(m_process, &QProcess::readyReadStandardOutput, this, &ProcessModel::standartOutputChanged);
    connect(m_process, &QProcess::readyReadStandardError, this, &ProcessModel::errorOutputChanged);
}

QString ProcessModel::title() const
{
    return QString::number(m_process->processId());
}

QString ProcessModel::standartOutput() const
{
    return m_process->readAllStandardOutput();
}

QString ProcessModel::errorOutput() const
{
    return m_process->readAllStandardError();
}

