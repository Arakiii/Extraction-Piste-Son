/****************************************************************************
** Meta object code from reading C++ file 'fileview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qtmidieditor/fileview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fileview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FileView_t {
    QByteArrayData data[7];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileView_t qt_meta_stringdata_FileView = {
    {
QT_MOC_LITERAL(0, 0, 8), // "FileView"
QT_MOC_LITERAL(1, 9, 18), // "requestDeleteTrack"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 4), // "num_"
QT_MOC_LITERAL(4, 34, 15), // "requestAddTrack"
QT_MOC_LITERAL(5, 50, 15), // "showContextMenu"
QT_MOC_LITERAL(6, 66, 4) // "pos_"

    },
    "FileView\0requestDeleteTrack\0\0num_\0"
    "requestAddTrack\0showContextMenu\0pos_"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    6,

       0        // eod
};

void FileView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FileView *_t = static_cast<FileView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestDeleteTrack((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->requestAddTrack((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->showContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FileView::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileView::requestDeleteTrack)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (FileView::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileView::requestAddTrack)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject FileView::staticMetaObject = {
    { &QListView::staticMetaObject, qt_meta_stringdata_FileView.data,
      qt_meta_data_FileView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FileView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FileView.stringdata0))
        return static_cast<void*>(const_cast< FileView*>(this));
    return QListView::qt_metacast(_clname);
}

int FileView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void FileView::requestDeleteTrack(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FileView::requestAddTrack(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
