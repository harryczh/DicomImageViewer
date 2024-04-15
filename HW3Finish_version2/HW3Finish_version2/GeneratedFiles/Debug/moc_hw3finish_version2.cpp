/****************************************************************************
** Meta object code from reading C++ file 'hw3finish_version2.h'
**
** Created: Thu Nov 30 15:08:16 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../hw3finish_version2.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hw3finish_version2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HW3Finish_version2[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,
      32,   19,   19,   19, 0x08,
      41,   19,   19,   19, 0x08,
      57,   19,   19,   19, 0x08,
      74,   19,   19,   19, 0x08,
      89,   19,   19,   19, 0x08,
     105,   19,   19,   19, 0x08,
     118,   19,   19,   19, 0x08,
     132,   19,   19,   19, 0x08,
     146,   19,   19,   19, 0x08,
     161,   19,   19,   19, 0x08,
     170,   19,   19,   19, 0x08,
     179,   19,   19,   19, 0x08,
     188,   19,   19,   19, 0x08,
     196,   19,   19,   19, 0x08,
     205,   19,   19,   19, 0x08,
     225,   19,   19,   19, 0x08,
     234,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_HW3Finish_version2[] = {
    "HW3Finish_version2\0\0Open_File()\0"
    "Update()\0Skin_isovalue()\0Skull_isovalue()\0"
    "Skin_opacity()\0Skull_opacity()\0"
    "Skin_color()\0Skull_color()\0Skin_accept()\0"
    "Skull_accept()\0Xslice()\0Yslice()\0"
    "Zslice()\0Level()\0Window()\0Orthogonal_planes()\0"
    "Action()\0Initial_value()\0"
};

void HW3Finish_version2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        HW3Finish_version2 *_t = static_cast<HW3Finish_version2 *>(_o);
        switch (_id) {
        case 0: _t->Open_File(); break;
        case 1: _t->Update(); break;
        case 2: _t->Skin_isovalue(); break;
        case 3: _t->Skull_isovalue(); break;
        case 4: _t->Skin_opacity(); break;
        case 5: _t->Skull_opacity(); break;
        case 6: _t->Skin_color(); break;
        case 7: _t->Skull_color(); break;
        case 8: _t->Skin_accept(); break;
        case 9: _t->Skull_accept(); break;
        case 10: _t->Xslice(); break;
        case 11: _t->Yslice(); break;
        case 12: _t->Zslice(); break;
        case 13: _t->Level(); break;
        case 14: _t->Window(); break;
        case 15: _t->Orthogonal_planes(); break;
        case 16: _t->Action(); break;
        case 17: _t->Initial_value(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData HW3Finish_version2::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject HW3Finish_version2::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HW3Finish_version2,
      qt_meta_data_HW3Finish_version2, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HW3Finish_version2::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HW3Finish_version2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HW3Finish_version2::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HW3Finish_version2))
        return static_cast<void*>(const_cast< HW3Finish_version2*>(this));
    return QWidget::qt_metacast(_clname);
}

int HW3Finish_version2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
