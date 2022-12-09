CONFIG -= qt

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/collision/b2_broad_phase.cpp \
    src/collision/b2_chain_shape.cpp \
    src/collision/b2_circle_shape.cpp \
    src/collision/b2_collide_circle.cpp \
    src/collision/b2_collide_edge.cpp \
    src/collision/b2_collide_polygon.cpp \
    src/collision/b2_collision.cpp \
    src/collision/b2_distance.cpp \
    src/collision/b2_dynamic_tree.cpp \
    src/collision/b2_edge_shape.cpp \
    src/collision/b2_polygon_shape.cpp \
    src/collision/b2_time_of_impact.cpp \
    src/common/b2_block_allocator.cpp \
    src/common/b2_draw.cpp \
    src/common/b2_math.cpp \
    src/common/b2_settings.cpp \
    src/common/b2_stack_allocator.cpp \
    src/common/b2_timer.cpp \
    src/dynamics/b2_body.cpp \
    src/dynamics/b2_chain_circle_contact.cpp \
    src/dynamics/b2_chain_polygon_contact.cpp \
    src/dynamics/b2_circle_contact.cpp \
    src/dynamics/b2_contact.cpp \
    src/dynamics/b2_contact_manager.cpp \
    src/dynamics/b2_contact_solver.cpp \
    src/dynamics/b2_distance_joint.cpp \
    src/dynamics/b2_edge_circle_contact.cpp \
    src/dynamics/b2_edge_polygon_contact.cpp \
    src/dynamics/b2_fixture.cpp \
    src/dynamics/b2_friction_joint.cpp \
    src/dynamics/b2_gear_joint.cpp \
    src/dynamics/b2_island.cpp \
    src/dynamics/b2_joint.cpp \
    src/dynamics/b2_motor_joint.cpp \
    src/dynamics/b2_mouse_joint.cpp \
    src/dynamics/b2_polygon_circle_contact.cpp \
    src/dynamics/b2_polygon_contact.cpp \
    src/dynamics/b2_prismatic_joint.cpp \
    src/dynamics/b2_pulley_joint.cpp \
    src/dynamics/b2_revolute_joint.cpp \
    src/dynamics/b2_weld_joint.cpp \
    src/dynamics/b2_wheel_joint.cpp \
    src/dynamics/b2_world.cpp \
    src/dynamics/b2_world_callbacks.cpp \
    src/rope/b2_rope.cpp

HEADERS += \
    box2d/b2_api.h \
    box2d/b2_block_allocator.h \
    box2d/b2_body.h \
    box2d/b2_broad_phase.h \
    box2d/b2_chain_shape.h \
    box2d/b2_circle_shape.h \
    box2d/b2_collision.h \
    box2d/b2_common.h \
    box2d/b2_contact.h \
    box2d/b2_contact_manager.h \
    box2d/b2_distance.h \
    box2d/b2_distance_joint.h \
    box2d/b2_draw.h \
    box2d/b2_dynamic_tree.h \
    box2d/b2_edge_shape.h \
    box2d/b2_fixture.h \
    box2d/b2_friction_joint.h \
    box2d/b2_gear_joint.h \
    box2d/b2_growable_stack.h \
    box2d/b2_joint.h \
    box2d/b2_math.h \
    box2d/b2_motor_joint.h \
    box2d/b2_mouse_joint.h \
    box2d/b2_polygon_shape.h \
    box2d/b2_prismatic_joint.h \
    box2d/b2_pulley_joint.h \
    box2d/b2_revolute_joint.h \
    box2d/b2_rope.h \
    box2d/b2_settings.h \
    box2d/b2_shape.h \
    box2d/b2_stack_allocator.h \
    box2d/b2_time_of_impact.h \
    box2d/b2_time_step.h \
    box2d/b2_timer.h \
    box2d/b2_types.h \
    box2d/b2_weld_joint.h \
    box2d/b2_wheel_joint.h \
    box2d/b2_world.h \
    box2d/b2_world_callbacks.h \
    box2d/box2d.h \
    src/dynamics/b2_chain_circle_contact.h \
    src/dynamics/b2_chain_polygon_contact.h \
    src/dynamics/b2_circle_contact.h \
    src/dynamics/b2_contact_solver.h \
    src/dynamics/b2_edge_circle_contact.h \
    src/dynamics/b2_edge_polygon_contact.h \
    src/dynamics/b2_island.h \
    src/dynamics/b2_polygon_circle_contact.h \
    src/dynamics/b2_polygon_contact.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/CMakeLists.txt
