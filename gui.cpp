#include <QtMath>
#include <cmath>
#include <functional>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>
#include <QMap>
#include <QSet>
#include <QVector>
#include <QQueue>
#include <QStringList>

class NetworkWindow : public QMainWindow {
    

    QMap<QString, QSet<QString>> graph;
    QGraphicsScene *scene;
    QLabel *status;
    QLabel *stats;
QStringList highlightedPath;
public:
    NetworkWindow() {
        setWindowTitle("Network Connection Analyzer");
        resize(1000, 650);

        QWidget *central = new QWidget;
        setCentralWidget(central);

        QVBoxLayout *mainLayout = new QVBoxLayout(central);

        QLabel *heading = new QLabel("NETWORK CONNECTION ANALYZER");
        heading->setStyleSheet(
            "font-size:25px; font-weight:bold; color:#38bdf8; padding:15px;"
        );
        mainLayout->addWidget(heading);

        stats = new QLabel("Devices: 0     Connections: 0");
        stats->setStyleSheet("font-size:16px; padding:8px;");
        mainLayout->addWidget(stats);

        scene = new QGraphicsScene(this);
        QGraphicsView *view = new QGraphicsView(scene);
        view->setMinimumHeight(350);
        view->setStyleSheet("background:#111827; border:1px solid #334155;");
        mainLayout->addWidget(view);

        QHBoxLayout *buttons = new QHBoxLayout;

        addButton(buttons, "Add Device", [this]() {
            bool ok;
            QString name = QInputDialog::getText(
                this, "Add Device", "Device name:",
                QLineEdit::Normal, "", &ok
            );

            name = name.trimmed();

            if (ok && !name.isEmpty()) {
                if (graph.contains(name)) {
                    QMessageBox::warning(this, "Error",
                                         "Device already exists!");
                } else {
                    graph[name] = QSet<QString>();
                    refresh();
                    status->setText("Added device: " + name);
                }
            }
        });

        addButton(buttons, "Connect Devices", [this]() {
            if (graph.size() < 2) {
                QMessageBox::warning(this, "Error",
                                     "Add at least two devices first.");
                return;
            }

            QStringList names = graph.keys();

            bool ok1, ok2;
            QString a = QInputDialog::getItem(
                this, "First Device", "Select device:",
                names, 0, false, &ok1
            );

            if (!ok1) return;

            QString b = QInputDialog::getItem(
                this, "Second Device", "Select device:",
                names, 0, false, &ok2
            );

            if (!ok2) return;

            if (a == b || graph[a].contains(b)) {
                QMessageBox::warning(this, "Error",
                                     "Invalid or existing connection.");
                return;
            }

            graph[a].insert(b);
            graph[b].insert(a);
            refresh();
            status->setText(a + " connected to " + b);
        });

        addButton(buttons, "DFS Traversal", [this]() {
            if (graph.isEmpty()) return;

            bool ok;
            QString start = QInputDialog::getItem(
                this, "DFS", "Starting device:",
                graph.keys(), 0, false, &ok
            );

            if (!ok) return;

            QSet<QString> visited;
            QStringList order;
            dfs(start, visited, order);

            status->setText("DFS: " + order.join(" -> "));
            QMessageBox::information(
                this, "DFS Traversal",
                order.join(" -> ")
            );
        });

        addButton(buttons, "Check Path", [this]() {
            if (graph.size() < 2) return;

            QStringList names = graph.keys();
            bool ok1, ok2;

            QString a = QInputDialog::getItem(
                this, "Source", "First device:",
                names, 0, false, &ok1
            );
            if (!ok1) return;

            QString b = QInputDialog::getItem(
                this, "Destination", "Second device:",
                names, 0, false, &ok2
            );
            if (!ok2) return;

         QSet<QString> visited;
QStringList route;
bool found = path(a, b, visited, route);

if (found) {
    highlightedPath = route;
    refresh();

    QString routeText = route.join(" -> ");
    status->setText("Path found: " + routeText);

    QMessageBox::information(
        this, "Connectivity Result",
        "A path exists!\n\nRoute: " + routeText
    );
} else {
    highlightedPath.clear();
    refresh();

    status->setText("No path exists between " + a + " and " + b + ".");

    QMessageBox::information(
        this, "Connectivity Result",
        "No path exists between the devices."
    );
}
        });

        addButton(buttons, "Reset", [this]() {
            graph.clear();
            refresh();
            status->setText("Network reset.");
        });

        mainLayout->addLayout(buttons);

        status = new QLabel("Welcome! Add devices to begin.");
        status->setStyleSheet("padding:12px; color:#38bdf8;");
        mainLayout->addWidget(status);

        setStyleSheet(
            "QMainWindow { background:#0f172a; color:white; }"
            "QLabel { color:white; }"
            "QMessageBox QLabel { color:#111827; }"
            "QPushButton { background:#2563eb; color:white;"
            "padding:12px; border-radius:7px; font-weight:bold; }"
            "QPushButton:hover { background:#1d4ed8; }"
        );
    }

private:
    void addButton(QHBoxLayout *layout, QString title,
                   std::function<void()> action) {
        QPushButton *button = new QPushButton(title);
        layout->addWidget(button);
        connect(button, &QPushButton::clicked, this, action);
    }

    void dfs(QString node, QSet<QString>& visited,
             QStringList& order) {
        visited.insert(node);
        order.append(node);

        for (const QString& next : graph[node]) {
            if (!visited.contains(next))
                dfs(next, visited, order);
        }
    }

        bool path(QString node, QString destination,
              QSet<QString>& visited, QStringList& route) {
        visited.insert(node);
        route.append(node);

        if (node == destination)
            return true;

        for (const QString& next : graph[node]) {
            if (!visited.contains(next) &&
                path(next, destination, visited, route))
                return true;
        }

        route.removeLast();
        return false;
    }

    void refresh() {
        scene->clear();

        QStringList names = graph.keys();
        int count = names.size();
        int radius = 170;

        QMap<QString, QPointF> positions;

        for (int i = 0; i < count; i++) {
            double angle = 6.283185307 * i / qMax(1, count);
            positions[names[i]] = QPointF(
                250 + radius * qCos(angle),
                200 + radius * qSin(angle)
            );
        }

        QPen edgePen(QColor("#38bdf8"), 3);

        for (const QString& a : names) {
            for (const QString& b : graph[a]) {
                if (names.indexOf(a) < names.indexOf(b)) {
                    QPointF p1 = positions[a];
                    QPointF p2 = positions[b];
                  QPen currentPen = edgePen;

int indexA = highlightedPath.indexOf(a);
int indexB = highlightedPath.indexOf(b);

if (indexA >= 0 && indexB >= 0 &&
    qAbs(indexA - indexB) == 1) {
    currentPen = QPen(QColor("#facc15"), 5);
}

scene->addLine(
    p1.x(), p1.y(), p2.x(), p2.y(), currentPen
);  
                }
            }
        }

        for (const QString& name : names) {
            QPointF p = positions[name];

            scene->addEllipse(
                p.x()-40, p.y()-22, 80, 44,
                QPen(Qt::white, 2),
                QBrush(highlightedPath.contains(name)
       ? QColor("#ca8a04")
       : QColor("#2563eb"))
            );

            QGraphicsTextItem *label = scene->addText(name);
            label->setDefaultTextColor(Qt::white);
            label->setPos(p.x()-30, p.y()-10);
        }

        int edges = 0;
        for (const QString& name : names)
            edges += graph[name].size();

        stats->setText(
            "Devices: " + QString::number(count) +
            "     Connections: " + QString::number(edges / 2)
        );

        scene->setSceneRect(0, 0, 520, 420);
    }
};


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    NetworkWindow window;
    window.show();

    return app.exec();
}
