/*
 * Copyright (c) 2009 Jacob Alexander <haata at users.sf.net>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name(s) of the above
 * copyright holders shall not be used in advertising or otherwise
 * to promote the sale, use or other dealings in this Software
 * without prior written authorization.
 */

// Qt Includes
#include <QAction>
#include <QApplication>
#include <QIcon>
#include <QMenu>
#include <QSystemTrayIcon>

// Local Includes
#include "MHover.h"


int main( int argc, char *argv[] )
{
    // Feeling too lazy today to make a native app
    QApplication app( argc, argv );

    // Mouse Wheel Detection and Redirection
    MHover hover( (QObject*)&app );

    // System tray icon
    QMenu menuTrayIcon;
    QAction actionQuit( QObject::tr("&Exit"), &menuTrayIcon );
    menuTrayIcon.addAction( &actionQuit );

    QSystemTrayIcon trayIcon( QIcon("tray.ico"), (QObject*)&app );
    trayIcon.setContextMenu( &menuTrayIcon );
    trayIcon.setToolTip( QObject::tr("MHover - Mouse Wheel Redirection - This utility redirects mouse wheel events to the current window under the mouse cursor rather than to the current focused window.") );
    trayIcon.show();

    // GUI Events
    QObject::connect( &actionQuit, SIGNAL( triggered() ), &app, SLOT( quit() ) );

    return app.exec();
}
