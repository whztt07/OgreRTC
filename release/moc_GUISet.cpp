/****************************************************************************
** Meta object code from reading C++ file 'GUISet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GUISet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUISet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GUISetWidget_t {
    QByteArrayData data[23];
    char stringdata[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GUISetWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GUISetWidget_t qt_meta_stringdata_GUISetWidget = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 9),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 10),
QT_MOC_LITERAL(4, 35, 7),
QT_MOC_LITERAL(5, 43, 8),
QT_MOC_LITERAL(6, 52, 5),
QT_MOC_LITERAL(7, 58, 8),
QT_MOC_LITERAL(8, 67, 8),
QT_MOC_LITERAL(9, 76, 9),
QT_MOC_LITERAL(10, 86, 7),
QT_MOC_LITERAL(11, 94, 10),
QT_MOC_LITERAL(12, 105, 10),
QT_MOC_LITERAL(13, 116, 9),
QT_MOC_LITERAL(14, 126, 11),
QT_MOC_LITERAL(15, 138, 13),
QT_MOC_LITERAL(16, 152, 9),
QT_MOC_LITERAL(17, 162, 11),
QT_MOC_LITERAL(18, 174, 14),
QT_MOC_LITERAL(19, 189, 16),
QT_MOC_LITERAL(20, 206, 11),
QT_MOC_LITERAL(21, 218, 8),
QT_MOC_LITERAL(22, 227, 10)
    },
    "GUISetWidget\0UpdateGUI\0\0UpdateList\0"
    "SetSlot\0PosXSlot\0value\0PosYSlot\0"
    "RollSlot\0PitchSlot\0YawSlot\0ScaleXSlot\0"
    "ScaleYSlot\0AlphaSlot\0VisibleSlot\0"
    "unVisibleSlot\0FrameSlot\0unFrameSlot\0"
    "BackGroundSlot\0unBackGroundSlot\0"
    "DestroySlot\0NameSlot\0WindowSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUISetWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  115,    2, 0x0a /* Public */,
       4,    0,  116,    2, 0x08 /* Private */,
       5,    1,  117,    2, 0x08 /* Private */,
       7,    1,  120,    2, 0x08 /* Private */,
       8,    1,  123,    2, 0x08 /* Private */,
       9,    1,  126,    2, 0x08 /* Private */,
      10,    1,  129,    2, 0x08 /* Private */,
      11,    1,  132,    2, 0x08 /* Private */,
      12,    1,  135,    2, 0x08 /* Private */,
      13,    1,  138,    2, 0x08 /* Private */,
      14,    0,  141,    2, 0x08 /* Private */,
      15,    0,  142,    2, 0x08 /* Private */,
      16,    0,  143,    2, 0x08 /* Private */,
      17,    0,  144,    2, 0x08 /* Private */,
      18,    0,  145,    2, 0x08 /* Private */,
      19,    0,  146,    2, 0x08 /* Private */,
      20,    0,  147,    2, 0x08 /* Private */,
      21,    1,  148,    2, 0x08 /* Private */,
      22,    0,  151,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,

       0        // eod
};

void GUISetWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GUISetWidget *_t = static_cast<GUISetWidget *>(_o);
        switch (_id) {
        case 0: _t->UpdateGUI(); break;
        case 1: _t->UpdateList(); break;
        case 2: _t->SetSlot(); break;
        case 3: _t->PosXSlot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->PosYSlot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->RollSlot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->PitchSlot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->YawSlot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->ScaleXSlot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->ScaleYSlot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->AlphaSlot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->VisibleSlot(); break;
        case 12: _t->unVisibleSlot(); break;
        case 13: _t->FrameSlot(); break;
        case 14: _t->unFrameSlot(); break;
        case 15: _t->BackGroundSlot(); break;
        case 16: _t->unBackGroundSlot(); break;
        case 17: _t->DestroySlot(); break;
        case 18: _t->NameSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->WindowSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GUISetWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUISetWidget::UpdateGUI)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject GUISetWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GUISetWidget.data,
      qt_meta_data_GUISetWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *GUISetWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUISetWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUISetWidget.stringdata))
        return static_cast<void*>(const_cast< GUISetWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int GUISetWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void GUISetWidget::UpdateGUI()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
