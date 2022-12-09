QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Box2D/src/collision/b2_broad_phase.cpp \
    Box2D/src/collision/b2_chain_shape.cpp \
    Box2D/src/collision/b2_circle_shape.cpp \
    Box2D/src/collision/b2_collide_circle.cpp \
    Box2D/src/collision/b2_collide_edge.cpp \
    Box2D/src/collision/b2_collide_polygon.cpp \
    Box2D/src/collision/b2_collision.cpp \
    Box2D/src/collision/b2_distance.cpp \
    Box2D/src/collision/b2_dynamic_tree.cpp \
    Box2D/src/collision/b2_edge_shape.cpp \
    Box2D/src/collision/b2_polygon_shape.cpp \
    Box2D/src/collision/b2_time_of_impact.cpp \
    Box2D/src/common/b2_block_allocator.cpp \
    Box2D/src/common/b2_draw.cpp \
    Box2D/src/common/b2_math.cpp \
    Box2D/src/common/b2_settings.cpp \
    Box2D/src/common/b2_stack_allocator.cpp \
    Box2D/src/common/b2_timer.cpp \
    Box2D/src/dynamics/b2_body.cpp \
    Box2D/src/dynamics/b2_chain_circle_contact.cpp \
    Box2D/src/dynamics/b2_chain_polygon_contact.cpp \
    Box2D/src/dynamics/b2_circle_contact.cpp \
    Box2D/src/dynamics/b2_contact.cpp \
    Box2D/src/dynamics/b2_contact_manager.cpp \
    Box2D/src/dynamics/b2_contact_solver.cpp \
    Box2D/src/dynamics/b2_distance_joint.cpp \
    Box2D/src/dynamics/b2_edge_circle_contact.cpp \
    Box2D/src/dynamics/b2_edge_polygon_contact.cpp \
    Box2D/src/dynamics/b2_fixture.cpp \
    Box2D/src/dynamics/b2_friction_joint.cpp \
    Box2D/src/dynamics/b2_gear_joint.cpp \
    Box2D/src/dynamics/b2_island.cpp \
    Box2D/src/dynamics/b2_joint.cpp \
    Box2D/src/dynamics/b2_motor_joint.cpp \
    Box2D/src/dynamics/b2_mouse_joint.cpp \
    Box2D/src/dynamics/b2_polygon_circle_contact.cpp \
    Box2D/src/dynamics/b2_polygon_contact.cpp \
    Box2D/src/dynamics/b2_prismatic_joint.cpp \
    Box2D/src/dynamics/b2_pulley_joint.cpp \
    Box2D/src/dynamics/b2_revolute_joint.cpp \
    Box2D/src/dynamics/b2_weld_joint.cpp \
    Box2D/src/dynamics/b2_wheel_joint.cpp \
    Box2D/src/dynamics/b2_world.cpp \
    Box2D/src/dynamics/b2_world_callbacks.cpp \
    Box2D/src/rope/b2_rope.cpp \
    block.cpp \
    enemy.cpp \
    level.cpp \
    main.cpp \
    mainwindow.cpp \
    mario.cpp \
    score.cpp \
    timer.cpp

HEADERS += \
    Box2D/b2_api.h \
    Box2D/b2_block_allocator.h \
    Box2D/b2_body.h \
    Box2D/b2_broad_phase.h \
    Box2D/b2_chain_shape.h \
    Box2D/b2_circle_shape.h \
    Box2D/b2_collision.h \
    Box2D/b2_common.h \
    Box2D/b2_contact.h \
    Box2D/b2_contact_manager.h \
    Box2D/b2_distance.h \
    Box2D/b2_distance_joint.h \
    Box2D/b2_draw.h \
    Box2D/b2_dynamic_tree.h \
    Box2D/b2_edge_shape.h \
    Box2D/b2_fixture.h \
    Box2D/b2_friction_joint.h \
    Box2D/b2_gear_joint.h \
    Box2D/b2_growable_stack.h \
    Box2D/b2_joint.h \
    Box2D/b2_math.h \
    Box2D/b2_motor_joint.h \
    Box2D/b2_mouse_joint.h \
    Box2D/b2_polygon_shape.h \
    Box2D/b2_prismatic_joint.h \
    Box2D/b2_pulley_joint.h \
    Box2D/b2_revolute_joint.h \
    Box2D/b2_rope.h \
    Box2D/b2_settings.h \
    Box2D/b2_shape.h \
    Box2D/b2_stack_allocator.h \
    Box2D/b2_time_of_impact.h \
    Box2D/b2_time_step.h \
    Box2D/b2_timer.h \
    Box2D/b2_types.h \
    Box2D/b2_weld_joint.h \
    Box2D/b2_wheel_joint.h \
    Box2D/b2_world.h \
    Box2D/b2_world_callbacks.h \
    Box2D/box2d/b2_api.h \
    Box2D/box2d/b2_block_allocator.h \
    Box2D/box2d/b2_body.h \
    Box2D/box2d/b2_broad_phase.h \
    Box2D/box2d/b2_chain_shape.h \
    Box2D/box2d/b2_circle_shape.h \
    Box2D/box2d/b2_collision.h \
    Box2D/box2d/b2_common.h \
    Box2D/box2d/b2_contact.h \
    Box2D/box2d/b2_contact_manager.h \
    Box2D/box2d/b2_distance.h \
    Box2D/box2d/b2_distance_joint.h \
    Box2D/box2d/b2_draw.h \
    Box2D/box2d/b2_dynamic_tree.h \
    Box2D/box2d/b2_edge_shape.h \
    Box2D/box2d/b2_fixture.h \
    Box2D/box2d/b2_friction_joint.h \
    Box2D/box2d/b2_gear_joint.h \
    Box2D/box2d/b2_growable_stack.h \
    Box2D/box2d/b2_joint.h \
    Box2D/box2d/b2_math.h \
    Box2D/box2d/b2_motor_joint.h \
    Box2D/box2d/b2_mouse_joint.h \
    Box2D/box2d/b2_polygon_shape.h \
    Box2D/box2d/b2_prismatic_joint.h \
    Box2D/box2d/b2_pulley_joint.h \
    Box2D/box2d/b2_revolute_joint.h \
    Box2D/box2d/b2_rope.h \
    Box2D/box2d/b2_settings.h \
    Box2D/box2d/b2_shape.h \
    Box2D/box2d/b2_stack_allocator.h \
    Box2D/box2d/b2_time_of_impact.h \
    Box2D/box2d/b2_time_step.h \
    Box2D/box2d/b2_timer.h \
    Box2D/box2d/b2_types.h \
    Box2D/box2d/b2_weld_joint.h \
    Box2D/box2d/b2_wheel_joint.h \
    Box2D/box2d/b2_world.h \
    Box2D/box2d/b2_world_callbacks.h \
    Box2D/box2d/box2d.h \
    Box2D/src/dynamics/b2_chain_circle_contact.h \
    Box2D/src/dynamics/b2_chain_polygon_contact.h \
    Box2D/src/dynamics/b2_circle_contact.h \
    Box2D/src/dynamics/b2_contact_solver.h \
    Box2D/src/dynamics/b2_edge_circle_contact.h \
    Box2D/src/dynamics/b2_edge_polygon_contact.h \
    Box2D/src/dynamics/b2_island.h \
    Box2D/src/dynamics/b2_polygon_circle_contact.h \
    Box2D/src/dynamics/b2_polygon_contact.h \
    backgrounditem.h \
    block.h \
    box2d/box2d.h \
    enemy.h \
    health.h \
    level.h \
    mainwindow.h \
    mario.h \
    score.h \
    timer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    maps_src.qrc

DISTFILES += \
    Box2D/src/CMakeLists.txt \
    libBox2D.a

unix|win32: LIBS += -L$$PWD/../build-Box2D-Desktop_Qt_6_4_1_MinGW_64_bit-Release/release/ -lBox2D

INCLUDEPATH += $$PWD/../build-Box2D-Desktop_Qt_6_4_1_MinGW_64_bit-Release/release
DEPENDPATH += $$PWD/../build-Box2D-Desktop_Qt_6_4_1_MinGW_64_bit-Release/release

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../build-Box2D-Desktop_Qt_6_4_1_MinGW_64_bit-Release/release/Box2D.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../build-Box2D-Desktop_Qt_6_4_1_MinGW_64_bit-Release/release/libBox2D.a

SUBDIRS += \
    Box2D/Box2D.pro
