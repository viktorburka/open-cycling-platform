#include "workoutcontroller.h"

#include <QtDebug>
#include <QTimer>

WorkoutController::WorkoutController(QObject *parent)
    : QObject(parent)
{
    m_ticker = new QTimer(this);
    connect(m_ticker, SIGNAL(timeout()), SLOT(updateValues()));
    setElapsedTime("00:00:00");
    setCurrentTime(QTime::currentTime().toString(Qt::LocalDate));
}

void WorkoutController::startWorkout()
{
    m_startTime = QTime::currentTime();
    m_ticker->start(1000);
}

void WorkoutController::updateValues()
{
    QTime ct = QTime::currentTime();
    QTime elapsed = QTime(0,0).addSecs(m_startTime.secsTo(ct));
    setElapsedTime(elapsed.toString("HH:mm:ss"));
    setCurrentTime(ct.toString(Qt::LocalDate));
}
