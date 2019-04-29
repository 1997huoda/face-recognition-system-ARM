/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../server/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_thr_t {
    QByteArrayData data[6];
    char stringdata0[47];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_thr_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_thr_t qt_meta_stringdata_thr = {
    {
QT_MOC_LITERAL(0, 0, 3), // "thr"
QT_MOC_LITERAL(1, 4, 13), // "update_signal"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 6), // "cmd_st"
QT_MOC_LITERAL(4, 26, 8), // "get_text"
QT_MOC_LITERAL(5, 35, 11) // "change_over"

    },
    "thr\0update_signal\0\0cmd_st\0get_text\0"
    "change_over"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_thr[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void thr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<thr *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->update_signal(); break;
        case 1: _t->cmd_st(); break;
        case 2: _t->get_text(); break;
        case 3: _t->change_over(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (thr::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&thr::update_signal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (thr::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&thr::cmd_st)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (thr::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&thr::get_text)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (thr::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&thr::change_over)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject thr::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_thr.data,
    qt_meta_data_thr,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *thr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *thr::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_thr.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int thr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void thr::update_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void thr::cmd_st()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void thr::get_text()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void thr::change_over()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[17];
    char stringdata0[275];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "timerUpdate"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 16), // "on_cmd_1_clicked"
QT_MOC_LITERAL(4, 41, 16), // "on_cmd_2_clicked"
QT_MOC_LITERAL(5, 58, 16), // "on_cmd_3_clicked"
QT_MOC_LITERAL(6, 75, 16), // "on_cmd_4_clicked"
QT_MOC_LITERAL(7, 92, 22), // "on_cmd_connect_clicked"
QT_MOC_LITERAL(8, 115, 9), // "update_ui"
QT_MOC_LITERAL(9, 125, 6), // "cmd_up"
QT_MOC_LITERAL(10, 132, 19), // "change_send_success"
QT_MOC_LITERAL(11, 152, 19), // "on_change_7_clicked"
QT_MOC_LITERAL(12, 172, 19), // "on_change_8_clicked"
QT_MOC_LITERAL(13, 192, 19), // "on_change_9_clicked"
QT_MOC_LITERAL(14, 212, 20), // "on_change_10_clicked"
QT_MOC_LITERAL(15, 233, 20), // "on_change_11_clicked"
QT_MOC_LITERAL(16, 254, 20) // "on_change_12_clicked"

    },
    "MainWindow\0timerUpdate\0\0on_cmd_1_clicked\0"
    "on_cmd_2_clicked\0on_cmd_3_clicked\0"
    "on_cmd_4_clicked\0on_cmd_connect_clicked\0"
    "update_ui\0cmd_up\0change_send_success\0"
    "on_change_7_clicked\0on_change_8_clicked\0"
    "on_change_9_clicked\0on_change_10_clicked\0"
    "on_change_11_clicked\0on_change_12_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    0,   92,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    0,  100,    2, 0x08 /* Private */,
      14,    0,  101,    2, 0x08 /* Private */,
      15,    0,  102,    2, 0x08 /* Private */,
      16,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->timerUpdate(); break;
        case 1: _t->on_cmd_1_clicked(); break;
        case 2: _t->on_cmd_2_clicked(); break;
        case 3: _t->on_cmd_3_clicked(); break;
        case 4: _t->on_cmd_4_clicked(); break;
        case 5: _t->on_cmd_connect_clicked(); break;
        case 6: _t->update_ui(); break;
        case 7: _t->cmd_up(); break;
        case 8: _t->change_send_success(); break;
        case 9: _t->on_change_7_clicked(); break;
        case 10: _t->on_change_8_clicked(); break;
        case 11: _t->on_change_9_clicked(); break;
        case 12: _t->on_change_10_clicked(); break;
        case 13: _t->on_change_11_clicked(); break;
        case 14: _t->on_change_12_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
