/****************************************************************************
** Meta object code from reading C++ file 'plugincardmanager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../plugincardmanager.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plugincardmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_PluginCardManager_t {
    uint offsetsAndSizes[6];
    char stringdata0[18];
    char stringdata1[12];
    char stringdata2[1];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_PluginCardManager_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_PluginCardManager_t qt_meta_stringdata_PluginCardManager = {
    {
        QT_MOC_LITERAL(0, 17),  // "PluginCardManager"
        QT_MOC_LITERAL(18, 11),  // "contextSent"
        QT_MOC_LITERAL(30, 0)   // ""
    },
    "PluginCardManager",
    "contextSent",
    ""
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_PluginCardManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x06,    1 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject PluginCardManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_PluginCardManager.offsetsAndSizes,
    qt_meta_data_PluginCardManager,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_PluginCardManager_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PluginCardManager, std::true_type>,
        // method 'contextSent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void PluginCardManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PluginCardManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->contextSent((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PluginCardManager::*)(QString );
            if (_t _q_method = &PluginCardManager::contextSent; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *PluginCardManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PluginCardManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PluginCardManager.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PluginManagerInterface"))
        return static_cast< PluginManagerInterface*>(this);
    if (!strcmp(_clname, "com.auratest.PluginManagerInterface/1.0.0"))
        return static_cast< PluginManagerInterface*>(this);
    return QObject::qt_metacast(_clname);
}

int PluginCardManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void PluginCardManager::contextSent(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

#ifdef QT_MOC_EXPORT_PLUGIN_V2
static constexpr unsigned char qt_pluginMetaDataV2_PluginCardManager[] = {
    0xbf, 
    // "IID"
    0x02,  0x78,  0x29,  'c',  'o',  'm',  '.',  'a', 
    'u',  'r',  'a',  't',  'e',  's',  't',  '.', 
    'P',  'l',  'u',  'g',  'i',  'n',  'M',  'a', 
    'n',  'a',  'g',  'e',  'r',  'I',  'n',  't', 
    'e',  'r',  'f',  'a',  'c',  'e',  '/',  '1', 
    '.',  '0',  '.',  '0', 
    // "className"
    0x03,  0x71,  'P',  'l',  'u',  'g',  'i',  'n', 
    'C',  'a',  'r',  'd',  'M',  'a',  'n',  'a', 
    'g',  'e',  'r', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN_V2(PluginCardManager, PluginCardManager, qt_pluginMetaDataV2_PluginCardManager)
#else
QT_PLUGIN_METADATA_SECTION
Q_CONSTINIT static constexpr unsigned char qt_pluginMetaData_PluginCardManager[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x78,  0x29,  'c',  'o',  'm',  '.',  'a', 
    'u',  'r',  'a',  't',  'e',  's',  't',  '.', 
    'P',  'l',  'u',  'g',  'i',  'n',  'M',  'a', 
    'n',  'a',  'g',  'e',  'r',  'I',  'n',  't', 
    'e',  'r',  'f',  'a',  'c',  'e',  '/',  '1', 
    '.',  '0',  '.',  '0', 
    // "className"
    0x03,  0x71,  'P',  'l',  'u',  'g',  'i',  'n', 
    'C',  'a',  'r',  'd',  'M',  'a',  'n',  'a', 
    'g',  'e',  'r', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(PluginCardManager, PluginCardManager)
#endif  // QT_MOC_EXPORT_PLUGIN_V2

QT_WARNING_POP
QT_END_MOC_NAMESPACE
