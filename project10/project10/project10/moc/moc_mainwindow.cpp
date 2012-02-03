/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Fri 3. Feb 17:59:07 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x0a,
      50,   11,   11,   11, 0x08,
      66,   11,   11,   11, 0x08,
      90,   11,   11,   11, 0x08,
     104,   11,   11,   11, 0x08,
     117,   11,   11,   11, 0x08,
     131,   11,   11,   11, 0x08,
     155,   11,   11,   11, 0x08,
     181,   11,   11,   11, 0x08,
     207,   11,   11,   11, 0x08,
     233,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0info\0positonUpdated(QGeoPositionInfo)\0"
    "sessionOpened()\0sendDataString(QString)\0"
    "pressedUnus()\0pressedDuo()\0pressedTres()\0"
    "on_pushButton_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_pushButton_3_clicked()\0"
    "on_pushButton_4_clicked()\0"
    "on_pushButton_5_clicked()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: positonUpdated((*reinterpret_cast< const QGeoPositionInfo(*)>(_a[1]))); break;
        case 1: sessionOpened(); break;
        case 2: sendDataString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: pressedUnus(); break;
        case 4: pressedDuo(); break;
        case 5: pressedTres(); break;
        case 6: on_pushButton_clicked(); break;
        case 7: on_pushButton_2_clicked(); break;
        case 8: on_pushButton_3_clicked(); break;
        case 9: on_pushButton_4_clicked(); break;
        case 10: on_pushButton_5_clicked(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
