#ifndef WORKER_H
#define WORKER_H

#include <QLinkedList>
#include <QPair>
#include <plane.h>

using namespace std;

/**
 * @class Worker
 *
 * @brief Questa classe genera la soluzione.
 *
 * Utilizza le funzionalità della classe Plane per generare le soluzioni.
 *
 * @author Diego Marcia { gpimple@gmail.com }
 */

class Worker {

public:

    QLinkedList<QLinkedList<int>> work();

private:

    QLinkedList<int> bigRoute;
    int pathLength;
    QLinkedList<QLinkedList<int>> subRoutes;

    QPair<int, QLinkedList<int>> build_sub_route (int start);
};

#endif // WORKER_H
