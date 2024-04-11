/****************************************************************************
** Meta object code from reading C++ file 'gamedemo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../DATA/baseClass/gamedemo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamedemo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameDemo_t {
    QByteArrayData data[21];
    char stringdata0[277];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameDemo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameDemo_t qt_meta_stringdata_GameDemo = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GameDemo"
QT_MOC_LITERAL(1, 9, 13), // "objectCreated"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 11), // "GameObject*"
QT_MOC_LITERAL(4, 36, 21), // "objectCreatedFromFile"
QT_MOC_LITERAL(5, 58, 2), // "id"
QT_MOC_LITERAL(6, 61, 21), // "objectRegistToManager"
QT_MOC_LITERAL(7, 83, 23), // "demoFuncRegistToManager"
QT_MOC_LITERAL(8, 107, 10), // "SoluteFunc"
QT_MOC_LITERAL(9, 118, 15), // "envStateChanged"
QT_MOC_LITERAL(10, 134, 18), // "playerStateChanged"
QT_MOC_LITERAL(11, 153, 15), // "npcStateChanged"
QT_MOC_LITERAL(12, 169, 17), // "eventStateChanged"
QT_MOC_LITERAL(13, 187, 16), // "initStateChanged"
QT_MOC_LITERAL(14, 204, 14), // "solveIntSignal"
QT_MOC_LITERAL(15, 219, 6), // "number"
QT_MOC_LITERAL(16, 226, 8), // "envState"
QT_MOC_LITERAL(17, 235, 11), // "playerState"
QT_MOC_LITERAL(18, 247, 8), // "npcState"
QT_MOC_LITERAL(19, 256, 10), // "eventState"
QT_MOC_LITERAL(20, 267, 9) // "initState"

    },
    "GameDemo\0objectCreated\0\0GameObject*\0"
    "objectCreatedFromFile\0id\0objectRegistToManager\0"
    "demoFuncRegistToManager\0SoluteFunc\0"
    "envStateChanged\0playerStateChanged\0"
    "npcStateChanged\0eventStateChanged\0"
    "initStateChanged\0solveIntSignal\0number\0"
    "envState\0playerState\0npcState\0eventState\0"
    "initState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameDemo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       5,   90, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    2,   67,    2, 0x06 /* Public */,
       6,    2,   72,    2, 0x06 /* Public */,
       7,    2,   77,    2, 0x06 /* Public */,
       9,    0,   82,    2, 0x06 /* Public */,
      10,    0,   83,    2, 0x06 /* Public */,
      11,    0,   84,    2, 0x06 /* Public */,
      12,    0,   85,    2, 0x06 /* Public */,
      13,    0,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    1,   87,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::UInt,    2,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 8, QMetaType::QString,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   15,

 // properties: name, type, flags
      16, QMetaType::Bool, 0x00495103,
      17, QMetaType::Bool, 0x00495103,
      18, QMetaType::Bool, 0x00495103,
      19, QMetaType::Bool, 0x00495103,
      20, QMetaType::Bool, 0x00495103,

 // properties: notify_signal_id
       4,
       5,
       6,
       7,
       8,

       0        // eod
};

void GameDemo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameDemo *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->objectCreated((*reinterpret_cast< GameObject*(*)>(_a[1]))); break;
        case 1: _t->objectCreatedFromFile((*reinterpret_cast< GameObject*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 2: _t->objectRegistToManager((*reinterpret_cast< GameObject*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->demoFuncRegistToManager((*reinterpret_cast< SoluteFunc(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->envStateChanged(); break;
        case 5: _t->playerStateChanged(); break;
        case 6: _t->npcStateChanged(); break;
        case 7: _t->eventStateChanged(); break;
        case 8: _t->initStateChanged(); break;
        case 9: _t->solveIntSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GameObject* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GameObject* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GameObject* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameDemo::*)(GameObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameDemo::objectCreated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GameDemo::*)(GameObject * , unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameDemo::objectCreatedFromFile)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GameDemo::*)(GameObject * , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameDemo::objectRegistToManager)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GameDemo::*)(SoluteFunc , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameDemo::demoFuncRegistToManager)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GameDemo::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameDemo::envStateChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GameDemo::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameDemo::playerStateChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GameDemo::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameDemo::npcStateChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GameDemo::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameDemo::eventStateChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (GameDemo::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameDemo::initStateChanged)) {
                *result = 8;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<GameDemo *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->envState(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->playerState(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->npcState(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->eventState(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->initState(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<GameDemo *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEnvState(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setPlayerState(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setNpcState(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setEventState(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->setInitState(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject GameDemo::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GameDemo.data,
    qt_meta_data_GameDemo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GameDemo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameDemo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameDemo.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GameDemo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void GameDemo::objectCreated(GameObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GameDemo::objectCreatedFromFile(GameObject * _t1, unsigned int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GameDemo::objectRegistToManager(GameObject * _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GameDemo::demoFuncRegistToManager(SoluteFunc _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GameDemo::envStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void GameDemo::playerStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void GameDemo::npcStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void GameDemo::eventStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void GameDemo::initStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
