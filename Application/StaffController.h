#ifndef STAFFCONTROLLER_H
#define STAFFCONTROLLER_H

#include "Staff.h"
#include <QObject>
#include <QList>

class StaffController : public QObject {
    Q_OBJECT

public:
    void addStaff(Staff *staff);
    void moveStaff(int staffId, int x, int y, double scale);
    Staff *findStaffById(int staffId);

private:
    QList<Staff *> staffs;
};

#endif // STAFFCONTROLLER_H
