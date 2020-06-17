#ifndef WORKOUTCONTROLLER_H
#define WORKOUTCONTROLLER_H

#include <QObject>
#include <QTime>

class QTimer;

class WorkoutController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString elapsedTime READ elapsedTime WRITE setElapsedTime NOTIFY elapsedTimeChanged)
    Q_PROPERTY(QString currentTime READ currentTime WRITE setCurrentTime NOTIFY currentTimeChanged)
public:
    explicit WorkoutController(QObject *parent = nullptr);

    QString elapsedTime() const {
        return m_elapsedTime;
    }

    void setElapsedTime(const QString & value) {
        m_elapsedTime = value;
        emit elapsedTimeChanged();
    }

    QString currentTime() const {
        return m_currentTime;
    }

    void setCurrentTime(const QString & value) {
        m_currentTime = value;
        emit currentTimeChanged();
    }

    Q_INVOKABLE void startWorkout();

signals:
    void elapsedTimeChanged();
    void currentTimeChanged();

private slots:
    void updateValues();

private:
    QString m_elapsedTime;
    QString m_currentTime;
    QTime m_startTime;
    QTimer *m_ticker;
};

#endif // WORKOUTCONTROLLER_H
