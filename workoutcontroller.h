#ifndef WORKOUTCONTROLLER_H
#define WORKOUTCONTROLLER_H

#include <QObject>

class WorkoutController : public QObject
{
    Q_OBJECT
public:
    explicit WorkoutController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // WORKOUTCONTROLLER_H
