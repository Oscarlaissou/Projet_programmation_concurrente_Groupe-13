#include "StaffController.h"

void StaffController::addStaff(Staff *staff) {
    staffs.append(staff);
}

void StaffController::moveStaff(int staffId, int x, int y, double scale) {
    for (Staff *staff : staffs) {
        if (staff->getId() == staffId) {
            staff->setPosition(x, y, scale);
            break;
        }
    }
}

Staff *StaffController::findStaffById(int staffId) {
    for (Staff *staff : staffs) {
        if (staff->getId() == staffId) {
            return staff;
        }
    }
    return nullptr;
}
