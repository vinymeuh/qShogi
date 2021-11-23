/*
 * Copyright (c) VinyMeuh. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include "GameController.h"


int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("qShogi");
    QGuiApplication::setOrganizationName("qShogi");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    GameController game = GameController(&engine);
    qmlRegisterSingletonInstance("qShogi", 1, 0, "GameController", &game);

    engine.load(QUrl("qrc:/qml/main.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
