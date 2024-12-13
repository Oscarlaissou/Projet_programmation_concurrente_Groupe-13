// #include "StaffController.h"

// StaffController::StaffController(QObject *parent)
//     : QObject(parent), scene(nullptr) {}

// void StaffController::setScene(QGraphicsScene *scene) {
//     this->scene = scene;
// }

// void StaffController::addStaff(const QString &imagePath, int id, int x, int y, double scale) {
//     if (!scene) return;

//     Staff *staff = new Staff(imagePath, id, this);
//     staff->setPosition(x, y, scale);
//     scene->addItem(staff->getGraphicsItem());
//     staffs.append(staff);
// }

// void StaffController::moveStaff(int staffId, int dx, int dy) {
//     Staff *staff = findStaffById(staffId);
//     if (staff) {
//         QGraphicsPixmapItem *item = staff->getGraphicsItem();
//         item->moveBy(dx, dy);
//     }
// }
// Staff* StaffController::findStaffById(int staffId) {
//     for (Staff *staff : staffs) {
//         if (staff->getId() == staffId) {
//             return staff;
//         }
//     }
//     return nullptr; // Retourne nullptr si aucun staff avec cet ID n'est trouvé
// }


