// SPDX-FileCopyrightText: 2011 - 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef READ_PIPE_DATA_TASK_H
#define READ_PIPE_DATA_TASK_H

#include <QObject>
#include <QRunnable>
#include <QMutex>

namespace KWayland
{
    namespace Client
    {
        class ConnectionThread;
        class DataControlOfferV1;
    } //Client
} //KWayland

using namespace KWayland::Client;

class ReadPipeDataTask : public QObject
{
    Q_OBJECT
public:
    explicit ReadPipeDataTask(ConnectionThread *connectionThread, DataControlOfferV1 *offerV1,
                              QString mimeType, QObject *parent = nullptr);

    void stopRunning();
    void run();

signals:
    void dataReady(qint64, const QString &, const QByteArray &);



private:
    bool readData(int fd, QByteArray &data);

private:
    bool m_stopRunning;
    QString m_mimeType;
    QMutex m_mutexLock;

    DataControlOfferV1 *m_pOffer;
    ConnectionThread *m_pConnectionThread;
};

#endif //READ_PIPE_DATA_TASK_H
